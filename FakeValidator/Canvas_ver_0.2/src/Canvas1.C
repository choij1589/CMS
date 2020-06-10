#include "FileNavi.h"
#include "FileNavi.C"

void Canvas1() {
	//==== Basic information ====
	TString pathData = "$PWD/../../Output_ver_0.2/2016/RunFakeSystUp__RunFakeSystDown__/DATA/";
	TString pathMC = "$PWD/../../Output_ver_0.2/2016/RunFakeSystUp__RunFakeSystDown__/Samples/";

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
	TString idset = "POGID";

	vector<TDirectory*> dSamples;
	TDirectory* dFake = NULL;
	vector<TH1D*> hSamples;
	TH1D* hFake = NULL;
	THStack* hStack = new THStack("hs", "");
	TH1D* hComp = NULL;
	// legend


	//==== Get Directory ====
	for (unsigned int i = 0; i < Samples.size(); i++) {
		TDirectory* this_dir = navi.GetDirectory(Samples.at(i), idset, false, 0);
		dSamples.push_back(this_dir);
	}
	dFake = navi.GetDirectory("DoubleEG", idset, true, 0);
	//dFake->ls();
	//dSamples.at(3)->ls();

	//==== Get Histograms ====
	histname += idset + "_Central";
	for (unsigned int i = 0; i < dSamples.size(); i++) {
		cout << histname << endl;
		TH1D* this_hist = (TH1D*) dSamples.at(i)->Get(histname);
		if (!this_hist) {
			cout << "[Canvas1] Null histogram" << endl;
			exit(EXIT_FAILURE);
		}
		hSamples.push_back(this_hist);
	}
	histname += "_FakeContribution";
	hFake = (TH1D*) dFake->Get(histname);
	hFake->Draw();
	//hSamples.at(3)->Draw();
	
	for (unsigned int i = 2; i < hSamples.size(); i++) {
		hStack->Add(hSamples.at(i));
	}
	hStack->Add(hFake);

	hComp = (TH1D*)hSamples.at(0)->Clone("data/mc");
	hComp->Divide(hSamples.at(1));

	hSamples.at(0)->Draw();
	hStack->Draw("same");
	//hComp->Draw();
}
