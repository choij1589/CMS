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

    //==== Other Functions ====
	TH1* GetHist(TString sample, TString histname);
    TH2D* GetFakeRatePtEta(TString idset, TString syst, TString prompt, double promptScale);
	vector<TH1D*> GetFakeRatePt(TString idset, TString syst, TString prompt, double promptScale);

	TH2D* GetPromptNormPtEta(TString id, TString syst, TString prompt);
	TH1D* GetPromptNormPt(TString id, TString syst, TString prompt);
	TH1D* GetPromptNormEta(TString id, TString syst, TString prompt);
};

#endif

