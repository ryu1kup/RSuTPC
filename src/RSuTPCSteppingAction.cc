#include "RSuTPCSteppingAction.hh"

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"

RSuTPCSteppingAction::RSuTPCSteppingAction(RSuTPCAnalysisManager* pAnalysisManager) :
  m_pAnalysisManager(pAnalysisManager)
{}

RSuTPCSteppingAction::~RSuTPCSteppingAction(){}

void RSuTPCSteppingAction::UserSteppingAction(const G4Step* pStep){
  m_hParticle = pStep->GetTrack()->GetDefinition()->GetParticleName();
  m_hVolume = pStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
  m_dEdep = pStep->GetTotalEnergyDeposit()/keV;
  
  if (m_hVolume == "UpperScintillator" && m_dEdep > 0) {
    m_pAnalysisManager->SetUpperFlag();
  }

  if (m_hVolume == "LowerScintillator" && m_dEdep > 0) {
    m_pAnalysisManager->SetLowerFlag();
  }

  if (m_hVolume == "Ar9C2H6") {
    m_pAnalysisManager->AddEdepInTarget(m_dEdep);
  }
}
