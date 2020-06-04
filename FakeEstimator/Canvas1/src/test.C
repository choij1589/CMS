#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"
#include <string>

void test() {
    //==== Basic Information ====
	TString pathData = "/home/choij/Documents/CMS/FakeEstimator/Outputs/2016/RunSysts__/DATA/";
	TString pathMC = "/home/choij/Documents/CMS/FakeEstimator/Outputs/2016/RunSysts__/Samples/";

	vector<TString> Samples = {"DoubleEG", "MC", "DYJets", "tt", "WJets_MG", "SingleTop", "tW"};
	vector<TString> IDs = {"passLooseID", "passTightID", "FakeLooseID", "FakeTightID"};
	vector<TString> Systs = {"Central", "JetPtCut30", "JetPtCut50", "JetPtCut60", "HadFlavor"};
	vector<TString> Prompts = {"Central", "JetResUp", "JetResDown", "JetEnUp", "JetEnDown",
							"ElectronResUp", "ElectronResDown", "ElectronEnUp", "ElectronEnDown", "PileUp"};
	vector<TString> Regions = {"QCDEnriched", "WEnriched", "ZEnriched"};

	//==== initialize FakeValidation ====
	FakeValidation fake(pathData, pathMC);
	fake.Init(Samples, IDs, Systs, Prompts, Regions);

	TCanvas* cvs = fake.DrawFake1D(Systs.at(4), -1);
	cvs->Draw();
}
