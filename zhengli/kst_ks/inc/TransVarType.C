#include "TTree.h"
#include "TChain.h"

void TransVarType(
	TChain *chain,
	const char *ifvarlist,
	const char *ofroot,
	const char *oftree,
	int nevt
	)
{
   if(nevt==-1) nevt = chain->GetEntries(); 

   cout<<"=========================================="<<endl;
   cout<<" Total Entries : "<<chain->GetEntries()<<endl;
   cout<<"   Run Entries : "<<nevt<<endl;
   cout<<"=========================================="<<endl;
  
   TFile *rootfile = new TFile( ofroot,"recreate");
   TTree *DecayTree = new TTree( oftree, "tree" );

   vector<string> AllOrigName; AllOrigName.clear();

   vector<string> BBOrigType; BBOrigType.clear();
   vector<string> SSOrigType; SSOrigType.clear();
   vector<string> CBOrigType; CBOrigType.clear();
   vector<string> IIOrigType; IIOrigType.clear();
   vector<string> DDOrigType; DDOrigType.clear(); 
   vector<string> DFOrigType; DFOrigType.clear();
   vector<string> FDOrigType; FDOrigType.clear();
   vector<string> FFOrigType; FFOrigType.clear();

   vector<string> BBOrigName; BBOrigName.clear();
   vector<string> SSOrigName; SSOrigName.clear();
   vector<string> CBOrigName; CBOrigName.clear();
   vector<string> IIOrigName; IIOrigName.clear();
   vector<string> DDOrigName; DDOrigName.clear();
   vector<string> DFOrigName; DFOrigName.clear();
   vector<string> FDOrigName; FDOrigName.clear();
   vector<string> FFOrigName; FFOrigName.clear();

   vector<string> BBTranType; BBTranType.clear();
   vector<string> SSTranType; SSTranType.clear();
   vector<string> CBTranType; CBTranType.clear();
   vector<string> IITranType; IITranType.clear();
   vector<string> DDTranType; DDTranType.clear(); 
   vector<string> DFTranType; DFTranType.clear();
   vector<string> FDTranType; FDTranType.clear();
   vector<string> FFTranType; FFTranType.clear();

   vector<string> BBTranName; BBTranName.clear();
   vector<string> SSTranName; SSTranName.clear();
   vector<string> CBTranName; CBTranName.clear();
   vector<string> IITranName; IITranName.clear();
   vector<string> DDTranName; DDTranName.clear();
   vector<string> DFTranName; DFTranName.clear();
   vector<string> FDTranName; FDTranName.clear();
   vector<string> FFTranName; FFTranName.clear();

   ifstream input_var( ifvarlist );
   if(!input_var){
	cout<<"====================================="<<endl;
	cout<<" The input varlist doesn't exit "<<endl;
	cout<<"====================================="<<endl;
	exit(0);
   }

   // Read parameters from file
   while(!input_var.eof()){
	string TmpOrigType;
	string TmpTranType;
	string TmpOrigName;
	string TmpTranName;

	input_var>>TmpOrigType>>TmpTranType>>TmpOrigName>>TmpTranName;

	AllOrigName.push_back(TmpOrigName);

	if( TmpOrigType == "Bool_t" && TmpTranType == "Bool_t" ){
	   BBOrigType.push_back( TmpOrigType );
	   BBTranType.push_back( TmpTranType );
	   BBOrigName.push_back( TmpOrigName );
	   BBTranName.push_back( TmpTranName );
	}
	if( TmpOrigType == "Short_t" && TmpTranType == "Short_t" ){
	   SSOrigType.push_back( TmpOrigType );
	   SSTranType.push_back( TmpTranType );
	   SSOrigName.push_back( TmpOrigName );
	   SSTranName.push_back( TmpTranName );
	}
	if( TmpOrigType == "Char_t" && TmpTranType == "Bool_t" ){
	   CBOrigType.push_back( TmpOrigType );
	   CBTranType.push_back( TmpTranType );
	   CBOrigName.push_back( TmpOrigName );
	   CBTranName.push_back( TmpTranName );
	}
	if( TmpOrigType == "Int_t" && TmpTranType == "Int_t" ){
	   IIOrigType.push_back( TmpOrigType );
	   IITranType.push_back( TmpTranType );
	   IIOrigName.push_back( TmpOrigName );
	   IITranName.push_back( TmpTranName );
	}
	if( TmpOrigType == "Double_t" && TmpTranType == "Double_t" ){
	   DDOrigType.push_back( TmpOrigType );
	   DDTranType.push_back( TmpTranType );
	   DDOrigName.push_back( TmpOrigName );
	   DDTranName.push_back( TmpTranName );
	}
	if( TmpOrigType == "Double_t" && TmpTranType == "Float_t" ){
	   DFOrigType.push_back( TmpOrigType );
	   DFTranType.push_back( TmpTranType );
	   DFOrigName.push_back( TmpOrigName );
	   DFTranName.push_back( TmpTranName );
	}
	if( TmpOrigType == "Float_t" && TmpTranType == "Double_t" ){
	   FDOrigType.push_back( TmpOrigType );
	   FDTranType.push_back( TmpTranType );
	   FDOrigName.push_back( TmpOrigName );
	   FDTranName.push_back( TmpTranName );
	}
	if( TmpOrigType == "Float_t" && TmpTranType == "Float_t" ){
	   FFOrigType.push_back( TmpOrigType );
	   FFTranType.push_back( TmpTranType );
	   FFOrigName.push_back( TmpOrigName );
	   FFTranName.push_back( TmpTranName );
	}
	//cout<<" "<<TmpOrigType<<" "<<TmpTranType<<" "<<TmpOrigName<<" "<<TmpTranName<<endl;
   }
   const int nBB = BBOrigType.size();
   const int nSS = SSOrigType.size();
   const int nCB = CBOrigType.size();
   const int nII = IIOrigType.size();
   const int nDD = DDOrigType.size();
   const int nDF = DFOrigType.size();
   const int nFD = FDOrigType.size();
   const int nFF = FFOrigType.size();
   cout<<"--------------------------------------------"<<endl;
   cout<<" Number of  Bool   -> Bool    : "<< nBB <<endl;
   cout<<" Number of  Short  -> Short   : "<< nSS <<endl;
   cout<<" Number of  Char   -> Bool    : "<< nCB <<endl;
   cout<<" Number of  Int    -> Int     : "<< nII <<endl;
   cout<<" Number of  Double -> Double  : "<< nDD <<endl;
   cout<<" Number of  Double -> Float   : "<< nDF <<endl;
   cout<<" Number of  Float  -> Double  : "<< nFD <<endl;
   cout<<" Number of  Float  -> Float   : "<< nFF <<endl;
   cout<<"--------------------------------------------"<<endl;

   //Char_t   OBBval[nBB]; Char_t   TBBval[nBB];
   bool   OBBval[nBB]; bool   TBBval[nBB];
   short  OSSval[nSS]; short  TSSval[nSS];
   char   OCBval[nCB]; char   TCBval[nCB];
   int    OIIval[nII]; int    TIIval[nII];
   double ODDval[nDD]; double TDDval[nDD];
   double ODFval[nDF]; float  TDFval[nDF];
   float  OFDval[nFD]; double TFDval[nFD];
   float  OFFval[nFF]; float  TFFval[nFF];

   // Set BranchAddress and Branch
   if(nBB!=0){
	for(int i=0; i<nBB; i++){
	   chain->SetBranchAddress(BBOrigName[i].c_str(),&OBBval[i]);
	   DecayTree->Branch(BBTranName[i].c_str(),&TBBval[i],TString::Format("%s/B",BBTranName[i].c_str()));
	}
   }
   if(nSS!=0){
	for(int i=0; i<nSS; i++){
	   chain->SetBranchAddress(SSOrigName[i].c_str(),&OSSval[i]);
	   DecayTree->Branch(SSTranName[i].c_str(),&TSSval[i],TString::Format("%s/S",SSTranName[i].c_str()));
	}
   }
   if(nCB!=0){
	for(int i=0; i<nCB; i++){
	   chain->SetBranchAddress(CBOrigName[i].c_str(),&OCBval[i]);
	   DecayTree->Branch(CBTranName[i].c_str(),&TCBval[i],TString::Format("%s/B",CBTranName[i].c_str()));
	}
   }
   if(nII!=0){
	for(int i=0; i<nII; i++){
	   chain->SetBranchAddress(IIOrigName[i].c_str(),&OIIval[i]);
	   DecayTree->Branch(IITranName[i].c_str(),&TIIval[i],TString::Format("%s/I",IITranName[i].c_str()));
	}
   }
   if(nDD!=0){
	for(int i=0; i<nDD; i++){
	   chain->SetBranchAddress(DDOrigName[i].c_str(),&ODDval[i]);
	   DecayTree->Branch(DDTranName[i].c_str(),&TDDval[i],TString::Format("%s/D",DDTranName[i].c_str()));
	}
   }
   if(nDF!=0){
	for(int i=0; i<nDF; i++){
	   chain->SetBranchAddress(DFOrigName[i].c_str(),&ODFval[i]);
	   DecayTree->Branch(DFTranName[i].c_str(),&TDFval[i],TString::Format("%s/F",DFTranName[i].c_str()));
	}
   }
   if(nFD!=0){
	for(int i=0; i<nFD; i++){
	   chain->SetBranchAddress(FDOrigName[i].c_str(),&OFDval[i]);
	   DecayTree->Branch(FDTranName[i].c_str(),&TFDval[i],TString::Format("%s/D",FDTranName[i].c_str()));
	}
   }
   if(nFF!=0){
	for(int i=0; i<nFF; i++){
	   chain->SetBranchAddress(FFOrigName[i].c_str(),&OFFval[i]);
	   DecayTree->Branch(FFTranName[i].c_str(),&TFFval[i],TString::Format("%s/F",FFTranName[i].c_str()));
	}
   }

   // SetBranchStatus
   chain->SetBranchStatus("*",0);
   for( int i=0; i<AllOrigName.size()-1; i++ ){
	chain->SetBranchStatus(AllOrigName[i].c_str(),1);
   }

   // GetEntry and Fill the tree
   for(int i=0; i<nevt; i++){
	if( i%10000==0 )
	   cout<<" Processing "<<i/1000<<" k events."<<endl;
	chain->GetEntry(i);
	for(int nvar=0; nvar<nBB; nvar++){ TBBval[nvar] = OBBval[nvar]; }
	for(int nvar=0; nvar<nSS; nvar++){ TSSval[nvar] = OSSval[nvar]; }
	for(int nvar=0; nvar<nCB; nvar++){ TCBval[nvar] = OCBval[nvar]; }
	for(int nvar=0; nvar<nII; nvar++){ TIIval[nvar] = OIIval[nvar]; }
	for(int nvar=0; nvar<nDD; nvar++){ TDDval[nvar] = ODDval[nvar]; }
	for(int nvar=0; nvar<nDF; nvar++){ TDFval[nvar] = ODFval[nvar]; }
	for(int nvar=0; nvar<nFD; nvar++){ TFDval[nvar] = OFDval[nvar]; }
	for(int nvar=0; nvar<nFF; nvar++){ TFFval[nvar] = OFFval[nvar]; }

	DecayTree->Fill();
   }

   DecayTree->Write();
   rootfile->Close();

}
