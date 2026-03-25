#include "InputGraph.C"
#include "Printpic.C"
#include "SetPlotStyle.C"
#include "TFfit.C"

// For OS Data, OS & SS MC, binned calibration
void OS_BinCaliTagEta(
	const char *InputTree,
	const char *TreeCut,
	const char *TagEta,
	const char *TagDec,
	const char *TrueID,
	const char *Weight,
	const char *outname,
	const char *funcmat,
	const char *XTitle,
	const char *YTitle,
	int    nBin,
	double BinPoint[]
    )
{

   // Input data
   TChain *chain = new TChain();
   chain->Add( InputTree );
 
   string midfix;
   string tmpcut = TreeCut;
   if(tmpcut==""){
	midfix = "";
   }else{
	midfix = "&&";
   }

   string Cut1 = Form("%s!=0%s%s",TagDec,midfix.c_str(),TreeCut);
   string Cut2 = Form("%s&&(%s*%s<0)",Cut1.c_str(),TrueID,TagDec);

   cout<<endl;
   cout<<"===================================================="<<endl;
   cout<<" Input data : "<<InputTree<<endl;
   cout<<" Selection  : "<<Cut2<<endl;
   cout<<" Total    Entries : "<<chain->GetEntries()<<endl;
   cout<<" Selected Entries : "<<chain->GetEntries(Cut2.c_str())<<endl;
   cout<<" Use      Weight  : "<<Weight<<endl;
   cout<<"===================================================="<<endl;

   // Define the histograms
   TH1D *hist_ostag = new TH1D("hist_ostag","",nBin,BinPoint);
   TH1D *hist_omega = new TH1D("hist_omega","",nBin,BinPoint);
   hist_ostag->Sumw2();
   hist_omega->Sumw2();

   // Fill the histograms
   chain->Project( hist_ostag->GetName(), TagEta, Form("%s*(%s)",Weight,Cut1.c_str()) );
   chain->Project( hist_omega->GetName(), TagEta, Form("%s*(%s)",Weight,Cut2.c_str()) );

   // Divide the histogram
   TH1D *hist_ratio = new TH1D(*hist_omega);
   TH1D *hist_ratio_nfit = new TH1D(*hist_omega); // Not be fitted
   hist_ratio->Divide( hist_omega,hist_ostag,1.,1.,"B" );
   hist_ratio_nfit->Divide( hist_omega,hist_ostag,1.,1.,"B" );

   // Set the style of histograms
   hist_ratio->SetName("hist_ratio");
   hist_ratio_nfit->SetName("hist_ratio_nfit");
   SetHistStyle( hist_ostag,4,7,1,4,1,2,XTitle,0,0 );
   SetHistStyle( hist_omega,4,7,1,4,1,2,XTitle,0,0 );
   SetHistStyle( hist_ratio,4,7,1,4,1,2,XTitle,0,0.5 );
   SetHistStyle( hist_ratio_nfit,4,7,1,4,1,2,XTitle,0,0.5 );
   hist_ratio->GetYaxis()->SetTitle(YTitle);

   // Fit the hist of ratio and save the fit parameters
   TF1 *poly = new TF1( "func", funcmat, 0., 0.5 );
   TFitResultPtr fitres = TFfit( hist_ratio, "func" );

   // Draw the plot
   TCanvas *pic = new TCanvas( "pic","",0,0,900,600);
   pic->cd();
   hist_ratio->Draw();

   // Save the histograms to root
   TFile *newfile = new TFile( Form("%s.root",outname),"recreate");
   newfile->cd();
   fitres->Write();
   hist_ostag->Write();
   hist_omega->Write();
   hist_ratio->Write();
   hist_ratio_nfit->Write();
   newfile->Close();

   Printpic( pic, outname, 1 );
   
   delete pic;
   delete newfile;
   delete hist_ostag;
   delete hist_omega;
   
}

// For the SS data, binned calibration 
void SS_BinCaliTagEta(
	const char *filepath,
	const char *funcmat,
	const char *outname,
	double ss_aveta,
	int binnum
	)
{

   TFile *newfile = new TFile( Form("%s.root",outname),"recreate");
   
   const int nBin = binnum;
   double x[nBin];
   double y[nBin];
   double x_l[nBin];
   double x_h[nBin];
   double y_l[nBin];
   double y_h[nBin];

   InputGraphTex( filepath, x, x_l, x_h, y, y_l, y_h );

   TCanvas *pic = new TCanvas("pic_grplot","",800,600);
   TGraphAsymmErrors *graph_nofit = new TGraphAsymmErrors(nBin,x,y,x_l,x_h,y_l,y_h);
   
   for( int i=0; i<nBin; i++ ){
	x_l[i] = 0;
	x_h[i] = 0;
   }
   TGraphAsymmErrors *graph = new TGraphAsymmErrors(nBin,x,y,x_l,x_h,y_l,y_h);

   graph->SetName("gr_fit");
   graph_nofit->SetName("gr_nofit");
   graph_nofit->SetMinimum(0);

   char funcname[] = "fitfunc";
   TF1 *func = new TF1(funcname,funcmat,0.,0.5);
   graph->Fit(funcname,"E");
   gMinuit->mnmatu(2);
   graph->GetFunction(funcname)->SetLineColor(4);
   graph->GetFunction(funcname)->SetLineWidth(1);

   graph->SetMinimum(0);
   graph->SetMaximum(0.6);
   graph->SetTitle("");
   graph->GetXaxis()->SetTitle(" #font[132]{#eta_{ss}} ");
   graph->GetYaxis()->SetTitle(" #font[132]{#omega_{ss}} ");
   graph->GetXaxis()->SetTitleSize(0.070);
   graph->GetYaxis()->SetTitleSize(0.070);

   graph->SetMarkerColor(1);
   graph->SetMarkerStyle(7);
   graph->SetMarkerSize(1);
   graph->SetLineColor(4);
   graph->SetLineWidth(1);

   graph_nofit->SetMarkerColor(4);
   graph_nofit->SetMarkerStyle(7);
   graph_nofit->SetMarkerSize(1);
   graph_nofit->SetLineColor(4);

   double chi2ndof = (func->GetChisquare())/(func->GetNDF());

   TLegend *leg = new TLegend(0.60,0.25,0.85,0.55);
   leg->SetTextFont( 132 );
   leg->AddEntry( "Lchi2ndof", Form("#chi^{2}/ndof = %.2lf",chi2ndof), "");
   leg->AddEntry( "Letabar", Form("#bar{#eta} = %.4lf",ss_aveta), "");

   for(int i=0; i<func->GetNumberFreeParameters(); i++){
      double val = func->GetParameter(i);
      double err = func->GetParError(i);
      leg->AddEntry( Form("Lp%i",i), Form("p%i = %.4lf #pm %.4lf",i,val,err), "");
   }

   pic->cd();
   graph->Draw("AP");
   graph_nofit->Draw("Psame");
   leg->Draw("same");

   newfile->cd();
   pic->Write();
   graph->Write();
   graph_nofit->Write();
   newfile->Close();

   Printpic( pic, outname, 1 );

   delete pic;
   delete newfile;

}
