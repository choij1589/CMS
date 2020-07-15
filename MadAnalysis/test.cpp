#include <vector>

void test() {
	TFile* sr1 = new TFile("test_SR1_go200.root");
	TFile* sr2 = new TFile("test_SR2_go500.root");
	TFile* sr3 = new TFile("test_SR3_go900.root");
	TFile* sr4 = new TFile("test_SR4_go1600.root");

	TTree* tr1 = (TTree*)sr1->Get("SR_1");
	TTree* tr2 = (TTree*)sr2->Get("SR_2");
	TTree* tr3 = (TTree*)sr3->Get("SR_3");
	TTree* tr4 = (TTree*)sr4->Get("SR_4");

	//==== create new TFile to store data ====
	TFile* f = new TFile("TripletMass.root", "recreate");
	f->cd();

	TTree* t1 = new TTree("tripletM_SR1", "");
	TTree* t2 = new TTree("tripletM_SR2", "");
	TTree* t3 = new TTree("tripletM_SR3", "");
	TTree* t4 = new TTree("tripletM_SR4", "");

	vector<double>* mass1=0;
	//mass2, mass3, mass4;
	vector<double>* gen_mass1=0;
	vector<double>* gen_mass3=0;
	//gen_mass2, gen_mass3, gen_mass4;
	//cout << &mass1 << endl;
	tr1->SetBranchAddress("tripletM", &mass1);
	//tr2->SetBranchAddress("tripletM", &mass2);
	//tr3->SetBranchAddress("tripletM", &mass3);
	//tr4->SetBranchAddress("tripletM", &mass4);
	tr1->SetBranchAddress("gen_tripletM", &gen_mass1);
	//tr2->SetBranchAddress("gen_tripletM", &gen_mass2);
	tr3->SetBranchAddress("gen_tripletM", &gen_mass3);
	//tr4->SetBranchAddress("gen_tripletM", &gen_mass4);

	double m1, gen_m1;
	t1->Branch("tripletM", &m1);
	t1->Branch("gen_tripletM", &gen_m1);

	for (int i = 0; i < tr1->GetEntries(); i++) {
		tr1->GetEntry(i);
		
		for (unsigned int i = 0; i < mass1->size(); ++i) {
			m1 = mass1->at(i);
			if (i < gen_mass1->size()) gen_m1 = gen_mass1->at(i);
			t1->Fill();
		}
	}

	double gen_m3;
	t3->Branch("gen_tripletM", &gen_m3);
	for (int i = 0; i < tr3->GetEntries(); i++) {
		tr3->GetEntry(i);

		for (unsigned int i = 0; i < gen_mass3->size(); i++) {
			gen_m3 = gen_mass3->at(i);
			t3->Fill();
		}
	}
	t1->Write();
	t3->Write();
	f->Close();
}
