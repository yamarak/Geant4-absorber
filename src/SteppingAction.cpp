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
//
/// \file absorber/src/SteppingAction.cpp
/// \brief Implementation of the SteppingAction class

#include "SteppingAction.h"
#include "RunAction.h"

#include "G4Step.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4ParticleTypes.hh"
#include "G4AnalysisManager.hh"

SteppingAction::SteppingAction(RunAction* runAction)
    : fRunAction(runAction)
{
    fDetector = G4PhysicalVolumeStore::GetInstance()->GetVolume("Detector");
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    // Collect energy step by step

    // Get current step point
    auto stepPoint = step->GetPreStepPoint();

    // Get volume of the current step
    auto volume = stepPoint->GetTouchableHandle()->GetVolume();

    if (volume == fDetector)
    {
        auto track = step->GetTrack();
        auto particle = track->GetDefinition();
        auto charge = particle->GetPDGCharge();

        auto ekin = stepPoint->GetKineticEnergy();

        // Energy spectrum
        //
        if (ekin > 0.0)
        {
            G4int ih = 0;
            if (particle == G4Electron::Electron() ||
                particle == G4Positron::Positron()) ih = 1;
            else if (particle == G4NeutrinoE::NeutrinoE() ||
                particle == G4AntiNeutrinoE::AntiNeutrinoE()) ih = 2;
            else if (particle == G4Gamma::Gamma()) ih = 3;
            else if (particle == G4Alpha::Alpha()) ih = 4;
            else if (charge > 2.0) ih = 5;
            if (ih)
            {
                G4AnalysisManager::Instance()->FillH1(ih, ekin);
                fRunAction->AddEkin(ih, ekin);
            }
        }
        track->SetTrackStatus(fStopAndKill);
    }
}
