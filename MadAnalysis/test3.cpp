void test3() {
	using namespace RooFit;

	//==== Load TTree for fitting ====
    TFile* f = new TFile("tripletM.root");
    TTree* tr = (TTree*)f->Get("tripletM_sr3");

	//==== Set up component pdfs ====
	RooRealVar x("tripletM_sr3", "x", 0, 2000);
	
	//==== Create two Gaussian pdfs g1 and g2 ====
	RooRealVar mean1("mean1", "mean1", 897., 890., 904.);
	RooRealVar mean2("mean2", "mean2", 842., 840.5, 843.5);
	RooRealVar sigma1("sigma1", "sigma1", 217., 210, 224);
	RooRealVar sigma2("sigma2", "sigma2", 73, 71.5, 74.5);

	RooGaussian sig1("sig1", "sig1", x, mean1, sigma1);
	RooGaussian sig2("sig2", "sig2", x, mean2, sigma2);

	//==== Build background pdf ====
	RooRealVar a("a", "a", 10e20, 10e28);
	RooRealVar b("b", "b", 7100,  6900, 7300);
	RooRealVar c("c", "c", 0., -200., 200.);
	RooRealVar d("d", "d", 10e-2, 10e-4, 10.);
	RooGenericPdf bkg("bkg", "bkg", "(a / x^(5+d*TMath::Log((x+c)/13000)))*(1 / (TMa    th::Exp(b / (x-c))-1))", RooArgSet(x, a, b, c, d));

	//==== Add Signal Components ====
	RooRealVar core_frac("core_frac", "core_frac", 0.2, 0., 1.);
	RooAddPdf sig("sig", "signal", RooArgList(sig1, sig2), core_frac);

	//==== Add signal and background ====
	RooRealVar bkgfrac("bkgfrac", "bkgfrac", 0.8, 0., 1.);
	RooAddPdf model("model", "g1+g2+a", RooArgList(bkg, sig), bkgfrac);

	//==== Load data ====
	RooDataSet data("data", "my data", RooArgSet(x), Import(*tr));
	RooDataHist* dhist = data.binnedClone();

	model.chi2FitTo(*dhist);
	//model.fitTo(data);

	//==== Plot result ====
	RooPlot* x_frame = x.frame();
	data.plotOn(x_frame);
	//sig.plotOn(x_frame);
	model.plotOn(x_frame, Components(bkg), LineStyle(kDashed));
	model.plotOn(x_frame);

	x_frame->Draw();
}
