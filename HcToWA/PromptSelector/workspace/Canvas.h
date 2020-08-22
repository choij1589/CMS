#ifndef Canvas_H__
#define Canvas_H__

#include "FileNavi.h"

class Canvas {
private:
	FileNavi navi;	
	// canvas 
    typedef enum {cRATIO, cFULL} CanvasType;
    typedef enum {pRATIO} PadType;
	typedef enum {NORMAL, RIGHTUP, LEFTUP} LegendType;

	TCanvas* cvs = nullptr;
	TLegend* leg = nullptr;
	TPad* pad_up = nullptr;
	TPad* pad_down = nullptr;

	// TObjects to decorate the canvas
	void Clear();
	void SetCanvas(const CanvasType& ctype);
	void SetPad(const PadType& ptye);
	void SetLegend(const LegendType& ltype);
public:
	// constructor
	Canvas();
	Canvas(const TString& pathData, const TString& pathMC, const vector<TString>& Samples);

	// destructor
	~Canvas();

	TCanvas* GetCanvas() const;

	// draw options
	void DrawCutflow(const TString& sample, const TString& region);
	void DrawNormalizedDistribution(const vector<TH1D*> hists);
	void DrawStack(const vector<TH1D*> hists);
	
};

#endif
