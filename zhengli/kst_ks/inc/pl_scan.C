
void pl_scan(
	const char *picname,
	const char *funcname,
	const char *estname,
	RooRealVar *scanvar,
	RooAbsData *scandata,
	RooAbsPdf  *scanpdf,
	double CL,
	int npoint,
	double plot_l,
	double plot_h
	)
{


   string tpic = picname;
   string tfun = funcname;

   RooRealVar *estvar = scanvar;
   estvar->SetName(estname);
   ProfileLikelihoodCalculator pl(*scandata,*scanpdf,RooArgSet(*estvar));
   pl.SetConfidenceLevel( CL ); 
   LikelihoodInterval *interval = pl.GetInterval();

   // print out the iterval on the first Parameter of Interest
   double esti_min = interval->LowerLimit(*estvar);
   double esti_max = interval->UpperLimit(*estvar);
   cout<<"-----------------------------------------"<<endl;
   cout<<"\n90\% interval on "<<estvar->GetName()
	<<" is : ["<< esti_min
	<<", "<< esti_max 
	<<"] "<<endl;
   cout<<"-----------------------------------------"<<endl;

   // make a plot
   cout << "making a plot of the profile likelihood function ....(if it is taking a lot of time use less points or the TF1 drawing option)\n";
   LikelihoodIntervalPlot plot(interval);
   plot.SetNPoints(npoint);  // do not use too many points, it could become very slow for some models

   TCanvas *pic_scan = new TCanvas("pic_pls","",800,600);
   pic_scan->cd();
   plot.SetRange(plot_l,plot_h);
   plot.Draw("tf1");  // use option TF1 if too slow (plot.Draw("tf1")

   pic_scan->Print(Form("./output/%s.C",tpic.c_str()));

   string syscmd1 = Form( "cp ./output/%s.C ./input", tpic.c_str() );
   string syscmd2 = Form( "sed -i 's/{/TF1* %s(){/g' ./input/%s.C", tfun.c_str(), tpic.c_str() );
   string syscmd3 = Form( "sed -i 's/}/   return _PLL_%s; \\n }/g' ./input/%s.C", estname, tpic.c_str() );
   string syscmd4 = Form( "sed -i 's/void %s()//g' ./input/%s.C", tpic.c_str(), tpic.c_str() );
   string syscmd5 = Form( "sed -i 's/_PLL_%s1/_PLL_%s/g' ./input/%s.C", estname, estname, tpic.c_str() );
   //cout<< syscmd1.c_str()<<endl;
   //cout<< syscmd2.c_str()<<endl;
   //cout<< syscmd3.c_str()<<endl;
   //cout<< syscmd4.c_str()<<endl;
   //cout<< syscmd5.c_str()<<endl;

   system( syscmd1.c_str() );
   system( syscmd2.c_str() );
   system( syscmd3.c_str() );
   system( syscmd4.c_str() );
   system( syscmd5.c_str() );

   delete pic_scan;

}
