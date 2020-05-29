#include <iostream>
#include <vector>
#include <map>
using namespace std;

class FileNavi {

private:
    TString pathData, pathMC;

    //==== information for fake rate measurement with systematics
    vector<TString> IDs;
    vector<TString> Systs;
    vector<TString> Prompts;
    vector<TString> Regions;
    vector<TString> Samples;

    //==== map for tree structure
    //==== MapFakeDirectory[sample][id][syst][prompt][region]
    map<TString,
        map<TString,
            map<TString,
                map<TString,
                    map<TString, TDirectory*>>>>> MapFakeDirectory;


public:
    //==== you can make different constructor for each analysis
    //==== constructor and destructor for the fake rate measurement
    FileNavi(const TString &path_data, const TString &path_mc)
			:pathData(path_data), pathMC(path_mc)
	{
        cout << "FileNavi Constructor called" << endl;
    }
    ~FileNavi(){
        cout << "Destructor called" << endl;
    }
	//==== Set Functions ====
	void SetPathData(const TString &path);
	void SetPathMC(const TString &path);
	void SetSamples(const vector<TString> &samples);
	void SetIDs(const vector<TString> &ids);
	void SetSysts(const vector<TString> &systs);
	void SetPrompts(const vector<TString> &prompts);
	void SetRegions(const vector<TString> &regions);
	
	//==== Get Functions ====
	TString GetPathData() const;
	TString GetPathMC() const;
	vector<TString> GetSamples() const;
	vector<TString> GetIDs() const;
	vector<TString> GetSysts() const;
	vector<TString> GetPrompts() const;
	vector<TString> GetRegions() const;

	//==== Load Directoreis ====
	void LoadFakeDirectory();
	TDirectory* GetFakeDirectory(
		TString sample, TString id, TString syst, TString prompt, TString region);
	TH1* GetHistFromFakeDirectory(TDirectory* dir, TString histname);
};

//==== set functions ====
void FileNavi::SetPathData(const TString &path) {
	pathData = path;
	cout << "[FileNavi::SetPathData] pathData = " << pathData << endl;
}
void FileNavi::SetPathMC(const TString &path) {
	pathMC = path;
	cout << "[FileNavi::SetPathMC] pathMC = " << pathMC << endl;
}
void FileNavi::SetSamples(const vector<TString> &samples) {
	Samples = samples;
	cout << "[FileNavi::SetSamples] Samples = {" << endl;
	for (unsigned int i = 0; i < Samples.size(); i++) {
		cout << Samples.at(i) << endl;
	}
	cout << "}" << endl;
}
void FileNavi::SetIDs(const vector<TString> &ids) {
	IDs = ids;
	cout << "[FileNavi::SetIDs] IDs = {" << endl;
	for (unsigned int i = 0; i < IDs.size(); i++) {
		cout << IDs.at(i) << endl;
	}
	cout << "}" << endl;
}
void FileNavi::SetSysts(const vector<TString> &systs) {
	Systs = systs;
	cout << "[FileNavi::SetSysts] Systs = {" << endl;
	for (unsigned int i = 0; i < Systs.size(); i++) {
		cout << Systs.at(i) << endl;
	}
	cout << "}" << endl;
}
void FileNavi::SetPrompts(const vector<TString> &prompts) {
	Prompts = prompts;
	cout << "[FileNavi::SetPrompts] Prompts = {" << endl;
	for (unsigned int i = 0; i < Prompts.size(); i++) {
		cout << Prompts.at(i) << endl;
	}
	cout << "}" << endl;
}
void FileNavi::SetRegions(const vector<TString> &regions) {
	Regions = regions;
	cout << "[FileNavi::SetRegions] Regions = {" << endl;
	for (unsigned int i = 0; i < Regions.size(); i++) {
		cout << Regions.at(i) << endl;
	}
	cout << "}" << endl;
}
//==== get functions ====
TString FileNavi::GetPathData() const {
	return pathData;
}
TString FileNavi::GetPathMC() const {
	return pathMC;
}
vector<TString> FileNavi::GetSamples() const {
	return Samples;
}
vector<TString> FileNavi::GetIDs() const {
	return IDs;
}
vector<TString> FileNavi::GetSysts() const {
	return Systs;
}
vector<TString> FileNavi::GetPrompts() const {
	return Prompts;
}
vector<TString> FileNavi::GetRegions() const {
	return Regions;
}

//==== other functions ====
void FileNavi::LoadFakeDirectory() {
	vector<TFile*> TFiles; // 0 for data, 1 for mc, 2~ for subsamples
    TFile* f_data = new TFile(pathData + "FakeEstimator_DoubleEG.root");
	TFiles.push_back(f_data);

	//==== Samples contain the information of the data also
	for (unsigned int i = 1; i < Samples.size(); i++) {
		TFile* f_mc = new TFile(pathMC + "FakeEstimator_" + Samples.at(i) + ".root");
		TFiles.push_back(f_mc);
	}

	//==== map
	for (unsigned int i = 0; i < Samples.size(); i++) { TString sample = Samples.at(i);
	for (unsigned int j = 0; j < IDs.size(); j++) { TString id = IDs.at(j);
	for (unsigned int k = 0; k < Systs.size(); k++) { TString syst = Systs.at(k);
	for (unsigned int l = 0; l < Prompts.size(); l++) { TString prompt = Prompts.at(l);
	for (unsigned int m = 0; m < Regions.size(); m++) { TString region = Regions.at(m);
		TFile* f = TFiles.at(i);
		auto* dirID = (TDirectory*)f->Get(id);
		auto* dirSyst = (TDirectory*)dirID->Get(syst);
		auto* dirPrompt = (TDirectory*)dirSyst->Get(prompt);
		auto* dirRegion = (TDirectory*)dirPrompt->Get(region);
		MapFakeDirectory[sample][id][syst][prompt][region] = dirRegion;
	}}}}}
}
TDirectory* FileNavi::GetFakeDirectory(
	TString sample, TString id, TString syst, TString prompt, TString region) {

	TDirectory* dir = MapFakeDirectory[sample][id][syst][prompt][region];
	if (dir == NULL) {
		cout << "[FileNavi::GetFakeDirectory] Null directory" << endl;
	}
	return dir;
}
TH1* FileNavi::GetHistFromFakeDirectory(TDirectory* dir, TString histname) {
	// you should use dynamic_cast<TH1D*>(temp) or dynamic_cast<TH2D*>(temp) to use it prperly
	TH1* temp;
	temp = (TH1*)dir->Get(histname);
	return temp;
}


































