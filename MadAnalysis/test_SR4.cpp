void test_SR4() {
	using namespace RooFit;
	TFile* f = new TFile("tripletM.root");

	bool trigSig = false;
	bool trigBkg = true;
	bool trigTotal = false;

	TString br;
	if (trigSig) br = "gen_tripletM_sr4";
	else br = "tripletM_sr4";

	TTree* tr = (TTree*)f->Get(br);
	RooRealVar x(br, "x", 0, 4000);

	//==== import data
	RooDataSet data("data", "data", RooArgSet(x), Import(*tr));
	RooDataHist* dhist = data.binnedClone();

	//==== Signal function
	//==== define variables
    //==== name of observable should be the same with the branch name
    //==== for signal, use double gaussian model
    RooRealVar mean1("mean1", "mean1", 1400, 1500);
    RooRealVar mean2("mean2", "mean2", 1500, 1600);
    RooRealVar sigma1("sigma1", "sigam1", 0, 400);
    RooRealVar sigma2("sigma2", "sigma2", 0, 400);

	RooGaussian sig1("sig1", "sig1", x, mean1, sigma1);
    RooGaussian sig2("sig2", "sig2", x, mean2, sigma2);

    RooRealVar sig1_frac("sig1_frac", "sig1_frac", 0.5, 0., 1.);
    RooAddPdf sig("sig", "sig", RooArgList(sig1, sig2), sig1_frac);

	//==== Backgournd function
	RooRealVar a("a", "a", 10e24, 10e30);
	RooRealVar b("b", "b", 6400,  6200, 6600);
	RooRealVar c("c", "c", 0, -200, 200);
	RooRealVar d("d", "d", 10e-2, 0, 10e-10);
    RooGenericPdf bkg("bkg", "bkg", "(a / x^(5+d*TMath::Log((x+c)/13000)))*(1 / (TMath::Exp(b / (x-c))-1))", RooArgSet(x, a, b, c, d));	
	if (trigSig) {
		sig.fitTo(data);

		RooPlot* sig_frame = x.frame();
		data.plotOn(sig_frame);
		sig.plotOn(sig_frame);

		sig_frame->Draw();
	}

	if (trigBkg) {
		bkg.fitTo(data);

		RooPlot* bkg_frame = x.frame();
		data.plotOn(bkg_frame);
		bkg.plotOn(bkg_frame);
		
		bkg_frame->Draw();
	}
}


