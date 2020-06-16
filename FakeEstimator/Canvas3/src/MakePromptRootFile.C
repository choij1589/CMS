#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void MakePromptRootFile() {
    //==== Basic Information ====
    TString pathData = "$PWD/../../Outputs/2016/RunSysts__OringTrigger/DATA/";
    TString pathMC = "$PWD/../../Outputs/2016/RunSysts__OringTrigger/Samples/";

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

	TH2D* h_POG_Data = fake.GetPromptRate("POG", true);
	TH2D* h_POG_MC = fake.GetPromptRate("POG", false);
	TH2D* h_Fake_Data = fake.GetPromptRate("Fake", true);
	TH2D* h_Fake_MC = fake.GetPromptRate("Fake", false);
	h_POG_Data->SetName("Electron_prompt_rate_POG_data");
	h_POG_MC->SetName("Electron_prompt_rate_POG_MC");
	h_Fake_Data->SetName("Electron_prompt_rate_Fake_data");
	h_Fake_MC->SetName("Electron_prompt_rate_Fake_MC");

	h_Fake_MC->Draw("colz");
	//
	//==== create root file to store the prompt rate ====
	TFile* f = new TFile("Electron_prompt_fate.root", "recreate");
	f->cd();
	h_POG_Data->Write();
	h_POG_MC->Write();
	h_Fake_Data->Write();
	h_Fake_MC->Write();

	f->Write();
	f->Close();
}

