#ifndef TrackerHit_h
#define TrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class TrackerHit : public G4VHit
{
  public:

     TrackerHit();
      ~TrackerHit();
      TrackerHit(const TrackerHit &right);
      const TrackerHit& operator=(const TrackerHit &right);
      G4int operator==(const TrackerHit &right) const;

      inline void * operator new(size_t);
      inline void operator delete(void *aHit);

      void Draw();
      void Print();
      void SetTrackID (G4int track) {trackID = track; };
      void SetEdep    (G4double de) {edep = de; };
      void SetPos     (G4ThreeVector xyz){pos = xyz;};
      void SetID      (G4String name){ particleID = name; };
      void SetEn    (G4double ke){particleEn = ke;}; 
      G4int GetTrackID()    { return trackID; };
      G4double GetEdep()    { return edep; };      
      G4ThreeVector GetPos(){ return pos; };
      G4String GetID(){ return particleID; };
      G4double GetEn() {return particleEn; }; 

  private:
      G4double edep;
      G4ThreeVector pos;
     
      G4int         trackID;
      
      G4String	    particleID;
      G4double particleEn;

  

};

typedef G4THitsCollection<TrackerHit> TrackerHitsCollection;

extern G4Allocator<TrackerHit> TrackerHitAllocator;

inline void* TrackerHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) TrackerHitAllocator.MallocSingle();
  return aHit;
}

inline void TrackerHit::operator delete(void *aHit)
{
  TrackerHitAllocator.FreeSingle((TrackerHit*) aHit);
}

#endif
