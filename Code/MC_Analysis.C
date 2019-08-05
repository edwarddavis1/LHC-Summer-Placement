#define MC_Analysis_cxx
#include "Headers/MC_Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <chrono>
#include "Headers/Get_N_pc2014.h"
#include "Headers/Get_N_higgs.h"
#include "Headers/Get_N_pc2012.h"
#include "Headers/Get_N_pc2014_v2.h"

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

	//--------------------------- POKING SECTION -----------------------------//
	string dataset = DataSet();
	string pcname = PCName();
	string data_name = DataFullName();
	double N = 0;
	double luminosity;
	if (pcname == "pc2014" or pcname == "pc2012") {
		N = GetN(dataset);
		luminosity = 36236.9;
	}
	// STILL NEED TO MAKE HIGGS WORK 

	// else if (pcname == "higgs") {
	// 	N = GetN_higgs(dataset);
	// 	if (data_name.find("r9364") != string::npos) {
	// 		luminosity = 36236.9;
	// 	}
	// 	else if (data_name.find("r10201") != string::npos) {
	// 		luminosity = 43587.3;
	// 	}
	// 	else cout << "FAILED" << endl;
	// }
	string ID = GetID();
	vector <double> info = csv_reader(ID);
	double lum_weight = luminosity_weighting_function(info, N, luminosity);
	// return;
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

		ParticleSelection();			// Selects lep_ variables
		event_type();					// Sets lep_type
		n_leptons = n_electrons + n_muons + n_taus;

		//--------------------------- WEIGHTING ------------------------------//
		// vector<double> info = csv_reader(ID);
		// double lum_weight = luminosity_weighting_function(info,
		// 										);

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
	h_elec_inv_mass->SetLineColor(4);
	h_elec_inv_mass_preselect->SetLineColor(3);

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
