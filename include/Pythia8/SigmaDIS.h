// SigmaDIS.h is a part of the PYTHIA event generator.
// Copyright (C) 2017 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.


#ifndef Pythia8_SigmaDIS_H
#define Pythia8_SigmaDIS_H

#include "Pythia8/PythiaComplex.h"
#include "Pythia8/SigmaProcess.h"

namespace Pythia8 {
    
//=============================================================================
    
// A derived class for gamma* f -> f.
    
class Sigma1gammaf2f : public Sigma1Process {

public:
    
  // Constructor.
    Sigma1gammaf2f() {}
    
  // Initialize process.

   //not needed as of now, should remove later 
  //virtual void initProc();
    
  // Calculate flavour-independent parts of cross section.
    virtual void sigmaKin();
    
  // Calculate sigmaHat(sHat).
    virtual double sigmaHat();
    
  // Select flavour, colour and anticolour.
    virtual void setIdColAcol();
    
  // Info on the subprocess.
    virtual string name()           const {return "gamma* f -> f";}
    //keeping code equal to max allowd for EW process for now
    virtual int code()              const {return 299;}  
    virtual string inFlux()         const {return "fgm";}
    
private:
  
  // parameters
    double pid,m1,m2,m1s,m2s;
    double sigma0,rhoms,sigma;
    double rdrs,xga;
    
};
    
//==================================================================================
    
}  // end namespace Pythia8

#endif //Pythia8_SigmaDIS_H
