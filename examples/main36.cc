// main36.cc is a part of the PYTHIA event generator.
// Copyright (C) 2017 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program.
// It illustrates how PYTHIA6 can be interfaced with PYTHIA8.

#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/LHAPythia6.h"

using namespace Pythia8;

int main() {
  Pythia py8;

  // Constructor for pythia6 plugin class.
  // LHAupPythia6(*PYTHIA8,FRAME,BEAM,TARGET,WIN)
  // where last 4 arguments are exactly same 
  // as what you would pass to Pythia6 in 
  // PYINIT(FRAME,BEAM,TARGET,WIN) call.
  LHAupPythia6 py6(&py8, "3mom", "p+", "e-", 0.0);

  // Flags to be set for Pythia6. These flags should
  // be modified by user according to the details of
  // their run. These flags are directly passed to pythia6
  // so look at Pythia6 documentation for further info. 
  py6.readString("p(1,1)    = 0");
  py6.readString("p(1,2)    = 0");
  py6.readString("p(1,3)    = 819.999");
  py6.readString("p(2,1)    = 0");
  py6.readString("p(2,2)    = 0");
  py6.readString("p(2,3)    = -26.700");
  py6.readString("msel      = 0") ;
  py6.readString("msub(10)  = 1");
  py6.readString("mstp(21)  = 1");

  // You can comment out all py6 statement above and 
  // uncomment py8.readString() calls below to instead 
  // do a standard Pythia8 run. This allows for easy
  // comparison of results from Pythia8 and Pythia6.
  // Modify options according to details of your run.
  // Look at Pythia8 documentation for more info.
  //py8.readString("Beams:frameType = 2");
  //py8.readString("Beams:idA = 2212");
  //py8.readString("Beams:eA = 820");
  //py8.readString("Beams:idB = 11");
  //py8.readString("Beams:eB = 26.7");
  //py8.readString("WeakBosonExchange:ff2ff(t:gmZ) = on");
  //py8.readString("WeakZ0:gmZmode = 1");

  // Following code will work whether you do a Pythia6 or 
  // Pythia8 run above. You can freely change anything
  // below according to your need. You will need to modify almost 
  // all of the code below according to details of your run 
  // for the output to make sense. 

  py8.init();

  // Create the output histogram.
  Hist hst("eT flow", 26, -1.25, 5.5);

  // Generate 100000 events.
  int iEvent(0), iAccept(0), iAttempt(0);
  Event &event = py8.event;
  while (iEvent < 1e5 && iAttempt < 1e6) {
    ++iAttempt;
    if (!py8.next()) continue;
    ++iEvent;
    
    // Skip if x < 1e-3.
    if (py8.info.x1() < 1e-3) continue;

    // Determine the relevant momentum vectors.
    int  iLep  = event[2].iBotCopyId();
    Vec4 hIn   = event[1].p();                     // Incoming proton.
    Vec4 lIn   = event[2].p();                     // Incoming electron.
    Vec4 lOut  = event[iLep].p();                  // Outgoing electron.
    Vec4 gamma = lIn - lOut;                       // Exchanged photon.

    // Calculate W2. Apply cuts to W2 and the outgoing electron.
    double w2 = (gamma + hIn).m2Calc();
    if (w2 < 3000) continue;
    if (lOut.e() < 14) continue;
    if (lOut.theta() < 157.0*M_PI/180) continue;
    if (lOut.theta() > 172.5*M_PI/180) continue;

    // Calculate the forward hadronic energy and apply cut.
    double e = 0;
    for (int iPrt = 0; iPrt < py8.event.size(); ++iPrt) {
      Particle *prt = &event[iPrt];
      if (iPrt == iLep) continue;
      if (!prt->isFinal()) continue;
      if (prt->theta() < 4.4*M_PI/180) continue;
      if (prt->theta() > 15.0*M_PI/180) continue;
      e += prt->e();
    }
    if (e < 0.5) continue;

    // Determine the rotations/boost for the hadronic CMS.
    RotBstMatrix hcms;
    hcms.bstback(gamma + hIn);
    gamma.rotbst(hcms);
    hcms.rot(0, -gamma.phi());
    hcms.rot(-gamma.theta(), 0);
    lOut.rotbst(hcms);
    hcms.rot(0, -lOut.phi());
    hIn.rotbst(hcms);

    // Determine the transverse energy and fill the histogram.
    for (int iPrt = 0; iPrt < py8.event.size(); ++iPrt) {
      Particle *prt = &py8.event[iPrt];
      if (iPrt == iLep) continue;
      if (!prt->isFinal()) continue;
      if (prt->theta() < 4.4*M_PI/180) continue;
      if (prt->theta() > 174.0*M_PI/180) continue;
      prt->rotbst(hcms);
      hst.fill(prt->eta(), prt->eT());
    } ++iAccept;
  }

  // Scale the histogram (and print).
  hst /= iAccept*(5.5 + 1.25)/26;
  cout << hst;

  // Save the histogram to a file.
  hst.table("histogram.txt");

  return 0;
}
