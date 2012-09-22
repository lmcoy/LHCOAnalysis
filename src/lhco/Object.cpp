/*
 * Object.cpp
 *
 *  Created on: 11.09.2012
 *      Author: lo
 */

#include "Object.h"

Object::Object(){
	Type = Unknown;
	PT = 0.0;
	Eta = 0.0;
	Phi = 0.0;
	BTag = 0.0;
	InvariantMass = 0.0;
	NumberOfTracks = 0.0;
	HadVsEmEnergy = 0.0;
	Dummy1 = 0.0;
	Dummy2 = 0.0;
}

Object::~Object() {

}

std::string Object::Name() const {
	switch(Type) {
	case Photon:
		return "photon";
	case Electron:
		return "electron";
	case Muon:
		return "muon";
	case Tau:
		return "tau";
	case Jet:
		return "jet";
	case MET:
		return "MET";
	default:
		return "unknown object";
	}
	return ""; // not reachable
}

FourVector Object::FourMomentum() const {
	FourVector result;
	result.SetFromMassPtEtaPhi(InvariantMass, PT, Eta, Phi);
	return result;
}

std::string Object::String() const {
	std::stringstream result;
	result << "{\n";
	result << "    \"Type\": \"" << Name() << "\",\n";
	result << "    \"Eta\": " << Eta << ",\n";
	result << "    \"Phi\": " << Phi << ",\n";
	result << "    \"PT\": " << PT << ",\n";
	result << "    \"InvariantMass\": " << InvariantMass << ",\n";
	result << "    \"NumberOfTracks\": " << NumberOfTracks << ",\n";
	result << "    \"HadVsEmEnergy\": " << HadVsEmEnergy << ",\n";
	result << "    \"BTag\": " << BTag << ",\n";
	result << "    \"Dummy1\": " << Dummy1 << ",\n";
	result << "    \"Dummy2\": " << Dummy2 << ",\n";
	result << "}";
	return result.str();
}
