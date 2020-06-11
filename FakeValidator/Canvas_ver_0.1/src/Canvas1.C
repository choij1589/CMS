#include "FileNavi.h"
#include "FileNavi.C"

void Canvas1() {
	//==== Basic information ====
	TString pathData = "$PWD/../../Output_ver_0.1/2016/RunFakeSystUp__RunFakeSystDown__/DATA/";
	TString pathMC = "$PWD/../../Output_ver_0.1/2016/RunFakeSystUp__RunFakeSystDown__/Samples/";

	vector<TString> Samples = {"DoubleEG", "MC", "ttVorH", "VV", "rare", "conv"};
	vector<TString> IDSets = {"POGID", "FakeID"};

	FileNavi navi;
	navi.SetPathData(pathData);
	navi.SetPathMC(pathMC);
	navi.SetSamples(Samples);
	navi.SetIDSets(IDSets);

	//==== Preparation ====
	//TString histname = "1st_electron_eta_";
	TString histname = "1st_electron_pt_";
	//TString histname = "2nd_electron_eta_";
	//TString histname = "2nd_electron_pt_";
	//TString histname = "3rd_electron_eta_";
	//TString histname = "3rd_electron_pt_";
	//TString idset = "FakeID";
	TString idset = "POGID";

	vector<TDirectory*> dSamples;
	TDirectory* dFake = NULL;
	TDirectory* dFakeUp = NULL;
	TDirectory* dFakeDown = NULL;
	vector<TH1D*> hSamples;
	TH1D* hFake = NULL;
	TH1D* hFakeUp = NULL;
	TH1D* hFakeDown = NULL;
	THStack* hStack = new THStack("hs", "");
	TH1D* hComp = NULL;
	TLegend* leg = new TLegend(0.73, 0.7, 0.93, 0.85);
	TString histnameUp = histname, histnameDown = histname;


	//==== Get Directory ====
	for (unsigned int i = 0; i < Samples.size(); i++) {
		TDirectory* this_dir = navi.GetDirectory(Samples.at(i), idset, false, 0);
		dSamples.push_back(this_dir);
	}
	dFake = navi.GetDirectory("DoubleEG", idset, true, 0);
	dFakeUp = navi.GetDirectory("DoubleEG", idset, true, +1);
	dFakeDown = navi.GetDirectory("DoubleEG", idset, true, -1);
	//dFake->ls();
	//dSamples.at(3)->ls();

	//==== Get Histograms ====
	histname += idset + "_Central";
	histnameUp += idset + "_SystUp_FakeContribution";
	histnameDown += idset + "_SystDown_FakeContribution";
	for (unsigned int i = 0; i < dSamples.size(); i++) {
		cout << histname << endl;
		TH1D* this_hist = (TH1D*) dSamples.at(i)->Get(histname);
		if (!this_hist) {
			cout << "[Canvas1] Null histogram" << endl;
			exit(EXIT_FAILURE);
		}
		hSamples.push_back(this_hist);
		if (i != 0) hSamples.at(i)->SetFillColor(kBlue);
		if (Samples.at(i).Contains("VV")) {
			hSamples.at(i)->SetFillColor(kGreen);
			hSamples.at(i)->SetLineColor(kGreen);
		}
		if (Samples.at(i).Contains("conv")) {
			hSamples.at(i)->SetFillColor(kRed);
			hSamples.at(i)->SetLineColor(kRed);
		}

		leg->AddEntry(hSamples.at(i), Samples.at(i), "lep");
	}

	histname += "_FakeContribution";
	
	hFake = (TH1D*) dFake->Get(histname);
	hFakeUp = (TH1D*) dFakeUp->Get(histnameUp);
	hFakeDown = (TH1D*) dFakeDown->Get(histnameDown);

	if (!hFake) {
		cout << "null fake hist" << endl;
		exit(EXIT_FAILURE);
	}
	hFake->SetFillColor(kGray);
	hFake->SetLineColor(kGray);
	leg->AddEntry(hFake, "Fake", "lep");
	//hSamples.at(3)->Draw();
	
	
	for (unsigned int i = 2; i < hSamples.size(); i++) {
		hStack->Add(hSamples.at(i));
	}
	hStack->Add(hFake);

	hComp = (TH1D*)hSamples.at(0)->Clone("data/mc");
	hComp->Divide(hSamples.at(1));

	//==== histogram settings ====
	hSamples.at(0)->GetXaxis()->SetTitle("p_{T}^{e}");
	hSamples.at(0)->GetYaxis()->SetTitle("Events / 5GeV");
	hSamples.at(0)->SetStats(0);
	hSamples.at(0)->Draw();
	hStack->Draw("histf same");
	hStack->Draw("e2 p same");
	leg->Draw("same");
	//hComp->Draw();
}
