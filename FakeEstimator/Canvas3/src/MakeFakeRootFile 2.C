#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void MakeFakeRootFile() {
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

	TH2D* h_POG = fake.GetFakeRateWithErr("POG");
	TH2D* h_Fake = fake.GetFakeRateWithErr("Fake");
	h_POG->SetName("Electron_fake_rate_POG");
	h_Fake->SetName("Electron_fake_rate_FAKE");

	h_POG->GetZaxis()->SetRangeUser(0, 0.5);
	h_POG->Draw("e1");
	//
	//==== create root file to store the fake rate
	TFile* f = new TFile("Electron_fake_rate.root", "recreate");
	f->cd();
	h_POG->Write();
	h_Fake->Write();
	f->Write();
	f->Close();
}
