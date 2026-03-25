#include "FtSaveplot.h"
#include "Printpic.C"

// Draw and save decaytime fit plots
//---------------------------------------------------------
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
	)
{

   // Set the binned data for plots
   RooAbsData *AllBindata = wdata->binnedClone();
   RooAbsData *MixBindata = mdata->binnedClone();
   RooAbsData *UixBindata = udata->binnedClone();

   // Set the TCanvas, TLatex and TLegend
   TCanvas *pic1 = new TCanvas("_pic1","",800,600);
   TCanvas *pic2 = new TCanvas("_pic2","",800,600);
   pic1->Divide(1,2,0,0,0);

   TLatex *mylatex1  = new TLatex(0.71,0.58,latext);
   mylatex1->SetTextFont(132);
   mylatex1->SetTextSize(0.06);
   mylatex1->SetNDC();

   TLatex *mylatex2  = new TLatex(0.71,0.58,latext);
   mylatex2->SetTextFont(132);
   mylatex2->SetTextSize(0.06);
   mylatex2->SetNDC();

   TLegend *leg = new TLegend(0.70,0.65,0.88,0.80);
   TLegendEntry *line1 = leg->AddEntry("Mixed","Mixed","LPE");
   TLegendEntry *line2 = leg->AddEntry("Unmixed","Unmixed","LPE");
   Color_t col1 = kBlue;
   Color_t col2 = kRed;
   line1->SetLineColor( col1 );
   line2->SetLineColor( col2 );
   line1->SetMarkerColor( col1 );
   line2->SetMarkerColor( col2 );
   line1->SetMarkerStyle( 8 );
   line2->SetMarkerStyle( 8 );
   leg->SetTextFont(132);
   leg->SetTextSize(0.06);
   
   TPaveText *logo = new TPaveText( 0.70, 0.80, 0.88, 0.88, "BRNDC" );
   logo->AddText("#font[132]{LHCb}");
   logo->SetShadowColor(0);
   logo->SetFillStyle(0);
   logo->SetBorderSize(0);
   logo->SetTextAlign(12);
   logo->SetTextSize(0.06);

   // Draw the total pdf
   double t_l = fitvar->getMin();
   double t_h = fitvar->getMax();
   double binwidth = 0.1;
   int nBin = int((t_h-t_l)/binwidth);

   TString name_dat = TString::Format("%s_dat",FitPdf->GetName());
   TString name_fit = TString::Format("%s_all",FitPdf->GetName());

   RooPlot *frame1 = fitvar->frame( Bins(nBin), Range(t_l,t_h) );
   wdata->plotOn(frame1,DataError(RooAbsData::SumW2),Name(name_dat));
   FitPdf->plotOn(frame1,ProjWData(*condset,*AllBindata),Name(name_fit));
   wdata->plotOn(frame1,DataError(RooAbsData::SumW2),Name(name_dat));

   pic1->cd(2);
   gPad->SetPad(0.02,0.02,0.98,0.77);
   gPad->SetTopMargin(0.002);
   gPad->SetLeftMargin(0.15);
   gPad->SetRightMargin(0.03);

   double ymax = frame1->GetMaximum();
   frame1->SetMaximum( ymax*1.08 );
   frame1->SetTitle("");
   frame1->GetXaxis()->SetTitle(" #it{t} [ps]");
   frame1->GetYaxis()->SetTitle( Form("Weighted cands. / (%.1lf ps)", binwidth) );
   frame1->GetXaxis()->SetTitleSize(0.09);
   frame1->GetYaxis()->SetTitleSize(0.085);
   frame1->GetXaxis()->SetTitleOffset(0.8);
   frame1->GetYaxis()->SetTitleOffset(0.8);
   frame1->addObject(logo);
   frame1->addObject(mylatex1);
   frame1->Draw();

   pic1->cd(1);
   gPad->SetPad(0.02,0.76,0.98,0.98);
   gPad->SetTopMargin(0);
   gPad->SetLeftMargin(0.15);
   gPad->SetRightMargin(0.03);

   RooPlot* pull = fitvar->frame();
   RooHist* hpull = frame1->pullHist();
   hpull->SetLineWidth( 0 );
   hpull->SetFillColor( kBlack );
   pull->addPlotable(hpull,"B");
   pull->SetTitle("");
   pull->GetXaxis()->SetTitle("");
   pull->GetYaxis()->SetRangeUser(-5,5);
   pull->GetYaxis()->SetNdivisions(505);
   pull->GetYaxis()->SetLabelSize(0.15);

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

   pull->Draw();

   // Draw the mixed and unmixed pdf
   pic2->cd();
   gPad->SetPad(0.02,0.02,0.98,0.98);
   gPad->SetLeftMargin(0.15);
   gPad->SetRightMargin(0.05);
   gPad->SetBottomMargin(0.18);

   t_h = 8.;
   nBin = int((t_h-t_l)/binwidth);
   
   TString name_mdat = TString::Format("%s_mdat",FitPdf->GetName());
   TString name_mfit = TString::Format("%s_mfit",FitPdf->GetName());
   TString name_udat = TString::Format("%s_udat",FitPdf->GetName());
   TString name_ufit = TString::Format("%s_ufit",FitPdf->GetName());
   
   RooPlot *frame2 = fitvar->frame( Bins(nBin), Range(t_l,t_h) );
 
   // Keep the plot order : data->plotOn(), pdf->plotOn()
   mdata->plotOn(frame2,DataError(RooAbsData::SumW2),Name(name_mdat),MarkerColor(col1),LineColor(col1));
   FitPdf->plotOn(frame2,ProjWData(*condset,*MixBindata),Name(name_mfit),LineColor(col1));
   mdata->plotOn(frame2,DataError(RooAbsData::SumW2),Name(name_mdat),MarkerColor(col1),LineColor(col1));
   udata->plotOn(frame2,DataError(RooAbsData::SumW2),Name(name_udat),MarkerColor(col2),LineColor(col2));
   FitPdf->plotOn(frame2,ProjWData(*condset,*UixBindata),Name(name_ufit),LineColor(col2));
   udata->plotOn(frame2,DataError(RooAbsData::SumW2),Name(name_udat),MarkerColor(col2),LineColor(col2));
   
   frame2->SetTitle("");
   frame2->GetXaxis()->SetTitle(" #it{t} [ps]");
   frame2->GetYaxis()->SetTitle( Form("Weighted cands. / (%.1lf ps)", binwidth) );
   frame2->GetXaxis()->SetTitleSize(0.085);
   frame2->GetYaxis()->SetTitleSize(0.075);
   frame2->GetXaxis()->SetTitleOffset(0.9);
   frame2->GetYaxis()->SetTitleOffset(1.0);
   frame2->addObject(logo);
   frame2->addObject(mylatex2);
   frame2->addObject(leg);
   frame2->Draw();
   
   double chi2_ndof5 = frame1->chiSquare(name_fit,name_dat,5);
   double chi2_ndof9 = frame1->chiSquare(name_fit,name_dat,9);
   cout<<endl;
   cout<<"========================================="<<endl;
   cout<< "Total chi2 : "<<endl;
   cout<< "chiSquare_NDOF(5) =" << chi2_ndof5 << endl;
   cout<< "chiSquare_NDOF(9) =" << chi2_ndof9 << endl;
   cout<<"========================================="<<endl;
  
   chi2_ndof5 = frame2->chiSquare(name_mfit,name_mdat,5);
   chi2_ndof9 = frame2->chiSquare(name_mfit,name_mdat,9);
   cout<<"========================================="<<endl;
   cout<< "Mixed chi2 : "<<endl;
   cout<< "chiSquare_NDOF(5) =" << chi2_ndof5 << endl;
   cout<< "chiSquare_NDOF(9) =" << chi2_ndof9 << endl;
   cout<<"========================================="<<endl;
   
   chi2_ndof5 = frame2->chiSquare(name_ufit,name_udat,5);
   chi2_ndof9 = frame2->chiSquare(name_ufit,name_udat,9);
   cout<<"========================================="<<endl;
   cout<< "Unmixed chi2 : "<<endl;
   cout<< "chiSquare_NDOF(5) =" << chi2_ndof5 << endl;
   cout<< "chiSquare_NDOF(9) =" << chi2_ndof9 << endl;
   cout<<"========================================="<<endl;

   Printpic(pic1,picname1,1);
   Printpic(pic2,picname2,1);

   delete pic1;
   delete pic2;
}

