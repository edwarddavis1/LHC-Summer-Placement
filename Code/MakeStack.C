#define MakeStack_cxx
#include "Headers/MC_Analysis.h"



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

void PlotSameAxes(TString file_name,TString hist1, TString hist2, string MC_type, TString legend_title, TString c_name) {
	TCanvas *c = new TCanvas(c_name);
	TFile* file = new TFile("OutputFiles/"+file_name+".root");
	auto legend = new TLegend(0.75,0.7,0.99,0.99);
	TH1F* h_1 = (TH1F*)file->Get(hist1);
	TH1F* h_2 = (TH1F*)file->Get(hist2);
	h_1->SetTitle(c_name);
	h_2->SetTitle(c_name);
	
	
	h_1->SetFillColor(kMagenta);	
	h_2->SetFillColor(kCyan);
	h_1->SetFillStyle(3001);
	h_2->SetFillStyle(3001);
	legend->AddEntry(h_1,hist1,"f");
	legend->AddEntry(h_2,hist2,"f");	
	
	float y_min = min(h_1->GetMinimum(),h_2->GetMinimum());
	y_min = fmax(y_min,0.8);
	h_1->SetMinimum(y_min);
	float y_max = 1.2*max(h_1->GetMaximum(),h_2->GetMaximum());
	h_1->SetMaximum(y_max);
	h_1->Draw();
	h_2->Draw("same");
	
	legend->SetHeader(legend_title,"C"); // option "C" allows to center the header
	legend->SetTextSize(0.02);
	legend->Draw();
	
	TFile outfile(TString::Format("OutputFiles/Stacked_%s.root",MC_type.c_str()),"UPDATE");
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
	
	PlotSameAxes("Zmm2jets_Min_N_TChannel","lep_eta","lep_rapidity","Zmm","Zmm2jets","Eta vs Rap");
	
	
	
	//AddStack("delta_R_lep_Zmm_CVetBFil","lep_delta_R",Zmm_CFilBVet,5,"Zmm");
	//AddStack("delta_R_rap_lep_Zmm_CVetBFil","lep_delta_R_rap",Zmm_CFilBVet,5,"Zmm");
	//AddStack("delta_eta_lep_Zmm_CVetBFil","lep_delta_eta",Zmm_CVetBFil,5,"Zmm");
	//AddStack("delta_phi_lep_Zmm_CVetBFil","lep_delta_phi",Zmm_CVetBFil,5,"Zmm");
	//AddStack("delta_eta_ljet_Zmm_CVetBFil","ljet_delta_eta",Zmm_CVetBFil,5,"Zmm");
	//AddStack("delta_phi_ljet_Zmm_CVetBFil","ljet_delta_phi",Zmm_CVetBFil,5,"Zmm");	
	
	//TString hists_eta_rap[]={"lep_delta_R","lep_delta_R_rap"};
	//AddCuts("Zmm2jets_R_eta_rap", hists_eta_rap, "Zmm2jets_Min_N_TChannel", 2, "Zmm");
	
	cout << "Stacks made!" << endl;

}
