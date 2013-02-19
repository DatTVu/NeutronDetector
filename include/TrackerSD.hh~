#ifndef TRACKERSD_H
#define TRACKERSD_H 1

#include "G4VSensitiveDetector.hh"
#include "TrackerHit.hh"
#include <iostream>
#include <fstream>

class G4Step;
class G4Track;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrackerSD : public G4VSensitiveDetector
{
  public:
      TrackerSD(G4String);
      TrackerSD(G4String, G4int);
     ~TrackerSD();

      virtual void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      virtual void EndOfEvent(G4HCofThisEvent*);
      void Clear();
      void DrawAll();
      void PrintAll();
 private:
 TrackerHitsCollection* trackerCollection;
 int aCount;
 G4double ke;
 G4String name;
 G4String cname;
 std::fstream* output;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
