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
TH1* FakeValidation::GetHist(TString sample, TString histname) const {
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

double FakeValidation::GetPromptScale(TString id, TString syst, TString prompt) const {

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

TH2D* FakeValidation::GetFakeRatePtEta(TString idset, TString syst, TString prompt, double promptScale) const {
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
		= (TH2D*)GetHist(Samples.at(0), "passID_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
	TH2D* hFakeLooseMC
		= (TH2D*)GetHist(Samples.at(1), "passID_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
	double scaleLoose = GetPromptScale(id_loose, syst, prompt);
	cout << "[FakeValidation::GetFakeRatePtEta] " << syst << " scaleLoose = " << scaleLoose << endl;
	
	TH2D* hFakeTightData
        = (TH2D*)GetHist(Samples.at(0), "passID_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
    TH2D* hFakeTightMC
        = (TH2D*)GetHist(Samples.at(1), "passID_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
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

vector<TH1D*> FakeValidation::GetFakeRatePt(TString idset, TString syst, TString prompt, Double_t promptScale) const {
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
        = (TH2D*)GetHist(Samples.at(0), "passID_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
    TH2D* hFakeLooseMC
        = (TH2D*)GetHist(Samples.at(1), "passID_" + Regions.at(0) + "_" + id_loose + "_" + syst + "_" + prompt);
	
	double scaleLoose = GetPromptScale(id_loose, syst, prompt);
    cout << "[FakeValidation::GetFakeRatePt] " << syst << " scaleLoose = " << scaleLoose << endl;

    TH2D* hFakeTightData
        = (TH2D*)GetHist(Samples.at(0), "passID_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
    TH2D* hFakeTightMC
        = (TH2D*)GetHist(Samples.at(1), "passID_" + Regions.at(0) + "_" + id_tight + "_" + syst + "_" + prompt);
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

TH2D* FakeValidation::GetFakeCompPtEta(TString idset, TString syst, TString prompt, double promptScale) const {

	cout << "[FakeValidation::GetFakeCompPtEta] Basic information" << endl;
	cout << "[FakeValidation::GetFakeCompPtEta] idset = " << idset << endl;
	cout << "[FakeValidation::GetFakeCompPtEta] syst = " << syst << endl;
	cout << "[FakeValidation::GetFakeCompPtEta] prompt = " << prompt << endl;
	cout << "[FakeValidation::GetFakeCompPtEta] promptScale = " << promptScale << endl;

	int prom;
	if (promptScale == 1) prom = 0;
	else if (promptScale > 1) prom = +1;
	else if (promptScale < 1) prom = -1;
	TH2D* h_central = GetFakeRatePtEta(idset, "Central", prompt , 1.);
	TH2D* h_syst = GetFakeRatePtEta(idset, syst, prompt, promptScale);
	TH2D* h_comp = (TH2D*) h_syst->Clone("_comp_" + idset + "_" + syst + "_" + prompt + TString::Itoa(prom, 10));
	h_comp->Add(h_central, -1);
	h_comp->Divide(h_central);

	return h_comp;
}


vector<TH1D*> FakeValidation::GetFakeCompPt(TString idset, TString syst, TString prompt, double promptScale) const{

	cout << "[FakeValidation::GetFakeCompPt] Basic information" << endl;
	cout << "[FakeValidation::GetFakeCompPt] idset = " << idset << endl;
	cout << "[FakeValidation::GetFakeCompPt] syst = " << syst << endl;
	cout << "[FakeValidation::GetFakeCompPt] prompt = " << prompt << endl;
	cout << "[FakeValidation::GetFakeCompPt] promptScale = " << promptScale << endl;

	vector<TH1D*> h_central = GetFakeRatePt(idset, "Central", prompt, 1.);
	vector<TH1D*> h_syst;
	vector<TH1D*> h_temp;
	if (syst.Contains("Central")) {
		for (unsigned int i = 0; i < h_central.size(); i++) {
			TH1D* temp = (TH1D*)h_central.at(i)->Clone("_clone" + TString::Itoa(i, 10));
			h_syst.push_back(temp);
		}
	}
	else {
		h_syst = GetFakeCompPt(idset, syst, prompt, promptScale);
	}
	
	h_temp = h_syst;
	for (unsigned int i = 0; i < h_syst.size(); i++) {
		h_temp.at(i)->Add(h_central.at(i), -1);
		h_temp.at(i)->Divide(h_central.at(i));
	}

	return h_temp;
}



TH2D* FakeValidation::GetPromptNormPtEta(TString id, TString syst, TString prompt) const {
	//==== Check information ====
	TString data = "DoubleEG";
	TString mc = "MC";
	
	TH2D* h_data = (TH2D*) GetHist(data, "passID_WEnriched_" + id + "_" + syst + "_" + prompt);
	TH2D* h_mc = (TH2D*) GetHist(mc, "passID_WEnriched_" + id + "_" + syst + "_" + prompt);

	TH2D* h = (TH2D*)h_data->Clone("PromptNorm_" + id + "_" + syst + "_" + prompt);
	h->Divide(h_mc);
	
	return h;
}

vector<TH1D*> FakeValidation::GetPromptNormPt(TString id, TString syst, TString prompt) const {
	TString data = "DoubleEG";
	TString mc = "MC";

	TH2D* h_data = (TH2D*) GetHist(data, "passID_WEnriched_" + id + "_" + syst + "_" + prompt);
	TH2D* h_mc = (TH2D*) GetHist(mc, "passID_WEnriched_" + id + "_" + syst + "_" + prompt);

	TH1D* h_total = h_data->ProjectionX("_px_" + syst + "_" + prompt); h_total->Divide(h_mc->ProjectionX("_px_mc_" + syst + "_" + prompt));
	TH1D* h_bin1 = h_data->ProjectionX("_px1_"+ syst + "_" + prompt, 1, 1); h_bin1->Divide(h_mc->ProjectionX("_px1_mc_" + syst + "_" + prompt, 1, 1));
	TH1D* h_bin2 = h_data->ProjectionX("_px2_"+ syst + "_" + prompt, 2, 2); h_bin2->Divide(h_mc->ProjectionX("_px2_mc_" + syst + "_" + prompt, 2, 2));
	TH1D* h_bin3 = h_data->ProjectionX("_px3_"+ syst + "_" + prompt, 3, 3); h_bin3->Divide(h_mc->ProjectionX("_px3_mc_" + syst + "_" + prompt, 3, 3));


	vector<TH1D*> temp;
	temp.push_back(h_total); temp.push_back(h_bin1); temp.push_back(h_bin2); temp.push_back(h_bin3);
	
	return temp;
}

TH2D* FakeValidation::GetPromptCompPtEta(TString id, TString syst, TString prompt) const {
	cout << "[FakeValidation::GetPromptCompPtEta] Basic information" << endl;
	cout << "[FakeValidation::GetPromptCompPtEta] id = " << id << endl;
	cout << "[FakeValidation::GetPromptCompPtEta] syst = " << syst << endl;
	cout << "[FakeValidation::GetPromptCompPtEta] prompt = " << prompt << endl;

	//==== recommended to put syst as "Central" to see the overall normalization variation ====
	TH2D* h_syst = GetPromptNormPtEta(id, syst, prompt);
	TH2D* h_central = GetPromptNormPtEta(id, syst, "Central");
	TH2D* h_temp = (TH2D*)h_syst->Clone("PromptCompPtEta_" + id + "_" + syst + "_" + prompt);
	h_temp->Add(h_central, -1);
	h_temp->Divide(h_central);

	return h_temp;
}

vector<TH1D*> FakeValidation::GetPromptCompPt(TString id, TString syst, TString prompt) const {
	cout << "[FakeValidation::GetPromptCompPt] Basic information" << endl;
    cout << "[FakeValidation::GetPromptCompPt] id = " << id << endl;
    cout << "[FakeValidation::GetPromptCompPt] syst = " << syst << endl;
    cout << "[FakeValidation::GetPromptCompPt] prompt = " << prompt << endl;	

	//==== recommended to put syst as "Central" to see the overall normalization variation ====
	vector<TH1D*> h_syst = GetPromptNormPt(id, syst, prompt);
	vector<TH1D*> h_central = GetPromptNormPt(id, syst, "Central");
	vector<TH1D*> h_temp;
	TH1D* temp = NULL;

	for (unsigned int i =0; i < h_syst.size(); i++) {
		temp = (TH1D*)h_syst.at(i)->Clone("PromptCompPt_" + id + "_" + syst + "_" + prompt + "_" + TString::Itoa(i, 10));
		temp->Add(h_central.at(i), -1);
		temp->Divide(h_central.at(i));
		h_temp.push_back(temp);
	}

	return h_temp;
}

			
TH2D* FakeValidation::GetFakeRateWithErr(TString idset) const {
	vector<TString> Systs = navi.GetSysts();
	int nbinx=6; //pt-bin
	int nbiny=3; //eta-bin

	TH2D* h = GetFakeRatePtEta(idset, Systs.at(0), "Central", 1.);
	vector<TH2D*> h_systs;
	for (unsigned int i = 1; i < Systs.size(); i++) {
		TH2D* temp = GetFakeRatePtEta(idset, Systs.at(i), "Central", 1.);
		h_systs.push_back(temp);
	}
	TH2D* h_up = GetFakeRatePtEta(idset, Systs.at(0), "Central", 1.15);
	TH2D* h_down = GetFakeRatePtEta(idset, Systs.at(0), "Central", 0.85);
	h_systs.push_back(h_up); h_systs.push_back(h_down);

	// for every bin;
	for (int i = 0; i < nbinx; i++) {
		for (int j = 0; j < nbiny; j++) {
			double totalerr = 0;
			double stat = h->GetBinError(i+1, j+1);
			stat /= h->GetBinContent(i+1, j+1);
			totalerr += stat*stat;
			for (unsigned int k = 0; k < h_systs.size(); k++) {
				double syst = h_systs.at(k)->GetBinContent(i+1, j+1) - h->GetBinContent(i+1, j+1);
				syst /= h->GetBinContent(i+1, j+1);
				totalerr += syst*syst;
			}
			totalerr = TMath::Sqrt(totalerr);
			totalerr *= h->GetBinContent(i+1, j+1);
			h->SetBinError(i+1, j+1, totalerr);
		}
	}
	return h;
}

vector<TH1D*> FakeValidation::GetFakeRatePtWithErr(TString idset) const {
	vector<TString> Systs = navi.GetSysts();
	int nbin = 6;

	vector<TH1D*> h = GetFakeRatePt(idset, Systs.at(0), "Central", 1.);
	vector< vector<TH1D*> > h_systs;
	for (unsigned int i = 1; i < Systs.size(); i++) {
		vector<TH1D*> temp = GetFakeRatePt(idset, Systs.at(i), "Central", 1.);
		h_systs.push_back(temp);
	}
	vector<TH1D*> h_up = GetFakeRatePt(idset, Systs.at(0), "Central", 1.15);
	vector<TH1D*> h_down = GetFakeRatePt(idset, Systs.at(0), "Central", 0.85);
	h_systs.push_back(h_up); h_systs.push_back(h_down);
	
	for (unsigned int i = 0; i < 4; i++) {
		// for every bin;
		for (int j = 0; j < nbin; j++) {
			double totalerr = 0;
			double stat = h.at(i)->GetBinError(j+1);
			stat /= h.at(i)->GetBinContent(j+1);
			totalerr += stat*stat;
			for (unsigned int k = 0; k < h_systs.size(); k++) {
				double syst = h_systs.at(k).at(i)->GetBinContent(j+1) - h.at(i)->GetBinContent(j+1);
				syst /= h.at(i)->GetBinContent(j+1);
				totalerr += syst*syst;
			}
			totalerr = TMath::Sqrt(totalerr);
			totalerr *= h.at(i)->GetBinContent(j+1);
			h.at(i)->SetBinError(j+1, totalerr);
		}
	}
	return h;
}


