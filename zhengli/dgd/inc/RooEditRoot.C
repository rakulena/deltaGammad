
// Copy the root with cut
void RootCut(
	const char* iftree,
	const char* ofroot,
	const char* treecut,
	int ininum = 0,
	int finnum = -1
	)
{
 
   cout<<"======================================"<<endl;
   cout<<" Input  tree : "<<iftree<<endl;
   cout<<" Output root : "<<ofroot<<endl;
   cout<<" Selection   : "<<treecut<<endl;
   cout<<"======================================"<<endl;

   TChain *chain = new TChain();
   chain->Add( iftree );

   if( finnum==-1 ) finnum = chain->GetEntries();

   TFile *newfile = new TFile( ofroot, "recreate" );
   TTree *newtree = chain->CopyTree( treecut, "", finnum, ininum );
   
   cout<<"======================================"<<endl;
   cout<<" Input  events : "<<finnum<<endl;
   cout<<" Output events : "<<newtree->GetEntries()<<endl;
   cout<<"======================================"<<endl;

   newfile->cd();
   newtree->Write("",TObject::kWriteDelete);
   newfile->Close();

   delete chain;
   delete newfile;
}

// Randomly divide the root into 2 parts
void RootDivRan(
	const char* iftree,
	const char* ofroot1,
	const char* ofroot2,
	double frac
	){
   
   cout<<"========================================="<<endl;
   cout<<" Input  tree  : "<<iftree<<endl;
   cout<<" Output root1 : "<<ofroot1<<endl;
   cout<<" Output root2 : "<<ofroot2<<endl;
   cout<<"========================================="<<endl;

   TChain *chain = new TChain();
   chain->Add( iftree );

   TFile *newfile1 = new TFile( ofroot1, "recreate" );
   TTree *newtree1 = chain->CloneTree(0);

   TFile *newfile2 = new TFile( ofroot2, "recreate" );
   TTree *newtree2 = chain->CloneTree(0);

   TRandom3 *dummy= new TRandom3(frac);

   cout<<" Total Entries : "<<chain->GetEntries()<<endl;
   for( int i=0; i<chain->GetEntries(); i++ ){
	if( i%20000==0 ) cout<<" -- Processing "<<i/1000<<" k. "<<endl;
	chain->GetEntry(i);
	double genval = dummy->Uniform(0.,1.);
	if( genval<frac ){
	   newtree1->Fill();
	}else{
	   newtree2->Fill();
	}
   }
   newfile1->cd();
   newtree1->Write("",TObject::kWriteDelete);
   newfile1->Close();

   newfile2->cd();
   newtree2->Write("",TObject::kWriteDelete);
   newfile2->Close();

   delete chain;
   delete newfile1;
   delete newfile2;

}

// Mix the rootfile according to the fraction of luminosity
void RootMixLumi(
	const char* iftree,
	const char* ofroot,
	int     nyear[],
	double  nlumi[],
	const int ny
	)
{
   
   TChain *chain = new TChain();
   chain->Add( iftree );

   int year;
   chain->SetBranchAddress("year", &year);
  
   // Get the map of year and fraction
   std::map<int,double> frac;

   double nyfb_min = 0;
   double nyfb[ny];
   for( int i=0; i<ny; i++ ){
	nyfb[i] = chain->GetEntries( Form("year==%i",nyear[i]) )/nlumi[i];
	if(i==0 ){
	   nyfb_min = nyfb[i];
	}else{
	   nyfb_min = min( nyfb_min, nyfb[i] );
	}
   }

   for( int i=0; i<ny; i++ ){
	frac[nyear[i]] = nyfb_min/nyfb[i];
   }

   // Get the mixed root corresponding to the fraction of luminosity
   TFile *newfile = new TFile( ofroot, "recreate" );
   TTree *newtree = chain->CloneTree(0);

   TRandom3 *dummy= new TRandom3( nyfb_min );

   //for( int i=0; i<50000; i++ ){
   for( int i=0; i<chain->GetEntries(); i++ ){
	if( i%50000==0 ) cout<<" -- Processing "<<i/1000<<" k. "<<endl;
	chain->GetEntry(i);
	
	double genval = dummy->Uniform(0.,1.);
	if( genval<frac[year] ) newtree->Fill();
   }

   newfile->cd();
   newtree->Write();
   newfile->Close();

}

// Copy the branches
void RootCopyBranches(
	const char* iftree,
	const char* ofroot,
	const char* treecut,
	vector<string> branch,
	int ininum,
	int finnum
	)
{
   TChain *chain = new TChain();
   chain->Add( iftree );
   chain->SetBranchStatus("*",0);

   for( int i=0; i<branch.size(); i++ )
	chain->SetBranchStatus(branch[i].c_str(),1);

   if( finnum==-1 ) finnum = chain->GetEntries();

   TFile *newfile = new TFile( ofroot, "recreate" );
   TTree *newtree = chain->CopyTree( treecut, "", finnum, ininum );

   newfile->cd();
   newtree->Write("",TObject::kWriteDelete);
   newfile->Close();

   delete chain;
   delete newfile;
}
