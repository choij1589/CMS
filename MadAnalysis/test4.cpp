void test4() {
	// to fit data with double gaussian model
	using namespace RooFit;

	TFile* f = new TFile("tripletM.root");
	TTree* tr = (TTree*)f->Get("gen_tripletM_sr3");

	RooRealVar x("gen_tripletM_sr3", "x", 0, 3500);

	RooRealVar mean1("mean1", "mean1", 800, 900);
	//RooRealVar mean2("mean2", "mean2", 800, 850);
	RooRealVar sigma1("sigma1", "sigma1", 50, 150);
	//RooRealVar sigma2("sigma2", "sigma2", 0, 200);

	RooGaussian sig1("sig1", "sig1", x, mean1, sigma1);
	//RooGaussian sig2("sig2", "sig2", x, mean2, sigma2);

	//==== Add signal components ====
	//RooRealVar frac("core_frac", "core_frac", 0.5, 0., 1.);
	//RooAddPdf model("model", "s1+s2", RooArgList(sig1, sig2), frac);


	RooDataSet data("data", "my data", RooArgSet(x), Import(*tr));
	RooDataHist* dhist = data.binnedClone();

	sig1.fitTo(data);

	RooPlot* x_frame = x.frame();
	data.plotOn(x_frame);
	sig1.plotOn(x_frame);

	x_frame->Draw();
	tr->Draw("gen_tripletM_sr3", "", "f&same");
}


