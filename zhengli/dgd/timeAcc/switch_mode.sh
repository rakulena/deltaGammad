#!/bin/bash

if [ $# -ne 1 ]; then
   echo param error!
   exit 1
fi

MODE=$1
FILE="fitTimeAcc.cpp"

if [ "$MODE" == "kst" ]; then

    # 1. data path
    sed -i 's|string path_sigM = .*|string path_sigM = Form("~/Sample/afterBDT/after_Bd2JpsiKstar_mc_%s_BDT.root/DecayTree",Year.c_str());|' $FILE
    sed -i 's|string path_conM = .*|string path_conM = Form("~/Sample/kplus/mc/v4r0_MC_Bu2JpsiKplus_%s_selected_bdt.root/DecayTree",Year.c_str());|' $FILE
    sed -i 's|string path_sigD = .*|string path_sigD = Form("~/Sample/afterBDT/after_Bd2JpsiKstar_data_%s_sw_base.root/DecayTree",Year.c_str());|' $FILE
    sed -i 's|string path_conD = .*|string path_conD = Form("~/Sample/kplus/data/Bu2Jpsikplus_data_%s_sw_base_bdt.root/DecayTree",Year.c_str());|' $FILE
    
    # 2. weights&vars
    sed -i 's|char wgt_sigM\[\] = .*|char wgt_sigM[] = "gbw";|' $FILE
    sed -i 's|char wgt_conM\[\] = .*|char wgt_conM[] = "gb_weights";|' $FILE
    sed -i 's|char wgt_sigD\[\] = .*|char wgt_sigD[] = "sig_sw";|' $FILE
    sed -i 's|char wgt_conD\[\] = .*|char wgt_conD[] = "sig_sw";|' $FILE
    
    # 3. resolution model
    # remove annotating jpsikst
    sed -i 's|^   // RooRealVar \*sM0 = new RooRealVar(Form("s%s_M0",|   RooRealVar *sM0 = new RooRealVar(Form("s%s_M0",|' $FILE
    sed -i 's|^   // RooRealVar \*sM1 = new RooRealVar(Form("s%s_M1",|   RooRealVar *sM1 = new RooRealVar(Form("s%s_M1",|' $FILE
    sed -i 's|^   // RooRealVar \*sM2 = new RooRealVar(Form("s%s_M2",|   RooRealVar *sM2 = new RooRealVar(Form("s%s_M2",|' $FILE
    sed -i 's|^   // RooFormulaVar \*wd1M = new RooFormulaVar("wd1M",|   RooFormulaVar *wd1M = new RooFormulaVar("wd1M",|' $FILE
    sed -i 's|^   // RooGaussModel \*resM = new RooGaussModel("resM",|   RooGaussModel *resM = new RooGaussModel("resM",|' $FILE
    
    # annotate jpsiks 
    sed -i 's|^   RooRealVar \*b_M1 = new RooRealVar(Form("b%s_M1",|   // RooRealVar *b_M1 = new RooRealVar(Form("b%s_M1",|' $FILE
    sed -i 's|^   RooRealVar \*c_M1 = new RooRealVar(Form("c%s_M1",|   // RooRealVar *c_M1 = new RooRealVar(Form("c%s_M1",|' $FILE
    sed -i 's|^   RooRealVar \*b_M2 = new RooRealVar(Form("b%s_M2",|   // RooRealVar *b_M2 = new RooRealVar(Form("b%s_M2",|' $FILE
    sed -i 's|^   RooRealVar \*c_M2 = new RooRealVar(Form("c%s_M2",|   // RooRealVar *c_M2 = new RooRealVar(Form("c%s_M2",|' $FILE
    sed -i 's|^   RooRealVar \*b_M3 = new RooRealVar(Form("b%s_M3",|   // RooRealVar *b_M3 = new RooRealVar(Form("b%s_M3",|' $FILE
    sed -i 's|^   RooRealVar \*c_M3 = new RooRealVar(Form("c%s_M3",|   // RooRealVar *c_M3 = new RooRealVar(Form("c%s_M3",|' $FILE
    sed -i 's|^   RooFormulaVar \*sigma_g1 = new RooFormulaVar(Form("sigma%s_g1",|   // RooFormulaVar *sigma_g1 = new RooFormulaVar(Form("sigma%s_g1",|' $FILE
    sed -i 's|^   RooFormulaVar \*sigma_g2 = new RooFormulaVar(Form("sigma%s_g2",|   // RooFormulaVar *sigma_g2 = new RooFormulaVar(Form("sigma%s_g2",|' $FILE
    sed -i 's|^   RooFormulaVar \*sigma_g3 = new RooFormulaVar(Form("sigma%s_g3",|   // RooFormulaVar *sigma_g3 = new RooFormulaVar(Form("sigma%s_g3",|' $FILE
    sed -i 's|^   RooGaussModel \*gauss1 = new RooGaussModel(Form("gauss1_%s",|   // RooGaussModel *gauss1 = new RooGaussModel(Form("gauss1_%s",|' $FILE
    sed -i 's|^   RooGaussModel \*gauss2 = new RooGaussModel(Form("gauss2_%s",|   // RooGaussModel *gauss2 = new RooGaussModel(Form("gauss2_%s",|' $FILE
    sed -i 's|^   RooGaussModel \*gauss3 = new RooGaussModel(Form("gauss3_%s",|   // RooGaussModel *gauss3 = new RooGaussModel(Form("gauss3_%s",|' $FILE
    sed -i 's|^   RooRealVar \*f_M1 = new RooRealVar(Form("f%s_M1",|   // RooRealVar *f_M1 = new RooRealVar(Form("f%s_M1",|' $FILE
    sed -i 's|^   RooRealVar \*f_M2 = new RooRealVar(Form("f%s_M2",|   // RooRealVar *f_M2 = new RooRealVar(Form("f%s_M2",|' $FILE
    sed -i 's|^   b_M1->setConstant|   // b_M1->setConstant|' $FILE
    sed -i 's|^   c_M1->setConstant|   // c_M1->setConstant|' $FILE
    sed -i 's|^   b_M2->setConstant|   // b_M2->setConstant|' $FILE
    sed -i 's|^   c_M2->setConstant|   // c_M2->setConstant|' $FILE
    sed -i 's|^   b_M3->setConstant|   // b_M3->setConstant|' $FILE
    sed -i 's|^   c_M3->setConstant|   // c_M3->setConstant|' $FILE
    sed -i 's|^   f_M1->setConstant|   // f_M1->setConstant|' $FILE
    sed -i 's|^   f_M2->setConstant|   // f_M2->setConstant|' $FILE
    sed -i 's|^   RooAddModel \*resM = new RooAddModel("resM",|   // RooAddModel *resM = new RooAddModel("resM",|' $FILE
    
    # 4. plot titles 
    # remove annotating jpsikst
    sed -i '/\/\/kstar_title/,/\/\/kshort_title/ {/\/\/kstar_title/! {/\/\/kshort_title/! {s/^\([[:space:]]*\)\/\//\1/}}}' $FILE

    # annotate jpsiks
    sed -i '/\/\/kshort_title/,/^[[:space:]]*};/ {/\/\/kshort_title/! {/^[[:space:]]*};/! {s/^\([[:space:]]*\)/\1\/\//}}}' $FILE

    # 5. resset parameters
    # remove annotating jpsikst
    sed -i 's|^[[:space:]]*//[[:space:]]*resSet->add( RooArgSet( \*sD0, \*sD1, \*sD2, \*sM0, \*sM1, \*sM2 ) );|   resSet->add( RooArgSet( *sD0, *sD1, *sD2, *sM0, *sM1, *sM2 ) );|' $FILE

    # annotate jpsiks
    sed -i 's|^[[:space:]]*resSet->add( RooArgSet( \*sD0, \*sD1, \*sD2,\*b_M1, \*c_M1,\*b_M2, \*c_M2,\*b_M3, \*c_M3,\*f_M1, \*f_M2) );|   //resSet->add( RooArgSet( *sD0, *sD1, *sD2,*b_M1, *c_M1,*b_M2, *c_M2,*b_M3, *c_M3,*f_M1, *f_M2) );|' $FILE   
   
    echo "change to jpsikst"
    
    elif [ "$MODE" == "ks" ]; then
    
    # 1. data path
    sed -i 's|string path_sigM = .*|string path_sigM = Form("~/Sample/afterBDT/after_Bd2JpsiKshort_mc_%s_BDT.root/DecayTree",Year.c_str());|' $FILE
    sed -i 's|string path_conM = .*|string path_conM = Form("~/Sample/kplus/mc/v4r0_MC_Bu2JpsiKplus_%s_selected_bdt.root/DecayTree",Year.c_str());|' $FILE
    sed -i 's|string path_sigD = .*|string path_sigD = Form("~/Sample/afterBDT/after_Bd2JpsiKshort_data_%s_sw_base.root/DecayTree",Year.c_str());|' $FILE
    sed -i 's|string path_conD = .*|string path_conD = Form("~/Sample/kplus/data/Bu2Jpsikplus_data_%s_sw_base_bdt.root/DecayTree",Year.c_str());|' $FILE
    
    # 2. weights & vars 
    sed -i 's|char wgt_sigM\[\] = .*|char wgt_sigM[] = "gbw";|' $FILE
    sed -i 's|char wgt_conM\[\] = .*|char wgt_conM[] = "gb_weights";|' $FILE
    sed -i 's|char wgt_sigD\[\] = .*|char wgt_sigD[] = "sig_sw";|' $FILE
    sed -i 's|char wgt_conD\[\] = .*|char wgt_conD[] = "sig_sw";|' $FILE
    
    # 3. resolution model
    # annotate jpsikst
    sed -i 's|^   RooRealVar \*sM0 = new RooRealVar(Form("s%s_M0",|   // RooRealVar *sM0 = new RooRealVar(Form("s%s_M0",|' $FILE
    sed -i 's|^   RooRealVar \*sM1 = new RooRealVar(Form("s%s_M1",|   // RooRealVar *sM1 = new RooRealVar(Form("s%s_M1",|' $FILE
    sed -i 's|^   RooRealVar \*sM2 = new RooRealVar(Form("s%s_M2",|   // RooRealVar *sM2 = new RooRealVar(Form("s%s_M2",|' $FILE
    sed -i 's|^   RooFormulaVar \*wd1M = new RooFormulaVar("wd1M",|   // RooFormulaVar *wd1M = new RooFormulaVar("wd1M",|' $FILE
    sed -i 's|^   RooGaussModel \*resM = new RooGaussModel("resM",|   // RooGaussModel *resM = new RooGaussModel("resM",|' $FILE
    
    # remove annotating jpsiks
    sed -i 's|^   // RooRealVar \*b_M1 = new RooRealVar(Form("b%s_M1",|   RooRealVar *b_M1 = new RooRealVar(Form("b%s_M1",|' $FILE
    sed -i 's|^   // RooRealVar \*c_M1 = new RooRealVar(Form("c%s_M1",|   RooRealVar *c_M1 = new RooRealVar(Form("c%s_M1",|' $FILE
    sed -i 's|^   // RooRealVar \*b_M2 = new RooRealVar(Form("b%s_M2",|   RooRealVar *b_M2 = new RooRealVar(Form("b%s_M2",|' $FILE
    sed -i 's|^   // RooRealVar \*c_M2 = new RooRealVar(Form("c%s_M2",|   RooRealVar *c_M2 = new RooRealVar(Form("c%s_M2",|' $FILE
    sed -i 's|^   // RooRealVar \*b_M3 = new RooRealVar(Form("b%s_M3",|   RooRealVar *b_M3 = new RooRealVar(Form("b%s_M3",|' $FILE
    sed -i 's|^   // RooRealVar \*c_M3 = new RooRealVar(Form("c%s_M3",|   RooRealVar *c_M3 = new RooRealVar(Form("c%s_M3",|' $FILE
    sed -i 's|^   // RooFormulaVar \*sigma_g1 = new RooFormulaVar(Form("sigma%s_g1",|   RooFormulaVar *sigma_g1 = new RooFormulaVar(Form("sigma%s_g1",|' $FILE
    sed -i 's|^   // RooFormulaVar \*sigma_g2 = new RooFormulaVar(Form("sigma%s_g2",|   RooFormulaVar *sigma_g2 = new RooFormulaVar(Form("sigma%s_g2",|' $FILE
    sed -i 's|^   // RooFormulaVar \*sigma_g3 = new RooFormulaVar(Form("sigma%s_g3",|   RooFormulaVar *sigma_g3 = new RooFormulaVar(Form("sigma%s_g3",|' $FILE
    sed -i 's|^   // RooGaussModel \*gauss1 = new RooGaussModel(Form("gauss1_%s",|   RooGaussModel *gauss1 = new RooGaussModel(Form("gauss1_%s",|' $FILE
    sed -i 's|^   // RooGaussModel \*gauss2 = new RooGaussModel(Form("gauss2_%s",|   RooGaussModel *gauss2 = new RooGaussModel(Form("gauss2_%s",|' $FILE
    sed -i 's|^   // RooGaussModel \*gauss3 = new RooGaussModel(Form("gauss3_%s",|   RooGaussModel *gauss3 = new RooGaussModel(Form("gauss3_%s",|' $FILE
    sed -i 's|^   // RooRealVar \*f_M1 = new RooRealVar(Form("f%s_M1",|   RooRealVar *f_M1 = new RooRealVar(Form("f%s_M1",|' $FILE
    sed -i 's|^   // RooRealVar \*f_M2 = new RooRealVar(Form("f%s_M2",|   RooRealVar *f_M2 = new RooRealVar(Form("f%s_M2",|' $FILE
    sed -i 's|^   // b_M1->setConstant|   b_M1->setConstant|' $FILE
    sed -i 's|^   // c_M1->setConstant|   c_M1->setConstant|' $FILE
    sed -i 's|^   // b_M2->setConstant|   b_M2->setConstant|' $FILE
    sed -i 's|^   // c_M2->setConstant|   c_M2->setConstant|' $FILE
    sed -i 's|^   // b_M3->setConstant|   b_M3->setConstant|' $FILE
    sed -i 's|^   // c_M3->setConstant|   c_M3->setConstant|' $FILE
    sed -i 's|^   // f_M1->setConstant|   f_M1->setConstant|' $FILE
    sed -i 's|^   // f_M2->setConstant|   f_M2->setConstant|' $FILE
    sed -i 's|^   // RooAddModel \*resM = new RooAddModel("resM",|   RooAddModel *resM = new RooAddModel("resM",|' $FILE
    
    # 4. plot titles
    # annotate jpsikst
    sed -i '/\/\/kstar_title/,/\/\/kshort_title/ {/\/\/kstar_title/! {/\/\/kshort_title/! {s/^\([[:space:]]*\)/\/\/\1/}}}' $FILE 
    # remove annotating jpsiks
    sed -i '/\/\/kshort_title/,/^[[:space:]]*};/ {/\/\/kshort_title/! {/^[[:space:]]*};/! {s/^\/\/\([[:space:]]*\)/\1/}}}' $FILE
    
     # 5. resset parameters 
    # annotate jpsikst
    sed -i 's|^[[:space:]]*resSet->add( RooArgSet( \*sD0, \*sD1, \*sD2, \*sM0, \*sM1, \*sM2 ) );|   //resSet->add( RooArgSet( *sD0, *sD1, *sD2, *sM0, *sM1, *sM2 ) );|' $FILE

    # remove annotating jpsiks
    sed -i 's|^[[:space:]]*//[[:space:]]*resSet->add( RooArgSet( \*sD0, \*sD1, \*sD2,\*b_M1, \*c_M1,\*b_M2, \*c_M2,\*b_M3, \*c_M3,\*f_M1, \*f_M2) );|   resSet->add( RooArgSet( *sD0, *sD1, *sD2,*b_M1, *c_M1,*b_M2, *c_M2,*b_M3, *c_M3,*f_M1, *f_M2) );|' $FILE    

    echo "change to jpsiks"
else
    echo "para error"
    exit 1
fi
