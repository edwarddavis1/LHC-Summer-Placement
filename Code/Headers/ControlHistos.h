// --------------------- INVARIANT MASS --------------------- //
h_lep_inv_mass_control->Fill(dilep_inv_mass);
if (lep_type == "Electron") {
    h_elec_inv_mass_control->Fill(dilep_inv_mass, lum_weight);
} if (lep_type == "Muon") {
    h_muon_inv_mass_control->Fill(dilep_inv_mass, lum_weight);
}
h_ljet_inv_mass_control->Fill(ljet_inv_mass, lum_weight);

h_lep_inv_mass_reco_control->Fill(lep_inv_mass_reco);

// ----------------------- Z BOSON -------------------------- //
h_Z_cent_control->Fill(Z_cent, lum_weight);
