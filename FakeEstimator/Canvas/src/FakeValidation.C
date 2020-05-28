#include <iostream>

class FakeValidation {

private:
	TString pathData;
	TString pathMC;

	vector<TString> Samples;
	vector<TString> IDs;
	vector<TString> Systs;
	vector<TString> Prompts;
	vector<TString> Regions;

public:
	//==== Constructor ====
	FakeValidation(const vector<TString> &samples, const vector<TString> &ids, 
			const vector<TString> systs, const vector<TString> &prompts, const vector<TString> regions)
		:Samples(samples), IDs(ids), Systs(systs), Prompts(prompts), Regions(regions) 
	{
		cout << "[FakeValidation] Constructor called" << endl;
	}
	
	//==== Set Functions ====
	void SetPathData(const TString &path);
	void SetPathMC(const TString &path);
	void SetSamples(const vector<TString> &samples);
	void SetSysts(const vector<TString> &systs);
	void SetPrompts(const vector<TString> &prompts);
	void SetRegions(const vector<TString. &regions);

	//==== Get Functions ====
	TString GetPathData() const;
	TString GetPathMC() const;
	vector<TString> GetSamples() const;
	vector<TString> GetIDs() const;
	vector<TString> GetSysts() const;
	vector<TString> GetPrompts() const;
	vector<TString> GetRegions() const;

	//==== Functions for fake rate calculation ====
	TH1D* GetHist1D(TDirectory* dir, TString histname);
	TH2D* GetHist2D(TDirectory* dir, TString histname);
	
	Double_t GetScale(TString id, TString syst, TString prompt);

	TH1D* MakeFake1D(TString id, TString syst, TString prompt, int scale);
	TH2D* MakeFake2D(TString id, TString syst, TString prompt, int scale);

	TCanvas* DrawFake1DPlot(TString id, TString syst, TString prompt, int scale);
	TCanvas* DrawFake1DPlot(TString id, TString syst, TString prompt, int scale);
};
