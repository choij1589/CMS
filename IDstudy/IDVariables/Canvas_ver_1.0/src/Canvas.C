#include "FileNavi.h"
#include "FileNavi.cpp"

void Canvas() {

	TString pathData = "$PWD/../../Output_ver_1.0/2016/DATA/";
	TString pathMC = "$PWD/../../Output_ver_1.0/2016/Samples/";
	vector<TString> Samples = {"SingleMuon", "DYJets", "TTLL_powheg"};
	vector<TString> MuonIDs = {"POGLoose", "POGMedium", "POGTight"};

	FileNavi navi(pathData, pathMC, Samples, MuonIDs);
	
	TString muonID = "POGTight";
	TString region = "DY";
	TString object = "mu1";
	TString hist = "pt";

	auto* d_data = navi.GetDirectory("SingleMuon", muonID, region, object);
	auto* d_TT = navi.GetDirectory("TTLL_powheg", muonID, region , object);
	auto* d_DY = navi.GetDirectory("DYJets", muonID, region , object);

	TH1D* h_data = (TH1D*) d_data->Get(hist);
	TH1D* h_TT = (TH1D*) d_TT->Get(hist);
	TH1D* h_DY = (TH1D*) d_DY->Get(hist);

	//==== scale histograms ====
	TH1D* h_scale_data = (TH1D*) d_data->Get("phi");
	TH1D* h_scale_TT = (TH1D*) d_TT->Get("phi");
	TH1D* h_scale_DY = (TH1D*) d_DY->Get("phi");

	double s_data = h_scale_data->Integral();
	double s_TT = h_scale_TT->Integral();
	double s_DY = h_scale_DY->Integral();

	//==== Canvas and legend ====
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
	TH1D* hData = NULL;
	TH1D* hMC = NULL;
	TH1D* hSyst = NULL;
	TH1D* hComp = NULL;
	TH1D* hCompSyst = NULL;

	//==== hData settings ====
	hData = (TH1D*)h_data->Clone("hData");
	hData->SetMarkerStyle(8);
    hData->SetMarkerSize(0.5);
    hData->SetMarkerColor(kBlack);
    hData->SetStats(0);
    hData->GetXaxis()->SetLabelSize(0);
	l->AddEntry(hData, "Data", "lep");

	//==== hMC settings ====
	hMC = (TH1D*)h_DY->Clone("hMC");
	hMC->Scale(s_data / s_DY);
	hSyst = (TH1D*) hMC->Clone("hSyst");
	hMC->SetFillColorAlpha(kYellow, 0.7);
	l->AddEntry(hMC, "DYJets", "f");

	hSyst->SetFillColorAlpha(kBlack, 0.2);
	hSyst->SetFillStyle(3144);
	l->AddEntry(hSyst, "stat error", "f");

	//==== hComp settings ====
	hComp = (TH1D*)h_data->Clone("hComp");
	hComp->Divide(hMC);
	hCompSyst = (TH1D*)hComp->Clone("hCompSyst");

	hComp->GetYaxis()->SetRangeUser(0.5, 1.5);
	hComp->SetMarkerStyle(8);
    hComp->SetMarkerSize(0.5);
    hComp->SetMarkerColor(kBlack);
	hComp->SetStats(0);
	hComp->GetYaxis()->SetLabelSize(0.06);
	hComp->GetYaxis()->SetTitle("Data/Pred");
	hComp->GetYaxis()->SetTitleSize(0.08);
	hComp->GetYaxis()->SetTitleOffset(0.5);
    hComp->GetXaxis()->SetLabelSize(0.08);
    hComp->GetXaxis()->SetTitle(hist);
    hComp->GetXaxis()->SetTitleSize(0.1);
    hComp->GetXaxis()->SetTitleOffset(0.8);

	hCompSyst->SetFillColorAlpha(kBlack, 0.2);
	hCompSyst->SetFillStyle(3144);

	//==== Draw on canvas ====
	pUp->cd();
    hData->Draw("p&hist");
	hMC->Draw("hist&same");
	hData->Draw("e1&same");
	hSyst->Draw("e2&f&same");
	l->Draw("same");

	pDown->cd();
	hComp->Draw("p&hist");
	hCompSyst->Draw("e2&f&same");

	c->cd();
	pUp->Draw();
	pDown->Draw();
	c->Draw();
}
