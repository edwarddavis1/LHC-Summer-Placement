// --------------------- INVARIANT MASS --------------------- //
double dilep_inv_mass = InvariantMass(lep_0_p4, lep_1_p4);
if (lep_type == "Electron") {
    h_elec_inv_mass->Fill(dilep_inv_mass, lum_weight);
} if (lep_type == "Muon") {
    h_muon_inv_mass->Fill(dilep_inv_mass, lum_weight);
}
double ljet_inv_mass = InvariantMass(ljet_0_p4, ljet_1_p4);
h_ljet_inv_mass->Fill(ljet_inv_mass, lum_weight);
h_bjet_inv_mass->Fill(InvariantMass(bjet_0_p4, bjet_1_p4), lum_weight);

// ------------------------ CONES ----------------------------//
h_elec_iso_etcone20->Fill(elec_0_iso_etcone20, lum_weight);
h_muon_iso_etcone20->Fill(muon_0_iso_etcone20, lum_weight);

h_elec_iso_ptcone30->Fill(elec_0_iso_ptcone30, lum_weight);
h_muon_iso_ptcone30->Fill(muon_0_iso_ptcone30, lum_weight);

// ---------------------- KINEMATICS ------------------------ //
h_lep_0_pt->Fill(lep_0_pt, lum_weight);						// Leptons
h_lep_0_phi->Fill(lep_0_phi, lum_weight);
h_lep_0_eta->Fill(lep_0_eta, lum_weight);
h_lep_rapidity->Fill(lep_0_p4->Rapidity(), lum_weight);
h_lep_1_pt->Fill(lep_1_pt, lum_weight);
h_lep_1_phi->Fill(lep_1_phi, lum_weight);
h_lep_1_eta->Fill(lep_1_eta, lum_weight);
h_lep_rapidity->Fill(lep_1_p4->Rapidity(), lum_weight);
double pt_balance = PtBalance(lep_0_p4, lep_1_p4,
                                ljet_0_p4, ljet_1_p4);
h_lep_pt_bal->Fill(pt_balance, lum_weight);

h_ljet_0_pt->Fill(ljet_0_pt, lum_weight);					// Light Jets
h_ljet_0_eta->Fill(ljet_0_eta, lum_weight);
h_ljet_0_phi->Fill(ljet_0_phi, lum_weight);
h_ljet_1_pt->Fill(ljet_1_pt, lum_weight);
h_ljet_1_eta->Fill(ljet_1_eta, lum_weight);
h_ljet_1_phi->Fill(ljet_1_phi, lum_weight);

h_bjet_0_pt->Fill(bjet_0_pt, lum_weight);					// b Jets
h_bjet_0_eta->Fill(bjet_0_eta, lum_weight);
h_bjet_0_phi->Fill(bjet_0_phi, lum_weight);

h_lep_eta_sum->Fill(lep_0_eta + lep_1_eta, lum_weight);
h_ljet_eta_sum->Fill(ljet_0_eta + ljet_1_eta, lum_weight);

// angular separation
h_ljet_delta_eta->Fill(ljet_0_eta - ljet_1_eta, lum_weight);
h_lep_delta_eta->Fill(lep_0_eta - lep_1_eta, lum_weight);
h_ljet_delta_phi->Fill(ljet_0_phi - ljet_1_phi, lum_weight);
h_lep_delta_phi->Fill(lep_0_phi - lep_1_phi, lum_weight);
h_ljet_delta_R->Fill(DeltaR(ljet_0_p4,ljet_1_p4), lum_weight);
h_lep_delta_R->Fill(DeltaR(lep_0_p4,lep_1_p4), lum_weight);

// ------------------------- JETS --------------------------- //
h_n_jets->Fill(n_jets);

if (ljet_2) {
h_ljet_2_eta->Fill(ljet_2_eta, lum_weight);
h_ljet_2_phi->Fill(ljet_2_phi, lum_weight);
h_ljet_delta_eta_2->Fill(ljet_1_eta - ljet_2_eta, lum_weight);
}
if (ljet_3) {
h_ljet_3_eta->Fill(ljet_3_eta, lum_weight);
h_ljet_3_phi->Fill(ljet_3_phi, lum_weight);
h_ljet_delta_eta_3->Fill(ljet_2_eta - ljet_3_eta, lum_weight);
}

if (n_jets == 2) {
    h_ljet_0_eta_2jets->Fill(ljet_0_eta, lum_weight);
    h_ljet_1_eta_2jets->Fill(ljet_1_eta, lum_weight);
}
if (n_jets == 3) {
    h_ljet_0_eta_3jets->Fill(ljet_0_eta, lum_weight);
    h_ljet_1_eta_3jets->Fill(ljet_1_eta, lum_weight);
    h_ljet_2_eta_3jets->Fill(ljet_2_eta, lum_weight);
}
if (n_jets == 4) {
    h_ljet_0_eta_4jets->Fill(ljet_0_eta, lum_weight);
    h_ljet_1_eta_4jets->Fill(ljet_1_eta, lum_weight);
    h_ljet_2_eta_4jets->Fill(ljet_2_eta, lum_weight);
    h_ljet_3_eta_4jets->Fill(ljet_3_eta, lum_weight);
}
if (n_jets == 5) {
    h_ljet_0_eta_5jets->Fill(ljet_0_eta, lum_weight);
    h_ljet_1_eta_5jets->Fill(ljet_1_eta, lum_weight);
    h_ljet_2_eta_5jets->Fill(ljet_2_eta, lum_weight);
    h_ljet_3_eta_5jets->Fill(ljet_3_eta, lum_weight);
}

// ----------------------- Z BOSON -------------------------- //
double Z_cent = Centrality(lep_0_p4, lep_1_p4,
                            ljet_0_p4, ljet_1_p4);
h_Z_cent->Fill(Z_cent, lum_weight);
// h_Z_cent_weight->Fill(Z_cent, lum_weight);


h_met_reco_pt->Fill(met_reco_p4->Pt(), lum_weight);
h_met_reco_phi->Fill(met_reco_p4->Phi(), lum_weight);
h_met_reco_eta->Fill(met_reco_p4->Eta(), lum_weight);
