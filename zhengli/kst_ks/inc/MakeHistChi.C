
void MakeHistChi(
	TH1D *hist1,
	TH1D *hist2,
	TH1D *hist3
	)
{
   double sum_chi2 = 0;
   for( int i=0; i<hist1->GetNbinsX(); i++ ){
	double err2_h1 = pow( hist1->GetBinError(i+1), 2 );
	double err2_h2 = pow( hist2->GetBinError(i+1), 2 );
	double err = sqrt( err2_h1+err2_h2 );
	double chi = 0.;
	double chierr = 1.;
	if( err>0 ){
	   chi = ( hist1->GetBinContent(i+1)-hist2->GetBinContent(i+1) )/err;
	   sum_chi2 = sum_chi2+chi*chi;
	}
	hist3->SetBinContent(i+1,chi);
	hist3->SetBinError(i+1,chierr);
   }
   cout<<"============================== "<<endl;
   cout<<" chi2/ndof of "<<hist3->GetXaxis()->GetTitle()<<" : "<<sum_chi2/(hist1->GetNbinsX()-1)<<endl;
   cout<<"============================== "<<endl;

}


void SetHistChi(
	TH1D *hist1,
	TH1D *hist2,
	TH1D *hist3,
	double scale,
	double ymin,
	double ymax,
	const char *XTitle,
	const char *YTitle
	)   
{

   // Transform the Yaxis : Events -> Events/Binwidth
   //for( int i=0; i<hist1->GetNbinsX(); i++ ){
   //   hist1->SetBinContent( i+1,hist1->GetBinContent(i+1)/hist1->GetBinWidth(i+1) );
   //   hist2->SetBinContent( i+1,hist2->GetBinContent(i+1)/hist2->GetBinWidth(i+1) );
   //   hist3->SetBinContent( i+1,hist3->GetBinContent(i+1)/hist3->GetBinWidth(i+1) );
   //}

   if( scale < 0 ){ scale = hist1->Integral(); }
   if( ymax < 0 ){ 
	ymax = hist1->GetMaximum()*1.17; 
   }

   hist1->Sumw2(); 
   hist2->Sumw2();
   hist1->Scale( scale/hist1->Integral() );
   hist2->Scale( scale/hist2->Integral() );  
   hist1->SetMinimum( ymin );
   hist1->SetMaximum( ymax );

   hist1->SetYTitle( YTitle );
   hist2->SetMarkerColor(kBlue);    
   hist2->SetLineColor(kBlue);    
   hist2->SetLineWidth(2);

   hist3->SetMinimum(-5);
   hist3->SetMaximum( 5);
   hist3->SetXTitle( XTitle );
   hist3->GetXaxis()->SetTitleSize(0.2);
   hist3->GetYaxis()->SetTitleSize(0.2);
   hist3->GetYaxis()->SetTitleOffset(0.18);
   hist3->GetXaxis()->SetTitleOffset(0.75);
   hist3->GetXaxis()->SetLabelSize(0.15);
   hist3->GetYaxis()->SetLabelSize(0.15);
   hist3->GetYaxis()->SetNdivisions(505);

   MakeHistChi( hist1, hist2, hist3 );

}
