#include "Canvas.h"
using namespace std;

// constructor
Canvas::Canvas() {}
Canvas::Canvas(const TString& pathData, const TString& pathMC, const vector<TString>& Samples) {
	navi.SetPathData(pathData);
	navi.SetPathMC(pathMC);
	navi.SetSamples(Samples);
}

// destructor
Canvas::~Canvas() {}

// get and set
void Canvas::Clear() {
	cvs = nullptr;
	leg = nullptr;
	pad_up = nullptr;
	pad_down = nullptr;
}

void Canvas::SetCanvas(const CanvasType& ctype) {
	switch (ctype) {
	case cRATIO:
		cvs = new TCanvas("cvs", "", 720, 800);
		cvs->SetGrid();
		break;
	case cFULL:
		// need settings
		cvs = new TCanvas("cvs", "", 720, 800);
		break;
	default:
		cout << "[Canvas::SetCanvas] CanvasType?" << endl;
	}
}

void Canvas::SetPad(const PadType& ptype) {
	switch (ptype) {
	case pRATIO:
		pad_up = new TPad("pad_up", "", 0, 0.25, 1, 1);
		pad_down = new TPad("pad_down", "", 0, 0, 1, 0.25);
		break;
	default:
		cout << "[Canvas::SetPad] PadType?" << endl;
	}
}

void Canvas::SetLegend(const LegendType& ltype) {
	switch (ltype) {
	case NORMAL:
		leg = new TLegend(0.70, 0.65, 0.90, 0.90);
		break;
	case RIGHTUP:
		cout << "[Canvas::SetLegend] need settings for RIGHTUP" << endl;
		break;
	case LEFTUP:
		cout << "[Canvas::SetLegend] need settings for LEFTUP" << endl;
		break;
	default:
		cout << "[Canvas::SetLegend] LegendType?" << endl;
	}
}

TCanvas* Canvas::GetCanvas() const { return cvs; }

void Canvas::DrawCutflow(const TString& sample, const TString& region) {
	TString path_pre = "preselection/cutflow";
	TString path_reg = region + "/cutflow";
	TH1D* cutflow_pre = (TH1D*)navi.GetHist(sample, path_pre);
	TH1D* cutflow_reg = (TH1D*)navi.GetHist(sample, path_reg);
	Clear();

	// merge cutflow
	TH1D* cutflow = new TH1D("cutflow_" + region, "", 9, 0., 9.);
	for (int i = 0; i < 5; i++) {
		cutflow->SetBinContent(i, cutflow_pre->GetBinContent(i));
	}
	for (int i = 5; i < 9; i++) {
		cutflow->SetBinContent(i, cutflow_reg->GetBinContent(i+1));
	}
	
	// decorate
	cutflow->SetStats(0);
	cutflow->SetLineColor(kAzure);
	cutflow->SetLineWidth(2);
	cutflow->SetTitle("cutflow_" + region);
	cutflow->GetYaxis()->SetTitle("Events");
	cutflow->GetXaxis()->SetBinLabel(1, "FULL");
	cutflow->GetXaxis()->SetBinLabel(2, "METFilter");
	cutflow->GetXaxis()->SetBinLabel(3, "nLep #ge 2");
	if (sample.Contains("TTLL")) cutflow->GetXaxis()->SetBinLabel(4, "Nj #ge 2, Nb #ge 1");
	if (sample.Contains("TTLJ")) cutflow->GetXaxis()->SetBinLabel(4, "Nj #ge 3, Nb #ge 1");
	if (region.Contains("dimu")) {
		cutflow->GetXaxis()->SetBinLabel(5, "Nmu = 2");
		cutflow->GetXaxis()->SetBinLabel(6, "OS");
		cutflow->GetXaxis()->SetBinLabel(7, "No addtional veto lep");
	}
	if (region.Contains("dielec")) {
		cutflow->GetXaxis()->SetBinLabel(5, "Ne = 2");
		cutflow->GetXaxis()->SetBinLabel(6, "OS");
		cutflow->GetXaxis()->SetBinLabel(7, "No additional veto lep");
	}
	if (region.Contains("emu")) {
		cutflow->GetXaxis()->SetBinLabel(5, "Nmu = 1, Ne = 1");
		cutflow->GetXaxis()->SetBinLabel(6, "OS");
		cutflow->GetXaxis()->SetBinLabel(7, "No additional veto lep");
	}
	if (region.Contains("mujj")) {
		cutflow->GetXaxis()->SetBinLabel(5, "Nmu = 1");
		cutflow->GetXaxis()->SetBinLabel(6, "No additional veto lep");
	}
	if (region.Contains("ejj")) {
		cutflow->GetXaxis()->SetBinLabel(5, "Ne = 1");
		cutflow->GetXaxis()->SetBinLabel(6, "No Additional veto lep");
	}

	// canvas
	SetCanvas(cFULL);
	//cvs->SetLogy();
	cvs->cd();
	cutflow->Draw();
	cvs->Draw();
}

void Canvas::DrawNormalizedDistribution(const vector<TH1D*> hists) {
	Clear();
	SetCanvas(cFULL);
	SetLegend(NORMAL);
	TString histname;
	double scale;
	cvs->cd();

	for (unsigned int i = 0; i < hists.size(); i++) {
		histname = hists.at(i)->GetName();
		TH1D* this_hist = (TH1D*)hists.at(i)->Clone("temp hist");
		scale = this_hist->Integral(); this_hist->Scale(1./scale);
		if (histname.Contains("EWPrompt")) {
			this_hist->SetLineColor(kAzure);
			leg->AddEntry(this_hist, "EWPrompt", "l");
		}
		else if (histname.Contains("EWTauDaughter")) {
			this_hist->SetLineColor(kGreen);
			leg->AddEntry(this_hist, "EWTauDaughter", "l");
		}
		else if (histname.Contains("fake")) {
			this_hist->SetLineColor(kRed);
			leg->AddEntry(this_hist, "fake", "l");
		}
		else if (histname.Contains("others")) {
			this_hist->SetLineColor(kGray);
			leg->AddEntry(this_hist, "others", "l");
		}
		else {
			this_hist->SetLineColor(kBlack);
            leg->AddEntry(this_hist, "ALL", "l");
		}

		// general options
		this_hist->SetStats(0);
        if (histname.Contains("electrons")) this_hist->GetYaxis()->SetRangeUser(0, 0.06);
		if (histname.Contains("muons") && histname.Contains("pt")) this_hist->GetYaxis()->SetRangeUser(0., 0.15);
		if (histname.Contains("muons") && !histname.Contains("pt")) this_hist->GetYaxis()->SetRangeUser(0, 0.06);
        this_hist->SetLineWidth(2);
		this_hist->GetYaxis()->SetTitle("A.U.");
		this_hist->GetYaxis()->SetTitleOffset(1.23);
		this_hist->GetYaxis()->SetLabelSize(0.028);
		if (histname.Contains("pt")) this_hist->GetXaxis()->SetTitle("p_{T}");
		if (histname.Contains("eta")) this_hist->GetXaxis()->SetTitle("#eta");
		if (histname.Contains("phi")) this_hist->GetXaxis()->SetTitle("#phi");
		if (histname.Contains("METv/pt")) this_hist->GetXaxis()->SetTitle("E_{T}^{miss}");
		if (histname.Contains("METv/phi")) this_hist->GetXaxis()->SetTitle("#phi(E_{T}^{miss})");
		// draw
		if (i == 0) this_hist->Draw("hist");
		else this_hist->Draw("hist same");
	}
	leg->Draw("same");
	cvs->Draw();
}

void Canvas::DrawStack(const vector<TH1D*> hists) {
	// initial settings
	Clear();
	SetCanvas(cFULL);
    SetLegend(NORMAL);
    TString histname;
	TH1D* hAll = (TH1D*)hists.at(0)->Clone("ALL");
	TH1D* hSyst = (TH1D*)hists.at(0)->Clone("Syst");
	THStack* hs = new THStack("hs", "");
	cvs->cd();

	// settings
	histname = hists.at(0)->GetName();
	hAll->SetMarkerStyle(8);
	if (histname.Contains("pt")) hAll->SetMarkerSize(0.4);
	else hAll->SetMarkerSize(0.7);
	hAll->SetMarkerColor(kBlack);
	hAll->SetStats(0);
    hAll->GetYaxis()->SetTitle("Events");
    hAll->GetYaxis()->SetTitleOffset(1.27);
    hAll->GetYaxis()->SetLabelSize(0.024);
	double yRange = hAll->GetMaximum();
    hAll->GetYaxis()->SetRangeUser(0, yRange*1.4);
    if (histname.Contains("pt")) hAll->GetXaxis()->SetTitle("p_{T}");
    if (histname.Contains("eta")) hAll->GetXaxis()->SetTitle("#eta");
    if (histname.Contains("phi")) hAll->GetXaxis()->SetTitle("#phi");
    if (histname.Contains("METv/pt")) hAll->GetXaxis()->SetTitle("E_{T}^{miss}");
    if (histname.Contains("METv/phi")) hAll->GetXaxis()->SetTitle("#phi(E_{T}^{miss})");

	leg->AddEntry(hAll, "All", "lep");
	hSyst->SetFillColorAlpha(kBlack, 0.4);
	hSyst->SetFillStyle(3144);
	leg->AddEntry(hSyst, "Stat err.", "f");
	for (unsigned int i = 1; i < hists.size(); i++) {
		histname = hists.at(i)->GetName();
        TH1D* this_hist = (TH1D*)hists.at(i)->Clone("temp hist");
        if (histname.Contains("EWPrompt")) {
            this_hist->SetFillColorAlpha(kAzure, 0.6);
            leg->AddEntry(this_hist, "EWPrompt", "f");
        }
        else if (histname.Contains("EWTauDaughter")) {
            this_hist->SetFillColorAlpha(kGreen, 0.6);
            leg->AddEntry(this_hist, "EWTauDaughter", "f");
        }
        else if (histname.Contains("fake")) {
            this_hist->SetFillColorAlpha(kRed, 0.6);
            leg->AddEntry(this_hist, "fake", "f");
        }
        else if (histname.Contains("others")) {
            this_hist->SetFillColorAlpha(kGray, 0.6);
            leg->AddEntry(this_hist, "others", "f");
        }
		hs->Add(this_hist);
	}
	
	hAll->Draw("p&hist");
	hs->Draw("hist&same");
	hSyst->Draw("e2&f&same");
	hAll->Draw("p&hist&same");
	leg->Draw("same");

	cvs->Draw();
}
