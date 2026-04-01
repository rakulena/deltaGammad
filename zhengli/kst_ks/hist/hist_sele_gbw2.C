#include "../inc/headfile.h"
#include "../inc/RooDrawDist.C"
#include "../inc/MakeHistChi.C"
#include "SetCompHist.C"
#include "./input/sele_optdef.h"

void hist_sele_gbw2(
	int year = 2017
	)
{

   gROOT->ProcessLine(".x ../inc/lhcbStyle.C");

   char varslist_path[] = "./input/varlist_sele_gbw2_ks";//ks
   //char varslist_path[] = "./input/varlist_sele_gbw2_kst";//kst
   TChain *chain1 = new TChain();
   TChain *chain2 = new TChain();
   chain1->Add( Form( sele_tree1, year ) );
   chain2->Add( Form( sele_tree3, year ) );

   cout<<Form( sele_tree1, year )<<endl;
   cout<<Form( sele_tree3, year )<<endl;

   char cut[] = "Bd_ConstJpsi_M>5220&&Bd_ConstJpsi_M<5330";
   char wname1[] = "1";
   char wname2[] = "1";
   char wname3[] = "1";

   // Input variables' name
   vector<string> varname1; varname1.clear();
   vector<string> xname;    xname.clear();
   vector<int>    logy;     logy.clear();
   vector<int>    nbin;     nbin.clear();
   vector<double> val_l;    val_l.clear();
   vector<double> val_h;    val_h.clear();
   vector<double> unit;     unit.clear();

   ifstream input_tvl(varslist_path);
    //cout<<"check1"<<endl;
   while(!input_tvl.eof()){
	string tmpname1;
	string tmpxname;
	int    tmplogy;
	int    tmpnbin;
	double tmpval_l;
	double tmpval_h;
	double tmpunit;
	input_tvl >>tmpname1 >>tmpxname >>tmplogy >>tmpnbin >>tmpval_l >>tmpval_h >>tmpunit;
//cout<<"check2"<<endl;
	varname1.push_back(tmpname1);
	xname.push_back(tmpxname);
	logy.push_back(tmplogy);
	nbin.push_back(tmpnbin);
	val_l.push_back(tmpval_l);
	val_h.push_back(tmpval_h);
	unit.push_back(tmpunit);

   }
   input_tvl.close();

   int num = varname1.size();
   cout<<" Number of varaiables: "<<num-1<<endl;

   const int nevt = num-1;

   TH1D *hist1[nevt];
   TH1D *hist2[nevt];
   TH1D *hist3[nevt];

   TCanvas *pic1 = new TCanvas("pic1","",2000,1500);
   pic1->Divide(3,3);

   TLegend* leg = new TLegend(0.55,0.65,0.75,0.85);
   leg->SetTextFont(132);
   leg->SetTextSize(0.05);
   leg->SetBorderSize(0);
   leg->SetFillColor(0);

   for( int i=0; i<nevt; i++){

	hist1[i] = new TH1D(Form("hist1_var%i",i),"",nbin[i],val_l[i]*unit[i],val_h[i]*unit[i]); 
	hist2[i] = new TH1D(Form("hist2_var%i",i),"",nbin[i],val_l[i]*unit[i],val_h[i]*unit[i]); 
	hist3[i] = new TH1D(Form("hist3_var%i",i),"",nbin[i],val_l[i]*unit[i],val_h[i]*unit[i]); 
	RooDrawOneDist( chain1, "sig_sw", varname1[i].c_str(), wname1, xname[i].c_str(), hist1[i], unit[i] );
	RooDrawOneDist( chain2, "Bd_BKGCAT==0||Bd_BKGCAT==50", varname1[i].c_str(), wname2, xname[i].c_str(), hist2[i], unit[i] );
	RooDrawOneDist( chain2, "gbw", varname1[i].c_str(), wname3, xname[i].c_str(), hist3[i], unit[i] );

	hist1[i]->Scale(1./hist1[i]->Integral());
	hist2[i]->Scale(1./hist2[i]->Integral());
	hist3[i]->Scale(1./hist3[i]->Integral());

      hist1[i]->SetLineColor(kGray);
      hist1[i]->SetFillColor(kGray);
	hist1[i]->SetMarkerSize(0.5);
	hist2[i]->SetLineColor(2);
	hist3[i]->SetLineColor(4);
	hist2[i]->SetMarkerColor(2);
	hist3[i]->SetMarkerColor(4);

	double minval = 0 ;
	double maxval = max( hist1[i]->GetMaximum(),hist2[i]->GetMaximum() );

	TH1D *hist_pull = new TH1D(*hist3[i]);
	SetCompHist( hist1[i], hist3[i], hist_pull, 1, minval, maxval, xname[i].c_str(), "" ); 

	if( logy[i]==1 ){
	   if( minval == 0. || minval<0. ) minval = pow(10,-3.9);
	   hist1[i]->SetMinimum( minval );
	}

	if( i==0 ){
	   leg->AddEntry(hist1[i],"SW Data","F");
	   leg->AddEntry(hist2[i],"MC","L");
	   leg->AddEntry(hist3[i],"GBWeight MC","L");
	}

      pic1->cd(i+1);
	TPad *pad1 = new TPad("pad1","",0.02, 0.25, 0.98, 0.98 );
	pad1->Draw();
	pad1->cd();
	pad1->SetLeftMargin(0.1);
	pad1->SetBottomMargin(0.02);

	if( logy[i]==1 ) pad1->SetLogy();

	hist1[i]->Sumw2(0);
	hist2[i]->Sumw2(0);
	hist3[i]->Sumw2(0);
	hist1[i]->Draw();
	hist2[i]->Draw("same");
	hist3[i]->Draw("same");
	if( i==0 ){ leg->Draw("same"); }

      pic1->cd(i+1);
	TPad *pad2 = new TPad("pad2","",0.02, 0.02, 0.98, 0.25 );
	pad2->SetLeftMargin(0.1);
	pad2->SetTopMargin(0.02);
	pad2->SetBottomMargin(0.4);
	pad2->Draw();
	pad2->cd();

	TLine *pline1 = new TLine(val_l[i]*unit[i], 3,val_h[i]*unit[i], 3);
	TLine *pline2 = new TLine(val_l[i]*unit[i],-3,val_h[i]*unit[i],-3);
	pline1->SetLineStyle(7);
	pline1->SetLineColor(2);
	pline1->SetLineWidth(2);
	pline2->SetLineStyle(7);
	pline2->SetLineColor(2);
	pline2->SetLineWidth(2);
	
      hist_pull->Sumw2(0);
      hist_pull->SetLineWidth(0);
      hist_pull->SetFillStyle(0);
      hist_pull->SetFillColor(kBlack);
      hist_pull->Draw("B");
      pline1->Draw("same");
      pline2->Draw("same");

      cout<<" "<<varname1[i]<<" "<<logy[i]<<" "<<nbin[i]<<" "<<val_l[i]<<" "<<val_h[i]<<" "<<unit[i]<<endl;

   }

   pic1->Print( Form("output/comp_sele_gbw2_%i_ks.png",year) );//ks
   //pic1->Print( Form("output/comp_sele_gbw2_%i_kst.png",year) );//kst
}
