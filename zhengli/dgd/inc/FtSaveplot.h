#include "headfile.h"
#ifndef __FTSAVEPLOT_HH__
#define __FTSAVEPLOT_HH__

using namespace std;
using namespace RooFit;
using namespace RooStats;

void FtSaveplot(
	RooRealVar *fitvar,
	RooArgSet  *condset,
	RooDataSet *wdata,
	RooDataSet *mdata,
	RooDataSet *udata,
	RooAbsPdf  *FitPdf,
	const char *latext,
	const char *picname1,
	const char *picname2
	);

#endif
