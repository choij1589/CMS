#include "FileNavi.h"
#include "FileNavi.C"

void Canvas1() {
	//==== Basic information ====
	TString pathData = "$PWD/../../Output_ver_0.2/2016/NoFlag/DATA/";
	TString pathMC = "$PWD/../../Output_ver_0.2/2016/NoFlag/Samples/";

	vector<TString> Samples = {"DoubleEG", "ZGTo2LG"};
	vector<TString> ElectronIDs = {"passLooseID", "passTightID", "FakeLooseID", "FakeTightID"};

	FileNavi navi;
	navi.SetPathData(pathData);
	navi.SetPathMC(pathMC);
	navi.SetSamples(Samples);
	navi.SetElectronIDs(ElectronIDs);

	//==== User Settings ====
	TString ElectronID = "passTightID";
	vector<TString> histnames
		= {"1st_electron_pt_", "1st_electron_eta_", "1st_electron_phi_",
		"2nd_electron_pt_", "2nd_electron_eta_", "2nd_electron_phi_",
		"3rd_electron_pt_", "3rd_electron_eta_", "3rd_electron_phi_",
		"M(3e)_", "M(e+e-)_", "MET_", "NJets_", "PassSelection_", "pairCnt_"};
	bool trigScale = false;
	bool trigHist = true;
	unsigned int histnum = 11;
	//==== Get histograms from the settings ====
	TDirectory* dData = navi.GetDirectory(Samples.at(0), ElectronID + "_Central");
	TDirectory* dMC = navi.GetDirectory(Samples.at(1), ElectronID + "_Central");

	for (unsigned int i = 0; i < histnames.size(); i++) {
		//====
		if (trigHist && i != histnum) continue;
		TString this_histname = histnames.at(i);
		this_histname += ElectronID + "_Central";

		//==== prepare histograms to draw ====
		TH1D* hData = (TH1D*)dData->Get(this_histname);
		TH1D* hMC = (TH1D*)dMC->Get(this_histname);

		//=== MC need scale ====
		if (trigScale) {
			double passData = ((TH1D*)dData->Get("PassSelection_" + ElectronID + "_Central"))->Integral();;
			double passMC = ((TH1D*)dMC->Get("PassSelection_" + ElectronID + "_Central"))->Integral();
			double scale = passData / passMC;
			cout << "trigScale on" << endl;
			cout << "passData = " << passData << endl;
			cout << "passMC = " << passMC << endl;
			cout << "scale factor = " << scale << endl;
			hMC->Scale(scale);
		}
			
		TH1D* hComp = (TH1D*)hData->Clone("hcomp");
		hComp->Divide(hMC);

		if (!hData || !hMC) {
			cout << "no histogram for " << this_histname << endl;
			exit(EXIT_FAILURE);
		}
		//hData->Draw();
		//hMC->Draw();

		//==== histogram setting ====
		hData->SetStats(0);
		hData->SetMarkerStyle(8);
		hData->SetMarkerSize(0.5);
		hData->SetMarkerColor(kBlack);
		hData->GetXaxis()->SetLabelSize(0);
		//axis title name

		hMC->SetStats(0);
		hMC->SetFillColorAlpha(kBlue, 0.6);

		hComp->SetStats(0);
		hComp->SetMarkerStyle(8);
		hComp->SetMarkerSize(0.5);
		hComp->SetMarkerColor(kBlack);
		
		//==== Canvas setting =====
		TCanvas* c = new TCanvas("canvas", "", 720, 800);
		TPad* pUp = new TPad("pUp", "", 0, 0.25, 1, 1);
		TPad* pDown = new TPad("pDown", "", 0, 0, 1, 0.25);
		TLegend* l = new TLegend(0.69, 0.65, 0.93, 0.88);

		pUp->SetTopMargin(0.08);
		pUp->SetBottomMargin(0.02);
		pUp->SetLeftMargin(0.15);
		pUp->SetRightMargin(0.05);

		pDown->SetTopMargin(0.05);
		pDown->SetBottomMargin(0.45);
		pDown->SetLeftMargin(0.15);
		pDown->SetRightMargin(0.05);
		pDown->SetGrid();

		l->AddEntry(hData, "Date", "lep");
		l->AddEntry(hMC, "ZGTo2LG", "f");

		//==== Draw histograms ====
		pUp->cd();
		hData->Draw("p&hist");
		hMC->Draw("hist&same");
		hMC->Draw("e2&same");
		l->Draw("same");

		pDown->cd();
		hComp->Draw("p&hist");

		c->cd();
		pUp->Draw();
		pDown->Draw();
		c->Draw();

		if (!trigHist) c->Close();
	}
}
