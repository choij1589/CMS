#include "FileNavi.h"
#include <iostream>
#include <vector>

using namespace std;

//==== Constructors ====
FileNavi::FileNavi() {
	cout << "[FileNavi::FileNavi] Constructor called" << endl;
}

FileNavi::FileNavi(const TString &p_data, const TString &p_MC, const vector<TString> samples, const vector<TString> muonIDs)
	: pathData(p_data), pathMC(p_MC), Samples(samples), MuonIDs(muonIDs) {
	cout << "[FileNavi::FileNavi] Constructor called" << endl;
}

//==== Destructors ====
FileNavi::~FileNavi() {}

//==== Member functions ====
void FileNavi::SetPathData(const TString &path) { pathData = path; }
void FileNavi::SetPathMC(const TString &path) { pathMC = path; }
void FileNavi::SetSamples(const vector<TString> &samples) { Samples = samples; }
void FileNavi::SetMuonIDs(const vector<TString> &ids) { MuonIDs = ids; }

TString FileNavi::GetPathData() const { return pathData; }
TString FileNavi::GetPathMC() const { return pathMC; }
vector<TString> FileNavi::GetSamples() const { return Samples; }
vector<TString> FileNavi::GetMuonIDs() const { return MuonIDs; }

TDirectory* FileNavi::GetDirectory(const TString &sample, const TString &muonID, const TString &region, const TString &obj) const {
	const TString path = sample.Contains("SingleMuon") ? pathData : pathMC;
	
	const TString file = "IDVariables_" +  sample + ".root";
	//cout << "[FileNavi::GetDirectory] file name = " << file << endl;
	TFile* f = new TFile(path + file);

	TString id = muonID + "_Central";
	auto* d = (TDirectory*) f->GetDirectory(id);

	enum REGION {DY, TT};
	
	int REG = -1;
	if (region.Contains("DY")) REG = DY;
	if (region.Contains("TT")) REG = TT;

	TDirectory* d_reg = NULL;
	TDirectory* d_reg_obj = NULL;
	switch (REG) {
	case DY:
		d_reg = (TDirectory*) d->Get("DY");
		if (obj.Contains("ev")) return d_reg;
		else if (obj.Contains("mu1")) {
			if (obj.Contains("IDvar")) {
				d_reg_obj = (TDirectory*) d_reg->Get("mu1");
				return (TDirectory*)d_reg_obj->Get("IDvar");
			}
			else return (TDirectory*)d_reg->Get("mu1");
		}
		else if (obj.Contains("mu2")) {
			if (obj.Contains("IDvar")) {
				d_reg_obj = (TDirectory*) d_reg->Get("mu2");
				return (TDirectory*)d_reg_obj->Get("IDvar");
			}
			else return (TDirectory*)d_reg->Get("mu2");
		}
		else if (obj.Contains("j1")) return (TDirectory*)d_reg->Get("j1");
		else if (obj.Contains("j2")) return (TDirectory*)d_reg->Get("j2");
		else {
			cout << "[FileNavi::GetDirectory] obj = " << obj << endl;
			cout << "[FileNavi::GetDIrectory] Wrong object" << endl;
			exit(EXIT_FAILURE);
		}
		break;
	
	case TT:
		d_reg = (TDirectory*) d->Get("TT");
		if (obj.Contains("ev")) return d_reg;
        else if (obj.Contains("mu1")) {
			if (obj.Contains("IDvar")) {
				d_reg_obj = (TDirectory*) d_reg->Get("mu1");
				return (TDirectory*)d_reg_obj->Get("IDvar");
			}
			else return (TDirectory*)d_reg->Get("mu1");
		}
        else if (obj.Contains("mu2")) {
			if (obj.Contains("IDvar")) {
				d_reg_obj = (TDirectory*) d_reg->Get("mu2");
				return (TDirectory*)d_reg_obj->Get("IDvar");
			}
			else return (TDirectory*)d_reg->Get("mu2");
		}
        else if (obj.Contains("j1")) return (TDirectory*)d_reg->Get("j1");
        else if (obj.Contains("j2")) return (TDirectory*)d_reg->Get("j2");
        else {
            cout << "[FileNavi::GetDirectory] obj = " << obj << endl;
            cout << "[FileNavi::GetDIrectory] Wrong object" << endl;
            exit(EXIT_FAILURE);
		}
		break;
	
	default:
		cout << "[FileNavi::GetDirectory] Wrong REGION" << endl;
		exit(EXIT_FAILURE);
		break;
	}
}







