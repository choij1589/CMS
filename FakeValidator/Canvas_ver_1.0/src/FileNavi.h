#ifndef FileNavi_H_
#define FileNavi_H_

using namespace std;

class FileNavi {

private:
	TString pathData, pathMC;
	vector<TString> Samples;
	vector<TString> IDSets;

public:
	// Constructor
	FileNavi() {
		cout << "2020.06.10 FakeValidator ver.0.1" << endl;
		cout << "[FileNavi] Constructor called" << endl;
	}

	// Destructor
	~FileNavi() {
		cout << "[FileNavi] Destructor called" << endl;
	}

	// Set Functions
	void SetPathData(const TString &path);
	void SetPathMC(const TString &path);
	void SetSamples(const vector<TString> &samples);
	void SetIDSets(const vector<TString> &idsets);

	// Get Functions
	TString GetPathData() const;
	TString GetPathMC() const;
	vector<TString> GetSamples() const;
	vector<TString> GetIDSets() const;

	// public functions
	TDirectory* GetDirectory(TString sample, TString direcName) const;
	TDirectory* GetDirectory(TString sample, TString idset, bool isFake, int sys);

};

#endif
