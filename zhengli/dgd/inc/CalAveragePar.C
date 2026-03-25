// Calculate average value of var with weight
//-----------------------------------------------------------

double CalAveragePar(
	TChain *chain,
	const char *varname,
	const char *weightname
	)
{
   double val_l = chain->GetMinimum(varname);
   double val_h = chain->GetMaximum(varname);

   // To include all events, val_l(h) are changed to lower(higer) value
   val_l = val_l-0.05*fabs(val_l);
   val_h = val_h+0.05*fabs(val_h);

   TH1D *hist1 = new TH1D(Form("wgt_%s",weightname),"",50,val_l,val_h);
   TH1D *hist2 = new TH1D(Form("wgtvar_%s",varname),"",50,val_l,val_h);

   chain->Project( hist1->GetName(), varname, weightname,"");
   chain->Project( hist2->GetName(), varname, Form("%s*%s",varname,weightname),"");

   double sumw    = hist1->Integral();
   double sumwvar = hist2->Integral();
   double avpar   = sumwvar/sumw;
   
   cout<<"==========================================="<<endl;
   cout<<" Variable      : "<<varname<<endl;
   cout<<" Weight        : "<<weightname<<endl;
   cout<<" Entries       : "<<chain->GetEntries()<<endl;
   cout<<" Sumw          : "<<sumw<<endl;
   cout<<" Sumwvar       : "<<sumwvar<<endl;
   cout<<" Average value : "<<avpar<<endl;
   cout<<"==========================================="<<endl;

   delete hist1;
   delete hist2;
   return avpar;
}

double CalAveragePar(
	TTree *seltree,
	const char *varname,
	const char *weightname
	)
{
   double val_l = seltree->GetMinimum(varname);
   double val_h = seltree->GetMaximum(varname);

   // To include all events, val_l(h) are changed to lower(higer) value
   val_l = val_l-0.05*fabs(val_l);
   val_h = val_h+0.05*fabs(val_h);

   TH1D *hist1 = new TH1D(Form("wgt_%s",weightname),"",50,val_l,val_h);
   TH1D *hist2 = new TH1D(Form("wgtvar_%s",varname),"",50,val_l,val_h);

   seltree->Project( hist1->GetName(), varname, weightname );
   seltree->Project( hist2->GetName(), varname, Form("%s*%s",varname,weightname) );

   double sumw    = hist1->Integral();
   double sumwvar = hist2->Integral();
   double avpar   = sumwvar/sumw;
   
   cout<<"==========================================="<<endl;
   cout<<" Variable      : "<<varname<<endl;
   cout<<" Weight        : "<<weightname<<endl;
   cout<<" Entries       : "<<seltree->GetEntries()<<endl;
   cout<<" Sumw          : "<<sumw<<endl;
   cout<<" Sumwvar       : "<<sumwvar<<endl;
   cout<<" Average value : "<<avpar<<endl;
   cout<<"==========================================="<<endl;

   delete hist1;
   delete hist2;
   return avpar;
}

double CalAveragePar(
	TTree *seltree,
	const char *varname,
	const char *weightname,
	const char *vartype,
	const char *wgttype
	)
{

   float fvar;
   float fw;
   double dvar;
   double dw;
   string tmpvartype = vartype;
   string tmpwgttype = wgttype;
   
   seltree->SetBranchStatus("*",0);
   seltree->SetBranchStatus(varname,1);
   seltree->SetBranchStatus(weightname,1);

   if( tmpvartype == "F" ) seltree->SetBranchAddress( varname, &fvar );
   if( tmpvartype == "D" ) seltree->SetBranchAddress( varname, &dvar );
   if( tmpwgttype == "F" ) seltree->SetBranchAddress( weightname, &fw );
   if( tmpwgttype == "D" ) seltree->SetBranchAddress( weightname, &dw );

   double sumwvar = 0;
   double sumw = 0;
   for( int i=0; i<seltree->GetEntries(); i++ ){
	seltree->GetEntry(i);
	double weight;
	double varval;
	if( tmpwgttype == "F" ) weight = fw;
	if( tmpwgttype == "D" ) weight = dw;
	if( tmpvartype == "F" ) varval = fvar;
	if( tmpvartype == "D" ) varval = dvar;
	sumw += weight;
	sumwvar += weight*varval;
   }
   double avpar = sumwvar/sumw;
   cout<<"==========================================="<<endl;
   cout<<" Variable      : "<<varname<<endl;
   cout<<" Weight        : "<<weightname<<endl;
   cout<<" Entries       : "<<seltree->GetEntries()<<endl;
   cout<<" Sumw          : "<<sumw<<endl;
   cout<<" Sumwvar       : "<<sumwvar<<endl;
   cout<<" Average value : "<<avpar<<endl;
   cout<<"==========================================="<<endl;

   return avpar;

}

double CalAveragePar(
	TChain *chain,
	const char *varname,
	const char *weightname,
	const char *vartype,
	const char *wgttype
	)
{

   float fvar;
   float fw;
   double dvar;
   double dw;
   string tmpvartype = vartype;
   string tmpwgttype = wgttype;

   chain->SetBranchStatus("*",0);
   chain->SetBranchStatus(varname,1);
   chain->SetBranchStatus(weightname,1);

   if( tmpvartype == "F" ) chain->SetBranchAddress( varname, &fvar );
   if( tmpvartype == "D" ) chain->SetBranchAddress( varname, &dvar );
   if( tmpwgttype == "F" ) chain->SetBranchAddress( weightname, &fw );
   if( tmpwgttype == "D" ) chain->SetBranchAddress( weightname, &dw );

   double sumwvar = 0;
   double sumw = 0;
   for( int i=0; i<chain->GetEntries(); i++ ){
	chain->GetEntry(i);
	double weight;
	double varval;
	if( tmpwgttype == "F" ) weight = fw;
	if( tmpwgttype == "D" ) weight = dw;
	if( tmpvartype == "F" ) varval = fvar;
	if( tmpvartype == "D" ) varval = dvar;
	sumw += weight;
	sumwvar += weight*varval;
   }
   double avpar = sumwvar/sumw;
   cout<<"==========================================="<<endl;
   cout<<" Variable      : "<<varname<<endl;
   cout<<" Weight        : "<<weightname<<endl;
   cout<<" Entries       : "<<chain->GetEntries()<<endl;
   cout<<" Sumw          : "<<sumw<<endl;
   cout<<" Sumwvar       : "<<sumwvar<<endl;
   cout<<" Average value : "<<avpar<<endl;
   cout<<"==========================================="<<endl;

   return avpar;

}

