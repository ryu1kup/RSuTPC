#ifndef __RSuTPCDETECTORCONSTRUCTION_HH_
#define __RSuTPCDETECTORCONSTRUCTION_HH_

#include "G4VUserDetectorConstruction.hh"
class G4VPhysicalVolume;

class RSuTPCDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    RSuTPCDetectorConstruction(G4String);
    ~RSuTPCDetectorConstruction();

  public:
    G4VPhysicalVolume* Construct();
    void ConstructTarget();
    void ConstructScintillator();

  private:
    G4String m_hSetup;

    G4LogicalVolume* m_pWorldLogicalVolume;
    G4LogicalVolume* m_pTargetLogicalVolume;
    G4LogicalVolume* m_pScintillatorLogicalVolume;

    G4VPhysicalVolume* m_pWorldPhysicalVolume;
    G4VPhysicalVolume* m_pTargetPhysicalVolume;
    G4VPhysicalVolume* m_pUpperScintillatorPhysicalVolume;
    G4VPhysicalVolume* m_pLowerScintillatorPhysicalVolume;
};

#endif
