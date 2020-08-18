#include "FileNavi.h"
#include "FileNavi.cpp"
#include "Canvas.h"
#include "Canvas.cpp"

void test() {
	TString pathData = "$PWD/../input/2016/Data/";
	TString pathMC = "$PWD/../input/2016/MCsamples/";
	vector<TString> Samples = {"TTLL_powheg", "TTLJ_powheg"};
	vector<TString> Regions = {"preselection", "dimu", "dielec", "emu", "ejj", "mujj"};
	vector<TString> Objects = {"muons", "electrons", "jets", "bjets", "METv"};
	vector<TString> LepType = {"ALL", "EWPrompt", "EWTauDaughter", "fake", "others"};
	vector<TString> LepType_inverse = {"others", "fake", "EWTauDaughter", "EWPrompt", "ALL"};	
	cout << "a" << endl;
	FileNavi navi(pathData, pathMC, Samples);
	Canvas cvs(pathData, pathMC, Samples);
	
	// path for emu/electron/
	TString sample = "TTLL_powheg";
	TString region = "emu";
	TString obj = "electrons"; 
	TString order = "1";
	TString var = "pt";
	vector<TH1D*> hists;
	for (const auto& type: LepType) {
		TString this_path;
		if (type.Contains("ALL")) this_path = region + "/" + obj + "/";
		else this_path = region + "/" + obj + "/" + type + "/";
		this_path += order + "/" + var;
		TH1D* this_hist = (TH1D*)navi.GetHist(sample, this_path);
		hists.push_back(this_hist);
	}
	cvs.DrawStack(hists);
	TCanvas* c = nullptr;
	c = cvs.GetCanvas();
	TString cvsTitle = region + "_" + obj + "_" + order + "_" + var;
	c->SetTitle(cvsTitle);
	c->SaveAs(cvsTitle + ".png");
	/*
	TCanvas* c = nullptr;
	TString sample;
	for (unsigned int i = 1; i < Regions.size(); i++) {
		c = nullptr;
		if (i < 4) sample = "TTLL_powheg";
		else sample = "TTLJ_powheg";
		cvs.DrawCutflow(sample, Regions.at(i));
		c = cvs.GetCanvas();
		c->SaveAs("cutflow_" + Regions.at(i) + ".png");
	}
	*/
}
