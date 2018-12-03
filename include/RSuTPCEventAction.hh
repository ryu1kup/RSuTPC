#ifndef __RSuTPCPEVENTACTION_HH__
#define __RSuTPCPEVENTACTION_HH__

#include <G4UserEventAction.hh>

#include "RSuTPCAnalysisManager.hh"

class G4Event;

class RSuTPCAnalysisManager;

class RSuTPCEventAction : public G4UserEventAction {
  public:
    RSuTPCEventAction(RSuTPCAnalysisManager*);
    ~RSuTPCEventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

  private:
    RSuTPCAnalysisManager* m_pAnalysisManager;
};

#endif
