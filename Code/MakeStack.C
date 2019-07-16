#include "Headers/MC_Analysis.h"

void MakeStack() {
	cout << "Making stacks..." << endl;
	
	
	///////////////////////////////////////////////////////////////
	//-------------- Electron inv mass ZeeMV70-140 --------------//
	///////////////////////////////////////////////////////////////
	gROOT->SetBatch(kTRUE);
	TCanvas *c_Zee_MV70_140_elec_inv_mass = new TCanvas("Zee_MV70-140_elec_inv_mass");
	THStack *h_Zee_MV70_140_elec_inv_mass_stack = new THStack("Zee_MV70-140_elec_inv_mass_stack", "Electron Invariant Mass ZeeMV70-140");

	// Read in histograms	
	TFile* Zee_MV70_140_file = new TFile("OutputFiles/Zee_MV70-140.root");
	TH1F* h_Zee_MV70_140_elec_inv_mass = (TH1F*)Zee_MV70_140_file->Get("elec_inv_mass");
	TH1F* h_Zee_MV70_140_elec_inv_mass_NoCuts = (TH1F*)Zee_MV70_140_file->Get("elec_inv_mass_NoCut");
	
	h_Zee_MV70_140_elec_inv_mass->SetFillColorAlpha(kCyan, 0);
	h_Zee_MV70_140_elec_inv_mass->SetFillStyle(3001);
	h_Zee_MV70_140_elec_inv_mass_NoCuts->SetFillColor(kCyan-10);
	h_Zee_MV70_140_elec_inv_mass_NoCuts->SetFillStyle(3003);
	
	h_Zee_MV70_140_elec_inv_mass_stack->Add(h_Zee_MV70_140_elec_inv_mass);
	h_Zee_MV70_140_elec_inv_mass_stack->Add(h_Zee_MV70_140_elec_inv_mass_NoCuts);
	

	h_Zee_MV70_140_elec_inv_mass_stack->Draw();
	h_Zee_MV70_140_elec_inv_mass_stack->GetXaxis()->SetTitle("E (GeV)");
	h_Zee_MV70_140_elec_inv_mass_stack->GetYaxis()->SetTitle("Counts");
	gPad->Modified();
	gPad->Update();
	
	auto l_ZeeMV70_140_elec_inv_mass = new TLegend(0.1,0.8,0.3,0.9);
	l_ZeeMV70_140_elec_inv_mass->AddEntry(h_Zee_MV70_140_elec_inv_mass,"Post Cuts","f");
	l_ZeeMV70_140_elec_inv_mass->AddEntry(h_Zee_MV70_140_elec_inv_mass_NoCuts,"Pre Cuts","f");
	l_ZeeMV70_140_elec_inv_mass->Draw();
	
	gROOT->SetBatch(kFALSE);
	
	///////////////////////////////////////////////////////////////
	//-------------- --Electron inv mass Zee2jets ---------------//
	///////////////////////////////////////////////////////////////
	gROOT->SetBatch(kTRUE);
	TCanvas *c_Zee2jets_elec_inv_mass = new TCanvas("Zee2jets_elec_inv_mass");
	THStack *h_Zee2jets_elec_inv_mass_stack = new THStack("Zee2jets_elec_inv_mass_stack", "Electron Invariant Mass Zee2jets");

	// Read in histograms	
	TFile* Zee2jets_file = new TFile("OutputFiles/Zee2jets_Min_N_TChannel.root");
	TH1F* h_Zee2jets_elec_inv_mass = (TH1F*)Zee2jets_file->Get("elec_inv_mass");
	TH1F* h_Zee2jets_elec_inv_mass_NoCuts = (TH1F*)Zee2jets_file->Get("elec_inv_mass_NoCut");
	
	h_Zee2jets_elec_inv_mass->SetFillColorAlpha(kCyan, 0);
	h_Zee2jets_elec_inv_mass->SetFillStyle(3001);
	h_Zee2jets_elec_inv_mass_NoCuts->SetFillColor(kCyan-10);
	h_Zee2jets_elec_inv_mass_NoCuts->SetFillStyle(3003);
	
	h_Zee2jets_elec_inv_mass_stack->Add(h_Zee2jets_elec_inv_mass);
	h_Zee2jets_elec_inv_mass_stack->Add(h_Zee2jets_elec_inv_mass_NoCuts);
	
	
	h_Zee2jets_elec_inv_mass_stack->Draw();
	h_Zee2jets_elec_inv_mass_stack->GetXaxis()->SetTitle("E (GeV)");
	h_Zee2jets_elec_inv_mass_stack->GetYaxis()->SetTitle("Counts");
	gPad->Modified();
	gPad->Update();
	
	auto l_Zee2jets_elec_inv_mass = new TLegend(0.1,0.8,0.3,0.9);
	l_Zee2jets_elec_inv_mass->AddEntry(h_Zee2jets_elec_inv_mass,"Post Cuts","f");
	l_Zee2jets_elec_inv_mass->AddEntry(h_Zee2jets_elec_inv_mass_NoCuts,"Pre Cuts","f");
	l_Zee2jets_elec_inv_mass->Draw();
	
	gROOT->SetBatch(kFALSE);
	
	///////////////////////////////////////////////////////////////
	//----------------- Z Centrality (Zmm2jets) -----------------//
	///////////////////////////////////////////////////////////////
	gROOT->SetBatch(kTRUE);
	TCanvas *c_Z_cent = new TCanvas("Z_cent");
	THStack *h_Z_cent_stack = new THStack("Z_cent_stack","");

	// Read in histograms	
	TFile* Z_cent_file = new TFile("OutputFiles/Zmm2jets_Min_N_TChannel.root");
	TH1F* h_Z_cent = (TH1F*)Z_cent_file->Get("Z_cent");
	TH1F* h_Z_cent_NoCuts = (TH1F*)Z_cent_file->Get("Z_cent_NoCut");
	
	h_Z_cent->SetFillColor(kCyan);
	h_Z_cent->SetFillStyle(3001);
	h_Z_cent_NoCuts->SetFillColor(kCyan-10);
	h_Z_cent_NoCuts->SetFillStyle(3003);
	
	h_Z_cent_stack->Add(h_Z_cent);
	h_Z_cent_stack->Add(h_Z_cent_NoCuts);
	
	
	h_Z_cent_stack->Draw();
	h_Z_cent_stack->GetXaxis()->SetTitle("Centrality");
	h_Z_cent_stack->GetYaxis()->SetTitle("Counts");
	gPad->Modified();
	gPad->Update();
	
	auto l_Z_cent = new TLegend(0.8,0.8,0.95,0.95);
	l_Z_cent->AddEntry(h_Z_cent,"Post Cuts","f");
	l_Z_cent->AddEntry(h_Z_cent_NoCuts,"Pre Cuts","f");
	l_Z_cent->SetHeader("Z Boson Centrality (Zmm2jets)","C"); // option "C" allows to center the header
	l_Z_cent->SetTextSize(0.02);
	l_Z_cent->Draw();
	
	
	

	TFile outfile("OutputFiles/StackedHists.root","RECREATE");
	c_Zee_MV70_140_elec_inv_mass->Write();
	c_Zee2jets_elec_inv_mass->Write();
	c_Z_cent->Write();
	outfile.Close();
	
	gROOT->SetBatch(kFALSE);
	cout << "Stacks made!" << endl;
	
}
