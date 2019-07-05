#ifndef Generic_Functions_h
#define Generic_Functions_h

// Calculates the invariant mass of two 4-vectors
double InvariantMass(TLorentzVector *Vector1, TLorentzVector *Vector2) {
	
	double inv_mass = (*Vector1 + *Vector2).M();
	return inv_mass;
}

void MC_Analysis::print_variable() {
	cout << "elec_0_pt from func def: " << elec_0_p4->Pt() << endl;
}

// Works out what type of event is occuring
string MC_Analysis::event_type() {
	string event_type;
	if (elec_0 > 0) {
		event_type = "Electron";
	}
	if (muon_0 > 0) {
		event_type = "Muon";
	}
	if (tau_0 > 0) {
		event_type = "Tau";
	}
	return event_type;
}

/*void MC_Analysis::particle_selection() {
	
	if (event_type() == "Electron") {
		lep_0 = elec_0; // MAY BE =& HERE 
		lep_0_p4 = elec_0_p4;
		lep_0_q = elec_0_q; // AND HERE 
	}
}*/

// Checks an event is a lepton-antilepton pair
bool MC_Analysis::event_pair_truth() {
	bool event_pair=true;

	if (event_type() == "Electron") {
		if (elec_1 == 0) {
			event_pair=false;
		}
		if (elec_0_q == elec_1_q) {
			event_pair=false;			
		}
	}
	if (event_type() == "Muon") {
		if (muon_1 == 0) {
			event_pair=false;
		}
		if (muon_0_q == muon_1_q) {
			event_pair=false;			
		}
	}
	if (event_type() == "Tau") {
		if (tau_1 == 0) {
			event_pair=false;
		}
		if (tau_0_q == tau_1_q) {
			event_pair=false;			
		}
	}

	return event_pair;	
}

// Finds out if an event meets initial selection cut criteria 
bool MC_Analysis::initial_cuts_truth() {
	bool passed_cuts=true;

	bool cut_kin=true;		// Kinematic Acceptance Cut pT <cut_kin_E GeV (NOTE will not have any effect on MC simulations)
	double cut_kin_E = 25;		
	bool cut_bjets=true;		// Removes events containing b meson jets
	bool cut_2jets=true;		// Check that events have at least two jets
	bool cut_jets_pt=true;		// Cuts leading jet at 55 GeV and sub-leading jet at 45 GeV (light jets)
	double cut_jets_L_pt = 55;
	double cut_jets_SL_pt = 45;
	bool cut_jet_inv_mass=true;	// Invariant mass of leading jets > 250 GeV
	double cut_jet_inv_mass_E = 250;
	bool cut_inv_mass_min=true;	// Invariant mass > 40 GeV
	double cut_inv_mass_min_E = 40; 

	double elec_0_pt = elec_0_p4->Pt();
	double elec_1_pt = elec_1_p4->Pt();
	double muon_0_pt = muon_0_p4->Pt();
	double muon_1_pt = muon_1_p4->Pt();
	double tau_0_pt = tau_0_p4->Pt();
	double tau_1_pt = tau_1_p4->Pt();
	double ljet_0_pt = ljet_0_p4->Pt();
	double ljet_1_pt = ljet_1_p4->Pt();
	
	if (event_type() == "Electron") {
		if (cut_kin == true) {
			if (elec_0_pt < cut_kin_E || elec_1_pt < cut_kin_E) {
				passed_cuts=false;
			}
		}	
		if (cut_inv_mass_min == true) {
			if (InvariantMass(elec_0_p4, elec_1_p4) < cut_inv_mass_min_E) {
				passed_cuts=false;
			}
		}
	}
	if (event_type() == "Muon") {
		if (cut_kin == true) {
			if (muon_0_pt < cut_kin_E || muon_1_pt < cut_kin_E) {
				passed_cuts=false;
			}
		}
		if (cut_inv_mass_min == true) {
			if (InvariantMass(muon_0_p4, muon_1_p4) < cut_inv_mass_min_E) {
				passed_cuts=false;
			}
		}
	}
	if (event_type() == "Tau") {
		if (cut_kin == true) {
			if (tau_0_pt < cut_kin_E || tau_1_pt < cut_kin_E) {
				passed_cuts=false;
			}
		}
		if (cut_inv_mass_min == true) {
			if (InvariantMass(tau_0_p4, tau_1_p4) < cut_inv_mass_min_E) {
				passed_cuts=false;
			}
		}
	}
	if (cut_bjets == true) {
		if (bjet_0 > 0) {
			passed_cuts=false;
		}
	}
	if (cut_2jets == true) {
		if (n_jets < 2) {
			passed_cuts=false;
		}
	}
	if (cut_jets_pt == true) {
		if (ljet_0_pt < cut_jets_L_pt) {
			passed_cuts=false;
		}
		if (ljet_1_pt < cut_jets_SL_pt) {
			passed_cuts=false;
		}
	}
	if (cut_jet_inv_mass == true) {
		if (InvariantMass(ljet_0_p4, ljet_1_p4) < cut_jet_inv_mass_E) {
			passed_cuts=false;
		}
	}
	



	return passed_cuts;
}



# endif
