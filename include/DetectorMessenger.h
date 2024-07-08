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
/// \file absorber/include/DetectorMessenger.h
/// \brief Definition of the DetectorMessenger class

#pragma once

#ifndef DetectorMessenger_h
#define DetectorMessenger_h

#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithAString;
class G4UIcmdWith3Vector;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;

class DetectorConstruction;

/// Messenger class that defines commands for DetectorConstruction.
///
/// It implements commands:
/// - /B2/det/setTargetMaterial name
/// - /B2/det/setChamberMaterial name
/// - /B2/det/stepMax value unit

class DetectorMessenger : public G4UImessenger
{
public:
	DetectorMessenger(DetectorConstruction* det);
	~DetectorMessenger() override;

	void SetNewValue(G4UIcommand* command, G4String newValue) override;

private:
	DetectorConstruction* fDetConstruction{ nullptr };

	G4UIdirectory* fDirectory{ nullptr };
	G4UIcmdWithABool* fSetAbsoCmd{ nullptr };
	G4UIcmdWithAnInteger* fSetNbOfAbsoCmd{ nullptr };
	G4UIcmdWithADoubleAndUnit* fAbso1ThickCmd{ nullptr };
	G4UIcmdWithAString* fAbso1MatCmd{ nullptr };
	G4UIcmdWithADoubleAndUnit* fAbso2ThickCmd{ nullptr };
	G4UIcmdWithAString* fAbso2MatCmd{ nullptr };
	G4UIcmdWithADoubleAndUnit* fAbso3ThickCmd{ nullptr };
	G4UIcmdWithAString* fAbso3MatCmd{ nullptr };
	G4UIcmdWithADoubleAndUnit* fAbso4ThickCmd{ nullptr };
	G4UIcmdWithAString* fAbso4MatCmd{ nullptr };
};

#endif // !DetectorMessenger_h
