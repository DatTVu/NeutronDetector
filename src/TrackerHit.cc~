#include "TrackerHit.hh"
#include "G4UnitsTable.hh"


G4Allocator<TrackerHit> TrackerHitAllocator;
TrackerHit::TrackerHit() {}
TrackerHit::~TrackerHit() {}
TrackerHit::TrackerHit(const TrackerHit& right)
: G4VHit() {
trackID = right.trackID;
pos = right.pos;
}
const TrackerHit& TrackerHit::operator=(const TrackerHit& right) {
trackID = right.trackID;
pos = right.pos;
return *this;
}
G4int TrackerHit::operator==(const TrackerHit& right) const {
return (this == &right) ? 1 : 0;
}
void TrackerHit::Draw()
{}
void TrackerHit::Print()
{}
