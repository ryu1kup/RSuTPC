#include "G4RunManager.hh"
#include "G4UImanager.hh"
//#include "G4UIExecutive.hh"

#include "RSuTPCDetectorConstruction.hh"
#include "RSuTPCPhysicsList.hh"
#include "RSuTPCActionInitialization.hh"

int GetArgs(int argc, char** argv);

G4String setup = "RSuTPC"; // -s
G4String input = "../data/cry_RSuTPC_mu.root"; // -i
G4String preinit = "../macros/preinit.mac"; // -p
G4String outputfilename = "output.root"; // -o

int main(int argc, char** argv){
  GetArgs(argc, argv);
  if (setup != "RSuTPC" && setup != "WuTPC") {
    G4cerr << "\x1b[31m" << "Error! " << "\x1b[37m" << "Invalid experiment setup" << G4endl;
    G4cerr << "allowd options are: \"RSuTPC\" or \"WuTPC\"" << G4endl;
    exit(-1);
  }

  G4cout << G4endl;
  G4cout << "*****      Welcome to RSuTPC montecalro!     *****" << G4endl;
  G4cout << G4endl;
  G4cout << "Experiment setup: " << setup << G4endl;

  // Construct the default run maddddnager
  G4RunManager* pRunManager = new G4RunManager;

  pRunManager->SetUserInitialization(new RSuTPCDetectorConstruction(setup));
  pRunManager->SetUserInitialization(new RSuTPCPhysicsList());
  pRunManager->SetUserInitialization(new RSuTPCActionInitialization(input, setup, outputfilename));

  // Initialize G4 kernel
  pRunManager->Initialize();

  // Start session
  //G4UIExecutive* pUIExecutive = new G4UIExecutive(argc, argv, "tcsh");
  G4UImanager* pUIManager = G4UImanager::GetUIpointer();
  pUIManager->ApplyCommand("/control/execute " + preinit);
  //pUIExecutive->SessionStart();

  // Job termination
  //delete pUIExecutive;
  delete pRunManager;

  return 0;
}

int GetArgs(int argc, char** argv){
  while (argc > 1 && argv[1][0] == '-') {
    switch (argv[1][1]) {
      case 's':
        setup = argv[2];
        ++argv;
        --argc;
        break;

      case 'i':
        input = argv[2];
        ++argv;
        --argc;
        break;

      case 'p':
        preinit = argv[2];
        ++argv;
        --argc;
        break;

      case 'o':
        outputfilename = argv[2];
        ++argv;
        --argc;
        break;
    }
    ++argv;
    --argc;
  }
  return 0;
}
