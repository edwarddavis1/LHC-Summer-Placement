TH1F* h_lep_n = new TH1F("Lepton_no", "Number of Leptons", 10, -0.5, 9.5);
/*
TH1S* h_lep_type = new TH1S("lep_type", "Lepton Type", 5, 0, 5);

TH1F* h_elec_pt = new TH1F("Electron_pt", "Electron pT in MC %s", 500, 0, 500);	
TH1F* h_muon_pt = new TH1F("Muon_pt", "Muon pT in MC %s", 500, 0, 500);
TH1F* h_tau_pt = new TH1F("Tau_pt", "Tau pT in MC %s", 500, 0, 500);
TH1F* h_elec_pt_FC = new TH1F("Electron_pt_FC", "Electron pT in MC %s Failed Cuts", 500, 0, 500);	
TH1F* h_muon_pt_FC = new TH1F("Muon_pt_FC", "Muon pT in MC %s Failed Cuts", 500, 0, 500);
TH1F* h_tau_pt_FC = new TH1F("Tau_pt_FC", "Tau pT in MC %s Failed Cuts", 500, 0, 500);
*/
TH1F* h_elec_inv_mass = new TH1F("inv_mass_elec", TString::Format("Dilepton Invariant Mass from Electrons in MC %s",choice.c_str()), 500, 0, 150);	
TH1F* h_muon_inv_mass = new TH1F("inv_mass_muon", TString::Format("Dilepton Invariant Mass from Muons in MC %s",choice.c_str()), 500, 0, 150);
TH1F* h_tau_inv_mass = new TH1F("inv_mass_tau", TString::Format("Dilepton Invariant Mass from Tauons in MC %s",choice.c_str()), 500, 0, 150);
TH1F* h_elec_muon_inv_mass = new TH1F("inv_mass_elec_muon", TString::Format("Dilepton Invariant Mass from ElectronMuon in MC %s",choice.c_str()), 500, 0, 150);	
TH1F* h_muon_tau_inv_mass = new TH1F("inv_mass_muon_tau", TString::Format("Dilepton Invariant Mass from MuonTau in MC %s",choice.c_str()), 500, 0, 150);
TH1F* h_elec_tau_inv_mass = new TH1F("inv_mass_elec_tau", TString::Format("Dilepton Invariant Mass from TauElectron in MC %s",choice.c_str()), 500, 0, 150);
TH1F* h_elec_inv_mass_FC = new TH1F("inv_mass_elec_FC", TString::Format("Dilepton Invariant Mass from Electrons in MC %s Failed Cuts",choice.c_str()), 500, 0, 150);	
TH1F* h_muon_inv_mass_FC = new TH1F("inv_mass_muon_FC", TString::Format("Dilepton Invariant Mass from Muons in MC %s Failed Cuts",choice.c_str()), 500, 0, 150);
TH1F* h_tau_inv_mass_FC = new TH1F("inv_mass_tau_FC", TString::Format("Dilepton Invariant Mass from Tauons in MC %s Failed Cuts",choice.c_str()), 500, 0, 150);
TH1F* h_elec_muon_inv_mass_FC = new TH1F("inv_mass_elec_muon_FC", TString::Format("Dilepton Invariant Mass from ElectronMuon in MC %s Failed Cuts",choice.c_str()), 500, 0, 150);	
TH1F* h_muon_tau_inv_mass_FC = new TH1F("inv_mass_muon_elec_FC", TString::Format("Dilepton Invariant Mass from MuonTau in MC %s Failed Cuts",choice.c_str()), 500, 0, 150);
TH1F* h_elec_tau_inv_mass_FC = new TH1F("inv_mass_elec_tau_FC", TString::Format("Dilepton Invariant Mass from TauElectron in MC %s Failed Cuts",choice.c_str()), 500, 0, 150);
/*
TH1F* h_elec_iso_etcone20 = new TString::Format("elec_etcone20", "MC %s Electrons etcone20", 500, -20, 100);
TH1F* h_muon_iso_etcone20 = new TH1F("muon_etcone20", "MC %s Muons etcone20", 500, -20, 100);
TH1F* h_elec_iso_etcone20_FC = new TH1F("elec_etcone20_FC", "MC %s Electrons etcone20 Failed Cuts", 500, -2000, 100000);
TH1F* h_muon_iso_etcone20_FC = new TH1F("muon_etcone20_FC", "MC %s Muons etcone20 Failed Cuts", 500, -2000, 100000);

TH1F* h_elec_iso_ptcone30 = new TH1F("elec_ptcone30", "MC %s Electrons ptcone30", 500, -2000, 100000);
TH1F* h_muon_iso_ptcone30 = new TH1F("muon_ptcone30", "MC %s Muons ptcone30", 500, -2000, 100000);
TH1F* h_elec_iso_ptcone30_FC = new TH1F("elec_ptcone30_FC", "MC %s Electrons ptcone30 Failed Cuts", 500, -2000, 100000);
TH1F* h_muon_iso_ptcone30_FC = new TH1F("muon_ptcone30_FC", "MC %s Muons ptcone30 Failed Cuts", 500, -2000, 100000);
*/
TH1F* h_n_jets = new TH1F("n_jets", "MC %s Number of Jets", 500, 0, 0);

TH1F* h_ljet_0_pt = new TH1F("ljet_0_pt", "MC %s Leading Leptonic Jets pT", 500, 0, 0);
TH1F* h_ljet_0_eta = new TH1F("ljet_0_eta", "MC %s Leading Leptonic Jets Eta", 500, 0, 0);
TH1F* h_ljet_0_phi = new TH1F("ljet_0_phi", "MC %s Leading Leptonic Jets Phi", 500, 0, 0);

TH1F* h_bjet_0_pt = new TH1F("bjet_0_pt", "MC %s Leading b Jets pT", 500, 0, 0);
TH1F* h_bjet_0_eta = new TH1F("bjet_0_eta", "MC %s Leading b Jets Eta", 500, 0, 0);
TH1F* h_bjet_0_phi = new TH1F("bjet_0_phi", "MC %s Leading b Jets Phi", 500, 0, 0);

TH1F* h_ljet_inv_mass = new TH1F("ljet_inv_mass", "MC %s Leptonic Jets Invariant Mass", 500, 0, 1000);
TH1F* h_bjet_inv_mass = new TH1F("bjet_inv_mass", "MC %s b Jets Invariant Mass", 500, 0, 1000);
TH1F* h_ljet_inv_mass_FC = new TH1F("ljet_inv_mass_FC", "MC %s Leptonic Jets Invariant Mass Failed Cuts", 500, 0, 1000);
TH1F* h_bjet_inv_mass_FC = new TH1F("bjet_inv_mass_FC", "MC %s b Jets Invariant Mass Failed Cuts", 500, 0, 1000);
