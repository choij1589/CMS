#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void Canvas5() {
	//==== This canvas is to check the prompt rate ====
	//==== which have to be approximately 1 to make sure the approximation holds true ====
	
	//==== inforamtion for Fake ====
    TString pathData = "$PWD/../../Outputs/2016/RunSysts__OringTrigger/DATA/";
    TString pathMC = "$PWD/../../Outputs/2016/RunSysts__OringTrigger/Samples/";

    vector<TString> Samples
        = {"DoubleEG", "MC", "DYJets", "tt", "WJets_MG", "SingleTop", "tW"};
    vector<TString> IDs
        = {"passLooseID", "passTightID", "FakeLooseID", "FakeTightID"};
    vector<TString> Systs
        = {"Central", "JetPtCut30", "JetPtCut50", "JetPtCut60", "HadFlavor"};
    vector<TString> Prompts
        = {"Central", "JetResUp", "JetResDown", "JetEnUp", "JetEnDown",
            "ElectronResUp", "ElectronResDown", "ElectronEnUp", "ElectronEnDown",
            "PileUp"};
    vector<TString> Regions
        = {"QCDEnriched", "WEnriched", "ZEnriched"};
    vector<TString> IDSets = {"POG", "Fake"};

    FakeValidation fake;
    fake.Init(pathData, pathMC, Samples, IDs, Systs, Prompts, Regions, IDSets);

	//==== Get histograms to make prompt rate ====
	//==== in WJets_MG sample ====
	TString idLoose = "FakeLooseID";
	TString idTight = "FakeTightID";

	TH2D* hLoose
		= (TH2D*)fake.GetHist("DoubleEG", "passID_WEnriched_" + idLoose + "_" + Systs.at(0) + "_" + Prompts.at(0));
	TH2D* hTight 
		= (TH2D*)fake.GetHist("DoubleEG", "passID_WEnriched_" + idTight + "_" +     Systs.at(0) + "_" + Prompts.at(0));
	TH2D* hPrompt = (TH2D*)hTight->Clone("prompt rate");
	hPrompt->Divide(hLoose);
	//hTight->Draw("colz");
	//hLoose->Draw("colz");
	hPrompt->Draw("colz");
}
