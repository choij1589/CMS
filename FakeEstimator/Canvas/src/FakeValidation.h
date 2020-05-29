#ifndef FileValidation_H__
#define FileValidation_H__

#include "FileNavi.h"

class FakeValidation {

private:
    TString pathData;
    TString pathMC;

    vector<TString> Samples;
    vector<TString> IDs;
    vector<TString> Systs;
    vector<TString> Prompts;
    vector<TString> Regions;

    FileNavi navi;

public:
    FakeValidation(const TString &path_data, const TString &path_mc):pathData(path_data), pathMC(path_mc) {
        cout << "[FakeValidation] Constructor called" << endl;
        navi.SetPathData(path_data);
        navi.SetPathMC(path_mc);
    }
    ~FakeValidation() {}

    void Init(
        const vector<TString> &samples, const vector<TString> &ids, const vector<TString> systs, const vector<TString> prompts,
        const vector<TString> &regions) {

        Samples = samples; navi.SetSamples(samples);
        IDs = ids; navi.SetIDs(ids);
        Systs = systs; navi.SetSysts(systs);
        Prompts = prompts; navi.SetPrompts(prompts);
        Regions = regions; navi.SetRegions(regions);

	navi.LoadFakeDirectory();
    }

    //==== Other Functions ====
    TH2D* GetFakeRate(TString syst, double scale);
	TH1D* GetFakeRatePt(TString syst, double scale);

	TCanvas* DrawFake1D(TString syst, int scale);
};

#endif

