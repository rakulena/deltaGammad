#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <unistd.h>
#include "Printpic.C"

   
// Efficiecncy Error
double Eff_Error(
	double a, 
	double b
	)
{
   double efferr = sqrt( (a+1.0)*fabs(b-a+1.0)/(b+2.0)/(b+2.0)/(b+3.0) );
   return efferr;
}

// F.O.M Error
double FOM_Error(
	double aim, 
	double nsig,
	double nbkg,
	double genEvt, 
	double eff
	)
{
   double efferr = Eff_Error( nsig, genEvt );
   //double bkgerr = 0.1;
   //if( nbkg != 0 ) bkgerr = sqrt( nbkg );

   double error = sqrt(
	   pow( efferr/( aim/2+sqrt(nbkg) ), 2) +
	   pow( eff/( 2.*sqrt(nbkg)*(aim/2+sqrt(nbkg))*(aim/2+sqrt(nbkg)) ), 2) );

   return error;
}

// F.O.M = eff/(0.5*a+sqrt(B))
// eff = MCEvt/GenMCEvt
void OptimizePunzi(
	TChain *sig_chain,
	TChain *bkg_chain,
	const char* sigcut,
	const char* bkgcut,
	const char* mvaname,
	const char* sigweight,
	const char* bkgweight,
	bool InverseCut,
	int binnum,
	double mva_l,
	double mva_h,
	double aim,
	double genEvt,
	double ratio,
	const char* texname,
	const char* picname
	)
{
   // Define the mva cut step 
   const int nBin = binnum;
   double mva_mins = sig_chain->GetMinimum(mvaname)-0.1*abs( sig_chain->GetMinimum(mvaname) );
   double mva_minb = bkg_chain->GetMinimum(mvaname)-0.1*abs( bkg_chain->GetMinimum(mvaname) );

   double mva_maxs = sig_chain->GetMaximum(mvaname)+0.1*abs( sig_chain->GetMaximum(mvaname) );
   double mva_maxb = bkg_chain->GetMaximum(mvaname)+0.1*abs( bkg_chain->GetMaximum(mvaname) );
   double mvastep = (mva_h-mva_l)/nBin;

   // Define the histograms
   double binpoint[nBin+1];
   binpoint[nBin] = mva_h;
   for( int i=0; i<nBin; i++){ binpoint[i] = mva_l+i*mvastep; }

   TH1D *hist_sig = new TH1D("hist_sig","",nBin,binpoint); // sig hist for optimized range
   TH1D *hist_bkg = new TH1D("hist_bkg","",nBin,binpoint); // bkg hist for optimized range
   
   // Set the edge histograms
   double eds_l,eds_h;
   double edb_l,edb_h;
   if( InverseCut==0 ){
	eds_l = binpoint[nBin];
	edb_l = binpoint[nBin];
	eds_h = mva_maxs;
	edb_h = mva_maxb;
   }else{
	eds_l = mva_mins;
	edb_l = mva_minb;
	eds_h = binpoint[0];
	edb_h = binpoint[0];
   }

   TH1D *hist_eds = new TH1D("hist_eds","",1,eds_l,eds_h); 
   TH1D *hist_edb = new TH1D("hist_edb","",1,edb_l,edb_h); 

   // Draw the histograms
   string sigcut_exp1;
   string sigcut_exp2;
   string bkgcut_exp1;
   string bkgcut_exp2;

   if( strcmp(sigcut,"")==0 ){
	sigcut_exp1 = Form( "%s*(%s>%lf&&%s<%lf)",sigweight, mvaname, mva_l, mvaname, mva_h );
	bkgcut_exp1 = Form( "%s*(%s>%lf&&%s<%lf)",sigweight, mvaname, eds_l, mvaname, eds_h );
   }else{
	sigcut_exp1 = Form( "%s*(%s&&%s>%lf&&%s<%lf)",sigweight, sigcut, mvaname, mva_l, mvaname, mva_h );
	bkgcut_exp1 = Form( "%s*(%s&&%s>%lf&&%s<%lf)",sigweight, sigcut, mvaname, eds_l, mvaname, eds_h );
   }

   if( strcmp(bkgcut,"")==0 ){
	sigcut_exp2 = Form( "%s*(%s>%lf&&%s<%lf)",bkgweight, mvaname, mva_l, mvaname, mva_h );
	bkgcut_exp2 = Form( "%s*(%s>%lf&&%s<%lf)",bkgweight, mvaname, edb_l, mvaname, edb_h );
   }else{
	sigcut_exp2 = Form( "%s*(%s&&%s>%lf&&%s<%lf)",bkgweight, bkgcut, mvaname, mva_l, mvaname, mva_h );
	bkgcut_exp2 = Form( "%s*(%s&&%s>%lf&&%s<%lf)",bkgweight, bkgcut, mvaname, edb_l, mvaname, edb_h );
   }

   sig_chain->Project( "hist_sig", mvaname, sigcut_exp1.c_str() );
   bkg_chain->Project( "hist_bkg", mvaname, sigcut_exp2.c_str() );
   sig_chain->Project( "hist_eds", mvaname, bkgcut_exp1.c_str() );
   bkg_chain->Project( "hist_edb", mvaname, bkgcut_exp2.c_str() );

   // Optimize mva cut
   cout<<"---------------------------------------------------"<<endl;
   cout<<"  "<<nBin<<" bins, "<<mvaname<<" : "<<mva_l<<"~"<<mva_h<<endl;
   cout<<"---------------------------------------------------"<<endl;
   cout<<"Num | "
	<<" Cut Value | "
	<<" Eff (%) | " 
	<<" F.O.M (10^-3) "<<endl;
   cout<<"---------------------------------------------------"<<endl;

   double x[nBin],xerr[nBin];
   double y[nBin],yerr[nBin];
   double ymin, ymax;
   double effmin, effmax;
   int minnum = 0;
   int maxnum = 0;


   double neds = hist_eds->Integral();
   double nedb = hist_edb->Integral();
   for( int i=0; i<nBin; i++ ){

	double nsig;
	double nbkg;
	if( InverseCut == 0 ){
	   nsig = hist_sig->Integral(i+1,nBin)+neds;
	   nbkg = hist_bkg->Integral(i+1,nBin)+nedb;
	}else{
	   nsig = hist_sig->Integral(0,i)+neds;
	   nbkg = hist_bkg->Integral(0,i)+nedb;
	}

      if( ratio==-1 ) ratio = nbkg;
	double eff  = nsig/genEvt;
	double FOM  = eff/( aim/2.+sqrt(nbkg*ratio) );
	double FOM_err = FOM_Error( aim, nsig, nbkg, genEvt, eff );

	x[i] = binpoint[i];
	y[i] = FOM;
	xerr[i] = 0.;
	yerr[i] = FOM_err;

	if( i == 0 ){ ymin = FOM; ymax = FOM; effmax = eff; }

	ymin = min( ymin, FOM );
	ymax = max( ymax, FOM );

	if( ymin == FOM ){ minnum = i; effmin = eff; }
	if( ymax == FOM ){ maxnum = i; effmax = eff; }

   }

   // Output the information into a tex file
   if( strcmp(texname,"")!=0 ){
	ofstream oftex( texname );
	for( int i=0; i<nBin; i++ ){
	   oftex<<" "<<x[i]<<" "<<xerr[i]<<" "<<xerr[i]
		<<" "<<y[i]<<" "<<yerr[i]<<" "<<yerr[i]<<endl;
	}
	oftex.close();
   }

   cout<<"---------------------------------------------------"<<endl;
   cout<<"Maximum point : "
	<<setiosflags(ios::fixed)<<setprecision(0)<<maxnum<<" "
	<<setiosflags(ios::fixed)<<setprecision(4)<<x[maxnum]<<" "
	<<setiosflags(ios::fixed)<<setprecision(2)<<effmax*100<<" "
	<<setiosflags(ios::fixed)<<setprecision(2)<<y[maxnum]*1000<<endl;
   cout<<"Minimum point : "
	<<setiosflags(ios::fixed)<<setprecision(0)<<minnum<<" "
	<<setiosflags(ios::fixed)<<setprecision(4)<<x[minnum]<<" "
	<<setiosflags(ios::fixed)<<setprecision(2)<<effmin*100<<" "
	<<setiosflags(ios::fixed)<<setprecision(2)<<y[minnum]*1000<<endl;
   //   cout<<"Minimum point : "<<minnum<<" "<<x[minnum]<<" "<<effmin<<" "<<y[minnum]<<endl;
   cout<<"---------------------------------------------------"<<endl<<endl;

   TGraphAsymmErrors *graph = new TGraphAsymmErrors(nBin,x,y,xerr,xerr,yerr,yerr);

   TGaxis::SetMaxDigits(3);
   graph->SetMinimum( ymin*0.5 );
   graph->SetMaximum( ymax*1.1 );
   graph->GetXaxis()->SetTitle( mvaname );
   graph->GetYaxis()->SetTitle( "F.O.M" );
   graph->GetXaxis()->SetTitleFont( 132 );
   graph->GetYaxis()->SetTitleFont( 132 );
   graph->SetMarkerColor(4);
   graph->SetLineColor(4);
   graph->SetMarkerStyle(7);
   graph->SetMarkerSize(2);

   TLine *optline = new TLine(x[maxnum],y[minnum]*0.5,x[maxnum],y[maxnum]*1.1);
   optline->SetLineColor(2);

   TLegend *optleg = new TLegend(0.18,0.82,0.28,0.90,Form("Cut~%.4lf",x[maxnum]));
   optleg->SetBorderSize(0);
   optleg->SetTextFont(132);
   optleg->SetTextSize(0.035);
   optleg->SetFillColor(0);

   TCanvas *pic = new TCanvas( picname ,"",800,600);
   pic->cd();
   pic->SetGridx();
   pic->SetGridy();
   gPad->SetTopMargin(0.07);

   graph->Draw("AP");
   optline->Draw("same");
   optleg->Draw("same");

   pic->Print( Form("%s.pdf",picname) );
   //Printpic( pic, picname, 2 );

   delete hist_sig;
   delete hist_bkg;
   delete hist_eds;
   delete hist_edb;

}
