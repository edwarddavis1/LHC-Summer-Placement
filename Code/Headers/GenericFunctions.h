#ifndef Generic_Functions_h
#define Generic_Functions_h

double InvariantMass(TLorentzVector *Vector1, TLorentzVector *Vector2) {

	double inv_mass = (*Vector1 + *Vector2).M();
	return inv_mass;
}

void MC_Analysis::print_variable() {
	cout << "elec_0_pt from func def: " << elec_0_p4->Pt() << endl;
}

double Centrality(TLorentzVector *Vector1, TLorentzVector *Vector2,
					TLorentzVector *Vector3, TLorentzVector *Vector4) {

	double Z_rapidity = ((*Vector1)+(*Vector2)).Rapidity();
	double j1_rapidity = Vector3->Eta();
	double j2_rapidity = Vector4->Eta();

	double sum1 = Z_rapidity - (j1_rapidity + j2_rapidity)/2;
	double Centrality = 2 * sum1/(Vector1->Rapidity() - Vector2->Rapidity());
	return Centrality;
}


double PtBalance(TLorentzVector *lep_0_Vector, TLorentzVector *lep_1_Vector,
				TLorentzVector *jet_0_Vector, TLorentzVector *jet_1_Vector) {
	double lep_0_pt = lep_0_Vector->Pt();
	double lep_1_pt = lep_1_Vector->Pt();
	double jet_0_pt = jet_0_Vector->Pt();
	double jet_1_pt = jet_1_Vector->Pt();
	double pt_sum_mod = abs(lep_0_pt + lep_1_pt + jet_0_pt + jet_1_pt);

	double pt_mod_sum = ((*lep_0_Vector) + (*lep_1_Vector) + (*jet_0_Vector)
	 					+ (*jet_1_Vector)).Pt();

	double pt_balance = pt_sum_mod / pt_mod_sum;

	return pt_balance;
}

// calculates angular separation
double DeltaR(TLorentzVector *Vector1, TLorentzVector *Vector2){
	double delta_eta = Vector1->Eta() - Vector2->Eta();
	double delta_phi = Vector1->Phi() - Vector2->Phi();
	double delta_R = sqrt(pow(delta_eta,2) + pow(delta_phi,2));
	return delta_R;
}

// works out what type of event is occuring
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
		lep_0 = elec_0;
		lep_0_p4 = elec_0_p4;
		lep_0_q = & elec_0_q;

		lep_1 = elec_1;
		lep_1_p4 = elec_1_p4;
		lep_1_q = & elec_1_q;

		n_leptons = n_electrons;
	}

	if (lep_type == "Muon") {
		lep_0 = muon_0;
		lep_0_p4 = muon_0_p4;
		lep_0_q = & muon_0_q;

		lep_1 = muon_1;
		lep_1_p4 = muon_1_p4;
		lep_1_q = & muon_1_q;

		n_leptons = n_muons;
	}

	if (lep_type == "Tau") {
		lep_0 = tau_0;
		lep_0_p4 = tau_0_p4;
		lep_0_q = & tau_0_q;

		lep_1 = tau_1;
		lep_1_p4 = tau_1_p4;
		lep_1_q = & tau_1_q;

		n_leptons = n_taus;
	}

	if (lep_type == "ElectronMuon") {
		if (elec_0_p4->Pt() > muon_0_p4->Pt()){
			lep_0 = elec_0;
			lep_0_p4 = elec_0_p4;
			lep_0_q = & elec_0_q;

			lep_1 = muon_1;
			lep_1_p4 = muon_1_p4;
			lep_1_q = & muon_1_q;
		} else {
			lep_0 = muon_0;
			lep_0_p4 = muon_0_p4;
			lep_0_q = & muon_0_q;

			lep_1 = elec_1;
			lep_1_p4 = elec_1_p4;
			lep_1_q = & elec_1_q;
		}
	}

	if (lep_type == "ElectronTau") {
		if (elec_0_p4->Pt() > tau_0_p4->Pt()){
			lep_0 = elec_0;
			lep_0_p4 = elec_0_p4;
			lep_0_q = & elec_0_q;

			lep_1 = tau_1;
			lep_1_p4 = tau_1_p4;
			lep_1_q = & tau_1_q;
		} else {
			lep_0 = tau_0;
			lep_0_p4 = tau_0_p4;
			lep_0_q = & tau_0_q;

			lep_1 = elec_1;
			lep_1_p4 = elec_1_p4;
			lep_1_q = & elec_1_q;
		}
	}

	if (lep_type == "MuonTau") {
		if (muon_0_p4->Pt() > tau_0_p4->Pt()){
			lep_0 = muon_0;
			lep_0_p4 = muon_0_p4;
			lep_0_q = & muon_0_q;

			lep_1 = tau_1;
			lep_1_p4 = tau_1_p4;
			lep_1_q = & tau_1_q;
		} else {
			lep_0 = tau_0;
			lep_0_p4 = tau_0_p4;
			lep_0_q = & tau_0_q;

			lep_1 = muon_1;
			lep_1_p4 = muon_1_p4;
			lep_1_q = & muon_1_q;
		}
	}
}

//If Vector 3 or 4 lies between Vector 1 and Vector 2, with pT greater than 25GeV
bool RapidityIntervalCheck(TLorentzVector *Vector1, TLorentzVector *Vector2, TLorentzVector *Vector3, TLorentzVector *Vector4) {

	bool rap_int_condition = true;

	//No additional jets with p_T > 25 GeV in rapidity interval between two leading jets
	//First, need to find which leading jet is max and min and assign them these names
	//Define the variables outside
	double maxjet;
	double minjet;

	if (Vector1->Rapidity() > Vector2->Rapidity()) { // if ljet_0 is greater than ljet_1, assign it as max
		maxjet = Vector1->Rapidity();
		minjet = Vector2->Rapidity();
	} else { // if it is smaller, assign it as the min
		minjet = Vector1->Rapidity();
		maxjet = Vector2->Rapidity();
	}

	// if additional jet_2 or jet_3 is between this rapidity interval, and have pT > 25, cut
	if (minjet <= Vector3->Rapidity() && Vector3->Rapidity() <= maxjet && Vector3->Pt() > 25) rap_int_condition = false;
	if (minjet <= Vector4->Rapidity() && Vector4->Rapidity() <= maxjet && Vector4->Pt() > 25) rap_int_condition = false;

	return rap_int_condition;

}

void MC_Analysis::SelectionCuts() {
	#include "Headers/VariableExtraction.h"

	//------------------------- PRE-SELECTION CUTS ---------------------------//
	pre_selection_cuts=true;

	if (lep_1 == 0) pre_selection_cuts = false;		// Two leptons

	if (lep_0_q == lep_1_q) pre_selection_cuts = false;		// Lepton pair

	if (ljet_1 == 0) pre_selection_cuts = false;	// At least two light jets

	double cut_kin_E = 30;							// lep_pt >= 25 GeV
	if (lep_0_pt < cut_kin_E or lep_1_pt < cut_kin_E) {
		pre_selection_cuts = false;
	}

	double cut_jets_L_pt = 55;						// leading jet at 55 GeV
	if (ljet_0_pt < cut_jets_L_pt) pre_selection_cuts = false;

	double cut_jets_SL_pt = 45;						// Sub-leading jet at 45 GeV
	if (ljet_1_pt < cut_jets_SL_pt) pre_selection_cuts = false;

	if (bjet_0 > 0) pre_selection_cuts = false;		// No b jets

	//---------------------------- BASELINE CUTS -----------------------------//
	baseline_cuts=true;

	double cut_jet_inv_mass = 250;		// Inv mass of leading jets > 250 GeV
	if (InvariantMass(ljet_0_p4, ljet_1_p4) < cut_jet_inv_mass) {
		baseline_cuts = false;
	}


}



# endif
