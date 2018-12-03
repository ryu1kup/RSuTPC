#include "RSuTPCEventAction.hh"

#include "G4Event.hh"

RSuTPCEventAction::RSuTPCEventAction(RSuTPCAnalysisManager* pAnaysisManager) :
  m_pAnalysisManager(pAnaysisManager)
{}

RSuTPCEventAction::~RSuTPCEventAction(){}

void RSuTPCEventAction::BeginOfEventAction(const G4Event* pEvent){
  if (pEvent->GetEventID() % 1000 == 0) {
    G4cout << "------ Begin event " << pEvent->GetEventID() << " -----" << G4endl;
  }
  m_pAnalysisManager->BeginOfEvent(pEvent);
}

void RSuTPCEventAction::EndOfEventAction(const G4Event* pEvent){
  m_pAnalysisManager->EndOfEvent(pEvent);
}
