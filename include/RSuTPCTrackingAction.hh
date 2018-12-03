#ifndef __RSuTPCTRACKINGACTION_HH__
#define __RSuTPCTRACKINGACTION_HH__

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class RSuTPCTrackingAction : public G4UserTrackingAction
{
  public:
    RSuTPCTrackingAction();
    virtual ~RSuTPCTrackingAction();

  public:
    virtual void PreTrackingAction(const G4Track*);
    virtual void PostTrackingAction(const G4Track*);
};

#endif
