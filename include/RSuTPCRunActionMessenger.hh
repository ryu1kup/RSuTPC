#ifndef __RSuTPCRUNACTIONMESSENGER_HH__
#define __RSuTPCRUNACTIONMESSENGER_HH__

#include <G4UImessenger.hh>
#include <globals.hh>

class RSuTPCRunAction;

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;

class RSuTPCRunActionMessenger : public G4UImessenger {
 public:
  RSuTPCRunActionMessenger(RSuTPCRunAction* pRunAction);
  ~RSuTPCRunActionMessenger();

 public:
  void SetNewValue(G4UIcommand* pCommand, G4String hNewValues);

 private:
  RSuTPCRunAction* m_pRunAction;
  G4UIdirectory* m_pDirectory;
  G4UIcmdWithAnInteger* m_pRandomSeedCmd;
};

#endif
