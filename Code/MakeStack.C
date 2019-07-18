#define MakeStack_cxx
#include "Headers/MC_Analysis.h"

void AddStack(TString c_name, TString get_hist, TString files[], int file_length,bool norm_hist=false) {
	TCanvas *c = new TCanvas(c_name);
	THStack *hs = new THStack(c_name+"_stack","");
	auto legend = new TLegend(0.75,0.7,0.99,0.99);
	TString leg_title;
	
	for (UInt_t i=0;i<file_length;i++){
		TFile* file = new TFile("OutputFiles/"+files[i]+".root");
		TH1F* h = (TH1F*)file->Get(get_hist);
		if (norm_hist == true) {
			Double_t norm = h->GetEntries();	// Normalise histogram 
			h->Scale(1/norm);
			h->SetLineColor(i+2);
			leg_title = get_hist+"_norm";
			cout << leg_title << endl;
		}
		else h->SetFillColor(i+2);
		leg_title=get_hist;
		//h->SetFillStyle(3003);
		hs->Add(h);
		legend->AddEntry(h,files[i],"f");
	
	hs->Draw();
	hs->GetXaxis()->SetTitle(get_hist);
	hs->GetYaxis()->SetTitle("Counts");
	gPad->Modified();
	gPad->Update();	
	
	legend->SetHeader(leg_title,"C"); // option "C" allows to center the header
	legend->SetTextSize(0.02);
	legend->Draw();
	}
	
	TFile outfile("OutputFiles/StackedHists.root","UPDATE");
	c->Write("",TObject::kOverwrite);
	outfile.Close();
}



void MakeStack() {
	cout << "Making stacks..." << endl;

	// All Zmumu datasets
	TString files[]={"Zmm2jets_Min_N_TChannel","Zmumu_MV70_140_BFil","Zmumu_MV70_140_CFilBVet","Zmumu_MV70_140_CVetBVet","Zmumu_MV140_280_BFil",
			"Zmumu_MV140_280_CFilBVet","Zmumu_MV140_280_CVetBVet", "Zmumu_MV0_70_BFil","Zmumu_MV0_70_CFilBVet","Zmumu_MV0_70_CVetBVet",
			"Zmumu_MV280_500_BFil","Zmumu_MV280_500_CFilBVet","Zmumu_MV280_500_CVetBVet","Zmumu_MV500_1000","Zmumu_MV1000_E_CMS"};
			
	bool norm_hist=true;
	AddStack("eta_mumu_norm","lep_eta",files,15,norm_hist);
	AddStack("eta_mumu","lep_eta",files,15);
	//AddStack("inv_mass_mumu_norm","muon_inv_mass",files,7,norm_hist);
	//AddStack("inv_mass_mumu_NoCut_norm","muon_inv_mass_NoCut",files,7,norm_hist);
	//AddStack("pt_mumu","lep_pt",files,7);
	cout << "Stacks made!" << endl;
	/*
	TCanvas* eta_diff = new TCanvas("eta_diff");
	auto l1 = new TLegend(0.75,0.8,0.99,0.99);
	
	TFile* file1 = new TFile("OutputFiles/Zmumu_MV140_280_CVetBVet.root");
	TH1F* h1 = (TH1F*)file1->Get("lep_eta");
	TFile* file2 = new TFile("OutputFiles/Zmm2jets_Min_N_TChannel.root");
	TH1F* h2 = (TH1F*)file2->Get("lep_eta");
	
	h1->Add(h2,-1);
	h1->SetFillColor(2);
	h2->SetFillColor(3);
	//h->SetFillStyle(3003);
	l1->AddEntry(h1,"Zmm2jets","f");
	l1->AddEntry(h2,"Zmumu_MV140_280_CVetBVet","f");
	h1->Draw();
	l1->SetHeader("delta eta","C"); // option "C" allows to center the header
	l1->SetTextSize(0.02);
	l1->Draw();
	*/
	
}
