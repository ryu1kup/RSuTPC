#ifndef __RSuTPCSTEPPINGACTION_HH__
#define __RSuTPCSTEPPINGACTION_HH__

#include "globals.hh"
#include "G4UserSteppingAction.hh"

#include "RSuTPCAnalysisManager.hh"

class RSuTPCAnalysisManager;

class RSuTPCSteppingAction : public G4UserSteppingAction {
  public:
    RSuTPCSteppingAction(RSuTPCAnalysisManager*);
    ~RSuTPCSteppingAction();

  public:
    void UserSteppingAction(const G4Step*);

  private:
    RSuTPCAnalysisManager* m_pAnalysisManager;
    G4String m_hParticle;
    G4String m_hVolume;
    G4double m_dEdep;
};

#endif
