#include "FileNavi.h"
#include "FileNavi.cpp"

void Macro_param(TString DataYear, TString userflag, TString region, TString obj, TString dist) {
	
	TString pathData = "$PWD/../input/" + DataYear + "/" + userflag + "__/DATA/";
	TString pathMC = "$PWD/../input/" + DataYear + "/" + userflag + "__/MCSamples/";
	vector<TString> Samples{"DoubleMuon", "prompt"};

	FileNavi navi(pathData, pathMC, Samples);

	//==== AxisName ====
	TString xAxisName = "";
	TString yAxisName = "Events";
	if (dist.Contains("pt")) {
		yAxisName = "Events / 10 GeV";
		if (obj.Contains("METv")) xAxisName = "E_{T}^{miss}";
		else xAxisName = "p_{T}";
	}
	if (dist.Contains("eta")) xAxisName = "#eta";
	if (dist.Contains("phi")) xAxisName = "#phi";
	if (dist.Contains("RelIso")) xAxisName = "I^{rel}";

	//==== Get histograms ====
	TH1D* h_data = nullptr;
	TH1D* h_prompt = nullptr;
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

	// prompt
	TString p_prompt = region + "/" + obj + "/" + dist;
	cout << "p_prompt: " << p_prompt << endl;
	h_prompt = (TH1D*) navi.GetHist("prompt", p_prompt);
	//h_prompt->Draw();
	
	// rebin
	if (dist.Contains("pt")) {
		h_data->Rebin(10);
		h_prompt->Rebin(10);
		h_fake->Rebin(10);
	}

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

	// h_data setting
	double y_range = h_data->GetMaximum();
	h_data->SetMarkerStyle(8);
    h_data->SetMarkerSize(0.5);
    h_data->SetMarkerColor(kBlack);
    h_data->SetStats(0);
    h_data->GetXaxis()->SetLabelSize(0);
    h_data->GetYaxis()->SetTitle(yAxisName);
	h_data->GetYaxis()->SetRangeUser(0, y_range * 1.5);
	//h_data->Draw("p&hist");
    
	l->AddEntry(h_data, "Data", "lep");

	// h_syst setting
    h_syst = (TH1D*)h_fake->Clone("h_syst");
    h_syst->Add(h_prompt);
	h_syst->SetStats(0);
    h_syst->SetFillColorAlpha(kBlack, 0.4);
    h_syst->SetFillStyle(3144);
    l->AddEntry(h_syst, "stat+syst(fake)", "f");
	h_syst->Draw("e2&f&same");

	// h_stack setting
	h_prompt->SetFillColorAlpha(kAzure, 0.5);
	h_fake->SetFillColorAlpha(kRed, 0.5);
	l->AddEntry(h_prompt, "prompt", "f");
	l->AddEntry(h_fake, "fake", "f");
	
	h_stack = new THStack("hs", "");
	h_stack->Add(h_prompt);
	h_stack->Add(h_fake);
	h_stack->Draw("hist&same");
	h_data->Draw("p&hist&same");
	
	// h_comp setting
	h_comp = (TH1D*)h_data->Clone("h_comp");
	h_comp->Divide(h_syst);
	h_comp_syst = (TH1D*)h_comp->Clone("h_comp_syst");

	h_comp->GetYaxis()->SetRangeUser(0, 2);
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

	h_comp_syst->SetFillColorAlpha(kBlack, 0.4);
    h_comp_syst->SetFillStyle(3144);

	// Draw on canvas
	pUp->cd();
	h_data->Draw("p&hist");
	h_stack->Draw("hist&same");
	h_data->Draw("e1&same");
	h_syst->Draw("e2&f&same");
	l->Draw("same");

	pDown->cd();
	h_comp->Draw("p&hist");
	h_comp_syst->Draw("e2&f&same");

	c->cd();
	pUp->Draw();
	pDown->Draw();
	c->Draw();

}
