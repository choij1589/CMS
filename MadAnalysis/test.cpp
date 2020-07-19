void test() {
	using namespace RooFit;

	//==== Load TTree for fitting ====
	TFile* f = new TFile("tripletM.root");
	TTree* tr = (TTree*)f->Get("tripletM_sr3");

	//==== Create Gaussian function ====
	RooRealVar x("tripletM_sr3", "x", 0, 3500);
	RooRealVar m("m", "mean", 850, 950);
	RooRealVar s("s", "sigma", 200, 150, 250);
	RooGaussian g("g", "gauss(x, m, s)", x, m, s);

	//==== Load TTree to the gaussian fitter ====
	RooDataSet data("data", "my data", RooArgSet(x), Import(*tr));
	g.fitTo(data);
	m.Print();
	s.Print();

	RooPlot* x_frame = x.frame();
	data.plotOn(x_frame);
	g.plotOn(x_frame);
	//g.paramOn(x_frame, data);
	x_frame->Draw();
}

