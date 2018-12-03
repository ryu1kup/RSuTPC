#include "RSuTPCPrimaryGeneratorAction.hh"

#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4SystemOfUnits.hh"

#include "TFile.h"
#include "TTree.h"

RSuTPCPrimaryGeneratorAction::RSuTPCPrimaryGeneratorAction(G4String input, G4String setup) : 
  m_hSetup(setup)
{
  m_hInput = input;
  m_file = TFile::Open(input.data(), "READ");
  m_tree = (TTree*)m_file->Get("events");
  m_tree->SetBranchAddress("nParticles", &m_nParticles);
  m_tree->SetBranchAddress("PDGId", m_PDGId);
  m_tree->SetBranchAddress("x", m_x);
  m_tree->SetBranchAddress("y", m_y);
  m_tree->SetBranchAddress("px", m_px);
  m_tree->SetBranchAddress("py", m_py);
  m_tree->SetBranchAddress("pz", m_pz);
}

RSuTPCPrimaryGeneratorAction::~RSuTPCPrimaryGeneratorAction(){
}

void RSuTPCPrimaryGeneratorAction::GeneratePrimaries(G4Event* pEvent){
  // get particle table
  G4ParticleTable* pParticleTable = G4ParticleTable::GetParticleTable();

  // access to branch 
  m_tree->GetEntry(pEvent->GetEventID());
  for (G4int iParticle = 0; iParticle < m_nParticles; iParticle++) {
    // particle definition
    G4String hParticleName = RSuTPCPrimaryGeneratorAction::GetParticleNameFromPDGId(m_PDGId[iParticle]);
    G4ParticleDefinition* pParticle = pParticleTable->FindParticle(hParticleName);

    // primary particle instance
    G4PrimaryParticle* pPrimaryParticle = new G4PrimaryParticle(pParticle, m_px[iParticle]*MeV, m_py[iParticle]*MeV, m_pz[iParticle]*MeV);
    const G4double hPrimaryZ = 200*mm;

    G4ThreeVector vtx = G4ThreeVector(m_x[iParticle]*m, m_y[iParticle]*m, hPrimaryZ);
    G4PrimaryVertex* pPrimaryVertex = new G4PrimaryVertex(vtx, 0);
    pPrimaryVertex->SetPrimary(pPrimaryParticle);
    pEvent->AddPrimaryVertex(pPrimaryVertex);
  }
}
