#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

using namespace std;

//===== Canvas2 =====
//===== check prompt normalization variation for pt-eta bin =====

void Canvas2() {
	//==== Basic Information ====
    TString pathData = "$PWD/../../Outputs/2016/RunSysts__/DATA/";
    TString pathMC = "$PWD/../../Outputs/2016/RunSysts__/Samples/";

    vector<TString> Samples = {"DoubleEG", "MC", "DYJets", "tt", "WJets_MG", "SingleTop", "tW"};
    vector<TString> IDs = {"passLooseID", "passTightID", "FakeLooseID", "FakeTightID"};
    vector<TString> Systs = {"Central", "JetPtCut30", "JetPtCut50", "JetPtCut60", "HadFlavor"};
    vector<TString> Prompts = {"Central", "JetResUp", "JetResDown", "JetEnUp", "JetEnDown",
                            "ElectronResUp", "ElectronResDown", "ElectronEnUp", "ElectronEnDown", "PileUp"};
    vector<TString> Regions = {"QCDEnriched", "WEnriched", "ZEnriched"};

    vector<TString> IDSets = {"POG", "Fake"};

    //==== initialize FakeValidation ====
    FakeValidation fake;
    fake.Init(pathData, pathMC, Samples, IDs, Systs, Prompts, Regions, IDSets);

	//==== Get histograms for normalization =====
	/*
	TCanvas* cvs = new TCanvas("cvs", "cvs", 16000, 900);
	TString id = IDs.at(2);
	TH2D* h_central = fake.GetPromptNormPtEta(id, Systs.at(0), Prompts.at(0));
	TH2D* h_syst = fake.GetPromptNormPtEta(id, Systs.at(0), Prompts.at(9));
	TH2D* h_var = (TH2D*)h_syst->Clone("h_var");
	h_var->Add(h_central, -1);
	h_var->Divide(h_central);

	h_var->SetStats(0);
	
	cvs->cd();
	h_var->Draw("colz");
	*/

	TString id = IDs.at(3);
	TH1D* h_central = fake.GetPromptNormEta(id, Systs.at(0), Prompts.at(0));
	TH1D* h_syst = fake.GetPromptNormEta(id, Systs.at(0), Prompts.at(9));
	TH1D* h_var = (TH1D*)h_syst->Clone("h_var");
	h_var->Add(h_central, -1);
	h_var->Divide(h_central);

	h_var->Draw();
	
}

