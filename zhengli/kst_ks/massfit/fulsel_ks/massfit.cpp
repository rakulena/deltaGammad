#define massfit_cxx
#include "massfit.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "../../inc/headfile.h"
#include "../../inc/RooIpatia2.h"
#include "../../inc/RooSaveFitPlot.C"

void massfit::Loop( Long64_t runevt, const char *runmode )
{
   // This is the loop skeleton where:
   //    jentry is the global entry number in the chain
   //    ientry is the entry number in the current Tree
   // Note that the argument to GetEntry must be:
   //    jentry for TChain::GetEntry
   //    ientry for TTree::GetEntry and TBranch::GetEntry
   // Long64_t nentries = fChain->GetEntriesFast();
   if (fChain == 0) return;

   gROOT->ProcessLine(".x ../../inc/lhcbStyle.C");

   // Set the mode, mvacut, mass window and output
   string mode = runmode;
   cout<<"==================================== "<<endl;
   cout<<" run mode : "<<mode<<endl;
   cout<<"==================================== "<<endl;

   int    nBin = 100; 
   double mvacut = 0; // same as the signal channel
   double mass_l = 5220.;
   double mass_h = 5330.;

   bool mc    = mode.find("mc")!=string::npos;
   bool Y2016 = mode.find("Y2016")!=string::npos;
   bool Y2017 = mode.find("Y2017")!=string::npos;
   bool Y2018 = mode.find("Y2018")!=string::npos;
   bool Nfit  = mode.find("Nfit")!=string::npos;
   bool Calw  = mode.find("Calw")!=string::npos;
   bool Nmc = !mc;

   string prefix = "data";
   string endfix = "_base";
   string Year = "_2016";
   if( Y2016 ){ Year = "_2016";
   mvacut = 0.40;
    }
   if( Y2017 ){ Year = "_2017";
   mvacut = 0.36;
    }
   if( Y2018 ){ Year = "_2018"; 
   mvacut = 0.35;
   }
   if( mc ){ prefix = "mc"; Calw = 0; }
   if( Calw ) Nfit = 1;
   
   string offitpar1 = "./parinfor/"+prefix+endfix+Year+".dat";
   string picname = Form("../output/Bdjpsikshort_%s%s%s",prefix.c_str(),endfix.c_str(),Year.c_str());
   string ofroot  = Form("/lzufs/user/zhanghy/Sample/afterBDT/after_Bd2JpsiKshort_data%s_sw%s.root",Year.c_str(),endfix.c_str());
   //Define fit pdfs
   //---------------------------------------------

   // Set the PDF signal
   RooRealVar *mass = new RooRealVar("mass","",mass_l,mass_h,"MeV");
   RooRealVar *mean1  = new RooRealVar("mean1","",5279.7,5200,5300);

   RooRealVar *zeta = new RooRealVar("zeta","",0.);
   RooRealVar *fb   = new RooRealVar("fb","",0.);

   // ca(n)_l(r)1 for Bd signal from MC fit
    RooRealVar *l1    = new RooRealVar("l1","",-3.26419,-30.,-1.);
   RooRealVar *ca_l1 = new RooRealVar("ca_l1","",2.0653,0.,5.);
   RooRealVar *cn_l1 = new RooRealVar("cn_l1","",2.6311,0.,20.);
   RooRealVar *ca_r1 = new RooRealVar("ca_r1","",2.2218,0.,5.);
   RooRealVar *cn_r1 = new RooRealVar("cn_r1","",5.2333,0.,20.);
   
   //double gaussian
    RooRealVar *sigma1 = new RooRealVar("sigma1","",10.,0.,20.);
   // RooRealVar *sigma2 = new RooRealVar("sigma2","",5,0.,10.);
   // RooRealVar  *frac = new RooRealVar("frac","",0.5,0.,1.);
   // RooGaussian *sig = new RooGaussian("sig","",*mass,*mean1,*sigma1);
   // RooGaussian *sig2 = new RooGaussian("sig2","",*mass,*mean1,*sigma2);
   // RooAbsPdf   *sig1  = new RooAddPdf("sig1","",RooArgList(*sig,*sig2),RooArgList(*frac));
   
   //single gaussian
   //RooRealVar *sigma1 = new RooRealVar("sigma1","",10.,0.,20.);
   //RooGaussian *sig1 = new RooGaussian("sig1","",*mass,*mean1,*sigma1);
 
   RooIpatia2 *sig1 = new RooIpatia2("sig1","",*mass,*l1,*zeta,*fb,*sigma1,*mean1,*ca_l1,*cn_l1,*ca_r1,*cn_r1);
   // Set the PDF for background
   RooRealVar *C_exp = new RooRealVar("C_exp","",0.0597819,-1,1);
   RooExponential *bkg1 = new RooExponential("bkg1","",*mass,*C_exp);

   // Set the global function
   RooRealVar *nsig1 = new RooRealVar("nsig1","", 33501,0,3e6);
   RooRealVar *nbkg1 = new RooRealVar("nbkg1","", 5000,0,1e6);
   RooRealVar *fitedm = new RooRealVar("fitedm","",1e-3);

   RooArgSet *pdfList;
   RooArgSet *numList;
   RooAbsPdf *unition;
   if( mc ){
	unition = sig1;
   }
   if( Nmc ){ 
	pdfList = new RooArgSet( *sig1, *bkg1);
	numList = new RooArgSet(*nsig1,*nbkg1);
	unition = new RooAddPdf("unition","unition PDF",*pdfList,*numList);
   }

   fChain->SetBranchStatus("*",0);
   fChain->SetBranchStatus("Bd_ConstJpsi_M",1);
   fChain->SetBranchStatus("BDT",1);

   RooDataSet *data  = new RooDataSet("data","data",RooArgSet(*mass));

   Long64_t nentries = runevt;
   for(Long64_t jentry=0; jentry<nentries;jentry++) {

	if(jentry%50000==0) cout<<"  Processing "<<jentry/1000<<" k. "<<endl;
	Long64_t ientry = LoadTree(jentry);
	if(ientry < 0) break;

	fChain->GetEntry(jentry);

   if(!( Bd_ConstJpsi_M>mass_l && Bd_ConstJpsi_M<mass_h&&BDT>mvacut )) continue;

	*mass = Bd_ConstJpsi_M;
	data->add(RooArgSet(*mass));
   }

   cout<<"-------------------------------------------"<<endl;
   cout<<" DataSet : "<<endl;
   data->Print();
   cout<<"-------------------------------------------"<<endl<<endl;
   RooArgSet *inforpar = unition->getParameters(*data);

   // Fit the data
   inforpar->readFromFile( offitpar1.c_str() );
   inforpar->add( *fitedm );
   
   if( !Nfit ){
      if( mc ){ 
         fb->setConstant(1);
         zeta->setConstant(1);
         l1->setConstant(0);
         ca_l1->setConstant(0);
         ca_r1->setConstant(0);
         cn_l1->setConstant(0);
         cn_r1->setConstant(0);
      }else{
         l1->setConstant(1);
         ca_l1->setConstant(1);
         ca_r1->setConstant(1);
         cn_l1->setConstant(1);
         cn_r1->setConstant(1);
      }

      // Fit the data
      double edmval;
      for( int nf=0; nf<3; nf++){
         RooAbsReal *nll = unition->createNLL(*data,NumCPU(5));

	   RooMinimizer mCC(*nll);
	   mCC.setStrategy(1);
	   mCC.setVerbose(kFALSE);
	   mCC.setPrintLevel(2);
	   mCC.migrad();
	   mCC.hesse();
	   RooFitResult *fitres = mCC.save();

	   edmval = fitres->edm();
	   fitedm->setVal( edmval );
	   if( edmval<1e-4 || edmval>100 ) break;
	}
	inforpar->writeToFile( offitpar1.c_str() );
	cout<<"==================================== "<<endl;
	cout<<" EDM Value : "<<edmval<<endl;
	cout<<"==================================== "<<endl;
   }

   // Set the frame
   RooPlot *frame = mass->frame( Bins(nBin) );
   data->plotOn(frame,MarkerSize(0.8),MarkerColor(kBlack));
   unition->plotOn(frame,Name("unition_all"),LineWidth(3));

   if( Nmc ){
	unition->plotOn(frame,Components(*sig1),Name("1"),LineStyle(9),LineWidth(2),LineColor(kRed));
	unition->plotOn(frame,Components(*bkg1),Name("3"),LineStyle(7),LineWidth(2),LineColor(kGreen+2));
   }
   data->plotOn(frame,Name("unition_fit"),MarkerSize(0.8),MarkerColor(kBlack));

   // Set TLatex
   char name_fit[400];
   TLatex *mytex;
   if( !mc ){
	sprintf(name_fit,
		"#splitline{N_{B_{d}} = %.0f #pm %.0f}{N_{bkg} = %.0f #pm %.0f}",
		nsig1->getVal(), nsig1->getError(),
		nbkg1->getVal(), nbkg1->getError()
		);
	mytex = new TLatex(0.23,0.40,name_fit);
   }else{
	mytex = new TLatex(0.97,0.97,"");
   }
   mytex->SetTextFont(132);
   mytex->SetTextSize(0.045);
   mytex->SetLineWidth(2);
   mytex->SetNDC();

   // Set logo
   TPaveText *logo = new TPaveText( 0.22, 0.80, 0.35, 0.87, "BRNDC" );
   logo->AddText("#font[132]{LHCb}");

   // Set Tlegend
   TLegend *leg;
   if( Nmc ){
	leg = new TLegend(0.22,0.52,0.40,0.78);
	leg->AddEntry(frame->findObject("unition_all"), "Data and fit","PL");
	leg->AddEntry(frame->findObject("1"), "#it{B^{0}#rightarrowJ/#psiK_{s}^{0}}","L");
	leg->AddEntry(frame->findObject("3"), "Combinatorial","L");
	leg->SetBorderSize(0);
	leg->SetTextFont(132);
	leg->SetTextSize(0.045);
	leg->SetFillColor(0);
   }else{
	leg = new TLegend(0.05,0.97,0.06,0.98);
   }

   const char* XTitle = "#it{m}(#it{J/#psi}#it{K_{s}^{0}}) [MeV/#it{c}^{2}]";
   const char* YTitle = Form("Candidates / (%.2lf MeV/#it{c}^{2})", (mass_h-mass_l)/nBin );
   if( Nmc ){
	RooSaveFitPlot( data, unition, mass, frame, logo, mytex, leg, XTitle, YTitle, picname.c_str(), 0, 0, 1);
   }else{
	RooSaveFitPlot( data, unition, mass, frame, logo, mytex, leg, XTitle, YTitle, picname.c_str(), 0, 0, 1);
   }

   double chi2_ndof5 = frame-> chiSquare("unition_all","unition_fit",5);
   double chi2_ndof9 = frame-> chiSquare("unition_all","unition_fit",9);
   cout<<"========================================="<<endl;
   cout<< "chiSquare_NDOF(5) =" << chi2_ndof5 << endl;
   cout<< "chiSquare_NDOF(9) =" << chi2_ndof9 << endl;
   cout<<"========================================="<<endl;

   if( Calw ){
      fChain->SetBranchStatus("*",1);

	RooStats::SPlot *splot = new RooStats::SPlot("splot","splot",*data,unition,*numList);
	splot->Print();
	data->Print("v");

	// Create a root file for saving data and Clone the tree
	double sig_sw,bkg_sw;

	TFile *rootfile = new TFile(ofroot.c_str(),"recreate");
	TTree *newtree = fChain->CloneTree(0);

	newtree->Branch("sig_sw",&sig_sw,"sig_sw/D");
	newtree->Branch("bkg_sw",&bkg_sw,"bkg_sw/D");

	// Fill the tree and save the data to rootfile
	int Num=0;
	for(int i=0;i<runevt;i++){
	   fChain->GetEntry(i);

      if(!( Bd_ConstJpsi_M>mass_l && Bd_ConstJpsi_M<mass_h&BDT>mvacut )) continue;

	   sig_sw = splot->GetSWeight( Num, nsig1->GetName() );
	   bkg_sw = splot->GetSWeight( Num, nbkg1->GetName() );
	   Num++;

	   newtree->Fill();
	}
	rootfile->cd();
	newtree->Write();
	rootfile->Close();

	//delete rootfile;
   }

   //Execute some linux commads
   cout<<"========================================="<<endl;
   system( Form("cat %s",offitpar1.c_str()) );
   cout<<"========================================="<<endl;
//   system( Form("evince %s.pdf",picname.c_str()) );
//cout << "nbkg1 = " << nbkg1->getVal() << " ± " << nbkg1->getError() << endl;

}
