#include "../inc/headfile.h"
#include "../inc/RooDrawDist.C"
#include "./input/sele_optdef.h"

void hist_sele_train(
	int year = 2016 
	)
{

   gROOT->ProcessLine(".x ../inc/lhcbStyle.C");
   //char varslist_path[] = "./input/varlist_sele_gbw2_kst";//kst
   char varslist_path[] = "./input/varlist_sele_gbw2_ks";//ks

   TChain *chain1 = new TChain();
   TChain *chain2 = new TChain();
   chain1->Add( Form( sele_tree2, year ) );
   chain2->Add( Form( sele_tree3, year ) );

   char cut1[] = "Bd_ConstJpsi_M>5220&&Bd_ConstJpsi_M<5330";
   char cut2[] = "Bd_ConstJpsi_M>5330&&Bd_ConstJpsi_M<5450";//ks
   //char cut2[] = "Bd_ConstJpsi_M>5330&&Bd_ConstJpsi_M<5350";//kst
   char wname1[] = "1";
   char wname2[] = "1";


   // Input variables' name
   vector<string> varname1; varname1.clear();
   vector<string> xname;    xname.clear();
   vector<int>    logy;     logy.clear();
   vector<int>    nbin;     nbin.clear();
   vector<double> val_l;    val_l.clear();
   vector<double> val_h;    val_h.clear();
   vector<double> unit;     unit.clear();

   ifstream input_tvl(varslist_path);
   while(!input_tvl.eof()){
	string tmpname1;
	string tmpxname;
	int    tmplogy;
      int    tmpnbin;
	double tmpval_l;
	double tmpval_h;
	double tmpunit;
	input_tvl >>tmpname1 >>tmpxname >>tmplogy >>tmpnbin >>tmpval_l >>tmpval_h >>tmpunit;

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

   const int runnum = num-1; 
   int initnum = 0;

   TCanvas *pic1 = new TCanvas("pic1","",2000,1500);
   pic1->Divide(3,3);

   //for( int i=initnum; i<1; i++){
   for( int i=initnum; i<runnum; i++){

      pic1->cd(i+1);
	char cvar1[200];
	char xTitle[200];
	sprintf( cvar1, "%s", varname1[i].c_str() ); // converted varname
	sprintf( xTitle, "%s", xname[i].c_str() );
	cout<<" "<<cvar1<<"  "<<logy[i]<<"  "<<val_l[i]<<" "<<val_h[i]<<" "<<unit[i]<<endl;

	if( i==1 ){
         RooDrawTwoDist( chain1, chain2, cut1, cut2, cvar1, cvar1, wname1, wname2, "signal", "background", xTitle, i, 40, val_l[i], val_h[i], unit[i], logy[i], 0);
	}else{                                 
         RooDrawTwoDist( chain1, chain2, cut1, cut2, cvar1, cvar1, wname1, wname2, "", "", xTitle, i, 40, val_l[i], val_h[i], unit[i], logy[i], 0);
	}

   }
   //pic1->Print( Form("output/comp_sele_train_%i_kst.png",year) );//kst
   pic1->Print( Form("output/comp_sele_train_%i_ks.png",year) );//ks

}

