#include "FileNavi.h"
using namespace std;

//==== Constructors ====
FileNavi::FileNavi() {
	cout << "[FileNavi::FileNavi] 2020.07.15 FileNavi for IDVariables" << endl;
	cout << "[FileNavi::FileNavi] Constructor called" << endl;
}

FileNavi::FileNavi(const TString &path_data, const TString &path_mc, const vector<TString> &samples, const vector<TString> &muonIDs)
	: pathData(path_data), pathMC(path_mc), Samples(samples), MuonIDs(muonIDs) {
	cout << "[FileNavi::FileNavi] 2020.07.15 FileNavi for IDVariables" << endl;
	cout << "[FileNavi::FileNavi] Constructor called" << endl;
}

//==== Destructor ====
FileNavi::~FileNavi() { cout << "[FileNavi::~FileNavi] Destructor called" << endl; }

//==== Member functions ====
//==== 1) Get and Set ====
TString FileNavi::GetPathData() const { return pathData; }
TString FileNavi::GetPathMC() const { return pathMC; }
vector<TString> FileNavi::GetSamples() const { return Samples; }
vector<TString> FileNavi::GetMuonIDs() const { return MuonIDs; }

void FileNavi::SetPathData(const TString &path) { pathData = path; }
void FileNavi::SetPathMC(const TString &path) { pathMC = path; }
void FileNavi::SetSamples(const vector<TString> &samples) { Samples = samples; }
void FileNavi::SetMuonIDs(const vector<TString> &muonIDs) { MuonIDs = muonIDs; }

//==== 2) Other member functions ====
TDirectory* FileNavi::GetDirectory(const TString &sample, const TString &path) {
	// Get TFile from sample
	TString path_file = sample.Contains("DoubleMuon")  
		? pathData + "IDVariables_" + sample + ".root" : pathMC + "IDVariables_" + sample + ".root";
	TFile* f = new TFile(path_file);

	// Tokenize the path
	vector<TString> Info;
	TString tok;
	Ssiz_t from = 0;
	while(path.Tokenize(tok, from, "/")) Info.push_back(tok);
	
	TDirectory* d = NULL;
	
	for (unsigned int i = 0; i < Info.size(); i++) {
		if (i == 0) d = (TDirectory*)f->Get(Info.at(i));
		else d = (TDirectory*)d->Get(Info.at(i));

		try {
            if (d==NULL) throw d;
        }
        catch (TDirectory* d) {
            cerr << "[FileNavi::GetHist] directory name = " << Info.at(i) << endl;
            cerr << "[FileNavi::GetHist] Wrong directory name" << endl;
            exit(EXIT_FAILURE);
        }
	}

	return d;
}

TH1* FileNavi::GetHist(const TString &sample, const TString &path) {
	// Get TFile from sample
	TString path_file = sample.Contains("DoubleMuon") 
		? pathData + "IDVariables_" + sample + ".root" : pathMC + "IDVariables_" + sample + ".root";
	TFile* f = new TFile(path_file);

	// Tokenize the path
	vector<TString> Info;
	TString tok;
	Ssiz_t from = 0;
	while(path.Tokenize(tok, from, "/")) Info.push_back(tok);
	
	TDirectory* d = NULL;
	TH1* h = NULL;
	
	for (unsigned int i = 0; i < Info.size()-1; i++) {
		if (i == 0) d = (TDirectory*) f->GetDirectory(Info.at(i));
		else d = (TDirectory*) d->Get(Info.at(i));

		try {
			if (d==NULL) throw d;
		}
		catch (TDirectory* d) {
			cerr << "[FileNavi::GetHist] directory name = " << Info.at(i) << endl;
			cerr << "[FileNavi::GetHist] Wrong directory name" << endl;
			exit(EXIT_FAILURE);
		}
	}
	h = (TH1D*)d->Get(Info.at(Info.size()-1));

	try {
		if (h==NULL) throw h;
		cout << "[FileNavi::GetHist] sample = " << sample << endl;
		cout << "[FileNavi::GetHist] path = " << path << endl;
	}
	catch(TH1* h) {
		cerr << "[FileNavi::GetHist] sample = " << sample << endl;
		cerr << "[FileNavi::GetHist] path = " << path << endl;
		cerr << "[FileNavi::GetHist] path info = " << endl;
		for (const auto &info : Info) cout << info << endl;
		cerr << "[FileNavi::GetHist] Null histogram" << endl;
		exit(EXIT_FAILURE);
	}

	return h;
}


