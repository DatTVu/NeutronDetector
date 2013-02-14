#include "TrackerSD.hh"
#include "TrackerHit.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4Track.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4VUserTrackInformation.hh"
#include "G4ios.hh"
#include "G4ThreeVector.hh"
#include <iostream>
#include "G4VProcess.hh"
TrackerSD::TrackerSD(G4String name): G4VSensitiveDetector(name)
{
aCount = 0;
G4String SDname;
collectionName.insert(SDname="TrackerHitsCollection");
totalEnergyOfTheEvent = 0;
}
//............
TrackerSD::~TrackerSD()
{}
//............
void TrackerSD::Initialize(G4HCofThisEvent* HCE)
{
trackerCollection = new TrackerHitsCollection
			(SensitiveDetectorName,collectionName[0]);
static G4int HCID =-1;
if(HCID<0)
{ HCID =G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);}
HCE->AddHitsCollection(HCID,trackerCollection);
}
//..............................................................................
G4bool TrackerSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "opticalphoton")

//if(aStep->GetTrack()->GetTrackID()==1)
 {
		
		TrackerHit* newHit = new TrackerHit();
                newHit-> SetTrackID (aStep -> GetTrack() -> GetTrackID());
 		
		newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
		newHit->SetID(aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName());
		newHit->SetEn(aStep->GetTrack()->GetKineticEnergy());
		cname = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();
                totalEnergyOfTheEvent = aStep->GetTrack()->GetKineticEnergy();
		name = aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
                
 		trackerCollection->insert(newHit );
	}		
else
	{
 		return false;
	}        
return true;
}

//...................................................................................
void TrackerSD::EndOfEvent(G4HCofThisEvent*)
{
    	G4int NbHits = trackerCollection->entries();
   
	aCount += NbHits;
	for (G4int i=0;i<NbHits;i++) 
	{
		(*trackerCollection)[i]->Print();
	}
	std::ofstream fout;
  fout.open("process_run13.txt", std::fstream::app);
  fout <<cname<< " " <<std::endl;;
  fout.close();
fout.open("alphadata100MeV_run13.txt", std::fstream::app);
	fout <<name<< " "<<std::endl;;
  fout.close();
  fout.open("number100MeV_run13.txt", std::fstream::app);
	fout <<NbHits<< " "<<std::endl;;
  fout.close();
  fout.open("energydata100MeV_run13.txt", std::fstream::app);
	fout <<totalEnergyOfTheEvent/eV<< " "<<std::endl;;
  fout.close();
}

void TrackerSD::DrawAll()
{}
void TrackerSD::PrintAll()
{}

