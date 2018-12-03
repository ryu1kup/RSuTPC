#ifndef __RSuTPCACTIONIITIALIZATION_HH__
#define __RSuTPCACTIONIITIALIZATION_HH__

#include "G4VUserActionInitialization.hh"

#include "RSuTPCAnalysisManager.hh"

class RSuTPCActionInitialization : public G4VUserActionInitialization
{
  public:
    RSuTPCActionInitialization(G4String input, G4String setup, G4String outputfilename);
    virtual ~RSuTPCActionInitialization();

    virtual void Build() const;

  private:
    G4String m_hInput;
    G4String m_hSetup;
    RSuTPCAnalysisManager* m_pAnalysisManager;
};

#endif
