void test6() {
	using namespace RooFit;

	//==== Load TTree for fitting ====
    TFile* f = new TFile("tripletM.root");
    TTree* tr = (TTree*)f->Get("tripletM_sr3");

    //==== Set up component pdfs ====
    RooRealVar x("tripletM_sr3", "x", 0, 3500);

	RooRealVar mean("mean", "mean", 850, 848, 852);
	RooRealVar sigma("sigma", "sigma", 108.5, 107, 110);

	RooGaussian sig("sig", "sig", x, mean, sigma);

	RooRealVar a("a", "a", 10e20, 10e28);
    RooRealVar b("b", "b", 6200,  6000, 6400);
    RooRealVar c("c", "c", 0., -200., 200.);
    RooRealVar d("d", "d", 10e-2, 10e-4, 10.);
    RooGenericPdf bkg("bkg", "bkg", "(a / x^(5+d*TMath::Log((x+c)/13000)))*(1 / (TMa    th::Exp(b / (x-c))-1))", RooArgSet(x, a, b, c, d));

	RooRealVar bkgfrac("bkgfrac", "bkgfrac", 0.8, 0., 1.);
    RooAddPdf model("model", "g1+g2+a", RooArgList(bkg, sig), bkgfrac);

	RooDataSet data("data", "my data", RooArgSet(x), Import(*tr));
    RooDataHist* dhist = data.binnedClone();

    model.chi2FitTo(*dhist);

	RooPlot* x_frame = x.frame();
    data.plotOn(x_frame);
	x_frame->Draw();
}
