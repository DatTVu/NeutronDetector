#include "B1DetectorConstruction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "B1StackingAction.hh"
#include "B1SteppingAction.hh"
#include "B1PhysicsList.hh"
#include "QGSP_BERT.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UnitsTable.hh"
#include "G4VisManager.hh"
#include "G4ios.hh"
#include <iostream>
#include <string>
#include "G4UnitsTable.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "Randomize.hh"

using namespace std;

int main(int argc,char** argv)
{
  
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  G4RunManager * runManager = new G4RunManager;
  runManager->SetUserInitialization(new B1DetectorConstruction);
  runManager->SetUserInitialization(new B1PhysicsList);
  runManager->SetUserAction(new B1PrimaryGeneratorAction);
  runManager->SetUserAction(new B1SteppingAction);     
  runManager->SetUserAction(new B1EventAction);
  runManager->SetUserAction(new B1RunAction);
  runManager->SetUserAction(new B1StackingAction);
  runManager->Initialize();
  
#ifdef G4VIS_USE
  
  G4VisManager* visManager = new G4VisExecutive;
  
  visManager->Initialize();
#endif

  
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc!=1) {
    
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac"); 
#else
    UImanager->ApplyCommand("/control/execute init.mac"); 
#endif
    ui->SessionStart();
    delete ui;
#endif
  }

  
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}

