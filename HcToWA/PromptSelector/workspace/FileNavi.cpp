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
TDirectory* FileNavi::GetDirectory(const TString& sample, const TString& path) {
	
	// get TFile
	cout << "[FileNavi::GetDirectory] Current path for samples only supports for MC samples" << endl;
	TString path_file = pathMC + "PromptSelector_" + sample + ".root";
	TFile* f = new TFile(path_file);
	TDirectory* out_dir = NULL;

	// Tokenize the path
	vector<TString> Info;
	TString tok;
	Ssiz_t from = 0;
	while(path.Tokenize(tok, from, "/")) Info.push_back(tok);
	
	for (unsigned int i = 0; i < Info.size(); i++) {
		if (i == 0) out_dir = (TDirectory*)f->Get(Info.at(i));
		else out_dir = (TDirectory*)out_dir->Get(Info.at(i));

		try {
			if (!out_dir) throw out_dir;
		}
		catch (TDirectory* out_dir) {
			cerr << "[FileNavi::GetDirectory] directory name = " << Info.at(i) << endl;
			cerr << "[FileNavi::GetDirectory] Null directory" << endl;
			exit(EXIT_FAILURE);
		}
	}

	return out_dir;
}

TH1* FileNavi::GetHist(const TString &sample, const TString &path) {

	// get TFile
	cout << "[FileNavi::GetHist] Current path for samples only supports for MC samples" << endl;
    TString path_file = pathMC + "PromptSelector_" + sample + ".root";
    TFile* f = new TFile(path_file);
	TDirectory* out_dir = NULL;
	TH1* out_hist = NULL;

	// Tokenize the path
    vector<TString> Info;
    TString tok;
    Ssiz_t from = 0;
	while(path.Tokenize(tok, from, "/")) Info.push_back(tok);

	for (unsigned int i = 0; i < Info.size()-1; i++) {
		if (i == 0) out_dir = (TDirectory*)f->Get(Info.at(i));
        else out_dir = (TDirectory*)out_dir->Get(Info.at(i));

        try {
            if (!out_dir) throw out_dir;
        }
        catch (TDirectory* out_dir) {
            cerr << "[FileNavi::GetHist] sample = " << sample << endl;
			cerr << "[FileNavi::GetHist] path = " << path << endl;
            cerr << "[FileNavi::GetHist] Null directory" << endl;
            exit(EXIT_FAILURE);
        }
    }
	out_hist = (TH1D*)out_dir->Get(Info.at(Info.size()-1));

	try {
		if (!out_hist) throw out_hist;
	}
	catch (TH1* out_hist) {
		cerr << "[FileNavi::GetHist] sample = " << sample << endl;
		cerr << "[FileNavi::GetHist] path = " << path << endl;
		cerr << "[FileNavi::GetHIs] Null hist" << endl;
		exit(EXIT_FAILURE);
	}

	return out_hist;
}
