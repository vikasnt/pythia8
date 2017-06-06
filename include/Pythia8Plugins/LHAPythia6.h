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

// internal pythia6 parser
  void pygive_(const char *chin, int len_chin);

// Initialize pythia6
  void pyinit_(const char *frame, const char *beam,
	       const char *target, double *win,
	       int len_frame, int len_beam, int len_target);

// Generate an pythia6 event.
  void pyevnt_();
  void pyevnw_();

// filling HEPEUP and HEPRUP common blocks in pythia6
  void pyupev_();
  void pyupin_();
}

//==========================================================================

// A derived class from LHAupFortran which allows pythia6
// to be directly interfaced with Pythia via a plugin structure. 

class LHAupPythia6 : public LHAupFortran {

public:

  // Constructor.
  LHAupPythia6(Pythia *pythia, string frameType, string idA, string idB, double win);
  
  // Deconstructor
  ~LHAupPythia6();
  void readString(string line);

  void readFile(string file);

protected:

  // Call pyinit and fill the HEPRUP commonblock.
  bool fillHepRup();

  // Call pyevnt and fill the HEEUP commonblock.
  bool fillHepEup();

private:

  int nev;   // number of events
  string frameType,idA,idB;
  double win;
 
};

//--------------------------------------------------------------------------

// Constructor.

 LHAupPythia6::LHAupPythia6(Pythia *pythia, string frameType, string idA, string idB, 
			   double win) {

  this->frameType = frameType;
  this->idA = idA;
  this->idB = idB;
  this->win = win;
  
  pythia->setLHAupPtr(this);
}

//-------------------------------------------------------------------------

// Deconstructor
LHAupPythia6::~LHAupPythia6() {
}

//--------------------------------------------------------------------------

// Read a setting in from a string.

 void LHAupPythia6::readString(string line) {

  pygive_(line.c_str(), line.size());

}

//-------------------------------------------------------------------------

// Read settings from a file.

 void LHAupPythia6::readFile(string file) {

   string line;
   fstream input(file.c_str(), ios::in);
   while (getline(input, line, '\n')) {
     pygive_(line.c_str(), line.size());
   }

 }

//------------------------------------------------------------------------


// Call pythia6 init and fill the HEPRUP commonblock.

bool LHAupPythia6::fillHepRup() {

  
  // initialise pythia6
  pyinit_(frameType.c_str(), idA.c_str(), idB.c_str(), &win,
	  frameType.size(), idA.size(), idB.size());

  //fill HEPRUP
  pyupin_();

  return fillHepEup();

}

//--------------------------------------------------------------------------

//  call pyevnt, and fill the HEPEUP commonblock.

bool LHAupPythia6::fillHepEup() {

  // Generate the event
   pyevnt_();

   //FILL HEPEUP
   pyupev_();

  return true;

}

//--------------------------------------------------------------------------

//==========================================================================

} // end namespace Pythia8

#endif // Pythia8_LHAPythia6_H
