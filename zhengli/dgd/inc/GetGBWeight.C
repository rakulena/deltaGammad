
void GetGBWeight(
	const char *iftree1,
	const char *iftree2,
	const char *treecut,
	const char *gbwname,
	const char *outname,
	const char *ofroot
	)
{

   cout<<" ------------------------------------- "<<endl;
   cout<<" Input tree1 : "<<iftree1<<endl;
   cout<<" Input tree2 : "<<iftree2<<endl;
   cout<<" Tree  cut   : "<<treecut<<endl;
   cout<<" Output root : "<<ofroot<<endl;
   cout<<" ------------------------------------- "<<endl;

   TChain *chain1 = new TChain();
   TChain *chain2 = new TChain();
   chain1->Add( iftree1 );
   chain2->Add( iftree2 );

   if( chain1->GetEntries(treecut) != chain2->GetEntries() ){
	cout<<" ------------------------------------- "<<endl;
	cout<<" The number of events is not matched "<<endl;
	cout<<" ------------------------------------- "<<endl;
	return;
   }else{
	cout<<" ------------------------------------- "<<endl;
	cout<<" The number of events is matched "<<endl;
	cout<<" ------------------------------------- "<<endl;
   }

   string tmpcut = treecut;
   TTree *seltree;
   if( tmpcut!="" ){
	seltree = chain1->CopyTree(treecut);
   }else{
	seltree = chain1;
   }

   double gbw;
   chain2->SetBranchAddress( gbwname ,&gbw);

   TFile *newfile = new TFile( ofroot, "recreate" );
   TTree *newtree = chain1->CloneTree(0);
   newtree->Branch(outname,&gbw,Form("%s/D",outname));

   for( int i=0; i<chain2->GetEntries(); i++ ){
	seltree->GetEntry(i);
	chain2->GetEntry(i);
	if( i%50000 == 0 ) cout<<" Processing "<<i/1000<<" k events. "<<endl;
	newtree->Fill();
   }

   newfile->cd();
   newtree->Write("",TObject::kWriteDelete);
   newfile->Close();

   delete chain1;
   delete chain2;
   delete newfile;
}

