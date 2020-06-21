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
	TH1* GetHist(TString sample, TString histname) const;
	double GetPromptScale(TString id, TString syst, TString prompt) const;
    TH2D* GetFakeRatePtEta(TString idset, TString syst, TString prompt, double promptScale) const;
	vector<TH1D*> GetFakeRatePt(TString idset, TString syst, TString prompt, double promptScale) const;

	TH2D* GetFakeCompPtEta(TString idset, TString syst, TString prompt, double promptScale) const;
	vector<TH1D*> GetFakeCompPt(TString idset, TString syst, TString prompt, double promptScale) const;

	TH2D* GetPromptNormPtEta(TString id, TString syst, TString prompt) const;
	vector<TH1D*> GetPromptNormPt(TString id, TString syst, TString prompt) const;

	TH2D* GetPromptCompPtEta(TString id, TString syst, TString prompt) const;
	vector<TH1D*> GetPromptCompPt(TString id, TString syst, TString prompt) const;

	TH2D* GetFakeRateWithErr(TString idset) const; //need update
	vector<TH1D*> GetFakeRatePtWithErr(TString idset) const;

	TH2D* GetFakeCompWithErr(TString idset) const; //need update
	vector<TH1D*> GetFakeCompPtWithErr(TString idset) const; //need update

	TH2D* GetPromptRate(TString idset, bool IsDATA);
};

#endif

