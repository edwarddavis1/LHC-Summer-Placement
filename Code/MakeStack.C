#define MakeStack_cxx
#include "Headers/MC_Analysis.h"
#include <iostream>
#include "vector"

void PlotSameAxes(TString file_names[],int files_len, TString hists[],
					int hists_len, string MC_type, TString legend_entries[],
					TString axis_title, TString region,
					bool write,	bool logx_scale, bool logy_scale) {

	int hist_num = hists_len + files_len;
	TCanvas *c = new TCanvas(axis_title+"_"+region+"_stack");
	if (logy_scale) c->SetLogy();
	if (logx_scale) c->SetLogx();
	auto legend = new TLegend(0.75, 0.89, 0.9, 0.9 - (hist_num - 1)*0.04);

	float temp_min=0, temp_max=0;
	for (UInt_t j=0; j<files_len; j++) {
		TFile* file = new TFile("OutputFiles/"+file_names[j]+".root");
		for (UInt_t i=0; i<hists_len; i++) {
			TH1F* h = (TH1F*)file->Get(hists[i]);
			if (logy_scale) h->SetMinimum(1);
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

			// could maybe remove this once a bunch of sims have been run
			// GetColour() in GenericFunctions colours individual sims
			if (file_names[j].Contains("VBF")) colour = 590;
			else if (file_names[j].Contains("jets")) {
				if (file_names[j].Contains("Zmm")) colour = 856;
				if (file_names[j].Contains("Zee")) colour = 851;
				if (file_names[j].Contains("Ztt")) colour = 853;
			}
			else if (file_names[j].Contains("ZqqZll")) colour = 806;
			else if (file_names[j].Contains("Wenu")) colour = 820;
			else if (file_names[j].Contains("Wmunu")) colour = 819;
			else if (file_names[j].Contains("Wtaunu")) colour = 827;
			else if (file_names[j].Contains("ttb")) colour = 632;
			else if (file_names[j].Contains("llll")) colour = 908;
			else if (file_names[j].Contains("lllv")) colour = 891;
			else if (file_names[j].Contains("llvv")) colour = 906;
			else if (file_names[j].Contains("lvvv")) colour = 901;
			else if (file_names[j].Contains("Z")) colour = 865;

			else colour = 0;

			if (file_names[j].Contains("r9364")) colour = 595;

			// h->SetLineColor(kBlack);
			h->SetLineColor(colour);

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
	legend->SetTextSize(0.03);
	legend->SetBorderSize(0);
	legend->Draw();

	TText *region_label = new TText();
	region_label-> SetNDC();
	region_label -> SetTextFont(42);
	region_label -> SetTextSize(0.03);
	region_label -> SetTextAlign(22);
	region_label -> DrawText(0.65, 0.86, region+" Region");

	TText *data_label = new TText();
	data_label-> SetNDC();
	data_label -> SetTextFont(42);
	data_label -> SetTextSize(0.03);
	data_label -> SetTextAlign(22);
	data_label -> DrawText(0.65, 0.8, "MC Simulation");

	if (write == true) {
		TFile outfile(TString::Format("OutputFiles/SameAxes_%s.root",
						MC_type.c_str()),"UPDATE");
		c->Write("",TObject::kOverwrite);
		outfile.Close();
		}
}

void PlotStack(TString file_names[],int files_len, TString hists[],
					int hists_len, TString legend_entries[],
					TString axis_title, TString region,
					bool logx_scale, bool logy_scale) {

	int hist_num = hists_len + files_len;
	TCanvas *c = new TCanvas(axis_title + "_" + region + "_stack");
	if (logy_scale) c->SetLogy();
	if (logx_scale) c->SetLogx();
	THStack *hs = new THStack(axis_title + "_" + region + "_stack", "");
	auto legend = new TLegend(0.75, 0.89, 0.9, 0.9 - (hist_num - 1)*0.04);

	// get files
	vector<Long64_t> hist_entries;
	Long64_t sum_hist_entries = 0;
	float temp_min=0, temp_max=0;
	for (UInt_t j=0; j<files_len; j++) {
		TFile* file = new TFile("OutputFiles/"+file_names[j]+".root");
		for (UInt_t i=0; i<hists_len; i++) {
			TH1F* h = (TH1F*)file->Get(hists[i]);
			Long64_t hist_entry = h -> GetEntries();
			hist_entries.push_back(hist_entry);
			sum_hist_entries += hist_entry;


			if (logy_scale) h->SetMinimum(1);
		}
	}

	// set style & draw
	int colour;
	for (UInt_t j=0; j<files_len; j++) {
		TFile* file = new TFile("OutputFiles/"+file_names[j]+".root");
		for (UInt_t i=0; i<hists_len; i++) {
			TH1F* h = (TH1F*)file->Get(hists[i]);
			h->SetStats(kFALSE);
			h->SetTitle("");
			h->GetXaxis()->SetRange(0, 200);

			// could maybe remove this once a bunch of sims have been run
			// GetColour() in GenericFunctions colours individual sims
			if (hists_len == 1) {
				if (file_names[j].Contains("VBF")) colour = 590;
				else if (file_names[j].Contains("jets")) {
					if (file_names[j].Contains("Zmm")) colour = 856;
					if (file_names[j].Contains("Zee")) colour = 851;
					if (file_names[j].Contains("Ztt")) colour = 853;
				}
				else if (file_names[j].Contains("ZqqZll")) colour = 806;
				else if (file_names[j].Contains("Wenu")) colour = 400;
				else if (file_names[j].Contains("Wmunu")) colour = 390;
				else if (file_names[j].Contains("Wtaunu")) colour = 395;
				else if (file_names[j].Contains("ttb")) colour = 632;
				else if (file_names[j].Contains("llll")) colour = 908;
				else if (file_names[j].Contains("lllv")) colour = 891;
				else if (file_names[j].Contains("llvv")) colour = 906;
				else if (file_names[j].Contains("lvvv")) colour = 901;
				else if (file_names[j].Contains("QCD")) colour = 865;
				else if (file_names[j].Contains("Zmumu")) colour = 840;
				else if (file_names[j].Contains("Zee")) colour = 849;
				else if (file_names[j].Contains("Ztt")) colour = 843;

				else colour = 0;
			}
			else {
				if (legend_entries[i+j].Contains("Pre-Select")) colour = 880;
				else if (legend_entries[i+j].Contains("Baseline")) colour = 600;
				else if (legend_entries[i+j].Contains("Search")) colour = 432;
				else if (legend_entries[i+j].Contains("Control")) colour = 416;
				else colour = 400;

			}

			if (file_names[j].Contains("r9364")) colour = 595;

			h->SetLineColor(kBlack);
			h->SetFillColor(colour);


			hs->Add(h);
			hs->Draw("h");
			legend->AddEntry(h,legend_entries[i+j]);
		}
	}

	hs->GetYaxis()->SetTitle("Events");
	hs->GetXaxis()->SetTitle(axis_title);

	legend->SetTextFont(42);
	legend->SetTextSize(0.03);
	legend->SetBorderSize(0);
	legend->Draw();

	TText *region_label = new TText();
	region_label-> SetNDC();
	region_label -> SetTextFont(42);
	region_label -> SetTextSize(0.03);
	region_label -> SetTextAlign(22);
	region_label -> DrawText(0.65, 0.86, region+" Region");

	TText *data_label = new TText();
	data_label-> SetNDC();
	data_label -> SetTextFont(42);
	data_label -> SetTextSize(0.03);
	data_label -> SetTextAlign(22);
	data_label -> DrawText(0.65, 0.8, "MC Simulation");

	// if (write == true) {
	// 	TFile outfile(TString::Format("OutputFiles/SameAxes_%s.root",
	// 					MC_type.c_str()),"UPDATE");
	// 	c->Write("",TObject::kOverwrite);
	// 	outfile.Close();
	// 	}

	// calculate percentages
	cout << "\nComposition of " << region << " Region:" << endl;
	for (int i = 0; i < hist_entries.size(); i++) {
		double percentage;

		percentage = 100 * ((double)hist_entries[i] / (double)sum_hist_entries);
    	cout << setprecision(3);
		cout << legend_entries[i] << ": " << percentage << " %" << endl;
	}


}

void MakeStack() {
	//gROOT->SetBatch(kTRUE);
	cout << "Making stacks..." << endl;

	bool write = true;
	bool dont_write = false;
	bool logy_scale = true;
	bool liny_scale = false;
	bool logx_scale = true;
	bool linx_scale = false;

	//-------------------------- Histograms -----------------------------//
	TString tau_inv_mass_baseline[] = {"tau_inv_mass_baseline"};
	TString tau_inv_mass_preselect[] = {"tau_inv_mass_preselect"};
	TString tau_inv_mass_search[] = {"tau_inv_mass_search"};
	TString tau_inv_mass_control[] = {"tau_inv_mass_control"};
	TString tau_inv_mass_highmass[] = {"tau_inv_mass_highmass"};
	TString tau_inv_mass_reco_baseline[] = {"tau_inv_mass_reco_baseline"};
	TString tau_inv_mass_reco_preselect[] = {"tau_inv_mass_reco_preselect"};
	TString tau_inv_mass_reco_search[] = {"tau_inv_mass_reco_search"};
	TString tau_inv_mass_reco_control[] = {"tau_inv_mass_reco_control"};
	TString tau_inv_mass_reco_highmass[] = {"tau_inv_mass_reco_highmass"};
	TString ljet_inv_mass_preselect[] = {"ljet_inv_mass_preselect"};
	TString ljet_inv_mass_baseline[] = {"ljet_inv_mass_baseline"};
	TString ljet_inv_mass_search[] = {"ljet_inv_mass_search"};
	TString ljet_inv_mass_control[] = {"ljet_inv_mass_control"};
	TString ljet_inv_mass_highmass[] = {"ljet_inv_mass_highmass"};
	TString tau_pt_balance_reco_baseline[] = {"tau_pt_balance_reco_baseline"};
	TString tau_pt_balance_reco_preselect[] = {"tau_pt_balance_reco_preselect"};
	TString tau_pt_balance_reco_search[] = {"tau_pt_balance_reco_search"};
	TString tau_pt_balance_reco_control[] = {"tau_pt_balance_reco_control"};
	TString tau_pt_balance_reco_highmass[] = {"tau_pt_balance_reco_highmass"};
	TString lep_no_preselect[] = {"lep_no_preselect"};
	TString lep_inv_mass_preselect[] = {"lep_inv_mass_preselect"};
	TString lep_inv_mass_baseline[] = {"lep_inv_mass_baseline"};
	TString lep_inv_mass_search[] = {"lep_inv_mass_search"};
	TString lep_inv_mass_control[] = {"lep_inv_mass_control"};
	TString lep_inv_mass_highmass[] = {"lep_inv_mass_highmass"};
	TString lep_inv_mass_reco_preselect[] = {"lep_inv_mass_reco_preselect"};
	TString lep_inv_mass_reco_baseline[] = {"lep_inv_mass_reco_baseline"};
	TString lep_inv_mass_reco_search[] = {"lep_inv_mass_reco_search"};
	TString lep_inv_mass_reco_control[] = {"lep_inv_mass_reco_control"};
	TString lep_inv_mass_reco_highmass[] = {"lep_inv_mass_reco_highmass"};
	TString elec_inv_mass_baseline[] = {"elec_inv_mass_baseline"};
	TString muon_inv_mass_baseline[] = {"muon_inv_mass_baseline"};
	TString elec_inv_mass_preselect[] = {"elec_inv_mass_preselect"};
	TString muon_inv_mass_preselect[] = {"muon_inv_mass_preselect"};
	TString elec_inv_mass_search[] = {"elec_inv_mass_search"};
	TString muon_inv_mass_search[] = {"muon_inv_mass_search"};
	TString elec_inv_mass_control[] = {"elec_inv_mass_control"};
	TString muon_inv_mass_control[] = {"muon_inv_mass_control"};
	TString elec_inv_mass_highmass[] = {"elec_inv_mass_highmass"};
	TString muon_inv_mass_highmass[] = {"muon_inv_mass_highmass"};
	TString elec_0_iso_etcone20_baseline[] = {"elec_0_iso_etcone20_baseline"};
	TString muon_0_iso_etcone20_baseline[] = {"muon_0_iso_etcone20_baseline"};
	TString elec_0_iso_ptcone30_baseline[] = {"elec_0_iso_ptcone30_baseline"};
	TString muon_0_iso_ptcone30_baseline[] = {"muon_0_iso_ptcone30_baseline"};
	TString n_jets_preselect[] = {"n_jets_preselect"};
	TString ljet_0_pt_baseline[] = {"ljet_0_pt_baseline"};
	TString ljet_0_eta_baseline[] = {"ljet_0_eta_baseline"};
	TString ljet_0_phi_baseline[] = {"ljet_0_phi_baseline"};
	TString ljet_1_pt_baseline[] = {"ljet_1_pt_baseline"};
	TString ljet_1_eta_baseline[] = {"ljet_1_eta_baseline"};
	TString ljet_1_phi_baseline[] = {"ljet_1_phi_baseline"};
	TString bjet_0_pt_baseline[] = {"bjet_0_pt_baseline"};
	TString bjet_0_eta_baseline[] = {"bjet_0_eta_baseline"};
	TString bjet_0_phi_baseline[] = {"bjet_0_phi_baseline"};
	TString bjet_inv_mass_baseline[] = {"bjet_inv_mass_baseline"};
	TString lep_0_pt_baseline[] = {"lep_0_pt_baseline"};
	TString lep_0_eta_baseline[] = {"lep_0_eta_baseline"};
	TString lep_0_phi_baseline[] = {"lep_0_phi_baseline"};
	TString lep_1_pt_baseline[] = {"lep_1_pt_baseline"};
	TString lep_1_eta_baseline[] = {"lep_1_eta_baseline"};
	TString lep_1_phi_baseline[] = {"lep_1_phi_baseline"};
	TString Z_centrality_baseline[] = {"Z_centrality_baseline"};
	TString Z_centrality_preselect[] = {"Z_centrality_preselect"};
	TString Z_centrality_search[] = {"Z_centrality_search"};
	TString Z_centrality_control[] = {"Z_centrality_control"};
	TString Z_centrality_highmass[] = {"Z_centrality_highmass"};
	TString ljet_delta_eta_baseline[] = {"ljet_delta_eta_baseline"};
	TString ljet_delta_eta_preselect[] = {"ljet_delta_eta_preselect"};
	TString ljet_delta_phi[] = {"ljet_delta_phi"};
	TString ljet_delta_R[] = {"ljet_delta_R"};
	TString ljet_delta_phi_preselect[] = {"ljet_delta_phi_preselect"};
	TString ljet_delta_R_preselect[] = {"ljet_delta_R_preselect"};
	TString lep_delta_eta_baseline[] = {"lep_delta_eta_baseline"};
	TString lep_delta_phi_baseline[] = {"lep_delta_phi_baseline"};
	TString lep_delta_R_baseline[] = {"lep_delta_R_baseline"};
	TString lep_delta_eta_preselect[] = {"lep_delta_eta_preselect"};
	TString lep_delta_phi_preselect[] = {"lep_delta_phi_preselect"};
	TString lep_delta_R_preselect[] = {"lep_delta_R_preselect"};
	TString lep_0_rapidity_baseline[] = {"lep_0_rapidity_baseline"};
	TString lep_eta_L_SL_preselect[] = {"lep_eta_L_SL_preselect"};
	TString ljet_eta_L_SL_preselect[] = {"ljet_eta_L_SL_preselect"};
	TString ljet_eta_L_SL_2jets_preselect[] = {"ljet_eta_L_SL_2jets_preselect"};
	TString lep_phi_L_SL_preselect[] = {"lep_phi_L_SL_preselect"};
	TString ljet_phi_L_SL_preselect[] = {"ljet_phi_L_SL_preselect"};
	TString ljet_2_pt_baseline[] = {"ljet_2_pt_baseline"};
	TString ljet_3_pt_baseline[] = {"ljet_3_pt_baseline"};
	TString ljet_2_eta_baseline[] = {"ljet_2_eta_baseline"};
	TString ljet_3_eta_baseline[] = {"ljet_3_eta_baseline"};
	TString ljet_2_phi_baseline[] = {"ljet_2_phi_baseline"};
	TString ljet_3_phi_baseline[] = {"ljet_3_phi_baseline"};
	TString lep_eta_sum_baseline[] = {"lep_eta_sum_baseline"};
	TString ljet_eta_sum_baseline[] = {"ljet_eta_sum_baseline"};
	TString ljet_2_delta_eta_baseline[] = {"ljet_2_delta_eta_baseline"};
	TString ljet_3_delta_eta_baseline[] = {"ljet_3_delta_eta_baseline"};
	TString ljet_0_eta_2jets_baseline[] = {"ljet_0_eta_2jets_baseline"};
	TString ljet_1_eta_2jets_baseline[] = {"ljet_1_eta_2jets_baseline"};
	TString ljet_2_eta_2jets_baseline[] = {"ljet_2_eta_2jets_baseline"};
	TString ljet_3_eta_2jets_baseline[] = {"ljet_3_eta_2jets_baseline"};
	TString ljet_0_eta_3jets_baseline[] = {"ljet_0_eta_3jets_baseline"};
	TString ljet_1_eta_3jets_baseline[] = {"ljet_1_eta_3jets_baseline"};
	TString ljet_2_eta_3jets_baseline[] = {"ljet_2_eta_3jets_baseline"};
	TString ljet_3_eta_3jets_baseline[] = {"ljet_3_eta_3jets_baseline"};
	TString ljet_0_eta_4jets_baseline[] = {"ljet_0_eta_4jets_baseline"};
	TString ljet_1_eta_4jets_baseline[] = {"ljet_1_eta_4jets_baseline"};
	TString ljet_2_eta_4jets_baseline[] = {"ljet_2_eta_4jets_baseline"};
	TString ljet_3_eta_4jets_baseline[] = {"ljet_3_eta_4jets_baseline"};
	TString ljet_0_eta_5jets_baseline[] = {"ljet_0_eta_5jets_baseline"};
	TString ljet_1_eta_5jets_baseline[] = {"ljet_1_eta_5jets_baseline"};
	TString ljet_2_eta_5jets_baseline[] = {"ljet_2_eta_5jets_baseline"};
	TString ljet_3_eta_5jets_baseline[] = {"ljet_3_eta_5jets_baseline"};
	TString lep_pt_balance_baseline[] = {"lep_pt_balance_baseline"};
	TString delta_eta_pt_ll_baseline[] = {"delta_eta_pt_ll_baseline"};
	TString delta_phi_pt_ll_baseline[] = {"delta_phi_pt_ll_baseline"};

	//---------------------------- Files --------------------------------//
	TString Zmm2jets[] = {"Zmm2jets_Min_N_TChannel_r10201",
							"Zee2jets_Min_N_TChannel_r10201",
							"Ztt2jets_Min_N_TChannel_r10201"};
	TString Zlls[] = {"Zmm2jets_Min_N_TChannel_r10201", "Zmumu"};
	TString Zlls_leg[] = {"EW Zll", "QCD Zll"};

	TString EW_QCD[] = {"ttb_nonallh_r10201",
						"lvvv_r10201", "llvv_r10201",
						"lllv_r10201", "llll_r10201",
						"Wtaunu", "Wmunu", "Wenu",
						"ZqqZll_r10201",
						"VBF",
						"Zll_QCD"};

	TString EW_QCD_leg[] = {"t#bar{t}",
							"lvvv", "llvv", "lllv", "llll",
							"Wtaunu", "Wmunu", "Wenu",
							"ZqqZll",
							"EW Zll",
							"QCD Zll"};

	TString all_processes[] = {"ttb_nonallh_r10201",
						"lvvv_r10201", "llvv_r10201",
						"lllv_r10201", "llll_r10201",
						"Wtaunu", "Wmunu", "Wenu",
						"ZqqZll_r10201",
						"Zmm2jets_Min_N_TChannel_r10201",
						"Zee2jets_Min_N_TChannel_r10201",
						"Ztt2jets_Min_N_TChannel_r10201",
						"Zmumu", "Zee", "Ztt"};

	TString all_processes_leg[] = {"t#bar{t}",
						"lvvv", "llvv",
						"lllv", "llll",
						"Wtaunu", "Wmunu", "Wenu",
						"ZqqZll",
						"EW Z#mu#mu",
						"EW Zee",
						"EW Ztt",
						"QCD Zmumu", "QCD Zee", "QCD Ztt"};

	TString EW_QCD_test[] = {"VBF_r9364", "VBF_r10201", "Zll_QCD"};

	TString QCD_Zll[] = {"Zmumu", "Zee", "Ztt"};
	TString regions[] = {"Control", "Search", "Baseline", "Pre-Select"};


	PlotStack(all_processes, 15, lep_inv_mass_preselect, 1,
					all_processes_leg, "mll [GeV/c^{2}]", "Pre-Selection",
					linx_scale, logy_scale);



	cout << "Stacks made!" << endl;
	gROOT->SetBatch(kFALSE);
}
