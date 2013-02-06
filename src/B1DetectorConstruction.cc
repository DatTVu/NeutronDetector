#include "B1DetectorConstruction.hh"
#include "B1SteppingAction.hh"
   
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4SDManager.hh"
#include "TrackerSD.hh"
#include "TrackerHit.hh"
#include "G4VSensitiveDetector.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpBoundaryProcess.hh"

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction()
{ 
  DefineMaterials();
}


B1DetectorConstruction::~B1DetectorConstruction()
{ }
//......................................................
void B1DetectorConstruction::DefineMaterials()
{ G4int ncomponents;
  G4double abundance, massfraction;
  G4Isotope* B10 = new G4Isotope("B10", 5, 10);
  G4Element* b10  = new G4Element("Boron10","B10",ncomponents=1);
  b10->AddIsotope(B10, abundance= 100.*perCent);
  G4Material* boron10 
         = new G4Material("Boron10", 2.46*g/cm3, ncomponents=1);
  boron10->AddElement(b10, massfraction=100.*perCent);
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* PyrexGlass = nist->FindOrBuildMaterial("G4_Pyrex_Glass");
  /*G4Material* Eu = nist->FindOrBuildMaterial("G4_Eu");*/

G4double a; G4double z; G4double density;
G4String name;
G4String symbol;

//elements for mixtures and compounds
G4Element* H = new G4Element(name="Hydrogen",symbol="H", z=1., a= 1.01*g/mole);
G4Element* C = new G4Element(name="Carbon", symbol="C", z=6., a= 12.01*g/mole);
G4int natoms;

G4Material* PTP = new G4Material(name="PTP",density= 1.234*g/cm3, ncomponents=2);
PTP->AddElement(C, natoms=18);
PTP->AddElement(H , natoms=14);


//*********
  
    
  G4double fractionmass;
  G4Material* GlassB = new G4Material("GlassB", 1.687941408*g/cm3, 3);
  GlassB->AddMaterial(boron10, fractionmass=45*perCent);
  GlassB->AddMaterial(PyrexGlass, fractionmass=10*perCent);
  GlassB->AddMaterial(PTP, fractionmass=45*perCent);
  
//.....................................................................

  const G4int nEntries = 45;

  G4double PhotonEnergy[nEntries] =
{1.0*eV,2.48*eV,2.611*eV,2.756*eV,2.918*eV,
2.988*eV,3.024*eV,3.100*eV,3.139*eV,3.179*eV,
3.221*eV,3.263*eV,3.307*eV,3.351*eV,3.425*eV,
3.543*eV,3.647*eV,3.658*eV,3.680*eV,3.701*eV,
3.713*eV,3.758*eV,3.815*eV,3.875*eV,3.974*eV,
4.133*eV,4.276*eV,4.429*eV,4.640*eV,4.509*eV,
4.559*eV,4.593*eV,4.733*eV,4.844*eV,4.901*eV,
4.960*eV,5.082*eV,5.232*eV,5.391*eV,5.511*eV,
5.636*eV,5.767*eV,5.905*eV,6.200*eV,10.*eV};
    
  G4double RefractiveIndex1[nEntries] =
{1.65,1.65,1.65,1.65,1.65,
1.65,1.65,1.65,1.65,1.65,
1.65,1.65,1.65,1.65,1.65,
1.65,1.65,1.65,1.65,1.65,
1.65,1.65,1.65,1.65,1.65,
1.65,1.65,1.65,1.65,1.65,
1.65,1.65,1.65,1.65,1.65,
1.65,1.65,1.65,1.65,1.65,
1.65,1.65,1.65,1.65,1.65};

  G4double Absorption1[nEntries] =
{3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,
3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,
3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,
3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,
3.0*um,3.0*um,2.995*um,2.756*um,2.512*um,
2.122*um,1.488*um,1.146*um,1.0*um,1.0*um,
1.146*um,1.341*um,1.634*um,1.976*um,2.268*um,
2.439*um,2.634*um,2.707*um,2.634*um,2.234*um,
1.488*um,0.805*um,500.0*um,1000.0*um,1000.*um};

  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();

  myMPT1->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex1,nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("ABSLENGTH",    PhotonEnergy, Absorption1,     nEntries)
        ->SetSpline(true);
 
  myMPT1->AddConstProperty("SCINTILLATIONYIELD",27000./eV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE",2.012);
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 3.3*ns);
  myMPT1->AddConstProperty("SLOWTIMECONSTANT",3.7*ns);
  myMPT1->AddConstProperty("YIELDRATIO",0.8);
  
  GlassB->SetMaterialPropertiesTable(myMPT1);

}


G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 50*cm, env_sizeZ = 50*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("GlassB");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 5*env_sizeXY;
  G4double world_sizeZ  = 5*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                  
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  G4VPhysicalVolume* envPhys = new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


// Wrap up method
const G4int NUM = 2;
	 G4double Ephoton[NUM] = {2.0*eV, 4.136*eV};
	 G4double reflectivity[NUM] = {0.95, 0.95};
	 G4double efficiency[NUM] = {0.0, 0.0}; 
	 G4MaterialPropertiesTable* WrapProperty = new G4MaterialPropertiesTable();
	 WrapProperty->AddProperty("REFLECTIVITY",Ephoton,reflectivity,NUM);
	 WrapProperty->AddProperty("EFFICIENCY",Ephoton,efficiency,NUM);
G4OpticalSurface* Wrap = new G4OpticalSurface("Wrap");
	 new G4LogicalBorderSurface("Wrap", physWorld, envPhys,Wrap);
	 Wrap->SetType(dielectric_metal);
	 Wrap->SetFinish(polished);
	 Wrap->SetModel(glisur);
 	 Wrap->SetMaterialPropertiesTable(WrapProperty);
  
//...........................................................................
  G4Material* shape2_mat = nist->FindOrBuildMaterial("GlassB");
  G4ThreeVector pos2 = G4ThreeVector(0, 0*cm, 0*cm);
  // Trapezoid shape       
  G4double shape2_dxa = 45*cm, shape2_dxb = 45*cm;
  G4double shape2_dya = 45*cm, shape2_dyb = 45*cm;
  G4double shape2_dz  = 45*cm;      
  G4Trd* solidShape2 =    
    new G4Trd("Shape2",                      //its name
              0.5*shape2_dxa, 0.5*shape2_dxb, 
              0.5*shape2_dya, 0.5*shape2_dyb, 0.5*shape2_dz); //its size
                
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name
  
           
  G4VPhysicalVolume* shapephys = new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
// Set sensitive detector  
G4SDManager *SDman = G4SDManager::GetSDMpointer();
  TrackerSD* sd = new TrackerSD("sd");
  SDman->AddNewDetector(sd);
  logicShape2->SetSensitiveDetector(sd);

//..............................................................................  
//Wrap shape2
const G4int NUM1 = 2;
	 G4double Ephoton1[NUM1] = {2.0*eV, 4.136*eV};
	 G4double efficiency1[NUM1] = {0.0, 0.0}; 
	 G4MaterialPropertiesTable* WrapProperty1 = new G4MaterialPropertiesTable();
	 WrapProperty1->AddProperty("EFFICIENCY",Ephoton1,efficiency1,NUM1);
G4OpticalSurface* Wrap1 = new G4OpticalSurface("Wrap");
	 new G4LogicalBorderSurface("Wrap", shapephys, envPhys,Wrap);
	 Wrap1->SetType(dielectric_metal);
	 Wrap1->SetFinish(polished);
	 Wrap1->SetModel(glisur);
 	 Wrap1->SetMaterialPropertiesTable(WrapProperty1);
                
  B1SteppingAction* steppingAction = B1SteppingAction::Instance(); 
  steppingAction->SetVolume(logicShape2);
   
  return physWorld;
}

