#include "RSuTPCDetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"

#include "RSuTPCMaterials.hh"

RSuTPCDetectorConstruction::RSuTPCDetectorConstruction(G4String setup) :
  m_hSetup(setup)
{}

RSuTPCDetectorConstruction::~RSuTPCDetectorConstruction(){}

G4VPhysicalVolume* RSuTPCDetectorConstruction::Construct(){
  RSuTPCMaterials* pMaterials = new RSuTPCMaterials();
  pMaterials->DefineMaterials();

  const G4double dWorldX = 1.0*m;
  const G4double dWorldY = 1.0*m;
  const G4double dWorldZ = 1.0*m;
  G4Box* pWorldBox = new G4Box("WorldBox", dWorldX/2.0, dWorldY/2.0, dWorldZ/2.0);

  G4Material* Air = G4Material::GetMaterial("G4_AIR");
  m_pWorldLogicalVolume = new G4LogicalVolume(pWorldBox, Air, "WorldLogicalVolume");
  m_pWorldLogicalVolume->SetVisAttributes(G4VisAttributes::Invisible);

  m_pWorldPhysicalVolume = new G4PVPlacement(G4Transform3D(), "World", m_pWorldLogicalVolume, 0, false, 0);

  ConstructTarget();
  ConstructScintillator();

  G4cout << "********** Ar + Ethane (9:1) **********" << G4endl;
  G4cout << m_pTargetLogicalVolume->GetMaterial() << G4endl;

  return m_pWorldPhysicalVolume;
}

void RSuTPCDetectorConstruction::ConstructTarget(){
  const G4double dTargetX = 100.0*mm;
  const G4double dTargetY = 100.0*mm;
  const G4double dTargetZ = 100.0*mm;
  G4Box* pTargetBox = new G4Box("TargetBox", dTargetX/2.0, dTargetY/2.0, dTargetZ/2.0);

  G4Material* Ar9C2H6 = G4Material::GetMaterial("Ar9C2H6");
  m_pTargetLogicalVolume = new G4LogicalVolume(pTargetBox, Ar9C2H6, "TargetLogicalVolume");

  m_pTargetPhysicalVolume = new G4PVPlacement(G4Transform3D(), "Ar9C2H6", m_pTargetLogicalVolume, m_pWorldPhysicalVolume, false, 1);
}

void RSuTPCDetectorConstruction::ConstructScintillator(){
  const G4double dScintillatorX = 100.0*mm;
  const G4double dScintillatorY = 100.0*mm;
  const G4double dScintillatorZ = 20.0*mm;
  G4Box* pScintillatorBox = new G4Box("ScintillatorBox", dScintillatorX/2.0, dScintillatorY/2.0, dScintillatorZ/2.0);

  G4Material* Plastic = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  m_pScintillatorLogicalVolume = new G4LogicalVolume(pScintillatorBox, Plastic, "ScintillatorLogicalVolume");

  if (m_hSetup == "RSuTPC") {
    m_pUpperScintillatorPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, 170*mm), "UpperScintillator", m_pScintillatorLogicalVolume, m_pWorldPhysicalVolume, false, 11);
    m_pLowerScintillatorPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, 130*mm), "LowerScintillator", m_pScintillatorLogicalVolume, m_pWorldPhysicalVolume, false, 12);
  } else if (m_hSetup == "WuTPC") {
    m_pUpperScintillatorPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, 130*mm), "UpperScintillator", m_pScintillatorLogicalVolume, m_pWorldPhysicalVolume, false, 11);
    m_pLowerScintillatorPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0, 0, -185*mm), "LowerScintillator", m_pScintillatorLogicalVolume, m_pWorldPhysicalVolume, false, 12);
  } else {
    G4cerr << "Invalid setup!" << G4endl;
    exit(-1);
  }
}
