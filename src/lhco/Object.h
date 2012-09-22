/*
 * Object.h
 *
 *  Created on: 11.09.2012
 *      Author: lo
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "src/math/FourVector.h"
#include <string>
#include <sstream>

/// Object represents an object seen by the detector.
class Object {
public:
	// Object type
	typedef enum {
		Photon = 0, Electron = 1, Muon = 2, Tau = 3, Jet = 4, MET = 6, Unknown = 200
	} Typ;

	// Object() constructs an object with type Unknown and all properties set to 0.0.
	Object();
	virtual ~Object();

	/// Name returns the name of the object e.g. "photon"
	std::string Name() const;

	/// Type of the object
	Typ Type;

	/// Pseudorapidity
	double Eta;
	/// azimuthal angle
	double Phi;
	/// transverse momentum
	double PT;
	/// invariant mass
	double InvariantMass;
	/// number of tracks (for leptons this number is multiplied with the charge)
	double NumberOfTracks;
	/// hadronic versus eletromagnetic energy deposited
	/// in the calorimeter cells associated with the object.
	double HadVsEmEnergy;
	int BTag;
	// For future use: should always be 0.0 at the moment
	double Dummy1;
	double Dummy2;

	/// FourMomentum returns the four momentum vector of this object.
	FourVector FourMomentum() const;

	/// String returns a JSON representation of the object.
	std::string String() const;

};

#endif /* OBJECT_H_ */
