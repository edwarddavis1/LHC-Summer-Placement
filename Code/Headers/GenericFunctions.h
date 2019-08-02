#ifndef Generic_Functions_h
#define Generic_Functions_h

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

	double pt_balance = pt_mod_sum / pt_sum_mod;

	return pt_balance;
}

double PtBalance3(TLorentzVector *lep_0_Vector, TLorentzVector *lep_1_Vector,
				TLorentzVector *jet_0_Vector, TLorentzVector *jet_1_Vector,
				TLorentzVector *jet_2_Vector) {
	double lep_0_pt = lep_0_Vector->Pt();
	double lep_1_pt = lep_1_Vector->Pt();
	double jet_0_pt = jet_0_Vector->Pt();
	double jet_1_pt = jet_1_Vector->Pt();
	double jet_2_pt = jet_2_Vector->Pt();
	double pt_sum_mod = abs(lep_0_pt + lep_1_pt + jet_0_pt
		 					+ jet_1_pt + jet_2_pt);

	double pt_mod_sum = ((*lep_0_Vector) + (*lep_1_Vector) + (*jet_0_Vector)
	 					+ (*jet_1_Vector) + (*jet_2_Vector)).Pt();

	double pt_balance_3 = pt_mod_sum / pt_sum_mod;

	return pt_balance_3;
}

double DotProdPt(TLorentzVector *Vector1, TLorentzVector *Vector2){
	double DotProduct = Vector1->Px()*Vector2->Px() + Vector1->Py()*Vector2->Py();

	return DotProduct;
}

// calculates the Et missing along a certain vector
double ETalongVectorCalc(TLorentzVector *lep_vector,
							TLorentzVector *met_vector){
	double Et_along_vector = (met_vector->Dot(*lep_vector))/lep_vector->Pt();
	return Et_along_vector;
}

// DeltaPhi using dot product
double DeltaPhi(TLorentzVector *Vector1, TLorentzVector *Vector2){
	double a_dot_b = DotProdPt(Vector1, Vector2);
	double denominator = abs(Vector1->Pt()) * abs(Vector2->Pt());
	double final_val = a_dot_b / denominator;

	double delta_phi = acos( final_val ); 		// between tau 1 and 2

	return delta_phi;

}

// azimuthal angle between two tau candidates < pi
bool TauPhiCheck(TLorentzVector *lep_a_vector,
					TLorentzVector *lep_b_vector,
					TLorentzVector *met_vector){
	double pi = 3.141592654;

	bool tau_phi_in_range = true;
	double delta_phi_aEt = DeltaPhi(lep_a_vector, met_vector);
	double delta_phi_bEt = DeltaPhi(lep_b_vector, met_vector);

	if (delta_phi_aEt + delta_phi_bEt > pi) tau_phi_in_range = false;

	return tau_phi_in_range;
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

// converts character array to string and returns it
string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

// gets the name of the pc you're currently logged in to
string PCName() {
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    string hostname_s = convertToString(hostname, strlen(hostname));
    int first_dot = hostname_s.find(".");
    string pcname = hostname_s.substr(0,first_dot);
    return pcname;
}

// This function will return a vector of doubles, containing information
// about luminosity weighting for a given file ID
vector<double> csv_reader(string ID) {

	// create the various variables to be used
	string Line, prevLine;
	vector <double> info;
	int matchPos = 0;
	bool counterActive = true;

	// detect which computer is being used
	string pcname = PCName();

	ifstream file;

	// get file contianing luminosity information
	if (pcname == "higgs") {
		cout << "getting luminosity info from higgs" << endl;
		file.open("/higgs-data3/sam/forTomRyunAliceLuca/v02/LepUniv_xsec.csv");
	} else if (pcname == "pc2014") {
		cout << "getting luminosity info from pc2014" << endl;
		file.open("/pc2014-data4/sam/VBF_Ztt/HIGG8D1/LepUniv_xsec.csv");
	} else if (pcname == "pc2012") {
		cout << "getting luminosity info from pc2012" << endl;
		file.open("/pc2012-data1/sam/VBF_Ztt/HIGG8D1/LepUniv_xsec.csv");
	}
	getline(file, Line, '\n');  //Get a new line

	while(!file.eof()){  // While not at the end of the file
		getline(file,Line);  // Get a new line

		// increment the counter if the counter is active
		if(counterActive) matchPos++;

		// if the ID finds a match for line number, deactivate the counter
		if( Line.substr(0,6) == ID ) counterActive = false;
	}

	file.close();

	ifstream file2;

	if (pcname == "higgs") {
		file2.open("/higgs-data3/sam/forTomRyunAliceLuca/v02/LepUniv_xsec.csv");
	} else if (pcname == "pc2012") {
		file2.open("/pc2012-data1/sam/VBF_Ztt/HIGG8D1/LepUniv_xsec.csv");
	} else if (pcname == "pc2014") {
		file2.open("/pc2014-data4/sam/VBF_Ztt/HIGG8D1/LepUniv_xsec.csv");
	}

	// get lines from the file until it reaches the line with the matched ID
	for(int i = 0; i < matchPos; i++) getline(file2, Line);

	double SampleID;
	double xsectioninpb;
	double kfactor;
	double filterefficiency;
	double xsecunc;

	// get the sample ID from the file
	getline(file2, Line, ',');
	SampleID = stod(Line);
	info.push_back(SampleID);

	// get the cross section in picobarns from the file
	getline(file2, Line, ',');
	getline(file2, Line, ',');
	xsectioninpb = stod(Line);
	info.push_back(xsectioninpb);

	// get the k factor from the file
	getline(file2, Line, ',');
	kfactor = stod(Line);
	info.push_back(kfactor);

	// get the filter efficiency from the file
	getline(file2, Line, ',');
	filterefficiency = stod(Line);
	info.push_back(filterefficiency);

	// get the cross section 'unc' from the file
	///NO IDEA WHAT THIS IS
	getline(file2, Line, '\n');
	xsecunc = stod(Line);
	info.push_back(xsecunc);

	return info;

}

// Luminosity weighting function
// extra weight to apply is xs*L/N
// N=initial # of generated MC events, luminosity is luminosity of detector
// for MC scaling)
// so have Lum_weighting = xs * k * eff_filter / N
double luminosity_weighting_function(vector<double> info, double N,
										double luminosity) {

	double xs = info[1];			// Cross section
	double k = info[2];				// Correction on cross section calculation
	double eff_filter = info[3];	// Filtering efficiency
	double extra_weight;

	extra_weight =  luminosity*(xs*k*eff_filter)/N;

	return extra_weight;

}


//If Vector 3 or 4 lies between Vector 1 and Vector 2, with pT greater than 25GeV
bool RapidityIntervalCheck(TLorentzVector *Vector1, TLorentzVector *Vector2,
	 					TLorentzVector *Vector3, TLorentzVector *Vector4) {

	bool rap_int_condition = true;

	// No additional jets with p_T > 25 GeV in rapidity interval between two leading jets
	// First, need to find which leading jet is max and min and assign them these names
	// Define the variables outside
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
	if (minjet <= Vector3->Rapidity() && Vector3->Rapidity() <= maxjet
	 		&& Vector3->Pt() > 25) rap_int_condition = false;

	if (minjet <= Vector4->Rapidity() && Vector4->Rapidity() <= maxjet
	 		&& Vector4->Pt() > 25) rap_int_condition = false;

	return rap_int_condition;

}


void MC_Analysis::SelectionCuts() {
	#include "Headers/VariableExtraction.h"

	//------------------------- PRE-SELECTION CUTS ---------------------------//
	pre_selection_cuts = true;

	if (lep_type == "ElectronTau" or lep_type == "MuonTau"
		or lep_type == "ElectronMuon") {				  // Physical tau events
			bool tau_phi_in_range = TauPhiCheck(lep_0_p4, lep_1_p4,
												met_reco_p4);
			if (not tau_phi_in_range) {
				pre_selection_cuts = false;
			}
	}
	if (lep_1 == 0) pre_selection_cuts = false;		              // Two leptons

	if (ljet_1 == 0) pre_selection_cuts = false;	  // At least two light jets

	double cut_kin_E = 25;									 // lep_pt >= 25 GeV
	if (lep_0_pt < cut_kin_E or lep_1_pt < cut_kin_E) {
		pre_selection_cuts = false;
	}
	if (lep_0_q == lep_1_q) pre_selection_cuts = false;			  // Lepton pair

	double cut_jets_L_pt = 55;							// leading jet at 55 GeV
	if (ljet_0_pt < cut_jets_L_pt) pre_selection_cuts = false;

	double cut_jets_SL_pt = 45;						// Sub-leading jet at 45 GeV
	if (ljet_1_pt < cut_jets_SL_pt) pre_selection_cuts = false;

	if (bjet_0 > 0) pre_selection_cuts = false;		               // No b jets



	// -------------------------- ADDITIONAL CUTS -----------------------------//
	baseline_cuts = true;
	search_cuts = true;
	control_cuts = true;
	high_mass_cuts = true;

	if (pre_selection_cuts) {

		// dilepton transverse momentum > 20 GeV
		double cut_pt_ll = 20;
		double pt_ll = ((*lep_0_p4) + (*lep_1_p4)).Pt();
		if (pt_ll < cut_pt_ll) {
			baseline_cuts = false;
			search_cuts = false;
			control_cuts = false;
			high_mass_cuts = false;
		}

		// inv mass of leading jets
		double cut_jet_inv_mass = 250;			// Baseline, Search, Control
		double cut_jet_inv_mass_HM = 1500;		// High-Mass
		if (InvariantMass(ljet_0_p4, ljet_1_p4) < cut_jet_inv_mass) {
			baseline_cuts = false;
			search_cuts = false;
			control_cuts = false;
		}
		if (InvariantMass(ljet_0_p4, ljet_1_p4) < cut_jet_inv_mass_HM) {
			high_mass_cuts = false;
		}

		// number of interval jets
		bool rap_int_condition = RapidityIntervalCheck(ljet_0_p4, ljet_1_p4,
														ljet_2_p4, ljet_3_p4);
		if (rap_int_condition) control_cuts = false;
		else {
			baseline_cuts = false;
			search_cuts = false;
			high_mass_cuts = false;
		}

		event_type();
		if (lep_type == "Electron" or lep_type == "Muon") {

				double lep_inv_mass = InvariantMass(lep_0_p4, lep_1_p4);
				if (lep_inv_mass < 81 or lep_inv_mass > 101) {
					baseline_cuts = false;
					search_cuts = false;
					control_cuts = false;
					high_mass_cuts = false;
				}

				double pt_balance = PtBalance(lep_0_p4, lep_1_p4,
												ljet_0_p4, ljet_1_p4);

				if (pt_balance >= 0.16) {
					baseline_cuts = false;
					search_cuts = false;
					high_mass_cuts = false;
				}
				double pt_balance_3 = PtBalance3(lep_0_p4, lep_1_p4,
												ljet_0_p4, ljet_1_p4, ljet_2_p4);
				if (pt_balance_3 >= 0.16) {
					control_cuts = false;
				}
		}

		if (lep_type == "ElectronTau" or lep_type == "MuonTau"
		 	or lep_type == "ElectronMuon") {

				double lep_inv_mass = InvariantMass(lep_0_p4, lep_1_p4);
				if (lep_inv_mass < 101 or lep_inv_mass > 81) {
					baseline_cuts = false;
					search_cuts = false;
					control_cuts = false;
					high_mass_cuts = false;
				}

				double centrality = Centrality(lep_0_p4, lep_1_p4,
												ljet_0_p4, ljet_1_p4);
				if (centrality < -1.92 or centrality > 1.92) {
					baseline_cuts = false;
					search_cuts = false;
					control_cuts = false;
					high_mass_cuts = false;
				}

				double t_delta_phi = DeltaPhi(lep_0_p4, lep_1_p4);
				if (t_delta_phi >= 2.2) {
					baseline_cuts = false;
					search_cuts = false;
					control_cuts = false;
					high_mass_cuts = false;
				}
		}
	}


}



# endif
