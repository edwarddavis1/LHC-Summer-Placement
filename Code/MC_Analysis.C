#define MC_Analysis_cxx
#include "Headers/MC_Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

// For Loading percentages
float prog, load;
int prog_int, last_prog=0;


void MC_Analysis::Loop()
{
	if (fChain == 0) return;			// If the chain is empty, end the loop

	Long64_t nentries = fChain->GetEntriesFast();	// Get the number of entries
	Long64_t nbytes = 0, nb = 0;			// Set number of bytes to zero


	/////////////////////////////////////////////////////////////////////////////////
	//------------------------------ Book Hists here ------------------------------//
	/////////////////////////////////////////////////////////////////////////////////
	#include "Headers/BookHistos.h"

	/////////////////////////////////////////////////////////////////////
	///------------------ FOR LOOP USED IN ANALYSIS ------------------///
	/////////////////////////////////////////////////////////////////////

	for (Long64_t jentry=0; jentry<nentries;jentry++ and load++) {
		
		/////////////////////////////////////////////////////////////////////
		///-------------------- DATA EXISTANCE CHECKS --------------------///
		/////////////////////////////////////////////////////////////////////

		Long64_t ientry = LoadTree(jentry);		// Load the entry in the tree with number jentry
		if (ientry < 0) break;				// If there is no entry, break the loop
		nb = fChain->GetEntry(jentry);   nbytes += nb;	// Add the position in bytes to nbytes 
		
		//////////////////////////////////////////////////////////////////////		
		///--------------------------- ANALYSIS ---------------------------///
		//////////////////////////////////////////////////////////////////////

		// Loading Percentages //
		prog = (load / nentries)*10;
		prog_int = (int)round(prog);
		if (prog_int != last_prog) {
			cout << prog_int*10-10 << "%" << endl;	
			last_prog = prog_int;
		}

		// Selects the lepton in the event and loads the data in to the lep_ variables
		ParticleSelection();
		event_type();
		
		double lep_0_pt = lep_0_p4->Pt();
		double lep_1_pt = lep_1_p4->Pt();

		// Apply selection cuts & fill
		bool event_pair = event_pair_truth();		// True if event has lepton-antilepton pair		
		bool passed_cuts = initial_cuts_truth();	// True if selection cuts are passed

		if (event_pair == true) {
			if (passed_cuts == true){	
				double dilep_inv_mass = InvariantMass(lep_0_p4, lep_1_p4);			
				if (lep_type == "Electron") h_elec_inv_mass->Fill(dilep_inv_mass);
				if (lep_type == "Muon") h_muon_inv_mass->Fill(dilep_inv_mass);
				if (lep_type == "Tau") h_tau_inv_mass->Fill(dilep_inv_mass);
				if (lep_type == "ElectronMuon") h_elec_muon_inv_mass->Fill(dilep_inv_mass);
				if (lep_type == "MuonTau") h_muon_tau_inv_mass->Fill(dilep_inv_mass);
				if (lep_type == "ElectronTau") h_elec_tau_inv_mass->Fill(dilep_inv_mass);
				/*
				h_elec_iso_etcone20->Fill(elec_0_iso_etcone20);
				h_muon_iso_etcone20->Fill(muon_0_iso_etcone20);

				h_elec_iso_ptcone30->Fill(elec_0_iso_ptcone30);
				h_muon_iso_ptcone30->Fill(muon_0_iso_ptcone30);
				*/
				h_ljet_inv_mass->Fill(InvariantMass(ljet_0_p4, ljet_1_p4));
				h_bjet_inv_mass->Fill(InvariantMass(bjet_0_p4, bjet_1_p4));

			}
			else {
				double dilep_inv_mass_FC = InvariantMass(lep_0_p4, lep_1_p4);							
				if (lep_type == "Electron") h_elec_inv_mass_FC->Fill(dilep_inv_mass_FC);
				if (lep_type == "Muon") h_muon_inv_mass_FC->Fill(dilep_inv_mass_FC);
				if (lep_type == "Tau") h_tau_inv_mass_FC->Fill(dilep_inv_mass_FC);
				if (lep_type == "ElectronMuon") h_elec_muon_inv_mass_FC->Fill(dilep_inv_mass_FC);
				if (lep_type == "MuonTau") h_muon_tau_inv_mass_FC->Fill(dilep_inv_mass_FC);
				if (lep_type == "ElectronTau") h_elec_tau_inv_mass_FC->Fill(dilep_inv_mass_FC);
/*
				h_elec_iso_etcone20_FC->Fill(elec_0_iso_etcone20);
				h_muon_iso_etcone20_FC->Fill(muon_0_iso_etcone20);

				h_elec_iso_ptcone30_FC->Fill(elec_0_iso_ptcone30);
				h_muon_iso_ptcone30_FC->Fill(muon_0_iso_ptcone30);
*/
				h_ljet_inv_mass_FC->Fill(InvariantMass(ljet_0_p4, ljet_1_p4));
				h_bjet_inv_mass_FC->Fill(InvariantMass(bjet_0_p4, bjet_1_p4));

			}
		}
		int lep_n;
		h_lep_n->Fill(lep_n);
	
		
		// Jets
		h_n_jets->Fill(n_jets);
		
		h_ljet_0_pt->Fill(ljet_0_p4->Pt());
		h_ljet_0_eta->Fill(ljet_0_p4->Eta());
		h_ljet_0_phi->Fill(ljet_0_p4->Phi());
		
		h_bjet_0_pt->Fill(bjet_0_p4->Pt());
		h_bjet_0_eta->Fill(bjet_0_p4->Eta());
		h_bjet_0_phi->Fill(bjet_0_p4->Phi());


	}
	
	// Set style for histograms //
	/*h_elec_pt->SetLineColor(8);			// pT
	h_elec_pt->GetXaxis()->SetTitle("pT (GeV)");
	h_elec_pt->GetYaxis()->SetTitle("Counts");
	
	h_muon_pt->SetLineColor(8);
	h_muon_pt->GetXaxis()->SetTitle("pT (GeV)");
	h_muon_pt->GetYaxis()->SetTitle("Counts");

	h_tau_pt->SetLineColor(8);
	h_tau_pt->GetXaxis()->SetTitle("pT (GeV)");
	h_tau_pt->GetYaxis()->SetTitle("Counts");*/

	// Create file to write histograms	
	TFile outfile(TString::Format("%s.root",choice.c_str()),"RECREATE");

	h_lep_n->Write();
/*
	h_lep_type->Write();

	h_elec_pt->Write();
	h_muon_pt->Write();
	h_tau_pt->Write();
	h_elec_pt_FC->Write();
	h_muon_pt_FC->Write();
	h_tau_pt_FC->Write();
*/
	h_elec_inv_mass->Write();
	h_muon_inv_mass->Write();
	h_tau_inv_mass->Write();
	h_elec_muon_inv_mass->Write();
	h_muon_tau_inv_mass->Write();
	h_elec_tau_inv_mass->Write();
	h_elec_inv_mass_FC->Write();
	h_muon_inv_mass_FC->Write();
	h_tau_inv_mass_FC->Write();
	h_elec_muon_inv_mass_FC->Write();
	h_muon_tau_inv_mass_FC->Write();
	h_elec_tau_inv_mass_FC->Write();

/*	
	h_elec_iso_etcone20->Write();
	h_muon_iso_etcone20->Write();
	h_elec_iso_etcone20_FC->Write();
	h_muon_iso_etcone20_FC->Write();

	h_elec_iso_ptcone30->Write();
	h_muon_iso_ptcone30->Write();
	h_elec_iso_ptcone30_FC->Write();
	h_muon_iso_ptcone30_FC->Write();
*/
	h_n_jets->Write();
	
	h_ljet_0_pt->Write();
	h_ljet_0_eta->Write();
	h_ljet_0_phi->Write();

	h_bjet_0_pt->Write();
	h_bjet_0_eta->Write();
	h_bjet_0_phi->Write();

	h_ljet_inv_mass->Write();
	h_bjet_inv_mass->Write();
	h_ljet_inv_mass_FC->Write();
	h_bjet_inv_mass_FC->Write();

	outfile.Close();


	cout << "Done!" << endl;
	//gROOT->ProcessLine("new TBrowser");
	
	
}


//   In a ROOT sess#define MC_Analysis_cxx
#include "Headers/MC_Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

// For Loading percentages
float prog, load;
int prog_int, last_prog=0;


void MC_Analysis::Loop()
{
	if (fChain == 0) return;			// If the chain is empty, end the loop

	Long64_t nentries = fChain->GetEntriesFast();	// Get the number of entries
	Long64_t nbytes = 0, nb = 0;			// Set number of bytes to zero


	/////////////////////////////////////////////////////////////////////////////////
	//------------------------------ Book Hists here ------------------------------//
	/////////////////////////////////////////////////////////////////////////////////
	#include "Headers/BookHistos.h"

	/////////////////////////////////////////////////////////////////////
	///------------------ FOR LOOP USED IN ANALYSIS ------------------///
	/////////////////////////////////////////////////////////////////////

	for (Long64_t jentry=0; jentry<nentries;jentry++ and load++) {
		
		/////////////////////////////////////////////////////////////////////
		///-------------------- DATA EXISTANCE CHECKS --------------------///
		/////////////////////////////////////////////////////////////////////

		Long64_t ientry = LoadTree(jentry);		// Load the entry in the tree with number jentry
		if (ientry < 0) break;				// If there is no entry, break the loop
		nb = fChain->GetEntry(jentry);   nbytes += nb;	// Add the position in bytes to nbytes 
		
		//////////////////////////////////////////////////////////////////////		
		///--------------------------- ANALYSIS ---------------------------///
		//////////////////////////////////////////////////////////////////////

		// Loading Percentages //
		prog = (load / nentries)*10;
		prog_int = (int)round(prog);
		if (prog_int != last_prog) {
			cout << prog_int*10-10 << "%" << endl;	
			last_prog = prog_int;
		}

		// Selects the lepton in the event and loads the data in to the lep_ variables
		ParticleSelection();
		event_type();
		
		double lep_0_pt = lep_0_p4->Pt();
		double lep_1_pt = lep_1_p4->Pt();

		// Apply selection cuts & fill
		bool event_pair = event_pair_truth();		// True if event has lepton-antilepton pair		
		bool passed_cuts = initial_cuts_truth();	// True if selection cuts are passed

		if (event_pair == true) {
			if (passed_cuts == true){	
				double dilep_inv_mass = InvariantMass(lep_0_p4, lep_1_p4);			
				if (lep_type == "Electron") h_elec_inv_mass->Fill(dilep_inv_mass);
				if (lep_type == "Muon") h_muon_inv_mass->Fill(dilep_inv_mass);
				if (lep_type == "Tau") h_tau_inv_mass->Fill(dilep_inv_mass);
				if (lep_type == "ElectronMuon") h_elec_muon_inv_mass->Fill(dilep_inv_mass);
				if (lep_type == "MuonTau") h_muon_tau_inv_mass->Fill(dilep_inv_mass);
				if (lep_type == "ElectronTau") h_elec_tau_inv_mass->Fill(dilep_inv_mass);
				/*
				h_elec_iso_etcone20->Fill(elec_0_iso_etcone20);
				h_muon_iso_etcone20->Fill(muon_0_iso_etcone20);

				h_elec_iso_ptcone30->Fill(elec_0_iso_ptcone30);
				h_muon_iso_ptcone30->Fill(muon_0_iso_ptcone30);
				*/
				h_ljet_inv_mass->Fill(InvariantMass(ljet_0_p4, ljet_1_p4));
				h_bjet_inv_mass->Fill(InvariantMass(bjet_0_p4, bjet_1_p4));

			}
			else {
				double dilep_inv_mass_FC = InvariantMass(lep_0_p4, lep_1_p4);							
				if (lep_type == "Electron") h_elec_inv_mass_FC->Fill(dilep_inv_mass_FC);
				if (lep_type == "Muon") h_muon_inv_mass_FC->Fill(dilep_inv_mass_FC);
				if (lep_type == "Tau") h_tau_inv_mass_FC->Fill(dilep_inv_mass_FC);
				if (lep_type == "ElectronMuon") h_elec_muon_inv_mass_FC->Fill(dilep_inv_mass_FC);
				if (lep_type == "MuonTau") h_muon_tau_inv_mass_FC->Fill(dilep_inv_mass_FC);
				if (lep_type == "ElectronTau") h_elec_tau_inv_mass_FC->Fill(dilep_inv_mass_FC);
/*
				h_elec_iso_etcone20_FC->Fill(elec_0_iso_etcone20);
				h_muon_iso_etcone20_FC->Fill(muon_0_iso_etcone20);

				h_elec_iso_ptcone30_FC->Fill(elec_0_iso_ptcone30);
				h_muon_iso_ptcone30_FC->Fill(muon_0_iso_ptcone30);
*/
				h_ljet_inv_mass_FC->Fill(InvariantMass(ljet_0_p4, ljet_1_p4));
				h_bjet_inv_mass_FC->Fill(InvariantMass(bjet_0_p4, bjet_1_p4));

			}
		}
		int lep_n;
		h_lep_n->Fill(lep_n);
	
		
		// Jets
		h_n_jets->Fill(n_jets);
		
		h_ljet_0_pt->Fill(ljet_0_p4->Pt());
		h_ljet_0_eta->Fill(ljet_0_p4->Eta());
		h_ljet_0_phi->Fill(ljet_0_p4->Phi());
		
		h_bjet_0_pt->Fill(bjet_0_p4->Pt());
		h_bjet_0_eta->Fill(bjet_0_p4->Eta());
		h_bjet_0_phi->Fill(bjet_0_p4->Phi());


	}
	
	// Set style for histograms //
	/*h_elec_pt->SetLineColor(8);			// pT
	h_elec_pt->GetXaxis()->SetTitle("pT (GeV)");
	h_elec_pt->GetYaxis()->SetTitle("Counts");
	
	h_muon_pt->SetLineColor(8);
	h_muon_pt->GetXaxis()->SetTitle("pT (GeV)");
	h_muon_pt->GetYaxis()->SetTitle("Counts");

	h_tau_pt->SetLineColor(8);
	h_tau_pt->GetXaxis()->SetTitle("pT (GeV)");
	h_tau_pt->GetYaxis()->SetTitle("Counts");*/

	// Create file to write histograms	
	TFile outfile(TString::Format("%s.root",choice.c_str()),"RECREATE");

	h_lep_n->Write();
/*
	h_lep_type->Write();

	h_elec_pt->Write();
	h_muon_pt->Write();
	h_tau_pt->Write();
	h_elec_pt_FC->Write();
	h_muon_pt_FC->Write();
	h_tau_pt_FC->Write();
*/
	h_elec_inv_mass->Write();
	h_muon_inv_mass->Write();
	h_tau_inv_mass->Write();
	h_elec_muon_inv_mass->Write();
	h_muon_tau_inv_mass->Write();
	h_elec_tau_inv_mass->Write();
	h_elec_inv_mass_FC->Write();
	h_muon_inv_mass_FC->Write();
	h_tau_inv_mass_FC->Write();
	h_elec_muon_inv_mass_FC->Write();
	h_muon_tau_inv_mass_FC->Write();
	h_elec_tau_inv_mass_FC->Write();

/*	
	h_elec_iso_etcone20->Write();
	h_muon_iso_etcone20->Write();
	h_elec_iso_etcone20_FC->Write();
	h_muon_iso_etcone20_FC->Write();

	h_elec_iso_ptcone30->Write();
	h_muon_iso_ptcone30->Write();
	h_elec_iso_ptcone30_FC->Write();
	h_muon_iso_ptcone30_FC->Write();
*/
	h_n_jets->Write();
	
	h_ljet_0_pt->Write();
	h_ljet_0_eta->Write();
	h_ljet_0_phi->Write();

	h_bjet_0_pt->Write();
	h_bjet_0_eta->Write();
	h_bjet_0_phi->Write();

	h_ljet_inv_mass->Write();
	h_bjet_inv_mass->Write();
	h_ljet_inv_mass_FC->Write();
	h_bjet_inv_mass_FC->Write();

	outfile.Close();


	cout << "Done!" << endl;
	//gROOT->ProcessLine("new TBrowser");
	
	
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
ion, you can do:
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
