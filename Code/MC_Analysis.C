#define MC_Analysis_cxx
#include "Headers/MC_Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <chrono>
#include "Headers/Get_N_pc2014.h"
#include "Headers/Get_N_higgs.h"
#include "Headers/Get_N_pc2012.h"

// Used to measure the elapsed time
auto start = chrono::steady_clock::now();


// For Loading percentages
float prog, load;
int prog_int, last_prog=0;
int cut_entries=0;


void MC_Analysis::Loop()
{

	// if the chain is empty, end the loop
	if (fChain == 0) return;

	// get the number of entries
	Long64_t nentries = fChain->GetEntriesFast();
	// set number of bytes to zero
	Long64_t nbytes = 0, nb = 0;

	//------------------------ ANALYSIS PRELIMINARIES ------------------------//
	string pcname = PCName();
	bool higgs;
	if (pcname == "higgs") higgs = true;
	string chain_name = ChainName();
	cout << chain_name << endl;
	int colour = GetColour();
	cout << colour << endl;
	string data_path = DataPath();
	double N = GetN(data_path);
	double luminosity = GetLuminosity();
	string ID = GetID();
	vector <double> info = csv_reader(ID);
	double lum_weight = luminosity_weighting_function(info, N, luminosity);

	////////////////////////////////////////////////////////////////////////////
	//--------------------------- Book Hists here ----------------------------//
	////////////////////////////////////////////////////////////////////////////
	#include "Headers/BookHistos.h"

	////////////////////////////////////////////////////////////////////////////
	///---------------------- FOR LOOP USED IN ANALYSIS ---------------------///
	////////////////////////////////////////////////////////////////////////////

	for (Long64_t jentry=0; jentry<nentries;jentry++ and load++) {

		////////////////////////////////////////////////////////////////////////
		///--------------------- DATA EXISTANCE CHECKS ----------------------///
		////////////////////////////////////////////////////////////////////////

		// load the entry in the tree with number jentry
		Long64_t ientry = LoadTree(jentry);
		// if there is no entry, break the loop
		if (ientry < 0) break;
		// add the position in bytes to nbytes
		nb = fChain->GetEntry(jentry);   nbytes += nb;

		////////////////////////////////////////////////////////////////////////
		///---------------------------- ANALYSIS ----------------------------///
		////////////////////////////////////////////////////////////////////////

		// loading Percentages
		prog = (load / nentries)*10;
		prog_int = (int)round(prog);
		if (prog_int != last_prog) {
			cout << prog_int*10-10 << "%" << endl;
			last_prog = prog_int;
		}

		ParticleSelection();		// Selects lep_ variables
		event_type();				// Sets lep_type

		n_leptons = n_electrons + n_muons + n_taus;

		//------------------- RECONSTRUCTION CALCULATIONS --------------------//

		// Missing transverse momentum centrality
		double MET_Centrality = METCentrality(met_reco_p4, lep_0_p4, lep_1_p4);

		// InorOut = true means the E_t is outside of the phi interval
		// Change these to TLorentzVector as needed for Z boson mass
		// reconstruction
		double Et_along_0;
		double Et_along_1;

		// calculate the lepton mass favour (whether a lepton points more
		// towards the hadronic tau or the leptonic tau
		double MET_Type_Favour = METTypeFavour(met_reco_p4, lep_0_p4, lep_1_p4);

		//Vector which cintains the neutrino transverse momentum vectors
		vector<double> neutrino_momenta;

		// Stores the momenta of the neutrinos pointed along lepton 0 and
		// lepton 1
		double neutrino_0_x_p, neutrino_0_y_p, neutrino_0_z_p;
		double neutrino_1_x_p, neutrino_1_y_p, neutrino_1_z_p;

		// is the missing energy inside or outside the lepton phi interval?
		bool outside_leptons = PhiIntervalInOrOut(lep_0_p4, lep_1_p4,
													met_reco_p4);

		// if OUTSIDE
		// outside the phi interval so need to see which one it favours
		if (outside_leptons) {

			// want to calcualate which tau it is closer to and find Et
			// component along that tau vector.
			// Closer to lep_0 aka TRUE
			if ( ETFavourCalc( lep_0_p4, lep_1_p4, met_reco_p4 ) ) {

				// Et_along_0 should be TLorentzVector along lep_0
				// Et along a
				Et_along_0 = ETalongVectorCalc(lep_0_p4, met_reco_p4);
				Et_along_1 = 0;

				// neutrino 1
				neutrino_0_x_p = x_component_pT(Et_along_0, lep_0_p4);
				neutrino_0_y_p = y_component_pT(Et_along_0, lep_0_p4);
				neutrino_0_z_p = p_z_neutrino_calc(Et_along_0, lep_0_p4);

				// neutrino 2
				neutrino_1_x_p = 0;
				neutrino_1_y_p = 0;
				neutrino_1_z_p = 0;


			}
			else { // closer to lep_1 aka FALSE
				// Et_along_1 should be TLorentzVector along lep_1
				Et_along_1 = ETalongVectorCalc(lep_1_p4, met_reco_p4);
				Et_along_0 = 0;

				// neutrino 1
				neutrino_0_x_p = 0;
				neutrino_0_y_p = 0;
				neutrino_0_z_p = 0;

				// neutrino 2
				neutrino_1_x_p = x_component_pT(Et_along_1, lep_1_p4);
				neutrino_1_y_p = y_component_pT(Et_along_1, lep_1_p4);
				neutrino_1_z_p = p_z_neutrino_calc(Et_along_1, lep_1_p4);

			}
		}
		// else INSIDE
		else { // normal "inside" the phi interval gap

			// neutrino transverse momentum
			neutrino_momenta = pTneutrinovector_calc(lep_0_p4, lep_1_p4,
														met_reco_p4);
			double neutrino_0_pt = abs(neutrino_momenta[0]);
			double neutrino_1_pt = abs(neutrino_momenta[1]);

			neutrino_0_x_p = x_component_pT(neutrino_0_pt, lep_0_p4);
			neutrino_0_y_p = y_component_pT(neutrino_0_pt, lep_0_p4);
			neutrino_0_z_p = p_z_neutrino_calc(neutrino_0_pt, lep_0_p4);

			neutrino_1_x_p = x_component_pT(neutrino_1_pt, lep_1_p4);
			neutrino_1_y_p = y_component_pT(neutrino_1_pt, lep_1_p4);
			neutrino_1_z_p = p_z_neutrino_calc(neutrino_1_pt, lep_1_p4);

		}
		// TLorentzVector (TLV) 4 momentum px,py,pz,E (E=p_tot) of neutrino 1
		TLorentzVector* neutrino_0_TLV = neutrino_TLV(neutrino_0_x_p,
														neutrino_0_y_p,
														neutrino_0_z_p);
		// TLorentzVector (TLV) 4 momentum px,py,pz,E (E=p_tot) of neutrino 2
		TLorentzVector* neutrino_1_TLV = neutrino_TLV(neutrino_1_x_p,
														neutrino_1_y_p,
														neutrino_1_z_p);

		// reconstruct tau candidate with tau lepton and neutrino
		lep_0_reco_p4 = merge_two_TLV(lep_0_p4, neutrino_0_TLV);
		lep_1_reco_p4 = merge_two_TLV(lep_1_p4, neutrino_1_TLV);

		double lep_inv_mass_reco = InvariantMass(lep_0_reco_p4, lep_1_reco_p4);


		//----------------------- FILLING HISTOGRAMS -------------------------//

		// extracts kinematic variables from 4-vectors
		#include "Headers/VariableExtraction.h"

		// apply selection cuts & fill // You were checking the tau phi cut
		SelectionCuts();
		if (pre_selection_cuts) {
			#include "Headers/PreSelectionHistos.h"
			if (baseline_cuts) {
				#include "Headers/BaselineHistos.h"
			}
			if (search_cuts) {
				#include "Headers/SearchHistos.h"
			}
			if (control_cuts) {
				#include "Headers/ControlHistos.h"
			}
			if (high_mass_cuts) {
				#include "Headers/HighMassHistos.h"
			}
		}




	}
	// ---------------------- HISTOGRAM STYLE --------------------------- //
	#include "Headers/ColourHistos.h"

	h_lep_eta_L_SL_preselect->GetXaxis()->SetTitle("Leading");
	h_lep_eta_L_SL_preselect->GetYaxis()->SetTitle("Sub-leading");
	h_ljet_eta_L_SL_preselect->GetXaxis()->SetTitle("Leading");
	h_ljet_eta_L_SL_preselect->GetYaxis()->SetTitle("Sub-leading");
	h_lep_phi_L_SL_preselect->GetXaxis()->SetTitle("Leading");
	h_lep_phi_L_SL_preselect->GetYaxis()->SetTitle("Sub-leading");
	h_ljet_phi_L_SL_preselect->GetXaxis()->SetTitle("Leading");
	h_ljet_phi_L_SL_preselect->GetYaxis()->SetTitle("Sub-leading");

	TFile outfile("outfile.root","RECREATE");
	#include "Headers/WriteHistos.h"		// Writes all histograms
	outfile.Close();

	cout << "Done!" << endl;

	// End of process time and print total time to terminal and ProcessTimes.txt
	auto end = chrono::steady_clock::now();
	int sec_elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();
	int min_elapsed = sec_elapsed / 60;
	sec_elapsed = sec_elapsed - 60*min_elapsed;
	cout << "Elapsed time: " << min_elapsed << " min " << sec_elapsed <<  " sec" << endl;

	ofstream ProcessTimes_File;
	ProcessTimes_File.open ("ProcessTimes.txt",ios_base::app);
	ProcessTimes_File << min_elapsed << ':' << sec_elapsed;
	ProcessTimes_File.close();
}


//   In a ROOT session, you can do:
//      Root > .L myAnalysis.C
//      Root > myAnalysis t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
