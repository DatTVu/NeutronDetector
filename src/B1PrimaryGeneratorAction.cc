
#include "B1PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "Randomize.hh"
#include "G4Neutron.hh"
#include "G4Electron.hh"

B1PrimaryGeneratorAction* B1PrimaryGeneratorAction::fgInstance = 0;


const B1PrimaryGeneratorAction* B1PrimaryGeneratorAction::Instance()
{


  return fgInstance;
}      



B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
    = particleTable->FindParticle("neutron");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(20*MeV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  
  fgInstance = this;
}



B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  delete fParticleGun;
  fgInstance = 0;
}

void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->SetParticlePosition(G4ThreeVector(-260,0,0));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}



