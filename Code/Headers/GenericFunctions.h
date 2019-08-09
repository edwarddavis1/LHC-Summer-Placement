#ifndef Generic_Functions_h
#define Generic_Functions_h

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ------------------------- GENERAL FUNCTIONS ------------------------------//
void MC_Analysis::print_variable() {
	cout << "elec_0_pt from func def: " << elec_0_p4->Pt() << endl;
}

// converts character array to string and returns it
string convertToString(char* a, int size) {
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

bool HiggsTruth() {
    string pcname = PCName();
    bool higgs = false;
    if (pcname == "higgs") higgs = true;
    return higgs;
}

bool pc2014Truth() {
    string pcname = PCName();
    bool pc2014 = false;
    if (pcname == "pc2014") pc2014 = true;
    return pc2014;
}

bool pc2012Truth() {
    string pcname = PCName();
    bool pc2012 = false;
    if (pcname == "pc2012") pc2012 = true;
    return pc2012;
}

// Splits a string between delimeters and either chooses one substring at
// position = pos or can get multiple substrings (as a single string) by
// specifying an end_pos.
// By setting pos = end_pos, the return string is from pos to the end of string
string ChooseSplit(string strToSplit, char delimeter, int pos,
                    int end_pos = 0) {
    stringstream ss(strToSplit);
    string item;
    vector<string> splittedStrings;
    while (getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }

    string chosen_split;
    vector<string> chosen_splits;
    if (end_pos == pos and pos != 0) end_pos = splittedStrings.size();

    if (end_pos == 0) {
        string chosen_split = splittedStrings[pos];
        return chosen_split;
    }
    else {
        for (int i = pos; i < end_pos; i++) {
            if (i == end_pos - 1) {
                chosen_splits.push_back(splittedStrings[i]);
            }
            else chosen_splits.push_back(splittedStrings[i] + "_");
        }
        chosen_split = accumulate(begin(chosen_splits), end(chosen_splits),
                                    chosen_split);
        return chosen_split;
    }

}

// find out which .root file is currently being read
string DataPath() {
	string data_path = gDirectory->GetPath();
	return data_path;
}

// find out which .root file is currently being read
string ChainName() {
    bool higgs = HiggsTruth();
    char dot{'.'};
    char underscore{'_'};
    string long_chain;
    string chain_name;
    string higgs_lum_line;
    string higgs_lum_code;
    string data_path = DataPath();

    if (higgs) {
        long_chain = ChooseSplit(data_path, dot, 6);
        chain_name = ChooseSplit(long_chain, underscore, 2, 2);
        higgs_lum_line = ChooseSplit(data_path, dot, 8);
        higgs_lum_code = ChooseSplit(higgs_lum_line, underscore, 2);
        chain_name += "_" + higgs_lum_code;

    }
    else {
        long_chain = ChooseSplit(data_path, dot, 7);
        chain_name = ChooseSplit(long_chain, underscore, 2, 2);
    }

    return chain_name;
}

int GetColour() {
	string chain_name = ChainName();
	int colour;
	if (chain_name.find("jets") != string::npos) colour = 590;
	else if (chain_name.find("ZqqZll") != string::npos) colour = 806;
	else if (chain_name.find("Wenu") != string::npos) colour = 820;
	else if (chain_name.find("Wmunu") != string::npos) colour = 819;
	else if (chain_name.find("Wtaunu") != string::npos) colour = 827;
	else if (chain_name.find("ttb") != string::npos) colour = 632;
	else if (chain_name.find("llll") != string::npos) colour = 908;
	else if (chain_name.find("lllv") != string::npos) colour = 891;
	else if (chain_name.find("llvv") != string::npos) colour = 906;
	else if (chain_name.find("lvvv") != string::npos) colour = 901;
	else if (chain_name.find("Z") != string::npos) colour = 865;

	return colour;
}

// find out ID of current file
string GetID() {
    bool higgs = HiggsTruth();
    string file_path = gDirectory->GetPath();
	vector<string> file_split;
	char delimeter{'.'};
    string dataset;
    if (higgs) dataset = ChooseSplit(file_path, delimeter, 5);
    else dataset = ChooseSplit(file_path, delimeter, 6);
	return dataset;
}

// This function will return a vector of doubles, containing information
// about luminosity weighting for a given file ID
vector<double> csv_reader(string ID) {

	string line;
	vector <double> info;
    string SampleID_s;
    string xs_s;
	string k_s;
	string e_filter_s;
    double SampleID;
	double xs;
	double k;
	double e_filter;
    vector<string> SampleID_v;

	bool higgs = HiggsTruth();
    bool pc2014 = pc2014Truth();
    bool pc2012 = pc2012Truth();
	ifstream file;

	// get file contianing luminosity information
	if (higgs) {
		file.open("/higgs-data3/sam/forTomRyunAliceLuca/v02/LepUniv_xsec.csv");
	} else if (pc2014) {
		file.open("/pc2014-data4/sam/VBF_Ztt/HIGG8D1/LepUniv_xsec.csv");
	} else if (pc2012) {
		file.open("/pc2012-data1/sam/VBF_Ztt/HIGG8D1/LepUniv_xsec.csv");
	}

    char comma{','};
    bool is_number;
    int i = 0;
    int pos = 0;
    vector<string> lines;
    if (file.is_open()) {
        while(getline(file, line)) {
            // remove large spaces in csv
            line.erase(remove_if(line.begin(), line.end(), ::isspace),
                        line.end());

            // remove lines without data (without a comma in the line)
            if (line.find(",") != string::npos) {
                SampleID_s = ChooseSplit(line, comma, 0);
                if (ID == SampleID_s) {
                    stringstream(SampleID_s)>>SampleID;
                    stringstream(ChooseSplit(line, comma, 2))>>xs;
                    stringstream(ChooseSplit(line, comma, 3))>>k;
                    stringstream(ChooseSplit(line, comma, 4))>>e_filter;
                    break;
                }
            }
        }
    }
    file.close();

    info.push_back(SampleID);
    info.push_back(xs);
    info.push_back(k);
    info.push_back(e_filter);

	return info;

}

double GetLuminosity() {
    bool higgs = HiggsTruth();
    string chain_name = ChainName();
	double luminosity;
	if (higgs) {
		if (chain_name.find("r9364") != string::npos) luminosity = 36236.9;
		else if (chain_name.find("r10201") != string::npos) luminosity = 43587.3;
	}
	else luminosity = 36236.9;

    return luminosity;
}

double GetN(string data_path) {
    bool higgs = HiggsTruth();
    bool pc2014 = pc2014Truth();
    bool pc2012 = pc2012Truth();
    string chain_name = ChainName();

    ifstream N_file;
    if (higgs) N_file.open("N_values_higgs.txt");
    else if (pc2014) N_file.open("N_values_pc2014.txt");
    else if (pc2012) N_file.open("N_values_pc2012.txt");

    string line;
	bool got_match = false;
    double N;
    if (N_file.is_open()) {
        while(getline(N_file, line)) {
            char colon{':'};
            string file_chain = ChooseSplit(line, colon, 0);
            string str_N = ChooseSplit(line, colon, 1);
            if (file_chain == chain_name) {
                N = stod(str_N);
				got_match = true;
            }
        }
        N_file.close();
    } else cout << "failed to open file" << endl;

	if (not got_match) cout << "Failed to get a match for N" << endl;
    return N;
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
	double e_filter = info[3];	    // Filtering efficiency
	double lum_weight;

    cout << "ID: " << info[0] << endl;
    cout << "cross section: " << xs << endl;
    cout << "k factor: " << k << endl;
    cout << "e_filter: " << e_filter << endl;
    cout << "N: " << N << endl;
    cout << "luminosity: " << luminosity << endl;

	lum_weight =  luminosity*(xs*k*e_filter)/N;
    cout << "lum weight: " << lum_weight << endl;
	return lum_weight;

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

// -------------------------- SELECTION CUTS --------------------------------//

double InvariantMass(TLorentzVector *Vector1, TLorentzVector *Vector2) {

	double inv_mass = (*Vector1 + *Vector2).M();
	return inv_mass;
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
							TLorentzVector *met_vector) {
	double Et_along_vector = (met_vector->Dot(*lep_vector))/lep_vector->Pt();
	return Et_along_vector;
}

double non_relative_DeltaPhi(TLorentzVector *Vector1, TLorentzVector *Vector2) {

	double DeltaPhi = Vector1->Phi() - Vector2->Phi();
	return abs(DeltaPhi);

}

// DeltaPhi using dot product
double DeltaPhi(TLorentzVector *Vector1, TLorentzVector *Vector2){
	double a_dot_b = DotProdPt(Vector1, Vector2);
	double denominator = abs(Vector1->Pt()) * abs(Vector2->Pt());
	double final_val = a_dot_b / denominator;

	double delta_phi = acos( final_val ); 		// between tau 1 and 2

	return delta_phi;
}

// decide if Etmiss is favouring the lepton or the hadron
// returns true if lep_a is closer to the missing energy in phi space
bool ETFavourCalc(TLorentzVector *lep_a_vector, TLorentzVector *lep_b_vector,
					TLorentzVector *met_vector){

	double delta_phi_aEt = DeltaPhi(lep_a_vector, met_vector);
	double delta_phi_bEt = DeltaPhi(lep_b_vector, met_vector);
	double delta_phi_ab = DeltaPhi(lep_a_vector, lep_b_vector);

	// closer to b
	if (delta_phi_aEt > delta_phi_bEt){ return false; }

	// otherwise Closer to a
	return true;
}

//-------------------------------- STOLEN ------------------------------------//

// general unit vector calculation
double UnitVector(double p, TLorentzVector *Vector1){
	double px = Vector1->Px();
	double py = Vector1->Py();

	double unitvector = p/pow( pow(px,2) + pow(py,2) ,0.5);

	return unitvector;
}

double METCentrality(TLorentzVector *Vector1, TLorentzVector *Vector2, TLorentzVector *Vector3){// for plotting how close the missing momentum is to the daughter products of the tau
	// function for calculating Centrality for E_T^{miss}

	double Emiss_Phi = Vector1->Phi();
	double tauproduct1_Phi = Vector2->Phi();
	double tauproduct2_Phi = Vector3->Phi();

	double sum1 = Emiss_Phi - (tauproduct1_Phi + tauproduct2_Phi)/2; // sum 1 to break things up

	double Centrality;

	Centrality = 2 * sum1/DeltaPhi(Vector2, Vector3);


	return Centrality;
}

// Function to decide if the Etmiss is inside the Phi interval or outside the phi interval
bool PhiIntervalInOrOut(TLorentzVector *tau_a_p4, TLorentzVector *tau_b_p4,
	 					TLorentzVector *met_p4){

	double delta_phi_aEt = DeltaPhi(tau_a_p4, met_p4);
	double delta_phi_bEt = DeltaPhi(tau_b_p4, met_p4);
	double delta_phi_ab = DeltaPhi(tau_a_p4, tau_b_p4);

	// IF INSIDE THE PHI ANGLE OF TAUS
	if ((delta_phi_aEt + delta_phi_bEt) <= delta_phi_ab + 0.0000001) {
		return false;
	}
	// OTHERWISE OUTSIDE THE PHI ANGLE OF TAUS
	return true;
}

double METTypeFavour(TLorentzVector *Vector1, TLorentzVector *Vector2,
						TLorentzVector *Vector3) {

	double phi_met = Vector1->Phi();
	double phi_had = Vector2->Phi();	// Hadronic Tau
	double phi_lep = Vector3->Phi();	// Lepton
	double favour;

	double delta_phi_lep_met = DeltaPhi(Vector3, Vector1);
	double delta_phi_had_met = DeltaPhi(Vector1, Vector2);
	double delta_phi_lep_had = DeltaPhi(Vector3, Vector2);

	favour = delta_phi_lep_met/delta_phi_lep_had;		// Denoted as omega(?)

	// if "inside" of taus contains the +/- pi discontinuity
	if (abs(non_relative_DeltaPhi(Vector2, Vector3)) > pi) {

		//if the leptonic tau has larger phi
		if (phi_lep > phi_had) {

			// if the missing energy is outside the interval on the leptonic
			// side (smaller than phi_lep)
			if (phi_met < phi_lep && phi_met > 0) favour *= -1;
		}
		// if the leptonic tau has smaller phi
		else {

			// if the missing energy is ouside the interval on the leptonic
			// side (larger than phi_lep)
			if (phi_met > phi_lep && phi_met < 0) favour *= -1;
		}
	}
	// if "inside" of taus DOES NOT contain the +/- pi discontinuity
	else {

		// if the leptonic tau has larger phi
		if (phi_lep > phi_had) {

			// if the missing energy is outside the interval on the leptonic
			// side (larger than phi_lep)
			if (phi_met > phi_lep || (phi_met < phi_lep - (3/2 * pi))) {
				favour *= -1;
			}
		}
		// if the leptonic tau has smaller phi
		else {

			// if the missing energy is ouside the interval on the leptonic
			// side (smaller than phi_lep)
			if (phi_met < phi_lep || (phi_met > phi_lep + (3/2 * pi))) {
				favour *= -1;
			}
		}
	}

	return favour;
}

//Simultaneous equations solved for MET
//Returns a vector containing the transverse momentum of neutrino 1 and 2
vector<double> pTneutrinovector_calc(TLorentzVector *tau_1_p4,
										TLorentzVector *tau_2_p4,
										TLorentzVector *met_p4){

	// a corresponds to tau and neutrino pair 1
	// b corresponds to tau and neutrino pair 2
	// 1 is x direction , 2 is y direction

	// by solving these simultaneous eqns we can get neutrinoa and neutrinob
	// c1 = a1*x + b1*y;
	// c2 = a2*x + b2*y;

	// a1 = unitvector of x component of tau 1, b1 = tau 2
	double a1 = UnitVector(tau_1_p4->Px(), tau_1_p4);
	double b1 = UnitVector(tau_2_p4->Px(), tau_2_p4);
	// a2 = unitvector of y component of tau 2, b2 = tau 2
	double a2 = UnitVector(tau_1_p4->Py(), tau_1_p4);
	double b2 = UnitVector(tau_2_p4->Py(), tau_2_p4);

	// MET data
	double c1 = met_p4->Px(); 		// c1 = total MET in x direction
	double c2 = met_p4->Py(); 		// c2 = total MET in y direction

	double neutrinoa, neutrinob;
	vector<double> pTneutrinovector;

	neutrinoa = (c1*b2 - c2*b1) / (a1*b2 - a2*b1);
	neutrinob = (c1*a2 - c2*a1)/ (b1*a2 - b2*a1);

	//Cramer's Rule
	//Derived in Luca's Book, page marked with I
	//Found on Stack Overflow, "Solving simultanous equations with C++"

	pTneutrinovector.push_back(neutrinoa);
	pTneutrinovector.push_back(neutrinob);

	return pTneutrinovector;
}

double p_z_neutrino_calc(double p_T, TLorentzVector *Vector1){
	double p_z; // to be calculated
	//double p_T; // given by neutrino_0_pt/neutrino_1_pT in Analysis.h
	double theta = Vector1->Theta(); // theta (angle between tau candidate and beam direction

	p_z = p_T/tan(theta); // p_z component of neutrino
	return p_z;
}

double x_component_pT(double p_T, TLorentzVector *Vector1){
	double p_x; // to be calculated
	//double p_T; // given by neutrino_0_pT/neutrino_1_pT in Analysis.h
	double u_x = UnitVector(Vector1->Px(), Vector1); // unit vector in x direction

	p_x = p_T*u_x;
	return p_x; // x momentum component of neutrino_0_pT/neutrino_1_pT
}

double y_component_pT(double p_T, TLorentzVector *Vector1){
	double p_y;// to be calculated
	//double p_T; // given by neutrino_0_pT/neutrino_1_pT in Analysis.h
	double u_y = UnitVector(Vector1->Py(), Vector1); // unit vector in y direction

	p_y = p_T*u_y;
	return p_y; // y momentum component of neutrino_0_pT/neutrino_1_pT
}

TLorentzVector* merge_two_TLV(TLorentzVector *lep_p4,
								TLorentzVector *neutrino_p4){
	double p_x = lep_p4->Px() + neutrino_p4 -> Px();
	double p_y = lep_p4->Py() + neutrino_p4 -> Py();
	double p_z = lep_p4->Pz() + neutrino_p4 -> Pz();
	double Energy = lep_p4->Energy() + neutrino_p4 -> Energy();

	TLorentzVector* merge_two_TLV = new TLorentzVector(p_x, p_y, p_z, Energy);

	return merge_two_TLV;

}

TLorentzVector* neutrino_TLV(double p_x, double p_y, double p_z){ // 4 momentum px,py,pz,E (E=p_tot) of neutrino
	// calculate the total energy of the neutrino (the modulus of total neutrino momentum)
	double p_tot = pow(p_x,2) + pow(p_y,2) + pow(p_z,2);
	double Energy = abs(pow(p_tot,0.5));

	TLorentzVector* neutrino_TLV = new TLorentzVector(p_x, p_y, p_z, Energy);

	return neutrino_TLV;

}

//----------------------------------------------------------------------------//

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

     // Physical tau events
	if (lep_type == "ElectronTau" or lep_type == "MuonTau"
		or lep_type == "ElectronMuon") {
			bool tau_phi_in_range = TauPhiCheck(lep_0_p4, lep_1_p4,
												met_reco_p4);
			if (not tau_phi_in_range) {
				pre_selection_cuts = false;
			}
	}
     // Two leptons
	if (lep_1 == 0) pre_selection_cuts = false;

    // At least two light jets
	if (ljet_1 == 0) pre_selection_cuts = false;

    // lep_pt >= 25 GeV
	double cut_kin_E = 25;
	if (lep_0_pt < cut_kin_E or lep_1_pt < cut_kin_E) {
		pre_selection_cuts = false;
	}
    // Lepton pair
	if (lep_0_q == lep_1_q) pre_selection_cuts = false;

    // leading jet at 55 GeV
	double cut_jets_L_pt = 55;
	if (ljet_0_pt < cut_jets_L_pt) pre_selection_cuts = false;

    // Sub-leading jet at 45 GeV
	double cut_jets_SL_pt = 45;
	if (ljet_1_pt < cut_jets_SL_pt) pre_selection_cuts = false;

     // No b jets
	if (bjet_0 > 0) pre_selection_cuts = false;


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
        double ljet_inv_mass = InvariantMass(ljet_0_p4, ljet_1_p4);
		if (ljet_inv_mass < cut_jet_inv_mass) {
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
