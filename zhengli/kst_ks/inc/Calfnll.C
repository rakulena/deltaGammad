// Calculate sum2/sumw2
//-----------------------------------------------------------
double Calfnll(
	TTree *chain,
	const char *varname,
	const char *vartype
	)
{
   float  fw;
   double dw;
   string tmpvartype = vartype;
   if( tmpvartype == "F" ) chain->SetBranchAddress( varname, &fw);
   if( tmpvartype == "D" ) chain->SetBranchAddress( varname, &dw);

   //chain->SetBranchStatus("*",0);
   //chain->SetBranchStatus(varname,1);
   
   double sumw  = 0.;
   double sumw2 = 0.;
   double weight;

   for( int i=0; i<chain->GetEntries(); i++){
	chain->GetEntry(i);
	if( tmpvartype == "F" ) weight = fw;
	if( tmpvartype == "D" ) weight = dw;
	sumw  = sumw  +weight;
	sumw2 = sumw2 +weight*weight;
   }
   double ratio = sumw/sumw2;
   cout<<"==========================================="<<endl;
   cout<<" "<<"Entries"<<"  "<<"sumw"<<"  "<<"sumw2"<<"  "<<"sumw/sumw2"<<endl;
   cout<<"==========================================="<<endl;
   cout<<" "<<chain->GetEntries()<<" "<<sumw<<" "<<sumw2<<" "<<ratio<<endl;
   cout<<"==========================================="<<endl;
   
   //chain->SetBranchStatus("*",1);

   return ratio;
}

double Calfnll(
	TChain *chain,
	const char *varname,
	const char *vartype
	)
{
   float  fw;
   double dw;
   string tmpvartype = vartype;
   if( tmpvartype == "F" ) chain->SetBranchAddress( varname, &fw);
   if( tmpvartype == "D" ) chain->SetBranchAddress( varname, &dw);
   
   double sumw  = 0.;
   double sumw2 = 0.;
   double weight;
   for( int i=0; i<chain->GetEntries(); i++){
	chain->GetEntry(i);
	if( tmpvartype == "F" ) weight = fw;
	if( tmpvartype == "D" ) weight = dw;
	sumw  = sumw  +weight;
	sumw2 = sumw2 +weight*weight;
   }
   double ratio = sumw/sumw2;
   cout<<"==========================================="<<endl;
   cout<<" "<<"Entries"<<"  "<<"sumw"<<"  "<<"sumw2"<<"  "<<"sumw/sumw2"<<endl;
   cout<<"==========================================="<<endl;
   cout<<" "<<chain->GetEntries()<<" "<<sumw<<" "<<sumw2<<" "<<ratio<<endl;
   cout<<"==========================================="<<endl;

   return ratio;
}

double Calfnll(
	TTree *chain,
	const char *varname
	)
{
   double wgt_l = chain->GetMinimum(varname) ;
   double wgt_h = chain->GetMaximum(varname) ;

   // To include all events, wgt_l(h) are changed to lower(higer) value
   wgt_l = wgt_l-0.05*fabs(wgt_l);
   wgt_h = wgt_h+0.05*fabs(wgt_h);
   
   TH1D *hist1 = new TH1D(Form( "sumw_%s",varname),"",50,wgt_l,wgt_h);
   TH1D *hist2 = new TH1D(Form("sumw2_%s",varname),"",50,wgt_l,wgt_h);

   chain->Project( hist1->GetName(), varname, varname );
   chain->Project( hist2->GetName(), varname, Form("%s*%s",varname,varname) );

   double sumw    = hist1->Integral();
   double sumw2   = hist2->Integral();
   double ratio = sumw/sumw2;
   cout<<"==========================================="<<endl;
   cout<<" "<<"Entries"<<"  "<<"sumw"<<"  "<<"sumw2"<<"  "<<"sumw/sumw2"<<endl;
   cout<<"==========================================="<<endl;
   cout<<" "<<chain->GetEntries()<<" "<<sumw<<" "<<sumw2<<" "<<ratio<<endl;
   cout<<"==========================================="<<endl;

   delete hist1;
   delete hist2;
   return ratio;
}

double Calfnll(
	TChain *chain,
	const char *varname
	)
{
   double wgt_l = chain->GetMinimum(varname) ;
   double wgt_h = chain->GetMaximum(varname) ;
   
   // To include all events, wgt_l(h) are changed to lower(higer) value
   wgt_l = wgt_l-0.05*fabs(wgt_l);
   wgt_h = wgt_h+0.05*fabs(wgt_h);

   TH1D *hist1 = new TH1D(Form( "sumw_%s",varname),"",50,wgt_l,wgt_h);
   TH1D *hist2 = new TH1D(Form("sumw2_%s",varname),"",50,wgt_l,wgt_h);

   chain->Project( hist1->GetName(), varname, varname );
   chain->Project( hist2->GetName(), varname, Form("%s*%s",varname,varname) );

   double sumw    = hist1->Integral();
   double sumw2   = hist2->Integral();
   double ratio = sumw/sumw2;
   cout<<"==========================================="<<endl;
   cout<<" "<<"Entries"<<"  "<<"sumw"<<"  "<<"sumw2"<<"  "<<"sumw/sumw2"<<endl;
   cout<<"==========================================="<<endl;
   cout<<" "<<chain->GetEntries()<<" "<<sumw<<" "<<sumw2<<" "<<ratio<<endl;
   cout<<"==========================================="<<endl;

   delete hist1;
   delete hist2;
   return ratio;
}
