// mymain01.cc is a part of the PYTHIA event generator.
// Copyright (C) 2017 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program to run DIS:gammaf2f.
#include "Pythia8/Pythia.h"

using namespace Pythia8;

int main()
{
  Pythia py8;

  // Change input beam energy etc as needed 
  // Do not use lepton2gamma.
  py8.readString("Beams:frameType = 2");
  py8.readString("Beams:idA = 2212");
  py8.readString("Beams:idB = 11");
  py8.readString("Beams:eA = 820.");
  py8.readString("Beams:eB = 26.7");
  py8.readString("DIS:gammaf2f= on");

  py8.init();
    for(int ie=0;ie<1000;++ie) {
       py8.next();
       //py8.event.list();
  }
  //print errors  
  py8.stat();
 return 0;

}