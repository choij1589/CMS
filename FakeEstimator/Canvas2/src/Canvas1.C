#include "FileNavi.h"
#include "FileNavi.C"
#include "FakeValidation.h"
#include "FakeValidation.C"

void Canvas1() {
	//==== Basic Information ====
	TString pathData = "$PWD/../../Outputs/2016/RunSysts__HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v/DATA/";
    TString pathMC = "$PWD/../../Outputs/2016/RunSysts__HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30_v/Samples/";

    vector<TString> Samples = {"DoubleEG", "MC", "DYJets", "tt", "WJets_MG", "SingleTop", "tW"};
    vector<TString> IDs = {"passLooseID", "passTightID", "FakeLooseID", "FakeTightID"};
    vector<TString> Systs = {"Central", "JetPtCut30", "JetPtCut50", "JetPtCut60", "HadFlavor"};
    vector<TString> Prompts = {"Central", "JetResUp", "JetResDown", "JetEnUp", "JetEnDown",
                            "ElectronResUp", "ElectronResDown", "ElectronEnUp", "ElectronEnDown", "PileUp"};
    vector<TString> Regions = {"QCDEnriched", "WEnriched", "ZEnriched"};

	vector<TString> IDSets = {"POG", "Fake"};

	//==== initialize FakeValidation ====
	FakeValidation fake;
	fake.Init(pathData, pathMC, Samples, IDs, Systs, Prompts, Regions, IDSets);

	//fake.GetFakeRatePtEta(IDSets.at(1), Systs.at(0), "Central", 0.85)->Draw("colz");
	//fake.GetFakeRatePt(IDSets.at(1), Systs.at(0), "Central", 1).at(3)->Draw();
	
	TCanvas* cvs = new TCanvas("cvs", "cvs", 800, 450);
	TLegend* leg = new TLegend(0.15, 0.7, 0.35, 0.85);

	TString idset = "POG";
	vector<TH1D*> Central = fake.GetFakeRatePt(idset, "Central", "Central", 1.);
	vector<TH1D*> ptcut30 = fake.GetFakeRatePt(idset, "JetPtCut30", "Central", 1.);
	vector<TH1D*> ptcut60 = fake.GetFakeRatePt(idset, "JetPtCut60", "Central", 1.);
	vector<TH1D*> hadflavor = fake.GetFakeRatePt(idset, "HadFlavor", "Central", 1.);
	vector<TH1D*> promptup = fake.GetFakeRatePt(idset, "Central", "Central", 1.15);
	vector<TH1D*> promptdown = fake.GetFakeRatePt(idset, "Central", "Central", 0.85);

	for (int i = 0; i < Central.size(); i++) {
		ptcut30.at(i)->Add(Central.at(i), -1);
		ptcut60.at(i)->Add(Central.at(i), -1);
		hadflavor.at(i)->Add(Central.at(i), -1);
		promptup.at(i)->Add(Central.at(i), -1);
		promptdown.at(i)->Add(Central.at(i), -1);

		ptcut30.at(i)->Divide(Central.at(i));
		ptcut60.at(i)->Divide(Central.at(i));
		hadflavor.at(i)->Divide(Central.at(i));
		promptup.at(i)->Divide(Central.at(i));
		promptdown.at(i)->Divide(Central.at(i));
	}
	hadflavor.at(0)->Draw();


	//TH2D* h = fake.GetFakeRatePtEta("Fake", "Central", "Central", 1.);
	//vector<TH1D*> hs = fake.GetFakeRatePt("POG", "Central", "Central", 1.);
	/* ==== codes to estimate the systematic variation for the prompt normalization factor ====
	 * ==== about 15% is enough for every id ====
	TString id = "FakeLooseID";
	TString syst = "Central";
	
	vector<TH2D*> hPrompts;
	vector<TH2D*> hPromptsComp;
	vector<TH1D*> hPromptsCompPt;
	vector<TH1D*> hPromptsCompEta;

	for (unsigned int i = 0; i < Prompts.size(); i++) {
		TH2D* temp = fake.GetPromptNormPtEta(id, syst, Prompts.at(i));
		temp->Add(fake.GetPromptNormPtEta(id, syst, "Central"), -1);
		temp->Divide(fake.GetPromptNormPtEta(id, syst, "Central"));
		hPromptsComp.push_back(temp);

		TH1D* tempPt = fake.GetPromptNormPt(id, syst, Prompts.at(i));
		tempPt->Add(fake.GetPromptNormPt(id, syst, "Central"), -1);
		tempPt->Divide(fake.GetPromptNormPt(id, syst, "Central"));
		hPromptsCompPt.push_back(tempPt);

		TH1D* tempEta = fake.GetPromptNormEta(id, syst, Prompts.at(i));
		tempEta->Add(fake.GetPromptNormEta(id, syst, "Central"), -1);
		tempEta->Divide(fake.GetPromptNormPt(id, syst, "Central"));
		hPromptsCompEta.push_back(tempEta);
	}
	
	hPromptsCompPt.at(0)->SetStats(0);
	hPromptsCompPt.at(0)->GetYaxis()->SetRangeUser(-0.5, 0.5);
	cvs->cd();
	hPromptsCompPt.at(0)->Draw();
	hPromptsCompPt.at(1)->Draw("same");
	hPromptsCompPt.at(2)->Draw("same");
	hPromptsCompPt.at(3)->Draw("same");
	hPromptsCompPt.at(4)->Draw("same");
	hPromptsCompPt.at(5)->Draw("same");
	hPromptsCompPt.at(6)->Draw("same");
	hPromptsCompPt.at(7)->Draw("same");
	hPromptsCompPt.at(8)->Draw("same");
	hPromptsCompPt.at(9)->Draw("same");
	
	
	hPromptsCompEta.at(0)->SetStats(0);
    hPromptsCompEta.at(0)->GetYaxis()->SetRangeUser(-0.5, 0.5);
    cvs->cd();
    hPromptsCompEta.at(0)->Draw();
    hPromptsCompEta.at(1)->Draw("same");
    hPromptsCompEta.at(2)->Draw("same");
    hPromptsCompEta.at(3)->Draw("same");
    hPromptsCompEta.at(4)->Draw("same");
    hPromptsCompEta.at(5)->Draw("same");
    hPromptsCompEta.at(6)->Draw("same");
    hPromptsCompEta.at(7)->Draw("same");
    hPromptsCompEta.at(8)->Draw("same");
    hPromptsCompEta.at(9)->Draw("same");
	*/
}

