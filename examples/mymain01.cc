#include "Pythia8/Pythia.h"
using namespace Pythia8;

int main() {
  Pythia py8;
  py8.readString("Beams:frameType = 2");
  py8.readString("Beams:idA = 2212");
  py8.readString("Beams:eA = 820");
  py8.readString("Beams:idB = 11");
  py8.readString("Beams:eB = 26.7");
  py8.readString("WeakBosonExchange:ff2ff(t:gmZ) = on");
  py8.readString("WeakZ0:gmZmode = 1");
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
  hst.table("pythia8.txt");
  return 0;
}

