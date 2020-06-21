#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void test() {
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

	TH2D* h1 = (TH2D*)fake.GetHist("DoubleEG", "passID3bins_QCDEnriched_passLooseID_Central_Central");
	TH2D* h2 = (TH2D*)fake.GetHist("DoubleEG", "passID3bins_QCDEnriched_FakeLooseID_Central_Central");

	h1->Draw("colz");
}
