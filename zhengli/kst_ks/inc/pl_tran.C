#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <unistd.h>
#include "../../inc/Printpic.C"

double pl_tran(
	const char* picname,
	TF1 *func,
	int nbin,
	double x_l,
	double x_h,
	double scale,
	bool saveplot
	)
{
   double optx;

   cout<<"X range : "<<"("<<x_l<<","<<x_h<<")"<<endl;

   const int nBin = nbin;
   double x[nBin];
   double y[nBin];
   double istep = (x_h-x_l)/nBin;
   double ymin,ymax;

   double suma = 0;
   double sumb = 0;

   for( int i=0; i<nBin; i++ ){
	x[i] = x_l+istep*i;
	y[i] = exp(-1*func->Eval(x[i]));

	if( i==0 ){ 
	   ymin = y[i]; ymax = y[i]; 
	}else{
	   ymin = min( ymin, y[i] );
	   ymax = max( ymax, y[i] );
	}

	if(x[i]>=0)
	   sumb = sumb+y[i];
   }

   double wd_xl = x_l;
   double wd_xh = x_h;
   double wd_yl = 0;
   double wd_yh = 0;
   double mu_x = 0;
   double mu_y = 0;

   double LnLambda = -0.5;
   double wd_y = exp( LnLambda ); 

   for( int i=0; i<nBin; i++ ){

	// Find the corresponding value when LnLambda = -0.5
	if( y[i]<=wd_y && x[i]<0.5*(x_l+x_h) ){
	   wd_xl = fabs(y[i]-wd_y)<fabs(wd_yl-wd_y)?x[i]*scale:wd_xl;
	   wd_yl = fabs(y[i]-wd_y)<fabs(wd_yl-wd_y)?y[i]:wd_yl;
	}
	if( y[i]<=wd_y && x[i]>0.5*(x_l+x_h) ){
	   wd_xh = fabs(y[i]-wd_y)<fabs(wd_yh-wd_y)?x[i]*scale:wd_xh;
	   wd_yh = fabs(y[i]-wd_y)<fabs(wd_yh-wd_y)?y[i]:wd_yh;
	}
	mu_x = fabs(y[i]-1.0)<fabs(mu_y-1.0)?x[i]*scale:mu_x;
	mu_y = fabs(y[i]-1.0)<fabs(mu_y-1.0)?y[i]:mu_y;

	// Integration until the CL at 90%
	if( suma/sumb<0.9 ){ 
	   if(x[i]>=0)
		suma = suma+y[i];
	}else{
	   optx = x[i-1];
	   cout<<" Square   : "<<suma/sumb<<endl;
	   cout<<" Uplimit  : "<<optx<<endl;
	   break;
	}
   }
	  
   // Output the width
   cout<<"---------------------------------------------------------"<<endl;
   cout<<" LnLambda ~ -0.5 correspoding to x, Lambda = "<<wd_xl<<", "<<wd_yl<<endl;
   cout<<" LnLambda ~ -0.5 correspoding to x, Lambda = "<<wd_xh<<", "<<wd_yh<<endl;
   cout<<" LnLambda ~  0   correspoding to x, Lambda = "<<mu_x<<", "<<mu_y<<endl;
   cout<<" Left & right & average sigma "<<mu_x-wd_xl<<", "<<wd_xh-mu_x<<", "<<0.5*(wd_xh-wd_xl)<<endl;
   cout<<"---------------------------------------------------------"<<endl;

   TF1 *gauss = new TF1("gauss",Form("TMath::Gaus(x,%lf,%lf)",mu_x*1.0,0.50*(wd_xh-wd_xl)),x_l*scale,x_h*scale);
   gauss->SetLineWidth(2);

   // Set graph and histogram of confidence interval
   TGraph *grCL = new TGraph( nBin, x, y );
   int nPoint = 1000;
   TH1D *hist = new TH1D(Form("hist_%s",picname),"",nPoint,0,optx*scale);

   for( int i=0; i<nBin; i++ ){
	double tmpx = (i+0.5)*optx/nPoint;
	double tmpy = grCL->Eval(tmpx);
	hist->SetBinContent(i+1,tmpy);
   }
   hist->SetFillStyle(1001);
   hist->SetLineColor(kRed-7);
   hist->SetFillColor(kRed-7);

   // Scale the function
   for( int i=0; i<nBin; i++ ){
	x[i] = x[i]*scale;
   }

   TGraph *graph1 = new TGraph(nBin,x,y);

   graph1->SetName("graph1");
   graph1->SetTitle("");
   graph1->SetMarkerColor(kBlue);
   graph1->SetMarkerStyle(1);
   graph1->SetMarkerSize(3);
   graph1->SetLineColor(kBlue);
   graph1->SetLineWidth(2);

   TH1F *grset = new TH1F("grset","",nBin,x_l*scale,x_h*scale);
   int fontnum = 132;
   
   grset->SetMinimum(ymin*0);
   grset->SetMaximum(ymax*1.08);
   grset->SetMarkerColor(kBlue);
   grset->SetMarkerStyle(1);
   grset->SetMarkerSize(2);
   grset->SetLineColor(kBlue);
   grset->SetDirectory(0);
   grset->SetStats(0);
   //grset->GetXaxis()->SetTitle("\\mathcal{A}");
   grset->GetXaxis()->SetTitle("#font[132]{#it{B}}#font[132]{(#it{B^{0}#rightarrowJ/#psi#phi})(10^{-8})}");
   grset->GetXaxis()->SetNdivisions(510);
   grset->GetXaxis()->SetLabelOffset(0.01);
   grset->GetXaxis()->SetLabelSize(0.06);
   grset->GetXaxis()->SetTitleSize(0.072);
   grset->GetXaxis()->SetTitleOffset(0.95);
   grset->GetXaxis()->SetTitleFont(fontnum);
   
   grset->GetYaxis()->SetTitle("#lambda");
   grset->GetYaxis()->SetNdivisions(510);
   grset->GetYaxis()->SetLabelOffset(0.01);
   grset->GetYaxis()->SetLabelSize(0.06);
   grset->GetYaxis()->SetTitleSize(0.072);
   grset->GetYaxis()->SetTitleOffset(0.95);
   grset->GetYaxis()->SetTitleFont(fontnum);
   grset->GetYaxis()->SetLabelFont(fontnum);

   graph1->SetHistogram(grset);

   //TMathText *Xtitle = new TMathText(2,0.0,"\\mathcal{B}");
   //Xtitle->Draw("same");
   TCanvas *pic1 = new TCanvas(Form("pic1_%s",picname),"",800,600);
   pic1->cd();
   grset->Draw();
   hist->Draw("same");
   //gauss->Draw("same");
   graph1->Draw("sameL");

   TLegend *leg = new TLegend(0.18,0.75,0.45,0.90,"#font[132]{LHCb}");
   leg->SetBorderSize(0);
   leg->SetTextFont(132);
   leg->SetTextSize(0.040);
   leg->SetFillColor(0);
   leg->AddEntry(hist, "Confidence interval", "F");
   leg->Draw("same");

   // Redraw the Xaxis
   TAxis *grsetX =  grset->GetXaxis();
   
   double xmin = grsetX->GetXmin();
   double xmax = grsetX->GetXmax();
   TGaxis *axis = new TGaxis(xmin,0,xmax,0, xmin,xmax,grsetX->GetNdivisions(),"L+");
   axis->SetLabelFont(132);
   axis->SetLabelSize( grsetX->GetLabelSize() );
   axis->SetLabelOffset( grsetX->GetLabelOffset() );
   axis->SetTitle("");
   axis->Draw("same");

   if( saveplot ) Printpic2( pic1, picname, 2 );

   return optx*scale;
}

double pl_tran2(
	const char* picname,
	TF1 *func,
	int nbin,
	double x_l,
	double x_h,
	double scale,
	bool saveplot
	)
{
   double optx;

   cout<<"X range : "<<"("<<x_l<<","<<x_h<<")"<<endl;

   const int nBin = nbin;
   double x[nBin];
   double y[nBin];
   double istep = (x_h-x_l)/nBin;
   double ymin,ymax;

   double suma = 0;
   double sumb = 0;

   for( int i=0; i<nBin; i++ ){
	x[i] = x_l+istep*i;
	y[i] = exp(-1*func->Eval(x[i]));

	if( i==0 ){ 
	   ymin = y[i]; ymax = y[i]; 
	}else{
	   ymin = min( ymin, y[i] );
	   ymax = max( ymax, y[i] );
	}

	if(x[i]>=0)
	   sumb = sumb+y[i];
   }

   for( int i=0; i<nBin; i++ ){

	if( suma/sumb<0.9 ){ 
	   if(x[i]>=0)
		suma = suma+y[i];
	}else{
	   optx = x[i-1];
	   cout<<" Square   : "<<suma/sumb<<endl;
	   cout<<" Uplimit  : "<<optx<<endl;
	   break;
	}
   }
   
   // Set graph and histogram of confidence interval
   TGraph *grCL = new TGraph( nBin, x, y );
   int nPoint = 1000;
   TH1D *hist = new TH1D(Form("hist_%s",picname),"",nPoint,0,optx*scale);

   for( int i=0; i<nBin; i++ ){
	double tmpx = (i+0.5)*optx/nPoint;
	double tmpy = grCL->Eval(tmpx);
	hist->SetBinContent(i+1,tmpy);
   }
   hist->SetFillStyle(1001);
   hist->SetLineColor(kRed-7);
   hist->SetFillColor(kRed-7);

   // Scale the function
   for( int i=0; i<nBin; i++ ){
	x[i] = x[i]*scale;
   }

   // Set the graph, graph1 & graph2 for projection & full scan plot
   TGraph *graph1 = new TGraph(nBin,x,y);
   TGraph *graph2 = new TGraph(nBin,x,y);

   graph1->SetName("graph1");
   graph1->SetTitle("");
   graph1->SetLineColor(kBlue);
   graph1->SetLineWidth(3);
   
   graph2->SetName("graph2");
   graph2->SetLineColor(kBlue);
   graph2->SetLineWidth(2);

   // Set the histograms for graph style
   TH1F *grset1 = new TH1F("grset1","",nBin,x_l*scale,x_h*scale);
   TH1F *grset2 = new TH1F("grset2","",nBin,x_l*scale,x_h*scale);
   
   TAxis *grsetX1 = grset1->GetXaxis();
   TAxis *grsetY1 = grset1->GetYaxis();
   double xmin = grsetX1->GetXmin();
   double xmax = grsetX1->GetXmax();
   
   int fontnum = 132;
   grset1->SetMinimum(ymin*0);
   grset1->SetMaximum(ymax*1.07);
   //grset1->GetXaxis()->SetTitle("\\mathcal{A}");
   grsetX1->SetTitle("#font[132]{#it{B}}#font[132]{(#it{B^{0}#rightarrowJ/#psi#phi})(10^{-8})}");
   grsetX1->SetNdivisions(510);
   grsetX1->SetLabelOffset(0.01);
   grsetX1->SetLabelSize(0.06);
   grsetX1->SetTitleSize(0.072);
   grsetX1->SetTitleOffset(0.95);
   grsetX1->SetTitleFont(fontnum);
   grsetX1->SetRangeUser(0,xmax);
   
   grsetY1->SetTitle("#lambda");
   grsetY1->SetNdivisions(510);
   grsetY1->SetLabelOffset(0.01);
   grsetY1->SetLabelSize(0.06);
   grsetY1->SetTitleSize(0.072);
   grsetY1->SetTitleOffset(0.95);
   grsetY1->SetTitleFont(fontnum);
   grsetY1->SetLabelFont(fontnum);
   grsetY1->SetRangeUser(0,hist->GetMaximum());
   graph1->SetHistogram(grset1);
   
   grset2->GetXaxis()->SetNdivisions(510);
   grset2->GetYaxis()->SetNdivisions(510);
   graph2->SetHistogram(grset2);

   // Set the leg
   TLegend *leg = new TLegend(0.60,0.70,0.85,0.85,"#font[132]{LHCb}");
   leg->SetBorderSize(0);
   leg->SetTextFont(132);
   leg->SetTextSize(0.04);
   leg->SetFillColor(0);
   leg->AddEntry(hist, "Confidence interval", "F");

   // Redraw the axis
   ymin = grset1->GetMinimum();
   ymax = grset1->GetMaximum();
   TGaxis *Xaxis = new TGaxis(0,0,xmax,0,0,xmax,grset1->GetXaxis()->GetNdivisions(),"U");
   TGaxis *Yaxis = new TGaxis(0,ymin,0,hist->GetMaximum(),ymin,grset1->GetMaximum(),hist->GetYaxis()->GetNdivisions(),"U");

   // Draw the projection of plot
   TCanvas *pic1 = new TCanvas(Form("pic1_%s",picname),"",800,600);
   pic1->cd();
   gPad->SetTopMargin(0.10);
   gPad->SetPad(0.02,0.04,0.98,0.97);
   grset1->Draw();
   hist->Draw("same");
   graph1->Draw("sameL");
   Xaxis->Draw("same");
   Yaxis->Draw("same");
   leg->Draw("same");

   // Draw the full scan plot
   Xaxis = new TGaxis(xmin,0,xmax,0, xmin,xmax,grsetX1->GetNdivisions(),"U");
   Yaxis = new TGaxis(xmin,ymin,xmin,ymax,ymin,ymax,grsetY1->GetNdivisions(),"U");
   
   TPad* pad1 = new TPad("pad1","",0.57,0.40,0.90,0.70);
   pad1->cd();
   pad1->SetTopMargin(0.10);
   grset2->Draw();
   hist->Draw("same");
   graph2->Draw("sameL");
   Xaxis->Draw("same");
   Yaxis->Draw("same");
   
   pic1->cd();
   pad1->Draw("same");

   if( saveplot ) Printpic2( pic1, picname, 2 );

   return optx*scale;
}
