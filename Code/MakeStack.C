#define MakeStack_cxx
#include "Headers/MC_Analysis.h"
#include <iostream>
#include "vector"

// void PlotSameAxes(TString file_names[],int files_len, TString hists[],
// 					int hists_len, string MC_type, TString legend_entries[],
// 					TString axis_title, TString region,
// 					bool write,	bool logx_scale, bool logy_scale) {
//
// 	int hist_num = hists_len + files_len;
// 	TCanvas *c = new TCanvas(axis_title+"_"+region+"_stack");
// 	if (logy_scale) c->SetLogy();
// 	if (logx_scale) c->SetLogx();
// 	auto legend = new TLegend(0.75, 0.89, 0.9, 0.9 - (hist_num - 1)*0.04);
//
// 	float temp_min=0, temp_max=0;
// 	for (UInt_t j=0; j<files_len; j++) {
// 		TFile* file = new TFile("OutputFiles/"+file_names[j]+".root");
// 		for (UInt_t i=0; i<hists_len; i++) {
// 			TH1F* h = (TH1F*)file->Get(hists[i]);
// 			if (logy_scale) h->SetMinimum(1);
// 			if ((i==0) && (j==0)) {
// 				temp_min = h->GetMinimum();
// 				temp_max = h->GetMaximum();
// 			}
// 			else {
// 				if (temp_min > h->GetMinimum()) temp_min = h->GetMinimum();
// 				if (temp_max < h->GetMaximum()) temp_max = h->GetMaximum();
// 			}
// 		}
// 	}
// 	int colour = 6;
// 	for (UInt_t j=0; j<files_len; j++) {
// 		TFile* file = new TFile("OutputFiles/"+file_names[j]+".root");
// 		for (UInt_t i=0; i<hists_len; i++) {
// 			TH1F* h = (TH1F*)file->Get(hists[i]);
// 			h->SetStats(kFALSE);
// 			h->SetTitle("");
//
// 			// could maybe remove this once a bunch of sims have been run
// 			// GetColour() in GenericFunctions colours individual sims
// 			if (file_names[j].Contains("VBF")) colour = 590;
// 			else if (file_names[j].Contains("jets")) {
// 				if (file_names[j].Contains("Zmm")) colour = 856;
// 				if (file_names[j].Contains("Zee")) colour = 851;
// 				if (file_names[j].Contains("Ztt")) colour = 853;
// 			}
// 			else if (file_names[j].Contains("ZqqZll")) colour = 806;
// 			else if (file_names[j].Contains("Wenu")) colour = 820;
// 			else if (file_names[j].Contains("Wmunu")) colour = 819;
// 			else if (file_names[j].Contains("Wtaunu")) colour = 827;
// 			else if (file_names[j].Contains("ttb")) colour = 632;
// 			else if (file_names[j].Contains("llll")) colour = 908;
// 			else if (file_names[j].Contains("lllv")) colour = 891;
// 			else if (file_names[j].Contains("llvv")) colour = 906;
// 			else if (file_names[j].Contains("lvvv")) colour = 901;
// 			else if (file_names[j].Contains("Z")) colour = 865;
//
// 			else colour = 0;
//
// 			if (file_names[j].Contains("r9364")) colour = 595;
//
// 			// h->SetLineColor(kBlack);
// 			h->SetLineColor(colour);
//
// 			legend->AddEntry(h,legend_entries[i+j],"f");
// 			h->GetYaxis()->SetTitle("Events");
// 			h->GetXaxis()->SetTitle(axis_title);
//
// 			if ((i==0) && (j==0)) {
// 				h->Draw("h");
// 				h->SetMaximum(1.2*temp_max);
// 				h->SetMinimum(temp_min);
// 			}
// 			else h->Draw("same");
// 		}
// 	}
// 	legend->SetTextFont(42);
// 	legend->SetTextSize(0.03);
// 	legend->SetBorderSize(0);
// 	legend->Draw();
//
// 	TText *region_label = new TText();
// 	region_label-> SetNDC();
// 	region_label -> SetTextFont(42);
// 	region_label -> SetTextSize(0.03);
// 	region_label -> SetTextAlign(22);
// 	region_label -> DrawText(0.65, 0.86, region+" Region");
//
// 	TText *data_label = new TText();
// 	data_label-> SetNDC();
// 	data_label -> SetTextFont(42);
// 	data_label -> SetTextSize(0.03);
// 	data_label -> SetTextAlign(22);
// 	data_label -> DrawText(0.65, 0.8, "MC Simulation");
//
// 	if (write == true) {
// 		TFile outfile(TString::Format("OutputFiles/SameAxes_%s.root",
// 						MC_type.c_str()),"UPDATE");
// 		c->Write("",TObject::kOverwrite);
// 		outfile.Close();
// 		}
// }

void PlotStack(vector<TString> file_names, vector<TString> hists,
					vector<TString> legend_entries,
					TString axis_title, TString region,
					bool logx_scale, bool logy_scale) {

	int files_len = file_names.size();
	int hists_len = hists.size();
	int hist_num = files_len + hists_len;
	TCanvas *c = new TCanvas(axis_title + "_" + region + "_stack");
	if (logy_scale) c->SetLogy();
	if (logx_scale) c->SetLogx();
	THStack *hs = new THStack(axis_title + "_" + region + "_stack", "");
	auto legend = new TLegend(0.75, 0.89, 0.9, 0.9 - (hist_num - 1)*0.04);

	// get files
	vector<Long64_t> hist_entries;
	Long64_t sum_hist_entries = 0;
	float temp_min = 0, temp_max = 0;
	int colour = 0;
	int hists_made = 0;
	for (UInt_t j = 0; j < files_len; j++) {
		TFile* file = new TFile("OutputFiles/" + file_names[j] + ".root");
		for (UInt_t i = 0; i < hists_len; i++) {
			TH1F* h = (TH1F*)file->Get(hists[i]);
			Long64_t hist_entry = h -> GetEntries();
			hist_entries.push_back(hist_entry);
			sum_hist_entries += hist_entry;

			if (logy_scale) h->SetMinimum(1);
			h->SetStats(kFALSE);
			h->SetTitle("");
			h->GetXaxis()->SetRange(0, 200);

			// could maybe remove this once a bunch of sims have been run
			// GetColour() in GenericFunctions colours individual sims
			if (legend_entries[hists_made].Contains("VBF")
				or legend_entries[hists_made].Contains("EW Zll")) colour = 590;
			else if (legend_entries[hists_made].Contains("jets")) {
				if (legend_entries[hists_made].Contains("Zmm")) colour = 856;
				if (legend_entries[hists_made].Contains("Zee")) colour = 851;
				if (legend_entries[hists_made].Contains("Ztt")) colour = 853;
			}
			else if (legend_entries[hists_made].Contains("ZqqZll")) colour = 806;
			else if (legend_entries[hists_made].Contains("Wenu")) colour = 400;
			else if (legend_entries[hists_made].Contains("Wmunu")) colour = 390;
			else if (legend_entries[hists_made].Contains("Wtaunu")) colour = 395;
			else if (legend_entries[hists_made].Contains("t#bar{t}")) colour = 632;
			else if (legend_entries[hists_made].Contains("llll")) colour = 908;
			else if (legend_entries[hists_made].Contains("lllv")) colour = 891;
			else if (legend_entries[hists_made].Contains("llvv")) colour = 906;
			else if (legend_entries[hists_made].Contains("lvvv")) colour = 901;
			else if (legend_entries[hists_made].Contains("QCD")) colour = 865;
			else if (legend_entries[hists_made].Contains("Zmumu")) colour = 840;
			else if (legend_entries[hists_made].Contains("Zee")) colour = 849;
			else if (legend_entries[hists_made].Contains("Ztt")) colour = 843;

			if (legend_entries[hists_made].Contains("Pre-Select")) {
				colour += 1;
				cout << "Pre-select loop" << endl;
			}
			if (legend_entries[hists_made].Contains("Baseline")) colour += 2;
			if (legend_entries[hists_made].Contains("Search")) colour += 3;
			if (legend_entries[hists_made].Contains("Control")) colour += 4;



			if (legend_entries[hists_made].Contains("r9364")) colour = 595;

			h->SetLineColor(kBlack);
			h->SetFillColor(colour);


			hs->Add(h);
			hs->Draw("h");
			legend->AddEntry(h,legend_entries[hists_made]);

			hists_made += 1;
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
	if (sum_hist_entries != 0) {
		for (int i = 0; i < hist_entries.size(); i++) {
			double percentage;

			percentage = 100 * ((double)hist_entries[i] / (double)sum_hist_entries);
	    	cout << setprecision(3);
			cout << legend_entries[i] << ": " << percentage << " %" << endl;
		}
	}
	else cout << "could not calculate! No entries at all!" << endl;

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

	//---------------------------- Files --------------------------------//
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

	PlotStack({"ttb_nonallh_r10201", "VBF"},
				{"ljet_inv_mass_preselect", "ljet_inv_mass_search"},
				{"t#bar{t} Pre-Select", "t#bar{t} Search",
					"EW Zll Pre-Select", "EW Zll Search"},
				"mll [GeV/c^{2}]", "Pre-Selection",
				linx_scale, logy_scale);




	cout << "Stacks made!" << endl;
	gROOT->SetBatch(kFALSE);
}
