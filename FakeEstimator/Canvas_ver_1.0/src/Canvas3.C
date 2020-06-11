#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void Canvas3() {
    //==== Basic Information ====
    TString pathData = "$PWD/../../Outputs_ver_1.0/2016/RunSysts__/DATA/";
    TString pathMC = "$PWD/../../Outputs_ver_1.0/2016/RunSysts__/Samples/";

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

    TCanvas* cvs = new TCanvas("cvs", "cvs", 800, 900);
    TLegend* leg = new TLegend(0.73, 0.7, 0.93, 0.85);

	TPad* pad_up = new TPad("pad_up", "", 0, 0.3, 1, 1);
	TPad* pad_down = new TPad("pad_down", "", 0, 0, 1, 0.3);

	TString idset = "Fake";
	int n = 1;
	int nbinx = 6;

	// histograms in pad_up
	vector<TH1D*> h = fake.GetFakeRatePtWithErr(idset);
	vector<TH1D*> h_30 = fake.GetFakeRatePt(idset, Systs.at(1), "Central", 1.);
	vector<TH1D*> h_60 = fake.GetFakeRatePt(idset, Systs.at(3), "Central", 1.);
	vector<TH1D*> h_had = fake.GetFakeRatePt(idset, Systs.at(4), "Central", 1.);
	vector<TH1D*> h_up = fake.GetFakeRatePt(idset, Systs.at(0), "Central", 1.15);
	vector<TH1D*> h_down = fake.GetFakeRatePt(idset, Systs.at(0), "Central", 0.85);

	h.at(n)->GetYaxis()->SetRangeUser(0, 0.5);
	h.at(n)->SetLineColor(kBlack);
	h.at(n)->SetFillColorAlpha(kBlack, 0.5);
	h.at(n)->SetFillStyle(3354);
	h.at(n)->GetXaxis()->SetTitleSize(0);
	h.at(n)->GetXaxis()->SetLabelSize(0);
	//h.at(n)->GetXaxis()->SetTitle("p_{T}^{Corr}");
	h.at(n)->GetYaxis()->SetTitle("fake rate");
	h.at(n)->SetStats(0);

	h_30.at(n)->SetLineColor(kBlue);
	h_60.at(n)->SetLineColor(kBlue);
	h_had.at(n)->SetLineColor(kRed);
	h_up.at(n)->SetLineColor(kGreen);
	h_down.at(n)->SetLineColor(kGreen);

	// histograms in pad_down
	vector<TH1D*> h_central;
	for (unsigned int i = 0; i < 4; i++) {
		TH1D* temp = (TH1D*)h.at(i)->Clone("clone_" + TString::Itoa(i, 10));
		h_central.push_back(temp);
	}
	for (unsigned int i = 0; i < h_central.size(); i++) {
		h_central.at(i)->Add(h_central.at(i), -1);
		for (int j = 0; j < nbinx; j++) {
			h_central.at(i)->SetBinError(j+1, h.at(i)->GetBinError(j+1) / h.at(i)->GetBinContent(j+1));
		}
	}
	//vector<TH1D*> h_comp_30 = fake.GetFakeCompPt(idset, Systs.at(1), "Central", 1.);
	//vector<TH1D*> h_comp_60 = fake.GetFakeCompPt(idset, Systs.at(3), "Central", 1.);
	//vector<TH1D*> h_comp_had = fake.GetFakeCompPt(idset, Systs.at(4), "Central", 1.);
	//vector<TH1D*> h_comp_up = fake.GetFakeCompPt(idset, Systs.at(0), "Central", 1.15);
	//vector<TH1D*> h_comp_down = fake.GetFakeCompPt(idset, Systs.at(0), "Central", 0.85);

	h_central.at(n)->SetFillColorAlpha(kBlack, 0.5);
	h_central.at(n)->GetYaxis()->SetRangeUser(-1, 1);
	h_central.at(n)->GetYaxis()->SetTitle("#Delta FR / FR");
	h_central.at(n)->GetYaxis()->SetLabelSize(0.06);
	h_central.at(n)->GetYaxis()->SetTitleSize(0.06);
	h_central.at(n)->GetYaxis()->SetTitleOffset(0.75);
	h_central.at(n)->GetXaxis()->SetTitle("P_{T}^{Corr}");
	h_central.at(n)->GetXaxis()->SetTitleSize(0.08);
	h_central.at(n)->GetXaxis()->SetLabelSize(0.08);

	leg->AddEntry(h.at(n), "Central", "lep");
	leg->AddEntry(h_30.at(n), "AwayJetPt", "lep");
	leg->AddEntry(h_had.at(n), "HasBJet", "lep");
	leg->AddEntry(h_up.at(n), "PromptNorm", "lep");

	pad_up->cd();
	pad_up->SetTopMargin(0.08); pad_up->SetBottomMargin(0.02); pad_up->SetLeftMargin(0.15); pad_up->SetRightMargin(0.05);
	pad_down->SetTopMargin(0.05); pad_down->SetBottomMargin(0.45); pad_down->SetLeftMargin(0.15); pad_down->SetRightMargin
    (0.05);

	h.at(n)->Draw("e2");
	h_30.at(n)->Draw("same");
	h_60.at(n)->Draw("same");
	h_had.at(n)->Draw("same");
	h_up.at(n)->Draw("same");
	h_down.at(n)->Draw("same");
	h.at(n)->Draw("e0 same");
	leg->Draw("same");

	pad_down->cd();
	h_central.at(n)->Draw("e2");
	//h_comp_30.at(n)->Draw("same");
	//h_comp_60.at(n)->Draw("same");
	//h_comp_had.at(n)->Draw("same");
	//h_comp_up.at(n)->Draw("same");
	//h_comp_down.at(n)->Draw("same");
	h_central.at(n)->Draw("e0 same");

	cvs->cd();
	pad_up->Draw();
	pad_down->Draw();
	cvs->Draw();
	//cvs->SaveAs("fake_rate_" + idset + "_" + TString::Itoa(n, 10) + ".pdf");
}
