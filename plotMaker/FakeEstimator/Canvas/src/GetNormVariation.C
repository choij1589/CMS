//==== files information ====
TString pathData = "/Users/choij/FakeEstimator/Outputs/2016/RunNormSysts__/DATA/FakeEstimator_DoubleEG_2016.root";
TString pathMC = "/Users/choij/FakeEstimator/Outputs/2016/RunNormSysts__/FakeEstimator_MC.root";

TFile* f_data = new TFile(pathData);
TFile* f_mc = new TFile(pathMC);

vector<TString> WPs = {"Loose", "Tight"};
vector<TString> Systs = {"Central",
						"ElectronEnDown", "ElectronEnUp",
						"ElectronResDown", "ElectronResUp",
						"JetEnDown", "JetEnUp",
						"JetResDown", "JetResUp",
						"PileUp"};

//==== function declarations ====
TDirectory* GetDirectory(bool isData, TString wp, TString syst);
Double_t GetScale(TString wp, TString syst);

//=============================
//====== Main Function ========
//=============================
void GetNormVariation() {
  Double_t scales_tight[Systs.size()], scales_loose[Systs.size()];
  for (unsigned int i = 0; i < Systs.size(); i++) {
	scales_tight[i] = GetScale("Tight", Systs.at(i));
	scales_loose[i] = GetScale("Loose", Systs.at(i));
	cout << "Tight_" + Systs.at(i) + ": " << scales_tight[i] << endl;
	cout << "Loose_" + Systs.at(i) + ": " << scales_loose[i] << endl;
	cout << "GetScale for " << Systs.at(i) << "finished" << endl;
  }

  cout << endl;
  cout << "Evaluate variation..." << endl;
  Double_t var_tight[Systs.size()], var_loose[Systs.size()];
  for (unsigned int i = 0; i < Systs.size(); i++) {
	var_tight[i] = ((scales_tight[i] - scales_tight[0]) / scales_tight[0]);
	var_loose[i] = ((scales_loose[i] - scales_loose[0]) / scales_loose[0]);
  }

  Double_t total_var_tight = 0, total_var_loose = 0;
  for (unsigned int i = 0; i < Systs.size(); i++) {
	cout << "Normalization Variation (Tight_" + Systs.at(i) + ") = " << var_tight[i] << endl;
	cout << "Normalization Varration (Loose_" + Systs.at(i) + ") = " << var_loose[i] << endl;
	total_var_tight += (var_tight[i] * var_tight[i]);
	total_var_loose += (var_loose[i] * var_loose[i]);
  }
  total_var_tight = TMath::Sqrt(total_var_tight);
  total_var_loose = TMath::Sqrt(total_var_loose);

  cout << endl;
  cout << "Total Variation for tight: " << total_var_tight << endl;
  cout << "Total Variation for loose: " << total_var_loose << endl;
}

//==== Private Functions ====
TDirectory* GetDirectory(bool isData, TString wp, TString syst) {
  TDirectory* temp_dir = NULL;

  if (isData == true) {
	temp_dir = (TDirectory*)f_data->GetDirectory(wp + "_" + syst);
  }
  else {
	temp_dir = (TDirectory*)f_mc->GetDirectory(wp + "_" + syst);
  }

  return temp_dir;
}

Double_t GetScale(TString wp, TString syst) {
  TDirectory* dir_data = GetDirectory(1, wp, syst);
  TDirectory* dir_mc = GetDirectory(0, wp, syst);

  TH1D* h_data = (TH1D*)dir_data->Get("Mt_W_enriched_" + wp + "_" + syst);
  TH1D* h_mc = (TH1D*)dir_mc->Get("Mt_W_enriched_" + wp + "_" + syst);

  Double_t scale = h_data->Integral() / h_mc->Integral();

  return scale;
}
