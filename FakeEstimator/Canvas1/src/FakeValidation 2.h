#ifndef FileValidation_H__
#define FileValidation_H__

#include "FileNavi.h"

class FakeValidation {

private:
    FileNavi navi;
	vector<TString> IDSets;
	
public:
	FakeValidation() {}
    ~FakeValidation() {}

    void Init(
        const TString &path_data, const TString &path_mc,
		const vector<TString> &samples, const vector<TString> &ids, const vector<TString> systs,
		const vector<TString> &prompts, const vector<TString> &regions,
		const vector<TString> &idsets);

    //==== Member Functions ====
	TH1* GetHist(TString sample, TString histname);
	double GetPromptScale(TString id, TString syst, TString prompt);
    TH2D* GetFakeRatePtEta(TString idset, TString syst, TString prompt, double promptScale);
	vector<TH1D*> GetFakeRatePt(TString idset, TString syst, TString prompt, double promptScale);

	TH2D* GetFakeCompPtEta(TString idset, TString syst, TString prompt, double promptScale);
	vector<TH1D*> GetFakeCompPt(TString idset, TString syst, TString prompt, double promptScale);

	TH2D* GetPromptNormPtEta(TString id, TString syst, TString prompt);
	vector<TH1D*> GetPromptNormPt(TString id, TString syst, TString prompt);

	TH2D* GetPromptCompPtEta(TString id, TString syst, TString prompt);
	vector<TH1D*> GetPromptCompPt(TString id, TString syst, TString prompt);

	TH2D* GetFakeRateWithErr(TString idset); //need update
	vector<TH1D*> GetFakeRatePtWithErr(TString idset);

	TH2D* GetFakeCompWithErr(TString idset); //need update
	vector<TH1D*> GetFakeCompPtWithErr(TString idset);
};

#endif

