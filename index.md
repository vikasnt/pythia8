Project Description-
My GSoC organization is Massachusetts Institute of Technology (MIT) under the umbrella of HEP Software Foundation (HSF) and the project I worked on is Pythia8.
PYTHIA8 is used for generation of events in high-energy collisions, using a coherent set of physics models for the evolution from a few-body hard process to a complex multiparticle final state. It is the C++ successor of Pythia6 which was written entirely in Fortran.
Pythia8 still lacks certain important functionalities before it can completely replace Pythia6. This project is also part of the same effort.

### Work done
In chronological order, the work I did can be briefly summarised as-

1. Building a Pythia6 plugin for Pythia8 : This will enable us to easily compare results between Pythia8 and Pythia6 for the process we will add ( as well as comparing existing process ) . This requires calling Pythia6 routine for hard process generation, then passing the hard process result via Les Houches Accord (LHA), and doing the later parts of event generation in Pythia8. We added the new code in include/Pythia8Plugins/LHAPythia6.h and this can be run using examples/main36.cc which also contains analysis code for HERA specefic comparisions. While this works as intended for 2-2 process ( which constitutes majority of Pythia8 use), the plugin isn't able to work well with 2-1 process ( only one 2-1 case checked as of now, process number 99). This is becuase of the way Pythi6 is passing the hard process data for this process and correcting this will require further work in future.

2. Updating lepton-hadron collision process : There are two ways of running lepton-hadron collision in Pythia6. First is a straightforward 2-2 process which already exist in Pythia8. We also used our plugin to compare the 2-2 process results from Pythia8 and Pythia6 with the experimental data from HERA and found all three to be in agreement as expected. In Pythia6, another way to do this is via gamma/lepton machinery which considers photon inside lepton beam and breaks it into many subprocess (2-2 as well as 2-1 process) based on how the photon interacts with the quark(inside hadron). Understanding the physics behind this breakdown as well as existing implementation in Pythia6 was followed by adding new process in Pythia8 called DIS:gammaf2f. A few other process needs to be added but they are extensions of already exsiting QCD process in Pythia8 but with relevant changes nedded to accomodate lepton-hadron event features. DIS:gammaf2f took quite sometime to completely debug because a) Implementation of physics in Pythia is complex and required a lot of time to be completely understood, b) this particular process is different from typical Pythia8 process, so we got errors difficult to debug. One important part of this gamma/lepton machinery is special treatment of gamma kinematics. What exist in Pythia8 is only for gamma-pair at the moment ( i.e lepton-lepton collision ) and also lacks flux contribution from VMD part of lepton. Updating gamma kinematics requires effort in almost all important parts of Pythia8 event generation, and we have already made progress in understanding what needs to be done. But, this wasn't possible to be done in GSoC timeline, considering it took a lot of time in understanding physics background of gamma/lepton machinery as well implementing DIS process itself.

3. Comparing results with experimental data : In order to compare result between experiment and existing gamma/lepton machinery based Pythia6 run ( as well as the above mentioned 2-2 process based run), we had to also write an example for running a full Pythia6 event because of the issue of 2-1 process not running correctly with the plugin. Thus, I wrote another example code which calls all relevant methods and variables from Pythia6 but uses C++ to analyse event. Histogram for all relevant subprocess as well as total process were compared and can be found in lepton-hadron-events.pdf in the repository.

### List of files edited/added while working on this project.
Examples:

examples/main35.cc  - example to run only Pythia6 event with HERA specefic event analysis.

examples/main36.cc  - example to run Pythia6 plugin with HERA sepecfic event analysis.

examples/mymain01.cc  - trivial example to only do Pythia8 run.

Plugin file:

include/Pythia8Plugins/LHAPythia6.h  - Plugin to run Pythia6 hard process with Pythia8 run. 

Xml file:

share/Pythia8/xmldoc/DISProcesses.xml - XML file for added DIS process.

share/Pythia8/xmldoc/ProgramFiles.xml - adding DIS to process list.

share/Pythia8/xmldoc/Index.xml - adding DIS to index list.

Source file:

src/BeamRemnants.cc - Editing Beamremnant to add outgoing electron for DIS specefic.

src/ProcessContainer.cc - Adding DIS to process known to Pythia8.

src/SigmaDIS.cc - Sigma calculation for added DIS process.

include/Pythia8/BeamRemnants.h
include/Pythia8/SigmaDIS.h


### Conclusion

A major part of this project involved understanding physics behind the event generation, and implementation of physics in Pythia8 as well as Pythia6 ( which vary quite a lot since one uses Fortran while other C++ ). Still a few thing remains to be done, but with the understanding acquired of technical and physical aspects of Pythia8, I will continue to work on the goals we had in mind at the start of this project as well as intend to join as regular contributor to Pythia8 in future.

### Authors and Contributors
GSoC participant - Vikas Gupta <@vikasnt> 

Mentors - Philip Ilten and Mike Williams.

I would like to thank Google as well as HSF and my mentors for this wonderful opportunity.

