#include "../inc/headfile.h"
#include "../inc/Calfnll.C"
#include "../inc/RooSaveFitPlot.C"
#include "../src/RooEffResModel.h"
#include "../src/RooBinnedPdf.h"
#include "../src/RooCubicSplineFun.h"
#include "../inc/RooMinuit.h"

using namespace RooFit;

void SetAccFrame(
    RooPlot *vframe,
    RooAbsReal *ACC_pdf,
    RooFitResult *fitres,
    bool isViserr,
    Color_t FCol,
    Color_t LCol,
    const char *XTitle,
    const char *YTitle,
    string lineobj = "")
{
   if (isViserr) ACC_pdf->plotOn(vframe, VisualizeError(*fitres, 1), FillColor(FCol));
   if (lineobj == "") {
        ACC_pdf->plotOn(vframe, LineStyle(1), LineColor(LCol));
   } else {
        ACC_pdf->plotOn(vframe, LineStyle(1), LineColor(LCol), Name(lineobj.c_str()));
   }
   vframe->SetMinimum(0.);
   vframe->SetMaximum(2.2);
   vframe->GetXaxis()->SetTitle(XTitle);
   vframe->GetYaxis()->SetTitle(YTitle);
   vframe->GetXaxis()->SetTitleFont(132);
   vframe->GetYaxis()->SetTitleFont(132);
   vframe->GetXaxis()->SetTitleSize(0.06);
   vframe->GetYaxis()->SetTitleSize(0.06);
   vframe->GetXaxis()->SetTitleOffset(1.05);
   vframe->GetYaxis()->SetTitleOffset(1.05);
   vframe->GetXaxis()->SetLabelSize(0.06);
   vframe->GetYaxis()->SetLabelSize(0.06);
}

void SaveAccPic(
    RooPlot *vframe,
    const char *picname)
{
   TCanvas *pic = new TCanvas(Form("pic_%s", picname), "", 10, 10, 800, 600);
   pic->cd();
   vframe->Draw();
   pic->SaveAs(Form("output/%s.pdf", picname));
}

int main(int argc, char **argv)
{
   RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
   gROOT->GetListOfCleanups();
   gROOT->ProcessLine(".x ../inc/lhcbStyle.C");

   cout << "===========================================" << endl;
   cout << " STARTING  TIME : " << endl;
   system("date");
   cout << "===========================================" << endl;

   // Command line parameter defaults
   double nfrac = 1;
   string mode = "";

   // Parse command line
   int c;
   while ((c = getopt(argc, argv, "hn:n:m:")) != -1) {
        switch (c) {
            case 'h':
                cout << "Usage: " << argv[0] << endl
                     << "         [-h] [-n <number_of_events>] " << endl
                     << "         [-m mode]     " << endl;
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

   bool Nfit = mode.find("Nfit") != string::npos;
   bool Vali = mode.find("Vali") != string::npos;
   bool Chck = mode.find("Chck") != string::npos;
   bool Y2017 = mode.find("Y2017") != string::npos;
   bool Y2018 = mode.find("Y2018") != string::npos;
   bool Dg = mode.find("Dg") != string::npos;
   bool Hesse = mode.find("Hesse") != string::npos;
   cout << "==================================" << endl;
   cout << " Mode : " << mode << endl;
   cout << "==================================" << endl;

   // define 3 years
   const int ny = 3;
   int years[ny] = {2016, 2017, 2018};
   string parfix[ny] = {"16", "17", "18"};
   
   string prefix = "base";
   double ftau_val = 1.;
   double dg_val = 0.01;
   double tau_val = 1.517;

   if (Vali) {
        prefix = "vali";
        ftau_val = 1.076;
        tau_val = 1.639;
   }
   if (Dg) {
        prefix = "dg";
   }

   string ifknots = "parinfor/knots_base";
   string ifresodata = "../FinalInput/reso_cali_data.dat"; 
   string ifresomc = "../FinalInput/reso_cali_mc.dat"; 
   string offitpar  = Form("parinfor/parinfor_%s_allyears.dat", prefix.c_str());
   string oftaccpar = Form("../FinalInput/tacc_coef_%s_allyears.dat", prefix.c_str());
   string offitres = Form("output/taccres_%s_allyears.root", prefix.c_str());

   cout << "=======================================================" << endl;
   cout << " Three years joint fit: 2016, 2017, 2018" << endl;
   cout << " knots file: " << ifknots << endl;
   cout << " fit parameters: " << offitpar << endl;
   cout << " fit rootfile: " << offitres << endl;
   cout << "=======================================================" << endl;
   cout << " Read the knots " << endl;
   cout << "=======================================================" << endl;

   // Read the knots
   ifstream iffile(ifknots.c_str());
   if (!iffile) {
        cout << "---------------------------------- " << endl;
        cout << "  The file of knots doesn't exit ! =_= " << endl;
        cout << "---------------------------------- " << endl;
        iffile.close();
        exit(0);
   }

   std::vector<double> knots;
   knots.clear();
   while (1) {
        double tmpknot;
        iffile >> tmpknot;
        if (!iffile.good()) break;
        knots.push_back(tmpknot);
        cout << "  " << tmpknot << endl;
   }
   iffile.close();
   const int nCof = knots.size() + 2;

   // Set the input
   char bmass[] = "Bd_ConstJpsi_M";
   char time[] = "Bd_ConstJpsi_tau";
   char timeerr[] = "Bd_ConstJpsi_tauErr";
   char wgt_sigD_kst[] = "sig_sw";
   char wgt_sigD_ks[] = "sig_sw";
   double t_l = knots[0];
   double t_h = 14;

   string cut1 = Form("%s>%.2lf&&%s<%.2lf", time, t_l, time, t_h);
   string cut_sigD_kst = Form("%s", cut1.c_str());
   string cut_sigD_ks = Form("%s", cut1.c_str());

   if (Vali) {
        cut_sigD_kst = Form("%s&&abs(%s)<100", cut1.c_str(), wgt_sigD_kst);
        cut_sigD_ks = Form("%s&&abs(%s)<100", cut1.c_str(), wgt_sigD_ks);
   }

   cout << "=======================================================" << endl;
   cout << " cut_sigD_kst: " << cut_sigD_kst << endl;
   cout << " cut_sigD_ks: " << cut_sigD_ks << endl;
   cout << "=======================================================" << endl;

   // Path templates
   string path_sigD_kst_template = "~/Sample/after_Bd2JpsiKstar_data_%s_sw_base.root/DecayTree";
   string path_sigD_ks_template = "~/Sample/after_Bd2JpsiKshort_data_%s_sw_base.root/DecayTree";

   // Set observables
   RooRealVar *t = new RooRealVar(time, "time [ps]", t_l, t_h);
   RooRealVar *et = new RooRealVar(timeerr, "time [ps]", 0., 0.15);
   RooRealVar *Dm = new RooRealVar("Dm", "", 0);

   // Shared parameters
   RooRealVar Dgd("Dgd", "deltagammad", 0.0, -0.1, 0.1, "ps^{-1}");
   
   RooRealVar tau("tau", "tau_mean", tau_val, 1.5, 1.65, "ps");
   RooFormulaVar y_d("y_d","@0*@1/2.0",RooArgList(Dgd,tau));
   RooRealVar phid("phid", "", 0.813, 0.0, M_PI/2);
   phid.setConstant(kTRUE);
   RooFormulaVar cos2beta("cos2beta", "cos(@0)", RooArgList(phid));
   RooFormulaVar tau_kst("tau_kst", "(@0 *(1+@1*@1)/(1-@1*@1))",RooArgList(tau, y_d));
   RooFormulaVar tau_ks("tau_ks", "(@0 /(1-@2*@2)) * ((1+2*@1*@2+@2*@2)/(1+@1*@2))",RooArgList(tau, cos2beta, y_d));
  
   // Arrays for each year
   TChain* chain_sigD_kst[ny];
   TChain* chain_sigD_ks[ny];
   TTree* tree_sigD_kst[ny];
   TTree* tree_sigD_ks[ny];
   RooRealVar* w_sigD_kst[ny];
   RooRealVar* w_sigD_ks[ny];
   RooDataSet* data_sigD_kst[ny];
   RooDataSet* data_sigD_ks[ny];
   RooRealVar* fnll_kst[ny];
   RooRealVar* fnll_ks[ny];
   
   RooRealVar *res_muD_kst[ny];
   RooRealVar *sD0_kst[ny];
   RooRealVar *sD1_kst[ny];
   RooRealVar *sD2_kst[ny];
   RooGaussModel *resD_kst[ny];
   
     // Set resolution function
     //jpsikst data from bd2jpsipipi data
   double init_s0[ny] = {0.0065840, 0.0035490, 0.0034240};
   double init_s1[ny] = {1.0247, 1.0501, 1.0498};
   double init_s2[ny] = {0.0, 0.0, 0.0};

   
   for (int i = 0; i < ny; i++) {
        res_muD_kst[i] = new RooRealVar(Form("res_muD_kst_%s", parfix[i].c_str()), "mean value", 0, -0.1, 0.1, "ps");
        sD0_kst[i] = new RooRealVar(Form("s%s_D0_kst", parfix[i].c_str()), "", init_s0[i], -0.1, 0.1);
        sD1_kst[i] = new RooRealVar(Form("s%s_D1_kst", parfix[i].c_str()), "", init_s1[i], 0, 2);
        sD2_kst[i] = new RooRealVar(Form("s%s_D2_kst", parfix[i].c_str()), "", init_s2[i], -30, 30);
        
        
        RooFormulaVar *wd1D = new RooFormulaVar(Form("wd1D_kst_%s", parfix[i].c_str()), "abs(@1+@2*@0+@3*@0*@0)",RooArgSet(*et, *sD0_kst[i], *sD1_kst[i], *sD2_kst[i]));
        
        resD_kst[i] = new RooGaussModel(Form("resD_kst_%s", parfix[i].c_str()), "", *t, *res_muD_kst[i], *wd1D);
   }
   
   // jpsiks data from sin2beta LL mc
   RooRealVar *res_muD_ks = new RooRealVar("res_muD_ks", "mean value", 0, -0.1, 0.1, "ps");
   RooRealVar *b_M1 = new RooRealVar("b_M1", "", -0.235, -0.5, 0.0, "ps");
   RooRealVar *c_M1 = new RooRealVar("c_M1", "", 17.87, 15.0, 20.0);
   RooRealVar *b_M2 = new RooRealVar("b_M2", "", -0.0018, -0.01, 0.01, "ps");
   RooRealVar *c_M2 = new RooRealVar("c_M2", "", 1.97, 1.0, 3.0);
   RooRealVar *b_M3 = new RooRealVar("b_M3", "", 0.00034, -0.005, 0.005, "ps");
   RooRealVar *c_M3 = new RooRealVar("c_M3", "", 0.983, 0.8, 1.2);
   
   // sigma = c * et + b
   RooFormulaVar *sigma_g1 = new RooFormulaVar("sigma_g1", "abs(@0*@1 + @2)", RooArgList(*c_M1, *et, *b_M1));
   RooFormulaVar *sigma_g2 = new RooFormulaVar("sigma_g2", "abs(@0*@1 + @2)", RooArgList(*c_M2, *et, *b_M2));
   RooFormulaVar *sigma_g3 = new RooFormulaVar("sigma_g3", "abs(@0*@1 + @2)", RooArgList(*c_M3, *et, *b_M3));
   
   RooGaussModel *gauss1 = new RooGaussModel("gauss1", "", *t, *res_muD_ks, *sigma_g1);
   RooGaussModel *gauss2 = new RooGaussModel("gauss2", "", *t, *res_muD_ks, *sigma_g2);
   RooGaussModel *gauss3 = new RooGaussModel("gauss3", "", *t, *res_muD_ks, *sigma_g3);
   
   RooRealVar *f_M1 = new RooRealVar("f_M1", "", 0.00430, 0.0, 0.01);
   RooRealVar *f_M2 = new RooRealVar("f_M2", "", 0.091, 0.0, 0.2);
   
   RooAddModel *resD_ks = new RooAddModel("resD_ks", "3 Gaussian",RooArgList(*gauss1, *gauss2, *gauss3),RooArgList(*f_M1, *f_M2));

   // Acceptance models for each year
   RooRealVar* accD_kst[ny][nCof];
   RooRealVar* accD_ks[ny][nCof];
   RooArgSet* coefList_sigD_kst[ny];
   RooArgSet* coefList_sigD_ks[ny];
   RooAbsReal* ACC_sigD_kst[ny];
   RooAbsReal* ACC_sigD_ks[ny];
   RooBinnedPdf* tacc_sigD_kst[ny];
   RooBinnedPdf* tacc_sigD_ks[ny];
   RooEffResModel* resacc_sigD_kst[ny];
   RooEffResModel* resacc_sigD_ks[ny];

   // PDFs for each year
   RooBDecay* fitpdf_sigD_kst[ny];
   RooBDecay* fitpdf_sigD_ks[ny];

   // Initialize arrays
   for (int i = 0; i < ny; i++) {
        string year_str = to_string(years[i]);
        
        // Read trees
        chain_sigD_kst[i] = new TChain();
        chain_sigD_ks[i] = new TChain();
        
        string path_kst = Form(path_sigD_kst_template.c_str(), year_str.c_str());
        string path_ks = Form(path_sigD_ks_template.c_str(), year_str.c_str());
        
        chain_sigD_kst[i]->Add(path_kst.c_str());
        chain_sigD_ks[i]->Add(path_ks.c_str());

        chain_sigD_kst[i]->SetBranchStatus("*", 0);
        chain_sigD_kst[i]->SetBranchStatus(bmass, 1);
        chain_sigD_kst[i]->SetBranchStatus(time, 1);
        chain_sigD_kst[i]->SetBranchStatus(timeerr, 1);
        chain_sigD_kst[i]->SetBranchStatus(wgt_sigD_kst, 1);

        chain_sigD_ks[i]->SetBranchStatus("*", 0);
        chain_sigD_ks[i]->SetBranchStatus(bmass, 1);
        chain_sigD_ks[i]->SetBranchStatus(time, 1);
        chain_sigD_ks[i]->SetBranchStatus(timeerr, 1);
        chain_sigD_ks[i]->SetBranchStatus(wgt_sigD_ks, 1);

        if (nfrac != 1) {
            tree_sigD_kst[i] = chain_sigD_kst[i]->CopyTree(cut_sigD_kst.c_str(), "", ceil(chain_sigD_kst[i]->GetEntries() * nfrac), 0);
            tree_sigD_ks[i] = chain_sigD_ks[i]->CopyTree(cut_sigD_ks.c_str(), "", ceil(chain_sigD_ks[i]->GetEntries() * nfrac), 0);
        } else {
            tree_sigD_kst[i] = chain_sigD_kst[i]->CopyTree(cut_sigD_kst.c_str());
            tree_sigD_ks[i] = chain_sigD_ks[i]->CopyTree(cut_sigD_ks.c_str());
        }

        // Set weights
        w_sigD_kst[i] = new RooRealVar(wgt_sigD_kst, "", tree_sigD_kst[i]->GetMinimum(wgt_sigD_kst), tree_sigD_kst[i]->GetMaximum(wgt_sigD_kst));
        w_sigD_ks[i] = new RooRealVar(wgt_sigD_ks, "", tree_sigD_ks[i]->GetMinimum(wgt_sigD_ks), tree_sigD_ks[i]->GetMaximum(wgt_sigD_ks));

        // Set datasets
        data_sigD_kst[i] = new RooDataSet(Form("data_sigD_kst_%s", parfix[i].c_str()), "", tree_sigD_kst[i], RooArgSet(*t, *et, *w_sigD_kst[i]), 0, wgt_sigD_kst);
        data_sigD_ks[i] = new RooDataSet(Form("data_sigD_ks_%s", parfix[i].c_str()), "", tree_sigD_ks[i], RooArgSet(*t, *et, *w_sigD_ks[i]), 0, wgt_sigD_ks);

        // Calculate NLL factors using the existing function from header
        fnll_kst[i] = new RooRealVar(Form("fnll_kst_%s", parfix[i].c_str()), "", Calfnll(tree_sigD_kst[i], wgt_sigD_kst));
        fnll_ks[i] = new RooRealVar(Form("fnll_ks_%s", parfix[i].c_str()), "", Calfnll(tree_sigD_ks[i], wgt_sigD_ks));
        fnll_kst[i]->setConstant(1);
        fnll_ks[i]->setConstant(1);

        cout << "---------------------------------------------------" << endl;
        cout << " Year " << years[i] << " Sig data (K*) " << endl;
        data_sigD_kst[i]->Print();
        cout << " Year " << years[i] << " Sig data (Ks) " << endl;
        data_sigD_ks[i]->Print();
        cout << "---------------------------------------------------" << endl;

        // Set acc functions
        coefList_sigD_kst[i] = new RooArgSet();
        coefList_sigD_ks[i] = new RooArgSet();

        for (int j = 0; j < nCof; j++) {
            accD_kst[i][j] = new RooRealVar(Form("accD_kst%s_%i", parfix[i].c_str(), j), "", 1., 0, 10);
            accD_ks[i][j] = new RooRealVar(Form("accD_ks%s_%i", parfix[i].c_str(), j), "", 1., 0, 10);
            coefList_sigD_kst[i]->add(*accD_kst[i][j]);
            coefList_sigD_ks[i]->add(*accD_ks[i][j]);
        }

        ACC_sigD_kst[i] = new RooCubicSplineFun(Form("ACC_sigD_kst_%s", parfix[i].c_str()), "spline", *t, knots, *coefList_sigD_kst[i]);
        ACC_sigD_ks[i] = new RooCubicSplineFun(Form("ACC_sigD_ks_%s", parfix[i].c_str()), "spline", *t, knots, *coefList_sigD_ks[i]);

        // Set binned acc
        int nAccBins = (t->getMax() - t->getMin()) / 0.01;
        RooUniformBinning acceptanceBinning(t->getMin(), t->getMax(), nAccBins, "acceptanceBinning");
        t->setBinning(acceptanceBinning, "acceptanceBinning");

        tacc_sigD_kst[i] = new RooBinnedPdf(Form("tacc_sigD_kst_%s", parfix[i].c_str()), "", *t, "acceptanceBinning", *ACC_sigD_kst[i]);
        tacc_sigD_ks[i] = new RooBinnedPdf(Form("tacc_sigD_ks_%s", parfix[i].c_str()), "", *t, "acceptanceBinning", *ACC_sigD_ks[i]);

        tacc_sigD_kst[i]->setForceUnitIntegral(true);
        tacc_sigD_ks[i]->setForceUnitIntegral(true);

        resacc_sigD_kst[i] = new RooEffResModel(Form("resacc_sigD_kst_%s", parfix[i].c_str()), "", *resD_kst[i], *tacc_sigD_kst[i]);
        resacc_sigD_ks[i] = new RooEffResModel(Form("resacc_sigD_ks_%s", parfix[i].c_str()), "", *resD_ks, *tacc_sigD_ks[i]);

        et->setBins(50, "cache");
        resacc_sigD_kst[i]->setParameterizeIntegral(RooArgSet(*et));
        resacc_sigD_ks[i]->setParameterizeIntegral(RooArgSet(*et));

        // Set the fit pdf
        fitpdf_sigD_kst[i] = new RooBDecay(Form("fitpdf_sigD_kst_%s", parfix[i].c_str()), "", *t, tau_kst, Dgd, RooConst(1.), RooConst(0), RooConst(0), RooConst(0), *Dm, *resacc_sigD_kst[i], RooBDecay::SingleSided);
        fitpdf_sigD_ks[i] = new RooBDecay(Form("fitpdf_sigD_ks_%s", parfix[i].c_str()), "", *t, tau_ks, Dgd, RooConst(1.), RooConst(0), RooConst(0), RooConst(0), *Dm, *resacc_sigD_ks[i], RooBDecay::SingleSided);
   }
   
   RooRealVar *ftau = new RooRealVar("ftau", "", ftau_val);
   
   // Set the set of pars 
   RooArgSet *inforpar = new RooArgSet();
   inforpar->add(tau);
   inforpar->add(Dgd);

   for (int i = 0; i < ny; i++) {
        inforpar->add(*coefList_sigD_kst[i]);
        inforpar->add(*coefList_sigD_ks[i]);
        inforpar->add(RooArgSet(*res_muD_kst[i], *sD0_kst[i], *sD1_kst[i], *sD2_kst[i], *res_muD_ks, *b_M1, *c_M1, *b_M2, *c_M2, *b_M3, *c_M3, *f_M1, *f_M2));
        inforpar->add(*fnll_kst[i]);
        inforpar->add(*fnll_ks[i]);
   }

   inforpar->readFromFile(offitpar.c_str());
   inforpar->readFromFile(ifresodata.c_str());
   inforpar->readFromFile(ifresomc.c_str());

   for (int i = 0; i < ny; i++) {
        for (int j = 0; j < nCof; j++) {
            accD_kst[i][j]->setConstant(1);
            accD_ks[i][j]->setConstant(1);
        }
   }
   
   // Set shared parameters to be fitted
   tau.setConstant(0);
   Dgd.setConstant(0);

   // Set the i-th accp pars to be fixed as 1
   int ith = 4;
   for (int i = 0; i < ny; i++) {
        accD_kst[i][ith]->setConstant(1);
        accD_kst[i][ith]->setVal(1);
        accD_ks[i][ith]->setConstant(1);
        accD_ks[i][ith]->setVal(1);
   }

   if (Dg) Dgd.setVal(dg_val);

   ftau->setVal(ftau_val);
   tau.setVal(tau_val);
   inforpar->Print("sv");

   RooFitResult *fitres;

   if (!Nfit) {
        // Create NLL functions for all years
        RooArgList nllList;
        int nCpu = 8;

        for (int i = 0; i < ny; i++) {
            RooArgSet *CondSet = new RooArgSet(*et);
            
            RooAbsReal *nll_sigD_kst = fitpdf_sigD_kst[i]->createNLL(*data_sigD_kst[i], Optimize(0), ConditionalObservables(*CondSet), NumCPU(nCpu));
            RooAbsReal *nll_sigD_ks = fitpdf_sigD_ks[i]->createNLL(*data_sigD_ks[i], Optimize(0), ConditionalObservables(*CondSet), NumCPU(nCpu));
            
            RooFormulaVar *wnll_kst = new RooFormulaVar(Form("wnll_kst_%s", parfix[i].c_str()), "@0*@1", RooArgSet(*nll_sigD_kst, *fnll_kst[i]));
            RooFormulaVar *wnll_ks = new RooFormulaVar(Form("wnll_ks_%s", parfix[i].c_str()), "@0*@1", RooArgSet(*nll_sigD_ks, *fnll_ks[i]));
            
            nllList.add(*wnll_kst);
            nllList.add(*wnll_ks);
        }

        RooAddition totalNLL("totalNLL", "", nllList);

        RooMinuit mCC(totalNLL);
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
            edmval = fitres->edm();
            if( edmval<5e-4 || edmval>200 ) break;
        }
        printf(" ***Total NLL = %15.2f\n", totalNLL.getVal());
         //mCC.minos(RooArgSet(*accD[0],*accD[3],*accD[5],*accD[7])); 
        fitres->SetName("fitres");
        fitres->Print("v");

        inforpar->writeToFile( offitpar.c_str() );
        
        TFile *newfile = new TFile( offitres.c_str(), "recreate" );
        newfile->cd();
        fitres->Write();
        newfile->Close();
   } else {
        TFile *iffitres = new TFile( offitres.c_str() );
        fitres = (RooFitResult *)iffitres->Get("fitres");
        iffitres->Close();
        fitres->Print("v");
   }
   
   inforpar->readFromFile( offitpar.c_str() );
   inforpar->writeToFile( offitpar.c_str() );

   // Draw and save plots for each year
   int nBin = (t_h - t_l) / 0.1;

   for (int i = 0; i < ny; i++) {
        RooDataHist *projdata_kst = new RooDataHist(Form("projdata_kst_%s", parfix[i].c_str()), "", *et, *data_sigD_kst[i]);
        RooDataHist *projdata_ks = new RooDataHist(Form("projdata_ks_%s", parfix[i].c_str()), "", *et, *data_sigD_ks[i]);

        RooPlot *vframe_kst = t->frame(Bins(nBin));
        RooPlot *vframe_ks = t->frame(Bins(nBin));

        data_sigD_kst[i]->plotOn(vframe_kst, MarkerSize(0.5));
        fitpdf_sigD_kst[i]->plotOn(vframe_kst, ProjWData(*projdata_kst), Name(Form("PDF_kst_%s", parfix[i].c_str())));
        data_sigD_kst[i]->plotOn(vframe_kst, MarkerSize(0.5), Name(Form("Data_kst_%s", parfix[i].c_str())));
        vframe_kst->SetMinimum(1e-2);

        data_sigD_ks[i]->plotOn(vframe_ks, MarkerSize(0.5));
        fitpdf_sigD_ks[i]->plotOn(vframe_ks, ProjWData(*projdata_ks), Name(Form("PDF_ks_%s", parfix[i].c_str())));
        data_sigD_ks[i]->plotOn(vframe_ks, MarkerSize(0.5), Name(Form("Data_ks_%s", parfix[i].c_str())));
        vframe_ks->SetMinimum(1e-2);

        // Set logo
        TPaveText *logo1 = new TPaveText(0.50, 0.75, 0.60, 0.85, "BRNDC");
        logo1->AddText(Form("#font[132]{LHCb Run 2 data, 5.4 fb^{-1}}"));
        SetLogo( logo1 );
        
        vframe_kst->addObject(logo1);
        vframe_ks->addObject(logo1);
        
        char XTitle[] = "#it{t} [ps]";
        char YTitle1[] = "Candidates / ( 0.1 ps )";
        
        string picname_kst = Form("output/%s_fit_sigd_kst_%d", prefix.c_str(), years[i]);
        string picname_ks = Form("output/%s_fit_sigd_ks_%d", prefix.c_str(), years[i]);
       
        RooSaveFitPlot(Form("Data_kst_%s", parfix[i].c_str()), Form("PDF_kst_%s", parfix[i].c_str()), t, vframe_kst, XTitle, YTitle1, picname_kst.c_str(), 0, 0, 1);
        RooSaveFitPlot(Form("Data_ks_%s", parfix[i].c_str()), Form("PDF_ks_%s", parfix[i].c_str()), t, vframe_ks, XTitle, YTitle1, picname_ks.c_str(), 0, 0, 1);
        
        // Get the binned acceptance using histogram method for K* and Ks
        RooBDecay *genpdf_sigD_kst = new RooBDecay(Form("genpdf_sigD_kst_%s", parfix[i].c_str()), "", *t, tau_kst, Dgd, RooConst(1.), RooConst(0), RooConst(0), RooConst(0), *Dm, *resD_kst[i], RooBDecay::SingleSided);
        RooBDecay *genpdf_sigD_ks = new RooBDecay(Form("genpdf_sigD_ks_%s", parfix[i].c_str()), "", *t, tau_ks, Dgd, RooConst(1.), RooConst(0), RooConst(0), RooConst(0), *Dm, *resD_ks, RooBDecay::SingleSided);

        const int hBin1 = 100;
        TH1D *hselt_sigD_kst = new TH1D(Form("hselt_sigD_kst_%s", parfix[i].c_str()), "", hBin1, t_l, t_h);
        TH1D *hselt_sigD_ks = new TH1D(Form("hselt_sigD_ks_%s", parfix[i].c_str()), "", hBin1, t_l, t_h);
        TH1D *htacc_sigD_kst = new TH1D(Form("htacc_sigD_kst_%s", parfix[i].c_str()), "", hBin1, t_l, t_h);
        TH1D *htacc_sigD_ks = new TH1D(Form("htacc_sigD_ks_%s", parfix[i].c_str()), "", hBin1, t_l, t_h);

        data_sigD_kst[i]->fillHistogram(hselt_sigD_kst, *t);
        data_sigD_ks[i]->fillHistogram(hselt_sigD_ks, *t);

        TH1D *hgent_sigD_kst = (TH1D *)genpdf_sigD_kst->createHistogram(Form("hgent_sigD_kst_%s", parfix[i].c_str()), *t, ProjWData(*projdata_kst), Binning(hBin1, t_l, t_h));
        TH1D *hgent_sigD_ks = (TH1D *)genpdf_sigD_ks->createHistogram(Form("hgent_sigD_ks_%s", parfix[i].c_str()), *t, ProjWData(*projdata_ks), Binning(hBin1, t_l, t_h));

        hgent_sigD_kst->Scale(hselt_sigD_kst->Integral() / hgent_sigD_kst->Integral());
        hgent_sigD_ks->Scale(hselt_sigD_ks->Integral() / hgent_sigD_ks->Integral());

        for (int j = 0; j < hgent_sigD_kst->GetNbinsX(); j++) {
            hgent_sigD_kst->SetBinError(j, 0);
            hgent_sigD_ks->SetBinError(j, 0);
        }

        double sum_sigD_kst = 0;
        double sum_sigD_ks = 0;
        for (int j = 0; j < htacc_sigD_kst->GetNbinsX(); j++) {
            *t = hgent_sigD_kst->GetBinCenter(j + 1);
            sum_sigD_kst += hgent_sigD_kst->GetBinContent(j + 1) * ACC_sigD_kst[i]->getVal(*t);
            sum_sigD_ks += hgent_sigD_ks->GetBinContent(j + 1) * ACC_sigD_ks[i]->getVal(*t);
        }

        htacc_sigD_kst->Divide(hselt_sigD_kst, hgent_sigD_kst, sum_sigD_kst, hgent_sigD_kst->Integral());
        htacc_sigD_ks->Divide(hselt_sigD_ks, hgent_sigD_ks, sum_sigD_ks, hgent_sigD_ks->Integral());

        RooDataHist *adata_sigD_kst = new RooDataHist(Form("adata_sigD_kst_%s", parfix[i].c_str()), "", RooArgSet(*t), htacc_sigD_kst);
        RooDataHist *adata_sigD_ks = new RooDataHist(Form("adata_sigD_ks_%s", parfix[i].c_str()), "", RooArgSet(*t), htacc_sigD_ks);

        // Save the acceptance plots for K* and Ks for each year
        Color_t FCol[5] = { kOrange,   kAzure+1, kMagenta-9, kPink-4, kGray };
        Color_t LCol[5] = { kOrange+1, kAzure,   kMagenta,   kPink+8, kBlack };

        string YTitle[2] = {
            Form("#it{#varepsilon}^{#it{J/#psiK^{*0}}}_{data}(%d)", years[i]),
            Form("#it{#varepsilon}^{#it{J/#psiK_{S}^{0}}}_{data}(%d)", years[i])
        };

        string accpic_kst = Form("%s_acc_sigD_kst_%d", prefix.c_str(), years[i]);
        string accpic_ks = Form("%s_acc_sigD_ks_%d", prefix.c_str(), years[i]);

        TPaveText *logo2 = new TPaveText(0.22, 0.80, 0.30, 0.90, "BRNDC");
        logo2->AddText(Form("#font[132]{LHCb Run 2 data, 5.4 fb^{-1}}"));
        SetLogo(logo2);

        RooPlot *aframe_kst = t->frame();
        RooPlot *aframe_ks = t->frame();
        
        aframe_kst->addObject(logo2);
        aframe_ks->addObject(logo2);

        // K* acceptance plot
        SetAccFrame(aframe_kst, ACC_sigD_kst[i], fitres, 1, FCol[0], LCol[0], "#it{t} [ps]", YTitle[0].c_str());
        adata_sigD_kst->plotOn(aframe_kst, MarkerSize(0.5));
        aframe_kst->SetMinimum(0.0);
        aframe_kst->SetMaximum(2.2);
        SaveAccPic(aframe_kst, accpic_kst.c_str());

        // Ks acceptance plot
        SetAccFrame(aframe_ks, ACC_sigD_ks[i], fitres, 1, FCol[1], LCol[1], "#it{t} [ps]", YTitle[1].c_str());
        adata_sigD_ks->plotOn(aframe_ks, MarkerSize(0.5));
        aframe_ks->SetMinimum(0.0);
        aframe_ks->SetMaximum(2.2);
        SaveAccPic(aframe_ks, accpic_ks.c_str());
        
        cout << "=========================================" << endl;
        cout << years[i] << " sigD_kst, chi2_NDOF(5) = " << vframe_kst->chiSquare(Form("PDF_kst_%s", parfix[i].c_str()), Form("Data_kst_%s", parfix[i].c_str()), 1) << endl;
        cout << years[i] << " sigD_ks, chi2_NDOF(5) = " << vframe_ks->chiSquare(Form("PDF_ks_%s", parfix[i].c_str()), Form("Data_ks_%s", parfix[i].c_str()), 1) << endl;
        cout << "=========================================" << endl;
   }

   cout << "===========================================" << endl;
   cout << " ENDING  TIME : " << endl;
   system("date");
   cout << "===========================================" << endl;
   
   return 0;
}
