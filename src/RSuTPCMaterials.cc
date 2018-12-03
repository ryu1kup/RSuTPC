#include "RSuTPCMaterials.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

RSuTPCMaterials::RSuTPCMaterials()
{
  return;
}

RSuTPCMaterials::~RSuTPCMaterials()
{
  return;
}

void RSuTPCMaterials::DefineMaterials(){
  G4NistManager* pNistManager = G4NistManager::Instance();

  // Air
  pNistManager->FindOrBuildMaterial("G4_AIR");

  // C2H6
  G4Element* elH  = pNistManager->FindOrBuildElement("H");
  G4Element* elC  = pNistManager->FindOrBuildElement("C");
  G4Element* elAr = pNistManager->FindOrBuildElement("Ar");

  // C2H6
  const G4double dC2H6Density = 1.356*kg/m3;
  G4Material* C2H6 = new G4Material("C2H6", dC2H6Density, 2, kStateGas);
  C2H6->AddElement(elC, 2);
  C2H6->AddElement(elH, 6);

  const G4double dArDensity = 1.784*kg/m3;
  G4Material* Ar = new G4Material("Ar", dArDensity, 1, kStateGas);
  Ar->AddElement(elAr, 1);

  G4Material* Ar9C2H6 = new G4Material("Ar9C2H6", dArDensity*0.9 + dC2H6Density*0.1, 2, kStateGas);
  Ar9C2H6->AddMaterial(Ar,   90.0*perCent);
  Ar9C2H6->AddMaterial(C2H6, 10.0*perCent);

  // plastic scintillator
  pNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
}
