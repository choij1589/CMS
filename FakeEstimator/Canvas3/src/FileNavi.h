#ifndef FileNavi_H__
#define FileNavi_H__

using namespace std;
class FileNavi {

private:
    TString pathData, pathMC;

    //==== information for fake rate measurement with systematics
    vector<TString> Samples;
    vector<TString> IDs;
    vector<TString> Systs;
    vector<TString> Prompts;
    vector<TString> Regions;

public:
    //==== you can make different constructor for each analysis
    //==== constructor and destructor for the fake rate measurement
    FileNavi() {};

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

    //==== Other Functions ====
    TDirectory* GetFakeDirectory(TString sample, TString id, TString syst, TString prompt, TString region) const;
};

#endif
