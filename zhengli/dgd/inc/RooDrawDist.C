#include <algorithm>
#include "Printpic.C"

void RooDrawOneDist( 
	TChain *chain,
	const char *TreeCut,
	const char *VarName,
	const char *wName, 
	const char *XTitle,
	TH1D  *hist,
	double unit
	)
{   

   string hname = hist->GetName();
   string tmpcut = TreeCut;

   TCanvas *tmppic = new TCanvas();
   tmppic->cd();
   if( tmpcut=="" ){
	chain->Project( hname.c_str(), Form("%s*%lf", VarName, unit), wName,"" );
   }else{
	chain->Project( hname.c_str(), Form("%s*%lf", VarName, unit), Form("%s*(%s)",wName,TreeCut),"" );
   }

   // Setting of histograms
   hist->SetMarkerStyle(8);
   hist->SetMarkerSize(1);
   hist->SetMarkerColor(4);
   hist->SetLineColor(4);
   hist->SetLineWidth(2);
   hist->GetXaxis()->SetTitle( XTitle );
   hist->GetXaxis()->SetTitleFont( 132 );
   hist->GetXaxis()->SetTitleSize(0.06);
   hist->GetXaxis()->SetTitleOffset(1.15);

   delete tmppic;

}

void RooDrawTwoDist( 
	TChain *chain1, 
	TChain *chain2, 
	const char *TreeCut1,
	const char *TreeCut2,
	const char *VarName1,
	const char *VarName2,
	const char *wName1, 
	const char *wName2,
	const char *legname1,
	const char *legname2,
	const char *XTitle,
	int    nNum,
	int    nBin,
	double val_l,
	double val_h,
	double unit,
	int DeciLogy,
	int DeciOnePic
	)
{   

   char hname1[200]; 
   char hname2[200]; 
   sprintf(hname1,"hist1_var%i",nNum);
   sprintf(hname2,"hist2_var%i",nNum);

   TH1D *hist1 = new TH1D(hname1,"",nBin,val_l*unit,val_h*unit);
   TH1D *hist2 = new TH1D(hname2,"",nBin,val_l*unit,val_h*unit);

   TCanvas *pic;
   if(DeciOnePic==1){
	pic = new TCanvas("pic","",800,600);
	pic->cd();
   }

   string tmpcut1 = TreeCut1;
   string tmpcut2 = TreeCut2;

   if( tmpcut1=="" ){
	chain1->Project( hname1, Form("%s*%lf", VarName1, unit), wName1,"" );
   }else{
	chain1->Project( hname1, Form("%s*%lf", VarName1, unit), Form("%s*(%s)",wName1,TreeCut1),"");
   }
   
   if( tmpcut2=="" ){
	chain2->Project( hname2, Form("%s*%lf", VarName2, unit), wName2,"same" );
   }else{
	chain2->Project( hname2, Form("%s*%lf", VarName2, unit), Form("%s*(%s)",wName2,TreeCut2),"same");
   }

   hist1->Scale(5./hist1->Integral());
   hist2->Scale(5./hist2->Integral());
   hist1->Sumw2(0);
   hist2->Sumw2(0);
  
   // Set the min, max value of histogram
   double maxval = max( hist1->GetMaximum(),hist2->GetMaximum() )*1.09;
   double minval = min( hist1->GetMinimum(),hist2->GetMinimum() )*0.1;
   
   hist1->SetMaximum(maxval);
   
  // if( DeciLogy==1 ){
  //    if( minval <= 0. ) minval = 1e-3;
  //    hist1->SetMinimum( minval );
  // }else{
  //    hist1->SetMinimum(0.0);
  // }

   // Setting of histograms
   if( DeciLogy==1 ) gPad->SetLogy();
   hist1->SetMarkerStyle(7);
   hist1->SetMarkerSize(1);
   hist1->SetMarkerColor(4);
   hist1->SetLineColor(4);
   hist1->SetFillColor(4);
   hist1->SetFillStyle(3004);
   hist1->SetLineWidth(2);
   hist1->GetXaxis()->SetTitle( XTitle );
   hist1->GetXaxis()->SetTitleFont( 132 );
   hist1->GetXaxis()->SetTitleSize(0.05);
   hist1->GetXaxis()->SetTitleOffset(1.15);

   hist2->SetMarkerStyle(7);
   hist2->SetMarkerSize(1);
   hist2->SetMarkerColor(2);
   hist2->SetFillStyle(3005);
   hist2->SetLineColor(2);
   hist2->SetFillColor(2);
   hist2->SetLineWidth(2);

   hist1->Draw();
   hist2->Draw("same");

   // Draw the legend
   string tmplegname1 = legname1;
   string tmplegname2 = legname2;
   
   if( tmplegname1!="" || tmplegname2!="" ){
	
	TLegend* leg = new TLegend(0.30,0.70,0.52,0.86);
	leg->SetTextFont(132);
	leg->SetTextSize(0.06);
	leg->SetBorderSize(0);
	leg->SetFillColor(0);

	leg->AddEntry(hist1, legname1,"F");
	leg->AddEntry(hist2, legname2,"F");

	leg->Draw("same");
   }

   if(DeciOnePic){
	Printpic( pic, VarName1, 2 );
   }

}

