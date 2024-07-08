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
/// \file absorber/src/RunAction.cpp
/// \brief Implementation of the RunAction class

#include "RunAction.h"
#include "PrimaryGeneratorAction.h"

//#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
{
    // Create or get analysis manager
    // The choice of the output format is done via the specified
    // file extension.
    auto analysisManager = G4AnalysisManager::Instance();

    // Create directories
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetFileName("A1");
    analysisManager->SetVerboseLevel(0);
    analysisManager->SetActivation(true);   //Enable inactivation of histograms
    // Note: merging ntuples is available only with Root output

    // Define histograms start values
    constexpr G4int kMaxHisto = 6;
    const G4String id[] = { "0","1","2","3","4","5" };
    const G4String title[] =
    {
        "dummy",                                //0
        "energy spectrum (%): e+ e-",           //1
        "energy spectrum (%): nu_e anti_nu_e",  //2
        "energy spectrum (%): gamma",           //3
        "energy spectrum (%): alpha",           //4
        "energy spectrum (%): ions",            //5
    };

    // Default values (to be reset via /analysis/h1/set command)
    constexpr G4int nbins = 100;
    constexpr G4double vmin = 0.0;
    constexpr G4double vmax = 100 * MeV;

    // Create all histograms as inactivated
    // as we have not yet set nbins, vmin, vmax
    for (G4int k = 0; k < kMaxHisto; k++)
    {
        auto ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
        analysisManager->SetH1Activation(ih, false);
    }

    // Register accumulable to the accumulable manager
    auto accumulableManager = G4AccumulableManager::Instance();

    for (G4int i = 0; i < fEkin.size(); i++)
    {
        accumulableManager->RegisterAccumulable(fEkin[i]);
    }
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Open an output file
    //
    analysisManager->OpenFile();

    // Reset accumulables to their initial values
    auto accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Save histograms
    //
    analysisManager->Write();
    analysisManager->CloseFile();

    G4int nofEvents = aRun->GetNumberOfEvent();
    if (nofEvents == 0) return;

    // Merge accumulables
    auto accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    // Compute Kinetic Energy
    auto electronEkin = fEkin[1].GetValue();
    auto neutrinoEkin = fEkin[2].GetValue();
    auto gammaEkin = fEkin[3].GetValue();
    auto alphaEkin = fEkin[4].GetValue();
    auto ionEkin = fEkin[5].GetValue();

    // Print
    //
    if (IsMaster())
    {
        G4cout
            << G4endl
            << "--------------------End of Global Run-----------------------";
    }
    else
    {
        G4cout
            << G4endl
            << "--------------------End of Local Run------------------------";
    }

    G4cout
        << G4endl
        << " The run consists of " << nofEvents << " primary events."
        << G4endl
        << " The total electron and positron kinetic energy is "
        << G4BestUnit(electronEkin, "Energy") << "."
        << G4endl
        << " The total neutrion and antineutrion kinetic energy is "
        << G4BestUnit(neutrinoEkin, "Energy") << "."
        << G4endl
        << " The total gamma kinetic energy is "
        << G4BestUnit(gammaEkin, "Energy") << "."
        << G4endl
        << " The total alpha kinetic energy is "
        << G4BestUnit(alphaEkin, "Energy") << "."
        << G4endl
        << " The total ion kinetic energy is "
        << G4BestUnit(ionEkin, "Energy") << "."
        << G4endl;
}

void RunAction::AddEkin(G4int ih, G4double ekin)
{
    fEkin[ih] += ekin;
}
