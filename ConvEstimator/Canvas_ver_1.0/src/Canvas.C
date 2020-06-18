#include "FileNavi.h"
#include "FileNavi.C"
#include "ConvEstimation.h"
#include "ConvEstimation.C"
#include "vector"

void Canvas() {
	//==== Basic information ====
    TString pathData = "$PWD/../../Output_ver_1.0/2016/RunFakeSyst__/DATA/";
    TString pathMC = "$PWD/../../Output_ver_1.0/2016/RunFakeSyst__/Samples/";

    vector<TString> Samples = {"DoubleEG", "MC", "conv", "VV", "rare", "ttVorH"};
    vector<TString> IDSets = {"POGID", "FakeID"};

	ConvEstimation conv;
	conv.Init(pathData, pathMC, Samples, IDSets);

    vector<TString> histnames
        = {"1st_electron_pt_", "1st_electron_eta_", "1st_electron_phi_",
        "2nd_electron_pt_", "2nd_electron_eta_", "2nd_electron_phi_",
        "3rd_electron_pt_", "3rd_electron_eta_", "3rd_electron_phi_",
        "M(3e)_", "M(e+e-)_", "MET_", "NJets_", "PassSelection_", "pairCnt_"};


	//==== User defined setting ====
	TString idset = "FakeID";
	bool trigScale = true;
	int sys = 0; // no effect on scale
	unsigned int histnum;
	TString xAxisName, yAxisName;
	int yAxisScale, compScale;

	cout << "[Canvas] User defined settings" << endl;
	cout << "[Canvas] histnames: " << endl;
	for (unsigned int i = 0; i < histnames.size(); i++) {
		cout << "[Canvas] histname " << i << ": " << histnames.at(i) << endl;
	}
	cout << "[Canvas] histnum = ";
	cin >> histnum;
	if (histnum >= histnames.size()) {
		cout << "[Canvas] histnum should be smaller than " << histnames.size() << endl;
		exit(EXIT_FAILURE);
	}
	cout << "[Canvas] histname = " << histnames.at(histnum) << endl;
	cout << "[Canvas] xAxisName: ";
	cin >> xAxisName;
	cout << "[Canvas] yAxisName: ";
	cin >> yAxisName;
	cout << "[Canvas] yAxisScale: ";
	cin >> yAxisScale;
	cout << "[Canvas] compScale: ";
	cin >> compScale;

	cout << "[Canvas] idset = " << idset << endl;
	cout << "[Canvas] trigScale = " << trigScale << endl;
	cout << "[Canvas] histname = " << histnames.at(histnum) << endl;
	cout << "[Canvas] sys = " << sys << endl;
	cout << "[Canvas] xAxisName = " << xAxisName << endl;
	cout << "[Canvas] yAxisName = " << yAxisName << endl;
	cout << "[Canvas] yAxisScale = " << yAxisScale << endl;
	cout << "[Canvas] compScale = " << compScale << endl;

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

	//==== Get Histograms to manipulate ====
	TH1D* hData = NULL;
	THStack* hs = new THStack("hs", "");
	TH1D* hSyst = NULL;
	TH1D* hComp = NULL;

	TString histname = histnames.at(histnum);
	vector<TH1D*> hSamples = conv.GetSampleHists(idset, histname);
	vector<TH1D*> hFakes = conv.GetFakeHists(idset, histname);
	
	//==== hData setting ====
	hData = (TH1D*)hSamples.at(0)->Clone("hData");
	hData->SetMarkerStyle(8);
    hData->SetMarkerSize(0.5);
    hData->SetMarkerColor(kBlack);
    hData->SetStats(0);
    hData->GetXaxis()->SetLabelSize(0);
    hData->GetYaxis()->SetTitle(yAxisName);
    hData->GetYaxis()->SetRangeUser(0, yAxisScale);

    l->AddEntry(hData, "Data", "lep");

	//==== hs setting ====
	for (unsigned int j = 2; j < Samples.size(); j++) {
		TH1D* this_hist = NULL;
		if (j==2 && trigScale) {
			this_hist = (TH1D*)hSamples.at(j)->Clone("conv");
			double scale = conv.GetScale(idset, 0);
			cout << "[Canvas] scale = " << scale << endl;
			this_hist->Scale(scale);
			hSyst = (TH1D*)this_hist->Clone("hSyst");
		}
		else if (j==2 && !trigScale) {
			this_hist = (TH1D*)hSamples.at(j)->Clone("conv");
			hSyst = (TH1D*)this_hist->Clone("hSyst");
		}
		else {
			this_hist = (TH1D*)hSamples.at(j)->Clone(Samples.at(j));
			hSyst->Add(this_hist);
		}

		//==== setting ====
		if (Samples.at(j).Contains("conv")) {
			this_hist->SetFillColorAlpha(kBlue, 0.5);
			l->AddEntry(this_hist, "conv", "f");
		}
		if (Samples.at(j).Contains("VV")) {
			this_hist->SetFillColorAlpha(kAzure, 0.5);
			l->AddEntry(this_hist, "VV", "f");
		}
		if (Samples.at(j).Contains("rare")) {
			this_hist->SetFillColorAlpha(kViolet, 0.5);
			l->AddEntry(this_hist, "rare", "f");
		}
		if (Samples.at(j).Contains("ttVorH")) {
			this_hist->SetFillColorAlpha(kGreen, 0.5);
			l->AddEntry(this_hist, "ttV/H", "f");
		}
		hs->Add(this_hist);
	}
	TH1D* hFake = NULL;
	if (sys == 0) hFake = (TH1D*)hFakes.at(0)->Clone("hFake");
	else if (sys == +1) hFake = (TH1D*)hFakes.at(1)->Clone("hFakeUp");
	else if (sys == -1) hFake = (TH1D*)hFakes.at(2)->Clone("hFakeDown");
	else {
		cout << "[Canvas] sys = " << sys << endl;
		cout << "[Canvas] sys should be 0,-1, 1" << endl;
		exit(EXIT_FAILURE);
	}
	hSyst->Add(hFake);
	hFake->SetFillColorAlpha(kRed, 0.5);
	l->AddEntry(hFake, "f");

	hs->Add(hFake);

	//==== hSyst setting ====
	hSyst->SetFillColorAlpha(kBlack, 0.9);
	hSyst->SetFillStyle(3144);

	//==== hComp setting ====
	hComp = (TH1D*)hData->Clone("hComp");
	hComp->Divide(hSyst);

	hComp->GetYaxis()->SetRangeUser(0, compScale);
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


	//==== Draw on canvas ====
	pUp->cd();
	hData->Draw("p&hist");
	hs->Draw("hist&same");
	hData->Draw("e1&same");
	hSyst->Draw("e2&f&same");
	l->Draw("same");

	pDown->cd();
	hComp->Draw();

	c->cd();
	pUp->Draw();
	pDown->Draw();
	c->Draw();
}
