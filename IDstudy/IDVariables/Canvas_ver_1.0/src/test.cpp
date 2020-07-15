#include "FileNavi.h"
#include "FileNavi.cpp"

void test() {
	int DataYear = 2016;
	TString pathData = "$PWD/../../Output_ver_1.0/" + TString::Itoa(DataYear, 10) + "/DATA/";
	TString pathMC = "$PWD/../../Output_ver_1.0/" + TString::Itoa(DataYear, 10) + "/Samples/";

	vector<TString> Samples = {"DoubleMuon", "DYJets", "TTLL_powheg"};
	vector<TString> MuonIDs = {"POGLoose", "POGMedium", "POGTight"};

	FileNavi navi(pathData, pathMC, Samples, MuonIDs);
	
	TH1D* h = (TH1D*)navi.GetHist("DoubleMuon", "POGTight_Central/TT/mu1/IDvar/Chi3");
	h->Draw();
}

