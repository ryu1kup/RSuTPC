#ifndef __RSuTPCANALYSISMANAGER_HH__
#define __RSuTPCANALYSISMANAGER_HH__

#include "RSuTPCPrimaryGeneratorAction.hh"
#include "RSuTPCRunAction.hh"
#include "RSuTPCEventAction.hh"
#include "RSuTPCTrackingAction.hh"
#include "RSuTPCSteppingAction.hh"

#include "TFile.h"
#include "TTree.h"

class G4Run;
class G4Event;
class G4Track;
class G4Step;

class RSuTPCEventData;
class RSuTPCPrimaryGeneratorAction;
class RSuTPCAnalysisMessenger;
class RSuTPCDetectorConstruction;

class RSuTPCAnalysisManager {
  public:
    RSuTPCAnalysisManager(G4String outputfilename);
    virtual ~RSuTPCAnalysisManager();

  public:
    virtual void BeginOfRun(const G4Run*);
    virtual void EndOfRun(const G4Run*);
    virtual void BeginOfEvent(const G4Event*);
    virtual void EndOfEvent(const G4Event*);
    virtual void PreTrack(const G4Track*);
    virtual void PostTrack(const G4Track*);
    virtual void Step(const G4Step*);
    void SetUpperFlag(){m_fPassedUpper = true;}
    void SetLowerFlag(){m_fPassedLower = true;}
    void AddEdepInTarget(G4double dEdep){m_dTotalEdep += dEdep;}

  private:
    TFile* m_ofile;
    TTree* m_otree;
    G4bool m_fPassedUpper;
    G4bool m_fPassedLower;
    G4double m_dTotalEdep;
};

#endif
