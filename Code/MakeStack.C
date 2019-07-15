void MakeStack() {
	//--------------------- Stacking accross datasets ----------------------//
	cout << "Making stacks..." << endl;
	TCanvas *c_elec_inv_mass = new TCanvas("elec_inv_mass");
	THStack *h_elec_inv_mass_stack = new THStack("elec_inv_mass_stack", "Electron Invariant Mass Test Stack");

	// Read in histogram from other datasets
	TFile* Zee2jets_file = new TFile("OutputFiles/Zee2jets_Min_N_TChannel.root");
	TH1F* h_Zee2jets_elec_inv_mass = (TH1F*)Zee2jets_file->Get("elec_inv_mass");
	TH1F* h_Zee2jets_elec_inv_mass_NoCuts = (TH1F*)Zee2jets_file->Get("elec_inv_mass_NoCut");

	TFile* Zee_MV0_file = new TFile("OutputFiles/Zee_MV0_70_CFilBVet.root");
	TH1F* h_Zee_MV0_elec_inv_mass = (TH1F*)Zee_MV0_file->Get("elec_inv_mass");	
	
	h_Zee2jets_elec_inv_mass->SetFillColor(kBlue);
	h_Zee2jets_elec_inv_mass_NoCuts->SetFillColor(kCyan);
	h_Zee_MV0_elec_inv_mass->SetLineColor(4);	
	
	h_elec_inv_mass_stack->Add(h_Zee2jets_elec_inv_mass);
	h_elec_inv_mass_stack->Add(h_Zee2jets_elec_inv_mass_NoCuts);
	h_elec_inv_mass_stack->Add(h_Zee_MV0_elec_inv_mass);

	h_elec_inv_mass_stack->Draw();
	gPad->BuildLegend(0.75,0.75,0.95,0.95,"");

	TFile outfile("StackFile","RECREATE");
	c_elec_inv_mass->Write();
	h_Zee2jets_elec_inv_mass->Write();
	outfile.Close();
	cout << "Stacks made!" << endl;
	
}
