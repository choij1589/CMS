#include "FileNavi.h"
#include "FileNavi.cpp"
#include "IDVariables.h"
#include "IDVariables.cpp"

void test() {
	int DataYear = 2017;
	TString pathData = "$PWD/../../Output_ver_1.0/" + TString::Itoa(DataYear, 10) + "/DATA/";
	TString pathMC = "$PWD/../../Output_ver_1.0/" + TString::Itoa(DataYear, 10) + "/Samples/";

	vector<TString> Samples = {"DoubleMuon", "DYJets", "TTLL_powheg"};
	vector<TString> MuonIDs = {"POGLoose", "POGMedium", "POGTight"};

	IDVariables IDvar(pathData, pathMC, Samples, MuonIDs);

	TString path = "POGTight_Central/TT/nBJets";

	TH1D* h_data = (TH1D*)IDvar.GetHist("DoubleMuon", path);
	TH1D* h_tt = (TH1D*)IDvar.GetHist("TTLL_powheg", path);
	TH1D* h_dy = (TH1D*)IDvar.GetHist("DYJets", path);

	h_tt->SetLineColor(kViolet);
	h_dy->SetLineColor(kRed);

	h_data->Draw();
	h_tt->Draw("same");
	h_dy->Draw("same");


	
	cout << IDvar.GetScale(path) << endl;
	

	//TH1D* h = (TH1D*)navi.GetHist("DoubleMuon", "POGTight_Central/TT/mu1/IDvar/Chi2");
	//h->Draw();
}

