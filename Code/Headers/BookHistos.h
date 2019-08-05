TH1F* h_lep_n = new TH1F("Lepton_no", "Number of Leptons", 10, -0.5, 9.5);

TH1F* h_elec_inv_mass = new TH1F("elec_inv_mass", "", 50, 0, 150);
TH1F* h_muon_inv_mass = new TH1F("muon_inv_mass", "", 50, 0, 150);

TH1F* h_elec_inv_mass_preselect = new TH1F("elec_inv_mass_preselect", "", 50, 0, 150);
TH1F* h_muon_inv_mass_preselect = new TH1F("muon_inv_mass_preselect", "", 50, 0, 150);

TH1F* h_elec_inv_mass_search = new TH1F("elec_inv_mass_search", "", 50, 0, 150);
TH1F* h_muon_inv_mass_search = new TH1F("muon_inv_mass_search", "", 50, 0, 150);

TH1F* h_elec_inv_mass_control = new TH1F("elec_inv_mass_control", "", 50, 0, 150);
TH1F* h_muon_inv_mass_control = new TH1F("muon_inv_mass_control", "", 50, 0, 150);

TH1F* h_elec_inv_mass_high_mass = new TH1F("elec_inv_mass_high_mass", "", 50, 0, 150);
TH1F* h_muon_inv_mass_high_mass = new TH1F("muon_inv_mass_high_mass", "", 50, 0, 150);

TH1F* h_elec_iso_etcone20 = new TH1F("elec_etcone20", "", 50, -20, 100);
TH1F* h_muon_iso_etcone20 = new TH1F("muon_etcone20", "", 50, -20, 100);

TH1F* h_elec_iso_ptcone30 = new TH1F("elec_ptcone30", "", 50, -2000, 100000);
TH1F* h_muon_iso_ptcone30 = new TH1F("muon_ptcone30", "", 50, -2000, 100000);

TH1F* h_n_jets = new TH1F("n_jets", "Number of Jets", 50, 0, 10);

TH1F* h_ljet_0_pt = new TH1F("ljet_0_pt", "", 50, 0, 1000);
TH1F* h_ljet_0_eta = new TH1F("ljet_0_eta", "", 50, -5, 5);
TH1F* h_ljet_0_phi = new TH1F("ljet_0_phi", "", 50, -4, 4);
TH1F* h_ljet_1_pt = new TH1F("ljet_1_pt", "", 50, 0, 1000);
TH1F* h_ljet_1_eta = new TH1F("ljet_1_eta", "", 50, -5, 5);
TH1F* h_ljet_1_phi = new TH1F("ljet_1_phi", "", 50, -4, 4);

TH1F* h_bjet_0_pt = new TH1F("bjet_0_pt", "Leading b Jets pT", 50, 0, 1000);
TH1F* h_bjet_0_eta = new TH1F("bjet_0_eta", "Leading b Jets Eta", 50, -5, 5);
TH1F* h_bjet_0_phi = new TH1F("bjet_0_phi", "Leading b Jets Phi", 50, -4, 4);

TH1F* h_ljet_inv_mass_preselect = new TH1F("ljet_inv_mass_preselect", "Leptonic Jets Invariant Mass", 50, 70, 4570);
TH1F* h_ljet_inv_mass = new TH1F("ljet_inv_mass", "Leptonic Jets Invariant Mass", 50, 70, 4570);
TH1F* h_ljet_inv_mass_search = new TH1F("ljet_inv_mass_search", "Leptonic Jets Invariant Mass", 50, 70, 4570);
TH1F* h_ljet_inv_mass_control = new TH1F("ljet_inv_mass_control", "Leptonic Jets Invariant Mass", 50, 70, 4570);
TH1F* h_ljet_inv_mass_high_mass = new TH1F("ljet_inv_mass_high_mass", "Leptonic Jets Invariant Mass", 50, 70, 4570);

TH1F* h_bjet_inv_mass = new TH1F("bjet_inv_mass", "b Jets Invariant Mass", 50, 0, 1000);

TH1F* h_lep_0_pt = new TH1F("lep_0_pt", "", 50, 0, 1000);
TH1F* h_lep_0_eta = new TH1F("lep_0_eta", "", 50, -5, 5);
TH1F* h_lep_0_phi = new TH1F("lep_0_phi", "", 50, -5, 5);
TH1F* h_lep_1_pt = new TH1F("lep_1_pt", "", 50, 0, 1000);
TH1F* h_lep_1_eta = new TH1F("lep_1_eta", "", 50, -5, 5);
TH1F* h_lep_1_phi = new TH1F("lep_1_phi", "", 50, -5, 5);

TH1F* h_Z_cent = new TH1F("Z_cent", "", 50, -10, 10);
TH1F* h_Z_cent_weight = new TH1F("Z_cent_weight", "", 50, -10, 10);
TH1F* h_Z_cent_preselect = new TH1F("Z_cent_preselect", "", 50, -10, 10);
TH1F* h_Z_cent_search = new TH1F("Z_cent_search", "", 50, -10, 10);
TH1F* h_Z_cent_control = new TH1F("Z_cent_control", "", 50, -10, 10);
TH1F* h_Z_cent_high_mass = new TH1F("Z_cent_high_mass", "", 50, -10, 10);

TH1F* h_ljet_delta_eta = new TH1F("ljet_delta_eta", "", 50, -10, 10);
TH1F* h_ljet_delta_eta_preselect = new TH1F("ljet_delta_eta_preselect", "", 50, -10, 10);
TH1F* h_ljet_delta_phi = new TH1F("ljet_delta_phi", "", 50, -10, 10);
TH1F* h_ljet_delta_R = new TH1F("ljet_delta_R", "", 50, 0, 10);
TH1F* h_ljet_delta_phi_preselect = new TH1F("ljet_delta_phi_preselect", "", 50, -10, 10);
TH1F* h_ljet_delta_R_preselect = new TH1F("ljet_delta_R_preselect", "", 50, 0, 10);

TH1F* h_lep_delta_eta = new TH1F("lep_delta_eta", "", 50, -10, 10);
TH1F* h_lep_delta_phi = new TH1F("lep_delta_phi", "", 50, -10, 10);
TH1F* h_lep_delta_R = new TH1F("lep_delta_R", "", 50, 0, 10);
TH1F* h_lep_delta_eta_preselect = new TH1F("lep_delta_eta_preselect", "", 50, -10, 10);
TH1F* h_lep_delta_phi_preselect = new TH1F("lep_delta_phi_preselect", "", 50, -10, 10);
TH1F* h_lep_delta_R_preselect = new TH1F("lep_delta_R_preselect", "", 50, 0, 10);
TH1F* h_lep_rapidity = new TH1F("lep_rapidity", "", 50, -5, 5);
TH1F* h_lep_delta_R_rap = new TH1F("lep_delta_R_rap", "", 50, 0, 10);

TH2F* h_lep_eta_L_SL_preselect = new TH2F("lep_eta_L_SL_preselect","", 50, -5, 5, 50, -5, 5);
TH2F* h_ljet_eta_L_SL_preselect = new TH2F("ljet_eta_L_SL_preselect","", 50, -5, 5, 50, -5, 5);
TH2F* h_ljet_eta_L_SL_2jets_preselect = new TH2F("ljet_eta_L_SL_2jets_preselect","",
                                            50, -5, 5, 50, -5, 5);
TH2F* h_lep_phi_L_SL_preselect = new TH2F("lep_phi_L_SL_preselect", "", 50, -5, 5, 50, -5, 5);
TH2F* h_ljet_phi_L_SL_preselect = new TH2F("ljet_phi_L_SL_preselect","", 50, -5, 5, 50, -5, 5);

TH1F* h_ljet_2_pt = new TH1F("ljet_2_pt", "", 50, 0, 1000);
TH1F* h_ljet_3_pt = new TH1F("ljet_3_pt", "", 50, 0, 1000);
TH1F* h_ljet_2_eta = new TH1F("ljet_2_eta", "", 50, -5, 5);
TH1F* h_ljet_3_eta = new TH1F("ljet_3_eta", "", 50, -5, 5);
TH1F* h_ljet_2_phi = new TH1F("ljet_2_phi", "", 50, -5, 5);
TH1F* h_ljet_3_phi = new TH1F("ljet_3_phi", "", 50, -5, 5);

TH1F* h_lep_eta_sum = new TH1F("lep_sum_eta", "", 50, -5, 5);
TH1F* h_ljet_eta_sum = new TH1F("ljet_sum_eta", "", 50, -5, 5);

TH1F* h_ljet_delta_eta_2 = new TH1F("ljet_delta_eta_2", "", 50, -10, 10);
TH1F* h_ljet_delta_eta_3 = new TH1F("ljet_delta_eta_3", "", 50, -10, 10);

TH1F* h_ljet_0_eta_2jets = new TH1F("ljet_0_eta_2jets", "", 50, -5, 5);
TH1F* h_ljet_1_eta_2jets = new TH1F("ljet_1_eta_2jets", "", 50, -5, 5);
TH1F* h_ljet_2_eta_2jets = new TH1F("ljet_2_eta_2jets", "", 50, -5, 5);
TH1F* h_ljet_3_eta_2jets = new TH1F("ljet_3_eta_2jets", "", 50, -5, 5);
TH1F* h_ljet_0_eta_3jets = new TH1F("ljet_0_eta_3jets", "", 50, -5, 5);
TH1F* h_ljet_1_eta_3jets = new TH1F("ljet_1_eta_3jets", "", 50, -5, 5);
TH1F* h_ljet_2_eta_3jets = new TH1F("ljet_2_eta_3jets", "", 50, -5, 5);
TH1F* h_ljet_3_eta_3jets = new TH1F("ljet_3_eta_3jets", "", 50, -5, 5);
TH1F* h_ljet_0_eta_4jets = new TH1F("ljet_0_eta_4jets", "", 50, -5, 5);
TH1F* h_ljet_1_eta_4jets = new TH1F("ljet_1_eta_4jets", "", 50, -5, 5);
TH1F* h_ljet_2_eta_4jets = new TH1F("ljet_2_eta_4jets", "", 50, -5, 5);
TH1F* h_ljet_3_eta_4jets = new TH1F("ljet_3_eta_4jets", "", 50, -5, 5);
TH1F* h_ljet_0_eta_5jets = new TH1F("ljet_0_eta_5jets", "", 50, -5, 5);
TH1F* h_ljet_1_eta_5jets = new TH1F("ljet_1_eta_5jets", "", 50, -5, 5);
TH1F* h_ljet_2_eta_5jets = new TH1F("ljet_2_eta_5jets", "", 50, -5, 5);
TH1F* h_ljet_3_eta_5jets = new TH1F("ljet_3_eta_5jets", "", 50, -5, 5);

TH1F* h_lep_pt_bal = new TH1F("lep_pt_bal", "", 50, 0, 7);

// Experimental
TH2F* h_delta_eta_pt_ll = new TH2F("delta_eta_pt_ll", "", 50, 0, 6, 50, 0, 1.5);
TH2F* h_delta_phi_pt_ll = new TH2F("delta_phi_pt_ll", "", 50, 0, 10, 50, 0, 1.5);

TH1F* h_met_reco_pt = new TH1F("met_reco_pt", "", 100, 0, 0);
TH1F* h_met_reco_phi = new TH1F("met_reco_phi", "", 100, 0, 0);
TH1F* h_met_reco_eta = new TH1F("met_reco_eta", "", 100, 0, 0);
