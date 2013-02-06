#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4LogicalVolume;

class B1SteppingAction : public G4UserSteppingAction
{
  public:
    B1SteppingAction();
    virtual ~B1SteppingAction();

    // static access method
    static B1SteppingAction* Instance();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

    // reset accumulated energy
    void Reset();

    // set methods
    void SetVolume(G4LogicalVolume* volume) { fVolume = volume; }
  
    // get methods
    G4LogicalVolume* GetVolume() const { return fVolume; }
    G4double GetEnergy() const { return fEnergy; }
   
  private:
    static B1SteppingAction* fgInstance;  
  
    G4LogicalVolume* fVolume;
    G4double  fEnergy;
};


#endif
