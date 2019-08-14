//------------------- RECONSTRUCTION CALCULATIONS --------------------//

// Missing transverse momentum centrality
double MET_Centrality = METCentrality(met_reco_p4, lep_0_p4, lep_1_p4);

// InorOut = true means the E_t is outside of the phi interval
// Change these to TLorentzVector as needed for Z boson mass
// reconstruction
double Et_along_0;
double Et_along_1;

// calculate the lepton mass favour (whether a lepton points more
// towards the hadronic tau or the leptonic tau
double MET_Type_Favour = METTypeFavour(met_reco_p4, lep_0_p4, lep_1_p4);

// vector which cnntains the neutrino transverse momentum vectors
vector<double> neutrino_momenta;

// Stores the momenta of the neutrinos pointed along lepton 0 and
// lepton 1
double neutrino_0_x_p, neutrino_0_y_p, neutrino_0_z_p;
double neutrino_1_x_p, neutrino_1_y_p, neutrino_1_z_p;

// is the missing energy inside or outside the lepton phi interval?
bool outside_leptons = PhiIntervalInOrOut(lep_0_p4, lep_1_p4,
                                            met_reco_p4);

// if OUTSIDE
// outside the phi interval so need to see which one it favours
if (outside_leptons) {

    // want to calcualate which tau it is closer to and find Et
    // component along that tau vector.
    // Closer to lep_0 aka TRUE
    if (ETFavourCalc(lep_0_p4, lep_1_p4, met_reco_p4 )) {

        // Et_along_0 should be TLorentzVector along lep_0
        // Et along a
        Et_along_0 = ETalongVectorCalc(lep_0_p4, met_reco_p4);
        Et_along_1 = 0;

        // neutrino 1
        neutrino_0_x_p = x_component_pT(Et_along_0, lep_0_p4);
        neutrino_0_y_p = y_component_pT(Et_along_0, lep_0_p4);
        neutrino_0_z_p = p_z_neutrino_calc(Et_along_0, lep_0_p4);

        // neutrino 2
        neutrino_1_x_p = 0;
        neutrino_1_y_p = 0;
        neutrino_1_z_p = 0;


    }
    else { // closer to lep_1 aka FALSE
        // Et_along_1 should be TLorentzVector along lep_1
        Et_along_1 = ETalongVectorCalc(lep_1_p4, met_reco_p4);
        Et_along_0 = 0;

        // neutrino 1
        neutrino_0_x_p = 0;
        neutrino_0_y_p = 0;
        neutrino_0_z_p = 0;

        // neutrino 2
        neutrino_1_x_p = x_component_pT(Et_along_1, lep_1_p4);
        neutrino_1_y_p = y_component_pT(Et_along_1, lep_1_p4);
        neutrino_1_z_p = p_z_neutrino_calc(Et_along_1, lep_1_p4);

    }
}
// else INSIDE
else { // normal "inside" the phi interval gap

    // neutrino transverse momentum
    neutrino_momenta = pTneutrinovector_calc(lep_0_p4, lep_1_p4,
                                                met_reco_p4);
    double neutrino_0_pt = abs(neutrino_momenta[0]);
    double neutrino_1_pt = abs(neutrino_momenta[1]);

    neutrino_0_x_p = x_component_pT(neutrino_0_pt, lep_0_p4);
    neutrino_0_y_p = y_component_pT(neutrino_0_pt, lep_0_p4);
    neutrino_0_z_p = p_z_neutrino_calc(neutrino_0_pt, lep_0_p4);

    neutrino_1_x_p = x_component_pT(neutrino_1_pt, lep_1_p4);
    neutrino_1_y_p = y_component_pT(neutrino_1_pt, lep_1_p4);
    neutrino_1_z_p = p_z_neutrino_calc(neutrino_1_pt, lep_1_p4);

}
// TLorentzVector (TLV) 4 momentum px,py,pz,E (E=p_tot) of neutrino 1
TLorentzVector* neutrino_0_TLV = neutrino_TLV(neutrino_0_x_p,
                                                neutrino_0_y_p,
                                                neutrino_0_z_p);
// TLorentzVector (TLV) 4 momentum px,py,pz,E (E=p_tot) of neutrino 2
TLorentzVector* neutrino_1_TLV = neutrino_TLV(neutrino_1_x_p,
                                                neutrino_1_y_p,
                                                neutrino_1_z_p);

// reconstruct tau candidate with tau lepton and neutrino
lep_0_reco_p4 = merge_two_TLV(lep_0_p4, neutrino_0_TLV);
lep_1_reco_p4 = merge_two_TLV(lep_1_p4, neutrino_1_TLV);

double lep_inv_mass_reco = InvariantMass(lep_0_reco_p4, lep_1_reco_p4);


double lep_no = n_electrons + n_muons + n_taus;

double lep_inv_mass = InvariantMass(lep_0_p4, lep_1_p4);
double ljet_inv_mass = InvariantMass(ljet_0_p4, ljet_1_p4);
double bjet_inv_mass = InvariantMass(bjet_0_p4, bjet_1_p4);

double lep_pt_balance = PtBalance(lep_0_p4, lep_1_p4,
                                ljet_0_p4, ljet_1_p4);
double lep_pt_balance_reco = PtBalance(lep_0_reco_p4, lep_1_reco_p4,
                                ljet_0_p4, ljet_1_p4);

double lep_delta_eta = lep_0_eta - lep_1_eta;
double ljet_delta_eta = ljet_0_eta - ljet_1_eta;
double ljet_2_delta_eta = ljet_1_eta - ljet_2_eta;
double ljet_3_delta_eta = ljet_2_eta - ljet_3_eta;
double lep_delta_phi = lep_0_phi - lep_1_phi;
double ljet_delta_phi = ljet_0_phi - ljet_1_phi;
double lep_delta_R = DeltaR(lep_0_p4,lep_1_p4);
double ljet_delta_R = DeltaR(ljet_0_p4,ljet_1_p4);

double lep_eta_sum = lep_0_eta + lep_1_eta;
double ljet_eta_sum = ljet_0_eta + ljet_1_eta;

double Z_centrality = Centrality(lep_0_p4, lep_1_p4,
                            ljet_0_p4, ljet_1_p4);
