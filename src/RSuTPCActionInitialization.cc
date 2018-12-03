#include "RSuTPCActionInitialization.hh"

#include "RSuTPCAnalysisManager.hh"
#include "RSuTPCPrimaryGeneratorAction.hh"
#include "RSuTPCRunAction.hh"
#include "RSuTPCEventAction.hh"
#include "RSuTPCTrackingAction.hh"
#include "RSuTPCSteppingAction.hh"

RSuTPCActionInitialization::RSuTPCActionInitialization(G4String input, G4String setup, G4String outputfilename) : G4VUserActionInitialization()
{
  m_hInput = input;
  m_hSetup = setup;
  m_pAnalysisManager = new RSuTPCAnalysisManager(outputfilename);
}

RSuTPCActionInitialization::~RSuTPCActionInitialization(){
  delete m_pAnalysisManager;
}

void RSuTPCActionInitialization::Build() const
{
  SetUserAction(new RSuTPCPrimaryGeneratorAction(m_hInput, m_hSetup));
  SetUserAction(new RSuTPCRunAction(m_pAnalysisManager));
  SetUserAction(new RSuTPCEventAction(m_pAnalysisManager));
  SetUserAction(new RSuTPCTrackingAction());
  SetUserAction(new RSuTPCSteppingAction(m_pAnalysisManager));
}
