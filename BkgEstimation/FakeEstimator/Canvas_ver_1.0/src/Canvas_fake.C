#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void Canvas_fake() {
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

	FakeValidation fake;
    fake.Init(pathData, pathMC, Samples, IDs, Systs, Prompts, Regions, IDSets);

	//==== User defined settings ====
	TString idset = "Fake";
	int etaRng = 3; // 0, 1, 2, 3
	int nbinx = 6;

	//==== Canvas and Legend ====
	TCanvas* c = new TCanvas("canvas", "", 720, 800);
    TLegend* l = new TLegend(0.69, 0.65, 0.93, 0.88);
    TPad* pUp = new TPad("pUp", "", 0, 0.25, 1, 1);
    TPad* pDown = new TPad("pDown", "", 0, 0, 1, 0.25);

    pUp->SetTopMargin(0.08);
    pUp->SetBottomMargin(0.02);
    pUp->SetLeftMargin(0.15);
    pUp->SetRightMargin(0.05);
    pUp->SetGrid();

    pDown->SetTopMargin(0.05);
    pDown->SetBottomMargin(0.45);
    pDown->SetLeftMargin(0.15);
    pDown->SetRightMargin(0.05);
    pDown->SetGrid();

    //==== Get histograms to manipulate ====
    TH1D* hCentral = NULL;
	TH1D* hSyst = NULL;
	TH1D* h30 = NULL;
	TH1D* h60 = NULL;
	TH1D* hHad = NULL;
	TH1D* hUp = NULL;
	TH1D* hDown = NULL;

    TH1D* hComp = NULL;
    TH1D* hCompSyst = NULL;
	TH1D* hComp30 = NULL;
	TH1D* hComp60 = NULL;
	TH1D* hCompHad = NULL;
	TH1D* hCompUp = NULL;
	TH1D* hCompDown = NULL;

	vector<TH1D*> h = fake.GetFakeRatePtWithErr(idset);
	vector<TH1D*> h_30 = fake.GetFakeRatePt(idset, Systs.at(1), "Central", 1.);
	vector<TH1D*> h_60 = fake.GetFakeRatePt(idset, Systs.at(3), "Central", 1.);
	vector<TH1D*> h_had = fake.GetFakeRatePt(idset, Systs.at(4), "Central", 1.);
	vector<TH1D*> h_up = fake.GetFakeRatePt(idset, Systs.at(0), "Central", 1.15);
	vector<TH1D*> h_down = fake.GetFakeRatePt(idset, Systs.at(0), "Central", 0.85);

	//==== pUp settings ====
	hCentral = (TH1D*)h.at(etaRng)->Clone("hCentral");
	h30 = (TH1D*)h_30.at(etaRng)->Clone("h30");
	h60 = (TH1D*)h_60.at(etaRng)->Clone("h60");
	hHad = (TH1D*)h_had.at(etaRng)->Clone("hHad");
	hUp = (TH1D*)h_up.at(etaRng)->Clone("hUp");
	hDown = (TH1D*)h_down.at(etaRng)->Clone("hDown");
	
	hCentral->GetYaxis()->SetRangeUser(0, 0.5);
	hCentral->SetMarkerStyle(8);
	hCentral->SetMarkerSize(0.5);
	hCentral->SetMarkerColor(kBlack);
	hCentral->GetXaxis()->SetTitleSize(0);
	hCentral->GetXaxis()->SetLabelSize(0);
	hCentral->GetYaxis()->SetTitle("fake rate");
	hCentral->SetStats(0);

	h30->SetMarkerStyle(8);
	h30->SetMarkerSize(0.5);
	h30->SetMarkerColor(kBlue);
	h60->SetMarkerStyle(8);
    h60->SetMarkerSize(0.5);
    h60->SetMarkerColor(kBlue);
	hHad->SetMarkerStyle(8);
    hHad->SetMarkerSize(0.5);
    hHad->SetMarkerColor(kRed);
	hUp->SetMarkerStyle(8);
    hUp->SetMarkerSize(0.5);
    hUp->SetMarkerColor(kGreen);
	hDown->SetMarkerStyle(8);
    hDown->SetMarkerSize(0.5);
    hDown->SetMarkerColor(kGreen);
	
	l->AddEntry(hCentral, "Central", "lep");
	l->AddEntry(h30, "AwayJetPt", "lep");
	l->AddEntry(hHad, "HasBJet", "lep");
	l->AddEntry(hUp, "PromptNorm", "lep");

	hSyst = (TH1D*) h.at(etaRng)->Clone("hSyst");
	hSyst->SetFillColorAlpha(kBlack, 0.3);
    hSyst->SetFillStyle(3144);
    l->AddEntry(hSyst, "stat+syst error", "f");

	pUp->cd();
	hCentral->Draw("hist&p");
	hSyst->Draw("same&f&e2");
	h30->Draw("same&hist&p");
    h60->Draw("same&hist&p");
    hHad->Draw("same&hist&p");
    hUp->Draw("same&hist&p");
    hDown->Draw("same&hist&p");
	hCentral->Draw("same&hist&p");
	l->Draw("same");

	//==== pDown settings ====
	hComp = (TH1D*) hCentral->Clone("hComp");
	hComp->Add(hComp, -1);
	for (int i = 0; i < nbinx; i++) {
		hComp->SetBinError(i+1, hCentral->GetBinError(i+1) / hCentral->GetBinContent(i+1));
	}
	hComp->GetYaxis()->SetRangeUser(-1, 1);
	hComp->SetStats(0);
	hComp->GetYaxis()->SetLabelSize(0.06);
    hComp->GetYaxis()->SetTitle("#Delta FR / FR");
    hComp->GetYaxis()->SetTitleSize(0.08);
    hComp->GetYaxis()->SetTitleOffset(0.5);
    hComp->GetXaxis()->SetLabelSize(0.08);
    hComp->GetXaxis()->SetTitle("p_{T}^{corr}");
    hComp->GetXaxis()->SetTitleSize(0.1);
    hComp->GetXaxis()->SetTitleOffset(1.0);

	hCompSyst = (TH1D*)hSyst->Clone("hCompSyst");
	hCompSyst->Add(hCentral, -1);
	for (int i = 0; i < nbinx; i++) {
        hCompSyst->SetBinError(i+1, hCentral->GetBinError(i+1) / hCentral->GetBinContent(i+1));
    }

	hComp30 = (TH1D*)h30->Clone("hComp30"); hComp30->Add(hCentral, -1); hComp30->Divide(hCentral);
	hComp60 = (TH1D*)h60->Clone("hComp60"); hComp60->Add(hCentral, -1); hComp60->Divide(hCentral);
	hCompHad = (TH1D*)hHad->Clone("hCompHad"); hCompHad->Add(hCentral, -1); hCompHad->Divide(hCentral);
	hCompUp = (TH1D*) hUp->Clone("hCompUp"); hCompUp->Add(hCentral, -1); hCompUp->Divide(hCentral);
	hCompDown = (TH1D*) hDown->Clone("hCompDown"); hCompDown->Add(hCentral, -1); hCompDown->Divide(hCentral);

	pDown->cd();
	hComp->Draw("hist&p");
	hCompSyst->Draw("e2&f&same");
	hComp30->Draw("hist&same&p");
	hComp60->Draw("hist&same&p");
	hCompHad->Draw("hist&same&p");
	hCompUp->Draw("hist&same&p");
	hCompDown->Draw("hist&same&p");
	hComp->Draw("hist&same&p");
	
	c->cd();
	pUp->Draw();
	pDown->Draw();
	c->Draw();

	if (etaRng == 0) c->SaveAs("fakerate_total.pdf");
	else if (etaRng == 1) c->SaveAs("FR_barrel.pdf");
	else if (etaRng == 2) c->SaveAs("FR_endcap1.pdf");
	else if (etaRng == 3) c->SaveAs("FR_endcap2.pdf");
	else {
		cout << "[Cavavs_fake] Wrong eta range" << endl;
	}
	c->Close();	
}

