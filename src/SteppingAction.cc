//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"

#include "HistoManager.hh"
#include "Run.hh"

#include "G4HadronicProcess.hh"
#include "G4ParticleTypes.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// SteppingAction::SteppingAction()
//: G4UserSteppingAction()
//{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // check trackID and stepNumber
  G4int trackID = aStep->GetTrack()->GetTrackID();
  G4int stepNb = aStep->GetTrack()->GetCurrentStepNumber();
  if (trackID * stepNb != 1) return;
  // ok, we are at first interaction of the primary particle

  Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());

  // count processes
  //
  const G4StepPoint* endPoint = aStep->GetPostStepPoint();
  G4VProcess* process = const_cast<G4VProcess*>(endPoint->GetProcessDefinedStep());
  run->CountProcesses(process);

  // check that an real interaction occured (eg. not a transportation)
  G4StepStatus stepStatus = endPoint->GetStepStatus();
  G4bool transmit = (stepStatus == fGeomBoundary || stepStatus == fWorldBoundary);
  if (transmit) return;

  // real processes : sum track length
  //
  G4double stepLength = aStep->GetStepLength();
  run->SumTrack(stepLength);

  // energy-momentum balance initialisation
  //
  const G4StepPoint* prePoint = aStep->GetPreStepPoint();
  G4double Q = -prePoint->GetKineticEnergy();
  G4ThreeVector Pbalance = -prePoint->GetMomentum();

  // initialisation of the nuclear channel identification
  //
  G4ParticleDefinition* particle = aStep->GetTrack()->GetDefinition();
  G4String partName = particle->GetParticleName();
  G4String nuclearChannel = partName;
  G4HadronicProcess* hproc = dynamic_cast<G4HadronicProcess*>(process);
  const G4Isotope* target = NULL;
  if (hproc) target = hproc->GetTargetIsotope();
  G4String targetName = "XXXX";
  if (target) targetName = target->GetName();
  nuclearChannel += " + " + targetName + " --> ";
  if (targetName == "XXXX") run->SetTargetXXX(true);

  // scattered primary particle (if any)
  //
  G4AnalysisManager* analysis = G4AnalysisManager::Instance();
  G4int ih = 1;
  if (aStep->GetTrack()->GetTrackStatus() == fAlive) {
    G4double energy = endPoint->GetKineticEnergy();
    analysis->FillH1(ih, energy);
    //
    G4ThreeVector momentum = endPoint->GetMomentum();
    Q += energy;
    Pbalance += momentum;
    //
    nuclearChannel += partName + " + ";
  }

  // secondaries
  G4double EmaxAll      = -1.;
  G4int    EmaxAll_id   = -1;
  G4int    EmaxTrack_id = -1;
  // Store the primary info
  auto primary = aStep->GetTrack()->GetDefinition();
  auto primary_name = primary->GetParticleName();
  // G4cout << " Primary Type !!! " << primary_name << G4endl;  
  const std::vector<const G4Track*>* secondary = aStep->GetSecondaryInCurrentStep();
  for (size_t lp = 0; lp < (*secondary).size(); lp++) 
  {
    particle = (*secondary)[lp]->GetDefinition();
    G4String name    = particle->GetParticleName();
    G4String type    = particle->GetParticleType();
    G4double energy  = (*secondary)[lp]->GetKineticEnergy();
    G4int   Track_id = (*secondary)[lp]->GetCreatorModelID();
    run->ParticleCount(name, energy);    
    // G4cout << " Second Type !!! " << name << G4endl;  
    if (energy > EmaxAll)
    {
      EmaxAll      = energy;
      EmaxAll_id   = lp;
      EmaxTrack_id = Track_id;
    }
  }
  analysis->FillH1(2,EmaxAll);
  // protection
  if (EmaxAll >= 0 && EmaxAll_id >= 0)
  {   
    particle = (*secondary)[EmaxAll_id]->GetDefinition();
    if(particle == primary)
    {
      analysis->FillH1(3,EmaxAll); 
      if ( EmaxTrack_id == 21350)    analysis->FillH1(4,EmaxAll); 
      if ( EmaxTrack_id == 21600)    analysis->FillH1(5,EmaxAll); 
    }
  }

  //  energy-momentum balance
  // G4double Pbal = Pbalance.mag();
  // run->Balance(Pbal);
  // ih = 11;
  // analysis->FillH1(ih, Q);
  // ih = 12;
  // analysis->FillH1(ih, Pbal);

  // nuclear channel
  const G4int kMax = 14;
  const G4String conver[] = {"0",  "1"  , "2 ",  "3 ",  "4 ",  "5 ",  "6 ",  "7 ", "8 ",
                             "9 ", "10 ", "11 ", "12 ", "13 "};
  std::map<G4ParticleDefinition*, G4int>::iterator ip;
  for (ip = fParticleFlag.begin(); ip != fParticleFlag.end(); ip++) {
    particle = ip->first;
    G4String name = particle->GetParticleName();
    G4int nb = ip->second;
    if (nb > kMax) nb = kMax;
    G4String Nb = conver[nb];
    if (particle == G4Gamma::Gamma()) {
      run->CountGamma(nb);
      Nb = "N ";
      name = "gamma or e-";
    }
    if (ip != fParticleFlag.begin()) nuclearChannel += " + ";
    nuclearChannel += Nb + name;
  }

  /// G4cout << "\n nuclear channel: " << nuclearChannel << G4endl;
  run->CountNuclearChannel(nuclearChannel, Q);

  fParticleFlag.clear();

  // kill event after first interaction
  //
  G4RunManager::GetRunManager()->AbortEvent();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
