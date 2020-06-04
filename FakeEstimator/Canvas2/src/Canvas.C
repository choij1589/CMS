#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void Canvas() {
	//==== Basic Information ====
	TString pathData = "$PWD/../../Outputs/2016/RunSysts__HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v/DATA/";
    TString pathMC = "$PWD/../../Outputs/2016/RunSysts__HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v/Samples/";

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

	//fake.GetFakeRatePtEta(IDSets.at(1), Systs.at(0), "Central", 0.85)->Draw("colz");
	//fake.GetFakeRatePt(IDSets.at(1), Systs.at(0), "Central", 1).at(3)->Draw();
	
	TCanvas* cvs = new TCanvas("cvs", "cvs", 800, 450);
	TLegend* leg = new TLegend(0.15, 0.7, 0.35, 0.85);

	vector<TH1D*> h = fake.GetFakeCompPt("POG", Systs.at(4), "Central", 1.);
	cvs->cd();
	h.at(0)->SetStats(0);
	h.at(0)->GetYaxis()->SetRangeUser(-1, 1);
	h.at(0)->SetLineColor(kBlack);

	h.at(1)->SetLineColor(kBlue);
	h.at(2)->SetLineColor(kGreen);
	h.at(3)->SetLineColor(kRed);

	h.at(0)->Draw();
	//h.at(1)->Draw("same");
	//h.at(2)->Draw("same");
	//h.at(3)->Draw("same");
	
	cvs->Draw();
}

