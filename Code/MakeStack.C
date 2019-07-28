#define MakeStack_cxx
#include "Headers/MC_Analysis.h"
#include <iostream>
#include "vector"

void AddStack(TString c_name, TString get_hist, TString files[], int file_length, string MC_type, bool norm_hist=false) {
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
		}
		else h->SetFillColor(i+2);
		leg_title=MC_type+" "+get_hist;
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
	
	TFile outfile(TString::Format("OutputFiles/Stacked_%s.root",MC_type.c_str()),"UPDATE");
	c->Write("",TObject::kOverwrite);
	outfile.Close();
}

void StackCuts(TString c_name, TString get_hists[], TString file_name, int hists_length, string MC_type, bool norm_hist=false) {
	TCanvas *c = new TCanvas(c_name);
	THStack *hs = new THStack(c_name+"_stack","");
	TFile* file = new TFile("OutputFiles/"+file_name+".root");
	auto legend = new TLegend(0.75,0.7,0.99,0.99);
	TString leg_title;
	
	for (UInt_t i=0;i<hists_length;i++){
		TH1F* h;
		h = (TH1F*)file->Get(get_hists[i]);
		h->SetFillColor(i+2);
		leg_title=file_name;
		hs->Add(h);
		legend->AddEntry(h,get_hists[i],"f");
		//h->Reset();
	
	hs->Draw();
	hs->GetYaxis()->SetTitle("Counts");
	gPad->Modified();
	gPad->Update();	
	
	legend->SetHeader(leg_title,"C"); // option "C" allows to center the header
	legend->SetTextSize(0.02);
	legend->Draw();
	}
	
	TFile outfile(TString::Format("OutputFiles/Stacked_%s.root",MC_type.c_str()),"UPDATE");
	c->Write("",TObject::kOverwrite);
	outfile.Close();
}


void PlotSameAxes(TString file_names[],int files_len, TString hists[], int hists_len, string MC_type, TString legend_title) {
	TCanvas *c = new TCanvas(legend_title);
	auto legend = new TLegend(0.75,0.7,0.99,0.99);
	
	
	float temp_min=0, temp_max=0;
	for (UInt_t j=0; j<files_len; j++) {
		TFile* file = new TFile("OutputFiles/"+file_names[j]+".root");	
		for (UInt_t i=0; i<hists_len; i++) {
			TH1F* h = (TH1F*)file->Get(hists[i]);
			if ((i==0) && (j==0)) {
				temp_min = h->GetMinimum();
				temp_max = h->GetMaximum();
			}
			else {
				if (temp_min > h->GetMinimum()) temp_min = h->GetMinimum();
				if (temp_max < h->GetMaximum()) temp_max = h->GetMaximum();
			}
		}
	}
	int colour = 6;
	for (UInt_t j=0; j<files_len; j++) {
		TFile* file = new TFile("OutputFiles/"+file_names[j]+".root");
		for (UInt_t i=0; i<hists_len; i++) {
			TH1F* h = (TH1F*)file->Get(hists[i]);
			h->SetFillColor(colour);
			colour += 1;
			h->SetFillStyle(3001);
			legend->AddEntry(h,file_names[j]+hists[i],"f");
			cout << "Drawing " << file_names[j] << endl;
			if ((i==0) && (j==0)) {
				h->Draw();
				h->SetMaximum(1.2*temp_max);
				h->SetMinimum(temp_min);
			}
			else h->Draw("same");
		}
	}
	legend->SetHeader(legend_title,"C");
	legend->SetTextSize(0.015);
	legend->Draw();
	
	TFile outfile(TString::Format("OutputFiles/SameAxes_%s.root",MC_type.c_str()),"UPDATE");
	c->Write("",TObject::kOverwrite);
	outfile.Close();

}

void MakeStack() {
	//gROOT->SetBatch(kTRUE);
	cout << "Making stacks..." << endl;

	// All Zmumu datasets: 15
	TString Zmm_[]={"Zmm2jets_Min_N_TChannel","Zmumu_MV70_140_BFil","Zmumu_MV70_140_CFilBVet","Zmumu_MV70_140_CVetBVet","Zmumu_MV140_280_BFil",
			"Zmumu_MV140_280_CFilBVet","Zmumu_MV140_280_CVetBVet", "Zmumu_MV0_70_BFil","Zmumu_MV0_70_CFilBVet","Zmumu_MV0_70_CVetBVet",
			"Zmumu_MV280_500_BFil","Zmumu_MV280_500_CFilBVet","Zmumu_MV280_500_CVetBVet","Zmumu_MV500_1000","Zmumu_MV1000_E_CMS"};
	
	// BFils and jets: 5
	TString Zmm_BFil[]={"Zmm2jets_Min_N_TChannel","Zmumu_MV0_70_BFil","Zmumu_MV70_140_BFil","Zmumu_MV140_280_BFil","Zmumu_MV280_500_BFil"};
	
	// CVetBFil and jets: 5
	TString Zmm_CFilBVet[]={"Zmm2jets_Min_N_TChannel","Zmumu_MV0_70_CFilBVet","Zmumu_MV70_140_CFilBVet","Zmumu_MV140_280_CFilBVet","Zmumu_MV280_500_CFilBVet"};
	TString Zee_CFilBVet[]={"Zee2jets_Min_N_TChannel","Zee_MV0_70_CFilBVet","Zee_MV70_140_CFilBVet","Zee_MV140_280_CFilBVet","Zee_MV280_500_CFilBVet"};
			
	bool norm_hist=true;
	
	TString ljet_pt[] = {"ljet_0_pt","ljet_1_pt","ljet_2_pt", "ljet_3_pt"};
	TString ljet_eta[] = {"ljet_0_eta","ljet_1_eta","ljet_2_eta","ljet_3_eta"};
	TString ljet_phi[] = {"ljet_0_phi","ljet_1_phi","ljet_2_phi","ljet_3_phi"};
	
	TString ljet_test[] = {"ljet_0_eta","ljet_0_phi"};
	
	TString jets_280[] = {"Zmm2jets_Min_N_TChannel","Zmumu_MV280_500_CFilBVet", "Zmumu_MV140_280_CFilBVet"};
	
	PlotSameAxes(jets_280,3,ljet_test,2,"Zmm", "jets_280_ljet_pt");


	cout << "Stacks made!" << endl;
	gROOT->SetBatch(kFALSE);
}
