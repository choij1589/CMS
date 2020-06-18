#include "FileNavi.h"
#include "FileNavi.C"

void Canvas1() {
	//==== Basic information ====
	///home/choij/Documents/CMS/FakeValidator/Output_ver_1.0/2016/RunFakeSyst__RunPrompt__/DATA
	TString pathData = "$PWD/../../Output_ver_1.0/2016/RunFakeSyst__RunPrompt__/DATA/";
	TString pathMC = "$PWD/../../Output_ver_1.0/2016/RunFakeSyst__RunPrompt__/Samples/";

	//vector<TString> Samples = {"DoubleEG", "MC", "ttVorH", "VV", "rare"};
	vector<TString> Samples = {"DoubleEG", "MC", "ttVorH", "VV", "rare", "conv"};
	vector<TString> IDSets = {"POGID", "FakeID"};

	FileNavi navi;
	navi.SetPathData(pathData);
	navi.SetPathMC(pathMC);
	navi.SetSamples(Samples);
	navi.SetIDSets(IDSets);

	//==== Preparation ====
	//TString histname = "1st_electron_eta_";
	TString histname = "1st_electron_pt_";
	//TString histname = "1st_electron_phi";
	//TString histname = "2nd_electron_eta_";
	//TString histname = "2nd_electron_phi_;
	//TString histname = "2nd_electron_pt_";
	//TString histname = "3rd_electron_eta_";
	//TString histname = "3rd_electron_pt_";
	//TString histname = "3rd_electron_phi_";
	//TString histname = "MET_";
	//TString histname = "Njets_";
	
	TString idset = "FakeID";
	//TString idset = "POGID";
	
	//==== prepare histograms to stack ====
	THStack* hs = new THStack("hs", "");
	vector<TH1D*> hSamples;
	//TLegend* leg = new TLegend(0, 0, 0, 0);
	for (unsigned int i = 0; i < Samples.size(); i++) {
		TDirectory* this_dir = navi.GetDirectory(Samples.at(i), idset, 0, 0);
		TString this_histname = histname + idset + "_Central";
		TH1D* this_hist = (TH1D*)this_dir->Get(this_histname);
		if (!this_hist) {
			cout << "no " << this_histname << endl;
			exit(EXIT_FAILURE);
		}
		//if(i != 0) this_hist->Scale(0.8);
		hSamples.push_back(this_hist);
	}
	TDirectory* dFake = navi.GetDirectory(Samples.at(0), idset, 1, 0);
	TDirectory* dFakeUp = navi.GetDirectory(Samples.at(0), idset, 1, 1);
	TDirectory* dFakeDown = navi.GetDirectory(Samples.at(0), idset, 1, -1);

	TH1D* hFake = (TH1D*)dFake->Get(histname + idset + "_Central_FakeContribution");
	TH1D* hFakeUp = (TH1D*)dFakeUp->Get(histname + idset + "_SystUp_FakeContribution");
	TH1D* hFakeDown = (TH1D*)dFakeDown->Get(histname + idset + "_SystDown_FakeContribution");
	//==== set errors for hFake ====
	int nbin = 0;
	if (histname.Contains("pt") && histname.Contains("1st")) nbin = hFake->FindBin(199);
	else if (histname.Contains("pt") && histname.Contains("2nd")) nbin = hFake->FindBin(159);
	else if (histname.Contains("pt") && histname.Contains("3rd")) nbin = hFake->FindBin(159);
	else if (histname.Contains("eta")) nbin = hFake->FindBin(2.9);
	else if (histname.Contains("phi")) nbin = hFake->FindBin(3.1);
	else if (histname.Contains("MET")) nbin = hFake->FindBin(150);
	else if (histname.Contains("NJets")) nbin = hFake->FindBin(6);
	else {
		cout << "no histogram for histname = " << histname << endl;
		exit(EXIT_FAILURE);
	}
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
		hFake->SetBinError(i+1, this_totalerr);
		cout << "bin " << i+1 << " : " << this_totalerr << endl;
	}
	hFake->SetFillColorAlpha(kRed, 0.7);
	//hFake->Draw();
	hSamples.push_back(hFake);

	for (unsigned int i = 2; i < hSamples.size(); i++) {
		hs->Add(hSamples.at(i));
	}

	TH1D* hSyst = (TH1D*) hFake->Clone("hSyst");
	for (unsigned int i = 2; i < hSamples.size()-1; i++) {
		hSyst->Add(hSamples.at(i));
	}
	TH1D* hComp = (TH1D*) hSamples.at(0)->Clone("hComp");
	hComp->Divide(hSyst);
	hSyst->SetFillColorAlpha(kBlack, 0.5);
	hSyst->SetFillStyle(3354);
	hSyst->GetYaxis()->SetRangeUser(0, 800);
	hSyst->Draw("e2");
	hSamples.at(0)->Draw("hist same&e&p");
	hs->Draw("hist f&same");
	//hComp->Draw();

}
