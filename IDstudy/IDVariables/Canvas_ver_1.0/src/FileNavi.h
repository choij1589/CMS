#ifndef FileNavi_H_
#define FileNavi_H_

//==== Class Description ====
//==== class FileNavi is made for entity class ====
//==== to navigate through the files of 

class FileNavi {

private:
	TString pathData, pathMC;
	vector<TString> Samples; // 0 for data, 1 for DYJets, 2 for TTLL_powheg
	vector<TString> MuonIDs;

public:
	//==== Constructor ====
	FileNavi();
	FileNavi(const TString &path_data, const TString &path_mc, const vector<TString> &samples, const vector<TString> &muonIDs);

	//==== Destructor ====
	~FileNavi();

	//==== Member Functions ====
	//==== 1) Get and Set ====
	TString GetPathData() const;
	TString GetPathMC() const;
	vector<TString> GetSamples() const;
	vector<TString> GetMuonIDs() const;

	void SetPathData(const TString &path);
	void SetPathMC(const TString &path);
	void SetSamples(const vector<TString> &samples);
	void SetMuonIDs(const vector<TString> &muonIDs);

	//==== 2) Other member functions ====
	TDirectory* GetDirectory(const TString &sample, const TString &path);
	TH1* GetHist(const TString &sample, const TString &path);
};

#endif
