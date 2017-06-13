#include "Pythia8/Pythia.h"
using namespace Pythia8;

int main()
{
  Pythia pythia;
  pythia.readString("WeakBosonExchange:ff2ff(t:gmZ) = on");
  pythia.readString("WeakZ0:gmZmode = 1");
  pythia.readString("Beams:frameType = 2");
  pythia.readString("Beams:idA = 2212");
  pythia.readString("Beams:idB = 11");
  pythia.readString("Beams:eA = 820");
  pythia.readString("Beams:eB = 26.7");
  Hist eT("Et", 26, -1.25, 5.5);
   pythia.init();
   int acceptance=0;
  for(int ie=0;ie<100000;++ie)
    {
      pythia.next(); 
      int eoindex=0;
      double W=0.,W2=0.;
      if(pythia.info.x1()>0.001)
          {
            eoindex = pythia.event[2].iBotCopyId();
            Vec4 eiP,eoP,old_eoP,pP,gP,pgP;
            eiP = pythia.event[2].p();
            eoP = pythia.event[eoindex].p();
            pP  = pythia.event[1].p();
            gP = eiP - eoP;
            pgP = pP + gP;
            W = pgP.mCalc();
            W2 = pow(W,2); 
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
                for(int i=0;i<pythia.event.size();++i)
                {
                  if(pythia.event[i].id()!=11 && pythia.event[i].isFinal())
                    {
                      P = pythia.event[i].p();
                      if(P.theta()>0.0767 && P.theta()<0.261 )
                      {
                        if(P.e()>0.5)
                        {
                          acceptance++;
                          P.rotbst(rotmx);
                          eT.fill(P.eta(),P.eT());
                        }
                      }
                    } 
                }
              }
          }
    }
    eT = eT/(acceptance*0.2596);
  cout << eT;
   pythia.stat();
  eT.table("pythia8.txt");
return 0;
}
