#include "B1PhysicsList.hh"
#include "G4HadronElasticPhysics.hh"
#include "HadronPhysicsQGSP_BERT_HP.hh"
#include "G4IonPhysics.hh"
#include "GammaPhysics.hh"

#include "G4OpticalPhysics.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "globals.hh"
#include "G4ProcessManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4EmStandardPhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PhysicsList::B1PhysicsList()
:G4VModularPhysicsList()
{
  G4int verb = 1;  
  SetVerboseLevel(verb);

  // Hadron Elastic scattering
  RegisterPhysics( new G4HadronElasticPhysics(verb) );
  // Hadron Physics
  RegisterPhysics( new HadronPhysicsQGSP_BERT_HP(verb));
  // Ion Physics
  RegisterPhysics( new G4IonPhysics(verb));
  // EM Physics
  RegisterPhysics(new G4EmStandardPhysics);
  // Gamma Physics
  RegisterPhysics( new GammaPhysics("gamma"));
  // Optical Physics
  G4OpticalPhysics* optPhys = new G4OpticalPhysics();
  RegisterPhysics(optPhys);
  optPhys->SetTrackSecondariesFirst(kScintillation,true);  
  optPhys->SetScintillationYieldFactor(1.0);
  optPhys->SetMaxNumPhotonsPerStep(1000);
  optPhys->SetScintillationByParticleType(false);
  optPhys->SetScintillationYieldFactor(1.0);
  optPhys->SetScintillationExcitationRatio(0.0);
//  optPhys->SetMaxBetaChangePerStep(10.0);
//  optPhys->SetTrackSecondariesFirst(kCerenkov,true);

     
}

B1PhysicsList::~B1PhysicsList()
{
}

void B1PhysicsList::ConstructParticle()
{
  G4OpticalPhoton::OpticalPhotonDefinition();

  G4BosonConstructor  pBosonConstructor;
  pBosonConstructor.ConstructParticle();

  G4LeptonConstructor pLeptonConstructor;
  pLeptonConstructor.ConstructParticle();

  G4MesonConstructor pMesonConstructor;
  pMesonConstructor.ConstructParticle();

  G4BaryonConstructor pBaryonConstructor;
  pBaryonConstructor.ConstructParticle();

  G4IonConstructor pIonConstructor;
  pIonConstructor.ConstructParticle();

  G4ShortLivedConstructor pShortLivedConstructor;
  pShortLivedConstructor.ConstructParticle();  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void B1PhysicsList::SetCuts()
{
 
 SetCutsWithDefault();   
  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
