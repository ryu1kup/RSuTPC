#include <random>
#include "Randomize.hh"
#include "RSuTPCRunAction.hh"

RSuTPCRunAction::RSuTPCRunAction(RSuTPCAnalysisManager* pAnalysisManager) :
  m_pAnalysisManager(pAnalysisManager)
{
  m_hRandomSeed = 0;
  m_pMessenger = new RSuTPCRunActionMessenger(this);
}

RSuTPCRunAction::~RSuTPCRunAction(){
  delete m_pMessenger;
}

void RSuTPCRunAction::BeginOfRunAction(const G4Run* pRun){
  // random seeding of the MC
  if (m_hRandomSeed > 0) {
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    G4cout << "RSuTPCRunAction::BeginOfRunAction Initialize random number with seed = " << m_hRandomSeed << G4endl;
    CLHEP::HepRandom::setTheSeed(m_hRandomSeed);
  } else {
    // initialize with time
    std::random_device rd;
    std::mt19937 mt(rd());
    G4long MersenneTwister = mt();
    G4cout << "RSuTPCRunAction::BeginOfRunAction Initialize random number with seed = " << MersenneTwister << G4endl;
    CLHEP::HepRandom::setTheSeed(MersenneTwister);
  }

  m_pAnalysisManager->BeginOfRun(pRun);
}

void RSuTPCRunAction::EndOfRunAction(const G4Run* pRun){
  G4cout << "RSuTPCRunAction::EndOfRunAction MC has been done!" << G4endl;
  m_pAnalysisManager->EndOfRun(pRun);
}
