#ifndef B1StackingAction_H
#define B1StackingAction_H 1

#include "G4UserStackingAction.hh"

class B1StackingAction : public G4UserStackingAction
{
  public:
    B1StackingAction();
    virtual ~B1StackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:
    int gammaCounter;
};

#endif
