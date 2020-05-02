#include "TdrStyle.C"
#include <vector>

struct Hist {
  TString histname;
  TString sample;
  TString wp;
  TString syst;
  TH1D* hist;
};

TDirectory* GetDirectory(TString, TString, TString);
TH1D* GetHist(TString, TString, TString, TString);
Double_t GetScale(TString, TString);
TString xAxisName = "", yAxisName = "";
void MakeHist(Hist* H, TString sample, TString histname, TString wp, TString syst);
void SetHist(Hist*, TLegend*);
void SetHist(vector<Hist*>, TLegend*);
void SetCompare(TH1D*);
void SetStack(THStack*, TString);
void SetLumi(TLatex*);
void SetLogo(TLatex*, TLatex*);
void SetPadUp(TPad*);
void SetPadDown(TPad*);

//==================================================
//================ Basic Information ===============
//==================================================

TString pathData = "/Users/choij/FakeEstimator/Outputs/2016/RunSysts__/DATA/";
TString pathMC = "/Users/choij/FakeEstimator/Outputs/2016/RunSysts__/";
TString Analyzer = "FakeEstimator_";
TString Year = "_2016";
TString suffix = ".root";

TString DataSample = "DoubleEG", MCSample = "MC";
vector<TString> Samples = {"tt", "DYJets", "WJets_MG", "tW", "SingleTop", "VV"};

vector<TString> WPs = {"Loose", "Tight"};
vector<TString> Systs = {"Central", "Syst_FlavorDependence", "Syst_JetPtCutDown", "Syst_JetPtCutUp"};

vector<TString> HistNames = {
  // QCD enriched region 0~5
  "corrPt_QCD_enriched", "electron_eta_QCD_enriched",
  "leading_jet_pt_QCD_enriched", "leading_jet_eta_QCD_enriched",
  "subleading_jet_pt_QCD_enriched", "subleading_jet_eta_QCD_enriched",
  // W enriched region 6~12
  "Mt_W_enriched",
  "MET_W_enriched", "MET_eta_W_enriched",
  "leading_jet_pt_W_enriched", "leading_jet_eta_W_enriched",
  "electron_pt_W_enriched", "electron_eta_W_enriched",
  // Z enriched region 13~19
  "M(ee)_Z_enriched",
  "leading_jet_pt_Z_enriched", "leading_jet_eta_Z_enriched",
  "leading_electron_pt_Z_enriched", "leading_electron_eta_Z_enriched",
  "subleading_electron_pt_Z_enriched", "subleading_electron_eta_Z_enriched"
  };

/////////////////////////////////////////////////////////////
//================  main function ===========================
/////////////////////////////////////////////////////////////

void DrawStack() {

  // ++++ User Define Settings ++++++++++++++++++++++++++++++++++++
  // ++++ Set Histogram, Working Point, Systematic information ++++
  //int hist = 4;
  int wp = 1;
  int syst = 3;

for (int hist = 0; hist < HistNames.size(); hist++) {
  // ++++ Set Canvas, Pad, Legend size and position +++++++++++++++
  TCanvas* cvs = new TCanvas("cvs", "cvs", 720, 800);
  TPad* pad_up = new TPad("pad_up", "pad_up", 0, 0.25, 1, 1);
  TPad* pad_down = new TPad("pad_down", "pad_down", 0, 0, 1, 0.25);

  TLegend* leg = new TLegend(0.69, 0.65, 0.93, 0.88);




  ///////////////////////////////////////////////////////////
  //============= 1.Histograms Preparation ==================
  ///////////////////////////////////////////////////////////

  //============= Navigation =====================

  vector<Hist*> HistsMC(Samples.size());
  Hist* HistData = new Hist;
  Hist* HistMC = new Hist;

  for (int i = 0; i < Samples.size(); i++) {
	HistsMC[i] = new Hist;
	MakeHist(HistsMC[i], Samples.at(i), HistNames.at(hist), WPs.at(wp), Systs.at(syst));
  }
  MakeHist(HistData, DataSample, HistNames.at(hist), WPs.at(wp), Systs.at(syst));
  MakeHist(HistMC, MCSample, HistNames.at(hist), WPs.at(wp), Systs.at(syst));
  //HistsMC.at(2)->hist->Draw();

  //============== Settings ====================
  // Scale is already set when calling SetHist
  SetHist(HistData, leg);
  SetHist(HistsMC, leg);



  ////////////////////////////////////////////////////////////
  //============= 2. Manipulate Histograms ===================
  ////////////////////////////////////////////////////////////

  //============= Manipulation ================
  TH1D* hist_compare = NULL;
  THStack* hstack = new THStack;

  TH1D* temp = HistMC->hist; temp->Scale(GetScale(WPs.at(wp), Systs.at(syst)));
  hist_compare = (TH1D*) HistData->hist->Clone("");
  hist_compare->Divide(temp);

  for (int i = 0; i < Samples.size(); i++) {
  	hstack->Add(HistsMC.at(i)->hist);
  }
  //============== Settings =====================
  SetCompare(hist_compare);
  SetStack(hstack, HistNames.at(hist));
  //hstack->GetYaxis()->SetTitle(yAxisName);
  //hstack->GetYaxis()->SetTitleSize(0.04);
  //hstack->GetYaxis()->SetTitleOffset(1.5);
  //hstack->GetXaxis()->SetLabelSize(0);
  //hstack->GetYaxis()->SetLabelSize(0.04);

  ////////////////////////////////////////////////////////////
  //============ 4. Final Drawing ============================
  ////////////////////////////////////////////////////////////
  SetTDRStyle();
  SetPadUp(pad_up);
  SetPadDown(pad_down);

  TLatex* lumi = new TLatex;
  TLatex* logo = new TLatex;
  TLatex* extralogo = new TLatex;

  cvs->cd();
  pad_up->Draw();
  pad_down->Draw();
  
  //============= pad_up =====================
  pad_up->cd();

  if (hist >= 0 && hist <= 12) {
	HistData->hist->Draw();
	hstack->Draw("histfsame");
	HistData->hist->Draw("sameaxis");
	hstack->Draw("same");
	HistData->hist->Draw("pe1same");
  }

  else if (hist >= 13 || hist <= 19) {
	hstack->Draw("histf");
	HistData->hist->Draw("sameaxis");
	HistData->hist->Draw("pe1same");
	hstack->Draw("same");
  }

  else exit(EXIT_FAILURE);

  leg->Draw("same");

  SetLumi(lumi);
  SetLogo(logo, extralogo);

  pad_up->Paint();

  //================ pad_down =================
  pad_down->cd();
  hist_compare->Draw("pe1same");
  pad_down->Paint();

  //================= Draw Canvas =============
  //cvs->Draw();
  cvs->SaveAs(HistNames.at(hist) + "_" +  WPs.at(wp) + "_" + Systs.at(syst) + ".pdf");
  cvs->Clear();  cvs->Close();
  delete HistData; delete HistMC; delete hstack;
}
}




//=====================================================
//================ Private Functions ==================
//=====================================================

TDirectory* GetDirectory(TString sample, TString wp, TString syst) {
  TDirectory* temp_dir = NULL;
  if (sample == DataSample) {
	TFile* f = new TFile(pathData + Analyzer + DataSample + Year + suffix);
	temp_dir = (TDirectory*) f->GetDirectory(wp + "_" + syst);
  }
  else {
	TFile* f = new TFile(pathMC + Analyzer + sample + suffix);
	temp_dir = (TDirectory*) f->GetDirectory(wp + "_" + syst);
  }

  return temp_dir;
}

TH1D* GetHist(TString sample, TString histname, TString wp, TString syst) {
  TH1D* temp_hist = NULL;
  TDirectory* temp_dir = GetDirectory(sample, wp, syst);
  temp_hist = (TH1D*) temp_dir->Get(histname + "_" + wp + "_" + syst);
  
  return temp_hist;
}

Double_t GetScale(TString wp, TString syst) {
  TH1D* hist_data = GetHist(DataSample, "Mt_W_enriched", wp, syst);
  TH1D* hist_mc = GetHist(MCSample, "Mt_W_enriched", wp, syst);

  Double_t scale = hist_data->Integral() / hist_mc->Integral();

  return scale;
}

void MakeHist(Hist* H, TString sample, TString histname, TString wp, TString syst) {
  TH1D* temp = GetHist(sample, histname, wp, syst);

  H->histname = histname;
  H->sample = sample;
  H->hist = temp;
  H->wp = wp;
  H->syst = syst;
}

void SetHist(Hist* H, TLegend* leg) {

  H->hist->SetTitle(H->histname);
  H->hist->SetStats(0);

  if (H->histname.Contains("Mt")) {
	xAxisName = "M_{T}(e, E_{T}^{miss}) (GeV)";
    yAxisName = "Events / 5GeV";
  }
  else if (H->histname.Contains("M(ee)")) {
    xAxisName = "M(ee) (GeV)";
    yAxisName = "Events / 5GeV";
  }
  else if (H->histname.Contains("nPV")) {
    xAxisName = "nPV";
    yAxisName = "Events";
  }
  else if (H->histname.Contains("corrPt")) {
	xAxisName = "p_{T}^{Corr}(e)";
	yAxisName = "Events / 5GeV";
  }
  else if (H->histname.Contains("electron_eta")) {
	xAxisName = "#eta(e)";
	yAxisName = "Events";
  }
  else if (H->histname.Contains("electron_pt")) {
	xAxisName = "p_{T}(e)";
	yAxisName = "Events / 5GeV";
  }
  else if (H->histname.Contains("jet_eta")) {
	xAxisName = "#eta(j)";
	yAxisName = "Events";
  }
  else if (H->histname.Contains("jet_pt")) {
	xAxisName = "p_{T}(j)";
	yAxisName = "Events / 5GeV";
  }
  else if (H->histname.Contains("MET")) {
	xAxisName = "E_{T}^{miss} (GeV)";
	yAxisName = "Events / 5GeV";
	if (H->histname.Contains("eta")) {
	  xAxisName = "#eta(E_{T}^{miss})";
	  yAxisName = "Events";
	}
  }
  else {
	xAxisName = "";
	yAxisName = "";
  }
  // title

  H->hist->GetYaxis()->SetTitle(yAxisName);
  H->hist->GetYaxis()->SetTitleSize(0.04);
  H->hist->GetYaxis()->SetTitleOffset(1.5);

  // axis range
  //H->hist->GetXaxis()->SetRangeUser(,);
  //H->hist->GetYaxis()->SetRangeUser(0, 1200);
  
  // axis label
  H->hist->GetXaxis()->SetLabelSize(0);
  H->hist->GetYaxis()->SetLabelSize(0.03);

  // marker
  H->hist->SetMarkerStyle(8);
  H->hist->SetMarkerSize(0.5);


  leg->AddEntry(H->hist, "Data", "lep");
}

void SetHist(vector<Hist*> Hs, TLegend* leg) {
  Double_t scale = GetScale(Hs.at(0)->wp, Hs.at(0)->syst);
  //cout << Hs.size() << endl;
  for (int i = 0; i < Hs.size(); i++) {
	Hs.at(i)->hist->Scale(scale);
	Hs.at(i)->hist->SetStats(0);
	if (Hs.at(i)->sample =="tt") {
      Hs.at(i)->hist->SetFillColorAlpha(kBlue, 0.7);
	  Hs.at(i)->hist->SetLineColor(kBlack);
	}
    else if (Hs.at(i)->sample =="DYJets") {
      Hs.at(i)->hist->SetFillColorAlpha(kGreen, 0.7);
      Hs.at(i)->hist->SetLineColor(kBlack);
	}
	else if (Hs.at(i)->sample == "SingleTop") {
      Hs.at(i)->hist->SetFillColorAlpha(kRed, 0.7);
      Hs.at(i)->hist->SetLineColor(kBlack);
	}
	else if (Hs.at(i)->sample == "tW") {
	  Hs.at(i)->hist->SetFillColorAlpha(kGray, 0.7);
      Hs.at(i)->hist->SetLineColor(kBlack);
	}
    else if (Hs.at(i)->sample == "WJets_MG") {
	  Hs.at(i)->hist->SetFillColorAlpha(kViolet, 0.7);
      Hs.at(i)->hist->SetLineColor(kBlack);
	}
    else if (Hs.at(i)->sample == "VV") {
      Hs.at(i)->hist->SetFillColorAlpha(kCyan, 0.7);
      Hs.at(i)->hist->SetLineColor(kBlack);
	}
    else {
	  cout << "[SetHist] No Matching Sample" << endl;
	  exit(EXIT_FAILURE);
	}
	leg->AddEntry(Hs.at(i)->hist, Hs.at(i)->sample, "f");
  }
}

void SetStack(THStack* stack, TString histname) {
  stack->SetTitle(histname);
  
  if (histname.Contains("Mt")) {
    xAxisName = "M_{T}(e, E_{T}^{miss}) (GeV)";
    yAxisName = "Events / 5GeV";
  }
  else if (histname.Contains("M(ee)")) {
    xAxisName = "M(ee) (GeV)";
    yAxisName = "Events / 5GeV";
  }
  else if (histname.Contains("nPV")) {
    xAxisName = "nPV";
    yAxisName = "Events";
  }
  else if (histname.Contains("corrPt")) {
    xAxisName = "p_{T}^{Corr}(e)";
    yAxisName = "Events / 5GeV";
  }
  else if (histname.Contains("electron_eta")) {
    xAxisName = "#eta(e)";
    yAxisName = "Events";
  }
  else if (histname.Contains("electron_pt")) {
    xAxisName = "p_{T}(e)";
    yAxisName = "Events / 5GeV";
  }
  else if (histname.Contains("jet_eta")) {
    xAxisName = "#eta(j)";
    yAxisName = "Events";
  }
  else if (histname.Contains("jet_pt")) {
    xAxisName = "p_{T}(j)";
    yAxisName = "Events / 5GeV";
  }
  else if (histname.Contains("MET")) {
    xAxisName = "E_{T}^{miss} (GeV)";
    yAxisName = "Events / 5GeV";
    if (histname.Contains("eta")) {
      xAxisName = "#eta(E_{T}^{miss})";
      yAxisName = "Events";
    }
  }
  else {
    xAxisName = "";
    yAxisName = "";
  }
  stack->Draw();
  // title
  stack->GetYaxis()->SetTitle(yAxisName);
  stack->GetYaxis()->SetTitleSize(0.04);
  stack->GetYaxis()->SetTitleOffset(1.7);

  // axis label
  stack->GetXaxis()->SetLabelSize(0);
  stack->GetYaxis()->SetLabelSize(0.04);

}

void SetCompare(TH1D* compare) {
  compare->SetStats(0);
  compare->SetTitle("");
  cout << xAxisName << endl;
  compare->GetXaxis()->SetTitle(xAxisName);
  compare->GetXaxis()->SetTitleSize(0.08);
  compare->GetXaxis()->SetTitleOffset(1);
  compare->GetXaxis()->SetLabelSize(0.08);

  compare->GetYaxis()->SetRangeUser(0, 2);
  compare->GetYaxis()->SetTitle("Data/Pred");
  compare->GetYaxis()->SetTitleSize(0.1);
  compare->GetYaxis()->SetTitleOffset(0.5);
  compare->GetYaxis()->SetLabelSize(0.07);

  compare->SetMarkerStyle(8);
  compare->SetMarkerSize(0.5);
  compare->SetFillColorAlpha(45, 0.35);
  
  //compare->SetNdivisions(504, "Y");

}

void SetPadUp(TPad* pad) {
  pad->SetTopMargin(0.08);
  pad->SetBottomMargin(0.02);
  pad->SetLeftMargin(0.15);
  pad->SetRightMargin(0.05);
  pad->SetGrid();
}

void SetPadDown(TPad* pad) {
  pad->SetTopMargin(0.05);
  pad->SetBottomMargin(0.45);
  pad->SetLeftMargin(0.15);
  pad->SetRightMargin(0.05);
  pad->SetGrid();
}
void SetLumi(TLatex* lumi) {
  TString lumi_13TeV = "#it{L}^{int} = 0.063 fb^{-1} (13TeV)";

  lumi->SetTextSize(0.035);
  lumi->SetTextFont(42);
  lumi->DrawLatexNDC(0.675, 0.925, lumi_13TeV);
}

void SetLogo(TLatex* logo, TLatex* extra) {
  TString cmsText = "CMS";
  TString extraText = "Preliminary";

  logo->SetTextSize(0.04);
  logo->SetTextFont(61);
  logo->DrawLatexNDC(0.16, 0.925, cmsText);
  extra->SetTextSize(0.035);
  extra->SetTextFont(52);
  extra->DrawLatexNDC(0.24, 0.925, extraText);
}
