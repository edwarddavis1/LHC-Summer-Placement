// --------------------- INVARIANT MASS --------------------- //
double dilep_inv_mass = InvariantMass(lep_0_p4, lep_1_p4);
if (lep_type == "Electron") {
    h_elec_inv_mass_high_mass->Fill(dilep_inv_mass);
} if (lep_type == "Muon") {
    h_muon_inv_mass_high_mass->Fill(dilep_inv_mass);
}

// ----------------------- Z BOSON -------------------------- //
double Z_cent = Centrality(lep_0_p4, lep_1_p4,
                            ljet_0_p4, ljet_1_p4);
h_Z_cent_high_mass->Fill(Z_cent);
