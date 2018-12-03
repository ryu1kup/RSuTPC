#ifndef __RSuTPCPRIMARYGENERATORACTION_HH__
#define __RSuTPCPRIMARYGENERATORACTION_HH__

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "TFile.h"
#include "TTree.h"
#include <map>
#include <string>

class G4Event;
class G4ParticleGun;

class RSuTPCPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    RSuTPCPrimaryGeneratorAction(G4String input, G4String setup);
    ~RSuTPCPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);
    inline G4String GetParticleNameFromPDGId(G4int id){
      std::map<G4int, G4String> PDGName;
      PDGName[11] = "e-";
      PDGName[-11] = "e+";
      PDGName[13] = "mu-";
      PDGName[-13] = "mu+";
      PDGName[22] = "gamma";
      PDGName[2112] = "neutron";
      PDGName[-2112] = "anti_neutron";
      PDGName[2212] = "proton";
      PDGName[-2212] = "anti_proton";
      PDGName[211] = "pi+";
      PDGName[-211] = "pi-";
      PDGName[321] = "kaon+";
      PDGName[-321] = "kaon-";
      return PDGName[id];
    }

  private:
    G4String m_hSetup;
    G4String m_hInput;
    TFile* m_file;
    TTree* m_tree;
    G4int m_nParticles;
    G4int m_PDGId[30];
    G4double m_x[30];
    G4double m_y[30];
    G4double m_px[30];
    G4double m_py[30];
    G4double m_pz[30];
};

#endif
