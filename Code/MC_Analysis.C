#define MC_Analysis_cxx
#include "Headers/MC_Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <chrono>

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

		// Loading Percentages //
		prog = (load / nentries)*10;
		prog_int = (int)round(prog);
		if (prog_int != last_prog) {
			cout << prog_int*10-10 << "%" << endl;
			last_prog = prog_int;
		}

		ParticleSelection();		// Selects lep_ variables
		event_type();				// Sets lep_type

		// extracts kinematic variables from 4-vectors
		#include "Headers/VariableExtraction.h"



		// Apply selection cuts & fill
		bool event_pair = event_pair_truth();			// Pre-selection cut
		bool passed_cuts = initial_cuts_truth();		// Selection cut

		if (event_pair == true) {
			if (passed_cuts == true){

				// --------------------- INVARIANT MASS --------------------- //
				double dilep_inv_mass = InvariantMass(lep_0_p4, lep_1_p4);
				if (lep_type == "Electron") {
					h_elec_inv_mass->Fill(dilep_inv_mass);
				} if (lep_type == "Muon") {
					h_muon_inv_mass->Fill(dilep_inv_mass);
				} if (lep_type == "Tau") {
					h_tau_inv_mass->Fill(dilep_inv_mass);
				} if (lep_type == "ElectronMuon") {
					h_elec_muon_inv_mass->Fill(dilep_inv_mass);
				} if (lep_type == "MuonTau") {
					h_muon_tau_inv_mass->Fill(dilep_inv_mass);
				} if (lep_type == "ElectronTau") {
					h_elec_tau_inv_mass->Fill(dilep_inv_mass);
				}
				h_ljet_inv_mass->Fill(InvariantMass(ljet_0_p4, ljet_1_p4));
				h_bjet_inv_mass->Fill(InvariantMass(bjet_0_p4, bjet_1_p4));


				// ------------------------ CONES ----------------------------//
				h_elec_iso_etcone20->Fill(elec_0_iso_etcone20);
				h_muon_iso_etcone20->Fill(muon_0_iso_etcone20);

				h_elec_iso_ptcone30->Fill(elec_0_iso_ptcone30);
				h_muon_iso_ptcone30->Fill(muon_0_iso_ptcone30);

				// ---------------------- KINEMATICS ------------------------ //
				h_lep_0_pt->Fill(lep_0_pt);						// Leptons
				h_lep_0_phi->Fill(lep_0_phi);
				h_lep_0_eta->Fill(lep_0_eta);
				h_lep_rapidity->Fill(lep_0_p4->Rapidity());
				h_lep_1_pt->Fill(lep_1_pt);
				h_lep_1_phi->Fill(lep_1_phi);
				h_lep_1_eta->Fill(lep_1_eta);
				h_lep_rapidity->Fill(lep_1_p4->Rapidity());
				double pt_balance = PtBalance(lep_0_p4, lep_1_p4,
					 							ljet_0_p4, ljet_1_p4);
				h_lep_pt_bal->Fill(pt_balance);

				h_ljet_0_pt->Fill(ljet_0_pt);					// Light Jets
				h_ljet_0_eta->Fill(ljet_0_eta);
				h_ljet_0_phi->Fill(ljet_0_phi);
				h_ljet_1_pt->Fill(ljet_1_pt);
				h_ljet_1_eta->Fill(ljet_1_eta);
				h_ljet_1_phi->Fill(ljet_1_phi);

				h_bjet_0_pt->Fill(bjet_0_pt);					// b Jets
				h_bjet_0_eta->Fill(bjet_0_eta);
				h_bjet_0_phi->Fill(bjet_0_phi);

				h_lep_eta_sum->Fill(lep_0_eta + lep_1_eta);
				h_ljet_eta_sum->Fill(ljet_0_eta + ljet_1_eta);

				// angular separation
				h_ljet_delta_eta->Fill(ljet_0_eta - ljet_1_eta);
				h_lep_delta_eta->Fill(lep_0_eta - lep_1_eta);
				h_ljet_delta_phi->Fill(ljet_0_phi - ljet_1_phi);
				h_lep_delta_phi->Fill(lep_0_phi - lep_1_phi);
				h_ljet_delta_R->Fill(DeltaR(ljet_0_p4,ljet_1_p4));
				h_lep_delta_R->Fill(DeltaR(lep_0_p4,lep_1_p4));

				// ------------------------- JETS --------------------------- //
				h_n_jets->Fill(n_jets);

				if (ljet_2) {
				h_ljet_2_eta->Fill(ljet_2_eta);
				h_ljet_2_phi->Fill(ljet_2_phi);
				h_ljet_delta_eta_2->Fill(ljet_1_eta - ljet_2_eta);
				}
				if (ljet_3) {
				h_ljet_3_eta->Fill(ljet_3_eta);
				h_ljet_3_phi->Fill(ljet_3_phi);
				h_ljet_delta_eta_3->Fill(ljet_2_eta - ljet_3_eta);
				}

				h_lep_eta_L_SL->Fill(lep_0_eta, lep_1_eta);
				h_ljet_eta_L_SL->Fill(ljet_0_eta, ljet_1_eta);

				if (n_jets == 2) {
					h_ljet_0_eta_2jets->Fill(ljet_0_eta);
					h_ljet_1_eta_2jets->Fill(ljet_1_eta);
				}
				if (n_jets == 3) {
					h_ljet_0_eta_3jets->Fill(ljet_0_eta);
					h_ljet_1_eta_3jets->Fill(ljet_1_eta);
					h_ljet_2_eta_3jets->Fill(ljet_2_eta);
				}
				if (n_jets == 4) {
					h_ljet_0_eta_4jets->Fill(ljet_0_eta);
					h_ljet_1_eta_4jets->Fill(ljet_1_eta);
					h_ljet_2_eta_4jets->Fill(ljet_2_eta);
					h_ljet_3_eta_4jets->Fill(ljet_3_eta);
				}
				if (n_jets == 5) {
					h_ljet_0_eta_5jets->Fill(ljet_0_eta);
					h_ljet_1_eta_5jets->Fill(ljet_1_eta);
					h_ljet_2_eta_5jets->Fill(ljet_2_eta);
					h_ljet_3_eta_5jets->Fill(ljet_3_eta);
				}

				// ----------------------- Z BOSON -------------------------- //
				double Z_cent = Centrality(lep_0_p4, lep_1_p4,
											ljet_0_p4, ljet_1_p4);
				h_Z_cent->Fill(Z_cent);


			}
			// NO Cuts
			// --------------------- INVARIANT MASS --------------------- //
			double dilep_inv_mass_NoCut = InvariantMass(lep_0_p4, lep_1_p4);
			if (lep_type == "Electron") {
				h_elec_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			} if (lep_type == "Muon") {
				h_muon_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			} if (lep_type == "Tau") {
				h_tau_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			} if (lep_type == "ElectronMuon") {
				h_elec_muon_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			} if (lep_type == "MuonTau") {
				h_muon_tau_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			} if (lep_type == "ElectronTau") {
				h_elec_tau_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			}
			// ------------------------ CONES ----------------------------//
			h_elec_iso_etcone20->Fill(elec_0_iso_etcone20);
			h_muon_iso_etcone20->Fill(muon_0_iso_etcone20);

			h_elec_iso_ptcone30->Fill(elec_0_iso_ptcone30);
			h_muon_iso_ptcone30->Fill(muon_0_iso_ptcone30);

			h_ljet_inv_mass->Fill(InvariantMass(ljet_0_p4, ljet_1_p4));
			h_bjet_inv_mass->Fill(InvariantMass(bjet_0_p4, bjet_1_p4));

			// ----------------------- Z BOSON -------------------------- //
			double Z_cent_NoCut = Centrality(lep_0_p4, lep_1_p4,
				 								ljet_0_p4, ljet_1_p4);
			h_Z_cent_NoCut->Fill(Z_cent_NoCut);

			// ---------------------- KINEMATICS ------------------------ //
			h_ljet_delta_eta_NoCut->Fill(ljet_0_eta - ljet_1_eta);
			h_lep_delta_eta_NoCut->Fill(lep_0_eta - lep_1_eta);
			h_ljet_delta_phi_NoCut->Fill(ljet_0_phi - ljet_1_phi);
			h_lep_delta_phi_NoCut->Fill(lep_0_phi - lep_1_phi);
			h_ljet_delta_R_NoCut->Fill(DeltaR(ljet_0_p4,ljet_1_p4));
			h_lep_delta_R_NoCut->Fill(DeltaR(lep_0_p4,lep_1_p4));

			int lep_n;
			h_lep_n->Fill(lep_n);
		}




	}
	// ---------------------- HISTOGRAM STYLE --------------------------- //
	h_elec_inv_mass->SetLineColor(4);
	h_elec_inv_mass_NoCut->SetLineColor(3);

	h_lep_eta_L_SL->GetXaxis()->SetTitle("Leading");
	h_lep_eta_L_SL->GetYaxis()->SetTitle("Sub-leading");
	h_ljet_eta_L_SL->GetXaxis()->SetTitle("Leading");
	h_ljet_eta_L_SL->GetYaxis()->SetTitle("Sub-leading");


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
