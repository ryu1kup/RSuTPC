#include "RSuTPCPhysicsList.hh"

#include "G4EmLivermorePhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"

RSuTPCPhysicsList::RSuTPCPhysicsList() : G4VModularPhysicsList() 
{
  RegisterPhysics(new G4EmLivermorePhysics());
  RegisterPhysics(new G4HadronElasticPhysics());
  RegisterPhysics(new G4HadronPhysicsQGSP_BERT());
}

RSuTPCPhysicsList::~RSuTPCPhysicsList(){}

void RSuTPCPhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
