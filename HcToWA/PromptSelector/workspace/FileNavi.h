#ifndef FileNavi_H__
#define FileNavi_H__

// entity class for PromptSelector
class FileNavi {
private:
	TString pathData, pathMC;
	vector<TString> Samples;

public:
	// constructor
	FileNavi();
	FileNavi(const TString& path_data, const TString& path_mc, const vector<TString>& samples);

	// destructor
	~FileNavi();

	// get and set
	TString GetPathData() const;
	TString GetPathMC() const;
	vector<TString> GetSamples() const;

	void SetPathData(const TString& path);
	void SetPathMC(const TString& path);
	void SetSamples(const vector<TString>& samples);

	// navigation
	TDirectory* GetDirectory(const TString& sample, const TString& path);
	TH1* GetHist(const TString& sample, const TString& path);
};

#endif
