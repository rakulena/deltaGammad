#include "RooSaveFitPlot.C"

void GaussFit(
	const char *tree,
	const char *treecut,
	const char *varname,
	const char *XTitle, 
	const char *YUnit,
	const char *picname,
	double fl, // scale factor of low  limit
	double fh, // scale factor of high limit
	const int nBin,
	double muval[2],
	bool blind = 0,
	bool dgauss = 0
	){

   // Set the tree
   TChain *chain = new TChain();
   chain->Add( tree );

   TTree *seltree = chain->CopyTree( treecut );
   cout<<treecut<<endl;
   
   double var_val;
   seltree->SetBranchStatus( "*",0 );
   seltree->SetBranchStatus( varname,1 );
   seltree->SetBranchAddress( varname, &var_val );

   // Set the fit range
   double v_l = seltree->GetMinimum( varname )*fl;
   double v_h = seltree->GetMaximum( varname )*fh;
   v_l = v_l-fabs(v_h-v_l)*0.1;
   v_h = v_h+fabs(v_h-v_l)*0.1;
   
   // Set the randon value in [ 2*v_l, 2*v_h ]
   double RndX = 0;
   if( blind ){
	TRandom3 *dummy= new TRandom3( v_l );
	RndX = dummy->Uniform(v_l,v_h)*5;

	v_l = v_l+RndX;
	v_h = v_h+RndX;
	cout<<RndX<<endl;
   }

   // Set the PDF
   RooRealVar *var  = new RooRealVar(varname,"",v_l,v_h);
   RooRealVar *mean = new RooRealVar("mean","",(v_l+v_h)/2.,v_l,v_h);
   RooRealVar *sigma1 = new RooRealVar("sigma1","",(v_h-v_l)/5.,0,(v_h-v_l));
   RooRealVar *sigma2 = new RooRealVar("sigma2","",(v_h-v_l)/5.,0,(v_h-v_l));
   RooRealVar *frac = new RooRealVar("frac","",0.5,0,1);

   RooGaussian *gauss1 = new RooGaussian("gauss1","",*var,*mean,*sigma1);
   RooGaussian *gauss2 = new RooGaussian("gauss2","",*var,*mean,*sigma2);
 
   RooAbsPdf *fitpdf = gauss1;
   if( dgauss ){
	fitpdf = new RooAddPdf("fitpdf","",RooArgSet(*gauss1,*gauss2),RooArgSet(*frac));
   }

   RooDataSet *data = new RooDataSet("data","",RooArgSet(*var));

   for( int i=0; i<seltree->GetEntries(); i++ ){
	seltree->GetEntry(i);
	*var = var_val+RndX;
	data->add( RooArgSet(*var) );
   }

   //RooDataSet *data = new RooDataSet("data","",seltree,RooArgSet(*var),0,0);
   cout<<"========================================="<<endl;
   cout<<" DataSet : "<<endl;
   data->Print();
   cout<<"========================================="<<endl<<endl;

   RooFitResult *fitres;
   for( int i=0; i<3; i++ ){
      fitres = fitpdf->fitTo( *data, NumCPU(2), Save() );
      double edm = fitres->edm();
      if (edm<1e-5 ) break;
   }

   double wd = sigma1->getVal();
   double wdErr = sigma1->getError();

   if( dgauss ){
	double f1 = frac->getVal();
	double wd1 = sigma1->getVal();
	double wd2 = sigma2->getVal();
	double wdErr1 = sigma1->getError();
	double wdErr2 = sigma2->getError();

	wd = sqrt( f1*wd1*wd1+(1-f1)*wd2*wd2 );
	wdErr = pow(wd,-1)*sqrt(pow(2*f1*wd1*wdErr1,2)+pow(2*(1-f1)*wd2*wdErr2,2));
   }

   muval[0] = mean->getVal();
   muval[1] = mean->getError();
   muval[2] = wd;
   muval[3] = wdErr;
   
   RooPlot *vframe = var->frame( Bins(nBin) );
   data->plotOn(vframe,MarkerSize(0.8),MarkerColor(kBlack));
   fitpdf->plotOn(vframe,Name("chi_all"),LineWidth(3));
   data->plotOn(vframe,Name("chi_fit"),MarkerSize(0.8),MarkerColor(kBlack));
   
   // Get decimal digits
   double binwidth = (v_h-v_l)/nBin;

   int ndigit = 0;
   double tmpval = 1;
   while( fabs(tmpval) <=1 ){
	tmpval = binwidth*pow(10,ndigit);
	ndigit++;
   }

   // Set TLatex
   string str_i = to_string(ndigit);
   string format = "#splitline{#mu = %."+str_i+"f #pm %."+str_i+"f}{#sigma = %."+str_i+"f #pm %."+str_i+"f}";
   string name_fit = Form( format.c_str(), mean->getVal(), mean->getError(), wd, wdErr );

   TLatex *mytex = new TLatex(0.23,0.75,name_fit.c_str());

   mytex->SetTextFont(132);
   mytex->SetTextSize(0.05);
   mytex->SetLineWidth(2);
   mytex->SetNDC();

   // Set logo
   TPaveText *logo = new TPaveText( 0.23, 0.83, 0.35, 0.90, "BRNDC" );
   logo->AddText("");
   //logo->AddText("#font[132]{LHCb}");


   format = "Candidates / ( %."+str_i+"f \%s )";
   const char* YTitle = Form( format.c_str(), binwidth, YUnit );

   vframe->addObject(mytex);
   RooSaveFitPlot( data, fitpdf, var, vframe, logo, XTitle, YTitle, picname, 0, 0, 1);

   double chi2_ndof5 = vframe-> chiSquare("chi_all","chi_fit",5);
   double chi2_ndof9 = vframe-> chiSquare("chi_all","chi_fit",9);
   cout<<"========================================="<<endl;
   cout<< "chiSquare_NDOF(5) =" << chi2_ndof5 << endl;
   cout<< "chiSquare_NDOF(9) =" << chi2_ndof9 << endl;
   cout<<"========================================="<<endl;

}
