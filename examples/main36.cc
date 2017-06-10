#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/LHAPythia6.h"
using namespace Pythia8;
int main() {
  Pythia py8;
  LHAupPythia6 py6(&py8,"CMS", "p", "e-", 846.7); 
  py6.readString("MSTP(21)=2");
  py8.readString("Beams:frameType = 5");
  py8.readString("WeakBosonExchange:ff2ff(t:gmZ) = on");
  py8.readString("WeakZ0:gmZmode = 1");
  Hist eT("Et", 26, -1.25, 5.5);
  int acceptance=0;
  py8.init();
  for (int iEvent = 0; iEvent < 10000; ++iEvent)
    { 
      py8.next();
      int eoindex=0;
      double W=0.,W2=0.;
      if(py8.info.x1()>0.001)
	    {
	      eoindex = py8.event[2].iBotCopyId();
	      Vec4 eiP,eoP,old_eoP,pP,gP,pgP;
	      eiP = py8.event[2].p();
	      eoP = py8.event[eoindex].p();
	      pP  = py8.event[1].p();
	      gP = eiP - eoP;
	      pgP = pP + gP;
	      W = pgP.mCalc();
	      W2 = pow(W,2); 
	  //angle in radians
	      Vec4 P;
	      old_eoP = eoP;
	      RotBstMatrix rotmx;
	      rotmx.bstback(pgP);
	      gP.rotbst(rotmx);
	      rotmx.rot(-gP.theta(),-gP.phi());
	      eoP.rotbst(rotmx);
	      rotmx.rot(0,-eoP.phi());
	      if(W2>3000 && old_eoP.e()>14 && old_eoP.theta()>2.738 && old_eoP.theta() <3.009)
	        {
	          for(int i=0;i<py8.event.size();++i)
                {
                  if(py8.event[i].id()!=11 && py8.event[i].isFinal())
                    {
                      P = py8.event[i].p();
                      if(P.theta()>0.0767 && P.theta()<0.261 )
					    {
			              if(P.e()>0.5)
			                {
			                  acceptance++;
			                  P.rotbst(rotmx);
			                  eT.fill(P.eta(),P.e());
			                }
			            }
                    } 
                }
	        } 
        }
//	    py8.info.list();
    }
  eT = eT/(acceptance*0.2596);
  cout << eT;
  // End of run.
  py8.stat();
  return 0;
}
