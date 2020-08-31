#include "FileNavi.h"
#include "FileNavi.cpp"

void muons_loose() {
	vector<TString> years{"2016", "2017", "2018"};
	TString userflag = "RunPOGTight__";
	TString region = "preselection";
	TString idflag = "TT";
	TString obj = "2";
	TString dist = "eta";
	double scale = 3.6;

	// constants
	// used for normalization
	const double lumi_2016 = 35.9;
	const double lumi_2017 = 41.5;
	const double lumi_2018 = 59.7;

	// file navigation
	map<TString, FileNavi> navis;
	vector<TString> samples{"DoubleMuon"};
	TString path_data;
	TString path_mc;
	for (const auto& year: years) {
		path_data = "$PWD/../input/" + year + "/" + userflag + "/DATA/";
		path_mc = "$PWD/../input/" + year + "/" + userflag + "/MCSamples/";
		FileNavi navi(path_data, path_mc, samples);
		navis[year] = navi;
	}

	// Canvas and legend
	TCanvas* c = new TCanvas("canvas", "", 720, 800);
	TLegend* l = new TLegend(0.75, 0.75, 0.90, 0.90);
	TLatex* lumi = new TLatex();
	lumi->SetTextSize(0.03);
	lumi->SetTextFont(42);

	// information
	TString lumi_info = "Normalized to L_{int} = 35.9 fb^{-1} (13TeV)";
	TString x_axis;
	TString y_axis;
	if (dist.Contains("pt")) {
		x_axis = "p_{T}";
		y_axis = "Events";
	}
	else if (dist.Contains("eta")) {
		x_axis = "#eta";
		y_axis = "Events";
	}
	else if (dist.Contains("phi")) {
		x_axis = "#phi";
		y_axis = "Events";
	}
	else {
		cerr << "wront dist = " << dist << endl;
		exit(EXIT_FAILURE);
	}
	
	// get histograms
	TH1D* h_2016 = nullptr;
	TH1D* h_2017 = nullptr;
	TH1D* h_2018 = nullptr;
	
	TString path = region + "/" + idflag + "/muons_loose/" + obj + "/" + dist;
	h_2016 = (TH1D*)navis["2016"].getHist("DoubleMuon", path);
	h_2017 = (TH1D*)navis["2017"].getHist("DoubleMuon", path);
	h_2018 = (TH1D*)navis["2018"].getHist("DoubleMuon", path);

	// scale 2017, 2018
	h_2017->Scale(lumi_2016 / lumi_2017);
	h_2018->Scale(lumi_2016 / lumi_2018);

	// rebin
	//h_2016->Rebin(5);
	//h_2017->Rebin(5);
	//h_2018->Rebin(5);

	// deco
	double y_range = h_2016->GetMaximum() * scale;
	h_2016->SetStats(0);
	h_2016->GetYaxis()->SetRangeUser(0, y_range);
	h_2016->GetYaxis()->SetTitle(y_axis);
	h_2016->GetYaxis()->SetTitleSize(0.03);
	h_2016->GetYaxis()->SetTitleOffset(1.45);
	h_2016->GetYaxis()->SetLabelSize(0.02);
	if (dist.Contains("pt")) h_2016->GetXaxis()->SetRangeUser(0, 80);
	h_2016->GetXaxis()->SetTitle(x_axis);
	h_2016->GetXaxis()->SetTitleSize(0.03);
	h_2016->GetXaxis()->SetTitleOffset(1.15);
	
	h_2016->SetLineColor(kRed);
	h_2017->SetLineColor(kGreen);
	h_2018->SetLineColor(kViolet);
	h_2016->SetLineWidth(2);
	h_2017->SetLineWidth(2);
	h_2018->SetLineWidth(2);

	l->AddEntry(h_2016, "2016", "l");
	l->AddEntry(h_2017, "2017", "l");
	l->AddEntry(h_2018, "2018", "l");

	c->cd();
	h_2016->Draw("hist");
	h_2017->Draw("hist&same");
	h_2018->Draw("hist&same");
	l->Draw("same");
	lumi->DrawLatexNDC(0.45, 0.91, lumi_info);
	c->SaveAs(idflag + "_" + obj + "_" + dist + ".png");
}
