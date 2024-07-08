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
/// \file absorber/src/DetectorConstruction.cpp
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.h"
#include "DetectorMessenger.h"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

DetectorConstruction::DetectorConstruction()
{
    fMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
    delete fMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Get nist material manager
    auto nist = G4NistManager::Instance();

    // Air defined using NIST Manager
    auto air = nist->FindOrBuildMaterial("G4_AIR");

    // Sizes of the principal geometrical components (solids)

    constexpr G4double detectorRadius = 20 * mm;
    constexpr G4double detectorLength = 20 * mm;
    G4double position = -20 * mm;

    constexpr G4double worldSize = 48 * mm;

    // Option to switch on/off checking of volumes overlaps
    //
    G4bool checkOverlaps = true;

    //
    // World
    //
    auto worldS = new G4Box("World",                  // its name
        worldSize / 2, worldSize / 2, worldSize / 2); // its size

    auto worldLV = new G4LogicalVolume(worldS,  // its solid
        air,                                    // its material
        "World");                               // its name

    //  Must place the World Physical volume unrotated at (0,0,0).
    //
    auto worldPV = new G4PVPlacement(nullptr,   // no rotation
        G4ThreeVector(),                        // at (0,0,0)
        worldLV,                                // its logical volume
        "World",                                // its name
        nullptr,                                // its mother  volume
        false,                                  // no boolean operation
        0,                                      // copy number
        checkOverlaps);                         // overlaps checking

    //
    // Absorber(s)
    //
    if (fIWantAbso && fNbOfAbso >= 1
        && fAbsoThick.size() == fNbOfAbso
        && fAbsoMat.size() == fNbOfAbso)
    {
        G4cout << "Preparing to define " << fNbOfAbso << " absorber(s)."
            << G4endl;
        for (G4int i = 1; i <= fNbOfAbso; i++)
        {
            auto absoMat = nist->FindOrBuildMaterial(fAbsoMat[i - 1]);

            if (absoMat && fAbsoThick[i - 1] > 0.0)
            {
                G4ThreeVector absoPos(0, 0, position + fAbsoThick[i - 1] / 2);
                position += fAbsoThick[i - 1];
                G4String absoName = "Absorber" + std::to_string(i);

                auto absoS = new G4Tubs(absoName,                           // its name
                    0, detectorRadius, fAbsoThick[i - 1] / 2, 0, twopi);    // its size

                auto absoLV = new G4LogicalVolume(absoS,    // its solid
                    absoMat,                                // its material
                    absoName);                              // its name

                new G4PVPlacement(nullptr,  // no rotation
                    absoPos,                // at position
                    absoLV,                 // its logical volume
                    absoName,               // its name
                    worldLV,                // its mother  volume
                    false,                  // no boolean operation
                    0,                      // copy number
                    checkOverlaps);         // overlaps checking
            }
            else
            {
                G4cout << "Warning: Absorber " << i
                    << " is not defined for wrong Material or Thickness!"
                    << G4endl;
                break;
            }
        }
    }
    else
    {
        G4cout << "Absorber(s) not defined." << G4endl;
    }

    //
    // Detector
    //
    G4ThreeVector detectorPos(0, 0, position + detectorLength / 2);

    auto detectorS = new G4Tubs("Detector",                 // its name
        0, detectorRadius, detectorLength / 2, 0, twopi);   // its size

    auto detectorLV = new G4LogicalVolume(detectorS,    // its solid    
        air,                                            // its material
        "Detector");                                    // its name

    new G4PVPlacement(nullptr,  // no rotation
        detectorPos,            // at position
        detectorLV,             // its logical volume
        "Detector",             // its name
        worldLV,                // its mother  volume
        false,                  // no boolean operation
        0,                      // copy number
        checkOverlaps);         // overlaps checking

    //
    // Always return the physical World
    //
    return worldPV;
}

void DetectorConstruction::SetAbso1Thick(G4double thick)
{
    G4int size = fAbsoThick.size();
    if (size == 0)
    {
        fAbsoThick.push_back(thick);
    }
    else if (size == 1)
    {
        fAbsoThick[0] = thick;
    }
    else
    {
        G4cout << "Warning: Wrong order!" << G4endl;
    }
}

void DetectorConstruction::SetAbso2Thick(G4double thick)
{
    G4int size = fAbsoThick.size();
    if (size == 1)
    {
        fAbsoThick.push_back(thick);
    }
    if (size == 2)
    {
        fAbsoThick[1] = thick;
    }
    else
    {
        G4cout << "Warning: Wrong order!" << G4endl;
    }
}

void DetectorConstruction::SetAbso3Thick(G4double thick)
{
    G4int size = fAbsoThick.size();
    if (size == 2)
    {
        fAbsoThick.push_back(thick);
    }
    if (size == 3)
    {
        fAbsoThick[2] = thick;
    }
    else
    {
        G4cout << "Warning: Wrong order!" << G4endl;
    }
}

void DetectorConstruction::SetAbso4Thick(G4double thick)
{
    G4int size = fAbsoThick.size();
    if (size == 3)
    {
        fAbsoThick.push_back(thick);
    }
    if (size == 4)
    {
        fAbsoThick[3] = thick;
    }
    else
    {
        G4cout << "Warning: Wrong order!" << G4endl;
    }
}

void DetectorConstruction::SetAbso1Mat(G4String mat)
{
    G4int size = fAbsoMat.size();
    if (size == 0)
    {
        fAbsoMat.push_back(mat);
    }
    else if (size == 1)
    {
        fAbsoMat[0] = mat;
    }
    else
    {
        G4cout << "Warning: Wrong order!" << G4endl;
    }
}

void DetectorConstruction::SetAbso2Mat(G4String mat)
{
    G4int size = fAbsoMat.size();
    if (size == 1)
    {
        fAbsoMat.push_back(mat);
    }
    else if (size == 2)
    {
        fAbsoMat[1] = mat;
    }
    else
    {
        G4cout << "Warning: Wrong order!" << G4endl;
    }
}

void DetectorConstruction::SetAbso3Mat(G4String mat)
{
    G4int size = fAbsoMat.size();
    if (size == 2)
    {
        fAbsoMat.push_back(mat);
    }
    else if (size == 3)
    {
        fAbsoMat[2] = mat;
    }
    else
    {
        G4cout << "Warning: Wrong order!" << G4endl;
    }
}

void DetectorConstruction::SetAbso4Mat(G4String mat)
{
    G4int size = fAbsoMat.size();
    if (size == 3)
    {
        fAbsoMat.push_back(mat);
    }
    else if (size == 4)
    {
        fAbsoMat[3] = mat;
    }
    else
    {
        G4cout << "Warning: Wrong order!" << G4endl;
    }
}
