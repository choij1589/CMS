#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void Canvas4() {
	//==== This canvas is to draw object plots ====
	//==== comparing data and mc ====
	vector<TString> Hists_QCD, Hists_W, Hists_Z;
	Hists_QCD = {"ElectronEta_", "LeadingJetEta_",
				"LeadingJetPt_", "corrPt_"};
	Hists_W = {"ElectronEta_", "ElectronPt_",
			"LeadingJetEta_", "LeadingJetPt_",
			"MET_", "MetPhi_",
			"Mt_", "corrPt_"};
	Hists_Z = {"LeadingElectronEta_", "LeadingElectronPt_",
			"LeadingJetEta_", "LeadingJetPt_",
			"M(ee)_", "SubLeadingElectronEta_",
			"SubLeadingElectronPt_"};

	//==== inforamtion for FileNavi ====
	TString pathData = "$PWD/../../Outputs/2016/RunSysts__OringTrigger/DATA/";
    TString pathMC = "$PWD/../../Outputs/2016/RunSysts__OringTrigger/Samples/";

    vector<TString> Samples 
		= {"DoubleEG", "MC", "DYJets", "tt", "WJets_MG", "SingleTop", "tW"};
    vector<TString> IDs 
		= {"passLooseID", "passTightID", "FakeLooseID", "FakeTightID"};
    vector<TString> Systs 
		= {"Central", "JetPtCut30", "JetPtCut50", "JetPtCut60", "HadFlavor"};
    vector<TString> Prompts 
		= {"Central", "JetResUp", "JetResDown", "JetEnUp", "JetEnDown",
			"ElectronResUp", "ElectronResDown", "ElectronEnUp", "ElectronEnDown",
			"PileUp"};
    vector<TString> Regions 
		= {"QCDEnriched", "WEnriched", "ZEnriched"};
    vector<TString> IDSets = {"POG", "Fake"};

	FakeValidation fake;
	fake.Init(pathData, pathMC, Samples, IDs, Systs, Prompts, Regions, IDSets);
	
	//==== Get histograms ====
	TString id = IDs.at(3);
	TString region = Regions.at(1);
	TString syst = Systs.at(0);
	TString prompt = Prompts.at(0);

	TString histname = Hists_W.at(7);
	histname += region + "_" + id + "_" + syst + "_" + prompt;

	//== Preparation ==
	TH1D* hData = NULL; TH1D* hSyst = NULL; 
	TH1D* hComp = NULL; TH1D* hCompSyst = NULL;
	THStack* hStack = new THStack("hs", "");
	TLegend* l = new TLegend(0.69, 0.65, 0.93, 0.88);
	TCanvas* c = new TCanvas("canvas", "", 720, 800);
	TPad* pUp = new TPad("pUp", "", 0, 0.25, 1, 1);
	TPad* pDown = new TPad("pDown", "", 0, 0, 1, 0.25);

	//== TPad setup ==
	pUp->SetTopMargin(0.08);
	pUp->SetBottomMargin(0.02);
	pUp->SetLeftMargin(0.15);
	pUp->SetRightMargin(0.05);

	pDown->SetTopMargin(0.05);
	pDown->SetBottomMargin(0.45);
	pDown->SetLeftMargin(0.15);
	pDown->SetRightMargin(0.05);

	//== histogram setup ==
	vector<TH1D*> hSamples;
	for (unsigned int i = 0; i < Samples.size(); i++) {
		TH1D* this_hist = (TH1D*)fake.GetHist(Samples.at(i), histname);
		double this_scale
			= fake.GetPromptScale(id, syst, prompt);
		if (i != 0) this_hist->Scale(this_scale);
		hSamples.push_back(this_hist);
	}
	
	//== data ==
	hData = (TH1D*)hSamples.at(0)->Clone("hData");
	hData->SetMarkerStyle(8);
	hData->SetMarkerSize(0.5);
	hData->SetMarkerColor(kBlack);
	hData->SetStats(0);
	hData->GetXaxis()->SetLabelSize(0);
	hData->GetYaxis()->SetTitle("Event / 5GeV");
	hData->GetYaxis()->SetRangeUser(0, 3000);
	l->AddEntry(hData, "Data", "lep");

	//== Stack ==
	for (unsigned int i = 2; i < Samples.size(); i++) {
		TH1D* this_hist 
			= (TH1D*)hSamples.at(i)->Clone(Samples.at(i) + "_for_stack");
		if (Samples.at(i).Contains("DY")) {
			this_hist->SetFillColorAlpha(kGreen, 0.7);
			l->AddEntry(this_hist, "DY", "f");
		}
		else if (Samples.at(i).Contains("tt")) {
			this_hist->SetFillColorAlpha(kBlue, 0.7);
			l->AddEntry(this_hist, "TT", "f");
		}
		else if (Samples.at(i).Contains("tW")) {
			this_hist->SetFillColorAlpha(kAzure, 0.7);
			l->AddEntry(this_hist, "tW", "f");
		}
		else if (Samples.at(i).Contains("SingleTop")) {
			this_hist->SetFillColorAlpha(kViolet, 0.7);
			l->AddEntry(this_hist, "SingleTop", "f");
		}
		else if (Samples.at(i).Contains("WJets")) {
			this_hist->SetFillColorAlpha(kRed, 0.7);
			l->AddEntry(this_hist, "WJets", "f");
		}
		else {
			cout << "no histogram for " << Samples.at(i) << endl;
			exit(EXIT_FAILURE);
		}

		hStack->Add(this_hist);
	}

	//== systematic for MC ==
	hSyst = (TH1D*)hSamples.at(1)->Clone("hSyst");
	hSyst->SetFillColorAlpha(kBlack, 0.9);
	hSyst->SetFillStyle(3021);
	
	//== Comparision plot ==
	hComp = (TH1D*)hSamples.at(0)->Clone("data/mc");
	hComp->Divide(hSyst);
	hComp->SetStats(0);
	hComp->SetMarkerStyle(8);
	hComp->SetMarkerSize(0.5);
	hComp->GetYaxis()->SetRangeUser(0, 2);
	hComp->GetYaxis()->SetLabelSize(0.06);
	hComp->GetYaxis()->SetTitle("Data/Pred");
	hComp->GetYaxis()->SetTitleSize(0.08);
	hComp->GetYaxis()->SetTitleOffset(0.5);
	hComp->GetXaxis()->SetLabelSize(0.08);
	//hComp->SetNdivisions(504, "Y");
	hCompSyst = (TH1D*)hComp->Clone("syst for comparison");
	hCompSyst->SetFillColor(kGray+1);
	hCompSyst->SetFillStyle(3144);


	pUp->cd();
	pUp->SetGrid();
	hData->Draw("p&hist");
	hStack->Draw("hist&same");
	hData->Draw("e1&same");
	hSyst->Draw("e2&f&same");
	l->Draw("same");

	pDown->cd();
	pDown->SetGrid();
	hComp->Draw("p&hist");
	hCompSyst->Draw("e2&same");

	c->cd();
	pUp->Draw();
	pDown->Draw();
	c->Draw();

}
