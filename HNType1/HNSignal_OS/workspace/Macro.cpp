#include "FileNavi.h"
#include "FileNavi.cpp"

void Macro() {
	TString DataYear = "2016";
	TString userflag = "RunPOGTight";
	TString region = "preselection";
	TString obj = "muons_tight/1";
	TString dist = "pt";
	bool logy = false;
	
	TString pathData = "$PWD/../input/" + DataYear + "/" + userflag + "__/DATA/";
	TString pathMC = "$PWD/../input/" + DataYear + "/" + userflag + "__/MCSamples/";
	//vector<TString> Samples{"DoubleMuon", "prompt"};
	vector<TString> Samples{"DoubleMuon", "VV", "tX", "others"};

	FileNavi navi(pathData, pathMC, Samples);

	//==== AxisName ====
	TString xAxisName = "";
	TString yAxisName = "Events";
	if (dist.Contains("pt")) {
		yAxisName = "Events / 1 GeV";
		//if (obj.Contains("fatjets")) yAxisName = "Events / 50 GeV";
		if (obj.Contains("METv")) xAxisName = "E_{T}^{miss}";
		else xAxisName = "p_{T}";
	}
	if (dist.Contains("eta")) xAxisName = "#eta";
	if (dist.Contains("phi")) xAxisName = "#phi";
	if (dist.Contains("RelIso")) xAxisName = "I^{rel}";

	//==== Get histograms ====
	TH1D* h_data = nullptr;
	TH1D* h_DY = nullptr;
	TH1D* h_TT = nullptr;
	TH1D* h_VV = nullptr;
	TH1D* h_tX = nullptr;
	TH1D* h_others = nullptr;
	TH1D* h_fake = nullptr;
	TH1D* h_syst = nullptr;
	TH1D* h_comp = nullptr;
	TH1D* h_comp_syst = nullptr;
	THStack* h_stack = nullptr;

	// data
	TString p_data = region + "/" + obj + "/" + dist;
	cout << "p_data: " << p_data << endl;
	h_data = (TH1D*)navi.GetHist("DoubleMuon", p_data);
	//h_data->Draw();

	// fake
	TString p_fake = region + "/fake/" + obj + "/" + dist;
	cout << "p_fake: " << p_fake << endl;
	h_fake = (TH1D*)navi.GetHist("DoubleMuon", p_fake);
	//h_fake->Draw();
	
	// DY
	TString p_DY = region + "/" + obj + "/" + dist;
	cout << "p_DY: " << p_DY << endl;
	h_DY = (TH1D*) navi.GetHist("DYJets", p_DY);

	// TTLL_powheg
	TString p_TT = region + "/" + obj + "/" + dist;
	cout << "p_TT: " << p_TT << endl;
	h_TT = (TH1D*) navi.GetHist("TTLL_powheg", p_TT);

	// tX
	TString p_tX = region + "/" + obj + "/" + dist;
	cout << "p_tX: " << p_tX << endl;
	h_tX = (TH1D*) navi.GetHist("tX", p_tX);
	//h_tX->Draw();

	// VV
	TString p_VV = region + "/" + obj + "/" + dist;
	cout << "p_VV:" << p_VV << endl;
	h_VV = (TH1D*) navi.GetHist("VV", p_VV);

	// others
	TString p_others = region + "/" + obj + "/" + dist;
    cout << "p_others:" << p_others << endl;
    h_others = (TH1D*) navi.GetHist("others", p_others);		
	
	// rebin
	/*
	if (dist.Contains("pt")) {
		h_data->Rebin(10);
		h_DY->Rebin(10);
		h_TT->Rebin(10);
		h_tX->Rebin(10);
		h_VV->Rebin(10);
		h_others->Rebin(10);
		h_fake->Rebin(10);
	}
	if (obj.Contains("fatjets") && (dist.Contains("pt") || dist.Contains("SDMass"))) {
		h_data->Rebin(5);
		h_DY->Rebin(5);
		h_TT->Rebin(5);
		h_tX->Rebin(5);
		h_VV->Rebin(5);
		h_others->Rebin(5);
		h_fake->Rebin(5);
	}
	*/

	//==== set systematic for fake ====
	cout << h_fake->GetNbinsX() << endl;
	for (unsigned int i = 0; i < h_fake->GetNbinsX(); i++) {
		// not sure for stat errors
		unsigned int bin = i+1;
		double stat_err = h_fake->GetBinError(bin);
		double syst_err = 0.3*h_fake->GetBinContent(bin);
		double err = TMath::Sqrt(stat_err*stat_err + syst_err*syst_err);
		//cout << "stat     for bin " << bin << ": " << h_fake->GetBinContent(bin) << endl;
		//cout << "stat err for bin " << bin << ": " << stat_err << endl;
		//cout << "syst err for bin " << bin << ": " << syst_err << endl;
		h_fake->SetBinError(bin, err);
	}
	//h_fake->Draw();
	
	// Get Canvas and pad
	TCanvas* c = new TCanvas("canvas", "", 720, 800);
	TLegend* l = new TLegend(0.69, 0.65, 0.95, 0.92);
	TLatex* lumi = new TLatex();
	TPad* pUp = new TPad("pUp", "", 0, 0.25, 1, 1);
	TPad* pDown = new TPad("pDown", "", 0, 0, 1, 0.25);

	TString lumi_info;
	if (DataYear.Contains("2016")) lumi_info = "L^{int} = 35.9 fb^{-1} (13TeV)";
	else if (DataYear.Contains("2017")) lumi_info = "L^{int} = 41.5 fb^{-1} (13Tev)";
	else if (DataYear.Contains("2018")) lumi_info = "L^{int} = 59.7 fb^{-1} (13TeV)";
	else {
		cerr << "Wrong DataYear" << endl;
		exit(EXIT_FAILURE);
	}
	lumi->SetTextSize(0.04);
	lumi->SetTextFont(42);

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

	// h_data setting
	double y_range = h_data->GetMaximum();
	h_data->SetMarkerStyle(8);
    h_data->SetMarkerSize(0.5);
    h_data->SetMarkerColor(kBlack);
    h_data->SetStats(0);
    h_data->GetXaxis()->SetLabelSize(0);
    h_data->GetYaxis()->SetTitle(yAxisName);
	h_data->GetYaxis()->SetRangeUser(0, y_range * 1.8);
	if (logy) h_data->GetYaxis()->SetRangeUser(1, y_range*10);
	//h_data->Draw("p&hist");
    
	l->AddEntry(h_data, "Data", "lep");

	// h_syst setting
    h_syst = (TH1D*)h_fake->Clone("h_syst");
    h_syst->Add(h_DY);
	h_syst->Add(h_TT);
	h_syst->Add(h_others);
	h_syst->Add(h_tX);
	h_syst->Add(h_VV);
	h_syst->SetStats(0);
    h_syst->SetFillColorAlpha(kBlack, 0.3);
    h_syst->SetFillStyle(3144);
    l->AddEntry(h_syst, "stat+syst(fake)", "f");
	//h_syst->Draw("e2&f&same");

	// h_stack setting
	h_others->SetFillColorAlpha(kAzure, 0.5);
	h_tX->SetFillColorAlpha(kBlue, 0.5);
	h_VV->SetFillColorAlpha(kOrange, 0.9);
	h_TT->SetFillColorAlpha(kRed, 0.5);
	h_DY->SetFillColorAlpha(kGreen, 0.7);
	h_fake->SetFillColorAlpha(kViolet, 0.7);
	l->AddEntry(h_fake, "fake", "f");
	l->AddEntry(h_DY, "DY", "f");
	l->AddEntry(h_TT, "TT", "f");
	l->AddEntry(h_VV, "VV", "f");
	l->AddEntry(h_tX, "tX", "f");
	l->AddEntry(h_others, "others", "f");
	
	h_stack = new THStack("hs", "");
	h_stack->Add(h_others);
	h_stack->Add(h_tX);
	h_stack->Add(h_VV);
	h_stack->Add(h_TT);
	h_stack->Add(h_DY);
	h_stack->Add(h_fake);
	//h_stack->Draw("hist&same");
	//h_data->Draw("p&hist&same");
	
	// h_comp setting
	h_comp = (TH1D*)h_data->Clone("h_comp");
	h_comp->Divide(h_syst);
	h_comp_syst = (TH1D*)h_comp->Clone("h_comp_syst");

	h_comp->GetYaxis()->SetRangeUser(0.5, 1.5);
    h_comp->SetStats(0);
    h_comp->SetMarkerStyle(8);
    h_comp->SetMarkerSize(0.5);
    h_comp->GetYaxis()->SetLabelSize(0.06);
    h_comp->GetYaxis()->SetTitle("Data/Pred");
    h_comp->GetYaxis()->SetTitleSize(0.08);
    h_comp->GetYaxis()->SetTitleOffset(0.5);
    h_comp->GetXaxis()->SetLabelSize(0.08);
    h_comp->GetXaxis()->SetTitle(xAxisName);
    h_comp->GetXaxis()->SetTitleSize(0.1);
    h_comp->GetXaxis()->SetTitleOffset(0.8);

	h_comp_syst->SetFillColorAlpha(kBlack, 0.3);
    h_comp_syst->SetFillStyle(3144);

	// Draw on canvas
	pUp->cd();
	h_data->Draw("p&hist");
	h_stack->Draw("hist&same");
	h_data->Draw("e1&same");
	h_syst->Draw("e2&f&same");
	if (logy) pUp->SetLogy();
	l->Draw("same");
	lumi->DrawLatexNDC(0.67, 0.93, lumi_info);

	pDown->cd();
	h_comp->Draw("p&hist");
	h_comp_syst->Draw("e2&f&same");

	c->cd();
	lumi->Draw();
	pUp->Draw();
	pDown->Draw();
	//c->SaveAs(DataYear + ".png");
	c->Draw();
}
