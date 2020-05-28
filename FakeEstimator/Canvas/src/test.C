#include "FileNavi.C"

void test() {
	// Basic Informations
	TString pathData = "/home/choij/Documents/CMS/FakeEstimator/Outputs/2016/RunSysts__/DATA/";
	TString pathMC = "/home/choij/Documents/CMS/FakeEstimator/Outputs/2016/RunSysts__/Samples/";

	vector<TString> IDs = {"passLooseID", "passTightID", "FakeLooseID", "FakeTightID"};
	vector<TString> Systs = {"Central", "JetPtCut30", "JetPtCut50", "JetPtCut60", "HadFlavor"};
	vector<TString> Prompts = {"Central", "JetResUp", "JetResDown", "JetEnUp", "JetEnDown",
        "ElectronResUp", "ElectronResDown", "ElectronEnUp", "ElectronEnDown", "PileUp"};
	vector<TString> Regions = {"QCDEnriched", "WEnriched", "ZEnriched"};
	vector<TString> Samples = {"DoubleEG", "MC", "DYJets", "WJets_MG", "tt", "SingleTop", "tW", "VV"};

	// FileNavi
	FileNavi a(Samples, IDs, Systs, Prompts, Regions);
	a.SetPathData(pathData);
	a.SetPathMC(pathMC);

	a.LoadFakeDirectory();
}
