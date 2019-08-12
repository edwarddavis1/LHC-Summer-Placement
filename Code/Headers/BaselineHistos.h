// --------------------- INVARIANT MASS --------------------- //
if (lep_type == "Electron") h_elec_inv_mass->Fill(dilep_inv_mass);
if (lep_type == "Muon") h_muon_inv_mass->Fill(dilep_inv_mass);
h_lep_inv_mass->Fill(dilep_inv_mass);
h_ljet_inv_mass->Fill(ljet_inv_mass);
h_bjet_inv_mass->Fill(bjet_inv_mass);

h_lep_inv_mass_reco->Fill(lep_inv_mass_reco);
// ------------------------ CONES ----------------------------//
h_elec_iso_etcone20->Fill(elec_0_iso_etcone20);
h_muon_iso_etcone20->Fill(muon_0_iso_etcone20);

h_elec_iso_ptcone30->Fill(elec_0_iso_ptcone30);
h_muon_iso_ptcone30->Fill(muon_0_iso_ptcone30);

// ---------------------- KINEMATICS ------------------------ //
h_lep_0_pt->Fill(lep_0_pt);						// Leptons
h_lep_0_phi->Fill(lep_0_phi);
h_lep_0_eta->Fill(lep_0_eta);
h_lep_rapidity->Fill(lep_0_p4->Rapidity());
h_lep_1_pt->Fill(lep_1_pt);
h_lep_1_phi->Fill(lep_1_phi);
h_lep_1_eta->Fill(lep_1_eta);
h_lep_rapidity->Fill(lep_1_p4->Rapidity());
h_lep_pt_bal->Fill(pt_balance);

h_ljet_0_pt->Fill(ljet_0_pt);					// Light Jets
h_ljet_0_eta->Fill(ljet_0_eta);
h_ljet_0_phi->Fill(ljet_0_phi);
h_ljet_1_pt->Fill(ljet_1_pt);
h_ljet_1_eta->Fill(ljet_1_eta);
h_ljet_1_phi->Fill(ljet_1_phi);

h_bjet_0_pt->Fill(bjet_0_pt);					// b Jets
h_bjet_0_eta->Fill(bjet_0_eta);
h_bjet_0_phi->Fill(bjet_0_phi);

h_lep_eta_sum->Fill(lep_0_eta + lep_1_eta);
h_ljet_eta_sum->Fill(ljet_0_eta + ljet_1_eta);

// angular separation
h_ljet_delta_eta->Fill(ljet_0_eta - ljet_1_eta);
h_lep_delta_eta->Fill(lep_0_eta - lep_1_eta);
h_ljet_delta_phi->Fill(ljet_0_phi - ljet_1_phi);
h_lep_delta_phi->Fill(lep_0_phi - lep_1_phi);
h_ljet_delta_R->Fill(ljet_delta_R);
h_lep_delta_R->Fill(lep_delta_R);

// ------------------------- JETS --------------------------- //
h_n_jets->Fill(n_jets);

if (ljet_2) {
h_ljet_2_eta->Fill(ljet_2_eta);
h_ljet_2_phi->Fill(ljet_2_phi);
h_ljet_delta_eta_2->Fill(ljet_1_eta - ljet_2_eta);
}
if (ljet_3) {
h_ljet_3_eta->Fill(ljet_3_eta);
h_ljet_3_phi->Fill(ljet_3_phi);
h_ljet_delta_eta_3->Fill(ljet_2_eta - ljet_3_eta);
}

if (n_jets == 2) {
    h_ljet_0_eta_2jets->Fill(ljet_0_eta);
    h_ljet_1_eta_2jets->Fill(ljet_1_eta);
}
if (n_jets == 3) {
    h_ljet_0_eta_3jets->Fill(ljet_0_eta);
    h_ljet_1_eta_3jets->Fill(ljet_1_eta);
    h_ljet_2_eta_3jets->Fill(ljet_2_eta);
}
if (n_jets == 4) {
    h_ljet_0_eta_4jets->Fill(ljet_0_eta);
    h_ljet_1_eta_4jets->Fill(ljet_1_eta);
    h_ljet_2_eta_4jets->Fill(ljet_2_eta);
    h_ljet_3_eta_4jets->Fill(ljet_3_eta);
}
if (n_jets == 5) {
    h_ljet_0_eta_5jets->Fill(ljet_0_eta);
    h_ljet_1_eta_5jets->Fill(ljet_1_eta);
    h_ljet_2_eta_5jets->Fill(ljet_2_eta);
    h_ljet_3_eta_5jets->Fill(ljet_3_eta);
}

// ----------------------- Z BOSON -------------------------- //
h_Z_cent->Fill(Z_cent);
