#ifndef HistHandler_h__
#define HistHandler_h__

class HistHandler {
private:
	FileNavi navi;

public:
	// constructor
	HistHandler(const TString& pathData, const TString& pathMC, const vector<TString>& Samples);

	// destructor
	~HistHandler();

	// other functions
	
}

#endif
