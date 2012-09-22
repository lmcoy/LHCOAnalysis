/*
 * Event.cpp
 *
 *  Created on: 11.09.2012
 *      Author: lo
 */

#include "Event.h"

Event::Event() {
	TriggeringInfo = 0;
	N = 0;
}

Event::~Event() {
	// TODO Auto-generated destructor stub
}

std::vector<Event> LoadEventsFromStream(std::istream & stream) {
	std::string line;
	std::vector<Event> events;
	int linenb = 0;
	bool noevents = true;
	Event currentEvent;
	while (std::getline(stream, line)) {
		size_t comment = line.find("#");
		line = line.substr(0, comment);
		std::vector<std::string> fields = Fields(line);

		if (fields.size() <= 1) {
			// empty line
			continue;
		}

		bool ok = false;
		long nb = ParseLong(fields[0], &ok);
		if (!ok) {
			fprintf(stderr, "line %d column 1: expected number.\n", linenb + 1);
			return events;
		}

		if (nb > 0) {
			if (noevents == true) {
				fprintf(stderr, "line %d: missing event definition line.\n", linenb + 1);
				return events;
			}
			if (fields.size() != 11) {
				fprintf(stderr, "line %d: too many or too few columns for an object.\n", linenb + 1);
				return events;
			}
			long typ = ParseLong(fields[1], &ok);
			if (!ok) {
				fprintf(stderr, "line %d: column 2: expected object type (int).\n", linenb + 1);
				return events;
			}

			double values[9];
			for (size_t i = 2; i < fields.size(); i++) {
				double value = ParseDouble(fields[i], &ok);
				if (!ok) {
					fprintf(stderr, "line %d: column %lu: expected double.\n", linenb + 1, i + 1);
					return events;
				}
				values[i - 2] = value;
			}
			Object object;
			object.Eta = values[0];
			object.Phi = values[1];
			object.PT = values[2];
			object.InvariantMass = values[3];
			object.NumberOfTracks = values[4];
			object.BTag = values[5];
			object.HadVsEmEnergy = values[6];
			object.Dummy1 = values[7];
			object.Dummy2 = values[8];
			object.Type = Object::Typ(typ);
			switch (object.Type) {
			case Object::Electron:
				currentEvent.Electrons.push_back(object);
				break;
			case Object::Photon:
				currentEvent.Photons.push_back(object);
				break;
			case Object::Muon:
				currentEvent.Muons.push_back(object);
				break;
			case Object::Tau:
				currentEvent.Taus.push_back(object);
				break;
			case Object::Jet:
				currentEvent.Jets.push_back(object);
				break;
			case Object::MET:
				currentEvent.MET = object;
				break;
			default:
				std::cerr << "unkown object: " << object.Type << "\n";
				break;
			}
		} else {
			if( nb < 0 ) {
				// TODO: error message
				return events;
			}
			if( noevents == false ) {
				events.push_back(currentEvent);
			}
			if( fields.size() != 3 ) {
				fprintf( stderr, "line %d: too many columns in first line of an event.\n", linenb+1 );
				return events;
			}
			long N = ParseLong(fields[1],&ok);
			if( !ok ) {
			fprintf( stderr, "line %d column 2: expected event number: %s\n", linenb+1, fields[1].c_str() );
			   return events;
			}
	 		long tinfo = ParseLong(fields[2], &ok );
			if( !ok ) {
				fprintf(stderr, "line %d column 3: expected TriggeringInfo (number): %s\n", linenb+1, fields[2].c_str() );
				return events;
			}		
			currentEvent.N = N;
			currentEvent.TriggeringInfo = tinfo;
			currentEvent.Electrons.clear();
			currentEvent.Muons.clear();
			currentEvent.Jets.clear();
			currentEvent.Taus.clear();
			currentEvent.Photons.clear();
			currentEvent.MET = Object();
			noevents = false;


		}
	}
	if( !noevents ) {
		events.push_back(currentEvent);
	}
	return events;

}

std::vector<Event> LoadEventsFromFile(const char * file) {
	std::ifstream stream;
	stream.open(file, std::fstream::in);
	std::vector<Event> events = LoadEventsFromStream(stream);
	stream.close();

	return events;
}

std::string Event::String() const {
	std::stringstream result;
	result << "{\n";

	// Jets
	result << "    \"Jets\": [";
	if (Jets.size() != 0) {
		result << "\n";
	}
	for (size_t i = 0; i < Jets.size(); i++) {
		result << "    " << Jets[i].String() << ",\n";
	}
	result << "    ],\n";

	// Photons
	result << "    \"Photons\": [";
	if (Photons.size() != 0) {
		result << "\n";
	}
	for (size_t i = 0; i < Photons.size(); i++) {
		result << "    " << Photons[i].String() << ",\n";
	}
	result << "    ],\n";

	// Electrons
	result << "    \"Electrons\": [";
	if (Electrons.size() != 0) {
		result << "\n";
	}
	for (size_t i = 0; i < Electrons.size(); i++) {
		result << "    " << Electrons[i].String() << ",\n";
	}
	result << "    ],\n";

	// Muons
	result << "    \"Muons\": [";
	if (Muons.size() != 0) {
		result << "\n";
	}
	for (size_t i = 0; i < Muons.size(); i++) {
		result << "    " << Muons[i].String() << ",\n";
	}
	result << "    ],\n";

	// Taus
	result << "    \"Taus\": [";
	if (Taus.size() != 0) {
		result << "\n";
	}
	for (size_t i = 0; i < Taus.size(); i++) {
		result << "    " << Taus[i].String() << ",\n";
	}
	result << "    ],\n";

	// Missing Transverse Energy
	result << "    \"MET\": \n" << MET.String() << "\n";

	result << "}";
	return result.str();
}
