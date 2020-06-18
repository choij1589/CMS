#include "FileNavi.h"
#include "FileNavi.C"

//==== Canvas discription ====
//==== This canvas is to get the conversion scale factor ====
//==== and check whether the distribution matches well ====

void Canvas1() {
	//==== Basic information ====
	TString pathData = "$PWD/../../Output_ver_1.0/2016/RunFakeSyst__/DATA/";
	TString pathMC = "$PWD/../../Output_ver_1.0/2016/RunFakeSyst__/Samples/";

	vector<TString> Samples = {"DoubleEG", "MC", "conv", "VV", "rare", "ttVorH"};
	vector<TString> IDSets = {"POGID", "FakeID"};

	FileNavi navi;
	navi.SetPathData(pathData);
	navi.SetPathMC(pathMC);
	navi.SetSamples(Samples);
	navi.SetIDSets(IDSets);

	//==== User Settings ====
	TString idset = "FakeID";
	vector<TString> histnames
		= {"1st_electron_pt_", "1st_electron_eta_", "1st_electron_phi_",
		"2nd_electron_pt_", "2nd_electron_eta_", "2nd_electron_phi_",
		"3rd_electron_pt_", "3rd_electron_eta_", "3rd_electron_phi_",
		"M(3e)_", "M(e+e-)_", "MET_", "NJets_", "PassSelection_", "pairCnt_"};
	bool trigScale = false;
	bool trigHist = true;
	unsigned int histnum = 0;


	//==== Get histograms from the settings ====
	//==== Get Directories ====
	vector<TDirectory*> dirs;
	for (unsigned int i = 0; i < Samples.size(); i++) {
		TDirectory* this_dir = navi.GetDirectory(Samples.at(i), idset, 0, 0);
		dirs.push_back(this_dir);
	}
	TDirectory* dFake = navi.GetDirectory(Samples.at(0), idset, 1, 0);
	TDirectory* dFakeUp = navi.GetDirectory(Samples.at(0), idset, 1, 1);
	TDirectory* dFakeDown = navi.GetDirectory(Samples.at(0), idset, 1, -1);
	
	//==== Get the conversion scale factor first ====
	TH1D* hData = (TH1D*) dirs.at(0)->Get("PassSelection_" + idset + "_Central");
	TH1D* hConv = (TH1D*) dirs.at(2)->Get("PassSelection_" + idset + "_Central");
	TH1D* hScale = (TH1D*) hData->Clone("Conv_scale");
	vector<TH1D*> hPrompts;
	for (unsigned int i = 3; i < Samples.size(); i++) {
		TH1D* this_hist = (TH1D*) dirs.at(i)->Get("PassSelection_" + idset + "_Central");
		hPrompts.push_back(this_hist);
		hScale->Add(this_hist, -1);
	}
	// subtract fake histograms
	hScale->Divide(hConv);
	double scale = hScale->Integral();
	cout << scale << endl;


	//==== Draw validation plots ====
	for (unsigned int i = 0; i < histnames.size(); i++) {
		if (trigHist && i != histnum) continue;
		
		//==== prepare canvas and legend ====
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
		
		//==== prepare histograms ====
		TString this_histname = histnames.at(i) + idset + "_Central";
		
		vector<TH1D*> this_hists;
		for (unsigned int j = 0; j < dirs.size(); j++) {
			TH1D* this_hist = (TH1D*) dirs.at(j)->Get(this_histname);
			if (trigScale && j==2) this_hist->Scale(scale);
			this_hists.push_back(this_hist);
		}
		
		TH1D* this_Fake = (TH1D*) dFake->Get(histnames.at(i) + idset + "_Fake_Central");
		TH1D* this_FakeUp = (TH1D*) dFakeUp->Get(histnames.at(i) + idset + "_Fake_SystUp");
		TH1D* this_FakeDown = (TH1D*) dFakeDown->Get(histnames.at(i) + idset + "_Fake_SystDown");

		// systematic setting for hFake
		
		TH1D* this_data = this_hists.at(0);
		TH1D* this_syst = (TH1D*)this_hists.at(2)->Clone("syst");
		for (unsigned int j = 3; j < Samples.size(); j++) {
			this_syst->Add(this_hists.at(j));
		}
		this_syst->Add(this_Fake);
		this_syst->Draw();
		
		TH1D* this_comp = (TH1D*)this_data->Clone("data/mc");
		this_comp->Divide(this_syst);

		//==== this_stack setting ====
		THStack* this_stack = new THStack("hs", "");
		for (unsigned int j = 2; j < this_hists.size(); j++) {
			// this_hists.at(j) need user settings
			if (Samples.at(j).Contains("conv")) {
				this_hists.at(j)->SetFillColorAlpha(kBlue, 0.5);
				l->AddEntry(this_hists.at(j), "conv", "f");
			}
			if (Samples.at(j).Contains("VV")) {
				this_hists.at(j)->SetFillColorAlpha(kAzure, 0.5);
				l->AddEntry(this_hists.at(j), "VV", "f");
			}
			if (Samples.at(j).Contains("rare")) {
				this_hists.at(j)->SetFillColorAlpha(kViolet, 0.5);
				l->AddEntry(this_hists.at(j), "rare", "f");
			}
			if (Samples.at(j).Contains("ttVorH")) {
				this_hists.at(j)->SetFillColorAlpha(kGreen, 0.5);
				l->AddEntry(this_hists.at(j), "ttV/H", "f");
			}

			this_stack->Add(this_hists.at(j));
		}
		this_Fake->SetFillColorAlpha(kRed, 0.5);
		this_stack->Add(this_Fake);
		l->AddEntry(this_Fake, "fake", "f");
		
		//==== this_data setting ====
		this_data->SetMarkerStyle(8);
		this_data->SetMarkerSize(0.5);
		this_data->SetMarkerColor(kBlack);
		
		this_data->GetYaxis()->SetRangeUser(0, 150);
		this_data->SetStats(0);
		l->AddEntry(this_data, "Data", "lep");

		//==== this_syst setting ====
		
		//==== this_comp setting ====
		this_comp->SetStats(0);
		this_comp->SetMarkerStyle(8);
        this_comp->SetMarkerSize(0.5);
        this_comp->SetMarkerColor(kBlack);
		
		//==== Draw ====
		pUp->cd();
		this_data->Draw("p&hist");
		this_data->Draw("e1&same");
		this_stack->Draw("hist&same");
		//this_syst->Draw("e2&f&same");
		l->Draw("same");

		pDown->cd();
		this_comp->Draw("p&hist");
		//this_comp->Draw("e2&same");

		c->cd();
		pUp->Draw();
		pDown->Draw();
		c->Draw();
		
		//c->SaveAs();
		//c->Close();
	}
}
