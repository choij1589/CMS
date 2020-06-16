#include "FileNavi.h"
#include <iostream>
#include <vector>

using namespace std;

//==== set functions =====
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
		cout << Samples.at(i) << ", ";
	}
	cout << Samples.at(Samples.size()-1) << "}" << endl;
}

void FileNavi::SetIDSets(const vector<TString> &idsets) {
	IDSets = idsets;
	cout << "[FileNavi::SetIDSets] IDSets = {";
	for (unsigned int i = 0; i < IDSets.size()-1; i++) {
		cout << IDSets.at(i) << ", ";
	}
	cout << IDSets.at(IDSets.size()-1) << "}" << endl;
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
vector<TString> FileNavi::GetIDSets() const {
	return IDSets;
}

TDirectory* FileNavi::GetDirectory(TString sample, TString direcName) const {
	TString path;
	if (sample.Contains("DoubleEG")) path = pathData;
	else path = pathMC;
	TString pathFile = path + "FakeValidator_" + sample + ".root";
	
	TFile* f = new TFile(pathFile);
	TDirectory* this_dir = (TDirectory*)f->Get(direcName);

	if (this_dir == NULL) {
		cout << "[FileNavi::GetDirectory] Null Directory" << endl;
		exit(EXIT_FAILURE);
	}
	
	return this_dir;
}

TDirectory* FileNavi::GetDirectory(TString sample, TString idset, bool isFake, int sys) {
	TString this_dirName = idset + "_";
	if (!isFake) this_dirName += "Central";
	else {
		if (sys == 0) this_dirName +="Central_WithPrompt_FakeContribution";
		else if (sys == +1) this_dirName += "SystUp_WithPrompt_FakeContribution";
		else if (sys == -1) this_dirName += "SystDown_WithPrompt_FakeContribution";
		else {
			cout << "[FileNavi::GetDirectory] sys should be 0, +1, -1" << endl;
			exit(EXIT_FAILURE);
		}
	}

	TDirectory* this_dir = GetDirectory(sample, this_dirName);
	return this_dir;
}
