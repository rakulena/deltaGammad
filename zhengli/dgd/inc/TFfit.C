
// Fit the histogram
//---------------------------------------

double TFfit( 
	TH1D *hist, 
	const char *funcname,
	int   LCol
	)
{
   hist->Fit(funcname,"E");
   gMinuit->mnmatu(1);

   TF1 *func = (TF1 *)hist->GetFunction(funcname);
   func->SetLineColor(LCol);
   func->SetLineWidth(2);

   double chi2 = func->GetChisquare();
   double chi2ndof = chi2/(func->GetNDF());
   cout<<endl;
   cout<<"=============================="<<endl;
   cout<<" CHI2NDOF =  "<< chi2ndof<<endl;
   cout<<"=============================="<<endl;

   return chi2ndof;
}

TFitResultPtr TFfit( 
	TH1D *hist, 
	const char *funcname
	)
{
   TFitResultPtr fitres = hist->Fit(funcname,"SE");
   gMinuit->mnmatu(1);
   fitres->Print();
   fitres->SetName("fitres");

   TF1 *func = (TF1 *)hist->GetFunction(funcname);
   func->SetLineColor(4);
   func->SetLineWidth(2);

   double chi2 = func->GetChisquare();
   double chi2ndof = chi2/(func->GetNDF());
   cout<<endl;
   cout<<"=============================="<<endl;
   cout<<" CHI2NDOF =  "<< chi2ndof<<endl;
   cout<<"=============================="<<endl;

   return fitres;

}

double TFfit( 
	TH1D *hist, 
	const char *funcname,
	const char *parname,
	const char *fitparpath,
	int digitnum
	)
{
   hist->Fit(funcname,"E");
   gMinuit->mnmatu(1);

   TF1 *func = (TF1 *)hist->GetFunction(funcname);
   func->SetLineColor(4);
   func->SetLineWidth(2);

   double chi2 = func->GetChisquare();
   double chi2ndof = chi2/(func->GetNDF());
   cout<<endl;
   cout<<"=============================="<<endl;
   cout<<" CHI2NDOF =  "<< chi2ndof<<endl;
   cout<<"=============================="<<endl;

   ofstream ofpar( fitparpath );
   for(int i=0; i<func->GetNumberFreeParameters(); i++){
	double val = func->GetParameter(i);
	double err = func->GetParError(i);
	cout<<"  p"<<i<<" = "<<val<<" +/- "<<err <<endl;
	ofpar
	   <<setiosflags(ios::fixed)<<setprecision( digitnum )
	   <<" double "<<parname<<i<<" = "<<val<<" ;"
	   <<" double "<<parname<<i<<"err = "<<err<<" ;"<<endl;
   }
   ofpar.close();

   return chi2ndof;
}
