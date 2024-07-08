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
/// \file absorber/include/DetectorConstruction.h
/// \brief Definition of the DetectorConstruction class

#pragma once

#ifndef DetectorConstruction_h
#define DetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include <vector>

class DetectorMessenger;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction() override;

	G4VPhysicalVolume* Construct() override;

	void SetWantAbso(G4bool bAbso) { fIWantAbso = bAbso; }
	void SetNbOfAbso(G4int nb) { fNbOfAbso = nb; }
	void SetAbso1Thick(G4double thick);
	void SetAbso2Thick(G4double thick);
	void SetAbso3Thick(G4double thick);
	void SetAbso4Thick(G4double thick);
	void SetAbso1Mat(G4String mat);
	void SetAbso2Mat(G4String mat);
	void SetAbso3Mat(G4String mat);
	void SetAbso4Mat(G4String mat);

private:
	DetectorMessenger* fMessenger{ nullptr };

	G4bool fIWantAbso{ false };
	G4int fNbOfAbso{ -1 };

	std::vector<G4double> fAbsoThick;
	std::vector<G4String> fAbsoMat;
};

#endif // !DetectorConstruction_h
