// SigmaDIS.cc is a part of the PYTHIA event generator.
// Copyright (C) 2017 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

#include "Pythia8/SigmaDIS.h"

namespace Pythia8 {
    
//======================================================================
    
// Sigma1gammaf2f class.
// Cross section for gamma* f -> f  (f is lepton).
    
//----------------------------------------------------------------------
    
// Initialize process.
void Sigma1gammaf2f::initProc() {
        
   // if needed
    
}
    
    
// Evaluate d(sigmaHat)/d(tHat), part independent of incoming flavour.
    
void Sigma1gammaf2f::sigmaKin() {
    
    // Store squared mass of beam and target particles
    if(beamAPtr->isGamma()) {
        m1  = beamAPtr->m();
        m2  = beamBPtr->m();
        pid = beamBPtr->id();
    }
    else { /* beam B is photon*/
        m1  = beamBPtr->m();
        m2  = beamAPtr->m();
        pid = beamAPtr->id();
    }
    m1s = m1*m1;
    m2s = m2*m2;
   // cout << beamAPtr->id()<<" and " <<beamBPtr->id() << endl;
    sigma0 = 0.389380 * 4. * pow(M_PI,2) * alpEM;  // *vint(315)*vint(316) at lowest order is equal to 1
    rhoms = pow2(particleDataPtr->m0(113));
   
    sigma0 /= (m1s + rhoms);
    // we are only running the case mstp(19)=1 for now here
    // need to define a flag and then below code will work
  /*  if( patronic_cross_section_flag == 0 )      sigma0 /= m1s;
    else if(patronic_cross_section_flag== 1 ) sigma0 /= (m1s + rhoms);
    else if(patronic_cross_section_flag== 2 ) sigma0 *= m1s / pow2(m1s + rhoms);
    else {
        sigma0 *= m1s / pow2(m1s + rhoms); //   w2ga = sH
    
    //if both beam particles are photons
    if(beamAPtr->isGamma() && beamBPtr->isGamma()) {
        rdrs = 4.1e-3 * pow(sH,2.167);
        rdrs /= pow2(m1s + (0.15*sH))*pow(m1s,0.75)*((1. + 0.11*m1s*m2s)/(1. + 0.02*pow(m2s)));
        xga  = m1s /( sH + m1s + m2s);
    }
    else {
        rdrs = (1.5e-4*pow(sH,2.167))/(pow2(m1s + 0.041*sH)*pow(m1s,0.57));
            xga  = m1s/(sH + m1s - pow2(particleDataPtr->m0(pid)));
    }
    sigma0 *= exp(-max(1e-10,rdrs));
    if(patronic_cross_section_flag == 4 ) sigma0 /= max(1e-2,xga);
    }
*/
 }

// Evaluate sigmahat(sHat).
double Sigma1gammaf2f::sigmaHat() {
    
    int id1Abs = abs(id1);
    double  e1 = couplingsPtr->ef(id1Abs);
    
    sigma = sigma0 * pow2(e1);
   
    return sigma;
    }
    
 void Sigma1gammaf2f::setIdColAcol() {

    cout << id1 << " and " << id2 << endl;
 	// Construct outgoing flavours.
 	if (abs(id2)==22)
 	setId( id1, id2, id1);
 	else
 	setId( id1, id2, id2);
 
 	// Color flow 
    if (abs(id2)==22)
 	setColAcol(1,0,0,0,1,0);
    else
    setColAcol(0,0,1,0,1,0);

	//swap when anti quarks
	if (id1 < 0 || id2 < 0) swapColAcol();
 }
//============================================================================

} // end namespace Pythia8
