#ifndef FakeValidation_H__
#define FakeValidation_H__

#include "FileNavi.h"

class FakeValidation {

private:
	FileNavi navi;

public:
	FakeValidation() {}
	~FakeValidation() {}

	void Init(const TString &pathdata, const TString &pathmc, const vector<TString> &samples, const vector<TString> idsets);

	//==== public functions ====
	TH1D* GetHist(const TString &idset, const TString &sample, TString histname)  const;
	TH1D* GetFakeHist(const TString &idset, TString histname, const int sys) const;

	vector<TH1D*> GetSampleHists(const TString &idset, TString histname) const;
	vector<TH1D*> GetFakeHists(const TString &idset, TString histname) const;
	double GetScale(const TString &idset);
};

#endif
