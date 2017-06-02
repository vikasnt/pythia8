// LHAPythia6.h is a part of the PYTHIA event generator.
// Copyright (C) 2017 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.
// Author: Philip Ilten, May 2015.

#ifndef Pythia8_LHAPythia6_H
#define Pythia8_LHAPythia6_H

#include "Pythia8Plugins/LHAFortran.h"
#include <sys/stat.h>
#include <unistd.h>

namespace Pythia8 {

//==========================================================================

// Give access to the pythia6 routines

extern "C" {

  // some variables
  #define ksusy1 1000000
  #define ksusy2 2000000
  #define ktechn 3000000
  #define kexcit 4000000
  #define kdimen 5000000

  //required int variables
  int pyk,pychge,pycomp;

  // some common blocks

  extern struct {
    int ngrdec[1];
  } decmod_;


  extern struct {
    int nevhep[1], nhep[1], isthep[4000], idhep[4000], jmohep[2][4000], 
      jdahep[2][4000];
    double phep[5][4000], vhep[4][4000];
  } hepevt_;

  extern struct {
    double ysav[1], ymax[1], resmax[1];
  } intsav_;

  extern struct {
    double xkappa[1];
  } kappa_;

  extern struct {
    int ihist[4], indx[1000];
    double bin[20000];
  } pybins_;

  extern struct {
    int mco[4000][2], ncc[1], jcco[4000][2], jccn[4000][2], maccpt[1];
  } pycbls_;

  extern struct {
    int nct[1], mct[4000][2];
  } pyctag_;

  extern struct {
    double alpha[1], alphas[1], sw2[1], mw2[1], tanb[1], vtb[1], v[1], a[1];
  } pyctbh_;

  extern struct {
    int mstu[200];
    double paru[200];
    int mstj[200];
    double parj[200];
  } pydat1_;

  extern struct {
    int kchg[500][4];
    double pmas[500][4], parf[2000], vckm[4][4];
  } pydat2_;

  extern struct {
    int mdcy[500][3], mdme[8000][2];
    double brat[8000];
    int kfdp[8000][5];
  } pydat3_;

  extern struct {
    char chaf[500][2];
  } pydat4_;

  extern struct {
    int mrpy[6];
    double rrpy[100];
  } pydatr_;

  extern struct {
    double x1[1];
  } pyg2dx_;

  extern struct {
    double hhh[7];
  } pyhtri_;

  extern struct {
    int mint[400];
    double vint[400];
  } pyint1_;

  extern struct {
    int iset[500], kfpr[500][2];
    double coef[500][20];
    int icol[40][4][2];
  } pyint2_;

  extern struct {
    double xsfx[2][81];
    int isig[1000][3];
    double sigh[1000];
  } pyint3_;

  extern struct {
    int mwid[500];
    double wids[500][5];
  } pyint4_;

  extern struct {
    int ngenpd[1], ngen[501][3];
    double xsec[501][3];
  } pyint5_;

  extern struct {
    char proc[501];
  } pyint6_;

  extern struct {
    double sigt[7][7][6];
  } pyint7_;

  extern struct {
    double xpvmd[13], xpanl[13], xpanh[13], xpbeh[13], xpdir[13];
  } pyint8_;

  extern struct {
    double vxpvmd[13], vxpanl[13], vxpanh[13], vxpdgm[13];
  } pyint9_;

  extern struct {
    double xxc[10];
    struct {double r, i;} cxc[8];
  } pyintc_;

  extern struct {
    int kfival[2][3], nmi[2], imi[2][800][2], nvc[2][13];
    double xassoc[2][13][240], xpsvc[13][242], pvctot[2][3], xmi[2][240], 
      pt2mi[240];
    int imisep[241];
  } pyintm_;

  extern struct {
    double xxm[20];
  } pyints_;

  extern struct {
    int mjn1mx[1], mjn2mx[1], mjoind[2][240];
  } pyisjn_;

  extern struct {
    int mimx[1], jsmx[1], kflamx[1], kflcmx[1], kfbeam[2], nisgen[2][240];
    double pt2mx[1], pt2amx[1], zmx[1], rm2cmx[1], q2bmx[1], phimx[1];
  } pyismx_;

  extern struct {
    int n[1], npad[1], k[4000][5];
    double p[4000][5], v[4000][5];
  } pyjets_;

  extern struct {
    char cpro[2], cver[2];
  } pylh3c_;

  extern struct {
    int modsel[200];
    double parmin[100], parext[200], rmsoft[101], au[3][3], ad[3][3], ae[3][3];
  } pylh3p_;

  extern struct {
    double rvlam[3][3][3], rvlamp[3][3][3], rvlamb[3][3][3];
  } pymsrv_;

  extern struct {
    int imss[100];
    double rmss[100];
  } pymssm_;

  extern struct {
    int mstp[200];
    double parp[200];
    int msti[200];
    double pari[200];
  } pypars_;

  extern struct {
    int npart[1], npartd[1], ipart[1000];
    double ptpart[1000];
  } pypart_;

  extern struct {
    int iued[100];
    double rued[100];
  } pypued_;

  extern struct {
    int nqnum[1], nqdum[1], kqnum[500][10];
  } pyqnum_;

  extern struct {
    double ab[2][16][2], rms[4], res[6][2];
    int intres[6][3], idr[1], idr2[1], dcmass[1], kfr[3];
  } pyrvnv_;

  extern struct {
    double rm[4], a[2], b[2], resm[2], resw[2];
    int mflag[1];
  } pyrvpm_;

  extern struct {
    int isub[1], isubsv[1], mmin1[1], mmax1[1], mmin2[1], mmax2[1], mmina[1], 
      mmaxa[1], kfac[2][81];
    double comfac[1], fack[1], faca[1], sh[1], th[1], uh[1], sh2[1], th2[1], 
      uh2[1], sqm3[1], sqm4[1], shr[1], sqpth[1], taup[1], be34[1], cth[1], 
      x[2], sqmz[1], sqmw[1], gmmz[1], gmmw[1], aem[1], as[1], xw[1], xw1[1], 
      xwc[1], xwv[1], poll[1], polr[1], polll[1], polrr[1];
  } pysgcm_;

  extern struct {
    double zmix[4][4], umix[2][2], vmix[2][2], smz[4], smw[2], sfmix[16][4], 
      zmixi[4][4], umixi[2][2], vmixi[2][2];
  } pyssmt_;

  extern struct {
    int msel[1], mselpd[1], msub[500], kfin[2][81];
    double ckin[200];
  } pysubs_;

  extern struct {
    double coefx[187][2];
  } pytcco_;

  extern struct {
    int itcm[100];
    double rtcm[100];
  } pytcsm_;

  extern struct {
    double xresi[1], xresj[1], xresk[1], xresij[1], xresik[1], xresjk[1], 
      rvlijk[1], rvlkij[1], rvljki[1], rvljik[1];
  } rvgsto_;

  extern struct {
    float super[72];
  } sspar_;

  extern struct {
    float mss[32], gss[31], mgutss[1], ggutss[1], agutss[1], ftgut[1], 
      fbgut[1], ftagut[1], fngut[1];
  } sugmg_;

  extern struct {
    float xnusug[18];
  } sugnu_;

  extern struct {
    float xtanb[1], msusy[1], amt[1], mgut[1], mu[1], g2[1], gp[1], v[1], 
      vp[1], xw[1], a1mz[1], a2mz[1], asmz[1], ftamz[1], fbmz[1], b[1], 
      sin2b[1], ftmt[1], g3mt[1], vev[1], higfrz[1], fnmz[1], amnrmj[1];
    int nogood[1], ial3un[1], itachy[1], mhpneg[1];
    float asm3[1], vumt[1], vdmt[1], asmtp[1], asmss[1], m3q[1];
  } sugpas_;

  extern struct {
    float xisain[24], xsugin[7], xgmin[14], xnrin[4], xamin[7];
  } sugxin_;

  extern struct {
    double sw021[1], cw021[1];
  } sw1_;

  extern struct {
    int ires[1], jres[1];
    double xmas[3], xwid[3], ymas[2], ywid[2];
  } tcpara_;

  extern struct {
    double xmplnk[1], xmd[1], rinv[1];
    int ndim[1];
  } uedgra_;

  extern struct {
    int nptype[1], ngroup[1], nset[1], mode[1], nfl[1], lo[1];
    double tmas[1];
  } w50511_;

  extern struct {
    double qcdl4[1], qcdl5[1];
  } w50512_;

  extern struct {
    double xmin[1], xmax[1], q2min[1], q2max[1];
  } w50513_;
// default data setting
  void pydata_();  

// internal pythia6 parser
  void pygive_(char *chin, int len_chin);

// Initialize pythia6
  void pyinit_(char *frame, int len_frame, char *beam, int len_beam, 
    char *target, int len_target, double *win);

// Generate an pythia6 event.
  void pyevnt_();
  void pyevnw_();

// print cross section
  void pystat_(int *mstat);

}

//==========================================================================

// A derived class from LHAupFortran which allows pythia6
// to be directly interfaced with Pythia via a plugin structure. 

class LHAupPythia6 : public LHAupFortran {

public:

  // Constructor.
  LHAupPythia6();

  bool readString(string name);
protected:

  // Call pyinit and fill the HEPRUP commonblock.
  bool fillHepRup();

  // Call pyevnt and fill the HEEUP commonblock.
  bool fillHepEup();

private:

  int len_frame,len_beam,len_target;
  char frame[10],beam[10],target[10];
  double win;
  int nev,nprt;   // number of events and nprt??
 
};

//--------------------------------------------------------------------------

// Constructor.

LHAupPythia6::LHAupPythia6() {


  string line;
  char *in;
  int len_in;


  string name = "main36.txt";
//set default parameters before run starts
std::cout << "badumm tss" << std::endl;
// parsing user input using pythia internal parser
  fstream input(name.c_str(), ios::in);
  input >> frame >> beam >> target >> win;
  input >> nev >> nprt;
  cout << frame << beam << target << win<<endl;
  cout <<nev << nprt <<endl;
  while (getline(input, line, '\n')) {
	in = &line[0];
	len_in = strlen(in);
	pygive_(in,len_in);
  }
len_frame = strlen(frame);
  len_beam = strlen(beam);
  len_target = strlen(target);

  // initialise pythia6
  pyinit_(frame,len_frame,beam,len_beam,target,len_target,&win);
  pydata_();

  cout << " code reaches here"<<endl;

}

//----------------------------------------------------------------------

bool LHAupPythia6::readString(string name) {

   char *in; int len_in;
   in = &name[0];
   len_in = strlen(in);
   pygive_(in,len_in);

   return 0;
 }


//------------------------------------------------------------------------


// Call pythia6 init and fill the HEPRUP commonblock.

bool LHAupPythia6::fillHepRup() {

/*
int a=1;
  // Generate the event nev times.
	for(int i=0; i<nev ;++i)
    pyevnt_();
	//pystat_(&a);*/

  //set user given options from settings map
  len_frame = strlen(frame);
  len_beam = strlen(beam);
  len_target = strlen(target);

  // initialise pythia6
  pyinit_(frame,len_frame,beam,len_beam,target,len_target,&win);
  return fillHepEup();

}

//--------------------------------------------------------------------------

//  call pyevnt, and fill the HEPEUP commonblock.

bool LHAupPythia6::fillHepEup() {
  int a=1;
  // Generate the event nev times.
	for(int i=0; i<nev ;++i)
    pyevnt_();
	pystat_(&a);

  return true;


}

//--------------------------------------------------------------------------

//==========================================================================

} // end namespace Pythia8

#endif // Pythia8_LHAPythia6_H
