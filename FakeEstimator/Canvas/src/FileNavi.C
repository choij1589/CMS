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
    FileNavi(const vector<TString> &samples, const vector<TString> &ids,
			const vector<TString> &systs, const vector<TString> &prompts,const vector<TString> &regions)
			:IDs(ids), Systs(systs), Prompts(prompts), Regions(regions), Samples(samples)
	{
        cout << "FileNavi Constructor called" << endl;
    }
    ~FileNavi(){
        cout << "Destructor called" << endl;
    }
    //==== Set Functions
    void SetPathData(const TString &path) {
        pathData = path;
    }
    void SetPathMC(const TString &path) {
        pathMC = path;
    }
    void SetIDs(const vector<TString> &ids) {
        IDs = ids;
    }
    void SetSysts(const vector<TString> &systs) {
        Systs = systs;
    }
    void SetPrompts(const vector<TString> &prompts) {
        Prompts = prompts;
    }
    void SetRegions(const vector<TString> &regions) {
        Regions = regions;
    }
    void SetSamples(const vector<TString> &samples) {
        Samples = samples;
    }

    //==== Get Functions
    void GetIDs() const {
        cout << "IDs = {" << endl;
        for (unsigned int i = 0; i < IDs.size(); i++) {
            cout << IDs.at(i) << endl;
        }
        cout << "}" << endl;
    }
    void GetSysts() const {
        cout << "Systs = {" << endl;
        for (unsigned int i = 0; i < Systs.size(); i++) {
            cout << Systs.at(i) << endl;
        }
        cout << "}" << endl;
    }
    void GetPrompts() const {
        cout << "Prompts = {" << endl;
        for (unsigned int i = 0; i < Prompts.size(); i++) {
            cout << Prompts.at(i) << endl;
        }
        cout << "}" << endl;
    }
    void GetRegions() const {
        cout << "Regions = {" << endl;
        for (unsigned int i = 0; i < Regions.size(); i++) {
            cout << Regions.at(i) << endl;
        }
        cout << "}" << endl;
    }
    void GetSamples() const {
        cout << "Samples = {" << endl;
        for (unsigned int i = 0; i < Samples.size(); i++) {
            cout << Samples.at(i) << endl;
        }
        cout << "}" << endl;
    }

    //==== Load Directories
    void LoadFakeDirectory() {
        vector<TFile*> TFiles; // 0 for data, 1 for mc, 2~ for subsamples
        TFile* f_data = new TFile(pathData + "FakeEstimator_DoubleEG.root");
        TFiles.push_back(f_data);

        for (unsigned int i = 1; i < Samples.size(); i++) {
            TFile* f_mc = new TFile(pathMC + "FakeEstimator_" + Samples.at(i) + ".root");
            TFiles.push_back(f_mc);
        }

        //map
        for (unsigned int i = 1; i < Samples.size(); i++) { TString sample = Samples.at(i);
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

	TDirectory* GetFakeDirectory
		(TString sample, TString id, TString syst, TString prompt, TString region) {
		TDirectory* dir = MapFakeDirectory[sample][id][syst][prompt][region];
		if (dir == NULL) {
			cout << "[FileNavi::GetFakeDirectory] Null directory" << endl;
		}

		return dir;
	}
};
