#include "FakeValidation.h"

//==== Other Functions ====
TH2D* FakeValidation::GetFakeRate(TString syst, double scale) {
	//==== return fake rate histogram
	//==== Setup
	//==== ID: FakeID
	//==== prompt: Central
	TString id_loose = IDs.at(2), id_tight = IDs.at(3);
	TString prompt = Prompts.at(0);

	TH2D* hFakeLooseData
	    = (TH2D*) navi.GetFakeDirectory(Samples.at(0), id_loose, syst, prompt, Regions.at(0))
		-> Get("passID3bins_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
	TH2D* hFakeLooseMC
	    = (TH2D*) navi.GetFakeDirectory(Samples.at(1), id_loose, syst, prompt, Regions.at(0))
		-> Get("passID3bins_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
	TH2D* hPromptLooseData
		= (TH2D*) navi.GetFakeDirectory(Samples.at(0), id_loose, syst, prompt, Regions.at(1))
		->Get("PromptEvents_" + Regions.at(1) + "_" + id_loose + "_" + syst + "_" + prompt);
	TH2D* hPromptLooseMC
		= (TH2D*) navi.GetFakeDirectory(Samples.at(1), id_loose, syst, prompt, Regions.at(1))
		->Get("PromptEvents_" + Regions.at(1) + "_" + id_loose + "_" + syst + "_" + prompt);
	Double_t scaleLoose = hPromptLooseData->Integral() / hPromptLooseMC->Integral();
	cout << "[FakeValidation::GetFakeRate] scaleLoose for " << syst << " = " << scaleLoose << endl;

	TH2D* hFakeTightData
	    = (TH2D*) navi.GetFakeDirectory(Samples.at(0), id_tight, syst, prompt, Regions.at(0))
		-> Get("passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
	TH2D* hFakeTightMC
		= (TH2D*) navi.GetFakeDirectory(Samples.at(1), id_tight, syst, prompt, Regions.at(0))
		-> Get("passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
	TH2D* hPromptTightData
		= (TH2D*) navi.GetFakeDirectory(Samples.at(0), id_tight, syst, prompt, Regions.at(1))
		->Get("PromptEvents_" + Regions.at(1) + "_" + id_tight + "_" + syst + "_" + prompt);
	TH2D* hPromptTightMC
		= (TH2D*) navi.GetFakeDirectory(Samples.at(1), id_tight, syst, prompt, Regions.at(1))
		->Get("PromptEvents_" + Regions.at(1) + "_" + id_tight + "_" + syst + "_" + prompt);
	Double_t scaleTight = hPromptTightData->Integral() / hPromptTightMC->Integral();
	cout << "[FakeValidation::GetFakeRate] scaleTight for " << syst << " = " << scaleTight << endl;

	TH2D* hFakeLoose = (TH2D*)hFakeLooseData->Clone("fake loose");
	hFakeLoose->Add(hFakeLooseMC, -1*scaleLoose*scale);
	//hFakeLoose->Draw("colz");
	TH2D* hFakeTight = (TH2D*)hFakeTightData->Clone("fake tight");
	hFakeTight->Add(hFakeTightMC, -1*scaleTight*scale);

	TH2D* hFakeRate = (TH2D*)hFakeTight->Clone("fake rate");
	hFakeRate->Divide(hFakeLoose);
	
	return hFakeRate;
};

TH1D* FakeValidation::GetFakeRatePt(TString syst, double scale) {
	//==== Setup
	//==== ID: FakeID
	//==== prompt: Central
	TString id_loose = IDs.at(2), id_tight = IDs.at(3);
	TString prompt = Prompts.at(0);

	TH2D* hFakeLooseData
	    = (TH2D*) navi.GetFakeDirectory(Samples.at(0), id_loose, syst, prompt, Regions.at(0))
		-> Get("passID3bins_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
	TH2D* hFakeLooseMC
	    = (TH2D*) navi.GetFakeDirectory(Samples.at(1), id_loose, syst, prompt, Regions.at(0))
		-> Get("passID3bins_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
	TH2D* hPromptLooseData
		= (TH2D*) navi.GetFakeDirectory(Samples.at(0), id_loose, syst, prompt, Regions.at(1))
		->Get("PromptEvents_" + Regions.at(1) + "_" + id_loose + "_" + syst + "_" + prompt);
	TH2D* hPromptLooseMC
		= (TH2D*) navi.GetFakeDirectory(Samples.at(1), id_loose, syst, prompt, Regions.at(1))
		->Get("PromptEvents_" + Regions.at(1) + "_" + id_loose + "_" + syst + "_" + prompt);
	Double_t scaleLoose = hPromptLooseData->Integral() / hPromptLooseMC->Integral();
	cout << "[FakeValidation::GetFakeRate] scaleLoose for " << syst << " = " << scaleLoose << endl;

	TH2D* hFakeTightData
	    = (TH2D*) navi.GetFakeDirectory(Samples.at(0), id_tight, syst, prompt, Regions.at(0))
		-> Get("passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
	TH2D* hFakeTightMC
		= (TH2D*) navi.GetFakeDirectory(Samples.at(1), id_tight, syst, prompt, Regions.at(0))
		-> Get("passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
	TH2D* hPromptTightData
		= (TH2D*) navi.GetFakeDirectory(Samples.at(0), id_tight, syst, prompt, Regions.at(1))
		->Get("PromptEvents_" + Regions.at(1) + "_" + id_tight + "_" + syst + "_" + prompt);
	TH2D* hPromptTightMC
		= (TH2D*) navi.GetFakeDirectory(Samples.at(1), id_tight, syst, prompt, Regions.at(1))
		->Get("PromptEvents_" + Regions.at(1) + "_" + id_tight + "_" + syst + "_" + prompt);
	Double_t scaleTight = hPromptTightData->Integral() / hPromptTightMC->Integral();
	cout << "[FakeValidation::GetFakeRate] scaleTight for " << syst << " = " << scaleTight << endl;

	TH2D* hFakeLoose = (TH2D*)hFakeLooseData->Clone("fake loose");
	hFakeLoose->Add(hFakeLooseMC, -1*scaleLoose*scale);
	TH1D* hFakeLoosePt = hFakeLoose->ProjectionX("_px_loose");

	TH2D* hFakeTight = (TH2D*)hFakeTightData->Clone("fake tight");
	hFakeTight->Add(hFakeTightMC, -1*scaleTight*scale);
	TH1D* hFakeTightPt = hFakeTight->ProjectionX("_px_tight");

	TH1D* hFakeRatePt = (TH1D*)hFakeTightPt->Clone("fake rate pt");
	hFakeRatePt->Divide(hFakeLoosePt);

	return hFakeRatePt;
}

TCanvas* FakeValidation::DrawFake1D(TString syst, int scale) {
	//==== scale can be 0, -1, 1 ====
	vector<TH2D*> hFakes, hFakes_up, hFakes_down;

	for (unsigned int i = 0; i < Systs.size(); i++) {
	    TH2D* hTemp = FakeValidation::GetFakeRate(Systs.at(i), 1);
		hTemp->SetStats(0);
		if (hTemp) hFakes.push_back(hTemp);
		else {
			cout << "[FakeValidation::DrawFake1D] NULL TH2D*" << endl;
			exit(EXIT_FAILURE);
		}
	}
	for (unsigned int i = 0; i < Systs.size(); i++) {
		TH2D* hTemp = FakeValidation::GetFakeRate(Systs.at(i), 1.15);
		hTemp->SetStats(0);
		if (hTemp) hFakes_up.push_back(hTemp);
		else {
			cout << "NULL TH2D*" << endl;
			exit(EXIT_FAILURE);
		}
	}
	for (unsigned int i = 0; i < Systs.size(); i++) {
	    TH2D* hTemp = FakeValidation::GetFakeRate(Systs.at(i), 0.85);
		hTemp->SetStats(0);
		if (hTemp) hFakes_down.push_back(hTemp);
		else {
			cout << "NULL TH2D*" << endl;
			exit(EXIT_FAILURE);
		}
	}

	map<TString, vector<TH1D*>> hFakes1D; // hFakes1D[Systs.at(i)].at(j)
	map<TString, vector<TH1D*>> hFakes1D_up;
	map<TString, vector<TH1D*>> hFakes1D_down;
			    
	for (unsigned int i = 0; i < Systs.size(); i++) {
		TString name = "_px_" + to_string(i);
		TString name1 = "_px1_" + to_string(i);
		TString name2 = "_px2_" + to_string(i);
		TString name3 = "_px3_" + to_string(i);

		TH1D* h_px = FakeValidation::GetFakeRatePt(Systs.at(i), 1);
		TH1D* h_px1 = hFakes.at(i)->ProjectionX(name1, 1, 1);
		TH1D* h_px2 = hFakes.at(i)->ProjectionX(name2, 2, 2);
		TH1D* h_px3 = hFakes.at(i)->ProjectionX(name3, 3, 3);
		hFakes1D[Systs.at(i)].push_back(h_px);
		hFakes1D[Systs.at(i)].push_back(h_px1);
		hFakes1D[Systs.at(i)].push_back(h_px2);
		hFakes1D[Systs.at(i)].push_back(h_px3);
	}

	for (unsigned int i = 0; i < Systs.size(); i++) {
	    TString name_up = "_px_up_" + to_string(i);
		TString name_up1 = "_px1_up_" + to_string(i);
		TString name_up2 = "_px2_up_" + to_string(i);
		TString name_up3 = "_px3_up_" + to_string(i);

		TH1D* h_px_up = FakeValidation::GetFakeRatePt(Systs.at(i), 1.15);
		TH1D* h_px_up1 = hFakes_up.at(i)->ProjectionX(name_up1, 1, 1);
		TH1D* h_px_up2 = hFakes_up.at(i)->ProjectionX(name_up2, 2, 2);
		TH1D* h_px_up3 = hFakes_up.at(i)->ProjectionX(name_up3, 3, 3);
		hFakes1D_up[Systs.at(i)].push_back(h_px_up);
		hFakes1D_up[Systs.at(i)].push_back(h_px_up1);
		hFakes1D_up[Systs.at(i)].push_back(h_px_up2);
		hFakes1D_up[Systs.at(i)].push_back(h_px_up3);
	}

	for (unsigned int i = 0; i < Systs.size(); i++) {
	    TString name_down = "_px_down_" + to_string(i);
		TString name_down1 = "_px1_down_" + to_string(i);
		TString name_down2 = "_px2_down_" + to_string(i);
		TString name_down3 = "_px3_down_" + to_string(i);

		TH1D* h_px_down = FakeValidation::GetFakeRatePt(Systs.at(i), 0.85);
		TH1D* h_px_down1 = hFakes_down.at(i)->ProjectionX(name_down1, 1, 1);
		TH1D* h_px_down2 = hFakes_down.at(i)->ProjectionX(name_down2, 2, 2);
		TH1D* h_px_down3 = hFakes_down.at(i)->ProjectionX(name_down3, 3, 3);
		hFakes1D_down[Systs.at(i)].push_back(h_px_down);
		hFakes1D_down[Systs.at(i)].push_back(h_px_down1);
		hFakes1D_down[Systs.at(i)].push_back(h_px_down2);
		hFakes1D_down[Systs.at(i)].push_back(h_px_down3);
	}

	//==== Choose histogram to dradw ====
	TH1D* h_central = hFakes1D["Central"].at(0);
	TH1D* h_syst = NULL;
	if (scale == 0) h_syst = hFakes1D[syst].at(0);
	else if (scale == +1) h_syst = hFakes1D_up[syst].at(0);
	else if (scale == -1) h_syst = hFakes1D_down[syst].at(0);
	else {
		cout << "[FakeValidation::DrawFake1D] Wrong scale" << endl;
		exit(EXIT_FAILURE);
	}
	if (!h_syst) {
		cout << "[FakeValidation::DrawFake1D] No systematic hist]" << endl;
		exit(EXIT_FAILURE);
	}
	//h_central->Draw();
	//h_syst->Draw();
	TH1D* h_compare = (TH1D*)h_syst->Clone("");
	h_compare->Add(h_central, -1);
	h_compare->Divide(h_central);

	//==== histogram up settings =====
	h_syst->SetStats(0);
	h_syst->SetLineColor(kBlue);
	h_central->SetStats(0);
	h_central->SetLineColor(kBlack);
	h_central->GetYaxis()->SetRangeUser(0, 0.5);

	//==== histogram down settings ====
	h_compare->SetStats(0);
	h_compare->SetLineColor(kBlack);
	h_compare->GetYaxis()->SetRangeUser(-1, 1);

	//==== Canvas settings =====
	TCanvas* cvs = new TCanvas("canvas", "canvas", 900, 1600);
	TPad* pad_up = new TPad("pad_up", "pad_up", 0, 0.25, 1, 1);
	TPad* pad_down = new TPad("pad_down", "pad_down", 0, 0, 1, 0.25);

	pad_up->cd();
	pad_up->SetGrid();
	h_central->Draw();
	h_syst->Draw("same");

	pad_down->cd();
	pad_down->SetGrid();
	h_compare->Draw();

	cvs->cd(); pad_up->Draw(); pad_down->Draw();
	
	return cvs;
}








































