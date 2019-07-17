#define MakeStack_cxx
#include "Headers/MC_Analysis.h"

void AddStack(TString c_name, TString get_hist, TString files[]) {
	TCanvas *c = new TCanvas(c_name);
	THStack *hs = new THStack(c_name+"_stack","");
	auto legend = new TLegend(0.75,0.8,0.99,0.99);
	
	int file_length = files->Length();
	for (UInt_t i=0;i<file_length;i++){
		TFile* file = new TFile("OutputFiles/"+files[i]+".root");
		TH1F* h = (TH1F*)file->Get(get_hist);
		h->SetFillColor(i+2);
		//h->SetFillStyle(3003);
		hs->Add(h);
		legend->AddEntry(h,files[i],"f");
	
	hs->Draw();
	hs->GetXaxis()->SetTitle(get_hist);
	hs->GetYaxis()->SetTitle("Counts");
	gPad->Modified();
	gPad->Update();	
	
	legend->SetHeader(get_hist,"C"); // option "C" allows to center the header
	legend->SetTextSize(0.02);
	legend->Draw();
	}
	
	TFile outfile("OutputFiles/StackedHists.root","RECREATE");
	c->Write();
	outfile.Close();
}


void MakeStack() {
	cout << "Making stacks..." << endl;

	TString files[]={"Zmm2jets_Min_N_TChannel","Zmumu_MV70_140_BFil","Zmumu_MV70_140_CFilBVet","Zmumu_MV70_140_CVetBVet","Zmumu_MV140_280_BFil",
			"Zmumu_MV140_280_CFilBVet","Zmumu_MV140_280_CVetBVet"};
	AddStack("eta_mumu","lep_eta",files);

	
	

	cout << "Stacks made!" << endl;
	
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
	
	/*TFile *f1 = TFile::Open("…/Downloads/Run08042_ProjectionX.root");
	TCanvas c1 = (TCanvas)f1->Get(c1”);
	TH1D h1 = (TH1D)c1->FindObject(“cutg”);
	TFile *f2 = TFile::Open("…/Downloads/Run08044_ProjectionX.root");
	TCanvas c2 = (TCanvas)f1->Get(“c1”);
	TH1D h2 = (TH1D)c2->FindObject(“cutg”);
	h1->Add(h2,-1);*/
	
}
