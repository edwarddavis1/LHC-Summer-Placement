#define MakeStack_cxx
#include "Headers/MC_Analysis.h"

template<int N>
int ListLength(TString (&list)[N]) {
	int length = sizeof(list)/sizeof(list[0]);
	return length;
}

void AddStack(TString c_name, TString get_hist, TString files[], int file_length, string MC_type, bool norm_hist=false) {
	TCanvas *c = new TCanvas(c_name);
	THStack *hs = new THStack(c_name+"_stack","");
	auto legend = new TLegend(0.75,0.7,0.99,0.99);
	TString leg_title;
	
	//cout << ListLength(files) << endl;
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
	TString Zmm_CVetBFil[]={"Zmm2jets_Min_N_TChannel","Zmumu_MV0_70_CFilBVet","Zmumu_MV70_140_CFilBVet","Zmumu_MV140_280_CFilBVet","Zmumu_MV280_500_CFilBVet"};
	TString Zee_CVetBFil[]={"Zee2jets_Min_N_TChannel","Zee_MV0_70_CFilBVet","Zee_MV70_140_CFilBVet","Zee_MV140_280_CFilBVet","Zee_MV280_500_CFilBVet"};
			
	bool norm_hist=true;
	
	//cout << ListLength(Zmm_BFil) << endl;
	AddStack("delta_R_ljet_Zmm_CVetBFil_NoCut","ljet_delta_R_NoCut",Zmm_CVetBFil,ListLength(Zmm_BFil),"Zmm");
	//AddStack("delta_R_lep_Zmm_CVetBFil","lep_delta_R",Zmm_CVetBFil,5,"Zmm");
	//AddStack("delta_R_lep_Zmm_CVetBFil_NoCut","lep_delta_R_NoCut",Zmm_CVetBFil,5,"Zmm");
	
	//AddStack("delta_R_ljet_Zee_CVetBFil","ljet_delta_R",Zee_CVetBFil,5,"Zee");
	//AddStack("delta_R_ljet_Zee_CVetBFil_NoCut","ljet_delta_R_NoCut",Zee_CVetBFil,5,"Zee");
	//AddStack("delta_R_lep_Zee_CVetBFil","lep_delta_R",Zee_CVetBFil,5,"Zee");
	//AddStack("delta_R_lep_Zee_CVetBFil_NoCut","lep_delta_R_NoCut",Zee_CVetBFil,5,"Zee");
		
	
	cout << "Stacks made!" << endl;

}
