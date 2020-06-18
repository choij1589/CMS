#include "ConvEstimation.h"
using namespace std;

//==== initialization ====
void ConvEstimation::Init(
		const TString &path_data, const TString &path_mc, const vector<TString> &samples, const vector<TString> &idsets) {
	navi.SetPathData(path_data);
	navi.SetPathMC(path_mc);
	navi.SetSamples(samples);
	navi.SetIDSets(idsets);
}

//==== public functions ====
vector<TDirectory*> ConvEstimation::GetSampleDirectories(const TString &idset) const {
	// information from FileNavi
	vector<TString> Samples = navi.GetSamples();

	vector<TDirectory*> this_dirs;
	// samples & fake directory
	for (unsigned int i = 0; i < Samples.size(); i++) {
		TDirectory* this_dir = navi.GetDirectory(Samples.at(i), idset, 0, 0);
		this_dirs.push_back(this_dir);
	}
	
	return this_dirs;
}

vector<TDirectory*> ConvEstimation::GetFakeDirectories(const TString &idset) const {
	TDirectory* this_fake = navi.GetDirectory("DoubleEG", idset, 1, 0);
	TDirectory* this_fakeUp = navi.GetDirectory("DoubleEG", idset, 1, 1);
	TDirectory* this_fakeDown = navi.GetDirectory("DoubleEG", idset, 1, -1);

	vector<TDirectory*> this_fakedirs; this_fakedirs.push_back(this_fake); this_fakedirs.push_back(this_fakeUp); this_fakedirs.push_back(this_fakeDown);

	return this_fakedirs;
}

TH1D* ConvEstimation::GetHist(const TString &idset, const TString &sample, TString histname) const {
	histname += idset + "_Central";

	TDirectory* this_dir = navi.GetDirectory(sample, idset, 0, 0);
	TH1D* this_hist = (TH1D*)this_dir->Get(histname);

	return this_hist;
}

TH1D* ConvEstimation::GetFakeHist(const TString &idset, TString histname, const int &sys) const {
	if (sys == 0) histname += idset + "_Fake_Central";
	else if (sys == +1) histname += idset + "_Fake_SystUp";
	else if (sys == -1) histname += idset + "_Fake_SystDown";
	else {
		cout << "[ConvEstimation::GetFakeHist] sys = " << sys << endl;
		cout << "[ConvEstimation::GetFakeHist] sys should be 0, -1, 1" << endl;
		exit(EXIT_FAILURE);
	}

	TDirectory* this_dir = navi.GetDirectory("DoubleEG", idset, 1, sys);
	TH1D* this_hist = (TH1D*) this_dir->Get(histname);
	return this_hist;
}

vector<TH1D*> ConvEstimation::GetSampleHists(const TString &idset, TString histname) const {
	vector<TString> Samples = navi.GetSamples();

	vector<TH1D*> this_hists;
	for (unsigned int i = 0; i < Samples.size(); i++) {
		TH1D* this_hist = GetHist(idset, Samples.at(i), histname);
		this_hists.push_back(this_hist);
	}

	return this_hists;
}

vector<TH1D*> ConvEstimation::GetFakeHists(const TString &idset, TString histname) const {
	TH1D* this_fake = GetFakeHist(idset, histname, 0);
	TH1D* this_fakeUp = GetFakeHist(idset, histname, 1);
	TH1D* this_fakeDown = GetFakeHist(idset, histname, -1);

	vector<TH1D*> this_hists; this_hists.push_back(this_fake); this_hists.push_back(this_fakeUp); this_hists.push_back(this_fakeDown);

	return this_hists;
}

double ConvEstimation::GetScale(const TString &idset, int sys) const {
	vector<TH1D*> this_samples = GetSampleHists(idset, "PassSelection_");
	vector<TH1D*> this_fake = GetFakeHists(idset, "PassSelection_");

	TH1D* hData = (TH1D*) this_samples.at(0)->Clone("hData");
	TH1D* hFake = NULL;
	if (sys == 0) hFake = (TH1D*)this_fake.at(0)->Clone("hFake");
	else if (sys == 1) hFake = (TH1D*)this_fake.at(1)->Clone("hFake");
	else if (sys == -1) hFake = (TH1D*)this_fake.at(2)->Clone("hFake");
	else {
		cout << "[ConvEstimation::GetScale] sys = " << sys << endl;
		cout <<	"[ConvEstimation::GetScale] sys should be 0, 1, -1" << endl;
		exit(EXIT_FAILURE);
	}
	//hData->Draw();
	hFake->Draw();
	TH1D* hScale = (TH1D*) hData->Clone("hScale");
	for (unsigned int i = 3; i < this_samples.size(); i++) {
		hScale->Add(this_samples.at(i), -1);
	}
	hScale->Add(hFake, -1);
	hScale->Divide(this_samples.at(2));

	return hScale->Integral();
}
	
















































	
