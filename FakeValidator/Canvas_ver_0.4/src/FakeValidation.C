#include "FakeEstimation.C"
using namespace std;

//==== initialization ====
void FakeEstimation::Init(const TString &pathdata, const TString &pathmc, const vector<TString> &samples, const vector<TString> idsets) {
	navi.SetPathData(pathdata);
	navi.SetPathMC(pahtmc);
	navi.SetSamples(samples);
	navi.SetIDSets(idsets);
}

//==== public functions ====
TH1D* FakeEstimation::GetHist(const TString &idset, const TString &sample, TString histname) const {
	histname += idset + "_Central";

	TDirectory* this_dir = navi.GetDirectory(sample, idset, 0, 0);
	TH1D* this_hist = (TH1D*)this_dir->Get(histname);

	return this_hist;
}

TH1D* FakeEstimation::GetFakeHist(const TString &idset, TString histname, const int sys) const {
	if (sys == 0) histname += idset + "_Fake_Central";
	else if (sys == +1) histname += idset + "_Fake_SystUp";
	else if (sys == -1) histname += idset + "_Fake_SystDown";
	else {
		cout << "[FakeValidation::GetFakeHist] sys = " << sys << endl;
		cout << "[FakeValidation::GetFakeHist] sys should be 0, -1, 1" << endl;
		exit(EXIT_FAILURE);
	}

	TDirectory* this_dir = navi.GetDirectory("DoubleEG", idset, 1, sys);
	TH1D* this_hist = (TH1D*) this_dir->Get(histname);
	return this_hist;
}

vector<TH1D*> FakeEstimation::GetSamplesHists(const TString &idset, TString histname) const {
	vector<TString> Samples = navi.GetSamples();

	vector<TH1D*> this_hists;
	for (unsigned int i = 0; i < Samples.size(); i++) {
		TH1D* this_hist = GetHist(idset, Samples.at(i), histname);
		this_hists.push_back(this_hist);
	}

	return this_hists;
}

vector<TH1D*> FakeEstimation::GetFakeHists(const TString &idset, TString histname) const {
	TH1D* this_fake = GetFakeHist(idset, histname, 0);
    TH1D* this_fakeUp = GetFakeHist(idset, histname, 1);
    TH1D* this_fakeDown = GetFakeHist(idset, histname, -1);

    vector<TH1D*> this_hists; this_hists.push_back(this_fake); this_hists.push_back(this_fakeUp); this_hists.push_back(this_fakeDown);

    return this_hists;
}

double FakeEstimation::GetScale(const TString &idset) {
	if (idset.Contains("POG")) return 0.239;
	else if (idset.Contains("Fake")) return 0.637;
	else {
		cout << "[FakeEstimation::GetScale] idset = " << idset << endl;
		cout << "[FakeEstimation::GetScale] Wrong idset" << endl;
		exit(EXIT_FAILURE);
	}
}
	
