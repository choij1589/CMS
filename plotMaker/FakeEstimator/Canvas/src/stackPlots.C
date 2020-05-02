#include "TdrStyle.C"

void stackPlots() {
  
  // ==== 1. Input parameters - Default Value ====

  // ==== input file name info ====
  TString whichPath = "/home/choij/FakeEstimator/AnalyzerOutputs/2016/RunSysts__";
  TString whichYear = "2016";
  TString whichData = "DATA/";
  TString whichMC = "";

  TString fileName = "FakeEstimator_";

  // ==== Sample List Info ====
  bool trigSig = false, trigBkg = true, trigData = true;

  // ==== SingleMuon dataset ====
  const int nData = 1; TString dataName = "DoubleEG_" + whichYear;

  // ==== Signal Set ====
  const int nSig = 1;
  TString sigList[nSig] = {"TTLL_powheg"};

  // ==== Background Set ====
  const int nBkg = 6;
  TString bkgList[nBkg] = {"tt", "SingleTop", "tW", "DYJets", "WJets_MG", "VV"};

  // ==== Systematic Kinds ====
  /*
	 const int Nsyst = 1;
	 TString SystList[NSyst] = {"XSec"};
  */

  // ==== Hist Info ====
  bool trigDir = true; TString histDir = "Tight_Central";
  bool trig_2D = false;
    
  const int histNum = 5;
  TString histname[histNum];
  histname[0] = "M(ee)_Z_enriched_Tight_Central";
  histname[1] = "Mt_W_enriched_Tight_Central";
  histname[2] = "nEvent_QCD_enriched_Tight_Central";
  histname[3] = "nEvent_W_enriched_Tight_Central";
  histname[4] = "nPV_Tight_Central";
    
for (int i = 0; i < histNum; i++) {
  TString histName;
  histName = histname[i];
  TString title = histName;

  TString xAxisName = ""; TString yAxisName = "";

  int nRebinx = 1.; float scale = 1., sigScale = 1., bkgScale = 1.;
  bool periodScale = false, normToAll = false, normToBkg = false, normTo1 = false;

  bool xRange = false; double xRangeMin = 0., xRangeMax = 1.1e3;
  bool yRange = false; double yRangeMin = 0., yRangeMax = 1.1e6;
  bool zRange = false; double zRangeMin = 0., zRangeMax = 10000.;
  bool auto_xRange = true, auto_yRange = true, auto_zRange =true;
  float auto_yAxisMarginUp = 1.2;
  bool logY = false;
  bool xLabelCustom = false;
  int nBinCustomLabel = 0;
  std::vector<TString> xBinlabel;
  float xLabelSize = 0.04, yLabelSize = 0.04;
  float xTitleSize = 0.049, yTitleSize = 0.045;
  float xTitleOffset = 1.4, yTitleOffset = 1.2;
  float linewidth = 3., markerSize_data = 0.5; int markerStyle_data = 8;
  Color_t errColor = kBlack, errBaseColor = kRed;
  float errBaseOpacity = 0; int errFillStyle = 3354;
  TString drawOpt = "";

  bool trigComp = true;
  float xLabelSizeUp, yLabelSizeUp, xLabelSizeDown, yLabelSizeDown;
  float yTitleSizeUp, xTitleSizeDown, yTitleSizeDown;
  float yTitleOffsetUp, xTitleOffsetDown, yTitleOffsetDown;
  //float compYrangeMin = 0.5, compYrangeMax = 1.5; // Tight
  float compYrangeMin = -0., compYrangeMax = 2.; // Normal

  if(trigComp) {
	xLabelSizeUp = xLabelSize, yLabelSizeUp = 0.04, xLabelSizeDown = 0.1, yLabelSizeDown = 0.1;
	yTitleSizeUp = 0.06, xTitleSizeDown = 0.1, yTitleSizeDown = 0.1;
	yTitleOffsetUp = 1.3, xTitleOffsetDown = 1.3, yTitleOffsetDown = 0.6;
  }

  // ==== Decoration Info (Legent, Stat, etc) ====
  bool multiStatBox = false;
  int optStat =0;
  //PosCorner: RU: 0.97, 0.93
  //float legX1=0.805, legY1=0.73, legX2=0.97, legY2=0.93;//Without MultiStatBox, No Signals
  float legX1=0.78, legY1=0.60, legX2=0.95, legY2=0.91;//Without MultiStatBox
  //float legX1=0.8, legY1=0.37, legX2=0.97, legY2=0.57;//With MultiStatBox
  TString legName;
  bool trigCut = true; double x1 = 1000., y1 = 0., x2 = 500., y2 = 0.;

  // ==== canvas info ====
  int canvasWidth = 800, canvasHeight = 600;
  float topMargin = 0.07, bottomMargin = 0.12, rightMargin = 0.03, leftMargin = 0.12;
  float downPadRatio, topMarginUp, bottomMarginUp, rightMarginUp, leftMarginUp, topMarginDown, bottomMarginDown, rightMarginDown, leftMarginDown;
  if(trigComp) {
	canvasWidth = 450, canvasHeight = 500, downPadRatio = 0.25;
	topMarginUp = 0.08, bottomMarginUp = 0.02, leftMarginUp = 0.15, rightMarginUp = 0.05;
	topMarginDown = 0.05, bottomMarginDown = 0.45, leftMarginDown = 0.15, rightMarginDown = 0.05;
  }

  SetTDRStyle();

  // ==== Output Info ====
  TString outName = histName; TString outSuffix = "_2016"; TString outFormat = ".pdf";


  // ==== 2. Conditions to Edit(Histogram Properties) ====
  // ==== Data & MC comparison ===
  if (histName.Contains("Mt")) {
	xAxisName = "M_{T}(e, E_{T}^{miss}) (GeV)";
	yAxisName = "Event / 2 GeV";
  }
  if (histName.Contains("M(ee)")) {
	xAxisName = "M(ee) (GeV)";
	yAxisName = "Event / 2 GeV";
  }
  if (histName.Contains("nPV")) {
	xAxisName = "nPV";
	yAxisName = "Event";
  }
  if (histName.Contains("nEvent")) {
	xAxisName = "";
	yAxisName = "Event";
  }
    
  // ==== 3. Histogram Preparation ====
  TH1* histData = NULL;
  THStack* hstackBkg = new THStack(histName + "_bkg", title);
  THStack* hstackSig = new THStack(histName + "_sig", title);
  TH1* hErrBkg = NULL;
  TH1* hData2MC = NULL;
  TLegend* legend = new TLegend(legX1, legY1, legX2, legY2);
  
  if (trigData) {
    TFile* fdata = new TFile(whichPath + whichVer + whichData + fileName + dataName + ".root");
	if (trigDir) {
	   fdata->cd();
	   TDirectory* dir_data = gFile->GetDirectory(histDir);
        cout << "[DEBUG] histName = " << histName << endl;
	   histData = (TH1*)dir_data->Get(histName);
	}
	else histData = (TH1*) fdata->Get(histName);
	legend->AddEntry(histData, "Data", "lep");
	histData->Rebin(nRebinx); histData->Scale( scale);
  }

  if (trigSig) {
    for (int i = 0; i < nSig; i++) {
	  TFile* fsig = new TFile(whichPath + whichVer + fileName + sigList[i] + ".root");
	  TH1* histSig = NULL;
	  if(trigDir) {
	    fsig->cd();
		TDirectory* dir_sig = gFile->GetDirectory(histDir);
		histSig = (TH1*)dir_sig->Get(histName);
	  }
	  else histSig = (TH1*) fsig->Get(histName);
	  if(!histSig) {
	    cout << "histSig not exist in " << sigList[i] << " Sample" << endl;
		continue;
	  }

	  // ==== Signal Option ====
	  if (sigList[i].Contains("TTLL_powheg")) {
	    histSig->SetLineColor(kGreen + 4);
		scale = sigScale;
		legName = "";
	  }

	  histSig->Rebin(nRebinx); histSig->Scale(scale);
	  histSig->SetLineWidth(linewidth);
      histSig->SetLineStyle(1);//solid //(2);dotted
      hstackSig->Add(histSig);
      hErrBkg->Add(histSig);
      legend->AddEntry(histSig, legName, "l");
	}
  }

  if (trigBkg) {
	for (int i = 0; i < nBkg; i++) {
      TFile* fbkg = new TFile(whichPath + whichVer + fileName + bkgList[i] + ".root");
      TH1* histBkg = NULL;
      if(trigDir) {
        fbkg->cd();
        TDirectory* dir_bkg = gFile->GetDirectory(histDir);
        histBkg = (TH1*)dir_bkg->Get(histName);
      }
      else histBkg = (TH1*) fbkg->Get(histName);
      if(!histBkg) {
        cout << "histBkg not exist in " << sigList[i] << " Sample" << endl;
        continue;
      }
	  // histBkg->Scale(1.11444); // Tight
	  // histBkg->Scale(2.61259); // Loose
	  histBkg->Scale(1.12238);

	  //double scale = 15483. / 319717.;
	  //histBkg->Scale(scale);
	  
	  // ==== MC Color Option ====i
	  if (bkgList[i]=="tt") {
		histBkg->SetFillColorAlpha(kBlue, 1.);
		histBkg->SetLineColor(38);
		legName = "t#bar{t}";}
	  if (bkgList[i]=="DYJets") {
		histBkg->SetFillColorAlpha(kGreen, 0.7);
		histBkg->SetLineColor(kGreen);
		legName="DYJets";}
	  if (bkgList[i] == "SingleTop") {
		histBkg->SetFillColorAlpha(kBlue, 0.7);
		histBkg->SetLineColor(4);
		legName="SingleTop";}
	  if (bkgList[i] == "tW") {
		histBkg->SetFillColorAlpha(kBlue, 0.4);
		histBkg->SetLineColor(9);
		legName="tW";}
	  else if (bkgList[i]=="WJets_MG") {
		histBkg->SetFillColorAlpha(kAzure, 0.7);  
		histBkg->SetLineColor(kAzure);  
		legName="WJets";}
      else if (bkgList[i]=="VV") {
		histBkg->SetFillColorAlpha(kRed, 0.7);   
		histBkg->SetLineColor(kRed);   
		legName="VV";}
	  else cout << "This BkgProc(" << bkgList[i] << ") does not have matched color!" << endl;

	  legend->AddEntry(histBkg, legName, "f");
      hstackBkg->Add(histBkg);
      if (!hErrBkg) hErrBkg = (TH1*) histBkg->Clone(histName+"_ErrBkg");
      else hErrBkg->Add(histBkg);
	}
  }

  // ==== Data & MC comparision ====
  if (trigComp) {
	hData2MC = (TH1*) histData->Clone("hData2MC");
	hData2MC->Divide(hErrBkg);
  }

  // ==== 4. Draw with setting options ====
  TCanvas* c1 = new TCanvas(histName, "c1", canvasWidth, canvasHeight);
  if (trigComp) {
	TPad* c1_up = new TPad("c1_up", "", 0, downPadRatio, 1, 1);
	c1_up->SetTopMargin(topMarginUp); c1_up->SetBottomMargin(bottomMarginUp);
	c1_up->SetLeftMargin(leftMarginUp); c1_up->SetRightMargin(rightMarginUp);
	c1_up->Draw();

	TPad* c1_down = new TPad("c1_down", "", 0, 0, 1, downPadRatio);
	c1_down->SetTopMargin(topMarginDown); c1_down->SetBottomMargin(bottomMarginDown);
	c1_down->SetLeftMargin(leftMarginDown); c1_down->SetRightMargin(rightMarginDown);
	c1_down->Draw();

	c1_up->cd();
	hstackBkg->Draw();

	histData->SetTitle(title);
	histData->GetYaxis()->SetTitle(yAxisName);

	if (xRange) histData->GetXaxis()->SetRangeUser(xRangeMin, xRangeMax);
	if (yRange) histData->GetYaxis()->SetRangeUser(yRangeMin, yRangeMax);
	if (auto_xRange) {
      xRangeMin = hstackBkg->GetXaxis()->GetXmin();
      xRangeMax = hstackBkg->GetXaxis()->GetXmax();
    }
	if (auto_yRange) {
	  float YmaxBkgMean=hErrBkg->GetMaximum(),  YmaxBkgErr=hErrBkg->GetBinError(hErrBkg->GetMaximumBin()), YmaxSig=hstackSig->GetMaximum("nostack");
      float YmaxDataMean=histData->GetMaximum(), YmaxDataErr=histData->GetBinError(histData->GetMaximumBin());
      float YmaxBkg=YmaxBkgMean+YmaxBkgErr, YmaxData=YmaxDataMean+YmaxDataErr;
      yRangeMax= YmaxBkg > YmaxSig ? YmaxBkg : YmaxSig;
      yRangeMax= yRangeMax > YmaxData ? yRangeMax : YmaxData;
      yRangeMax *= auto_yAxisMarginUp; //1.2

	  if (logY) yRangeMax*= 10;
	  histData->SetMinimum(yRangeMin); histData->SetMaximum(yRangeMax);
	}

	if(logY) {
	  histData->SetMinimum(1); hstackBkg->SetMinimum(1); hErrBkg->SetMinimum(10); c1_up->SetLogy(1);
	}
	if (yRangeMax > 1000) yTitleOffsetUp *= 1.2;
	if (yRangeMax > 10000) {yTitleOffsetUp *= 1.3;  yLabelSizeUp *= 1.3;}
	histData->GetXaxis()->SetLabelSize(0);
    histData->GetYaxis()->SetLabelSize(yLabelSizeUp);
    histData->GetYaxis()->SetTitleSize(yTitleSize);
    histData->GetYaxis()->SetTitleOffset(yTitleOffsetUp);
    if (yRangeMax > 1.0E5) TGaxis::SetExponentOffset(-0.07, 0.01, "y");
    histData->SetMarkerStyle(markerStyle_data);
    histData->SetMarkerSize(markerSize_data);
        
    hErrBkg->SetMarkerColorAlpha(errBaseColor, errBaseOpacity);
    hErrBkg->SetFillStyle(errFillStyle);
    hErrBkg->SetFillColor(errColor);
        
    gStyle->SetHatchesSpacing(1.2); //0.4
    gStyle->SetHatchesLineWidth(1);
	gStyle->SetOptStat(optStat);

	histData->Draw();
    hstackBkg->Draw("histfsame");
    histData->Draw("sameaxis");
    hstackBkg->Draw("sameaxis");
    hErrBkg->Draw("e2sames");
    if (trigSig) hstackSig->Draw("nostackhistsame");
    histData->Draw("epsames");
    legend->Draw("same");

    TPaveStats* StatBox1; TPaveStats* StatBox2;

	TLatex* label_DatInfo = new TLatex();
    label_DatInfo->SetTextSize(0.04);
    label_DatInfo->SetTextFont(42);
    label_DatInfo->DrawLatexNDC(0.68, 0.94, "0.063 fb^{-1} / 10 (13TeV)");

	c1_down->cd();
    double x_g1[2], y_g1[2];
    x_g1[0] =  1000;  y_g1[0] = 1;
    x_g1[1] = -1000;  y_g1[1] = 1;
    TGraph *g1 = new TGraph(2, x_g1, y_g1);

    hData2MC->SetTitle("");
    hData2MC->GetXaxis()->SetRangeUser(xRangeMin, xRangeMax);
    hData2MC->GetYaxis()->SetRangeUser(compYrangeMin, compYrangeMax);
    hData2MC->GetXaxis()->SetTitle(xAxisName);
    hData2MC->GetYaxis()->SetTitle("Data/Pred");
    hData2MC->SetNdivisions(504, "Y");
    if(xLabelCustom){
      for(int i=0; i < nBinCustomLabel; i++) {
        hData2MC->GetXaxis()->SetBinLabel(i+1, xBinlabel.at(i));
      }
    }
    hData2MC->GetXaxis()->SetLabelSize(xLabelSizeDown);
    hData2MC->GetYaxis()->SetLabelSize(yLabelSizeDown);
    hData2MC->GetXaxis()->SetTitleSize(xTitleSizeDown);
    hData2MC->GetYaxis()->SetTitleSize(yTitleSizeDown);
    hData2MC->GetXaxis()->SetTitleOffset(xTitleOffsetDown);
    hData2MC->GetYaxis()->SetTitleOffset(yTitleOffsetDown);
    hData2MC->SetMarkerStyle(markerStyle_data); hData2MC->SetMarkerSize(markerSize_data);
    hData2MC->SetFillColorAlpha(45,0.35);
    gStyle->SetOptStat(0);
    hData2MC->Draw("");

    g1->Draw("same");
    hData2MC->Draw("pe1same");
  }
  c1->SaveAs(outName+outSuffix+outFormat);
  c1->Clear(); c1->Close();
}
}
