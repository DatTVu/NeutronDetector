#include "B1StackingAction.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include <iostream>

B1StackingAction::B1StackingAction()
  : gamma_e(0)
{;}

B1StackingAction::~B1StackingAction()
{;}

G4ClassificationOfNewTrack
B1StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition())
    { // particle is optical photon
      if(aTrack->GetParentID()>0){
	/*{ // particle is secondary
	  if(aTrack->GetCreatorProcess()->GetProcessName()=="Scintillation")
	  {scinCounter++;}
	  else if(aTrack->GetCreatorProcess()->GetProcessName()=="Cerenkov")
	  {gammaCounter++;}*/
	// keeping track of optical photon energy
	gamma_e.push_back(aTrack->GetKineticEnergy());
	//gammaCounter ++;
      }
    }//  if(aTrack->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition())   
  return fUrgent;
}

void B1StackingAction::NewStage()
{
  G4cout << "Number of Cerenkov photons produces in this event : "

         << gamma_e.size() << G4endl;
  
  for(G4int i=0; i<gamma_e.size(); i++){
   
  std::ofstream fout;
  fout.open("energydata_10MeV_run1.txt", std::fstream::app);
	fout <<gamma_e[i]/eV<< " "<<std::endl;;
  fout.close();

    G4cout << gamma_e[i] << G4endl;
  }//for loop over gamma_e


}

void B1StackingAction::PrepareNewEvent()
{ //gammaCounter = 0;  
  gamma_e.clear();
}
