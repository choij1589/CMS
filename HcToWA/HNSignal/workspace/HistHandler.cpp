#include "FileNavi.h"
#include "FileNaiv.cpp"
#include "HistHandler.h"

HistHandler::HistHandler(const TString& pathData, const TString& pathMC, const vector<TString>& Samples) {
	navi.SetPathData(pathData);
	navi.SetPathMC(pathMC);
	navi.SetSamples(Samples);
}
