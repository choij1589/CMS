#ifndef FileNavi_H__
#define FileNavi_H__

// entity class for PromptSelector
class FileNavi {
private:
	TString path_data_, path_mc_;
	vector<TString> samples_;

public:
	// constructor
	FileNavi();
	FileNavi(const TString& path_data, const TString& path_mc, const vector<TString>& samples);

	// destructor
	~FileNavi();

	// get and set
	TString path_data() const;
	TString path_mc() const;
	vector<TString> samples() const;

	void set_path_data(const TString& path);
	void set_path_mc(const TString& path);
	void set_samples(const vector<TString>& samples);

	// navigation
	TDirectory* getDirectory(const TString& sample, const TString& path);
	TH1* getHist(const TString& sample, const TString& path);
};

#endif
