#include "IDVariables.h"
using namespace std;

//==== Constructor ====
IDVariables::IDVariables() {}
IDVariables::IDVariables(const TString &path_data, const TString &path_mc, const vector<TString> &samples, const vector<TString> &muonIDs) {
	navi.SetPathData(path_data);
	navi.SetPathMC(path_mc);
	navi.SetSamples(samples);
	navi.SetMuonIDs(muonIDs);
}

//==== Destructor ====
IDVariables::~IDVariables() {}

//==== Member functions ====
double IDVariables::GetScale(const TString &path) {
	vector<TString> samples = navi.GetSamples();
	TString data = samples.at(0);
	TString mc = path.Contains("DY") ? samples.at(1) : samples.at(2);

	//==== make new path to get scale factor ====
	TString this_path = "";
	TString tok;
	Ssiz_t from = 0;
	while(path.Tokenize(tok, from, "/")) {
		this_path += tok;
		this_path += "/";
		if (tok.Contains("TT") || tok.Contains("DY")) break;
	}

	this_path += "mu1/phi";
	
	TH1D* h_data = (TH1D*) navi.GetHist(data, this_path);
	TH1D* h_mc = (TH1D*) navi.GetHist(mc, this_path);

	double i_data = h_data->Integral();
	double i_mc = h_mc->Integral();

	return i_data / i_mc;
}

TH1* IDVariables::GetHist(const TString &sample, const TString &path) {
	return navi.GetHist(sample, path);
}
