#ifndef __RSuTPCPHYSICSLIST_HH__
#define __RSuTPCPHYSICSLIST_HH__

#include "G4VModularPhysicsList.hh"

class RSuTPCPhysicsList : public G4VModularPhysicsList
{
  public:
    RSuTPCPhysicsList();
    ~RSuTPCPhysicsList();

  public:
    void SetCuts();
};
#endif
