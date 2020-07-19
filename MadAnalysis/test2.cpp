void test2() {
	TFile* sr3 = new TFile("test_SR3_go900.root");

	TTree* tr3 = (TTree*)sr3->Get("SR_3");

	TFile* f = new TFile("out.root", "recreate");
	f->cd();

	TTree* t3 = new TTree("tripletM_SR3", "");

	vector<double>* p_mass3=0;
	tr3->SetBranchAddress("tripletM", &p_mass3);

	double m3;
	t3->Branch("tripletM", &m3);
	//t3->Branch("gen_tripletM", &gen_m3);
	//
	for (unsigned int i = 0; i < tr3->GetEntries(); i++) {
		tr3->GetEntry(i);
		for (unsigned int it = 0; it < p_mass3->size(); it++) {
			//cout << p_mass3->at(it) << " ";
			m3 = p_mass3->at(it);
			t3->Fill();
		}
		cout << endl;
	}
	
	f->cd();
	t3->Write();
	f->Close();
}

	
