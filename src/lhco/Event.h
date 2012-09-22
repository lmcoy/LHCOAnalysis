/*
 * Event.h
 *
 *  Created on: 11.09.2012
 *      Author: lo
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <vector>
#include <iostream>
#include <fstream>
#include "src/lhco/Object.h"
#include "src/utils/Utils.h"

const double keV = 1.0e+6;
const double MeV = 1.0e+3;
const double GeV = 1.0;
const double TeV = 1.0e-3;


/// Event represents an event in the detector.
class Event {
public:
	Event();
	virtual ~Event();

	int TriggeringInfo;
	/// Event number
	int N;

	/// Photons of this event
	std::vector<Object> Photons;
	/// Jets of this event
	std::vector<Object> Jets;
	/// Electrons of this event
	std::vector<Object> Electrons;
	/// Muons of this event
	std::vector<Object> Muons;
	/// Taus of this event
	std::vector<Object> Taus;
	/// Missing transverse energy
	Object MET;


	/// String returns a string representation (JSON) of this object.
	std::string String() const;
};

// LoadEventsFromStream loads events from a stream in lhco format.
std::vector<Event> LoadEventsFromStream(std::istream & stream);

// LoadEventsFromStream loads events from a file in lhco format.
std::vector<Event> LoadEventsFromFile(const char * file);

#endif /* EVENT_H_ */
