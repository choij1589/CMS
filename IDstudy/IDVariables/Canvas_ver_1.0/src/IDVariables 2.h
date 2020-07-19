#ifndef IDVariables_H__
#define IDVariables_H__

#include "FileNavi.h"

class IDVariables {
private:
	FileNavi navi;

public:
	//==== Constructors ====
	IDVariables();
	IDVariables(const TString &path_data, const TString &path_mc, const vector<TString> &samples, const vector<TString> &muonIDs);

	//==== Destructor ====
	~IDVariables();

	//==== Member functions ====
	double GetScale(const TString &path);
	TH1* GetHist(const TString &sample, const TString &path);
};

#endif

