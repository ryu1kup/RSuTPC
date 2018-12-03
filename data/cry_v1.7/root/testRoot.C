#include "CRYGenerator.h"
#include "CRYSetup.h"

#include "TTree.h"
#include "TMath.h"
#include "TH1F.h"
#include "TFile.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

Int_t main(Int_t argc, const Char_t** argv) {
  if ( argc < 2 ) {
    cerr << "usage " << argv[0] << " <setup file name> <N events>" << endl;;
    cerr << "N events = 10k by default" << endl;
    exit(-1);
  }

  Int_t nEv = 10000;
  if (argc > 2) nEv = atoi(argv[2]);

  // Read the setup file Int_to setupString
  ifstream inputFile;
  inputFile.open(argv[1],ios::in);
  Char_t buffer[1000];

  TString setupString("");
  while (!inputFile.getline(buffer,1000).eof()) {
    setupString.Append(buffer);
    setupString.Append(" ");
  }

  // Parse the contents of the setup file
  CRYSetup* setup = new CRYSetup(setupString.Data(), "./data");

  // Setup the CRY event generator
  CRYGenerator gen(setup);

  // ROOT output file
  TFile* outputFile = new TFile("output.root","RECREATE");
  TTree* outputTree = new TTree("events", "Generated events");
  Int_t nParticles;
  Int_t PDGId[30];
  Double_t qx[30], qy[30], qz[30];
  Double_t px[30], py[30], pz[30];
  //const Double_t uH = -0.2 + 0.16; // upper scintillator lower surface z
  //const Double_t lH = -0.2 + 0.05; // target box upper surface z
  const Float_t uH = -0.2 + 0.12;   // upper scintillator lower surface z
  const Float_t lH = -0.2 - 0.175;  // lower scintillator upper surface z
  const Double_t L = 0.05;          // detector size
  Double_t ux[30], uy[30], lx[30], ly[30];
  outputTree->Branch("nParticles", &nParticles, "nParticles/I");
  outputTree->Branch("PDGId", PDGId, "PDGId[nParticles]/I");
  outputTree->Branch("x", qx, "x[nParticles]/D");
  outputTree->Branch("y", qy, "y[nParticles]/D");
  outputTree->Branch("z", qz, "z[nParticles]/D");
  outputTree->Branch("px", px, "px[nParticles]/D");
  outputTree->Branch("py", py, "py[nParticles]/D");
  outputTree->Branch("pz", pz, "pz[nParticles]/D");

  // Generate the events
  vector<CRYParticle*>* ev = new vector<CRYParticle*>;
  Long_t nCalc = 0, nOutput = 0;
  cout << endl;
  for (nCalc = 0; nOutput < nEv; nCalc++) {
    ev->clear();
    gen.genEvent(ev);

    nParticles = Int_t(ev->size());

    for (Int_t j = 0; j < nParticles; j++) {
      CRYParticle* part = ev->at(j);

      PDGId[j] = part->PDGid();
      qx[j] = part->x();
      qy[j] = part->y();
      qz[j] = part->z();
      Double_t kE = part->ke();

      px[j] = kE * part->u();
      py[j] = kE * part->v();
      pz[j] = kE * part->w();

      ux[j] = qx[j] + part->u() / part->w() * uH;
      uy[j] = qy[j] + part->v() / part->w() * uH;
      lx[j] = qx[j] + part->u() / part->w() * lH;
      ly[j] = qy[j] + part->v() / part->w() * lH;

      delete ev->at(j);
    }

    // for RSuTPC
    // the case of particle could pass through two scintillator is filled
    for (Int_t k = 0; k < nParticles; k++) {
      if (ux[k] < L && ux[k] > -L && uy[k] < L && uy[k] > -L &&
          lx[k] < L && lx[k] > -L && ly[k] < L && ly[k] > -L) {
        outputTree->Fill();
        nOutput++;
        cout << "\r" << "Currently " << nOutput << " output events are generated." << flush;
      }
    }
  }
  cout << endl;
  cout << "Run completed." << endl;
  cout << "Number of calculated events: " << nCalc << " events" << endl;
  cout << "Number of output events: " << nOutput << " events" << endl;
  cout << "Total time simulated: " << gen.timeSimulated() << " seconds" << endl;

  // write
  outputFile->Write();
  outputFile->Close();

  delete setup;

  return 0;
}
