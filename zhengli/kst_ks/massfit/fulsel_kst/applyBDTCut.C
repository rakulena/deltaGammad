#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"

void applyBDT(int year=2016) {
    // Set BDT cut based on year
    double bdtCut = 0.0;
    if (year == 2016) {
        bdtCut = 0.33;
    } else if (year == 2017) {
        bdtCut = 0.31;
    } else if (year == 2018) {
        bdtCut = 0.30;
    } 
    std::string yearStr = std::to_string(year);
    
    std::string inputPath = Form("/lzufs/user/zhanghy/Sample/Train/Bd2JpsiKstar_mc_%s_BDT.root", yearStr.c_str());
    std::string outputPath = Form("/lzufs/user/zhanghy/Sample/afterBDT/after_Bd2JpsiKstar_mc_%s_BDT.root", yearStr.c_str());

    TFile *inputFile = TFile::Open(inputPath.c_str());
 
    TTree *inputTree = (TTree*)inputFile->Get("DecayTree");

    TFile *outputFile = TFile::Open(outputPath.c_str(), "RECREATE");

    TCut cut = Form("BDT > %f", bdtCut); 
    TTree *outputTree = inputTree->CopyTree(cut);
    outputTree->Write();
    Long64_t nTotal = inputTree->GetEntries();
    Long64_t nPassed = outputTree->GetEntries();
    std::cout << "Year " << year << ": " << nPassed << " out of " << nTotal 
              << " entries passed BDT > " << bdtCut << std::endl;
 
    outputFile->Close();
    inputFile->Close();
}
void applyBDTCut(){
    applyBDT(2016);
    applyBDT(2017);
    applyBDT(2018);
    exit(0);
}