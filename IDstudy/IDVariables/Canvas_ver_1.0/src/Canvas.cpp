#include "FileNavi.h"
#include "FileNavi.cpp"
#include "IDVariables.h"
#include "IDVariables.cpp"

void Canvas(const int &DataYear,const TString &path, const TString &xAxisName, const TString &yAxisName, const int &yAxisScale, const double &compScaleUp, const double &compScaleDown) {
	//==== User setting information ====
	//int DataYear = 2016;
	//TString path = "POGTight_Central/TT/METv_xyCorr_phi";
	//TString yAxisName = "Events";
	//TString xAxisName = "p_{T}";
	//int yAxisScale = 4000;
	//double compScaleUp = 1.5, compScaleDown = 0.5;



	//==== Basic settings ====
	TString pathData = "$PWD/../../Output_ver_1.0/" + TString::Itoa(DataYear, 10) + "/DATA/";
	TString pathMC = "$PWD/../../Output_ver_1.0/" + TString::Itoa(DataYear, 10) + "/Samples/";

	vector<TString> Samples = {"DoubleMuon", "DYJets", "TTLL_powheg"};
	vector<TString> MuonIDs = {"POGLoose", "POGMedium", "POGTight"};

	IDVariables IDvar(pathData, pathMC, Samples, MuonIDs);

	TString mc;
	if (path.Contains("DY")) mc = Samples.at(1);
	else if (path.Contains("TT")) mc = Samples.at(2);
	else { cout << "Wrong path" << endl; exit(EXIT_FAILURE); }

	//==== output path manipulation ====
	TString outpath = "$PWD/";
	TString tok;
	Ssiz_t from = 0;
	while(path.Tokenize(tok, from, "/")) outpath += tok + "_";
	outpath += "prelim.png";


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

	//==== hData setting ====
	hData = (TH1D*)IDvar.GetHist(Samples.at(0), path);
	hData->SetMarkerStyle(8);
    hData->SetMarkerSize(0.5);
    hData->SetMarkerColor(kBlack);
    hData->SetStats(0);
    hData->GetXaxis()->SetLabelSize(0);
    hData->GetYaxis()->SetTitle(yAxisName);
	hData->GetYaxis()->SetRangeUser(0, yAxisScale);
	
	l->AddEntry(hData, "Data", "lep");

	//==== hMC setting ====
	hMC = (TH1D*)IDvar.GetHist(mc, path);
	double scale = IDvar.GetScale(path);
	cout << "[Canvas] scale = " << scale << endl;
	hMC->Scale(scale);
	if (path.Contains("DY")) {
		hMC->SetFillColorAlpha(kYellow, 0.4);
		l->AddEntry(hMC, "DYJets", "f");
	}
	if (path.Contains("TT")) {
		hMC->SetFillColorAlpha(kViolet, 0.4);
		l->AddEntry(hMC, "TTLL_powheg", "f");
	}

	//==== hSyst setting ====
	hSyst = (TH1D*)hMC->Clone("hSyst");
	hSyst->SetFillColorAlpha(kBlack, 0.9);
	hSyst->SetFillStyle(3144);

	//==== hComp setting ====
	hComp = (TH1D*)hData->Clone("hComp");
	hComp->Divide(hMC);
	hCompSyst = (TH1D*)hComp->Clone("hCompSyst");

	hComp->GetYaxis()->SetRangeUser(compScaleDown, compScaleUp);
    hComp->SetStats(0);
    hComp->SetMarkerStyle(8);
    hComp->SetMarkerSize(0.5);
    hComp->GetYaxis()->SetLabelSize(0.06);
    hComp->GetYaxis()->SetTitle("Data/Pred");
    hComp->GetYaxis()->SetTitleSize(0.08);
    hComp->GetYaxis()->SetTitleOffset(0.5);
    hComp->GetXaxis()->SetLabelSize(0.08);
    hComp->GetXaxis()->SetTitle(xAxisName);
    hComp->GetXaxis()->SetTitleSize(0.1);
    hComp->GetXaxis()->SetTitleOffset(0.8);

	//==== hCompSyst setting ====
	hCompSyst->SetFillColorAlpha(kBlack, 0.4);
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
	c->SaveAs(outpath);

	c->Close();
}

	


