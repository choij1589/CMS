#include "FakeValidation.h"
using namespace std;

//==== initialize "FileNavi navi" ====
void FakeValidation::Init(
        const TString &path_data, const TString &path_mc,
        const vector<TString> &samples, const vector<TString> &ids, const vector<TString> systs,
        const vector<TString> &prompts, const vector<TString> &regions,
		const vector<TString> &idsets) {

	navi.SetPathData(path_data);
    navi.SetPathMC(path_mc);
    navi.SetSamples(samples);
    navi.SetIDs(ids);
    navi.SetSysts(systs);
    navi.SetPrompts(prompts);
    navi.SetRegions(regions);

    navi.LoadFakeDirectory();

	IDSets = idsets;
}

//==== Other Functions ====
TH1* FakeValidation::GetHist(TString sample, TString histname) {
	//==== informatino setup ====
	vector<TString> Samples = navi.GetSamples();
	vector<TString> IDs = navi.GetIDs();
	vector<TString> Systs = navi.GetSysts();
	vector<TString> Prompts = navi.GetPrompts();
	vector<TString> Regions = navi.GetRegions();

	//==== read information from the histname ====
	TString id, syst, prompt, region;
	for (unsigned int i = 0; i < IDs.size(); i++) {
		if (histname.Contains(IDs.at(i))) id = IDs.at(i);
	}
	for (unsigned int i = 0; i < Systs.size(); i++) {
        if (histname.Contains(Systs.at(i))) syst = Systs.at(i);
    }
	for (unsigned int i = 0; i < Prompts.size(); i++) {
        if (histname.Contains(Prompts.at(i))) prompt = Prompts.at(i);
    }
	for (unsigned int i = 0; i < Regions.size(); i++) {
        if (histname.Contains(Regions.at(i))) region = Regions.at(i);
    }
	//==== check the information ====
	//cout << "[FakeValidation::GetHist] histname = " << histname << endl;
	//cout << "[FakeValidation::GetHist] sample = " << sample << endl;
	//cout << "[FakeValidation::GetHist] id = " << id << endl;
	//cout << "[FakeValidation::GetHist] syst = " << syst << endl;
	//cout << "[FakeValidation::GetHist] prompt = " << prompt << endl;
	//cout << "[FakeValidation::GetHist] region = " << region << endl;

	//==== get directory from the information ====
	TDirectory* dir = navi.GetFakeDirectory(sample, id, syst, prompt, region);
	if (!dir) {
		cout << "[FakeValidation::GetHist] NULL Directory" << endl;
		exit(EXIT_FAILURE);
	}

	//==== get histogram ====
	TH1* hist = (TH1*)dir->Get(histname);
	return hist;
}

double FakeValidation::GetPromptScale(TString id, TString syst, TString prompt) {

    //==== informatino setup ====
    vector<TString> Samples = navi.GetSamples();
    //vector<TString> IDs = navi.GetIDs();
    //vector<TString> Systs = navi.GetSysts();
    //vector<TString> Prompts = navi.GetPrompts();
    vector<TString> Regions = navi.GetRegions();

    TH1D* hPromptData = (TH1D*)GetHist(Samples.at(0), "PromptEvents_" + Regions.at(1) +  "_" + id + "_" + syst + "_" + prompt);
    TH1D* hPromptMC = (TH1D*)GetHist(Samples.at(1), "PromptEvents_" + Regions.at(1) + "_" + id + "_" + syst + "_" + prompt);
    double scale = hPromptData->Integral() / hPromptMC->Integral();

    return scale;
}

TH2D* FakeValidation::GetFakeRatePtEta(TString idset, TString syst, TString prompt, double promptScale) {
	//==== information setup ====
    vector<TString> Samples = navi.GetSamples();
    vector<TString> IDs = navi.GetIDs();
    //vector<TString> Systs = navi.GetSysts();
    //vector<TString> Prompts = navi.GetPrompts();
    vector<TString> Regions = navi.GetRegions();

	//==== ID setting ====
	TString id_loose, id_tight;
	for (unsigned int i = 0; i < IDSets.size(); i++) {
		if (idset == IDSets.at(i)) {
			id_loose = IDs.at(i*2);
			id_tight = IDs.at(i*2 + 1);
		}
	}
	cout << "[FakeValidation::GetFakeRatePtEta] id_loose = " << id_loose << endl;
	cout << "[FakeValidation::GetFakeRatePtEta] id_tight = " << id_tight << endl;

	//==== load hitograms ====
	TH2D* hFakeLooseData
		= (TH2D*)GetHist(Samples.at(0), "passID3bins_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
	TH2D* hFakeLooseMC
		= (TH2D*)GetHist(Samples.at(1), "passID3bins_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
	double scaleLoose = GetPromptScale(id_loose, syst, prompt);
	cout << "[FakeValidation::GetFakeRatePtEta] " << syst << " scaleLoose = " << scaleLoose << endl;
	
	TH2D* hFakeTightData
        = (TH2D*)GetHist(Samples.at(0), "passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
    TH2D* hFakeTightMC
        = (TH2D*)GetHist(Samples.at(1), "passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
	double scaleTight = GetPromptScale(id_tight, syst, prompt);
    cout << "[FakeValidation::GetFakeRatePtEta] " << syst << " scaleTight = " << scaleTight << endl;

	//==== Fake Rate Manipulation ====
	TH2D* hFakeLoose = (TH2D*)hFakeLooseData->Clone("fake loose");
    hFakeLoose->Add(hFakeLooseMC, -1 * scaleLoose * promptScale);
    TH2D* hFakeTight = (TH2D*)hFakeTightData->Clone("fake tight");
    hFakeTight->Add(hFakeTightMC, -1 * scaleTight * promptScale);

    TH2D* hFakeRate = (TH2D*)hFakeTight->Clone("fake rate");
    hFakeRate->Divide(hFakeLoose);

	cout << "[FakeValidation::GetFakeRatePtEta] fake rate called" << endl;
	cout << "[FakeValidation::GetFakeRatePtEta] syst = " << syst << endl;
	cout << "[FakeValidation::GetFakeRatePtEta] prompt = " << prompt << endl;

    return hFakeRate;
}

vector<TH1D*> FakeValidation::GetFakeRatePt(TString idset, TString syst, TString prompt, Double_t promptScale){
	//==== information setup ====
    vector<TString> Samples = navi.GetSamples();
    vector<TString> IDs = navi.GetIDs();
    //vector<TString> Systs = navi.GetSysts();
    //vector<TString> Prompts = navi.GetPrompts();
    vector<TString> Regions = navi.GetRegions();

	//==== ID setting ====
    TString id_loose, id_tight;
    for (unsigned int i = 0; i < IDSets.size(); i++) {
        if (idset == IDSets.at(i)) {
            id_loose = IDs.at(i*2);
            id_tight = IDs.at(i*2 + 1);
        }
    }
    cout << "[FakeValidation::GetFakeRatePt] id_loose = " << id_loose << endl;
    cout << "[FakeValidation::GetFakeRatePt] id_tight = " << id_tight << endl;

	//==== prepare fake rate histograms ====
	vector<TH1D*> temp;
	int scale;
	if (promptScale == 1) scale = 0;
	else if (promptScale > 1) scale = 1;
	else if (promptScale < 1) scale = -1;
	TString name = "_px_" + syst + "_" + prompt + TString::Itoa(scale, 10);
	TString name1 = "_px1_" + syst + "_" + prompt + TString::Itoa(scale, 10);
	TString name2 = "_px2_" + syst + "_" + prompt + TString::Itoa(scale, 10);
	TString name3 = "_px3_" + syst + "_" + prompt + TString::Itoa(scale, 10);
	
	TH2D* hFakeLooseData
        = (TH2D*)GetHist(Samples.at(0), "passID3bins_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
    TH2D* hFakeLooseMC
        = (TH2D*)GetHist(Samples.at(1), "passID3bins_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
	
	double scaleLoose = GetPromptScale(id_loose, syst, prompt);
    cout << "[FakeValidation::GetFakeRatePt] " << syst << " scaleLoose = " << scaleLoose << endl;

    TH2D* hFakeTightData
        = (TH2D*)GetHist(Samples.at(0), "passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
    TH2D* hFakeTightMC
        = (TH2D*)GetHist(Samples.at(1), "passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
	double scaleTight = GetPromptScale(id_tight, syst, prompt);
    cout << "[FakeValidation::GetFakeRatePt] " << syst << " scaleTight = " << scaleTight << endl;

	TH2D* hFakeLoose = (TH2D*)hFakeLooseData->Clone("fake loose");
    hFakeLoose->Add(hFakeLooseMC, -1 * scaleLoose * promptScale);
    TH2D* hFakeTight = (TH2D*)hFakeTightData->Clone("fake tight");
    hFakeTight->Add(hFakeTightMC, -1 * scaleTight * promptScale);

	TH1D* fakeProjectionX = hFakeTight->ProjectionX(name);
	fakeProjectionX->Divide(hFakeLoose->ProjectionX(""));

	TH2D* fakePtEta = GetFakeRatePtEta(idset, syst, prompt, promptScale);
	TH1D* fake1 = fakePtEta->ProjectionX(name1, 1, 1);
	TH1D* fake2 = fakePtEta->ProjectionX(name2, 2, 2);
	TH1D* fake3 = fakePtEta->ProjectionX(name3, 3, 3);

	temp.push_back(fakeProjectionX);
	temp.push_back(fake1);
	temp.push_back(fake2);
	temp.push_back(fake3);

	return temp;
}

TH2D* FakeValidation::GetFakeCompPtEta(TString idset, TString syst, TString prompt, double promptScale) {

	cout << "[FakeValidation::GetFakeCompPtEta] Basic information" << endl;
	cout << "[FakeValidation::GetFakeCompPtEta] idset = " << idset << endl;
	cout << "[FakeValidation::GetFakeCompPtEta] syst = " << syst << endl;
	cout << "[FakeValidation::GetFakeCompPtEta] prompt = " << prompt << endl;
	cout << "[FakeValidation::GetFakeCompPtEta] promptScale = " << promptScale << endl;

	TH2D* h_central = GetFakeRatePtEta(idset, "Central", prompt , 1.);
	TH2D* h_syst = GetFakeRatePtEta(idset, syst, prompt, promptScale);
	TH2D* h_comp = (TH2D*) h_syst->Clone("");
	h_comp->Add(h_central, -1);
	h_comp->Divide(h_central);

	return h_comp;
}


vector<TH1D*> FakeValidation::GetFakeCompPt(TString idset, TString syst, TString prompt, double promptScale){

	cout << "[FakeValidation::GetFakeCompPt] Basic information" << endl;
	cout << "[FakeValidation::GetFakeCompPt] idset = " << idset << endl;
	cout << "[FakeValidation::GetFakeCompPt] syst = " << syst << endl;
	cout << "[FakeValidation::GetFakeCompPt] prompt = " << prompt << endl;
	cout << "[FakeValidation::GetFakeCompPt] promptScale = " << promptScale << endl;

	vector<TH1D*> h_central = GetFakeRatePt(idset, "Central", prompt, 1.);
	vector<TH1D*> h_syst = GetFakeRatePt(idset, syst, prompt, promptScale);
	
	vector<TH1D*> h_comp = h_syst;
	for (unsigned int i = 0; i < h_comp.size(); i++) {
		h_comp.at(i)->Add(h_central.at(i), -1);
		h_comp.at(i)->Divide(h_central.at(i));
	}

	return h_comp;
}



TH2D* FakeValidation::GetPromptNormPtEta(TString id, TString syst, TString prompt) {
	//==== Check information ====
	TString data = "DoubleEG";
	TString mc = "MC";
	
	TH2D* h_data = (TH2D*) GetHist(data, "passID3bins_WEnriched_" + id + "_" + syst + "_" + prompt);
	TH2D* h_mc = (TH2D*) GetHist(mc, "passID3bins_WEnriched_" + id + "_" + syst + "_" + prompt);

	TH2D* h = (TH2D*)h_data->Clone("");
	h->Divide(h_mc);
	
	return h;
}

vector<TH1D*> FakeValidation::GetPromptNormPt(TString id, TString syst, TString prompt) {
	TString data = "DoubleEG";
	TString mc = "MC";

	TH2D* h_data = (TH2D*) GetHist(data, "passID3bins_WEnriched_" + id + "_" + syst + "_" + prompt);
	TH2D* h_mc = (TH2D*) GetHist(mc, "passID3bins_WEnriched_" + id + "_" + syst + "_" + prompt);

	TH1D* h_total = h_data->ProjectionX("_px_" + syst + "_" + prompt); h_total->Divide(h_mc->ProjectionX("_px_mc_" + syst + "_" + prompt));
	TH1D* h_bin1 = h_data->ProjectionX("_px1_"+ syst + "_" + prompt, 1, 1); h_bin1->Divide(h_mc->ProjectionX("_px1_mc_" + syst + "_" + prompt, 1, 1));
	TH1D* h_bin2 = h_data->ProjectionX("_px2_"+ syst + "_" + prompt, 2, 2); h_bin2->Divide(h_mc->ProjectionX("_px2_mc_" + syst + "_" + prompt, 2, 2));
	TH1D* h_bin3 = h_data->ProjectionX("_px3_"+ syst + "_" + prompt, 3, 3); h_bin3->Divide(h_mc->ProjectionX("_px3_mc_" + syst + "_" + prompt, 3, 3));


	vector<TH1D*> temp;
	temp.push_back(h_total); temp.push_back(h_bin1); temp.push_back(h_bin2); temp.push_back(h_bin3);
	
	return temp;
}

TH2D* FakeValidation::GetPromptCompPtEta(TString id, TString syst, TString prompt) {
	cout << "[FakeValidation::GetPromptCompPtEta] Basic information" << endl;
	cout << "[FakeValidation::GetPromptCompPtEta] id = " << id << endl;
	cout << "[FakeValidation::GetPromptCompPtEta] syst = " << syst << endl;
	cout << "[FakeValidation::GetPromptCompPtEta] prompt = " << prompt << endl;

	//==== recommended to put syst as "Central" to see the overall normalization variation ====
	TH2D* h_syst = GetPromptNormPtEta(id, syst, prompt);
	TH2D* h_central = GetPromptNormPtEta(id, syst, "Central");
	h_syst->Add(h_central, -1);
	h_syst->Divide(h_central);

	return h_syst;
}

vector<TH1D*> FakeValidation::GetPromptCompPt(TString id, TString syst, TString prompt) {
	cout << "[FakeValidation::GetPromptCompPt] Basic information" << endl;
    cout << "[FakeValidation::GetPromptCompPt] id = " << id << endl;
    cout << "[FakeValidation::GetPromptCompPt] syst = " << syst << endl;
    cout << "[FakeValidation::GetPromptCompPt] prompt = " << prompt << endl;	

	//==== recommended to put syst as "Central" to see the overall normalization variation ====
	vector<TH1D*> h_syst = GetPromptNormPt(id, syst, prompt);
	vector<TH1D*> h_central = GetPromptNormPt(id, syst, "Central");

	for (unsigned int i =0; i < h_syst.size(); i++) {
		h_syst.at(i)->Add(h_central.at(i), -1);
		h_syst.at(i)->Divide(h_central.at(i));
	}

	return h_syst;
}

TH2D* FakeValidation::GetFakeRateWithErr(TString idset) {
	vector<TString> Systs = navi.GetSysts();
	int nbinx = 3; int nbiny = 3;

	TH2D* h_cent = GetFakeRatePtEta(idset, Systs.at(0), "Central", 1.);
	vector<TH2D*> h_comps;
	for (unsigned int i = 0; i < Systs.size(); i++) {
		TH2D* temp = GetFakeCompPtEta(idset, Systs.at(i), "Central", 1.);
		h_comps.push_back(temp);
	}
	TH2D* h_promptUp = GetFakeCompPtEta(idset, Systs.at(0), "Central", 1.15);
	TH2D* h_promptDown = GetFakeCompPtEta(idset, Systs.at(0), "Central", 0.85);
	h_comps.push_back(h_promptUp); h_comps.push_back(h_promptDown);

	// for every bin:
	for (int i = 0; i < nbinx; i++) {
		for (int j = 0; j < nbiny; j++) {
			// (i+1, j+1)-bin
			double total = 0;
			double stat = h_central->GetBinError(i+1, j+1); total += stat * stat;
			for (unsigned int k = 1; k < h_comps.size(); k++) {
				double syst = h_comps.at(k)->GetBinContent(i+1, j+1);
				total += syst * syst; 
			}
			total = TMath::Sqrt(total);
			h_cent->SetBinError(i+1, j+1, total);
		}
	}
	h_cent->Draw();
	return h_cent;
}
			
	
vector<TH1D*> FakeValidation::GetFakeCompPtWithErr(TString idset) {
	vector<TString> Systs = navi.GetSysts();
	int nbin = 3;

	vector<TH1D*> h_central = GetFakeCompPt(idset, Systs.at(0), "Central", 1.);
	h_central.at(0)->Draw();
	vector< vector<TH1D*> > h_comps;
	for (unsigned int i = 0; i < Systs.size(); i++) {
		vector<TH1D*> temp = GetFakeCompPt(idset, Systs.at(i), "Central", 1.);
		h_comps.push_back(temp);
	}
	vector<TH1D*> h_promptUp = GetFakeCompPt(idset, Systs.at(0), "Central", 1.15);
	vector<TH1D*> h_promptDown = GetFakeCompPt(idset, Systs.at(0), "Central", 0.85);
	h_comps.push_back(h_promptUp); h_comps.push_back(h_promptDown);

	for (unsigned int i = 0; i < 4; i++) {
		// for every bin:
		for (int j = 0; j < nbin; j++) {
			double totalerr = 0;
			for (unsigned int k = 1; k < h_comps.size(); k++) {
				double syst = h_comps.at(i).at(j)->GetBinContent(j+1);
				totalerr += syst * syst;
			}
			totalerr = TMath::Sqrt(totalerr);
			h_central.at(i)->SetBinError(j+1, totalerr);
		}
	}
	//h_central.at(0)->Draw();
	return h_central;
}

