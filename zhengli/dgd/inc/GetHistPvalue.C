
string cal_hist_pvalue(
      TH1D *hpull,
      bool exl_highchi = 0
      ){

   double sum_chi2(0);
   double chi(0);
   int ndof = hpull->GetNbinsX()-1;
   int ncor = 0;

   for( int i=0; i<hpull->GetNbinsX(); i++ ){

      chi = hpull->GetBinContent(i+1);
      if( chi==0 ){ ncor++; };

      // Exclude events at high decay-time region.
      if( exl_highchi ){
         if( abs(chi)>5 ){
            chi=0;
         }
      }

      sum_chi2 += pow( chi, 2 );
   }

   ndof = ndof-ncor;
   double pvalue = TMath::Prob( sum_chi2, ndof );
   string info_chi2 = Form("#splitline{#chi^{2}/ndof = %.0f/%i }{p-value = %.1e}",sum_chi2,ndof,pvalue);

   cout<<" chi2/ndof & p-value : "<<Form("%.0f/%i",sum_chi2,ndof)<<" "<<pvalue<<endl;

   return info_chi2;
}
