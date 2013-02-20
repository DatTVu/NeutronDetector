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
   /*{ // particle is secondary
    if(aTrack->GetCreatorProcess()->GetProcessName()=="Scintillation")
	{scinCounter++;}
    else if(aTrack->GetCreatorProcess()->GetProcessName()=="Cerenkov")
	{gammaCounter++;}*/
// keeping track of optical photon energy

    energy2=aTrack->GetKineticEnergy();

    gammaCounter ++;
    
    
  }

  return fUrgent;
}

void B1StackingAction::NewStage()
{
  G4cout << "Number of Cerenkov photons produces in this event : "
         << gammaCounter << G4endl;
  G4cout << "Energy is:"
         <<energy2 <<G4endl;
  /*G4cout << "Number of Scintillation photons produces in this event: "
         << scinCounter << G4endl;*/
}

void B1StackingAction::PrepareNewEvent()
{ gammaCounter = 0; }
