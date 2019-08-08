#define MakeStack_cxx
#include "Headers/MC_Analysis.h"
#include <iostream>
#include "vector"

void PlotSameAxes(TString file_names[],int files_len, TString hists[],
					int hists_len, string MC_type, TString legend_entries[],
					TString axis_title, bool write,	bool log_scale) {

	TCanvas *c = new TCanvas(axis_title);
	if (log_scale) c->SetLogy();
	auto legend = new TLegend(0.60, 0.89, 0.9, 0.6);

	float temp_min=0, temp_max=0;
	for (UInt_t j=0; j<files_len; j++) {
		TFile* file = new TFile("OutputFiles/"+file_names[j]+".root");
		for (UInt_t i=0; i<hists_len; i++) {
			TH1F* h = (TH1F*)file->Get(hists[i]);
			if (log_scale) h->SetMinimum(1);
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
			h->SetStats(kFALSE);
			h->SetTitle("");
			h->SetLineColor(kBlack);
			h->SetFillColor(colour);
			colour += 1;
			legend->AddEntry(h,legend_entries[i+j],"f");
			h->GetYaxis()->SetTitle("Events");
			h->GetXaxis()->SetTitle(axis_title);
			if ((i==0) && (j==0)) {
				h->Draw("h");
				h->SetMaximum(1.2*temp_max);
				h->SetMinimum(temp_min);
			}
			else h->Draw("same");
		}
	}
	legend->SetTextFont(42);
	legend->SetTextSize(0.037);
	legend->SetBorderSize(0);
	legend->Draw();

	if (write == true) {
		TFile outfile(TString::Format("OutputFiles/SameAxes_%s.root",
						MC_type.c_str()),"UPDATE");
		c->Write("",TObject::kOverwrite);
		outfile.Close();
		}
}

void PlotStack(TString file_names[],int files_len, TString hists[],
					int hists_len, string MC_type, TString legend_entries[],
					TString axis_title, bool write,	bool log_scale) {

	TCanvas *c = new TCanvas(axis_title+"_stack");
	if (log_scale) c->SetLogy();
	THStack *hs = new THStack(axis_title+"_stack", "");
	auto legend = new TLegend(0.60, 0.89, 0.9, 0.6);

	float temp_min=0, temp_max=0;
	for (UInt_t j=0; j<files_len; j++) {
		TFile* file = new TFile("OutputFiles/"+file_names[j]+".root");
		for (UInt_t i=0; i<hists_len; i++) {
			TH1F* h = (TH1F*)file->Get(hists[i]);
			if (log_scale) h->SetMinimum(1);
		}
	}
	int colour = 6;
	for (UInt_t j=0; j<files_len; j++) {
		TFile* file = new TFile("OutputFiles/"+file_names[j]+".root");
		for (UInt_t i=0; i<hists_len; i++) {
			TH1F* h = (TH1F*)file->Get(hists[i]);
			h->SetStats(kFALSE);
			h->SetTitle("");
			h->SetLineColor(kBlack);
			h->SetFillColor(colour);
			colour += 1;
			hs->Add(h);
			hs->Draw("h");
			legend->AddEntry(h,legend_entries[i+j],"f");
		}
	}
	// hs->Draw();
	hs->GetYaxis()->SetTitle("Events");
	hs->GetXaxis()->SetTitle(axis_title);

	legend->SetTextFont(42);
	legend->SetTextSize(0.037);
	legend->SetBorderSize(0);
	legend->Draw();

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
	TString VBF[] = {"VBF"};
	TString VBF_r10201[] = {"VBF_r10201"};
	TString EW[] = {"ttb_nonallh_r10201", "VBF_r10201", "Diboson", "Zll_QCD"};
	TString EW_leg[] = {"t#bar{t}", "VBF", "Diboson", "Z#rightarrowll QCD"};
	TString EW_QCD[] = {"VBF_r10201", "Zll_QCD"};
	TString EW_QCD_leg[] = {"VBF", "Z#rightarrowll QCD"};

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
	TString ljet_inv_mass[] = {"ljet_inv_mass", "ljet_inv_mass_search"};
	TString ljet_inv_mass_preselect[] = {"ljet_inv_mass_preselect"};
	TString ljet_inv_mass_search[] = {"ljet_inv_mass_search"};

	bool write = true;
	bool dont_write = false;
	bool log_scale = true;
	bool lin_scale = false;

	TString regions[] = {"Baseline", "Search"};


	// PlotSameAxes(Zmm2jets, 1, centrality, 4, "Zmm",
	// 				"Zmm2jets Centrality", regions, "Centrality", dont_write,
					// line_scale);

	// PlotSameAxes(EW, 3, ljet_inv_mass_preselect, 1, "EW",
	// 				EW_leg, "mjj_r10201 [GeV/c^{2}]", dont_write, log_scale);

	PlotStack(EW_QCD, 2, ljet_inv_mass_search, 1, "EW",
					EW_QCD_leg, "mjj_r10201 [GeV/c^{2}]", dont_write, log_scale);

	cout << "Stacks made!" << endl;
	gROOT->SetBatch(kFALSE);
}
