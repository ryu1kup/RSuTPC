#include "RSuTPCAnalysisManager.hh"

#include "G4SystemOfUnits.hh"

RSuTPCAnalysisManager::RSuTPCAnalysisManager(G4String outputfilename)
{
  m_ofile = new TFile(outputfilename, "recreate");
  m_otree = new TTree("events", "RSuTPC Geant4 MC results");
}

RSuTPCAnalysisManager::~RSuTPCAnalysisManager(){
  delete m_otree;
  delete m_ofile;
}

void RSuTPCAnalysisManager::BeginOfRun(const G4Run*){
  m_otree->Branch("passed_upper", &m_fPassedUpper, "upper/O");
  m_otree->Branch("passed_lower", &m_fPassedLower, "lower/O");
  m_otree->Branch("total_edep",   &m_dTotalEdep,   "edep/D");
}

void RSuTPCAnalysisManager::EndOfRun(const G4Run*){
  m_ofile->cd();
  m_otree->Write();
}

void RSuTPCAnalysisManager::BeginOfEvent(const G4Event*){
  m_fPassedUpper = false;
  m_fPassedLower = false;
  m_dTotalEdep = 0;
}

void RSuTPCAnalysisManager::EndOfEvent(const G4Event*)
{
  m_otree->Fill();
}

void RSuTPCAnalysisManager::PreTrack(const G4Track*){}

void RSuTPCAnalysisManager::PostTrack(const G4Track*){}

void RSuTPCAnalysisManager::Step(const G4Step*){}
