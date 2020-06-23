#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void Canvas() {
    //==== Basic Information ====
    TString pathData = "$PWD/../../Outputs_ver_1.0/2016/RunSysts__/DATA/";
    TString pathMC = "$PWD/../../Outputs_ver_1.0/2016/RunSysts__/Samples/";

    vector<TString> Samples = {"DoubleEG", "MC", "DYJets", "tt", "VV",  "WJets_MG", "SingleTop", "tW"};
    vector<TString> IDs = {"passLooseID", "passTightID", "FakeLooseID", "FakeTightID"};
    vector<TString> Systs = {"Central", "JetPtCut30", "JetPtCut50", "JetPtCut60", "HadFlavor"};
    vector<TString> Prompts = {"Central", "JetResUp", "JetResDown", "JetEnUp", "JetEnDown",
                            "ElectronResUp", "ElectronResDown", "ElectronEnUp", "ElectronEnDown", "PileUp"};
    vector<TString> Regions = {"QCDEnriched", "WEnriched", "ZEnriched"};

    vector<TString> IDSets = {"POG", "Fake"};

	vector<TString> histnames
		= {"ElectronEta_", "LeadingJetEta_", "LeadingJetPt_", "corrPt_", // QCD enriched, 0~3
			"ElectronEta_", "ElectronPt_", "LeadingJetEta_",
			"LeadingJetPt_", "MET_", "MetPhi_", "Mt_", "corrPt_", // W enriched, 4~11
			"LeadingElectronEta_", "LeadingElectronPt_", "LeadingJetEta_",
			"LeadingJetPt_", "M(ee)_", "SubLeadingElectronEta_", "SubLeadingElectronPt_"}; // Z enriched 12~18

    FakeValidation fake;
    fake.Init(pathData, pathMC, Samples, IDs, Systs, Prompts, Regions, IDSets);

	//==== User defined settings ====
	TString id = "passTightID";
	TString syst = "Central";
	TString prompt = "Central";
	bool trigScale = true;
	double scale = 0;
	if (trigScale) scale = fake.GetPromptScale(id, syst, prompt);
	unsigned int histnum;
	TString xAxisName, yAxisName;
	int yAxisScaleUp, yAxisScaleDown;

	cout << "[Canvas] User defined settings" << endl;
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


	cout << "[Canvas] user defined settings" << endl;
	cout << "[Canvas] id = " << id << endl;
	cout << "[Canvas] syst = " << syst << endl;
	cout << "[Canvas] prompt = " << prompt << endl;
    cout << "[Canvas] trigScale = " << trigScale << endl;
	if (trigScale) {
		cout << "[Canvas] Scale = " << scale << endl;
	}
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
	if (0 <= histnum && histnum < 4) histname += Regions.at(0);
	else if (4 <= histnum && histnum < 12) histname += Regions.at(1);
	else if (12 <= histnum && histnum < 19) histname += Regions.at(2);
	else {
		cout << "[Canvas] histnum = " << histnum << endl;
		cout << "[Canvas] Wrong histnum" << endl;
		exit(EXIT_FAILURE);
	}
	histname += "_" + id + "_" + syst + "_" + prompt;
	vector<TH1D*> hSamples;
	for (unsigned int i = 0; i < Samples.size(); i++) {
		TH1D* this_hist = (TH1D*)fake.GetHist(Samples.at(i), histname);
		hSamples.push_back(this_hist);
	}
	//hSamples.at(0)->Draw();

	//==== hData settings ====
	hData = (TH1D*)hSamples.at(0)->Clone("hData");
    hData->SetMarkerStyle(8);
    hData->SetMarkerSize(0.5);
    hData->SetMarkerColor(kBlack);
    hData->SetStats(0);
    hData->GetXaxis()->SetLabelSize(0);
    hData->GetYaxis()->SetTitle(yAxisName);
    hData->GetYaxis()->SetRangeUser(0, yAxisScaleUp);

    l->AddEntry(hData, "Data", "lep");

	//==== hs settings ====
	for (unsigned int i = 2; i < Samples.size(); i++) {
		TH1D* this_hist = (TH1D*)hSamples.at(i)->Clone("this_hist");
		if (!this_hist) {
			cout << "[Canvas] histname = " << histname << endl;
			cout << "[Canvas] histogram does not exist" << endl;
			exit(EXIT_FAILURE);
		}
		//this_hist->Draw();
		if (trigScale) {
			this_hist->Scale(scale);
		}

		if (i == 2) hSyst = (TH1D*) this_hist->Clone("hSyst");
		else hSyst->Add(this_hist);

		if (Samples.at(i).Contains("DYJets")) {
			this_hist->SetFillColorAlpha(kGreen, 0.5);
			l->AddEntry(this_hist, "DY", "f");
		}
		if (Samples.at(i).Contains("VV")) {
			this_hist->SetFillColorAlpha(kViolet, 0.5);
			l->AddEntry(this_hist, "VV", "f");
		}
		if (Samples.at(i).Contains("tt")) {
			this_hist->SetFillColorAlpha(kBlue, 0.5);
			l->AddEntry(this_hist, "tt", "f");
		}
		if (Samples.at(i).Contains("tW")) {
			this_hist->SetFillColorAlpha(kAzure, 0.5);
			l->AddEntry(this_hist, "tW", "f");
		}
		if (Samples.at(i).Contains("SingleTop")) {
			this_hist->SetFillColorAlpha(kAzure, 0.7);
			l->AddEntry(this_hist, "SingleTop", "f");
		}
		if (Samples.at(i).Contains("WJets")) {
			this_hist->SetFillColorAlpha(kRed, 0.5);
			l->AddEntry(this_hist, "WJets", "f");
		}
		if (!this_hist) cout << "sibal" << endl;
		hs->Add(this_hist);
	}

	//==== hSyst settings ====
	hSyst->SetFillColorAlpha(kBlack, 0.4);
	hSyst->SetFillStyle(3144);
	l->AddEntry(hSyst, "stat error", "f");
	
	//==== hComp settings ====
	hComp = (TH1D*) hData->Clone("hComp");
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

    //==== hCompSyst settings ====
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
}	

	

