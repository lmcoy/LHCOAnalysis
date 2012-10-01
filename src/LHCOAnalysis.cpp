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

extern "C" {
#include <getopt.h>
}

#include "src/lhco/Event.h"


bool sortPT(const Object & obj1, const Object & obj2 ) { return (obj1.PT>obj2.PT); }

bool ApplyCuts( Event & event, unsigned long jet_multiplicity, double min_MET, double min_HT ) {
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

	if( event.MET.PT < min_MET ) {
		return false;
	}

	double HT = 0.0;
	for( auto jet = event.Jets.begin(); jet != event.Jets.end(); ++jet ) {
		HT += jet->FourMomentum().ET();
	}

	if( HT < min_HT ) {
		return false;
	}


	return true;
}

void print_usage(void) {
	std::cout << "Usage:\n";
	std::cout << "    LHCOAnalysis --jet_mult 3 --min_ht 100 --min_met 50 file.lhco\n";
	std::cout << "        (reads events from file)\n";
	std::cout << "  or\n";
	std::cout << "    LHCOAnalysis --jet_mult 3 --min_ht 100 --min_met 50\n";
	std::cout << "        (reads events from stdin)\n";
	std::cout << "Options:\n";
	std::cout.width(20);
	std::cout << std::left << "  --jet_mult" << "jet multiplicity. Event must have at least jet_mult (>= 2) jets to pass cuts.\n";
	std::cout.width(20);
	std::cout << std::left << "  --min_ht" << "H_T cut. Only events with H_T > min_ht (in GeV) pass cuts.\n";
	std::cout.width(20);
	std::cout << std::left << "  --min_met" << "MET cut. Only events with MET > min_met (in GeV) pass cuts.\n";
}


int main(int argc, char* argv[]) {


	// define possible cmd line options
	static struct option long_options[] = {
		{"jet_mult", required_argument, 0, 'j'},
		{"min_met", required_argument, 0, 'e'},
		{"min_ht", required_argument, 0, 'm'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};
	int option_index = 0;
	int c;
	char *jopt = 0;
	char *eopt = 0;
	char *mopt = 0;

	// parse cmd line options
	while (( c = getopt_long_only(argc, argv,"hj:e:m:", long_options, &option_index )) != -1 ) {
		switch(c) {
		case 'j':
			jopt = optarg;
			break;
		case 'e':
			eopt = optarg;
			break;
		case 'm':
			mopt = optarg;
			break;
		case 'h':
			print_usage();
			exit(EXIT_SUCCESS);
		case '?':
			break;
		default:
			exit(EXIT_FAILURE);
		}
	}

	// Check if all options are set
	bool failed = false;
	if( jopt == 0 ) {
		std::cerr << "error: jet multiplicity is missing.\n    You have to use the --jet_mult int (>=2) option.\n";
		failed = true;
	}
	if( mopt == 0 ) {
		std::cerr << "error: min H_T cut is missing.\n    Use --min_ht float (>=0.0) option.\n";
		failed = true;
	}	   
	if( eopt == 0 ) {
		std::cerr << "error: min MET cut is missing.\n    Use --min_met float (>=0.0) option.\n";
		failed = true;
	}
	if( failed ) {
		exit(EXIT_FAILURE);
	}

	// use cmd line options
	bool ok = true;
	double min_HT = ParseDouble(mopt, &ok);
	if( !ok || min_HT < 0.0 ) {
		std::cerr << "error: --min_ht expects a float (>= 0.0).\n";
		failed = true;
	}
	double min_MET = ParseDouble(eopt, &ok);
	if( !ok || min_MET < 0.0 ) {
		std::cerr << "error: --min_met expects a float (>= 0.0).\n";
		failed = true;
	}
	int jet_multiplicity = ParseLong(jopt, &ok);
	if( !ok || jet_multiplicity < 2 ) {
		std::cerr << "error: --jet_mult expects a int (>= 2).\n";
		failed = true;
	}
	if( failed ) {
		exit(EXIT_FAILURE);
	}

	std::cout << "--min_ht =   " << min_HT << "\n";
	std::cout << "--min_met =  " << min_MET << "\n";
	std::cout << "--jet_mult = " << jet_multiplicity << "\n";


	std::vector<Event> events;
	if(optind < argc) {
		if(optind+1 != argc) {
			std::cerr << "warning: only one file is supported. ignoring all other files...\n";
		}
		std::cout << "file: " << argv[optind] << "\n";
		events = LoadEventsFromFile(argv[optind]);

		if( events.size() == 0 ) {
			std::cerr << "error: no events read from " << argv[optind] << ". Does it exist?\n";
			exit(EXIT_FAILURE);
		}
		std::cout << events.size() << " events read from " << argv[optind] << "\n";
	} else {
		events = LoadEventsFromStream( std::cin );
		std::cout << events.size() << " events read from stdin\n";
	}


	unsigned long passed = 0;
	for( auto it = events.begin(); it != events.end(); ++it ) {
		if( ApplyCuts(*it, jet_multiplicity, min_MET, min_HT ) ) {
			passed += 1;
		}
	}

	std::cout << passed << " events pass the cuts\n";
	std::cout << "efficiency: " << (double)passed/(double)events.size() << "\n";

	return EXIT_SUCCESS;
}
