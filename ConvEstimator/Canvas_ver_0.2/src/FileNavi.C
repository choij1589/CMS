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

void FileNavi::SetElectronIDs(const vector<TString> &ids) {
	ElectronIDs = ids;
	cout << "[FileNavi::SetElectronIDs] ElectronIDs = {";
	for (unsigned int i = 0; i < ElectronIDs.size()-1; i++) {
		cout << ElectronIDs.at(i) << ", ";
	}
	cout << ElectronIDs.at(ElectronIDs.size()-1) << "}" << endl;
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
vector<TString> FileNavi::GetElectronIDs() const {
	return ElectronIDs;
}

TDirectory* FileNavi::GetDirectory(TString sample, TString dirName) const {
	TString path;
	if (sample.Contains("DoubleEG")) path = pathData;
	else path = pathMC;
	TString pathFile = path + "ConvEstimator_" + sample + ".root";
	
	TFile* f = new TFile(pathFile);
	TDirectory* this_dir = (TDirectory*)f->Get(dirName);

	if (this_dir == NULL) {
		cout << "[FileNavi::GetDirectory] Null Directory" << endl;
		exit(EXIT_FAILURE);
	}
	
	return this_dir;
}

