#include "../inc/Printpic.C"
#include "../inc/GetPhsp.C"

Color_t color[10] = { kBlack, kRed, kGreen, kBlue, kPink+6, kViolet+2, kOrange, kMagenta-1, kCyan+2, kViolet+7 };
Int_t markstyle[10] = { 20, 21, 22, 23, 27, 28, 2, 3, 4, 5 };

void SetHistStyle(
      int i,
	TH1D *hist1,
	double ymin,
	double ymax,
	const char *XTitle,
	const char *YTitle
	)   
{
   hist1->Scale(10./hist1->Integral(1,40));

   if( i==0 ){
      if( ymax < 0 ){ 
         ymax = hist1->GetMaximum()*1.2; 
      }
      hist1->SetMinimum( ymin );
      hist1->SetMaximum( ymax );
      hist1->SetXTitle( XTitle );
      hist1->SetYTitle( YTitle );
   
      hist1->GetYaxis()->SetTitleOffset(1.0);
      hist1->GetXaxis()->SetTitleOffset(1.1);
   }

}

TCanvas *DefinePic(
      const char *picname,
	bool logdec
	)
{

   TCanvas *pic = new TCanvas(picname,"",800,560) ;
   pic->cd();
   gPad->SetTopMargin(0.06);
   gPad->SetLeftMargin(0.18);
   gPad->SetRightMargin(0.03);
   gPad->SetPad(0.0,0.03,0.98,0.97);
   gPad->SetLogy( logdec );
   
   return pic;
}

void comp_accp_mva(
	int year = 2016
	)
{
   gROOT->ProcessLine(".x ../inc/lhcbStyle.C");

   string intree1 = Form("/lzufs/user/zhanghy/Sample/Train/Bd2JpsiKshort_mc_%i_BDT.root/DecayTree",year);

   char varname[] = "BDT";
   
   //string weight1 = "phsp(m_hh_true)";
   string weight2 = "1./exp(-1/1.519*Bd_ConstJpsi_tau)";
   string cut1 = "abs(Bd_JpsiConst_M-5279.65)<30)";
   
   string prefix = "comp";

   const int n = 2;
   double tpoint[n] = {0,0.35 };

   TH1D *h_time[n];

   // Fill and set histograms 
   TChain *seltree = new TChain();
   seltree->Add( intree1.c_str() );
   
   int nbin1 = 50;
   double t_l = 0.3;
   double t_h = 10.;
   
   string YTitle1 = "Efficiency (a.u.)";
  
   TLegend *leg = new TLegend(0.60,0.30,0.80,0.55);
   leg->SetTextFont(132);
   leg->SetTextSize(0.05);
   leg->SetBorderSize(0);
   leg->SetFillColor(0);

   for( int i=0; i<n; i++ ){
   
      string selcut1 = Form("%s*(%s>%f)*(Jpsi_Hlt1DiMuonHighMassDecision_TOS==1)", weight2.c_str(), varname, tpoint[i]);

      // Draw the plots
      h_time[i] = new TH1D(Form("%s_h_time%i_%i",prefix.c_str(),i,year),"",nbin1,t_l,t_h);
      
      seltree->Project(h_time[i]->GetName(),"Bd_ConstJpsi_tau",selcut1.c_str());
      SetHistStyle( i, h_time[i], 1e-4, -1, "#it{t} [ps]", YTitle1.c_str() );


      if( i==0 ){
         leg->AddEntry(h_time[i],Form("w/o %s",varname),"PEL");
      }else{
         leg->AddEntry(h_time[i],Form("%s> %.3f",varname,tpoint[i]),"PEL");
      }

      h_time[i]->SetMarkerStyle( markstyle[i] );
      h_time[i]->SetMarkerColor( color[i] );
      h_time[i]->SetLineColor( color[i] );
   }

   // Draw plots
   TCanvas *pic1 = DefinePic( Form("time_%i",year), 0);

   TPaveText *logo = new TPaveText( 0.22,0.80,0.40,0.90, "BRNDC" );
   logo->AddText("LHCb");
   logo->SetShadowColor(0);
   logo->SetFillStyle(0);
   logo->SetBorderSize(0);
   logo->SetTextAlign(12);
   logo->SetTextSize(0.05);
   logo->SetTextFont(132);

   for( int i=0; i<n; i++ ){
      pic1->cd(); h_time[i]->Draw("same"); logo->Draw("same"); leg->Draw("same");
   }

   if( year==-1 ){
      Printpic( pic1, Form("output/%s_accp_mva_time_run2",prefix.c_str()), 1 );
   }else{
      Printpic( pic1, Form("output/%s_accp_mva_time_%i_ks",prefix.c_str(),year), 1 );
   }

}

void hist_comp_accp_mva_ks(
	){

   //comp_accp_mva( -1 );
   comp_accp_mva( 2016 );
   //comp_accp_mva( 2017 );
   //comp_accp_mva( 2018 );

   exit(0);

}
