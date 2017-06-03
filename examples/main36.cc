#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/LHAPythia6.h"
using namespace Pythia8;
int main() {
  Pythia py8;
  LHAupPythia6 py6(&py8,"CMS", "p", "p", 14000); 
  py8.readString("Beams:frameType = 5");
  py8.init();
  for (int iEvent = 0; iEvent < 100; ++iEvent) 
  py8.next();
  // End of run.
  py8.stat();
  return 0;
}
