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
  py8.init();
  Hist eT("Et", 26, -1.25, 5.5);
  int acceptance=0;
  for (int iEvent = 0; iEvent < 10; ++iEvent)
    { 
      py8.next();
      //      py8.info.list();
    }
  // End of run.
  py8.stat();
  return 0;
}
