#include "headfile.h"
#include "Printpic.C" 
#include "InputGraph.C"
#include "ShadeTF1.C"

void Cali_var_relation(
	const char *iffile,
	const char *offile,
	const char *picname,
	const char *picfile,
	const char *XTitle,
	const char *YTitle,
	const char *funcmat,
	const char *parname,
	int nBin,
	double XUnit,
	double YUnit,
	bool bandplot = 0
	)
{

   const int num = nBin;
   double x[num], x_l[num], x_h[num];
   double y[num], y_l[num], y_h[num];
   InputGraphTex( iffile, x, x_l, x_h, y, y_l, y_h, XUnit, YUnit);

   // Do the calibration and output fit parameters
   //----------------------------------------------------------   
   // graph1 for the plot
   // graph2 for the fit
   //----------------------------------------------------------   
   TGraphAsymmErrors *graph1 = new TGraphAsymmErrors(num,x,y,x_l,x_h,y_l,y_h);
   TGraphAsymmErrors *graph2 = new TGraphAsymmErrors(num,x,y,0,0,y_l,y_h); 

   graph1->SetName("graph_nfit");
   graph2->SetName("graph_fit");

   double xmin = graph1->GetXaxis()->GetXmin();
   double xmax = graph1->GetXaxis()->GetXmax();
 
   TF1 *func = new TF1("fitfunc",funcmat,xmin,xmax);
   graph2->Fit("fitfunc","E");
   gMinuit->mnmatu(1);
   func->SetLineColor(2);
   func->SetLineWidth(2);

   ofstream ofpar( offile );
   
   const int nPar = func->GetNumberFreeParameters();
   for(int i=0; i<nPar; i++){
	double val = func->GetParameter(i);
	double err = func->GetParError(i);
	cout<<"  p"<<i<<" = "<<val<<" +/- "<<err <<endl;
	ofpar
	   <<" double "<<parname<<i<<" = "<<val<<" ;"
	   <<" double "<<parname<<i<<"err = "<<err<<" ;"<<endl;
   }
   ofpar.close();

   double chi2ndof = ( func->GetChisquare() )/( func->GetNDF() );
   cout<<endl;
   cout<<"=============================="<<endl;
   cout<<" CHI2NDOF =  "<< chi2ndof<<endl;
   cout<<"=============================="<<endl;

	
   TGraph *grshade[nPar];
   if( bandplot ){

	// Obtain graph shades at 68% CL
	// The correlations bettween parameters are not included

	TF1 *grfunc[2*nPar];
	for( int i=0; i<2*nPar; i++ ){
	   grfunc[i] = new TF1(Form("grfunc_%02i",i),funcmat,xmin,xmax);
	   grfunc[i]->SetFillColor(kYellow-6);
	   grfunc[i]->SetFillStyle(1001);
	}

	for(int i=0; i<nPar; i++){
	   for( int j=0; j<nPar; j++ ){

		double parj1 = func->GetParameter(j);
		double parj2 = func->GetParameter(j);
		if( i==j ){
		   parj1 = parj1+func->GetParError(j); 
		   parj2 = parj2-func->GetParError(j); 
		   //if( func->GetParError(j) > parj1 ){
		   //   parj1 = 0;
		   //   parj2 = 0;
		   //}
		}
		grfunc[2*i]->SetParameter(j,parj1);
		grfunc[2*i+1]->SetParameter(j,parj2);

	   }

	   grshade[i] = ShadeTF1( grfunc[2*i], grfunc[2*i+1], func );
	   grshade[i]->SetMarkerColor(kBlue);
	}
   }

   // Draw and save the plots
   TCanvas *pic = new TCanvas(picname,"",800,600);

   pic->cd();
   gPad->SetLeftMargin(0.15);
   
   graph1->SetMinimum( graph1->GetYaxis()->GetXmin()-abs(graph1->GetYaxis()->GetXmin())*0.2 );
   graph1->SetMaximum( graph1->GetYaxis()->GetXmax()+abs(graph1->GetYaxis()->GetXmax())*0.1 );
   graph1->SetMarkerStyle(7);
   graph1->SetMarkerSize(2);
   graph1->SetMarkerColor(1);
   graph1->SetLineColor(1);
   graph1->SetLineWidth(1);
   graph1->GetXaxis()->SetTitle( XTitle );
   graph1->GetYaxis()->SetTitle( YTitle );
   graph1->GetYaxis()->SetTitleOffset(1);
  
   graph1->Draw("AP");
   if( bandplot ){
	for( int i=0; i<nPar; i++ ){
	   grshade[i]->Draw("fsame");
	}
   }
   func->Draw("same");
   graph1->Draw("Psame");
   Printpic(pic,picname,1); // Print the pictures

   // Save the graphs
   TFile *rootfile = new TFile(picfile,"recreate");
   rootfile->cd();
   graph1->Write();
   graph2->Write();
   rootfile->Close();

}
