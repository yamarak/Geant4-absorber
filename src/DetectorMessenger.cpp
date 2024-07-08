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
/// \file absorber/src/DetectorMessenger.cpp
/// \brief Implementation of the DetectorMessenger class

#include "DetectorMessenger.h"
#include "DetectorConstruction.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* det)
    : fDetConstruction(det)
{
    fDirectory = new G4UIdirectory("/det/");
    fDirectory->SetGuidance("UI commands specific to detector construction control.");

    fSetAbsoCmd = new G4UIcmdWithABool("/det/setAbsorber", this);
    fSetAbsoCmd->SetGuidance("Set Absorber");
    fSetAbsoCmd->SetParameterName("fIWantAbsorber", false);
    fSetAbsoCmd->AvailableForStates(G4State_PreInit);

    fSetNbOfAbsoCmd = new G4UIcmdWithAnInteger("/det/setNbOfAbsoCmd", this);
    fSetNbOfAbsoCmd->SetGuidance("");
    fSetNbOfAbsoCmd->SetParameterName("fNbOfAbso", false);
    fSetNbOfAbsoCmd->AvailableForStates(G4State_PreInit);

    fAbso1ThickCmd = new G4UIcmdWithADoubleAndUnit("/det/setAbso1Thick", this);
    fAbso1ThickCmd->SetGuidance("Set Thickness of the Absorber1.");
    fAbso1ThickCmd->SetParameterName("Abs1Thick", false);
    fAbso1ThickCmd->AvailableForStates(G4State_PreInit);

    fAbso1MatCmd = new G4UIcmdWithAString("/det/setAbso1Mat", this);
    fAbso1MatCmd->SetGuidance("Set Material of the Absorber1.");
    fAbso1MatCmd->SetParameterName("choice", false);
    fAbso1MatCmd->AvailableForStates(G4State_PreInit);

    fAbso2ThickCmd = new G4UIcmdWithADoubleAndUnit("/det/setAbso2Thick", this);
    fAbso2ThickCmd->SetGuidance("Set Thickness of the Absorber2.");
    fAbso2ThickCmd->SetParameterName("Abs2Thick", false);
    fAbso2ThickCmd->AvailableForStates(G4State_PreInit);

    fAbso2MatCmd = new G4UIcmdWithAString("/det/setAbso2Mat", this);
    fAbso2MatCmd->SetGuidance("Set Material of the Absorber2.");
    fAbso2MatCmd->SetParameterName("choice", false);
    fAbso2MatCmd->AvailableForStates(G4State_PreInit);

    fAbso3ThickCmd = new G4UIcmdWithADoubleAndUnit("/det/setAbso3Thick", this);
    fAbso3ThickCmd->SetGuidance("Set Thickness of the Absorber3.");
    fAbso3ThickCmd->SetParameterName("Abs3Thick", false);
    fAbso3ThickCmd->AvailableForStates(G4State_PreInit);

    fAbso3MatCmd = new G4UIcmdWithAString("/det/setAbso3Mat", this);
    fAbso3MatCmd->SetGuidance("Set Material of the Absorber3.");
    fAbso3MatCmd->SetParameterName("choice", false);
    fAbso3MatCmd->AvailableForStates(G4State_PreInit);

    fAbso4ThickCmd = new G4UIcmdWithADoubleAndUnit("/det/setAbso4Thick", this);
    fAbso4ThickCmd->SetGuidance("Set Thickness of the Absorber4.");
    fAbso4ThickCmd->SetParameterName("Abs4Thick", false);
    fAbso4ThickCmd->AvailableForStates(G4State_PreInit);

    fAbso4MatCmd = new G4UIcmdWithAString("/det/setAbso4Mat", this);
    fAbso4MatCmd->SetGuidance("Set Material of the Absorber4.");
    fAbso4MatCmd->SetParameterName("choice", false);
    fAbso4MatCmd->AvailableForStates(G4State_PreInit);
}

DetectorMessenger::~DetectorMessenger()
{
    delete fSetAbsoCmd;
    delete fSetNbOfAbsoCmd;
    delete fAbso1ThickCmd;
    delete fAbso1MatCmd;
    delete fAbso2ThickCmd;
    delete fAbso2MatCmd;
    delete fAbso3ThickCmd;
    delete fAbso3MatCmd;
    delete fAbso4ThickCmd;
    delete fAbso4MatCmd;
    delete fDirectory;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if (command == fSetAbsoCmd)
    {
        fDetConstruction->SetWantAbso(fSetAbsoCmd->GetNewBoolValue(newValue));
    }

    if (command == fSetNbOfAbsoCmd)
    {
        fDetConstruction->SetNbOfAbso(fSetNbOfAbsoCmd->GetNewIntValue(newValue));
    }

    if (command == fAbso1ThickCmd)
    {
        fDetConstruction->SetAbso1Thick(fAbso1ThickCmd->GetNewDoubleValue(newValue));
    }

    if (command == fAbso1MatCmd)
    {
        fDetConstruction->SetAbso1Mat(newValue);
    }

    if (command == fAbso2ThickCmd)
    {
        fDetConstruction->SetAbso2Thick(fAbso2ThickCmd->GetNewDoubleValue(newValue));
    }

    if (command == fAbso2MatCmd)
    {
        fDetConstruction->SetAbso2Mat(newValue);
    }

    if (command == fAbso3ThickCmd)
    {
        fDetConstruction->SetAbso3Thick(fAbso3ThickCmd->GetNewDoubleValue(newValue));
    }

    if (command == fAbso3MatCmd)
    {
        fDetConstruction->SetAbso3Mat(newValue);
    }

    if (command == fAbso4ThickCmd)
    {
        fDetConstruction->SetAbso4Thick(fAbso4ThickCmd->GetNewDoubleValue(newValue));
    }

    if (command == fAbso4MatCmd)
    {
        fDetConstruction->SetAbso4Mat(newValue);
    }
}
