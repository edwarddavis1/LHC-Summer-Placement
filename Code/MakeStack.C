#define MakeStack_cxx
#include "Headers/MC_Analysis.h"
#include <iostream>
#include "vector"

void AddStack(TString c_name, TString get_hist, TString files[],
			int file_length, string MC_type, bool norm_hist=false) {
	TCanvas *c = new TCanvas(c_name);
	THStack *hs = new THStack(c_name+"_stack","");
	auto legend = new TLegend(0.75,0.7,0.99,0.99);
	TString leg_title;

	for (UInt_t i=0;i<file_length;i++){
		TFile* file = new TFile("OutputFiles/"+files[i]+".root");
		TH1F* h = (TH1F*)file->Get(get_hist);

		if (norm_hist == true) {
			Double_t norm = h->GetEntries();
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

	legend->SetHeader(leg_title,"C");
	legend->SetTextSize(0.02);
	legend->Draw();
	}

	TFile outfile(TString::Format("OutputFiles/Stacked_%s.root",
									MC_type.c_str()),"UPDATE");
	c->Write("",TObject::kOverwrite);
	outfile.Close();
}

void StackCuts(TString c_name, TString get_hists[], TString file_name,
				int hists_length, string MC_type, bool norm_hist=false) {

	TCanvas *c = new TCanvas(c_name);
	THStack *hs = new THStack(c_name+"_stack","");
	TFile* file = new TFile("OutputFiles/"+file_name+".root");
	auto legend = new TLegend(0.75,0.7,0.99,0.99);
	TString leg_title;

	for (UInt_t i=0;i<hists_length;i++){
		TH1F* h;
		h = (TH1F*)file->Get(get_hists[i]);
		h->SetLineColor(i+2);
		leg_title=file_name;
		hs->Add(h);
		legend->AddEntry(h,get_hists[i],"f");
		//h->Reset();

	hs->Draw();
	hs->GetYaxis()->SetTitle("Counts");
	gPad->Modified();
	gPad->Update();

	legend->SetHeader(leg_title,"C");
	legend->SetTextSize(0.02);
	legend->Draw();
	}

	TFile outfile(TString::Format("OutputFiles/Stacked_%s.root",
									MC_type.c_str()),"UPDATE");
	c->Write("",TObject::kOverwrite);
	outfile.Close();
}


void PlotSameAxes(TString file_names[],int files_len, TString hists[],
					int hists_len, string MC_type, TString legend_title,
					TString legend_entries[], TString axis_title, bool write) {

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
	int colour = 2;
	for (UInt_t j=0; j<files_len; j++) {
		TFile* file = new TFile("OutputFiles/"+file_names[j]+".root");
		for (UInt_t i=0; i<hists_len; i++) {
			TH1F* h = (TH1F*)file->Get(hists[i]);
			h->SetLineColor(colour);
			colour += 1;
			// h->SetFillStyle(3001);
			legend->AddEntry(h,legend_entries[i],"f");
			h->GetYaxis()->SetTitle("Counts");
			h->GetXaxis()->SetTitle(axis_title);
			if ((i==0) && (j==0)) {
				h->Draw();
				h->SetMaximum(1.2*temp_max);
				h->SetMinimum(temp_min);
			}
			else h->Draw("same");
		}
	}
	legend->SetHeader(legend_title,"C");
	legend->SetTextFont(42);
	//legend->SetBorderSize(0);
	legend->Draw();
	TLegendEntry *header = (TLegendEntry*)legend->GetListOfPrimitives()->First();
	header->SetTextFont(42);
	header->SetTextSize(0.025);

	if (write == true) {
		TFile outfile(TString::Format("OutputFiles/SameAxes_%s.root",
						MC_type.c_str()),"UPDATE");
		c->Write("",TObject::kOverwrite);
		outfile.Close();
		}
}

void MakeStack() {
	//gROOT->SetBatch(kTRUE);
	cout << "Making stacks..." << endl;

	// All Zmumu datasets: 15
	TString Zmm_[]={"Zmm2jets_Min_N_TChannel", "Zmumu_MV70_140_BFil",
				"Zmumu_MV70_140_CFilBVet", "Zmumu_MV70_140_CVetBVet",
				"Zmumu_MV140_280_BFil", "Zmumu_MV140_280_CFilBVet",
				"Zmumu_MV140_280_CVetBVet", "Zmumu_MV0_70_BFil",
				"Zmumu_MV0_70_CFilBVet", "Zmumu_MV0_70_CVetBVet",
				"Zmumu_MV280_500_BFil", "Zmumu_MV280_500_CFilBVet",
				"Zmumu_MV280_500_CVetBVet", "Zmumu_MV500_1000",
				"Zmumu_MV1000_E_CMS"};

	// BFils and jets: 5
	TString Zmm_BFil[]={"Zmm2jets_Min_N_TChannel","Zmumu_MV0_70_BFil",
						"Zmumu_MV70_140_BFil","Zmumu_MV140_280_BFil",
						"Zmumu_MV280_500_BFil"};

	// CVetBFil and jets: 5
	TString Zmm_CFilBVet[]={"Zmm2jets_Min_N_TChannel",
							"Zmumu_MV280_500_CFilBVet",
							"Zmumu_MV140_280_CFilBVet",
							"Zmumu_MV70_140_CFilBVet",
							"Zmumu_MV0_70_CFilBVet"};

	TString Zee_CFilBVet[]={"Zee2jets_Min_N_TChannel",
							"Zee_MV0_70_CFilBVet",
							"Zee_MV140_280_CFilBVet",
							"Zee_MV70_140_CFilBVet",
							"Zee_MV280_500_CFilBVet"};

	//---------------------------- Files --------------------------------//
	TString Zmm2jets[] = {"Zmm2jets_Min_N_TChannel"};
	TString Zmumu_MV280_500_CFilBVet[] = {"Zmumu_MV280_500_CFilBVet"};
	TString Zmumu_MV140_280_CFilBVet[] = {"Zmumu_MV140_280_CFilBVet"};

	//-------------------------- Histograms -----------------------------//
	TString ljet_pt[] = {"ljet_0_pt","ljet_1_pt","ljet_2_pt", "ljet_3_pt"};
	TString ljet_eta[] = {"ljet_0_eta","ljet_1_eta","ljet_2_eta","ljet_3_eta"};
	TString ljet_phi[] = {"ljet_0_phi","ljet_1_phi","ljet_2_phi","ljet_3_phi"};
	TString ljet_delta_eta_2[] = {"ljet_delta_eta_2"};
	TString ljet_delta_eta[] = {"ljet_delta_eta"};
	TString ljet_delta_eta_3[] = {"ljet_delta_eta_3"};
	TString ljet_0_eta_2jets[] = {"ljet_0_eta_2jets"};
	TString ljet_1_eta_2jets[] = {"ljet_1_eta_2jets"};
	TString ljet_0_eta_indi[] = {"ljet_0_eta_2jets", "ljet_0_eta_3jets",
									"ljet_0_eta_4jets", "ljet_0_eta_5jets"};
	TString ljet_1_eta_indi[] = {"ljet_1_eta_2jets", "ljet_1_eta_3jets",
									"ljet_1_eta_4jets", "ljet_1_eta_5jets"};
	TString ljet_2_eta_indi[] = {"ljet_2_eta_2jets", "ljet_2_eta_3jets",
									"ljet_2_eta_4jets", "ljet_2_eta_5jets"};
	TString ljet_3_eta_indi[] = {"ljet_3_eta_2jets", "ljet_3_eta_3jets",
									"ljet_3_eta_4jets", "ljet_3_eta_5jets"};
	TString ljets_phi[] = {"ljet_0_phi", "ljet_1_phi", "ljet_2_phi",
							"ljet_3_phi"};
	TString inv_mass_cuts[] = {"muon_inv_mass_preselect", "muon_inv_mass",
								"muon_inv_mass_search", "muon_inv_mass_control",
								"muon_inv_mass_high_mass"};
	TString centrality[] = {"Z_cent", "Z_cent_search",
							"Z_cent_control", "Z_cent_high_mass"};
	TString ljet_inv_mass[] = {"ljet_inv_mass", "ljet_inv_mass_search",
								"ljet_inv_mass_control",
								"ljet_inv_mass_high_mass"};

	bool write=true;
	bool dont_write=false;
	TString regions[] = {"Baseline", "Search", "Control",
	 						"High Mass"};

	PlotSameAxes(Zmm2jets, 1, centrality, 4, "Zmm",
					"Zmm2jets Centrality", regions, "Centrality", dont_write);

	PlotSameAxes(Zmm2jets, 1, ljet_inv_mass, 4, "Zmm",
					"Zmm2jets mjj", regions, "mjj", dont_write);


	cout << "Stacks made!" << endl;
	gROOT->SetBatch(kFALSE);
}
