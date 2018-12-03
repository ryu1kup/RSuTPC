#include "RSuTPCRunActionMessenger.hh"

#include <G4UIcmdWith3Vector.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UIcmdWithABool.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIdirectory.hh>

#include "RSuTPCRunAction.hh"

RSuTPCRunActionMessenger::RSuTPCRunActionMessenger(RSuTPCRunAction *pRunAction) :
  m_pRunAction(pRunAction)
{
  // create directory
  m_pDirectory = new G4UIdirectory("/run/random/");
  m_pDirectory->SetGuidance("RunAction control commands.");

  // set particle
  m_pRandomSeedCmd = new G4UIcmdWithAnInteger("/run/random/setRandomSeed", this);
  m_pRandomSeedCmd->SetGuidance("Random seed");
  G4int iDef = 12345;
  m_pRandomSeedCmd->SetDefaultValue(iDef);
}

RSuTPCRunActionMessenger::~RSuTPCRunActionMessenger(){
  delete m_pDirectory;
}

void RSuTPCRunActionMessenger::SetNewValue(G4UIcommand* command, G4String newValues) {
  if (command == m_pRandomSeedCmd) {
    m_pRunAction->SetRandomSeed(m_pRandomSeedCmd->GetNewIntValue(newValues));
  }
}
