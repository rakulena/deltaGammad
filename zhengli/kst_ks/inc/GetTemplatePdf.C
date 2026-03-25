#include "Printpic.C"

void GetTemplatePdf(
	const char* iffile,
	const char* offile,
	const char* treecut,
	const char* varname,
	const char* vartype,
	const char* fitname,
	const char* pdfname,
      const char* picname,
	const char* XTitle,
	double var_l,
	double var_h,
	double var_shift,
	int nBin,
	int nEvt,
	RooKeysPdf::Mirror mirror,
	double rho
	)

{

   TChain *chain = new TChain();
   chain->Add( iffile );

   TTree *seltree = chain->CopyTree( treecut );

   float  fvar;
   double dvar;
   double tmpvar;
   string tmptype = vartype;

   if( tmptype=="F" ) seltree->SetBranchAddress( varname, &fvar );
   if( tmptype=="D" ) seltree->SetBranchAddress( varname, &dvar );
   
   RooRealVar *var = new RooRealVar( fitname ,"",var_l,var_h );
   RooDataSet *data =new RooDataSet( Form("%s_data",pdfname),"",RooArgSet(*var) );

   if( nEvt==-1 || nEvt>seltree->GetEntries() ) 
	nEvt = seltree->GetEntries();
   
   for( int i=0; i<nEvt; i++ ){
	seltree->GetEntry(i);
	if( i%10000 == 0) cout<<" Processing "<<i/1000<<" k."<<endl;

	if( tmptype=="F" ) tmpvar = fvar+var_shift;
	if( tmptype=="D" ) tmpvar = dvar+var_shift;
	if(!( tmpvar>var_l && tmpvar<var_h )) continue;

	*var = tmpvar;
	data->add(RooArgSet(*var));

   }
   
   cout<<"========================================="<<endl;
   cout<<" DataSet : "<<endl;
   data->Print();
   cout<<"========================================="<<endl<<endl;

   RooKeysPdf *shape_Ubin = new RooKeysPdf( Form("ubin_%s",pdfname),"",*var,*data,mirror,rho );

   TCanvas *pic = new TCanvas( Form("pic_%s",pdfname),"",800,600);

   pic->cd();
   RooPlot *frame = var->frame( Bins(nBin) );
   data->plotOn(frame);
   shape_Ubin->plotOn(frame,Name("2"),LineColor(4),LineWidth(2));

   frame->SetTitle("");
   frame->GetXaxis()->SetTitle( XTitle );
   frame->GetYaxis()->SetTitle( "" );
   frame->Draw();

   TFile *rootfile = new TFile( offile, "recreate");
   rootfile->cd();
   shape_Ubin->Write();
   rootfile->Close();

   Printpic2( pic, pdfname, 1 );

}

void GetTemplatePdf(
	const char* iffile,
	const char* offile,
	const char* treecut,
	const char* varname,
	const char* vartype,
	const char* fitname,
	const char* pdfname,
      const char* picname,
	const char* XTitle,
	const int nInt,
	double var_l[],
	double var_h[],
	double var_shift,
	int nBin,
	int nEvt,
	RooKeysPdf::Mirror mirror,
	double rho
	)

{

   TChain *chain = new TChain();
   chain->Add( iffile );

   TTree *seltree = chain->CopyTree( treecut );

   float  fvar;
   double dvar;
   double tmpvar;
   string tmptype = vartype;

   if( tmptype=="F" ) seltree->SetBranchAddress( varname, &fvar );
   if( tmptype=="D" ) seltree->SetBranchAddress( varname, &dvar );
   
   RooRealVar *var = new RooRealVar( fitname ,"",var_l[0],var_h[0] );
   RooDataSet *data =new RooDataSet( Form("%s_data",pdfname),"",RooArgSet(*var) );

   if( nEvt==-1 || nEvt>seltree->GetEntries() ) nEvt = seltree->GetEntries();
   
   for( int i=0; i<nEvt; i++ ){
	seltree->GetEntry(i);
	if( i%10000 == 0) cout<<" Processing "<<i/1000<<" k."<<endl;

	if( tmptype=="F" ) tmpvar = fvar+var_shift;
	if( tmptype=="D" ) tmpvar = dvar+var_shift;
	if(!( tmpvar>var_l[0] && tmpvar<var_h[0] )) continue;

	*var = tmpvar;
	data->add(RooArgSet(*var));
   }
   
   cout<<"========================================="<<endl;
   cout<<" DataSet : "<<endl;
   data->Print();
   cout<<"========================================="<<endl<<endl;

   RooKeysPdf *shape_Ubin = new RooKeysPdf( Form("ubin_%s",pdfname),"",*var,*data,mirror,rho );

   // Integral over the specific range
   for( int i=0; i<nInt; i++ ) var->setRange( Form("InteR_%i",i),var_l[i],var_h[i]);
   cout<<"========================================="<<endl;
   for( int i=0; i<nInt; i++ ){
	RooAbsReal *IntegVar = shape_Ubin->createIntegral( *var, NormSet(*var), Range(Form("InteR_%i",i)) );
	double IntegVar_val = IntegVar->getVal();
	cout<<" Integral value in ["<<var_l[i]<<","<<var_h[i]<<"], "<<IntegVar_val<<endl;
   }
   cout<<"========================================="<<endl;

   TCanvas *pic = new TCanvas( Form("pic_%s",pdfname),"",800,600);

   pic->cd();
   RooPlot *frame = var->frame( Bins(nBin) );
   data->plotOn(frame);
   shape_Ubin->plotOn(frame,Name("2"),LineColor(4),LineWidth(2));

   frame->SetTitle("");
   frame->GetXaxis()->SetTitle( XTitle );
   frame->GetYaxis()->SetTitle( "" );
   frame->Draw();

   TFile *rootfile = new TFile( offile, "recreate");
   rootfile->cd();
   shape_Ubin->Write();
   rootfile->Close();

   Printpic( pic, picname, 1 );

}

