#ifndef FileNavi_H_
#define FileNavi_H_

using namespace std;

class FileNavi {

private:
	TString pathData, pathMC;
	vector<TString> Samples;
	vector<TString> MuonIDs;

public:
	//==== Construction ====
	FileNavi();
	FileNavi(const TString &p_data, const TString &p_MC, const vector<TString> samples, const vector<TString> &muonIDs);
	//==== Desturctor ====
	~FileNavi();

	//==== Member functions ====
	void SetPathData(const TString &path);
	void SetPathMC(const TString &path);
	void SetSamples(const vector<TString> &samples);
	void SetMuonIDs(const vector<TString> &ids);

	TString GetPathData() const;
	TString GetPathMC() const;
	vector<TString> GetSamples() const;
	vector<TString> GetMuonIDs() const;

	TDirectory* GetDirectory(const TString &sample, const TString &muonID, const TString &region, const TString &obj) const;
};

#endif
