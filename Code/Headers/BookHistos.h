TH1F* h_lep_n = new TH1F("Lepton_no", "Number of Leptons", 10, -0.5, 9.5);

TH1F* h_lep_type = new TH1F("lep_type", "Lepton Type", 5, 0, 5);

TH1F* h_elec_pt = new TH1F("Electron_pt", "Electron pT in MC Zmm2jets", 500, 0, 500);	
TH1F* h_muon_pt = new TH1F("Muon_pt", "Muon pT in MC Zmm2jets", 500, 0, 500);
TH1F* h_tau_pt = new TH1F("Tau_pt", "Tau pT in MC Zmm2jets", 500, 0, 500);
TH1F* h_elec_pt_FC = new TH1F("Electron_pt_FC", "Electron pT in MC Zmm2jets Failed Cuts", 500, 0, 500);	
TH1F* h_muon_pt_FC = new TH1F("Muon_pt_FC", "Muon pT in MC Zmm2jets Failed Cuts", 500, 0, 500);
TH1F* h_tau_pt_FC = new TH1F("Tau_pt_FC", "Tau pT in MC Zmm2jets Failed Cuts", 500, 0, 500);

TH1F* h_elec_inv_mass = new TH1F("inv_mass_elec", "Dilepton Invariant Mass from Electrons in MC Zmm2jets", 500, 0, 150);	
TH1F* h_muon_inv_mass = new TH1F("inv_mass_muon", "Dilepton Invariant Mass from Muons in MC Zmm2jets", 500, 0, 150);
TH1F* h_tau_inv_mass = new TH1F("inv_mass_tau", "Dilepton Invariant Mass from Tauons in MC Zmm2jets", 500, 0, 150);
TH1F* h_elec_inv_mass_FC = new TH1F("inv_mass_elec_FC", "Dilepton Invariant Mass from Electrons in MC Zmm2jets Failed Cuts", 500, 0, 150);	
TH1F* h_muon_inv_mass_FC = new TH1F("inv_mass_muon_FC", "Dilepton Invariant Mass from Muons in MC Zmm2jets Failed Cuts", 500, 0, 150);
TH1F* h_tau_inv_mass_FC = new TH1F("inv_mass_tau_FC", "Dilepton Invariant Mass from Tauons in MC Zmm2jets Failed Cuts", 500, 0, 150);

TH1F* h_elec_iso_etcone20 = new TH1F("elec_etcone20", "MC Zmm2jets Electrons etcone20", 500, -20, 100);
TH1F* h_muon_iso_etcone20 = new TH1F("muon_etcone20", "MC Zmm2jets Muons etcone20", 500, -20, 100);
TH1F* h_elec_iso_etcone20_FC = new TH1F("elec_etcone20_FC", "MC Zmm2jets Electrons etcone20 Failed Cuts", 500, -2000, 100000);
TH1F* h_muon_iso_etcone20_FC = new TH1F("muon_etcone20_FC", "MC Zmm2jets Muons etcone20 Failed Cuts", 500, -2000, 100000);

TH1F* h_elec_iso_ptcone30 = new TH1F("elec_ptcone30", "MC Zmm2jets Electrons ptcone30", 500, -2000, 100000);
TH1F* h_muon_iso_ptcone30 = new TH1F("muon_ptcone30", "MC Zmm2jets Muons ptcone30", 500, -2000, 100000);
TH1F* h_elec_iso_ptcone30_FC = new TH1F("elec_ptcone30_FC", "MC Zmm2jets Electrons ptcone30 Failed Cuts", 500, -2000, 100000);
TH1F* h_muon_iso_ptcone30_FC = new TH1F("muon_ptcone30_FC", "MC Zmm2jets Muons ptcone30 Failed Cuts", 500, -2000, 100000);

TH1F* h_n_jets = new TH1F("n_jets", "MC Zmm2jets Number of Jets", 500, 0, 0);

TH1F* h_ljet_0_pt = new TH1F("ljet_0_pt", "MC Zmm2jets Leading Leptonic Jets pT", 500, 0, 0);
TH1F* h_ljet_0_eta = new TH1F("ljet_0_eta", "MC Zmm2jets Leading Leptonic Jets Eta", 500, 0, 0);
TH1F* h_ljet_0_phi = new TH1F("ljet_0_phi", "MC Zmm2jets Leading Leptonic Jets Phi", 500, 0, 0);

TH1F* h_bjet_0_pt = new TH1F("bjet_0_pt", "MC Zmm2jets Leading b Jets pT", 500, 0, 0);
TH1F* h_bjet_0_eta = new TH1F("bjet_0_eta", "MC Zmm2jets Leading b Jets Eta", 500, 0, 0);
TH1F* h_bjet_0_phi = new TH1F("bjet_0_phi", "MC Zmm2jets Leading b Jets Phi", 500, 0, 0);

TH1F* h_ljet_inv_mass = new TH1F("ljet_inv_mass", "MC Zmm2jets Leptonic Jets Invariant Mass", 500, 0, 1000);
TH1F* h_bjet_inv_mass = new TH1F("bjet_inv_mass", "MC Zmm2jets b Jets Invariant Mass", 500, 0, 1000);
TH1F* h_ljet_inv_mass_FC = new TH1F("ljet_inv_mass_FC", "MC Zmm2jets Leptonic Jets Invariant Mass Failed Cuts", 500, 0, 1000);
TH1F* h_bjet_inv_mass_FC = new TH1F("bjet_inv_mass_FC", "MC Zmm2jets b Jets Invariant Mass Failed Cuts", 500, 0, 1000);
