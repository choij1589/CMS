#ifndef ConvEstimation_H__
#define ConvEstimation_H__

#include "FileNavi.h"

class ConvEstimation {

private:
	FileNavi navi;

public:
	ConvEstimation() {}
	~ConvEstimation() {}

	void Init(const TString &path_data, const TString &path_mc, const vector<TString> &samples, const vector<TString> &idsets);

	//==== public functions ====
	vector<TDirectory*> GetSampleDirectories(const TString &idset) const;
	vector<TDirectory*> GetFakeDirectories(const TString &idset) const;

	TH1D* GetHist(const TString &idset, const TString &sample, TString histname) const;
	TH1D* GetFakeHist(const TString &idset, TString histname, const int &sys) const;

	vector<TH1D*> GetSampleHists(const TString &idset, TString histname) const;
	vector<TH1D*> GetFakeHists(const TString &idset, TString histname) const;	
	double GetScale(const TString &idset, int sys) const;
};

#endif
