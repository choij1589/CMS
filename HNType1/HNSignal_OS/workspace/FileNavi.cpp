#include "FileNavi.h"
using namespace std;

// constructor
FileNavi::FileNavi() {}
FileNavi::FileNavi(const TString& path_data, const TString& path_mc, const vector<TString>& samples)
	: pathData(path_data), pathMC(path_mc), Samples(samples) {}

// destructor
FileNavi::~FileNavi() {}

// get and set
TString FileNavi::GetPathData() const { return pathData; }
TString FileNavi::GetPathMC() const { return pathMC; }
vector<TString> FileNavi::GetSamples() const { return Samples; }

void FileNavi::SetPathData(const TString &path) { pathData = path; }
void FileNavi::SetPathMC(const TString &path) { pathMC = path; }
void FileNavi::SetSamples(const vector<TString> &samples) { Samples = samples; }

// navigation
TH1* FileNavi::GetHist(const TString &sample, const TString &path) {
	TFile* f = nullptr;
	TH1* out = nullptr;

	// get TFile
    TString path_file;
	if (sample.Contains("DoubleMuon")) path_file = pathData + "HNSignal_OS_" + sample + ".root";
	else path_file = pathMC + "HNSignal_OS_" + sample + ".root";
    f = new TFile(path_file);

	try {
		if (!f) throw f;

		out = (TH1*)f->Get(path);
		if (!out) throw out;

		return out;
	}
	catch (TFile* f) {
		cerr << "[FileNavi::GetHist] file path = " << path_file << endl;
		cerr << "[FileNavi::GetHist] null TFile" << endl;
		exit(EXIT_FAILURE);
	}
	catch (TH1* out) {
		cerr << "[FileNavi::GetHist] hist path = " << path << endl;
		cerr << "[FileNavi::GetHist] null histogram" << endl;
		exit(EXIT_FAILURE);
	}
}	
