void test5() {
	using namespace RooFit;

	TFile* f = new TFile("tripletM.root");
	TTree* tr = (TTree*)f->Get("tripletM_sr3");

	RooRealVar x("tripletM_sr3", "x", 0, 3500);

	//==== background only fit ====
	//RooRealVar p_0("p_0", "p_0", 0, 10000);
	//RooRealVar p_1("p_1", "p_1", 0, 0, 100);
	//RooRealVar p_2("p_2", "p_2", 0, 0, 100);
	//RooRealVar p_3("p_3", "p_3", 0, 0, 100);
	//RooGenericPdf bkg("bkg", "bkg", "p_0*(1 - (x / 13000))^(p_1) / (x / 13000)^(p_2 + p_3*TMath::Log(x / 13000))", RooArgSet(p_0, p_1, p_2, p_3));

	//RooRealVar a("a", "a", 0, 100);
	//RooRealVar b("b", "b", 0, 10);
	//RooRealVar c("c", "c", 0, 300);
	//RooRealVar d("d", "d", 0);
	//RooGenericPdf bkg("bkg", "bkg", "(1 / (x + c)^(5 + d*TMath::Log(x/13000)))*(a / (TMath::Exp(b/ (x+c)) - 1))", RooArgSet(a, b, c, d));
	
	//RooRealVar c0("c0", "c0", 1.0, -1., 1.);
	//RooRealVar c1("c1", "c1", 0.1, -1., 1.);
	//RooRealVar c2("c2", "c2", 0.1, -1., 1.);
	//RooChebychev bkg("bkg", "bkg", x, RooArgList(c0, c1, c2));
	
	//RooRealVar meanl("meanl", "meanl", 800, 1000);
	//RooRealVar sigmal("sigmal", "sigmal", 100, 300);
	//RooLandau landau("landau", "landau", x, meanl, sigmal);

	//RooRealVar meang("meang", "meang", 800, 1000);
	//RooRealVar sigmag("sigmag", "sigmag", 100, 300);
	//RooGaussian gauss("gauss", "gauss", x, meang, sigmag);

	//RooNumConvPdf bkg("bkg", "bkg", x, landau, gauss);
	
	RooRealVar a("a", "a", 10e24, 10e30);
	RooRealVar b("b", "b", 6400,  6200, 6600);
	RooRealVar c("c", "c", 0, -200, 200);
	RooRealVar d("d", "d", 10e-2, 0, 10e-10);
	RooGenericPdf bkg("bkg", "bkg", "(a / x^(5+d*TMath::Log((x+c)/13000)))*(1 / (TMath::Exp(b / (x-c))-1))", RooArgSet(x, a, b, c, d));

	//==== data ====
	RooDataSet data("data", "my data", RooArgSet(x), Import(*tr));
	RooDataHist* dhist = data.binnedClone();

	bkg.chi2FitTo(*dhist);

	RooPlot* x_frame = x.frame();
	data.plotOn(x_frame);
	bkg.plotOn(x_frame);

	x_frame->Draw();
}


