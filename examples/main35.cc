// main36.cc is a part of the PYTHIA event generator.
// Copyright (C) 2017 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program.
// It calls pythia6 routines to do full event generation in Pythia6 but process them in C++ instead of fortran.

#include "Pythia8/Pythia.h"

using namespace Pythia8;



extern "C" {

  // Particle record.
  extern struct {
    int n[1], npad[1], k[5][4000];
    double p[5][4000], v[5][4000];
  } pyjets_;

    extern struct {
    int mstp[200];
    double parp[200];
    int msti[200];
    double pari[200];
  } pypars_;

void pygive_(const char *chin, int len_chin);

void pyinit_(const char *frame, const char *beam,
         const char *target, double *win,
         int len_frame, int len_beam, int len_target);

void pyevnt_();
void pylist_(int *mlist);
void pystat_(int *mlist);
}


int main()
{
  pyjets_.p[0][0]=0;
  pyjets_.p[1][0]=0;
  pyjets_.p[2][0]=820.0;

  pyjets_.p[0][1]=0;
  pyjets_.p[1][1]=0;
  pyjets_.p[2][1]=-26.700;
  
  //setting process of interest
  //mstp values required to match dis of pythia8 run
  
  string line="MSEL=2";
  pygive_(line.c_str(), line.size());
//   line="MSUB(10)=1";
//  pygive_(line.c_str(), line.size());
/*  line="MSTP(17)=1";
  pygive_(line.c_str(), line.size());
  line="MSTP(19)=1";
  pygive_(line.c_str(), line.size());
  
*/
  string frame="3MOM";
  string beama="p";
  string beamb="gamma/e-";
  double win=0.0;
  pyinit_(frame.c_str(),beama.c_str(),beamb.c_str(),&win,frame.size()
    ,beama.size(),beamb.size());

  // Create the output histogram.
   Hist hst("eT flow", 26, -1.25, 5.5);

  // Generate events.
  int iEvent(0),iAccept(0),one(1),iprint(0);
  int dis=0;
  while (iEvent < 35000) { 
    pyevnt_();
   if(pypars_.msti[0]<100) continue;
//    cout << iEvent << "\t";
    //Print few events.
//    pylist_(&one);
    ++iEvent;++iprint;
    if(iprint==1000) {
      iprint=0;
     cout << "event: "<< iEvent << endl;
   }
//   cout << pypars_.pari[32] << endl;
    // Skip if x < 1e-3.
    if (pypars_.pari[32] < 1e-3) continue;

    // find outoging electron
    int iLep;
    for(int i=0;i<pyjets_.n[0];++i)
      if(pyjets_.k[0][i]<10 && pyjets_.k[1][i]==11) {
        iLep = i;
        break;
      }
//      cout << iLep << endl;
    // Determine the relevant momentum vectors.
      Vec4 hIn,lIn,lOut,gamma;

      for(int i=0;i<4;++i) {
      hIn[i+1] =pyjets_.p[i][0];    // Incoming proton.
      lIn[i+1] =pyjets_.p[i][1];    // Incoming electron.
      lOut[i+1]=pyjets_.p[i][iLep]; // Outgoing electron.
      }                               
      gamma = lIn - lOut;           // Exchanged photon.

    
  // Calculate W2. Apply cuts to W2 and the outgoing electron.

    double w2 = (gamma + hIn).m2Calc();
  //  cout << w2 << endl;
    if (w2 < 3000) continue;
    if (lOut.e() < 14) continue;
    if (lOut.theta() < 157.0*M_PI/180) continue;
    if (lOut.theta() > 172.5*M_PI/180) continue;

    
    // Calculate the forward hadronic energy and apply cut.
    double e = 0;
    Vec4 iparticle;
    for (int iPrt = 0; iPrt < pyjets_.n[0]; ++iPrt) {
      if (iPrt == iLep) continue;
      if (pyjets_.k[0][iPrt]>10 || pyjets_.k[0][iPrt] <1  ) continue;
      iparticle[1]=pyjets_.p[0][iPrt];
      iparticle[2]=pyjets_.p[1][iPrt];
      iparticle[3]=pyjets_.p[2][iPrt];
      iparticle[4]=pyjets_.p[3][iPrt];
      if (iparticle.theta() < 4.4*M_PI/180) continue;
      if (iparticle.theta() > 15.0*M_PI/180) continue;
      e += iparticle.e();
    }
//    cout << e << endl;
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
    for (int iPrt = 0; iPrt < pyjets_.n[0]; ++iPrt) {
      if (iPrt == iLep) continue;
      if (pyjets_.k[0][iPrt]>10 || pyjets_.k[0][iPrt] <1 ) continue;
      iparticle[1]=pyjets_.p[0][iPrt];
      iparticle[2]=pyjets_.p[1][iPrt];
      iparticle[3]=pyjets_.p[2][iPrt];
      iparticle[4]=pyjets_.p[3][iPrt];
      if (iparticle.theta() < 4.4*M_PI/180) continue;
      if (iparticle.theta() > 174.0*M_PI/180) continue;
      iparticle.rotbst(hcms);
      hst.fill(iparticle.eta(), iparticle.eT());
    } ++iAccept; 

    //count no of dis events when not restricting histogram
    //to only dis events
    //if(pypars_.msti[0]==99) dis++;
  }

  // Scale the histogram (and print).
  hst /= iAccept*(5.5 + 1.25)/26;
  cout << hst;
  cout << iAccept << endl;
  //cout <<"number of events from dis : " << dis << endl;

  // Save the histogram to a file.
  hst.table("pythia6.txt");
  pystat_(&one);

  
return 0;
}



  
