// --------------------- INVARIANT MASS --------------------- //
double dilep_inv_mass = InvariantMass(lep_0_p4, lep_1_p4);
if (lep_type == "Electron") {
    h_elec_inv_mass_preselect->Fill(dilep_inv_mass);
} if (lep_type == "Muon") {
    h_muon_inv_mass_preselect->Fill(dilep_inv_mass);
}
h_ljet_inv_mass->Fill(InvariantMass(ljet_0_p4, ljet_1_p4));
h_bjet_inv_mass->Fill(InvariantMass(bjet_0_p4, bjet_1_p4));

// ------------------------ CONES ----------------------------//
h_elec_iso_etcone20->Fill(elec_0_iso_etcone20);
h_muon_iso_etcone20->Fill(muon_0_iso_etcone20);

h_elec_iso_ptcone30->Fill(elec_0_iso_ptcone30);
h_muon_iso_ptcone30->Fill(muon_0_iso_ptcone30);

// ----------------------- Z BOSON -------------------------- //
double Z_cent_preselect = Centrality(lep_0_p4, lep_1_p4,
                                    ljet_0_p4, ljet_1_p4);
h_Z_cent_preselect->Fill(Z_cent_preselect);

// ---------------------- KINEMATICS ------------------------ //
h_ljet_delta_eta_preselect->Fill(ljet_0_eta - ljet_1_eta);
h_lep_delta_eta_preselect->Fill(lep_0_eta - lep_1_eta);
h_ljet_delta_phi_preselect->Fill(ljet_0_phi - ljet_1_phi);
h_lep_delta_phi_preselect->Fill(lep_0_phi - lep_1_phi);
h_ljet_delta_R_preselect->Fill(DeltaR(ljet_0_p4,ljet_1_p4));
h_lep_delta_R_preselect->Fill(DeltaR(lep_0_p4,lep_1_p4));

// 2D Plots
h_lep_eta_L_SL->Fill(lep_0_eta, lep_1_eta);
h_lep_phi_L_SL->Fill(lep_0_phi, lep_1_phi);
h_ljet_eta_L_SL->Fill(ljet_0_eta, ljet_1_eta);
h_ljet_phi_L_SL->Fill(ljet_0_phi, ljet_1_phi);

h_lep_n->Fill(n_leptons);

// ----------------------- Z BOSON -------------------------- //
double Z_cent = Centrality(lep_0_p4, lep_1_p4,
                            ljet_0_p4, ljet_1_p4);
h_Z_cent_preselect->Fill(Z_cent);
