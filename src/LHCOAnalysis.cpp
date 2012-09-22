//============================================================================
// Name        : LHCOAnalysis.cpp
// Author      : Lennart Oymanns
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include "src/lhco/Event.h"


bool sortPT(const Object & obj1, const Object & obj2 ) { return (obj1.PT>obj2.PT); }

bool ApplyCuts( Event & event, unsigned long jet_multiplicity ) {
	std::sort(event.Jets.begin(), event.Jets.end(), sortPT );
	if( event.Jets.size() < jet_multiplicity ) {
		return false;
	}
	// leading jet with PT > 100.0 GeV required
	if( event.Jets.at(0).PT < 100.0*GeV ) {
		return false;
	}
	// 2 <= i <= multiplicty jets with pT >= 50.0 GeV
	for( unsigned long i = 1; i < jet_multiplicity; i++ ) {
		if( event.Jets.at(i).PT < 50.0*GeV ) {
			return false;
		}		
	}

	// no isolated lepton with pT > 20 GeV
	for( auto electron = event.Electrons.begin(); electron != event.Electrons.end(); ++electron ) {
		if( electron->PT > 20*GeV ) {
			return false;
		}
	}
	for( auto muon = event.Muons.begin(); muon != event.Muons.end(); ++muon ) {
		if( muon->PT > 20*GeV ) {
			return false;
		}
	}
	for( auto tau = event.Taus.begin(); tau != event.Taus.end(); ++tau ) {
		if( tau->PT > 20*GeV ) {
			return false;
		}
	}

	size_t max = (jet_multiplicity==2)?2:3;
	for( size_t j = 0; j < max; j++ ) {
		Vector3 met = event.MET.FourMomentum().Momentum();
		Vector3 p_j = event.Jets.at(j).FourMomentum().Momentum();

		if( abs(p_j.PseudoRapidity()) > 2.5 ) {
			return false;
		}
		double dphi = Vector3::DeltaPhi(met,p_j );

		if( abs(dphi) < 0.2 ) {
			return false;
		}
	}


	double METvsMeff = 0.0;
	switch(jet_multiplicity) {
		case 2:
			METvsMeff = 0.30;
			break;
		case 3:
			METvsMeff = 0.25;
			break;
		default:
			METvsMeff = 0.20;
			break;
	}
	double Meff = event.MET.PT;
	for( unsigned long i = 0; i < jet_multiplicity; i++ ) {
		Meff += event.Jets.at(i).PT;
	}
	if( event.MET.PT / Meff < METvsMeff ) {
		return false;
	}
	return true;
}


int main(int argc, char* argv[]) {
	if( argc != 3 ) {
		std::cerr << "usage of " << argv[0] << ":\n    " << argv[0] << " jet_multiplicity(int) file.lhco\n";
		return EXIT_FAILURE;
	}


	bool ok = false;
	std::string mult(argv[1]);
	long jet_multiplicity = ParseLong(mult,&ok);
	if( !ok ) {
		std::cerr << "jet multiplicity must be an integer but got \""<<mult<<"\".\n";
		return EXIT_FAILURE;
	}
	if( jet_multiplicity <= 1 ) {
		std::cerr << "jet multiplicity must be greater than 1 but got " << jet_multiplicity << ".\n";
		return EXIT_FAILURE;
	}

	std::vector<Event> events = LoadEventsFromFile(argv[2]);

	if( events.size() == 0 ) {
		std::cerr << "no events read from " << argv[2] << ". Does it exist?\n";
		return EXIT_FAILURE;
	}

	std::cout << events.size() << " events read from " << argv[2] << "\n";

	unsigned long passed = 0;
	for( auto it = events.begin(); it != events.end(); ++it ) {
		if( ApplyCuts(*it, jet_multiplicity ) ) {
			passed += 1;
		}
	}

	std::cout << passed << " events pass the cuts\n";

	return EXIT_SUCCESS;
}
