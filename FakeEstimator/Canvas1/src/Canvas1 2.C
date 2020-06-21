#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void Canvas1() {
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

	//fake.GetFakeRatePtEta(IDSets.at(1), Systs.at(0), "Central", 0.85)->Draw("colz");
	//fake.GetFakeRatePt(IDSets.at(1), Systs.at(0), "Central", 1).at(3)->Draw();
	
	TCanvas* cvs = new TCanvas("cvs", "cvs", 800, 450);
	TLegend* leg = new TLegend(0.15, 0.7, 0.35, 0.85);

	TH1D* fakeCentral = fake.GetFakeRatePt(IDSets.at(0), Systs.at(0), "Central", 1).at(0);
	TH1D* fakeJetPt30 = fake.GetFakeRatePt(IDSets.at(0), Systs.at(1), "Central", 1).at(0);
	TH1D* fakeJetPt60 = fake.GetFakeRatePt(IDSets.at(0), Systs.at(3), "Central", 1).at(0);
	TH1D* fakeHadFlavor = fake.GetFakeRatePt(IDSets.at(0), Systs.at(4), "Central", 1).at(0);
	TH1D* fakePromptNormUp = fake.GetFakeRatePt(IDSets.at(0), Systs.at(0), "Central", 1.15).at(0);
	TH1D* fakePromptNormDown = fake.GetFakeRatePt(IDSets.at(0), Systs.at(0), "Central", 0.85).at(0);

	double errJetPt30[3];
	double errJetPt60[3];
	double errHadFlavor[3];
	double errPromptNormUp[3];
	double errPromptNormDown[3];

	fakeJetPt30->Add(fakeCentral, -1);
	fakeJetPt30->Divide(fakeCentral);
	fakeJetPt30->SetLineColor(kBlue);
	fakeJetPt30->SetMarkerColor(kBlue);
	fakeJetPt30->SetMarkerStyle(8);
	leg->AddEntry(fakeJetPt30, "AwayJetPt");

	fakeJetPt60->Add(fakeCentral, -1);
	fakeJetPt60->Divide(fakeCentral);
	fakeJetPt60->SetLineColor(kBlue);
	fakeJetPt60->SetMarkerColor(kBlue);
	fakeJetPt60->SetMarkerStyle(8);

	fakeHadFlavor->Add(fakeCentral, -1);
	fakeHadFlavor->Divide(fakeCentral);
	fakeHadFlavor->SetLineColor(kGreen);
	fakeHadFlavor->SetMarkerColor(kGreen);
	fakeHadFlavor->SetMarkerStyle(8);
	leg->AddEntry(fakeHadFlavor, "HasBJet");

	fakePromptNormUp->Add(fakeCentral, -1);
	fakePromptNormUp->Divide(fakeCentral);
	fakePromptNormUp->SetLineColor(kRed);
	fakePromptNormUp->SetMarkerColor(kRed);
	fakePromptNormUp->SetMarkerStyle(8);
	leg->AddEntry(fakePromptNormUp, "PromptNorm");

	fakePromptNormDown->Add(fakeCentral, -1);
	fakePromptNormDown->Divide(fakeCentral);
	fakePromptNormDown->SetLineColor(kRed);
	fakePromptNormDown->SetMarkerColor(kRed);
	fakePromptNormDown->SetMarkerStyle(8);
	for (int i = 0; i < 3; i++) {
		errJetPt30[i] = fakeJetPt30->GetBinContent(i+1);
		errJetPt60[i] = fakeJetPt60->GetBinContent(i+1);
		errHadFlavor[i] = fakeHadFlavor->GetBinContent(i+1);
		errPromptNormUp[i] = fakePromptNormUp->GetBinContent(i+1);
		errPromptNormDown[i] = fakePromptNormDown->GetBinContent(i+1);
	}
	
	double err[3];
	for (int i = 0; i < 3; i++) {
		int temp = 0;
		temp += errJetPt30[i]*errJetPt30[i];
		cout << temp << endl;
		temp += errJetPt60[i]*errJetPt60[i];
		cout << temp << endl;
		temp += errHadFlavor[i]*errHadFlavor[i];
		cout << temp << endl;
		temp += errPromptNormUp[i]*errPromptNormUp[i];
		cout << temp << endl;
		temp += errPromptNormDown[i]*errPromptNormDown[i];
		cout << temp << endl;
		temp = std::sqrt(temp);
		err[i] = temp;
	}

	TH1D* fCentral = (TH1D*)fakeCentral->Clone("");
	fakeCentral->Add(fCentral, -1);
	fakeCentral->Divide(fCentral);
	fakeCentral->SetLineColor(kBlack);
	fakeCentral->SetLineWidth(2);
	fakeCentral->SetStats(0);
	fakeCentral->SetXTitle("p_{T}^{Corr} (GeV)");
	fakeCentral->SetYTitle("#Delta FR/FR");

	cvs->cd();
	cvs->SetGrid();
	fakeCentral->GetYaxis()->SetRangeUser(-1, 1);
	fakeCentral->Draw();
	fakeJetPt30->Draw("P same");
	fakeJetPt60->Draw("P same");
	fakeHadFlavor->Draw("P same");
	fakePromptNormUp->Draw("P same");
	fakePromptNormDown->Draw("P same");
	leg->Draw("same");

	cvs->Draw();

	TCanvas* c1 = new TCanvas("c1", "c1", 800, 450);
	c1->cd();
	fake.GetFakeRatePtEta(IDSets.at(0), Systs.at(0), "Central", 1)->SetStats(0);
	fake.GetFakeRatePtEta(IDSets.at(0), Systs.at(0), "Central", 1)->Draw("colz");
	c1->Draw();
}
