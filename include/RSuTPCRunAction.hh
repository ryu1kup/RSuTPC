#ifndef __RSuTPCRUNACTION_HH__
#define __RSuTPCRUNACTION_HH__

#include "G4UserRunAction.hh"

#include "RSuTPCRunActionMessenger.hh"
#include "RSuTPCAnalysisManager.hh"

class G4Run;

class RSuTPCAnalysisManager;

class RSuTPCRunAction : public G4UserRunAction {
 public:
  RSuTPCRunAction(RSuTPCAnalysisManager* pAnalysisManager);
  ~RSuTPCRunAction();

 public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  void SetRandomSeed(G4long hRandomSeed){ m_hRandomSeed = hRandomSeed; }

 private:
  G4int m_hRandomSeed;
  RSuTPCRunActionMessenger* m_pMessenger;
  RSuTPCAnalysisManager* m_pAnalysisManager;
};

#endif
