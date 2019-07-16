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


// Calculates Centrality for Z boson
double Centrality(TLorentzVector *Vector1, TLorentzVector *Vector2, TLorentzVector *Vector3, TLorentzVector *Vector4) {
	
	double Z_rapidity = ((*Vector1)+(*Vector2)).Rapidity(); // Z boson rapidity using muon 4 vectors
	double j1_rapidity = Vector3->Eta();// jet 1 rapidity
	double j2_rapidity = Vector4->Eta();// jet 2 rapidity	

	double sum1 = Z_rapidity - (j1_rapidity + j2_rapidity)/2; // sum 1 to break things up
	double Centrality = 2 * sum1/(Vector1->Rapidity() - Vector2->Rapidity());
	return Centrality;
}

// Works out what type of event is occuring
void MC_Analysis::event_type() {

	if (elec_0 > 0 && muon_0 == 0 && tau_0 == 0) {
		lep_type = "Electron";
	}
	if (elec_0 == 0 && muon_0 > 0 && tau_0 == 0) {
		lep_type = "Muon";
	}
	if (elec_0 == 0 && muon_0 == 0 && tau_0 > 0) {
		lep_type = "Tau";
	}
	if (elec_0 == 0 && muon_0 > 0 && tau_0 > 0) {
		lep_type = "MuonTau";
	}
	if (elec_0 > 0 && muon_0 == 0 && tau_0 > 0) {
		lep_type = "ElectronTau";
	}
	if (elec_0 > 0 && muon_0 > 0 && tau_0 == 0) {
		lep_type = "ElectronMuon";
	}
}

void MC_Analysis::ParticleSelection() {
	event_type();
	if (lep_type == "Electron") {
		lep_0 = & elec_0;
		lep_0_p4 = elec_0_p4;
		lep_0_q = & elec_0_q;

		lep_1 = & elec_1;
		lep_1_p4 = elec_1_p4;
		lep_1_q = & elec_1_q;

		n_leptons = n_electrons; 
	}
		
	if (lep_type == "Muon") {
		lep_0 = & muon_0;
		lep_0_p4 = muon_0_p4;
		lep_0_q = & muon_0_q;

		lep_1 = & muon_1;
		lep_1_p4 = muon_1_p4;
		lep_1_q = & muon_1_q;

		n_leptons = n_muons; 
	}

	if (lep_type == "Tau") {
		lep_0 = & tau_0;
		lep_0_p4 = tau_0_p4;
		lep_0_q = & tau_0_q;

		lep_1 = & tau_1;
		lep_1_p4 = tau_1_p4;
		lep_1_q = & tau_1_q;

		n_leptons = n_taus; 
	}
	
	if (lep_type == "ElectronMuon") {
		if (elec_0_p4->Pt() > muon_0_p4->Pt()){
			lep_0 = & elec_0;
			lep_0_p4 = elec_0_p4;
			lep_0_q = & elec_0_q;

			lep_1 = & muon_1;
			lep_1_p4 = muon_1_p4;
			lep_1_q = & muon_1_q;
		} else {
			lep_0 = & muon_0;
			lep_0_p4 = muon_0_p4;
			lep_0_q = & muon_0_q;

			lep_1 = & elec_1;
			lep_1_p4 = elec_1_p4;
			lep_1_q = & elec_1_q;
		}		
	}

	if (lep_type == "ElectronTau") {
		if (elec_0_p4->Pt() > tau_0_p4->Pt()){
			lep_0 = & elec_0;
			lep_0_p4 = elec_0_p4;
			lep_0_q = & elec_0_q;

			lep_1 = & tau_1;
			lep_1_p4 = tau_1_p4;
			lep_1_q = & tau_1_q;
		} else {
			lep_0 = & tau_0;
			lep_0_p4 = tau_0_p4;
			lep_0_q = & tau_0_q;

			lep_1 = & elec_1;
			lep_1_p4 = elec_1_p4;
			lep_1_q = & elec_1_q;
		} 
	}

	if (lep_type == "MuonTau") {
		if (muon_0_p4->Pt() > tau_0_p4->Pt()){
			lep_0 = & muon_0;
			lep_0_p4 = muon_0_p4;
			lep_0_q = & muon_0_q;

			lep_1 = & tau_1;
			lep_1_p4 = tau_1_p4;
			lep_1_q = & tau_1_q;
		} else {
			lep_0 = & tau_0;
			lep_0_p4 = tau_0_p4;
			lep_0_q = & tau_0_q;

			lep_1 = & muon_1;
			lep_1_p4 = muon_1_p4;
			lep_1_q = & muon_1_q;
		} 
	}	
}

// Checks an event is a lepton-antilepton pair
bool MC_Analysis::event_pair_truth() {
	bool event_pair=true;

	if (lep_type == "Electron") {
		if (elec_1 == 0) {
			event_pair=false;
		}
		if (elec_0_q == elec_1_q) {
			event_pair=false;			
		}
	}
	if (lep_type == "Muon") {
		if (muon_1 == 0) {
			event_pair=false;
		}
		if (muon_0_q == muon_1_q) {
			event_pair=false;			
		}
	}
	if (lep_type == "Tau") {
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
	
	if (lep_type == "Electron") {
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
	if (lep_type == "Muon") {
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
	if (lep_type == "Tau") {
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
