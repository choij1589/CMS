#include <string>

void Macro() {
	vector<TFile*> files;
	for (unsigned int i = 0; i < 4; i++) {
		string mass;
		if (i == 0) mass = "200";
		else if (i == 1) mass = "500";
		else if (i == 2) mass = "900";
		else if (i == 3) mass = "1600";
		TString filename = "test_SR" + to_string(i+1) + "_go" + mass + ".root";
		TFile* f = new TFile(filename);

		files.push_back(f);
	}

	//===== Get histograms for sr1 =====
	vector<TH1D*> jet_pt1;
	for (unsigned int i = 0; i < 10; i++) {
		TString histname = "jet_pt_" + to_string(i+1) + "_1";
		TH1D* h = (TH1D*) files.at(0)->Get(histname);
		jet_pt1.push_back(h);
	}
	jet_pt1.at(0)->GetXaxis()->SetRangeUser(0, 1000);
	jet_pt1.at(0)->GetYaxis()->SetRangeUser(0, 1100);
	jet_pt1.at(0)->SetStats(0);

	jet_pt1.at(0)->GetXaxis()->SetTitle("p_T (GeV)");
	jet_pt1.at(0)->GetYaxis()->SetTitle("Event / GeV");
	jet_pt1.at(0)->GetXaxis()->SetTitleOffset(1.1);
	jet_pt1.at(0)->GetYaxis()->SetTitleOffset(1.2);
	jet_pt1.at(0)->SetTitle("SR1");
	//jet_pt1.at(0)->Draw();
	//for (unsigned int i = 0; i < 10; i++) {
	//	jet_pt1.at(i)->Draw("same");
	//}
	
	//===== Get histograms for sr2 =====
	vector<TH1D*> jet_pt2;
	for (unsigned int i = 0; i < 10; i++) {
		TString histname = "jet_pt_" + to_string(i+1) + "_2";
		TH1D* h = (TH1D*) files.at(1)->Get(histname);
		jet_pt2.push_back(h);
	}
	jet_pt2.at(0)->GetXaxis()->SetRangeUser(0, 1500);
	jet_pt2.at(0)->GetYaxis()->SetRangeUser(0, 2700);
	jet_pt2.at(0)->SetStats(0);

	jet_pt2.at(0)->GetXaxis()->SetTitle("p_T (GeV)");
	jet_pt2.at(0)->GetYaxis()->SetTitle("Event / GeV");
	jet_pt2.at(0)->GetXaxis()->SetTitleOffset(1.1);
	jet_pt2.at(0)->GetYaxis()->SetTitleOffset(1.2);
	jet_pt2.at(0)->SetTitle("SR2");
	//jet_pt2.at(0)->Draw();
	//for (unsigned int i = 0; i < 10; i++) {
	//	jet_pt2.at(i)->Draw("same");
	//}

	//===== Get histograms for sr3 =====
	vector<TH1D*> jet_pt3;
	for (unsigned int i = 0; i < 10; i++) {
		TString histname = "jet_pt_" + to_string(i+1) + "_3";
		TH1D* h = (TH1D*) files.at(2)->Get(histname);
		jet_pt3.push_back(h);
	}
	jet_pt3.at(0)->GetXaxis()->SetRangeUser(0, 1200);
	jet_pt3.at(0)->GetYaxis()->SetRangeUser(0, 1500);
	jet_pt3.at(0)->SetStats(0);

	jet_pt3.at(0)->GetXaxis()->SetTitle("p_T (GeV)");
	jet_pt3.at(0)->GetYaxis()->SetTitle("Event / GeV");
	jet_pt3.at(0)->GetXaxis()->SetTitleOffset(1.1);
	jet_pt3.at(0)->GetYaxis()->SetTitleOffset(1.2);
	jet_pt3.at(0)->SetTitle("SR3");
	//jet_pt3.at(0)->Draw();
	//for (unsigned int i = 0; i < 10; i++) {
	//	jet_pt3.at(i)->Draw("same");
	//}

	//===== Get histograms for sr4 =====
	vector<TH1D*> jet_pt4;
	for (unsigned int i = 0; i < 10; i++) {
		TString histname = "jet_pt_" + to_string(i+1) + "_4";
		TH1D* h = (TH1D*) files.at(3)->Get(histname);
		jet_pt4.push_back(h);
	}
	jet_pt4.at(0)->GetXaxis()->SetRangeUser(0, 2000);
	jet_pt4.at(0)->GetYaxis()->SetRangeUser(0, 1000);
	jet_pt4.at(0)->SetStats(0);

	jet_pt4.at(0)->GetXaxis()->SetTitle("p_T (GeV)");
	jet_pt4.at(0)->GetYaxis()->SetTitle("Event / GeV");
	jet_pt4.at(0)->GetXaxis()->SetTitleOffset(1.1);
	jet_pt4.at(0)->GetYaxis()->SetTitleOffset(1.2);
	jet_pt4.at(0)->SetTitle("SR4");
	//jet_pt4.at(0)->Draw();
	//for (unsigned int i = 0; i < 10; i++) {
	//jet_pt4.at(i)->Draw("same");
	//}

	TCanvas* cvs = new TCanvas("cvs", "cvs", 1800, 1200);;
	TPad* pad1 = new TPad("pad_1", "pad_1", 0, 0.5, 0.5, 1);
	TPad* pad2 = new TPad("pad_2", "pad_2", 0.5, 0.5, 1, 1);
	TPad* pad3 = new TPad("pad_3", "pad_3", 0, 0, 0.5, 0.5);
	TPad* pad4 = new TPad("pad_4", "pad_4", 0.5, 0., 1, 0.5);

	pad1->cd();
	jet_pt1.at(0)->Draw();
	for (unsigned int i = 0; i < 10; i++) jet_pt1.at(i)->Draw("same");

	pad2->cd();
	jet_pt2.at(0)->Draw();
	for (unsigned int i = 0; i < 10; i++) jet_pt2.at(i)->Draw("same");

	pad3->cd();
	jet_pt3.at(0)->Draw();
	for (unsigned int i = 0; i < 10; i++) jet_pt3.at(i)->Draw("same");

	pad4->cd();
	jet_pt4.at(0)->Draw();
	for (unsigned int i = 0; i < 10; i++) jet_pt4.at(i)->Draw("same");

	cvs->cd();
	pad1->Draw(); pad2->Draw(); pad3->Draw(); pad4->Draw();

	cvs->SaveAs("dd.pdf");
}
