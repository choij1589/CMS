#include "TdrStyle.C"

//==== files information ====
TString pathData = "/Users/choij/FakeEstimator/Outputs/2016/RunSysts__/DATA/FakeEstimator_DoubleEG_2016.root";
TString pathMC = "/Users/choij/FakeEstimator/Outputs/2016/RunSysts__/FakeEstimator_MC.root";

TFile* f_data = new TFile(pathData);
TFile* f_mc = new TFile(pathMC);

vector<TString> WPs = {"Loose", "Tight"};
vector<TString> Systs = {"Central", "Syst_FlavorDependence", "Syst_JetPtCutDown", "Syst_JetPtCutUp"};

//==== function declarations ====
TDirectory* GetDirectory(bool isData, TString wp, TString syst);
TH2D* GetHistogram(TDirectory* dir, TString histname);
Double_t GetScale(TString wp, TString syts);
TH2D* MakeFake2D(TString syst);
TH2D* MakeFake2D(int syst);
TH1D* MakeFake1D(int syst);
TCanvas* DrawFake1DPlot(TString syst);
TCanvas* DrawFake1DPlot(int syst);


//=======================================
//========= Main Function ===============
//=======================================
void DrawFake1D() {
  int i = 3;
  TCanvas* c = DrawFake1DPlot(Systs.at(i));
  c->SaveAs("FR_" + Systs.at(i) + ".pdf");

  //TCanvas* c = DrawFake1DPlot(i);
  //if (i == 0) c->SaveAs("FR_Norm.pdf");
  //else if (i == -1) c->SaveAs("FR_Norm_Down.pdf");
  //else if (i == 1) c->SaveAs("FR_Norm_Up.pdf");
  //else exit(EXIT_FAILURE);

  c->Clear(); c->Close();
}

//==== Private Functions ====
TDirectory* GetDirectory(bool isData, TString wp, TString syst) {
  TDirectory* temp_dir = NULL;

  if (isData == true) {
    temp_dir = (TDirectory*)f_data->GetDirectory(wp + "_" + syst);
  }
  else {
    temp_dir = (TDirectory*)f_mc->GetDirectory(wp + "_" + syst);
  }

  return temp_dir;
}

TH2D* GetHistogram(TDirectory* dir, TString histname) {
  TH2D* hist = (TH2D*)dir->Get(histname);
  return hist;
}

Double_t GetScale(TString wp, TString syst) {
  TDirectory* dir_data = GetDirectory(1, wp, syst); TDirectory* dir_mc = GetDirectory(0, wp, syst);

  TH1D* h_data = (TH1D*) dir_data->Get("Mt_W_enriched_" + wp + "_" + syst);
  TH1D* h_mc = (TH1D*) dir_mc->Get("Mt_W_enriched_" + wp + "_" + syst);

  Double_t scale = h_data->Integral() / h_mc->Integral();

  return scale;
}

TH2D* MakeFake2D(TString syst) {
  TDirectory* dir_data_loose = GetDirectory(1, "Loose", syst);
  TDirectory* dir_mc_loose = GetDirectory(0, "Loose", syst);
  TDirectory* dir_data_tight = GetDirectory(1, "Tight", syst);
  TDirectory* dir_mc_tight = GetDirectory(0, "Tight", syst);

  TH2D* h_data_loose = GetHistogram(dir_data_loose, "nEvent_QCD_enriched_pass_Loose_" + syst);
  TH2D* h_mc_loose = GetHistogram(dir_mc_loose, "nEvent_QCD_enriched_pass_Loose_" + syst);
  Double_t scale_loose = GetScale("Loose", syst);
  h_data_loose->Add(h_mc_loose, scale_loose * -1);

  TH2D* h_data_tight = GetHistogram(dir_data_tight, "nEvent_QCD_enriched_pass_Tight_" + syst);
  TH2D* h_mc_tight = GetHistogram(dir_mc_tight, "nEvent_QCD_enriched_pass_Tight_" + syst);
  Double_t scale_tight = GetScale("Tight", syst);
  h_data_tight->Add(h_mc_tight, scale_tight * -1);

  TH2D* h_fake = (TH2D*)h_data_tight->Clone("fake rate");
  h_fake->Divide(h_data_loose);

  return h_fake;
}

TH2D* MakeFake2D(int syst) {
  // Varaition for prompt subtraction
  TDirectory* dir_data_loose = GetDirectory(1, "Loose", "Central");
  TDirectory* dir_mc_loose = GetDirectory(0, "Loose", "Central");
  TDirectory* dir_data_tight = GetDirectory(1, "Tight", "Central");
  TDirectory* dir_mc_tight = GetDirectory(0, "Tight", "Central");

  TH2D* h_data_loose = GetHistogram(dir_data_loose, "nEvent_QCD_enriched_pass_Loose_Central");
  TH2D* h_mc_loose = GetHistogram(dir_mc_loose, "nEvent_QCD_enriched_pass_Loose_Central");
  Double_t scale_loose = GetScale("Loose", "Central");
  if (syst == 0) h_data_loose->Add(h_mc_loose, scale_loose * -1);
  else if (syst == -1) h_data_loose->Add(h_mc_loose, scale_loose * -0.85);
  else if (syst == 1) h_data_loose->Add(h_mc_loose, scale_loose * 1.15);
  else {
	cout << "[MakeFake2D] syst should be 0, -1, 1" << endl;
	exit(EXIT_FAILURE);
  }

  TH2D* h_data_tight = GetHistogram(dir_data_tight, "nEvent_QCD_enriched_pass_Tight_Central");
  TH2D* h_mc_tight = GetHistogram(dir_mc_tight, "nEvent_QCD_enriched_pass_Tight_Central");
  Double_t scale_tight = GetScale("Tight", "Central");
  if (syst == 0) h_data_tight->Add(h_mc_tight, scale_tight * -1);
  else if (syst == -1) h_data_tight->Add(h_mc_tight, scale_tight * -0.85);
  else if (syst == 1) h_data_tight->Add(h_mc_tight, scale_tight * 1.15);
  else {
	cout << "[MakeFake2D] syst should be 0, -1, 1" << endl;
	exit(EXIT_FAILURE);
  }

  TH2D* h_fake = (TH2D*)h_data_tight->Clone("fake rate");
  h_fake->Divide(h_data_loose);

  return h_fake;
}

TH1D* MakeFake1D(TString syst) {
  // for compare plots
  TDirectory* dir_data_loose = GetDirectory(1, "Loose", syst);
  TDirectory* dir_mc_loose = GetDirectory(0, "Loose", syst);
  TDirectory* dir_data_tight = GetDirectory(1, "Tight", syst);
  TDirectory* dir_mc_tight = GetDirectory(0, "Tight", syst);

  TH2D* h_data_loose = GetHistogram(dir_data_loose, "nEvent_QCD_enriched_pass_Loose_" + syst);
  TH2D* h_mc_loose = GetHistogram(dir_mc_loose, "nEvent_QCD_enriched_pass_Loose_" + syst);
  Double_t scale_loose = GetScale("Loose", syst);
  TH1D* h_data_loose_px = h_data_loose->ProjectionX("px_data");
  TH1D* h_mc_loose_px = h_mc_loose->ProjectionX("px_mc");
  h_data_loose_px->Add(h_mc_loose_px, scale_loose * -1);

  TH2D* h_data_tight = (TH2D*)GetHistogram(dir_data_tight, "nEvent_QCD_enriched_pass_Tight_" + syst);
  TH2D* h_mc_tight = (TH2D*)GetHistogram(dir_mc_tight, "nEvent_QCD_enriched_pass_Tight_" + syst);
  Double_t scale_tight = GetScale("Tight", syst);
  TH1D* h_data_tight_px = h_data_tight->ProjectionX("px_data_tight");
  TH1D* h_mc_tight_px = h_mc_tight->ProjectionX("px_mc_tight");
  h_data_tight_px->Add(h_mc_tight_px, scale_tight * -1);

  TH1D* h_temp = (TH1D*)h_data_tight_px->Clone("fake 1D");
  h_temp->Divide(h_data_loose_px);

  return h_temp;
}

TH1D* MakeFake1D(int syst) {
  // for compare plots
  TDirectory* dir_data_loose = GetDirectory(1, "Loose", "Central");
  TDirectory* dir_mc_loose = GetDirectory(0, "Loose", "Central");
  TDirectory* dir_data_tight = GetDirectory(1, "Tight", "Central");
  TDirectory* dir_mc_tight = GetDirectory(0, "Tight", "Central");

  TH2D* h_data_loose = GetHistogram(dir_data_loose, "nEvent_QCD_enriched_pass_Loose_Central");
  TH2D* h_mc_loose = GetHistogram(dir_mc_loose, "nEvent_QCD_enriched_pass_Loose_Central");
  Double_t scale_loose = GetScale("Loose", "Central");
  TH1D* h_data_loose_px = h_data_loose->ProjectionX("px_data");
  TH1D* h_mc_loose_px = h_mc_loose->ProjectionX("px_mc");
  if (syst == 0) h_data_loose_px->Add(h_mc_loose_px, scale_loose * -1);
  else if (syst == -1) h_data_loose_px->Add(h_mc_loose_px, scale_loose * -0.85);
  else if (syst == 1) h_data_loose_px->Add(h_mc_loose_px, scale_loose * 1.15);
  else {
	cout << "[MakeFake1D] syst should be 0, -1, 1" << endl;
	exit(EXIT_FAILURE);
  }

  TH2D* h_data_tight = (TH2D*)GetHistogram(dir_data_tight, "nEvent_QCD_enriched_pass_Tight_Central");
  TH2D* h_mc_tight = (TH2D*)GetHistogram(dir_mc_tight, "nEvent_QCD_enriched_pass_Tight_Central");
  Double_t scale_tight = GetScale("Tight", "Central");
  TH1D* h_data_tight_px = h_data_tight->ProjectionX("px_data_tight");
  TH1D* h_mc_tight_px = h_mc_tight->ProjectionX("px_mc_tight");
  if (syst == 0) h_data_tight_px->Add(h_mc_tight_px, -1);
  else if (syst == -1) h_data_tight_px->Add(h_mc_tight_px, -0.85);
  else if (syst == 1) h_data_tight_px->Add(h_mc_tight_px, 1.15);
  else {
	cout << "[MakeFake1D] syst should be 0, -1, 1" << endl;
	exit(EXIT_FAILURE);
  }

  TH1D* h_temp = (TH1D*)h_data_tight_px->Clone("fake 1D");
  h_temp->Divide(h_data_loose_px);
  
  return h_temp;
}

TCanvas* DrawFake1DPlot(TString syst) {
    SetTDRStyle();

    TCanvas* cvs = new TCanvas("cvs", "cvs", 750, 800);
    TPad* pad_up = new TPad("pad_up", "pad_up", 0, 0.3, 1, 1);
    TPad* pad_down = new TPad("pad_down", "pad_down", 0, 0, 1, 0.3);
    TLegend* leg = new TLegend(0.64, 0.68, 0.91, 0.88);

    TLatex* lumi = new TLatex;
    TLatex* logo = new TLatex;
    TLatex* extralogo = new TLatex;
    TString lumi_13TeV = "#it{L}^{int} = 0.063 fb^{-1} (13TeV)";
    TString cmsText = "CMS";
    TString extraText = "Preliminary";

    pad_up->SetTopMargin(0.08); pad_up->SetBottomMargin(0.02);
    pad_up->SetLeftMargin(0.15); pad_up->SetRightMargin(0.05);
    pad_up->SetGrid();
    pad_down->SetTopMargin(0.05); pad_down->SetBottomMargin(0.45);
    pad_down->SetLeftMargin(0.15); pad_down->SetRightMargin(0.05);
    pad_down->SetGrid();


    TH2D* h = MakeFake2D(syst);
    TH1D* h1 = h->ProjectionX("_px1", 1, 1);
    TH1D* h2 = h->ProjectionX("_px2", 2, 2);
    TH1D* h3 = h->ProjectionX("_px3", 3, 3);

    h1->SetLineColor(kRed);
    h1->GetXaxis()->SetLabelSize(0);
    h1->GetXaxis()->SetTitle("p^{Corr}_{T} (GeV)");
    h1->GetXaxis()->SetTitleSize(0);
    h1->GetYaxis()->SetTitle("fake rate");
    h1->GetYaxis()->SetTitleSize(0.05);
    h1->GetYaxis()->SetTitleOffset(1);
    h1->GetYaxis()->SetRangeUser(0., 0.5);
    h1->GetYaxis()->SetLabelSize(0.03);
    h1->SetStats(0);
    leg->AddEntry(h1, "0 < |#eta| < 0.8");

    h2->SetLineColor(kGreen);
    h2->SetStats(0);
    leg->AddEntry(h2, "0.8 < |#eta| < 1.479");

    h3->SetLineColor(kBlue);
    h3->SetStats(0);
    leg->AddEntry(h3, "1.479 < |#eta| < 2.5");

    TH1D* h_comp = MakeFake1D(syst);
	TH1D* h_central = MakeFake1D("Central");
	h_comp->Add(h_central, -1);
	h_comp->Divide(h_central);

    h_comp->SetLineColor(kBlack);
    h_comp->GetXaxis()->SetTitle("p^{Corr}_{T} (GeV)");
    h_comp->GetXaxis()->SetTitleSize(0.08);
    h_comp->GetYaxis()->SetRangeUser(-1, 1);
    h_comp->GetYaxis()->SetTitle("#Delta FR / FR");
    h_comp->GetYaxis()->SetTitleSize(0.09);
    h_comp->GetYaxis()->SetTitleOffset(0.5);
    h_comp->GetYaxis()->SetLabelSize(0.06);
    h_comp->SetStats(0);

    if (syst == "Central") {
        TLegend* leg_ = new TLegend(0.66, 0.7, 0.93, 0.9);
        leg_->AddEntry(h1, "0 < |#eta| < 0.8");
        leg_->AddEntry(h2, "0.8 < |#eta| < 1.479");
        leg_->AddEntry(h3, "1.479 < |#eta| < 2.5");

        cvs->cd();

        h1->GetXaxis()->SetLabelSize(0.03);
        h1->GetXaxis()->SetTitleSize(0.03);
        h1->GetXaxis()->SetTitleOffset(1.3);

        h1->GetYaxis()->SetTitleSize(0.04);
        h1->GetYaxis()->SetTitleOffset(1.7);
        h1->GetYaxis()->SetRangeUser(0., 0.5);
        h1->GetYaxis()->SetLabelSize(0.03);

        h1->Draw();
        h2->Draw("same");
        h3->Draw("same");

        lumi->SetTextSize(0.035);
        lumi->SetTextFont(42);
        lumi->DrawLatexNDC(0.65, 0.955, lumi_13TeV);

        logo->SetTextSize(0.04);
        logo->SetTextFont(61);
        logo->DrawLatexNDC(0.16, 0.955, cmsText);
        extralogo->SetTextSize(0.035);
        extralogo->SetTextFont(52);
        extralogo->DrawLatexNDC(0.245, 0.955, extraText);

        leg_->Draw("same");
        lumi->Draw();
        logo->Draw();
        extralogo->Draw();

    }
    else {
        cvs->cd();

        pad_up->Draw();
        pad_down->Draw();

        pad_up->cd();
        h1->Draw();
        h2->Draw("same");
        h3->Draw("same");
        leg->Draw("same");

        lumi->SetTextSize(0.04);
        lumi->SetTextFont(42);
        lumi->DrawLatexNDC(0.655, 0.93, lumi_13TeV);

        logo->SetTextSize(0.05);
        logo->SetTextFont(61);
        logo->DrawLatexNDC(0.15, 0.93, cmsText);
        extralogo->SetTextSize(0.045);
        extralogo->SetTextFont(52);
        extralogo->DrawLatexNDC(0.237, 0.93, extraText);

        lumi->Draw();
        logo->Draw();
        extralogo->Draw();
        //pad_up->BuildLegend();

        pad_up->Paint();

        pad_down->cd();
        h_comp->Draw();
        pad_down->Paint();
    }
    return cvs;
}

TCanvas* DrawFake1DPlot(int syst) {
    SetTDRStyle();

    TCanvas* cvs = new TCanvas("cvs", "cvs", 750, 800);
    TPad* pad_up = new TPad("pad_up", "pad_up", 0, 0.3, 1, 1);
    TPad* pad_down = new TPad("pad_down", "pad_down", 0, 0, 1, 0.3);
    TLegend* leg = new TLegend(0.64, 0.68, 0.91, 0.88);

    TLatex* lumi = new TLatex;
    TLatex* logo = new TLatex;
    TLatex* extralogo = new TLatex;
    TString lumi_13TeV = "#it{L}^{int} = 0.063 fb^{-1} (13TeV)";
    TString cmsText = "CMS";
    TString extraText = "Preliminary";

    pad_up->SetTopMargin(0.08); pad_up->SetBottomMargin(0.02);
    pad_up->SetLeftMargin(0.15); pad_up->SetRightMargin(0.05);
    pad_up->SetGrid();
    pad_down->SetTopMargin(0.05); pad_down->SetBottomMargin(0.45);
    pad_down->SetLeftMargin(0.15); pad_down->SetRightMargin(0.05);
    pad_down->SetGrid();


    TH2D* h = MakeFake2D(syst);
    TH1D* h1 = h->ProjectionX("_px1", 1, 1);
    TH1D* h2 = h->ProjectionX("_px2", 2, 2);
    TH1D* h3 = h->ProjectionX("_px3", 3, 3);

    h1->SetLineColor(kRed);
    h1->GetXaxis()->SetLabelSize(0);
    h1->GetXaxis()->SetTitle("p^{Corr}_{T} (GeV)");
    h1->GetXaxis()->SetTitleSize(0);
    h1->GetYaxis()->SetTitle("fake rate");
    h1->GetYaxis()->SetTitleSize(0.05);
    h1->GetYaxis()->SetTitleOffset(1);
    h1->GetYaxis()->SetRangeUser(0., 0.5);
    h1->GetYaxis()->SetLabelSize(0.03);
    h1->SetStats(0);
    leg->AddEntry(h1, "0 < |#eta| < 0.8");

    h2->SetLineColor(kGreen);
    h2->SetStats(0);
    leg->AddEntry(h2, "0.8 < |#eta| < 1.479");

    h3->SetLineColor(kBlue);
    h3->SetStats(0);
    leg->AddEntry(h3, "1.479 < |#eta| < 2.5");

    TH1D* h_comp = MakeFake1D(syst);
	TH1D* h_central = MakeFake1D(0);
	h_comp->Add(h_central, -1);
	h_comp->Divide(h_central);

    h_comp->SetLineColor(kBlack);
    h_comp->GetXaxis()->SetTitle("p^{Corr}_{T} (GeV)");
    h_comp->GetXaxis()->SetTitleSize(0.08);
    h_comp->GetYaxis()->SetRangeUser(-1, 1);
    h_comp->GetYaxis()->SetTitle("#Delta FR / FR");
    h_comp->GetYaxis()->SetTitleSize(0.09);
    h_comp->GetYaxis()->SetTitleOffset(0.5);
    h_comp->GetYaxis()->SetLabelSize(0.06);
    h_comp->SetStats(0);

    if (syst == 0) {
        TLegend* leg_ = new TLegend(0.66, 0.7, 0.93, 0.9);
        leg_->AddEntry(h1, "0 < |#eta| < 0.8");
        leg_->AddEntry(h2, "0.8 < |#eta| < 1.479");
        leg_->AddEntry(h3, "1.479 < |#eta| < 2.5");

        cvs->cd();

        h1->GetXaxis()->SetLabelSize(0.03);
        h1->GetXaxis()->SetTitleSize(0.03);
        h1->GetXaxis()->SetTitleOffset(1.3);

        h1->GetYaxis()->SetTitleSize(0.04);
        h1->GetYaxis()->SetTitleOffset(1.7);
        h1->GetYaxis()->SetRangeUser(0., 0.5);
        h1->GetYaxis()->SetLabelSize(0.03);

        h1->Draw();
        h2->Draw("same");
        h3->Draw("same");

        lumi->SetTextSize(0.035);
        lumi->SetTextFont(42);
        lumi->DrawLatexNDC(0.65, 0.955, lumi_13TeV);

        logo->SetTextSize(0.04);
        logo->SetTextFont(61);
        logo->DrawLatexNDC(0.16, 0.955, cmsText);
        extralogo->SetTextSize(0.035);
        extralogo->SetTextFont(52);
        extralogo->DrawLatexNDC(0.245, 0.955, extraText);

        leg_->Draw("same");
        lumi->Draw();
        logo->Draw();
        extralogo->Draw();

    }
    else {
        cvs->cd();
		cvs->SetGrid();

        pad_up->Draw();
        pad_down->Draw();

        pad_up->cd();
        h1->Draw();
        h2->Draw("same");
        h3->Draw("same");
        leg->Draw("same");

        lumi->SetTextSize(0.04);
        lumi->SetTextFont(42);
        lumi->DrawLatexNDC(0.655, 0.93, lumi_13TeV);

        logo->SetTextSize(0.05);
        logo->SetTextFont(61);
        logo->DrawLatexNDC(0.15, 0.93, cmsText);
        extralogo->SetTextSize(0.045);
        extralogo->SetTextFont(52);
        extralogo->DrawLatexNDC(0.237, 0.93, extraText);

        lumi->Draw();
        logo->Draw();
        extralogo->Draw();
        //pad_up->BuildLegend();

        pad_up->Paint();

        pad_down->cd();
        h_comp->Draw();
        pad_down->Paint();
    }
    return cvs;
}
