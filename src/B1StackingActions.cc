#include "B1StackingAction.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"

B1StackingAction::B1StackingAction()
: gammaCounter(0)
{;}

B1StackingAction::~B1StackingAction()
{;}

G4ClassificationOfNewTrack
B1StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      gammaCounter++;
// keeping track of optical photon energy
/*
G4int ke=aStep->GetTrack()->GetKineticEnergy());
*/
    }
  }

  return fUrgent;
}

void B1StackingAction::NewStage()
{
  G4cout << "Number of gamma produces in this event : "
         << gammaCounter << G4endl;
}

void B1StackingAction::PrepareNewEvent()
{ gammaCounter = 0; }
