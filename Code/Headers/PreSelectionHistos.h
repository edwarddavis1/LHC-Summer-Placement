// --------------------- INVARIANT MASS --------------------- //
h_lep_inv_mass_preselect->Fill(dilep_inv_mass);
if (lep_type == "Electron") {
    h_elec_inv_mass_preselect->Fill(dilep_inv_mass);
} if (lep_type == "Muon") {
    h_muon_inv_mass_preselect->Fill(dilep_inv_mass);
}
h_ljet_inv_mass_preselect->Fill(ljet_inv_mass);

h_lep_inv_mass_reco_preselect->Fill(lep_inv_mass_reco);

// ----------------------- Z BOSON -------------------------- //
h_Z_cent_preselect->Fill(Z_cent_preselect);

// ---------------------- KINEMATICS ------------------------ //
h_ljet_delta_eta_preselect->Fill(ljet_0_eta - ljet_1_eta);
h_lep_delta_eta_preselect->Fill(lep_0_eta - lep_1_eta);
h_ljet_delta_phi_preselect->Fill(ljet_0_phi - ljet_1_phi);
h_lep_delta_phi_preselect->Fill(lep_0_phi - lep_1_phi);
h_ljet_delta_R_preselect->Fill(DeltaR(ljet_0_p4,ljet_1_p4));
h_lep_delta_R_preselect->Fill(DeltaR(lep_0_p4,lep_1_p4));

// 2D Plots
h_lep_eta_L_SL_preselect->Fill(lep_0_eta, lep_1_eta);
h_lep_phi_L_SL_preselect->Fill(lep_0_phi, lep_1_phi);
h_ljet_eta_L_SL_preselect->Fill(ljet_0_eta, ljet_1_eta);
h_ljet_phi_L_SL_preselect->Fill(ljet_0_phi, ljet_1_phi);
if (n_jets == 2) h_ljet_eta_L_SL_2jets_preselect->Fill(ljet_0_eta, ljet_1_eta);

h_lep_n->Fill(n_leptons);

// Experimental
h_delta_eta_pt_ll->Fill(abs(lep_0_eta - lep_1_eta), pt_balance);
h_delta_phi_pt_ll->Fill(abs(lep_0_phi - lep_1_phi), pt_balance);
