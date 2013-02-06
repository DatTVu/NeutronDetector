#ifndef GammaPhysics_h
#define GammaPhysics_h 1

#include "globals.hh"
#include "G4VPhysicsConstructor.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GammaPhysics : public G4VPhysicsConstructor
{
  public:
    GammaPhysics(const G4String& name="gamma");
   ~GammaPhysics();

  public:
    void ConstructParticle() { };
    void ConstructProcess();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
