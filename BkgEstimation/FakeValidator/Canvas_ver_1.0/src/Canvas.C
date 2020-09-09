#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void Canvas() {
	//==== Basic information ====
	TString pathData = "$PWD/../../Output_ver_1.0/2016/RunFakeSyst__RunPrompt__/DATA/";
	TString pathMC = "$PWD/../../Output_ver_1.0/2016/RunFakeSyst__RunPrompt__/Samples/";

	vector<TString> Samples = {"DoubleEG", "MC", "ttVorH", "VV", "rare", "conv"};
	vector<TString> IDSets = {"POGID", "FakeID"};

	FakeValidation fake;
	fake.Init(pathData, pathMC, Samples, IDSets);

	vector<TString> histnames
		= {"1st_electron_pt_", "1st_electron_eta_", "1st_electron_phi_",
			"2nd_electron_pt_", "2nd_electron_eta_", "2nd_electron_phi_",
			"3rd_electron_pt_", "3rd_electron_eta_", "3rd_electron_phi_",
			"MET_", "Njets_", "M(ee)_"};

	//==== User defined setting ====
	TString idset = "POGID";
	bool trigScale = true;
	unsigned int histnum;
	TString xAxisName, yAxisName;
	int yAxisScaleUp, yAxisScaleDown;

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
    cout << "[Canvas] yAxisScaleUp: ";
    cin >> yAxisScaleUp;
    cout << "[Canvas] yAxisScaleDown: ";
    cin >> yAxisScaleDown;

	cout << "[Canvas] idset = " << idset << endl;
    cout << "[Canvas] trigScale = " << trigScale << endl;
    cout << "[Canvas] histname = " << histnames.at(histnum) << endl;
    cout << "[Canvas] xAxisName = " << xAxisName << endl;
    cout << "[Canvas] yAxisName = " << yAxisName << endl;
    cout << "[Canvas] yAxisScaleUp = " << yAxisScaleUp << endl;
    cout << "[Canvas] yAxisScaleDown = " << yAxisScaleDown << endl;

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
    THStack* hs = new THStack("hs", "");
    TH1D* hSyst = NULL;
    TH1D* hComp = NULL;
	TH1D* hCompSyst = NULL;

    TString histname = histnames.at(histnum);
    vector<TH1D*> hSamples = fake.GetSampleHists(idset, histname);
    vector<TH1D*> hFakes = fake.GetFakeHists(idset, histname);

	//==== hData setting ====
	hData = (TH1D*)hSamples.at(0)->Clone("hData");
    hData->SetMarkerStyle(8);
    hData->SetMarkerSize(0.5);
    hData->SetMarkerColor(kBlack);
    hData->SetStats(0);
    hData->GetXaxis()->SetLabelSize(0);
    hData->GetYaxis()->SetTitle(yAxisName);
    hData->GetYaxis()->SetRangeUser(0, yAxisScaleUp);

    l->AddEntry(hData, "Data", "lep");

	//==== hs setting ====
	for (unsigned int j = 2; j < Samples.size(); j++) {
        TH1D* this_hist = NULL;
        if (j==2 && trigScale) {
            this_hist = (TH1D*)hSamples.at(j)->Clone("conv");
            double scale = fake.GetScale(idset);
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

	//==== fake systematics setting ====
	TH1D* hFake = (TH1D*) hFakes.at(0)->Clone("hFake");
	TH1D* hFakeUp = (TH1D*) hFakes.at(1)->Clone("hFakeUp");
	TH1D* hFakeDown = (TH1D*) hFakes.at(2)->Clone("hFakeDown");

	int nbin = 0;
	if (histnum == 0) nbin = hFake->FindBin(199);
	else if (histnum == 1) nbin = hFake->FindBin(2.9);
	else if (histnum == 2) nbin = hFake->FindBin(3.1);
	else if (histnum == 3) nbin = hFake->FindBin(159);
	else if (histnum == 4) nbin = hFake->FindBin(2.9);
	else if (histnum == 5) nbin = hFake->FindBin(3.1);
	else if (histnum == 6) nbin = hFake->FindBin(150);
	else if (histnum == 7) nbin = hFake->FindBin(2.9);
	else if (histnum == 8) nbin = hFake->FindBin(3.1);
	else if (histnum == 9) nbin = hFake->FindBin(159);
	else if (histnum == 10) nbin = hFake->FindBin(6);
	else {
		cout << "[Canvas] No histogram for histname = " << histname << endl;
		exit(EXIT_FAILURE);
	}
	// set error bin by bin
	for (int i = 0; i < nbin; i++) {
		double this_errUp = hFakeUp->GetBinContent(i+1) - hFake->GetBinContent(i+1);
        this_errUp /= hFake->GetBinContent(i+1);
        double this_errDown = hFakeDown->GetBinContent(i+1) - hFake->GetBinContent(i+1);
        this_errDown /= hFake->GetBinContent(i+1);
        double this_stat = hFake->GetBinError(i+1);
        this_stat /= hFake->GetBinContent(i+1);
        double this_totalerr = this_stat*this_stat + this_errUp*this_errUp + this_errDown*this_errDown;
        this_totalerr = TMath::Sqrt(this_totalerr);
        this_totalerr *= hFake->GetBinContent(i+1);
        if (i == 0 || i == nbin-1) this_totalerr = 0;
        if (!isnan(this_totalerr)) hFake->SetBinError(i+1, this_totalerr);
        cout << "[Canvas] bin error " << i+1 << " : " << this_totalerr << endl;
	}
	hSyst->Add(hFake);
	hFake->SetFillColorAlpha(kRed, 0.5);
	l->AddEntry(hFake, "fake", "f");
	hs->Add(hFake);

	//==== hSyst setting ====
	hSyst->SetFillColorAlpha(kBlack, 0.4);
    hSyst->SetFillStyle(3144);
	l->AddEntry(hSyst, "stat+syst(fake)", "f");

	//==== hComp setting ====
	hComp = (TH1D*)hData->Clone("hComp");
    hComp->Divide(hSyst);
	hCompSyst = (TH1D*) hComp->Clone("hCompSyst");

    hComp->GetYaxis()->SetRangeUser(0, yAxisScaleDown);
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
    hs->Draw("hist&same");
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
	c->SaveAs(histname + idset + "_scaleOFF.pdf");

}
