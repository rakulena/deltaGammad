#include "../inc/headfile.h"
#include "../inc/Calfnll.C"
#include "../inc/RooSaveFitPlot.C"
#include "../src/RooEffResModel.h"
#include "../src/RooBinnedPdf.h"
#include "../src/RooCubicSplineFun.h"
#include "../inc/RooMinuit.h"

using namespace RooFit ;

void SetAccFrame(
	RooPlot *vframe,
	RooAbsReal *ACC_pdf,
	RooFitResult *fitres,
	bool isViserr,
	Color_t FCol,
	Color_t LCol,
	const char *XTitle,
	const char *YTitle,
	string lineobj = ""
	)
{
   if( isViserr )	ACC_pdf->plotOn( vframe,VisualizeError(*fitres,1),FillColor(FCol) );
   if( lineobj== "" ){
	ACC_pdf->plotOn( vframe,LineStyle(1),LineColor(LCol) );
   }else{
	ACC_pdf->plotOn( vframe,LineStyle(1),LineColor(LCol),Name(lineobj.c_str()) );
   }
   vframe->SetMinimum(0.);
   vframe->SetMaximum(2.2);
   vframe->GetXaxis()->SetTitle( XTitle );
   vframe->GetYaxis()->SetTitle( YTitle );
   vframe->GetXaxis()->SetTitleFont(132);
   vframe->GetYaxis()->SetTitleFont(132);
   vframe->GetXaxis()->SetTitleSize(0.06);
   vframe->GetYaxis()->SetTitleSize(0.06);
   vframe->GetXaxis()->SetTitleOffset(1.05);
   vframe->GetYaxis()->SetTitleOffset(1.05);
}

void SaveAccPic(
	RooPlot *vframe,
	const char *picname
	)
{
   TCanvas* pic = new TCanvas(Form("pic_%s",picname),"",10,10,800,600);
   pic->cd();
   vframe->Draw();
   
   pic->SaveAs(Form("output/%s.pdf",picname));
}

int main(int argc, char **argv)
{
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   gROOT->GetListOfCleanups();
   gROOT->ProcessLine(".x ../inc/lhcbStyle.C");

   cout<<"==========================================="<<endl;
   cout<<" STARTING  TIME : "<<endl;
   system("date");
   cout<<"==========================================="<<endl;

   //command line parameter defaults
   double nfrac = 1;
   string mode = "";

   //parse command line
   int c;
   while( (c=getopt(argc,argv,"hn:n:m:")) != -1 ){
	switch(c){
	   case 'h':
		cout <<"Usage: " << argv[0]<<endl
		   <<"         [-h] [-n <number_of_events>] " << endl
		   <<"         [-m mode]     " << endl;
		exit(0);
		break;
	   case 'n':
		nfrac = atof(optarg);
		if (nfrac < 0) nfrac = 0.1;
		break;
	   case 'm':
		mode = optarg;
		break;
	}
   }

   bool Nfit = mode.find("Nfit")!=string::npos;
   bool Vali = mode.find("Vali")!=string::npos;
   bool Chck = mode.find("Chck")!=string::npos;
   bool Y2017 = mode.find("Y2017")!=string::npos;
   bool Y2018 = mode.find("Y2018")!=string::npos;
   bool Dg = mode.find("Dg")!=string::npos;
   bool Hesse = mode.find("Hesse")!=string::npos;
   cout<<"=================================="<<endl;
   cout<<" Mode : "<<mode<<endl;
   cout<<"=================================="<<endl;

   string Year = "2016";
   string parfix = "16";
   if( Y2017 ){ Year = "2017"; parfix = "17"; }
   if( Y2018 ){ Year = "2018"; parfix = "18"; }

   // sig & con for signal & control channel
   // M & D for mc & data
   string path_sigM = Form("/lzufs/user/zhanghy/Sample/afterBDT/after_Bd2JpsiKshort_mc_%s_BDT.root/DecayTree",Year.c_str());
   string path_conM = Form("/lzufs/user/zhanghy/Sample/kplus/mc/v4r0_MC_Bu2JpsiKplus_%s_selected_bdt.root/DecayTree",Year.c_str());
   string path_sigD = Form("/lzufs/user/zhanghy/Sample/afterBDT/after_Bd2JpsiKshort_data_%s_sw_base.root/DecayTree",Year.c_str());
   string path_conD = Form("/lzufs/user/zhanghy/Sample/kplus/data/Bu2Jpsikplus_data_%s_sw_base_bdt.root/DecayTree",Year.c_str());

   string prefix = "base";
   double ftau_val = 0.9261; // ratio for lifetime of signal to control
   double dg_val = 0.01; // Alternative value of Dgd
   double tau_sigM_val = 1.517;
   double tau_conM_val = 1.638;
   double tau_conD_val = 1.638;

   if( Vali ){
	prefix = "vali";
	ftau_val = 1.076;
	tau_sigM_val = 1.638;

	string path_sigM = Form("/lzufs/user/zhanghy/Sample/afterBDT/after_Bd2JpsiKstar_mc_%s_BDT.root/DecayTree",Year.c_str());
	string path_sigD = Form("/lzufs/user/zhanghy/Sample/afterBDT/after_Bd2JpsiKstar_data_%s_sw_base.root/DecayTree",Year.c_str());
 }
   if( Dg ){
	prefix = "dg";
   }

   string ifknots  = "parinfor/knots_base";
   string ifresodata = "../FinalInput/reso_cali_data.dat"; 
   string ifresomc   = "../FinalInput/reso_cali_mc.dat"; 
   string offitpar  = Form( "parinfor/parinfor_%s_%s.dat", prefix.c_str(), Year.c_str() ); 
   string oftaccpar = Form( "../FinalInput/tacc_coef_%s_%s.dat", prefix.c_str(), Year.c_str() ); 
   string offitres  = Form( "output/taccres_%s_%s.root", prefix.c_str(), Year.c_str() ); 

   cout<<"======================================================="<<endl;
   cout<<" Signal  MC   : "<<path_sigM<<endl;
   cout<<" Control MC   : "<<path_conM<<endl;
   cout<<" Signal  Data : "<<path_sigD<<endl;
   cout<<" Control Data : "<<path_conD<<endl;
   cout<<" knots file   : "<<ifknots<<endl;
   cout<<" fit parameters : "<<offitpar<<endl;
   cout<<" fit rootfile   : "<<offitres<<endl;
   cout<<"======================================================="<<endl;
   cout<<" Read the knots "<<endl;
   cout<<"======================================================="<<endl;

   // Read the knots
   ifstream iffile( ifknots.c_str() );
   if(!iffile){
	cout<<"---------------------------------- "<<endl;
	cout<<"  The file of knots doesn't exit ! =_= "<<endl;
	cout<<"---------------------------------- "<<endl;
	iffile.close();
	exit(0);
   }

   std::vector<double> knots; knots.clear();
   while(1){
	double tmpknot;
	iffile>>tmpknot;
	if(!iffile.good()) break;
	knots.push_back(tmpknot);
	cout<<"  "<<tmpknot<<endl;
   }
   iffile.close();
   const int nCof = knots.size()+2;

   // Set the input
   char bmass[] = "Bd_ConstJpsi_M";
   char time[]  = "Bd_ConstJpsi_tau";
   char timeerr[] = "Bd_ConstJpsi_tauErr";
   char wgt_sigM[] = "gbw";
   char wgt_conM[] = "gb_weights";
   char wgt_sigD[] = "sig_sw";
   char wgt_conD[] = "sig_sw";
   double t_l = knots[0];
   double t_h = 14;

   string cut1 = Form("%s>%.2lf&&%s<%.2lf",time,t_l,time,t_h);
   string cut_sigM = Form("%s&&%s>5220&&%s<5330&&abs(%s)<100",cut1.c_str(),bmass,bmass,wgt_sigM);
   string cut_conM = Form("%s&&%s>5220&&%s<5330&&abs(%s)<100",cut1.c_str(),bmass,bmass,wgt_conM);
   string cut_conD = Form("%s&&abs(%s)<100",cut1.c_str(),wgt_conD);
   string cut_sigD = Form("%s",cut1.c_str(),wgt_sigD);

   if( Vali ){
	cut_sigM = Form("%s&&abs(%s)<100",cut1.c_str(),wgt_sigM);
   }

   cout<<"======================================================="<<endl;
   cout<<" cut_sigM : "<<cut_sigM<<endl;
   cout<<" cut_conM : "<<cut_conM<<endl;
   cout<<" cut_sigD : "<<cut_sigD<<endl;
   cout<<" cut_conD : "<<cut_conD<<endl;
   cout<<"======================================================="<<endl;

   // Read trees
   TChain *chain_sigM = new TChain();
   TChain *chain_conM = new TChain();
   TChain *chain_sigD = new TChain();
   TChain *chain_conD = new TChain();

   chain_sigM->Add( path_sigM.c_str() );
   chain_conM->Add( path_conM.c_str() );
   chain_sigD->Add( path_sigD.c_str() );
   chain_conD->Add( path_conD.c_str() );

   chain_sigM->SetBranchStatus("*",0);
   chain_sigM->SetBranchStatus(bmass,1);
   chain_sigM->SetBranchStatus(time,1);
   chain_sigM->SetBranchStatus(timeerr,1);
   chain_sigM->SetBranchStatus(wgt_sigM,1);

   chain_conM->SetBranchStatus("*",0);
   chain_conM->SetBranchStatus(bmass,1);
   chain_conM->SetBranchStatus(time,1);
   chain_conM->SetBranchStatus(timeerr,1);
   chain_conM->SetBranchStatus(wgt_conM,1);
   
   chain_sigD->SetBranchStatus("*",0);
   chain_sigD->SetBranchStatus(time,1);
   chain_sigD->SetBranchStatus(timeerr,1);
   chain_sigD->SetBranchStatus(wgt_sigD,1);

   chain_conD->SetBranchStatus("*",0);
   chain_conD->SetBranchStatus(time,1);
   chain_conD->SetBranchStatus(timeerr,1);
   chain_conD->SetBranchStatus(wgt_conD,1);

   // chain_conM->SetBranchStatus("bdtg3",1);
   // chain_conD->SetBranchStatus("bdtg3",1);
   // chain_sigM->SetBranchStatus("BDT",1);
   // chain_sigD->SetBranchStatus("BDT",1);
   
   TTree *tree_sigM; 
   TTree *tree_conM; 
   TTree *tree_sigD; 
   TTree *tree_conD; 
   if( nfrac!=1 ){
	tree_sigM = chain_sigM->CopyTree( cut_sigM.c_str(), "", ceil(chain_sigM->GetEntries()*nfrac), 0 );
	tree_conM = chain_conM->CopyTree( cut_conM.c_str(), "", ceil(chain_conM->GetEntries()*nfrac), 0 );
	tree_conD = chain_conD->CopyTree( cut_conD.c_str(), "", ceil(chain_conD->GetEntries()*nfrac), 0 );
	tree_sigD = chain_sigD->CopyTree( cut_sigD.c_str(), "", ceil(chain_sigD->GetEntries()*nfrac), 0 );
   }else{
	tree_sigM = chain_sigM->CopyTree( cut_sigM.c_str() ); 
	tree_conM = chain_conM->CopyTree( cut_conM.c_str() ); 
	tree_sigD = chain_sigD->CopyTree( cut_sigD.c_str() ); 
	tree_conD = chain_conD->CopyTree( cut_conD.c_str() ); 
   }

   // Set observables
   RooRealVar *t = new RooRealVar(time,"time [ps]",t_l,t_h);
   RooRealVar *et = new RooRealVar(timeerr,"time [ps]",0.,0.15);
   RooRealVar *Dm = new RooRealVar("Dm","",0.);
   RooRealVar *DeltaG = new RooRealVar("DeltaG","",0.);

   // Set the weights
   RooRealVar *w_sigM = new RooRealVar(wgt_sigM,"",tree_sigM->GetMinimum(wgt_sigM),tree_sigM->GetMaximum(wgt_sigM));
   RooRealVar *w_conM = new RooRealVar(wgt_conM,"",tree_conM->GetMinimum(wgt_conM),tree_conM->GetMaximum(wgt_conM));
   RooRealVar *w_sigD = new RooRealVar(wgt_sigD,"",tree_sigD->GetMinimum(wgt_sigD),tree_sigD->GetMaximum(wgt_sigD));
   RooRealVar *w_conD = new RooRealVar(wgt_conD,"",tree_conD->GetMinimum(wgt_conD),tree_conD->GetMaximum(wgt_conD));

   // Set datasets
   RooDataSet *data_sigM = new RooDataSet("data_sigM","",tree_sigM,RooArgSet(*t,*et,*w_sigM),0,wgt_sigM);
   RooDataSet *data_conM = new RooDataSet("data_conM","",tree_conM,RooArgSet(*t,*et,*w_conM),0,wgt_conM);
   RooDataSet *data_sigD = new RooDataSet("data_sigD","",tree_sigD,RooArgSet(*t,*et,*w_sigD),0,wgt_sigD);
   RooDataSet *data_conD = new RooDataSet("data_conD","",tree_conD,RooArgSet(*t,*et,*w_conD),0,wgt_conD);
   cout<<"---------------------------------------------------"<<endl;
   cout<<" Sig mc & Con mc & Sig data & Con data DataSets : "<<endl;
   data_sigM->Print();
   data_conM->Print();
   data_sigD->Print();
   data_conD->Print();
   cout<<"---------------------------------------------------"<<endl;

   // Set resolution function for data and mc
   //jpsikst mc & bu2jpsik mc from bd2jpsipipi mc,,bu2jpsik data from bd2jpsipipi data
 
   // RooRealVar *res_muD = new RooRealVar("res_muD","mean value",0,-0.1,0.1,"ps");
   // RooRealVar *res_muM = new RooRealVar("res_muM","mean value",0,-0.1,0.1,"ps");
   // res_muD->setConstant(true);
   // res_muM->setConstant(true);

   // RooRealVar *sM0 = new RooRealVar(Form("s%s_M0",parfix.c_str()),"",5.7001e-03,0,0.1);
   // RooRealVar *sM1 = new RooRealVar(Form("s%s_M1",parfix.c_str()),"",6.5188e-01,-20,20);
   // RooRealVar *sM2 = new RooRealVar(Form("s%s_M2",parfix.c_str()),"",3.9518e+00,-20,20);  
   // sD0->setConstant(true);
   // sD1->setConstant(true);
   // sD2->setConstant(true);
   // sM0->setConstant(true);
   // sM1->setConstant(true);
   // sM2->setConstant(true);
   // RooFormulaVar *wd1D = new RooFormulaVar("wd1D","abs(@1+@2*@0+@3*@0*@0)",RooArgSet(*et,*sD0,*sD1,*sD2));
   // RooFormulaVar *wd1M = new RooFormulaVar("wd1M","abs(@1+@2*@0+@3*@0*@0)",RooArgSet(*et,*sM0,*sM1,*sM2));

   // RooGaussModel *resD = new RooGaussModel("resD","", *t, *res_muD, *wd1D);
   // RooGaussModel *resM = new RooGaussModel("resM","", *t, *res_muM, *wd1M);

   //jpsiks mc & bu2jpsik mc from sin2beta LL mc ,bu2jpsik data from bd2jpsipipi data
   RooRealVar *res_muD = new RooRealVar("res_muD", "mean value", 0, -0.1, 0.1, "ps");
   RooRealVar *res_muM = new RooRealVar("res_muM", "mean value", 0, -0.1, 0.1, "ps"); 
   res_muD->setConstant(true);
   res_muM->setConstant(true); 

   RooRealVar *sD0 = new RooRealVar(Form("s%s_D0", parfix.c_str()), "", 0.00985331);
   RooRealVar *sD1 = new RooRealVar(Form("s%s_D1", parfix.c_str()), "", 0.494388);
   RooRealVar *sD2 = new RooRealVar(Form("s%s_D2", parfix.c_str()), "", 9.07483); 

   RooFormulaVar *wd1D = new RooFormulaVar("wd1D", "abs(@1+@2*@0+@3*@0*@0)",RooArgSet(*et, *sD0, *sD1, *sD2));
   RooGaussModel *resD = new RooGaussModel("resD", "", *t, *res_muD, *wd1D);
   RooRealVar *b_M1 = new RooRealVar(Form("b%s_M1", parfix.c_str()), "", -0.235, -0.5, 0.0, "ps");
   RooRealVar *c_M1 = new RooRealVar(Form("c%s_M1", parfix.c_str()), "", 17.87, 15.0, 20.0);

   RooRealVar *b_M2 = new RooRealVar(Form("b%s_M2", parfix.c_str()), "", -0.0018, -0.01, 0.01, "ps");
   RooRealVar *c_M2 = new RooRealVar(Form("c%s_M2", parfix.c_str()), "", 1.97, 1.0, 3.0);

   RooRealVar *b_M3 = new RooRealVar(Form("b%s_M3", parfix.c_str()), "", 0.00034, -0.005, 0.005, "ps");
   RooRealVar *c_M3 = new RooRealVar(Form("c%s_M3", parfix.c_str()), "", 0.983, 0.8, 1.2);
   // sigma = c * et + b
   RooFormulaVar *sigma_g1 = new RooFormulaVar(Form("sigma%s_g1", parfix.c_str()),"@0*@1 + @2", RooArgList(*c_M1, *et, *b_M1));
   RooFormulaVar *sigma_g2 = new RooFormulaVar(Form("sigma%s_g2", parfix.c_str()),"@0*@1 + @2", RooArgList(*c_M2, *et, *b_M2));
   RooFormulaVar *sigma_g3 = new RooFormulaVar(Form("sigma%s_g3", parfix.c_str()),"@0*@1 + @2", RooArgList(*c_M3, *et, *b_M3));

   RooGaussModel *gauss1 = new RooGaussModel(Form("gauss1_%s", parfix.c_str()), "",*t, *res_muM, *sigma_g1);
   RooGaussModel *gauss2 = new RooGaussModel(Form("gauss2_%s", parfix.c_str()), "",*t, *res_muM, *sigma_g2);
   RooGaussModel *gauss3 = new RooGaussModel(Form("gauss3_%s", parfix.c_str()), "",*t, *res_muM, *sigma_g3);

   RooRealVar *f_M1 = new RooRealVar(Form("f%s_M1", parfix.c_str()), "",0.00430, 0.0, 0.01);
   RooRealVar *f_M2 = new RooRealVar(Form("f%s_M2", parfix.c_str()), "",0.091, 0.0, 0.2); 
   b_M1->setConstant(true);
   c_M1->setConstant(true);
   b_M2->setConstant(true);
   c_M2->setConstant(true);
   b_M3->setConstant(true);
   c_M3->setConstant(true);
   f_M1->setConstant(true); 
   f_M2->setConstant(true);  
   RooAddModel *resM = new RooAddModel("resM", "3 Gaussian",RooArgList(*gauss1, *gauss2, *gauss3),RooArgList(*f_M1, *f_M2));
   

   // Set acc functions
   // ACC_sigM for signal mc
   // ACC_sigD for signal data
   // ACC_effR = ACC_sig(D,M)/ACC_con(D,M), relative ACC ratio of control and signal
   RooRealVar *accM[nCof];
   RooRealVar *accD[nCof];
   RooRealVar *accR[nCof];

   RooArgSet *coefList_sigM = new RooArgSet();
   RooArgSet *coefList_sigD = new RooArgSet();
   RooArgSet *coefList_effR = new RooArgSet();

   for( int i=0; i<nCof; i++ ){
	accM[i] = new RooRealVar( Form("accM%s_%i",parfix.c_str(),i), "", 1.,0,10); 
	accD[i] = new RooRealVar( Form("accD%s_%i",parfix.c_str(),i), "", 1.,0,10); 
	accR[i] = new RooRealVar( Form("accR%s_%i",parfix.c_str(),i), "", 1.,0,10);
	coefList_sigM->add( RooArgList(*accM[i]) );
	coefList_sigD->add( RooArgList(*accD[i]) );
	coefList_effR->add( RooArgList(*accR[i]) );
   }
   RooAbsReal *ACC_sigM = new RooCubicSplineFun("ACC_sigM", "spline", *t, knots, *coefList_sigM);
   RooAbsReal *ACC_sigD = new RooCubicSplineFun("ACC_sigD", "spline", *t, knots, *coefList_sigD);
   RooAbsReal *ACC_effR = new RooCubicSplineFun("ACC_effR", "spline", *t, knots, *coefList_effR);

   //RooAbsReal *ACC_conM = new RooProduct("ACC_conM","@0*@1",RooArgList(*ACC_sigM,*ACC_effR));
   //RooAbsReal *ACC_conD = new RooProduct("ACC_conD","@0*@1",RooArgList(*ACC_sigD,*ACC_effR));
   RooAbsReal *ACC_conM = new RooFormulaVar("ACC_conM","@0/@1",RooArgList(*ACC_sigM,*ACC_effR));
   RooAbsReal *ACC_conD = new RooFormulaVar("ACC_conD","@0/@1",RooArgList(*ACC_sigD,*ACC_effR));
   
   // Set binned acc
   int nAccBins = (t->getMax()-t->getMin())/0.01;
   RooUniformBinning acceptanceBinning(t->getMin(),t->getMax(), nAccBins,"acceptanceBinning");
   t->setBinning(acceptanceBinning, "acceptanceBinning");

   RooBinnedPdf tacc_sigM("tacc_sigM","tacc_sigM", *t, "acceptanceBinning", *ACC_sigM);                     
   RooBinnedPdf tacc_conM("tacc_conM","tacc_conM", *t, "acceptanceBinning", *ACC_conM);                     
   RooBinnedPdf tacc_conD("tacc_conD","tacc_conD", *t, "acceptanceBinning", *ACC_conD); 
   tacc_sigM.setForceUnitIntegral(true);
   tacc_conM.setForceUnitIntegral(true);
   tacc_conD.setForceUnitIntegral(true);

   RooEffResModel resacc_sigM("resacc_sigM","resacc_sigM",*resM,tacc_sigM);
   RooEffResModel resacc_conM("resacc_conM","resacc_conM",*resM,tacc_conM);
   RooEffResModel resacc_conD("resacc_conD","resacc_conD",*resD,tacc_conD);
   et->setBins( 50, "cache");

   resacc_sigM.setParameterizeIntegral(RooArgSet(*et));
   resacc_conM.setParameterizeIntegral(RooArgSet(*et));
   resacc_conD.setParameterizeIntegral(RooArgSet(*et));

   // Set the fit pdf
   RooRealVar *tau_sigM = new RooRealVar("tau_sigM","",1.517,1.5,1.65);
   RooRealVar *tau_conM = new RooRealVar("tau_conM","",1.638,1.5,1.65);
   RooRealVar *tau_conD = new RooRealVar("tau_conD","",1.638,1.5,1.65);
   //RooDecay *fitpdf_sigM = new RooDecay("fitpdf_sigM","", *t, *tau_sigM, resacc_sigM, RooDecay::SingleSided);
   //RooDecay *fitpdf_conM = new RooDecay("fitpdf_conM","", *t, *tau_conM, resacc_conM, RooDecay::SingleSided);
   //RooDecay *fitpdf_conD = new RooDecay("fitpdf_conD","", *t, *tau_conD, resacc_conD, RooDecay::SingleSided);


   RooBDecay *fitpdf_sigM = new RooBDecay("fitpdf_sigM","",*t,*tau_sigM,*DeltaG,RooConst(1.),RooConst(0),RooConst(0),RooConst(0),*Dm,resacc_sigM,RooBDecay::SingleSided);
   RooBDecay *fitpdf_conM = new RooBDecay("fitpdf_conM","",*t,*tau_conM,*DeltaG,RooConst(1.),RooConst(0),RooConst(0),RooConst(0),*Dm,resacc_conM,RooBDecay::SingleSided);
   RooBDecay *fitpdf_conD = new RooBDecay("fitpdf_conD","",*t,*tau_conD,*DeltaG,RooConst(1.),RooConst(0),RooConst(0),RooConst(0),*Dm,resacc_conD,RooBDecay::SingleSided);
   
   RooRealVar *ftau = new RooRealVar("ftau","",ftau_val);
   RooFormulaVar *tau_sigD = new RooFormulaVar("tau_sigD","@0*@1",RooArgSet(*ftau,*tau_conD));

   // Set the set of pars
   RooArgSet *resSet = new RooArgSet();
   resSet->add( RooArgSet( *ftau, *DeltaG, *tau_conD, *tau_sigM, *tau_conM, *res_muD, *res_muM ) );
   //jpsikst
   //resSet->add( RooArgSet( *sD0, *sD1, *sD2, *sM0, *sM1, *sM2 ) );
   //jpsiks
   resSet->add( RooArgSet( *sD0, *sD1, *sD2,*b_M1, *c_M1,*b_M2, *c_M2,*b_M3, *c_M3,*f_M1, *f_M2) );
   RooArgSet *inforpar = new RooArgSet();
   inforpar->add( *coefList_sigM );
   inforpar->add( *coefList_sigD );
   inforpar->add( *coefList_effR );
   inforpar->add( *resSet );
   inforpar->readFromFile( offitpar.c_str() );
   inforpar->readFromFile( ifresodata.c_str() );
   inforpar->readFromFile( ifresomc.c_str() );

   for( int i=0; i<nCof; i++ ){
	accD[i]->setConstant(0);
	accM[i]->setConstant(0);
	accR[i]->setConstant(0);
   }

   // Set the i-th accp pars to be fixed as 1
   int ith = 4;
   accD[ith]->setConstant(1);
   accM[ith]->setConstant(1);
   accR[ith]->setConstant(1);
   accD[ith]->setVal(1);
   accM[ith]->setVal(1);
   accR[ith]->setVal(1);


   if( Dg ) DeltaG->setVal( dg_val );

   ftau->setVal( ftau_val );
   tau_sigM->setVal( tau_sigM_val );
   tau_conM->setVal( tau_conM_val );
   tau_conD->setVal( tau_conD_val );   
   inforpar->Print("sv");
   tau_sigM->setConstant(true);
   tau_conM->setConstant(true);
   tau_conD->setConstant(true);

   // Set factor of Sumw2/Sumw
   RooRealVar *fw[3];
   for( int i=0; i<3; i++ ){ fw[i] = new RooRealVar( Form("fw%i",i),"",1.); }
   fw[0]->setVal( Calfnll(tree_sigM, wgt_sigM ) );
   fw[1]->setVal( Calfnll(tree_conM, wgt_conM ) );
   fw[2]->setVal( Calfnll(tree_conD, wgt_conD ) );
   fw[0]->setConstant(1);
   fw[1]->setConstant(1);
   fw[2]->setConstant(1);

   // Set Conditional set
   RooArgSet *CondSet = new RooArgSet(*et);

   RooFitResult *fitres;
   if( !Nfit ) {
	// Create NLL functions
	int nCpu = 8;
	RooAbsReal *nll_sigM, *nll_conM, *nll_conD;
	nll_sigM = fitpdf_sigM->createNLL(*data_sigM,Optimize(0),ConditionalObservables(*CondSet), NumCPU(nCpu));
	nll_conM = fitpdf_conM->createNLL(*data_conM,Optimize(0),ConditionalObservables(*CondSet), NumCPU(nCpu));
	nll_conD = fitpdf_conD->createNLL(*data_conD,Optimize(0),ConditionalObservables(*CondSet), NumCPU(nCpu));
	RooFormulaVar *nll = new RooFormulaVar("nll","@0*@3+@1*@4+@2*@5", RooArgSet(*nll_sigM,*nll_conM,*nll_conD,*fw[0],*fw[1],*fw[2]));

	RooMinuit mCC(*nll);
	mCC.setErrorLevel(0.5);
	mCC.setStrategy(1);
	mCC.setVerbose(0);
	//mCC.setVerbose(kTRUE);
	mCC.setPrintLevel(2);
	
	double edmval;
	for( int i=0; i<3; i++ ){
	   mCC.migrad();
	   if( Hesse ) mCC.hesse();    
	   fitres = mCC.save();
	   edmval =fitres->edm();
	   if( edmval<5e-4 || edmval>200 ) break;
	}
	printf(" ***NLL = %15.2f\n", nll->getVal());
	//mCC.minos(RooArgSet(*accD[0],*accD[3],*accD[5],*accD[7])); 
	fitres->SetName("fitres");
	fitres->Print("v");

	inforpar->writeToFile( offitpar.c_str() );
	if( !Vali ) coefList_sigD->writeToFile( oftaccpar.c_str() );

	TFile *newfile = new TFile( offitres.c_str(), "recreate" );
	newfile->cd();
	fitres->Write();
	newfile->Close();
   }else{
	TFile *iffitres = new TFile( offitres.c_str() );
	fitres = (RooFitResult *)iffitres->Get("fitres");
	iffitres->Close();
	fitres->Print("v");
   }
	inforpar->readFromFile( offitpar.c_str() );
	inforpar->writeToFile( offitpar.c_str() );

   // Draw and save the plots
   int nBin = (t_h-t_l)/0.1;

   RooDataHist *projdata1 = new RooDataHist("projdata1","",*et,*data_sigM);
   RooDataHist *projdata2 = new RooDataHist("projdata2","",*et,*data_conM);
   RooDataHist *projdata3 = new RooDataHist("projdata3","",*et,*data_conD);
   RooDataHist *projdata4 = new RooDataHist("projdata4","",*et,*data_sigD);
   
   RooPlot *vframe1 = t->frame( Bins(nBin) );
   RooPlot *vframe2 = t->frame( Bins(nBin) );
   RooPlot *vframe3 = t->frame( Bins(nBin) );

   data_sigM->plotOn(vframe1,MarkerSize(0.5));
   data_conM->plotOn(vframe2,MarkerSize(0.5));
   data_conD->plotOn(vframe3,MarkerSize(0.5));
   fitpdf_sigM->plotOn(vframe1,ProjWData(*projdata1),Name("PDF1"));
   fitpdf_conM->plotOn(vframe2,ProjWData(*projdata2),Name("PDF2"));
   fitpdf_conD->plotOn(vframe3,ProjWData(*projdata3),Name("PDF3"));
   data_sigM->plotOn(vframe1,MarkerSize(0.5),Name("Data1"));
   data_conM->plotOn(vframe2,MarkerSize(0.5),Name("Data2"));
   data_conD->plotOn(vframe3,MarkerSize(0.5),Name("Data3"));
   vframe1->SetMinimum(1e-2);
   vframe2->SetMinimum(1e-2);
   vframe3->SetMinimum(1e-2);

   // Set logo
   TPaveText *logo1 = new TPaveText( 0.70, 0.75, 0.80, 0.85, "BRNDC" );
   logo1->AddText("#font[132]{LHCb}");
   SetLogo( logo1 );

   vframe1->addObject(logo1);
   vframe2->addObject(logo1);
   vframe3->addObject(logo1);

   char XTitle[] = "#it{t} [ps]";
   char YTitle1[] = "Candidates / ( 0.1 ps )";

   string picname1 = Form("output/%s_fit_sigmc_%s",  prefix.c_str(), Year.c_str());
   string picname2 = Form("output/%s_fit_conmc_%s",  prefix.c_str(), Year.c_str());
   string picname3 = Form("output/%s_fit_condata_%s",prefix.c_str(), Year.c_str());

   RooSaveFitPlot( "Data1", "PDF1", t, vframe1, XTitle, YTitle1, picname1.c_str(), 0, 0, 1);
   RooSaveFitPlot( "Data2", "PDF2", t, vframe2, XTitle, YTitle1, picname2.c_str(), 0, 0, 1);
   RooSaveFitPlot( "Data3", "PDF3", t, vframe3, XTitle, YTitle1, picname3.c_str(), 0, 0, 1);

   // Get the binned acceptance using histogram method
   //RooDecay *genpdf_sigM = new RooDecay("genpdf_sigM","", *t, *tau_sigM, *resM, RooDecay::SingleSided);
   //RooDecay *genpdf_conM = new RooDecay("genpdf_conM","", *t, *tau_conM, *resM, RooDecay::SingleSided);
   //RooDecay *genpdf_sigD = new RooDecay("genpdf_sigD","", *t, *tau_sigD, *resD, RooDecay::SingleSided);
   //RooDecay *genpdf_conD = new RooDecay("genpdf_conD","", *t, *tau_conD, *resD, RooDecay::SingleSided);
   RooBDecay *genpdf_sigM = new RooBDecay("genpdf_sigM","",*t,*tau_sigM,*DeltaG,RooConst(1.),RooConst(0),RooConst(0),RooConst(0),*Dm,*resM,RooBDecay::SingleSided);
   RooBDecay *genpdf_conM = new RooBDecay("genpdf_conM","",*t,*tau_conM,*DeltaG,RooConst(1.),RooConst(0),RooConst(0),RooConst(0),*Dm,*resM,RooBDecay::SingleSided);
   RooBDecay *genpdf_sigD = new RooBDecay("genpdf_sigD","",*t,*tau_sigD,*DeltaG,RooConst(1.),RooConst(0),RooConst(0),RooConst(0),*Dm,*resD,RooBDecay::SingleSided);
   RooBDecay *genpdf_conD = new RooBDecay("genpdf_conD","",*t,*tau_conD,*DeltaG,RooConst(1.),RooConst(0),RooConst(0),RooConst(0),*Dm,*resD,RooBDecay::SingleSided);


#if 1
   const int hBin1 = 100;
   TH1D *hselt_sigM = new TH1D("hselt_sigM","",hBin1,t_l,t_h);
   TH1D *hselt_conM = new TH1D("hselt_conM","",hBin1,t_l,t_h);
   TH1D *hselt_sigD = new TH1D("hselt_sigD","",hBin1,t_l,t_h);
   TH1D *hselt_conD = new TH1D("hselt_conD","",hBin1,t_l,t_h);
   TH1D *htacc_sigM = new TH1D("htacc_sigM","",hBin1,t_l,t_h);
   TH1D *htacc_conM = new TH1D("htacc_conM","",hBin1,t_l,t_h);
   TH1D *htacc_sigD = new TH1D("htacc_sigD","",hBin1,t_l,t_h);
   TH1D *htacc_conD = new TH1D("htacc_conD","",hBin1,t_l,t_h);
   
   // fillHistogram() can consider the weight of dataset
   data_sigM->fillHistogram( hselt_sigM,*t );
   data_conM->fillHistogram( hselt_conM,*t );
   data_sigD->fillHistogram( hselt_sigD,*t );
   data_conD->fillHistogram( hselt_conD,*t );

   TH1D *hgent_sigM = (TH1D*)genpdf_sigM->createHistogram("hgent_sigM", *t, ProjWData(*projdata1), Binning(hBin1,t_l,t_h));
   TH1D *hgent_conM = (TH1D*)genpdf_conM->createHistogram("hgent_conM", *t, ProjWData(*projdata2), Binning(hBin1,t_l,t_h));
   TH1D *hgent_conD = (TH1D*)genpdf_conD->createHistogram("hgent_conD", *t, ProjWData(*projdata3), Binning(hBin1,t_l,t_h));
   TH1D *hgent_sigD = (TH1D*)genpdf_sigD->createHistogram("hgent_sigD", *t, ProjWData(*projdata4), Binning(hBin1,t_l,t_h));

   hgent_sigM->Scale( hselt_sigM->Integral()/hgent_sigM->Integral() );
   hgent_conM->Scale( hselt_conM->Integral()/hgent_conM->Integral() );
   hgent_sigD->Scale( hselt_sigD->Integral()/hgent_sigD->Integral() );
   hgent_conD->Scale( hselt_conD->Integral()/hgent_conD->Integral() );

   for( int i=0; i<hgent_sigM->GetNbinsX(); i++ ){
      hgent_sigM->SetBinError(i,0);
      hgent_conM->SetBinError(i,0);
      hgent_sigD->SetBinError(i,0);
      hgent_conD->SetBinError(i,0);
   }
   
   double sum_sigM = 0;
   double sum_conM = 0;
   double sum_sigD = 0;
   double sum_conD = 0;
   for( int i=0; i<htacc_sigM->GetNbinsX(); i++ ){
	*t = hgent_sigM->GetBinCenter(i+1);
	sum_sigM += hgent_sigM->GetBinContent(i+1) * ACC_sigM->getVal(*t);
	sum_conM += hgent_conM->GetBinContent(i+1) * ACC_conM->getVal(*t);
	sum_sigD += hgent_sigD->GetBinContent(i+1) * ACC_sigD->getVal(*t);
	sum_conD += hgent_conD->GetBinContent(i+1) * ACC_conD->getVal(*t);
   }

   htacc_sigM->Divide( hselt_sigM, hgent_sigM, sum_sigM, hgent_sigM->Integral() );
   htacc_conM->Divide( hselt_conM, hgent_conM, sum_conM, hgent_conM->Integral() );
   htacc_sigD->Divide( hselt_sigD, hgent_sigD, sum_sigD, hgent_sigD->Integral() );
   htacc_conD->Divide( hselt_conD, hgent_conD, sum_conD, hgent_conD->Integral() );
   
   // for the relative efficiency obtained by sWeighted data and MC
   TH1D *htacc_effD = new TH1D("htacc_effD","",hBin1,t_l,t_h);
   TH1D *htacc_effM = new TH1D("htacc_effM","",hBin1,t_l,t_h);
   
   htacc_effD->Divide( htacc_sigD, htacc_conD, 1, 1 );
   htacc_effM->Divide( htacc_sigM, htacc_conM, 1, 1 );
  
   RooDataHist *adata_sigM = new RooDataHist("adata_sigM","",RooArgSet(*t),htacc_sigM);
   RooDataHist *adata_conM = new RooDataHist("adata_conM","",RooArgSet(*t),htacc_conM);
   RooDataHist *adata_conD = new RooDataHist("adata_conD","",RooArgSet(*t),htacc_conD);
   RooDataHist *adata_sigD = new RooDataHist("adata_sigD","",RooArgSet(*t),htacc_sigD);
   RooDataHist *adata_effD = new RooDataHist("adata_effD","",RooArgSet(*t),htacc_effD);
   RooDataHist *adata_effM = new RooDataHist("adata_effM","",RooArgSet(*t),htacc_effM);

   // Save the acceptance plots
   Color_t FCol[5] = { kOrange,   kAzure+1, kMagenta-9, kPink-4, kGray };
   Color_t LCol[5] = { kOrange+1, kAzure,   kMagenta,   kPink+8, kBlack };

   string YTitle[5] = {
      //kstar
   //  "#it{#varepsilon}^{#it{J/#psiK^{*0}}}_{MC}",
   //  "#it{#varepsilon}^{#it{J/#psiK^{+}}}_{MC}",
   //  "#it{#varepsilon}^{#it{J/#psiK^{+}}}_{data}",
   //  "#it{#varepsilon}^{#it{J/#psiK^{+}}}_{data}#times#it{#varepsilon}^{#it{J/#psiK^{*0}}}_{MC}/#it{#varepsilon}^{#it{J/#psiK^{+}}}_{MC}",
   //  "#it{#varepsilon}^{#it{J/#psiK^{*0}}}_{MC}/#it{#varepsilon}^{#it{J/#psiK^{+}}}_{MC}"
    //kshort K_{S}^{0}
     "#it{#varepsilon}^{#it{J/#psiK_{S}^{0}}}_{MC}",
	  "#it{#varepsilon}^{#it{J/#psiK^{+}}}_{MC}",
	  "#it{#varepsilon}^{#it{J/#psiK^{+}}}_{data}",
	  "#it{#varepsilon}^{#it{J/#psiK^{+}}}_{data}#times#it{#varepsilon}^{#it{J/#psiK_{S}^{0}}}_{MC}/#it{#varepsilon}^{#it{J/#psiK^{+}}}_{MC}",
	  "#it{#varepsilon}^{#it{J/#psiK_{S}^{0}}}_{MC}/#it{#varepsilon}^{#it{J/#psiK^{+}}}_{MC}"
   };
   if( Vali ){
	YTitle[0] = "#it{#varepsilon}^{#it{J/#psiK^{+}}}_{MC}";
	YTitle[3] = "#it{#varepsilon}^{#it{J/#psiK^{*0}}}_{data}#times#it{#varepsilon}^{#it{J/#psiK^{+}}}_{MC}/#it{#varepsilon}^{#it{J/#psiK^{*0}}}_{MC}";
	YTitle[4] = "#it{#varepsilon}^{#it{J/#psiK^{+}}}_{MC}/#it{#varepsilon}^{#it{J/#psiK^{*0}}}_{MC}";
   }

   string accpic[5] ={
	Form("%s_acc_sigM_%s",prefix.c_str(),Year.c_str()), 
	Form("%s_acc_conM_%s",prefix.c_str(),Year.c_str()),
	Form("%s_acc_conD_%s",prefix.c_str(),Year.c_str()),
	Form("%s_acc_sigD_%s",prefix.c_str(),Year.c_str()),
	Form("%s_acc_effR_%s",prefix.c_str(),Year.c_str())
   };

   TPaveText *logo2 = new TPaveText( 0.22, 0.80, 0.30, 0.90, "BRNDC" );
   logo2->AddText("#font[132]{LHCb}");
   SetLogo( logo2 );

   RooPlot *aframe[5];
   RooAbsReal *ACC_pdf[5];
   ACC_pdf[0] = ACC_sigM;
   ACC_pdf[1] = ACC_conM;
   ACC_pdf[2] = ACC_conD;
   ACC_pdf[3] = ACC_sigD;
   ACC_pdf[4] = ACC_effR;

   for( int i=0; i<5; i++ ){
	aframe[i] = t->frame();
	aframe[i]->addObject( logo2 );
	SetAccFrame( aframe[i], ACC_pdf[i], fitres, 1, FCol[i], LCol[i], XTitle, YTitle[i].c_str() );
	if( i==0 ) adata_sigM->plotOn( aframe[i], MarkerSize(0.5) );
	if( i==1 ) adata_conM->plotOn( aframe[i], MarkerSize(0.5) );
	if( i==2 ) adata_conD->plotOn( aframe[i], MarkerSize(0.5) );
	if( i==3 ) adata_sigD->plotOn( aframe[i], MarkerSize(0.5) );
	if( i==4 ){

	   ACC_pdf[i]->plotOn( aframe[i], Name("1"), LineStyle(1), MarkerColor(kBlack),LineColor(kBlack)  );
	   adata_effD->plotOn( aframe[i], Name("2"), MarkerSize(0.5), MarkerColor(kRed) ,LineColor(kRed)  );
	   adata_effM->plotOn( aframe[i], MarkerSize(0.5), MarkerColor(kBlack),LineColor(kBlack) );

	   TLegend *tmpleg = new TLegend( 0.22, 0.65, 0.40, 0.80 );
	   tmpleg->AddEntry(aframe[i]->findObject("1"),"Simulation and fit","PL");
	   tmpleg->AddEntry(aframe[i]->findObject("2"),"Data sWeighted","PEL");
	   aframe[i]->addObject(tmpleg);
	}
	aframe[i]->SetMinimum( 0.0 );
	aframe[i]->SetMaximum( 2.2 );
	SaveAccPic( aframe[i], accpic[i].c_str() );
   }

//#if 0
#if 1
   // Save the plots of comparison
   string compicname = Form("%s_acc_comp_%s",prefix.c_str(),Year.c_str());
   TCanvas *compic = new TCanvas( Form("pic_%s",compicname.c_str()),"",800,600 );
   compic->cd();

   TLegend *leg1 = new TLegend(0.2,0.66,0.4,0.90);
   leg1->SetBorderSize(0);
   leg1->SetTextFont(132);
   leg1->SetTextSize(0.05);
   leg1->SetFillColor(0);
   
   TLegend *leg2 = new TLegend(0.4,0.74,0.65,0.90);
   leg2->SetBorderSize(0);
   leg2->SetTextFont(132);
   leg2->SetTextSize(0.05);
   leg2->SetFillColor(0);
   
   RooPlot *cframe = t->frame();
   for( int i=0; i<5; i++ ){
	SetAccFrame( cframe, ACC_pdf[i], fitres, 0, FCol[i], LCol[i], XTitle, YTitle[i].c_str(), ACC_pdf[i]->GetName() );
	
	if( i<3 ) {
	   leg1->AddEntry(cframe->findObject(ACC_pdf[i]->GetName()),YTitle[i].c_str(),"L");
	}else{
	   leg2->AddEntry(cframe->findObject(ACC_pdf[i]->GetName()),YTitle[i].c_str(),"L");
	}

   }
   cframe->GetYaxis()->SetTitle("#it{#varepsilon}");
   cframe->addObject(leg1);
   cframe->addObject(leg2);
   cframe->Draw();
   
   compic->SaveAs( Form("output/%s.pdf",compicname.c_str()) );
#endif

   cout<<"========================================="<<endl;
   cout<<"sigM, chi2_NDOF(5) = "<<vframe1->chiSquare("PDF1","Data1",5)<<endl;
   cout<<"conM, chi2_NDOF(5) = "<<vframe2->chiSquare("PDF2","Data2",5)<<endl;
   cout<<"conD, chi2_NDOF(5) = "<<vframe3->chiSquare("PDF3","Data3",5)<<endl;
   cout<<"========================================="<<endl;

   // Extract tau_B+/tau_B0 for validation
   if( Chck ){

	// set the PDF for Bu data
	RooBinnedPdf tacc_sigD("tacc_sigD","tacc_sigD", *t, "acceptanceBinning", *ACC_sigD);                     
	tacc_sigD.setForceUnitIntegral(true);

	RooEffResModel resacc_sigD("resacc_sigD","resacc_sigD",*resD,tacc_sigD);
	et->setBins(50,"cache");
	resacc_sigD.setParameterizeIntegral(RooArgSet(*et));

	RooDecay *fitpdf_sigD = new RooDecay("fitpdf_sigD","", *t, *tau_sigD, resacc_sigD, RooDecay::SingleSided);

	// fix the time acceptance pars
	RooArgSet *ConsSet = new RooArgSet();

	for( int i=0; i<nCof; i++ ){
	   accD[i]->setConstant(0);
	   //if( i!=4 ){
	   if( i>1 && i!=4 ){
		double conval = accD[i]->getVal();
		double conerr = accD[i]->getError();
		RooGaussian *ConsAcc  = new RooGaussian(Form("Cons_%s",accD[i]->GetName()),"",*accD[i],RooConst(conval),RooConst(conerr));
		ConsSet->add( *ConsAcc );
	   }
	}
	accD[ith]->setConstant(1);

	// float the time ratio
	ftau->setConstant(0);
	ftau->setRange(0.9,1.1);
	cout<<"==========================================="<<endl;
	cout<<" Constrained parameters : "<<endl;
	ConsSet->Print("v");
	cout<<"==========================================="<<endl;

	if( Vali ){
	   fitpdf_sigD->fitTo(*data_sigD,Optimize(0),
		   ConditionalObservables(*CondSet),ExternalConstraints(*ConsSet),NumCPU(8));
	}

	RooArgSet *inforpar2 = fitpdf_sigD->getParameters( *data_sigD );
	inforpar2->Print("v");
	inforpar2->writeToFile( Form("parinfor/tau_ratio_%s_%s.dat",prefix.c_str(),Year.c_str()) );

	// draw the plot
	RooAbsData *projdata4 = data_sigD->binnedClone();

	RooPlot *vframe4 = t->frame( Bins(nBin) );
	data_sigD->plotOn(vframe4,MarkerSize(0.5));
	fitpdf_sigD->plotOn(vframe4,ProjWData(*CondSet,*projdata4),Name("PDF4"));
	data_sigD->plotOn(vframe4,MarkerSize(0.5),Name("Data4"));
	vframe4->SetMinimum(1e-2);
	vframe4->addObject(logo1);

	string picname4 = Form("output/%s_fit_sigdata_%s",prefix.c_str(),Year.c_str());
	RooSaveFitPlot( "Data4", "PDF4", t, vframe4, XTitle, YTitle1, picname4.c_str(), 0, 0, 1);
   
	cout<<"========================================="<<endl;
	cout<<" sigD, chi2_NDOF(5) = "<<vframe4->chiSquare("PDF4","Data4",5)<<endl;
	cout<<"========================================="<<endl;
   }

   cout<<"==========================================="<<endl;
   cout<<" ENDING  TIME : "<<endl;
   system("date");
   cout<<"==========================================="<<endl;
#endif
}



