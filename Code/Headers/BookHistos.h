TH1F* h_lep_n = new TH1F("Lepton_no", "Number of Leptons", 10, -0.5, 9.5);

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

TH1F* h_elec_iso_etcone20 = new TH1F("elec_etcone20", TString::Format("MC %s Electrons etcone20",choice.c_str()), 500, -20, 100);
TH1F* h_muon_iso_etcone20 = new TH1F("muon_etcone20", TString::Format("MC %s Muons etcone20",choice.c_str()), 500, -20, 100);
TH1F* h_elec_iso_etcone20_FC = new TH1F("elec_etcone20_FC", TString::Format("MC %s Electrons etcone20 Failed Cuts",choice.c_str()), 500, -2000, 100000);
TH1F* h_muon_iso_etcone20_FC = new TH1F("muon_etcone20_FC", TString::Format("MC %s Muons etcone20 Failed Cuts",choice.c_str()), 500, -2000, 100000);

TH1F* h_elec_iso_ptcone30 = new TH1F("elec_ptcone30", TString::Format("MC %s Electrons ptcone30",choice.c_str()), 500, -2000, 100000);
TH1F* h_muon_iso_ptcone30 = new TH1F("muon_ptcone30", TString::Format("MC %s Muons ptcone30",choice.c_str()), 500, -2000, 100000);
TH1F* h_elec_iso_ptcone30_FC = new TH1F("elec_ptcone30_FC", TString::Format("MC %s Electrons ptcone30 Failed Cuts",choice.c_str()), 500, -2000, 100000);
TH1F* h_muon_iso_ptcone30_FC = new TH1F("muon_ptcone30_FC", TString::Format("MC %s Muons ptcone30 Failed Cuts",choice.c_str()), 500, -2000, 100000);

TH1F* h_n_jets = new TH1F("n_jets", TString::Format("MC %s Number of Jets",choice.c_str()), 500, 0, 10);

TH1F* h_ljet_0_pt = new TH1F("ljet_0_pt", TString::Format("MC %s Leading Leptonic Jets pT",choice.c_str()), 500, 0, 1000);
TH1F* h_ljet_0_eta = new TH1F("ljet_0_eta", TString::Format("MC %s Leading Leptonic Jets Eta",choice.c_str()), 500, -5, 5);
TH1F* h_ljet_0_phi = new TH1F("ljet_0_phi", TString::Format("MC %s Leading Leptonic Jets Phi",choice.c_str()), 500, -4, 4);

TH1F* h_bjet_0_pt = new TH1F("bjet_0_pt", TString::Format("MC %s Leading b Jets pT",choice.c_str()), 500, 0, 1000);
TH1F* h_bjet_0_eta = new TH1F("bjet_0_eta", TString::Format("MC %s Leading b Jets Eta",choice.c_str()), 500, -5, 5);
TH1F* h_bjet_0_phi = new TH1F("bjet_0_phi", TString::Format("MC %s Leading b Jets Phi",choice.c_str()), 500, -4, 4);

TH1F* h_ljet_inv_mass = new TH1F("ljet_inv_mass", TString::Format("MC %s Leptonic Jets Invariant Mass",choice.c_str()), 500, 0, 1000);
TH1F* h_bjet_inv_mass = new TH1F("bjet_inv_mass", TString::Format("MC %s b Jets Invariant Mass",choice.c_str()), 500, 0, 1000);
TH1F* h_ljet_inv_mass_FC = new TH1F("ljet_inv_mass_FC", TString::Format("MC %s Leptonic Jets Invariant Mass Failed Cuts",choice.c_str()), 500, 0, 1000);
TH1F* h_bjet_inv_mass_FC = new TH1F("bjet_inv_mass_FC", TString::Format("MC %s b Jets Invariant Mass Failed Cuts",choice.c_str()), 500, 0, 1000);

TH1F* h_lep_pt = new TH1F("lep_pt", TString::Format("Transverse Momentum from Leptons in MC %s",choice.c_str()), 500, 0, 1000);
TH1F* h_lep_eta = new TH1F("lep_eta", TString::Format("Pseudorapidity from Leptons in MC %s",choice.c_str()), 500, -5, 5);
TH1F* h_lep_phi = new TH1F("lep_phi", TString::Format("Phi from Leptons in MC %s",choice.c_str()), 500, -5, 5);
TH1F* h_elec_pt = new TH1F("elec_pt", TString::Format("Transverse Momenta from Electron in MC %s",choice.c_str()), 500, 0, 1000);
TH1F* h_elec_eta = new TH1F("elec_eta", TString::Format("Pseudorapidity from Electron in MC %s",choice.c_str()), 500, -5, 5);
TH1F* h_elec_phi = new TH1F("elec_phi", TString::Format("Phi from Electron in MC %s",choice.c_str()), 500, -4, 4);
