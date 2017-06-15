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

// Give access to the PYTHIA 6 commonblocks and subroutines.

extern "C" {

  // Cross-section info.
  extern struct {
    int ngenpd[1], ngen[3][501];
    double xsec[3][501];
  } pyint5_;

  // Particle record.
  extern struct {
    int n[1], npad[1], k[5][4000];
    double p[5][4000], v[5][4000];
  } pyjets_;

  // Settings parser.
  void pygive_(const char *chin, int len_chin);

  // Initialization sub-routine.
  void pyinit_(const char *frame, const char *beam,
	       const char *target, double *win,
	       int len_frame, int len_beam, int len_target);

  // Initialize the beams.
  void pyinbm_(const char *chfram, const char *chbeam, const char *chtarg,
	       double *win, int len_chfram, int len_chbeam, int len_chtarg);

  // LHA hard process event generation.
  void pyupev_();

  // LHA hard process run initialization.
  void pyupin_();

  // List the event.
  void pylist_(int *mlist);

}

//==========================================================================

// A derived class from LHAupFortran which allows a the hard processes
// generated in Pythia 6 to be directly interfaced with Pythia 8.

class LHAupPythia6 : public LHAupFortran {

public:

  // Constructor.
  LHAupPythia6(Pythia *pythia, string frameType, string idA, string idB,
	       double win);
  
  // Read a configuration line.
  bool readString(string line);

  // Read a file.
  bool readFile(string name);

protected:

  // Call pyinit and fill the HEPRUP commonblock.
  bool fillHepRup();

  // Call pyevnt and fill the HEPEUP commonblock.
  bool fillHepEup();

private:

  // Beam configuration members.
  string frameType, idA, idB;
  double win;
 
};

//--------------------------------------------------------------------------

// Constructor.

LHAupPythia6::LHAupPythia6(Pythia *pythia, string frameTypeIn, string idAIn,
			   string idBIn, double winIn) :
  frameType(frameTypeIn), idA(idAIn), idB(idBIn), win(winIn) {

  readString("mstp(124) = 2");
  pythia->readString("Beams:frameType = 5");
  pythia->setLHAupPtr(this);

}

//--------------------------------------------------------------------------

// Read a setting in from a string.

bool LHAupPythia6::readString(string line) {

  pygive_(line.c_str(), line.size());
  return true;

}

//-------------------------------------------------------------------------

// Read settings from a file.

bool LHAupPythia6::readFile(string name) {

  fstream config(name.c_str(), ios::in); string line;
  while (getline(config, line, '\n')) readString(line);
  config.close();
  return true;

}

//------------------------------------------------------------------------

// Call pyinit, pyupin, and fill the HEPRUP commonblock.

bool LHAupPythia6::fillHepRup() {

  string chfram(12, ' '), chbeam(12, ' '), chtarg(12, ' ');
  chfram.replace(0, frameType.size(), frameType);
  chbeam.replace(0, idA.size(), idA);
  chtarg.replace(0, idB.size(), idB);
  pyinbm_(chfram.c_str(), chbeam.c_str(), chtarg.c_str(),
	  &win, chfram.size(), chbeam.size(), chtarg.size());
  Vec4 pA(pyjets_.p[0][0], pyjets_.p[1][0], pyjets_.p[2][0], pyjets_.p[3][0]);
  Vec4 pB(pyjets_.p[0][1], pyjets_.p[1][1], pyjets_.p[2][1], pyjets_.p[3][1]);
  pyinit_(frameType.c_str(), idA.c_str(), idB.c_str(), &win,
	  frameType.size(), idA.size(), idB.size());
  pyupin_();
  for (int ip = 0; ip < heprup_.nprup; ++ip)
    heprup_.xsecup[ip] = pyint5_.xsec[0][heprup_.lprup[ip]]*1e9;
  heprup_.ebmup[0] = pA.e();
  heprup_.ebmup[1] = pB.e();
  return true;

}

//--------------------------------------------------------------------------

// Call pyevnt and fill the HEPEUP commonblock.
// TO-DO: handle the random numbers.

bool LHAupPythia6::fillHepEup() {

  pyupev_();
  return true;

}

//==========================================================================

} // end namespace Pythia8

#endif // Pythia8_LHAPythia6_H
