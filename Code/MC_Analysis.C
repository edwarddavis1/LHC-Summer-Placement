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
		
		#include "Headers/VariableExtraction.h"	// Extracts pt,eta,phi from 4-vectors
		
		h_lep_pt->Fill(lep_0_pt);
		h_lep_phi->Fill(lep_0_phi);
		h_lep_eta->Fill(lep_0_eta);
		
		h_elec_pt->Fill(elec_0_pt);
		h_elec_phi->Fill(elec_0_phi);
		h_elec_eta->Fill(elec_0_eta);

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
				
				h_elec_iso_etcone20->Fill(elec_0_iso_etcone20);
				h_muon_iso_etcone20->Fill(muon_0_iso_etcone20);

				h_elec_iso_ptcone30->Fill(elec_0_iso_ptcone30);
				h_muon_iso_ptcone30->Fill(muon_0_iso_ptcone30);
				
				h_ljet_inv_mass->Fill(InvariantMass(ljet_0_p4, ljet_1_p4));
				h_bjet_inv_mass->Fill(InvariantMass(bjet_0_p4, bjet_1_p4));
				
				double Z_cent = Centrality(lep_0_p4, lep_1_p4, ljet_0_p4, ljet_1_p4);
				h_Z_cent->Fill(Z_cent);

			}
			double dilep_inv_mass_NoCut = InvariantMass(lep_0_p4, lep_1_p4);			
			if (lep_type == "Electron") h_elec_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			if (lep_type == "Muon") h_muon_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			if (lep_type == "Tau") h_tau_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			if (lep_type == "ElectronMuon") h_elec_muon_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			if (lep_type == "MuonTau") h_muon_tau_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			if (lep_type == "ElectronTau") h_elec_tau_inv_mass_NoCut->Fill(dilep_inv_mass_NoCut);
			
			h_elec_iso_etcone20->Fill(elec_0_iso_etcone20);
			h_muon_iso_etcone20->Fill(muon_0_iso_etcone20);

			h_elec_iso_ptcone30->Fill(elec_0_iso_ptcone30);
			h_muon_iso_ptcone30->Fill(muon_0_iso_ptcone30);
			
			h_ljet_inv_mass->Fill(InvariantMass(ljet_0_p4, ljet_1_p4));
			h_bjet_inv_mass->Fill(InvariantMass(bjet_0_p4, bjet_1_p4));
			
			double Z_cent_NoCut = Centrality(lep_0_p4, lep_1_p4, ljet_0_p4, ljet_1_p4);
			h_Z_cent_NoCut->Fill(Z_cent_NoCut);

			
		}
		int lep_n;
		h_lep_n->Fill(lep_n);
		
		h_n_jets->Fill(n_jets);
		
		h_ljet_0_pt->Fill(ljet_0_pt);
		h_ljet_0_eta->Fill(ljet_0_eta);
		h_ljet_0_phi->Fill(ljet_0_phi);
		
		h_bjet_0_pt->Fill(bjet_0_pt);
		h_bjet_0_eta->Fill(bjet_0_eta);
		h_bjet_0_phi->Fill(bjet_0_phi);
		
		h_elec_inv_mass->SetLineColor(4);
		h_elec_inv_mass_NoCut->SetLineColor(3);


	}

	// Create file to write histograms
	TFile outfile("outfile.root","RECREATE");
	#include "Headers/WriteHistos.h"
	outfile.Close();

	cout << "Done!" << endl;
	
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
