Project Description-
My GSoC organization is Massachusetts Institute of Technology (MIT) under the umbrella of HEP Software Foundation (HSF) and the project I worked on is Pythia8.
PYTHIA8 is used for generation of events in high-energy collisions, using a coherent set of physics models for the evolution from a few-body hard process to a complex multiparticle final state. It is the C++ successor of Pythia6 which was written entirely in Fortran.
Pythia8 still lacks certain important functionalities before it can completely replace Pythia6. This project is also part of the same effort.

### Project Goals
After discussion with mentors in the Community Bonding Period, We decided on the following goals for the GSoC timeline-

1. Building a Pythia6 plugin for Pythia8 : This will enable us to easily compare results between Pythia8 and Pythia6 for the process we will add ( as well as comparing existing process ) . This requires calling Pythia6 routine for hard process generation, then passing the hard process result via Les Houches Accord (LHA), and doing the later parts of event generation in Pythia8. We added the new code in include/Pythia8Plugins/LHAPythia6.h and this can be run using examples/main36.cc which also contains analysis code for HERA specefic comparisions. While this works as intended for 2-2 process ( which constitutes majority of Pythia8 use), the plugin isn't able to work well with 2-1 process ( only one 2-1 case checked as of now, process number 99). This is becuase of the way Pythi6 is passing the hard process data for this process and correcting this will require further work in future.
Things I learned while doing this- Cross language programming and basic details of running Pythia6 and Pythia8 event generation. 

2. Adding lepton-hadron collision process : There are two ways of running lepton-hadron collision in Pythia6. First is a 2-2 process which already exist in Pythi8 but another ( and recent method ) is via gamma/lepton machinery which considers photon inside lepton beam and breaks it into many subprocess (2-2 as well as 2-1 process) involving photon inside lepton beam itself. This is also considerably complex and requires consideration of VMD contribution to gamma flux.... 


### Authors and Contributors
GSoC participant - Vikas Gupta <@vikasnt> 

Mentors - Philip Ilten and Mike Williams.

I would like to thank Google as well as HSF and my mentors for this wonderful opportunity.

