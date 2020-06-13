#include "FileNavi.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;

//==== Set Functions ====
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
	cout << "[FileNavi::SetSamples] Samples = {";
	for (unsigned int i = 0; i < Samples.size()-1; i++) {
		cout << Samples.at(i) << ", " ;
	}
	cout << Samples.at(Samples.size()-1) << "}" << endl;
}
void FileNavi::SetIDs(const vector<TString> &ids) {
	IDs = ids;
	cout << "[FileNavi::SetIDs] IDs = {";
	for (unsigned int i = 0; i < IDs.size()-1; i++) {
		cout << IDs.at(i) << ", ";
	}
	cout << IDs.at(IDs.size()-1) << "}" << endl;
}
void FileNavi::SetSysts(const vector<TString> &systs) {
	Systs = systs;
	cout << "[FileNavi::SetSysts] Systs = {";
	for (unsigned int i = 0; i < Systs.size()-1; i++) {
		cout << Systs.at(i) << ", ";
	}
	cout << Systs.at(Systs.size()-1) << "}" << endl;
}
void FileNavi::SetPrompts(const vector<TString> &prompts) {
	Prompts = prompts;
	cout << "[FileNavi::SetPrompts] Prompts = {";
	for (unsigned int i = 0; i < Prompts.size()-1; i++) {
		cout << Prompts.at(i) << ", ";
	}
	cout << Prompts.at(Prompts.size()-1) << "}" << endl;
}
void FileNavi::SetRegions(const vector<TString> &regions) {
	Regions = regions;
	cout << "[FileNavi::SetRegions] Regions = {";
	for (unsigned int i = 0; i < Regions.size()-1; i++) {
		cout << Regions.at(i) << ", ";
	}
	cout << Regions.at(Regions.size()-1) << "}" << endl;
}
//==== Get Functions ====
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

//==== Other Functions ====
TDirectory* FileNavi::GetFakeDirectory(
	TString sample, TString id, TString syst, TString prompt, TString region) const {
	TFile* f = NULL;
	if (sample.Contains("DoubleEG")) f = new TFile(pathData + "FakeEstimator_DoubleEG.root");
	else f = new TFile(pathMC + "FakeEstimator_" + sample + ".root");

	auto* dirID = (TDirectory*) f->Get(id);
	auto* dirSyst = (TDirectory*) dirID->Get(syst);
	auto* dirPrompt = (TDirectory*) dirSyst->Get(prompt);
	auto* dirRegion = (TDirectory*) dirPrompt->Get(region);

	if (dirRegion == NULL) {
		cout << "[FileNavi::GetFakeDirectory] Null directory" << endl;
	}
	return dirRegion;
}
