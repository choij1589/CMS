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
	TH2D* hPromptLooseData
		= (TH2D*)GetHist(Samples.at(0), "PromptEvents_" + Regions.at(1) + "_" + id_loose + "_" + syst + "_" + prompt);
	TH2D* hPromptLooseMC
		= (TH2D*)GetHist(Samples.at(1), "PromptEvents_" + Regions.at(1) + "_" + id_loose + "_" + syst + "_" + prompt);
	Double_t scaleLoose = hPromptLooseData->Integral() / hPromptLooseMC->Integral();
	cout << "[FakeValidation::GetFakeRatePtEta] " << syst << " scaleLoose = " << scaleLoose << endl;
	
	TH2D* hFakeTightData
        = (TH2D*)GetHist(Samples.at(0), "passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
    TH2D* hFakeTightMC
        = (TH2D*)GetHist(Samples.at(1), "passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
    TH2D* hPromptTightData
        = (TH2D*)GetHist(Samples.at(0), "PromptEvents_" + Regions.at(1) + "_" + id_tight + "_" + syst + "_" + prompt);
    TH2D* hPromptTightMC
        = (TH2D*)GetHist(Samples.at(1), "PromptEvents_" + Regions.at(1) + "_" + id_tight + "_" + syst + "_" + prompt);
    Double_t scaleTight = hPromptTightData->Integral() / hPromptTightMC->Integral();
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

vector<TH1D*> FakeValidation::GetFakeRatePt(TString idset, TString syst, TString prompt, Double_t promptScale) {
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
    TH2D* hPromptLooseData
        = (TH2D*)GetHist(Samples.at(0), "PromptEvents_" + Regions.at(1) + "_" + id_loose + "_" + syst + "_" + prompt);
    TH2D* hPromptLooseMC
        = (TH2D*)GetHist(Samples.at(1), "PromptEvents_" + Regions.at(1) + "_" + id_loose + "_" + syst + "_" + prompt);
    Double_t scaleLoose = hPromptLooseData->Integral() / hPromptLooseMC->Integral();
    cout << "[FakeValidation::GetFakeRatePt] " << syst << " scaleLoose = " << scaleLoose << endl;

    TH2D* hFakeTightData
        = (TH2D*)GetHist(Samples.at(0), "passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
    TH2D* hFakeTightMC
        = (TH2D*)GetHist(Samples.at(1), "passID3bins_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
    TH2D* hPromptTightData
        = (TH2D*)GetHist(Samples.at(0), "PromptEvents_" + Regions.at(1) + "_" + id_tight + "_" + syst + "_" + prompt);
    TH2D* hPromptTightMC
        = (TH2D*)GetHist(Samples.at(1), "PromptEvents_" + Regions.at(1) + "_" + id_tight + "_" + syst + "_" + prompt);
    Double_t scaleTight = hPromptTightData->Integral() / hPromptTightMC->Integral();
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

TH1D* FakeValidation::GetPromptNormPt(TString id, TString syst, TString prompt) {
	TString data = "DoubleEG";
	TString mc = "MC";

	TH2D* h_data = (TH2D*) GetHist(data, "passID3bins_WEnriched_" + id + "_" + syst + "_" + prompt);
	TH2D* h_mc = (TH2D*) GetHist(mc, "passID3bins_WEnriched_" + id + "_" + syst + "_" + prompt);

	TH1D* h_data_pt = h_data->ProjectionX("_px_data");
	TH1D* h_mc_pt = h_mc->ProjectionX("_px_mc");

	TH1D* h = (TH1D*)h_data_pt->Clone("");
	h->Divide(h_mc_pt);
	return h;
}

TH1D* FakeValidation::GetPromptNormEta(TString id, TString syst, TString prompt) {
    TString data = "DoubleEG";
    TString mc = "MC";

    TH2D* h_data = (TH2D*) GetHist(data, "passID3bins_WEnriched_" + id + "_" + syst + "_" + prompt);
    TH2D* h_mc = (TH2D*) GetHist(mc, "passID3bins_WEnriched_" + id + "_" + syst + "_" + prompt);

    TH1D* h_data_eta = h_data->ProjectionY("_py_data");
    TH1D* h_mc_eta = h_mc->ProjectionY("_py_mc");

    TH1D* h = (TH1D*)h_data_eta->Clone("");
    h->Divide(h_mc_eta);
    return h;
}















