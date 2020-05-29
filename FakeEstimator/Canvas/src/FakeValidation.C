#include <iostream>

//==== INFO =====
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

//==== Set Functions ====
void FakeValidation::SetPathData(const TString &path) {
	pathData = path;
	cout << "[FakeValidation::SetPathData] pathData = " << pathData << endl;
}
void FakeValidation::SetPathMC(const TString &path) {
	pathMC = path;
	cout << "[FakeValidation::SetPathMC] pathMC = " << pathMC << endl;
}
void FakeValidation::SetSamples(const vector<TString> &samples) {
	Samples = samples;
	cout << "[FakeValidation::SetSamples] Samples = {" << endl;
	for (unsigned int i = 0; i < Samples.size(); i++) {
		cout << Samples.at(i) << endl;
	}
	cout << "}" << endl;
}
void FakeValidation::SetSysts(const vector<TString> &systs) {
	Systs = systs;
	cout << "[FakeValidation::SetSysts] Systs = {" << endl;
	for (unsigned int i = 0; i < Systs.size(); i++) {
		cout << Systs.at(i) << endl;
	}
	cout << "}" << endl;
}
void FakeValidation::SetPrompts(const vector<TString> &prompts) {
	Prompts = prompts;
	cout << "[FakeValidation::SetPrompts] Prompts = {" << endl;
	for (unsigned int i = 0; i < Prompts.size(); i++) {
		cout << Prompts.at(i) << endl;
	}
	cout << "}" << endl;
}
void FakeValidation::SetRegions(const vector<TString> &regions) {
	Regions = regions;
	cout << "[FakeValidation::SetRegions] Regions = {" << endl;
	for (unsigned int i = 0; i < Regions.size(); i++) {
		cout << Regions.at(i) << endl;
	}
	cout << "}" << endl;
}
//==== Get Functions ====
TString FakeValidation::GetPathData() const {
	return pathData;
}
TString FakeValidation::GetPathMC() const {
	return pathMC;
}
vector<TString> GetSamples() const {
	return Samples;
}
vector<TString> GetIDs() const {
	return IDs;
}
vector<TString> GetSysts() const {
	return Systs;
}
vector<TString> GetPrompts const {
	return Prompts;
}
vector<TString> GetRegions const {
	return Regions;
}
//==== Functions for fake rate calcuation ====































