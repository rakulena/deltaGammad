#include "headfile.h"
#include "Printpic.C"
#include <random>

// Set var frame
void SetVarFrame(
	RooPlot *vframe,
	const char* XTitle,
	const char* YTitle,
	bool LogyDec = 0
	)
{
   double ymax = vframe->GetMaximum();
   double ymin = vframe->GetMinimum();
   
   if( ymin >= 0 || LogyDec ){
	vframe->SetMinimum( 1e-2 );
   }

   vframe->SetMaximum( ymax*1.087 );
   vframe->SetXTitle( XTitle );
   vframe->SetYTitle( YTitle );

   TAttAxis *xAxis = vframe->GetXaxis();
   TAttAxis *yAxis = vframe->GetYaxis();

   double yoff;
   if( ymax<1e2 )  yoff = 1.05;
   if( ymax>=1e2 && ymax<1e3 ) yoff = 1.10;
   if( ymax>=1e3 && ymax<1e4 ) yoff = 1.20;
   if( ymax>=1e4 || ymax<=1e-1){ yoff = 1.25; }

   double xsize = xAxis->GetTitleSize(); 
   xsize = min(xsize,0.065);

   xAxis->SetTitleFont(132);
   yAxis->SetTitleFont(132);
   xAxis->SetTitleSize(xsize);
   yAxis->SetTitleSize(0.070);
   xAxis->SetTitleOffset(1.15);
   yAxis->SetTitleOffset(yoff);
   xAxis->SetLabelOffset(0.02);
   yAxis->SetLabelOffset(0.01);
}
   
// Get pull frame, 2 mehtods can be used
RooPlot *GetPullFrame(
	RooPlot *vframe,
	RooRealVar *fitvar,
	const char *plotdata,
	const char *plotpdf
	)
{
   // Get number of bins & [x_low,x_high] from plot
   int nBin = vframe->GetXaxis()->GetNbins();
   double x_l = vframe->GetXaxis()->GetXmin();
   double x_h = vframe->GetXaxis()->GetXmax();

   // pull frame
   RooPlot *pull = fitvar->frame( Bins(nBin), Range(x_l,x_h) );
   RooHist* hpull = vframe->pullHist(plotdata,plotpdf);
   hpull->SetLineWidth( 0 );
   hpull->SetFillColor( kBlack );
   pull->addPlotable(hpull,"B");

   //pull->addObject((TObject*)vframe->pullHist(plotdata,plotpdf),"P") ;

   return pull;
}

RooPlot *GetPullFrame(
	RooPlot *vframe,
	RooRealVar *fitvar,
	RooDataSet *data,
	RooAbsPdf  *fitpdf
	)
{
   // Get number of bins & [x_low,x_high] from plot
   int nBin = vframe->GetXaxis()->GetNbins();
   double x_l = vframe->GetXaxis()->GetXmin();
   double x_h = vframe->GetXaxis()->GetXmax();

   // pull frame
   RooPlot* pframe = fitvar->frame( Bins(nBin), Range(x_l,x_h) );
   data->plotOn(pframe);
   fitpdf->plotOn(pframe);
   RooPlot* pull = fitvar->frame( Bins(nBin), Range(x_l,x_h) );
   RooHist* hpull = pframe->pullHist();

   hpull->SetLineWidth( 0 );
   hpull->SetFillColor( kBlack );
   pull->addPlotable(hpull,"B");

   return pull;
}

// Get pull frame for a conditional fit
RooPlot *GetPullFrame(
	RooPlot *vframe,
	RooRealVar *fitvar,
	RooDataSet *data,
	RooAbsPdf  *fitpdf,
	RooArgSet  *condset
	)
{
   // Get number of bins & [x_low,x_high] from plot
   int nBin = vframe->GetXaxis()->GetNbins();
   double x_l = vframe->GetXaxis()->GetXmin();
   double x_h = vframe->GetXaxis()->GetXmax();

   RooAbsData *Bindata = data->binnedClone();

   // pull frame
   RooPlot* pframe = fitvar->frame( Bins(nBin), Range(x_l,x_h) );
   data->plotOn(pframe);
   fitpdf->plotOn(pframe,ProjWData(*condset,*Bindata));

   RooPlot* pull = fitvar->frame( Bins(nBin), Range(x_l,x_h) );
   RooHist* hpull = pframe->pullHist();
   
   hpull->SetLineWidth( 0 );
   hpull->SetFillColor( kBlack );
   pull->addPlotable(hpull,"B");

   return pull;
}

// Set pull frame
void SetPullFrame(
	RooPlot *pull,
	const char* XTitle
	)
{
   TAttAxis *pxAxis = pull->GetXaxis();
   TAttAxis *pyAxis = pull->GetYaxis();
   pxAxis->SetTitleFont(132);
   pxAxis->SetTitleSize(0.17);
   pxAxis->SetTitleOffset(1.14);
   pxAxis->SetLabelOffset(0.02);
   pyAxis->SetLabelOffset(0.01);

   pull->SetTitle("");
   pull->SetXTitle( XTitle );
   pull->GetYaxis()->SetRangeUser(-5,5);
   pull->GetYaxis()->SetNdivisions(505);
   pull->GetYaxis()->SetLabelSize(0.15);
   pull->GetXaxis()->SetLabelSize(0.16);

   double xmin = pull->GetXaxis()->GetXmin();
   double xmax = pull->GetXaxis()->GetXmax();
   TLine *pline1 = new TLine(xmin, 3,xmax, 3);
   TLine *pline2 = new TLine(xmin,-3,xmax,-3);
   pline1->SetLineStyle(7);
   pline2->SetLineStyle(7);
   pline1->SetLineColor(2);
   pline2->SetLineColor(2);
   pline1->SetLineWidth(2);
   pline2->SetLineWidth(2);
   pull->addObject( pline1 );
   pull->addObject( pline2 );
}

// Set the logo, latex, legend
void SetLogo(
	TPaveText *logo
	)
{
   logo->SetShadowColor(0);
   logo->SetFillStyle(0);
   logo->SetBorderSize(0);
   logo->SetTextAlign(12);
   logo->SetTextSize(0.06);
}

void SetTex(
	TLatex *mytex
	)
{
   mytex->SetTextFont(132);
   mytex->SetTextSize(0.050);
   mytex->SetLineWidth(2);
   mytex->SetNDC();
}

void SetLeg(
	TLegend *leg
	)
{
   leg->SetBorderSize(0);
   leg->SetTextFont(132);
   leg->SetTextSize(0.045);
   leg->SetFillColor(0);
}

// Set the canvas without pull frame
void SetPicNorm(
	TCanvas *pic,
	bool LogyDec = 0
	)
{
   pic->cd();
   gPad->SetPad(0.02,0.04,0.95,0.97);
   gPad->SetTopMargin(0.06);
   gPad->SetLeftMargin(0.15);
   gPad->SetRightMargin(0.10);

   gPad->SetLogy( LogyDec );
}

// Set the canvas with pull frame
void SetPicPull(
	TCanvas *pic,
	bool LogyDec = 0
	)
{
   pic->cd(1);
   gPad->SetTopMargin(0.06);
   gPad->SetLeftMargin(0.18);
   gPad->SetRightMargin(0.06);
   gPad->SetPad(0.02,0.20,0.98,0.97);
   if(LogyDec) gPad->SetBottomMargin(0.10);
   gPad->SetLogy( LogyDec );

   pic->cd(2);
   gPad->SetTopMargin(0);
   gPad->SetLeftMargin(0.18);
   gPad->SetRightMargin(0.06);
   gPad->SetBottomMargin(0.42);
   gPad->SetPad(0.02,0.02,0.98,0.32);
}

// Save the plots
// nform = 4, save plot as *.pdf, *.png, *.eps, *.C 

void SavePic(
	RooPlot *vframe,
	RooPlot *pull,
	const char *picname,
	bool isDraft = 0,
	bool LogyDec = 0,
	int nform = 2
	)
{


   srand( time(NULL) );
   double rndnum = rand();
   system( "sleep 1s" ); // ensure the seed is different
   //cout<<" rndnum "<<rndnum<<endl;

   string canfix = "";
   string namefix = "";
   if( !LogyDec ){
	canfix = "pic";
   }else{
	canfix = "logpic";
	namefix = "_log";
   }

   // Save plots without/with pull frame
   if( isDraft ){
	TCanvas *pic1 = new TCanvas(Form("%s2_%0.f",canfix.c_str(),rndnum),"",800,560);
	SetPicNorm( pic1, LogyDec );

	pic1->cd();
	vframe->Draw();

	Printpic( pic1, Form("%s%s_draft",picname,namefix.c_str()), nform );
   }else{

	TCanvas *pic2 = new TCanvas(Form("%s1_%0.lf",canfix.c_str(),rndnum),"",800,600);
	pic2->Divide(1,2);

	SetPicPull( pic2, LogyDec );

	pic2->cd(1);
	vframe->Draw();

	pic2->cd(2);
	pull->Draw();

	Printpic( pic2, Form("%s%s",picname,namefix.c_str()), nform );
   }
}

// 1st mehtod to save the plots
void RooSaveFitPlot(
	const char *plotdata,
	const char *plotpdf,
	RooRealVar *fitvar,
	RooPlot   *vframe,
	const char* XTitle,
	const char* YTitle,
	const char* picname,
	bool isDraft = 0,
	bool LogyDec = 0,
	int nform = 1
	)
{
   // Set var frame
   SetVarFrame( vframe, XTitle, YTitle, LogyDec );

   // Set pull frame
   RooPlot* pull = GetPullFrame( vframe, fitvar, plotdata, plotpdf );
   SetPullFrame( pull, XTitle );

   // Save plots
   SavePic( vframe, pull, picname, isDraft, LogyDec, nform );
}

// 2nd method to save the plots
void RooSaveFitPlot(
	RooDataSet *data,
	RooAbsPdf  *fitpdf,
	RooRealVar *fitvar,
	RooPlot   *vframe,
	TPaveText *logo,
	const char* XTitle,
	const char* YTitle,
	const char* picname,
	bool isDraft,
	bool LogyDec = 0,
	int nform = 2
	)
{

   // Set var frame
   SetVarFrame( vframe, XTitle, YTitle, LogyDec );

   // Set pull frame
   RooPlot* pull = GetPullFrame(  vframe, fitvar, data, fitpdf );
   SetPullFrame( pull, XTitle );

   // Add logo
   SetLogo( logo );
   vframe->addObject( logo );

   // Save draft plots
   if( isDraft )
	SavePic( vframe, pull, picname, isDraft, LogyDec, nform );

   // Save plots
   SavePic( vframe, pull, picname, 0, LogyDec, nform );

}

void RooSaveFitPlot(
	RooDataSet *data,
	RooAbsPdf  *fitpdf,
	RooRealVar *fitvar,
	RooPlot   *vframe,
	TPaveText *logo,
	TLatex    *latex,
	TLegend   *leg,
	const char* XTitle,
	const char* YTitle,
	const char* picname,
	bool isDraft,
	bool LogyDec = 0,
	int nform = 2
	)
{

   // Set var frame
   SetVarFrame( vframe, XTitle, YTitle, LogyDec );

   // Set pull frame
   RooPlot* pull = GetPullFrame(  vframe, fitvar, data, fitpdf );
   SetPullFrame( pull, XTitle );

   // Add logo
   SetLogo( logo );
   vframe->addObject( logo );

   // Save draft plots
   if( isDraft )
	SavePic( vframe, pull, picname, isDraft, LogyDec, nform );

   // Save plots
   SetTex( latex );
   SetLeg( leg );
   vframe->addObject( latex );
   vframe->addObject( leg );
   
   SavePic( vframe, pull, picname, 0, LogyDec, nform );

}

// For a conditional fit 
void RooSaveFitPlot(
	RooDataSet *data,
	RooAbsPdf  *fitpdf,
	RooRealVar *fitvar,
	RooArgSet  *condset,
	RooPlot   *vframe,
	TPaveText *logo,
	TLatex    *latex,
	TLegend   *leg,
	const char* XTitle,
	const char* YTitle,
	const char* picname,
	bool isDraft,
	bool LogyDec = 0,
	int nform = 2
	)
{

   // Set var frame
   SetVarFrame( vframe, XTitle, YTitle, LogyDec );

   // Set pull frame
   RooPlot* pull = GetPullFrame(  vframe, fitvar, data, fitpdf, condset );
   SetPullFrame( pull, XTitle );

   // Add logo
   SetLogo( logo );
   vframe->addObject( logo );

   // Save draft plots
   if( isDraft )
	SavePic( vframe, pull, picname, isDraft, LogyDec, nform );

   // Save plots
   SetTex( latex );
   SetLeg( leg );
   vframe->addObject( latex );
   vframe->addObject( leg );
   
   SavePic( vframe, pull, picname, 0, LogyDec, nform );

}

void RooSaveFitPlot(
	RooDataSet *data,
	RooAbsPdf  *fitpdf,
	RooRealVar *fitvar,
	RooArgSet  *condset,
	RooPlot   *vframe,
	TPaveText *logo,
	const char* XTitle,
	const char* YTitle,
	const char* picname,
	bool isDraft,
	bool LogyDec = 0,
	int nform = 2
	)
{

   // Set var frame
   SetVarFrame( vframe, XTitle, YTitle, LogyDec );

   // Set pull frame
   RooPlot* pull = GetPullFrame(  vframe, fitvar, data, fitpdf, condset );
   SetPullFrame( pull, XTitle );

   // Add logo
   SetLogo( logo );
   vframe->addObject( logo );

   // Save draft plots
   if( isDraft )
	SavePic( vframe, pull, picname, isDraft, LogyDec, nform );

   // Save plots
   SavePic( vframe, pull, picname, 0, LogyDec, nform );

}
