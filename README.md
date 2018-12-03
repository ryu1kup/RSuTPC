# RSuTPC
based on Geant4 for Resistive Sheet micro TPC.

# prerequisites
- ROOT5
- Geant4.10

# usage
```
$ cd bench
$ ./run_RSuTPC.sh
```
or specify the experiment setup and path to macro on your own as follows,
```
$ cd bench
$ ../bin/RSuTPC_G4p10 -s <setup> -p <preinit>
```
where `<setup>` is the experiment setup, `RSuTPC` or `WuTPC`, and `<preinit>` is the path to preinit macro such as `../macros/preinit.mac`.

# compilation
```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make install
```

# output
The branches in an output root file are:
- upper ... the flag of upper scintillator
- lower ... the flag of lower scintillator
- edep .... energy deposit in the target [keV]

# class list
- RSuTPCAnalysisManager
- RSuTPCDetectorConstruction
- RSuTPCMaterials
- RSuTPCPhysicsList
- RSuTPCActionInitialization
- RSuTPCPrimaryGeneratorAction
- RSuTPCRunAction
- RSuTPCRunActionMessenger
- RSuTPCEventAction
- RSuTPCSteppingAction
