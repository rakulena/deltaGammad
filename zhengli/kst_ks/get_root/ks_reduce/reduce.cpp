#define reduce_cxx
#include "reduce.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "../../inc/headfile.h"
#include "../../inc/hel.C"

void reduce::Loop( Long64_t runevt, Int_t year, const char *inforfile, const char *runmode )
{
//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
   // Long64_t nentries = fChain->GetEntriesFast();
   if (fChain == 0) return;

   // Read input infor
   string mode = runmode;

   vector<string> inputinfor;
   inputinfor.clear();

   ifstream iffile( inforfile );
   while(!iffile.eof()){
	string tmpinfor;
	iffile>>tmpinfor;
	inputinfor.push_back(tmpinfor);
   }
   iffile.close();

   // Set the mode
   bool sig_mc      = mode.find("sig_mc")!=string::npos;

   bool bkg_cat60    = mode.find("bkg_cat60")!=string::npos;

   // root file and tree
   TFile *rootfile = new TFile(inputinfor[0].c_str(),"recreate");
   TTree *ntree = new TTree("DecayTree","DecayTree");

   // Mass and decay length
   //float Bd_LOKI_MASS_JpsiConstr;
   //float Bd_PVConst_J_psi_1S_MERR;
   //float Bd_PVConst_M;
   //float Bd_PVConst_MERR;

   // For new caculated branches
   double clight = 0.29979245; // light speed
   
   double TrAng_pimup;
   double TrAng_pimum;
   double cosh; 
   double cosl;
   double phih;
   bool trigb;
   bool trigj;
   double m_ppi;
   
   double min_mu_PIDmu;
   // double piplus_ProbNNpi_k_corr;
   // double piminus_ProbNNpi_k_corr;
   double log_Bd_IPCHI2_OWNPV;
   double log_Bd_ENDVERTEX_CHI2NDOF;
   double log_Bd_OnlyPV_CHI2NDOF;
   double log_Bd_DTF_NoPV_CHI2NDOF;
   double min_mu_ProbNNmu_corr;


   double muplus_ProbNNmu_corr;      
   double muplus_ProbNNmu_pidcorr_default; 
   double muminus_ProbNNmu_corr;      
   double muminus_ProbNNmu_pidcorr_default;

   //tree->Branch("",&,"/D");
   if( year!= 0 ){
	cout<<"  Set the year to be "<<year<<endl;
	ntree->Branch("year",&year,"year/I");
   }
   ntree->Branch("runNumber",&runNumber,"runNumber/I");
   ntree->Branch("eventNumber",&eventNumber,"eventNumber/L");
   
   if( sig_mc ){
   ntree->Branch("Bd_BKGCAT",&Bd_BKGCAT,"Bd_BKGCAT/I");
	ntree->Branch("Bd_TRUEID",&Bd_TRUEID,"Bd_TRUEID/I");
	ntree->Branch("Kshort_TRUEID",&Kshort_TRUEID,"Kshort_TRUEID/I");//ks
	ntree->Branch("Jpsi_TRUEID",&Jpsi_TRUEID,"Jpsi_TRUEID/I");
	//ntree->Branch("muplus_TRUEID",&muplus_TRUEID,"muplus_TRUEID/I");
	//ntree->Branch("muminus_TRUEID",&muminus_TRUEID,"muminus_TRUEID/I");
	ntree->Branch("piplus_TRUEID",&piplus_TRUEID,"piplus_TRUEID/I");
	//ntree->Branch("piminus_TRUEID",&piminus_TRUEID,"piminus_TRUEID/I");
	ntree->Branch("Bd_TRUETAU",&Bd_TRUETAU,"Bd_TRUETAU/D");
   // ntree->Branch("Bd_ConstJpsi_tau",&Bd_ConstJpsi_tau,"Bd_ConstJpsi_tau/D");
   // ntree->Branch("Bd_ConstJpsi_tauErr",&Bd_ConstJpsi_tauErr,"Bd_ConstJpsi_tauErr/D");
   //ks tau
   // ntree->Branch("Bd_D0ToKshort_tau",&Bd_D0ToKshort_tau,"Bd_D0ToKshort_tau/D");
   // ntree->Branch("Bd_D0ToKshort_tauErr",&Bd_D0ToKshort_tauErr,"Bd_D0ToKshort_tauErr/D");
   
	ntree->Branch("Bd_TRUEP_X", &Bd_TRUEP_X, "Bd_TRUEP_X/D");
   ntree->Branch("Bd_TRUEP_Y", &Bd_TRUEP_Y, "Bd_TRUEP_Y/D");
   ntree->Branch("Bd_TRUEP_Z", &Bd_TRUEP_Z, "Bd_TRUEP_Z/D");
   ntree->Branch("Bd_TRUEP_E", &Bd_TRUEP_E, "Bd_TRUEP_E/D");
   ntree->Branch("Bd_TRUEPT",&Bd_TRUEPT,"Bd_TRUEPT/D");
   ntree->Branch("Jpsi_TRUEP_X", &Jpsi_TRUEP_X, "Jpsi_TRUEP_X/D");
   ntree->Branch("Jpsi_TRUEP_Y", &Jpsi_TRUEP_Y, "Jpsi_TRUEP_Y/D");
   ntree->Branch("Jpsi_TRUEP_Z", &Jpsi_TRUEP_Z, "Jpsi_TRUEP_Z/D");
   ntree->Branch("Jpsi_TRUEP_E", &Jpsi_TRUEP_E, "Jpsi_TRUEP_E/D");
   ntree->Branch("Jpsi_TRUEPT", &Jpsi_TRUEPT, "Jpsi_TRUEPT/D");

   ntree->Branch("piplus_ProbNNk_corr", &piplus_ProbNNk_pidcorr_default, "piplus_ProbNNk_corr/D");
   ntree->Branch("piplus_ProbNNpi_corr", &piplus_ProbNNpi_pidcorr_default, "piplus_ProbNNpi_corr/D");
   ntree->Branch("piplus_ProbNNp_corr", &piplus_ProbNNp_pidcorr_default, "piplus_ProbNNp_corr/D");

   ntree->Branch("piminus_ProbNNk_corr", &piminus_ProbNNk_pidcorr_default, "piminus_ProbNNk_corr/D");
   ntree->Branch("piminus_ProbNNpi_corr", &piminus_ProbNNpi_pidcorr_default, "piminus_ProbNNpi_corr/D");
   ntree->Branch("piminus_ProbNNp_corr", &piminus_ProbNNp_pidcorr_default, "piminus_ProbNNp_corr/D");
   ntree->Branch("muplus_ProbNNmu_corr", &muplus_ProbNNmu_pidcorr_default, "muplus_ProbNNmu_corr/D");
   ntree->Branch("muminus_ProbNNmu_corr", &muminus_ProbNNmu_pidcorr_default, "muminus_ProbNNmu_corr/D");

 
   }
   if(!sig_mc ){
   ntree->Branch("piplus_ProbNNk_corr", &piplus_ProbNNk, "piplus_ProbNNk_corr/D");
   ntree->Branch("piplus_ProbNNpi_corr", &piplus_ProbNNpi, "piplus_ProbNNpi_corr/D");
   ntree->Branch("piplus_ProbNNp_corr", &piplus_ProbNNp, "piplus_ProbNNp_corr/D");

   ntree->Branch("piminus_ProbNNk_corr", &piminus_ProbNNk, "piminus_ProbNNk_corr/D");
   ntree->Branch("piminus_ProbNNpi_corr", &piminus_ProbNNpi, "piminus_ProbNNpi_corr/D");
   ntree->Branch("piminus_ProbNNp_corr", &piminus_ProbNNp, "piminus_ProbNNp_corr/D");
   ntree->Branch("muplus_ProbNNmu_corr", &muplus_ProbNNmu, "muplus_ProbNNmu_corr/D");
   ntree->Branch("muminus_ProbNNmu_corr", &muminus_ProbNNmu, "muminus_ProbNNmu_corr/D");
  
   }
   //ntree->Branch("Polarity",&Polarity,"Polarity/S");
   ntree->Branch("nTracks", &nTracks, "nTracks/I");
   ntree->Branch("nLongTracks", &nLongTracks, "nLongTracks/I");
   ntree->Branch("nPVs", &nPVs, "nPVs/I");
   ntree->Branch("nSPDHits", &nSPDHits, "nSPDHits/I");
   ntree->Branch("totCandidates", &totCandidates, "totCandidates/L");
   ntree->Branch("L0DUTCK", &L0DUTCK, "L0DUTCK/I");
   ntree->Branch("HLT1TCK", &HLT1TCK, "HLT1TCK/I");
   ntree->Branch("HLT2TCK", &HLT2TCK, "HLT2TCK/I");
   ntree->Branch("Bd_ConstJpsi_tau", &Bd_ConstJpsi_tau, "Bd_ConstJpsi_tau/D");
   ntree->Branch("Bd_ConstJpsi_tauErr", &Bd_ConstJpsi_tauErr, "Bd_ConstJpsi_tauErr/D");

   ntree->Branch("Bd_ConstJpsi_M", &Bd_ConstJpsi_M, "Bd_ConstJpsi_M/F"); 
   ntree->Branch("Bd_ConstJpsi_MERR", &Bd_ConstJpsi_MERR, "Bd_ConstJpsi_MERR/F");
   ntree->Branch("Bd_OnlyPV_M", &Bd_OnlyPV_M, "Bd_OnlyPV_M/F");
   ntree->Branch("Bd_OnlyPV_MERR", &Bd_OnlyPV_MERR, "Bd_OnlyPV_MERR/F");


   ntree->Branch("Bd_OnlyPV_tau", &Bd_OnlyPV_tau, "Bd_OnlyPV_tau/D");
   ntree->Branch("Bd_OnlyPV_tauErr", &Bd_OnlyPV_tauErr, "Bd_OnlyPV_tauErr/D");
   ntree->Branch("Bd_ConstJpsi_CHI2NDOF", &Bd_ConstJpsi_CHI2NDOF, "Bd_ConstJpsi_CHI2NDOF/D");
   ntree->Branch("Bd_OnlyPV_CHI2NDOF", &Bd_OnlyPV_CHI2NDOF, "Bd_OnlyPV_CHI2NDOF/D");
   ntree->Branch("Bd_IP_OWNPV", &Bd_IP_OWNPV, "Bd_IP_OWNPV/D");
   ntree->Branch("Bd_IPCHI2_OWNPV", &Bd_IPCHI2_OWNPV, "Bd_IPCHI2_OWNPV/D");
   ntree->Branch("Bd_FD_OWNPV", &Bd_FD_OWNPV, "Bd_FD_OWNPV/D");
   ntree->Branch("Bd_FDCHI2_OWNPV", &Bd_FDCHI2_OWNPV, "Bd_FDCHI2_OWNPV/D");
   ntree->Branch("Bd_DIRA_OWNPV", &Bd_DIRA_OWNPV, "Bd_DIRA_OWNPV/D");
   ntree->Branch("Bd_TAU", &Bd_TAU, "Bd_TAU/D");
   ntree->Branch("Bd_TAUERR", &Bd_TAUERR, "Bd_TAUERR/D");
   
   ntree->Branch("Bd_L0Global_Dec", &Bd_L0Global_Dec, "Bd_L0Global_Dec/B");
   ntree->Branch("Bd_L0MuonDecision_TOS", &Bd_L0MuonDecision_TOS, "Bd_L0MuonDecision_TOS/B");
   ntree->Branch("Bd_L0DiMuonDecision_TOS", &Bd_L0DiMuonDecision_TOS, "Bd_L0DiMuonDecision_TOS/B");
   ntree->Branch("Bd_Hlt1TrackMuonMVADecision_TOS", &Bd_Hlt1TrackMuonMVADecision_TOS, "Bd_Hlt1TrackMuonMVADecision_TOS/B");
   ntree->Branch("Bd_Hlt1TwoTrackMVADecision_TOS", &Bd_Hlt1TwoTrackMVADecision_TOS, "Bd_Hlt1TwoTrackMVADecision_TOS/B");
   ntree->Branch("Bd_Hlt1DiMuonHighMassDecision_TOS", &Bd_Hlt1DiMuonHighMassDecision_TOS, "Bd_Hlt1DiMuonHighMassDecision_TOS/B");
   ntree->Branch("Jpsi_Hlt1TrackMuonDecision_TOS", &Jpsi_Hlt1TrackMuonDecision_TOS, "Jpsi_Hlt1TrackMuonDecision_TOS/B");
   ntree->Branch("Jpsi_Hlt1DiMuonHighMassDecision_TOS", &Jpsi_Hlt1DiMuonHighMassDecision_TOS, "Jpsi_Hlt1DiMuonHighMassDecision_TOS/B");
   ntree->Branch("Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS", &Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS, "Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS/B");
   
   ntree->Branch("hlt1b", &hlt1b, "hlt1b/I");
   ntree->Branch("Bd_ENDVERTEX_X", &Bd_ENDVERTEX_X, "Bd_ENDVERTEX_X/D");
   ntree->Branch("Bd_ENDVERTEX_Y", &Bd_ENDVERTEX_Y, "Bd_ENDVERTEX_Y/D");
   ntree->Branch("Bd_ENDVERTEX_Z", &Bd_ENDVERTEX_Z, "Bd_ENDVERTEX_Z/D");
   ntree->Branch("Bd_ENDVERTEX_CHI2NDOF", &Bd_ENDVERTEX_CHI2NDOF, "Bd_ENDVERTEX_CHI2NDOF/D");
   ntree->Branch("Bd_OWNPV_X", &Bd_OWNPV_X, "Bd_OWNPV_X/D");
   ntree->Branch("Bd_OWNPV_Y", &Bd_OWNPV_Y, "Bd_OWNPV_Y/D");
   ntree->Branch("Bd_OWNPV_Z", &Bd_OWNPV_Z, "Bd_OWNPV_Z/D");
   ntree->Branch("Bd_OWNPV_CHI2NDOF", &Bd_OWNPV_CHI2NDOF, "Bd_OWNPV_CHI2NDOF/D");
   ntree->Branch("Bd_MINIPCHI2NEXTBEST", &Bd_MINIPCHI2NEXTBEST, "Bd_MINIPCHI2NEXTBEST/D");
   ntree->Branch("Bd_MINIPCHI2", &Bd_MINIPCHI2, "Bd_MINIPCHI2/D");
   ntree->Branch("Bd_MINIP", &Bd_MINIP, "Bd_MINIP/D");
   ntree->Branch("Bd_DTF_NoPV_CHI2NDOF", &Bd_DTF_NoPV_CHI2NDOF, "Bd_DTF_NoPV_CHI2NDOF/D");
   ntree->Branch("Jpsi_MM", &Jpsi_MM, "Jpsi_MM/D");
   
   ntree->Branch("Jpsi_ConstJpsiNoPV_M", &Jpsi_ConstJpsiNoPV_M, "Jpsi_ConstJpsiNoPV_M/F");
   ntree->Branch("Jpsi_OnlyPV_M", &Jpsi_OnlyPV_M, "Jpsi_OnlyPV_M/F");
   
   ntree->Branch("Jpsi_ENDVERTEX_CHI2", &Jpsi_ENDVERTEX_CHI2, "Jpsi_ENDVERTEX_CHI2/D");
   ntree->Branch("Jpsi_ENDVERTEX_NDOF", &Jpsi_ENDVERTEX_NDOF, "Jpsi_ENDVERTEX_NDOF/I");
   ntree->Branch("Jpsi_ENDVERTEX_CHI2NDOF", &Jpsi_ENDVERTEX_CHI2NDOF, "Jpsi_ENDVERTEX_CHI2NDOF/D");
   ntree->Branch("Bd_ETA", &Bd_ETA, "Bd_ETA/D");
   ntree->Branch("Bd_PX", &Bd_PX, "Bd_PX/D");
   ntree->Branch("Bd_PY", &Bd_PY, "Bd_PY/D");
   ntree->Branch("Bd_PZ", &Bd_PZ, "Bd_PZ/D");
   ntree->Branch("Bd_PT", &Bd_PT, "Bd_PT/D");
   ntree->Branch("Bd_PE", &Bd_PE, "Bd_PE/D");
   ntree->Branch("Bd_P", &Bd_P, "Bd_P/D");
   ntree->Branch("Bd_M", &Bd_M, "Bd_M/D");
   ntree->Branch("Bd_ID", &Bd_ID, "Bd_ID/I");
   ntree->Branch("muplus_TRACK_CHI2NDOF", &muplus_TRACK_CHI2NDOF, "muplus_TRACK_CHI2NDOF/D");
   ntree->Branch("muplus_PT", &muplus_PT, "muplus_PT/D");
   ntree->Branch("muplus_P", &muplus_P, "muplus_P/D");
   //ntree->Branch("muplus_ProbNNmu", &muplus_ProbNNmu, "muplus_ProbNNmu/D");
   ntree->Branch("muplus_PIDmu", &muplus_PIDmu, "muplus_PIDmu/D");
   ntree->Branch("muminus_TRACK_CHI2NDOF", &muminus_TRACK_CHI2NDOF, "muminus_TRACK_CHI2NDOF/D");
   ntree->Branch("muminus_PT", &muminus_PT, "muminus_PT/D");
   ntree->Branch("muminus_P", &muminus_P, "muminus_P/D");
   //ntree->Branch("muminus_ProbNNmu", &muminus_ProbNNmu, "muminus_ProbNNmu/D");
   ntree->Branch("muminus_PIDmu", &muminus_PIDmu, "muminus_PIDmu/D");
   ntree->Branch("muplus_TRACK_GhostProb", &muplus_TRACK_GhostProb, "muplus_TRACK_GhostProb/D");
   ntree->Branch("muminus_TRACK_GhostProb", &muminus_TRACK_GhostProb, "muminus_TRACK_GhostProb/D");
   ntree->Branch("muplus_TRACK_MatchCHI2", &muplus_TRACK_MatchCHI2, "muplus_TRACK_MatchCHI2/D");
   ntree->Branch("muminus_TRACK_MatchCHI2", &muminus_TRACK_MatchCHI2, "muminus_TRACK_MatchCHI2/D");
   ntree->Branch("muplus_IPCHI2_OWNPV", &muplus_IPCHI2_OWNPV, "muplus_IPCHI2_OWNPV/D");
   ntree->Branch("muminus_IPCHI2_OWNPV", &muminus_IPCHI2_OWNPV, "muminus_IPCHI2_OWNPV/D");
   ntree->Branch("muplus_IP_OWNPV", &muplus_IP_OWNPV, "muplus_IP_OWNPV/D");
   ntree->Branch("muminus_IP_OWNPV", &muminus_IP_OWNPV, "muminus_IP_OWNPV/D");
   ntree->Branch("muplus_MINIP", &muplus_MINIP, "muplus_MINIP/D");
   ntree->Branch("muminus_MINIP", &muminus_MINIP, "muminus_MINIP/D");
   ntree->Branch("muplus_MINIPCHI2", &muplus_MINIPCHI2, "muplus_MINIPCHI2/D");
   ntree->Branch("muminus_MINIPCHI2", &muminus_MINIPCHI2, "muminus_MINIPCHI2/D");
   ntree->Branch("muplus_PE", &muplus_PE, "muplus_PE/D");
   ntree->Branch("muplus_PX", &muplus_PX, "muplus_PX/D");
   ntree->Branch("muplus_PY", &muplus_PY, "muplus_PY/D");
   ntree->Branch("muplus_PZ", &muplus_PZ, "muplus_PZ/D");
   ntree->Branch("muminus_PE", &muminus_PE, "muminus_PE/D");
   ntree->Branch("muminus_PX", &muminus_PX, "muminus_PX/D");
   ntree->Branch("muminus_PY", &muminus_PY, "muminus_PY/D");
   ntree->Branch("muminus_PZ", &muminus_PZ, "muminus_PZ/D");
   
   ntree->Branch("Jpsi_ConstJpsi_M", &Jpsi_ConstJpsi_M, "Jpsi_ConstJpsi_M/F");
   
   ntree->Branch("piminus_IPCHI2_OWNPV", &piminus_IPCHI2_OWNPV, "piminus_IPCHI2_OWNPV/D");
   ntree->Branch("piminus_PE", &piminus_PE, "piminus_PE/D");
   ntree->Branch("piminus_PX", &piminus_PX, "piminus_PX/D");
   ntree->Branch("piminus_PY", &piminus_PY, "piminus_PY/D");
   ntree->Branch("piminus_PZ", &piminus_PZ, "piminus_PZ/D");
   ntree->Branch("piminus_TRACK_CHI2NDOF", &piminus_TRACK_CHI2NDOF, "piminus_TRACK_CHI2NDOF/D");
   ntree->Branch("piminus_PT", &piminus_PT, "piminus_PT/D");
   ntree->Branch("piminus_P", &piminus_P, "piminus_P/D");
   //ntree->Branch("piminus_ProbNNk", &piminus_ProbNNk, "piminus_ProbNNk/D");
   //ntree->Branch("piminus_ProbNNpi", &piminus_ProbNNpi, "piminus_ProbNNpi/D");
   //ntree->Branch("piminus_ProbNNp", &piminus_ProbNNp, "piminus_ProbNNp/D");
   
   ntree->Branch("piminus_isMuon", &piminus_isMuon, "piminus_isMuon/B");
   
   ntree->Branch("piminus_PIDK", &piminus_PIDK, "piminus_PIDK/D");
   ntree->Branch("piminus_TRACK_GhostProb", &piminus_TRACK_GhostProb, "piminus_TRACK_GhostProb/D");
   ntree->Branch("piminus_TRACK_MatchCHI2", &piminus_TRACK_MatchCHI2, "piminus_TRACK_MatchCHI2/D");
   ntree->Branch("piminus_MINIPCHI2", &piminus_MINIPCHI2, "piminus_MINIPCHI2/D");
   ntree->Branch("piminus_MINIP", &piminus_MINIP, "piminus_MINIP/D");

   ntree->Branch("Bd_D0ToKshort_tau", &Bd_D0ToKshort_tau, "Bd_D0ToKshort_tau/D");
   ntree->Branch("Bd_D0ToKshort_tauErr", &Bd_D0ToKshort_tauErr, "Bd_D0ToKshort_tauErr/D");
   //
   ntree->Branch("Bd_D0ToKshort_M", &Bd_D0ToKshort_M, "Bd_D0ToKshort_M/F");
   ntree->Branch("Bd_D0ToKshort_MERR", &Bd_D0ToKshort_MERR, "Bd_D0ToKshort_MERR/F");
   ntree->Branch("Bd_D0ToKshort_P", &Bd_D0ToKshort_P, "Bd_D0ToKshort_P/F");
   ntree->Branch("Bd_D0ToKshort_PERR", &Bd_D0ToKshort_PERR, "Bd_D0ToKshort_PERR/F");
   ntree->Branch("Bd_D0ToKshort_decayLength", &Bd_D0ToKshort_decayLength, "Bd_D0ToKshort_decayLength/F");
   ntree->Branch("Bd_D0ToKshort_decayLengthErr", &Bd_D0ToKshort_decayLengthErr, "Bd_D0ToKshort_decayLengthErr/F");
   ntree->Branch("Bd_D0ToKshort_chi2", &Bd_D0ToKshort_chi2, "Bd_D0ToKshort_chi2/F");
   ntree->Branch("Bd_D0ToKshort_nDOF", &Bd_D0ToKshort_nDOF, "Bd_D0ToKshort_nDOF/F");
   ntree->Branch("Bd_D0ToKshort_chi2ndof", &Bd_D0ToKshort_chi2ndof, "Bd_D0ToKshort_chi2ndof/F");
   ntree->Branch("Bd_D0ToKshort_status", &Bd_D0ToKshort_status, "Bd_D0ToKshort_status/F");
   ntree->Branch("Kshort_D0ToKshort_M", &Kshort_D0ToKshort_M, "Kshort_D0ToKshort_M/F");
   ntree->Branch("Kshort_D0ToKshort_MERR", &Kshort_D0ToKshort_MERR, "Kshort_D0ToKshort_MERR/F");
   ntree->Branch("Kshort_D0ToKshort_P", &Kshort_D0ToKshort_P, "Kshort_D0ToKshort_P/F");
   ntree->Branch("Kshort_D0ToKshort_PERR", &Kshort_D0ToKshort_PERR, "Kshort_D0ToKshort_PERR/F");
   ntree->Branch("Kshort_D0ToKshort_decayLength", &Kshort_D0ToKshort_decayLength, "Kshort_D0ToKshort_decayLength/F");
   ntree->Branch("Kshort_D0ToKshort_decayLengthErr", &Kshort_D0ToKshort_decayLengthErr, "Kshort_D0ToKshort_decayLengthErr/F");
   ntree->Branch("Kshort_OnlyPV_M", &Kshort_OnlyPV_M, "Kshort_OnlyPV_M/F");
   ntree->Branch("Kshort_OnlyPV_MERR", &Kshort_OnlyPV_MERR, "Kshort_OnlyPV_MERR/F");
   ntree->Branch("Kshort_ConstJpsi_M", &Kshort_ConstJpsi_M, "Kshort_ConstJpsi_M/F");
   ntree->Branch("Kshort_ConstJpsi_MERR", &Kshort_ConstJpsi_MERR, "Kshort_ConstJpsi_MERR/F");
   //
   ntree->Branch("Kshort_P", &Kshort_P, "Kshort_P/D");
   ntree->Branch("Kshort_PT", &Kshort_PT, "Kshort_PT/D");
   ntree->Branch("Kshort_PX", &Kshort_PX, "Kshort_PX/D");
   ntree->Branch("Kshort_PY", &Kshort_PY, "Kshort_PY/D");
   ntree->Branch("Kshort_PZ", &Kshort_PZ, "Kshort_PZ/D");
   ntree->Branch("Kshort_ETA", &Kshort_ETA, "Kshort_ETA/D");
   ntree->Branch("Kshort_DOCA_12", &Kshort_DOCA_12, "Kshort_DOCA_12/D");
   ntree->Branch("Kshort_DOCA_12_CHI2", &Kshort_DOCA_12_CHI2, "Kshort_DOCA_12_CHI2/D");
   ntree->Branch("Kshort_FDS", &Kshort_FDS, "Kshort_FDS/D");
   ntree->Branch("Kshort_IPCHI2_OWNPV", &Kshort_IPCHI2_OWNPV, "Kshort_IPCHI2_OWNPV/D");
   ntree->Branch("Kshort_FDCHI2_OWNPV", &Kshort_FDCHI2_OWNPV, "Kshort_FDCHI2_OWNPV/D");
   ntree->Branch("Kshort_FD_OWNPV", &Kshort_FD_OWNPV, "Kshort_FD_OWNPV/D");
   ntree->Branch("Kshort_DIRA_OWNPV", &Kshort_DIRA_OWNPV, "Kshort_DIRA_OWNPV/D");
   ntree->Branch("Kshort_OWNPV_CHI2NDOF", &Kshort_OWNPV_CHI2NDOF, "Kshort_OWNPV_CHI2NDOF/D");
   ntree->Branch("Kshort_OWNPV_X", &Kshort_OWNPV_X, "Kshort_OWNPV_X/D");
   ntree->Branch("Kshort_OWNPV_Y", &Kshort_OWNPV_Y, "Kshort_OWNPV_Y/D");
   ntree->Branch("Kshort_OWNPV_Z", &Kshort_OWNPV_Z, "Kshort_OWNPV_Z/D");
   ntree->Branch("Kshort_ENDVERTEX_X", &Kshort_ENDVERTEX_X, "Kshort_ENDVERTEX_X/D");
   ntree->Branch("Kshort_ENDVERTEX_Y", &Kshort_ENDVERTEX_Y, "Kshort_ENDVERTEX_Y/D");
   ntree->Branch("Kshort_ENDVERTEX_Z", &Kshort_ENDVERTEX_Z, "Kshort_ENDVERTEX_Z/D");
   ntree->Branch("Kshort_ENDVERTEX_CHI2NDOF", &Kshort_ENDVERTEX_CHI2NDOF, "Kshort_ENDVERTEX_CHI2NDOF/D");
   ntree->Branch("piplus_IPCHI2_OWNPV", &piplus_IPCHI2_OWNPV, "piplus_IPCHI2_OWNPV/D");
   ntree->Branch("piplus_MINIPCHI2", &piplus_MINIPCHI2, "piplus_MINIPCHI2/D");
   ntree->Branch("piplus_MINIP", &piplus_MINIP, "piplus_MINIP/D");
   ntree->Branch("piplus_PE", &piplus_PE, "piplus_PE/D");
   ntree->Branch("piplus_PX", &piplus_PX, "piplus_PX/D");
   ntree->Branch("piplus_PY", &piplus_PY, "piplus_PY/D");
   ntree->Branch("piplus_PZ", &piplus_PZ, "piplus_PZ/D");
   ntree->Branch("piplus_TRACK_CHI2NDOF", &piplus_TRACK_CHI2NDOF, "piplus_TRACK_CHI2NDOF/D");
   ntree->Branch("piplus_PT", &piplus_PT, "piplus_PT/D");
   ntree->Branch("piplus_P", &piplus_P, "piplus_P/D");
   
   ntree->Branch("piplus_isMuon", &piplus_isMuon, "piplus_isMuon/B");
   
   ntree->Branch("piplus_PIDK", &piplus_PIDK, "piplus_PIDK/D");
   ntree->Branch("piplus_TRACK_GhostProb", &piplus_TRACK_GhostProb, "piplus_TRACK_GhostProb/D");
   ntree->Branch("piplus_TRACK_MatchCHI2", &piplus_TRACK_MatchCHI2, "piplus_TRACK_MatchCHI2/D");

 
   //new branch
   ntree->Branch("min_mu_PIDmu",&min_mu_PIDmu,"min_mu_PIDmu/D");
   // ntree->Branch("piplus_ProbNNpi_k_corr",&piplus_ProbNNpi_k_corr,"piplus_ProbNNpi_k_corr/D");
   // ntree->Branch("piminus_ProbNNpi_k_corr",&piminus_ProbNNpi_k_corr,"piminus_ProbNNpi_k_corr/D");
   ntree->Branch("log_Bd_IPCHI2_OWNPV",&log_Bd_IPCHI2_OWNPV,"log_Bd_IPCHI2_OWNPV/D");
   ntree->Branch("log_Bd_ENDVERTEX_CHI2NDOF",&log_Bd_ENDVERTEX_CHI2NDOF,"log_Bd_ENDVERTEX_CHI2NDOF/D");
   ntree->Branch("trigb",&trigb,"trigb/B");
   ntree->Branch("trigj",&trigj,"trigj/B");
   //ntree->Branch("log_Bd_DTF_NoPV_CHI2NDOF",&log_Bd_DTF_NoPV_CHI2NDOF,"log_Bd_DTF_NoPV_CHI2NDOF/D");
   ntree->Branch("log_Bd_OnlyPV_CHI2NDOF",&log_Bd_OnlyPV_CHI2NDOF,"log_Bd_OnlyPV_CHI2NDOF/D");
   ntree->Branch("min_mu_ProbNNmu_corr",&min_mu_ProbNNmu_corr,"min_mu_ProbNNmu_corr/D");
   ntree->Branch("m_ppi",&m_ppi,"m_ppi/D");
    if (sig_mc) {
      fChain->SetBranchAddress("muplus_ProbNNmu_pidcorr_default", &muplus_ProbNNmu_pidcorr_default);
      fChain->SetBranchAddress("muminus_ProbNNmu_pidcorr_default", &muminus_ProbNNmu_pidcorr_default);
   } else {
      fChain->SetBranchAddress("muplus_ProbNNmu", &muplus_ProbNNmu);
      fChain->SetBranchAddress("muminus_ProbNNmu", &muminus_ProbNNmu);
   }

   Long64_t nentries = runevt;
   for(Long64_t jentry=0; jentry<nentries;jentry++) {

	if(jentry%100000==0) cout<<"  Processing "<<jentry/1000<<" k. "<<endl;
	Long64_t ientry = LoadTree(jentry);
	if(ientry < 0) break;
	fChain->GetEntry(jentry);  
      //  std::cout << "Event " << jentry << ": "
      //         << "muplus_ProbNNmu_corr = " << muplus_ProbNNmu_corr << ", "
      //         << "muminus_ProbNNmu_corr = " << muminus_ProbNNmu_corr << std::endl;
 //cut 
   if (sig_mc) {
         muplus_ProbNNmu_corr = muplus_ProbNNmu_pidcorr_default;
         muminus_ProbNNmu_corr = muminus_ProbNNmu_pidcorr_default;
      }
   else{
       muplus_ProbNNmu_corr = muplus_ProbNNmu;
       muminus_ProbNNmu_corr = muminus_ProbNNmu;
   }
   if(sig_mc){
      if(!(Bd_BKGCAT == 0 || Bd_BKGCAT == 10 || (Bd_BKGCAT == 50 && Bd_TRUETAU > 0) || Bd_BKGCAT == 60)) continue;
   }
   //triggerline
	//if(!( Jpsi_Hlt1DiMuonHighMassDecision_TOS)) continue;
   //if(!( Jpsi_L0Global_Dec )) continue;
	if(!( Jpsi_Hlt1DiMuonHighMassDecision_TOS || Bd_Hlt1TrackMuonMVADecision_TOS || Bd_Hlt1TwoTrackMVADecision_TOS )) continue;
	if(!( Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS )) continue;
   //daughter cut kshort->pi+pi-
   if(!( piplus_P>2500 )) continue;
   if(!( piplus_PT>300 )) continue;
   if(!( piplus_PIDK<0 )) continue;
   //(MINIPCHI2WITHDV()>5

   if(!( piminus_P>2500 )) continue;
   if(!( piminus_PT>300 )) continue;
   if(!( piminus_PIDK<0 )) continue;
   // (MINIPCHI2WITHDV()>5
   // //kshort cut
   if(!(fabs(Kshort_ConstJpsi_M-497.61)<40 )) continue;
   if(!(Kshort_ENDVERTEX_CHI2NDOF<30)) continue;
   if(!(Kshort_DOCA_12_CHI2<30)) continue;
   // //B cut
   if(!(Bd_ENDVERTEX_CHI2NDOF>0&&Bd_ENDVERTEX_CHI2NDOF<10))continue;
   if(!(fabs(Bd_ConstJpsi_M-5279.6)<200))continue;
   if(!(Bd_ConstJpsi_tau>0.2&&Bd_ConstJpsi_tau<15.))continue;
   if(!(Bd_DIRA_OWNPV>0.999))continue;
   if(!(Bd_IPCHI2_OWNPV>0 && Bd_IPCHI2_OWNPV<20 )) continue;
   //if(!(Bd_DTF_NoPV_CHI2NDOF>0&&Bd_DTF_NoPV_CHI2NDOF < 20)) continue;
   if(!(Bd_OnlyPV_CHI2NDOF>0&&Bd_OnlyPV_CHI2NDOF < 1e10)) continue;
   if(!(muplus_ProbNNmu_corr>0&&muminus_ProbNNmu_corr >0)) continue;
   
      //hp:pi+ hm:pi- lp:mu+ lm:mu-
	// Jpsippi  : p+pi- -> pi+pi-
	double m_pi = 139.57061;    // pi+ mass
	double m_p  = 938.2720813;  // p+  mass

	TLorentzVector p_vec, pi_vec,ppi_vec;
	double p_PE = sqrt( pow(m_p,2) +pow(piplus_PX,2) +pow(piplus_PY,2) +pow(piplus_PZ,2) );
	p_vec.SetPxPyPzE( piplus_PX, piplus_PY, piplus_PZ, p_PE );

   double pi_PE = sqrt( pow(m_pi,2) +pow(piminus_PX,2) +pow(piminus_PY,2) +pow(piminus_PZ,2) );
	pi_vec.SetPxPyPzE( piminus_PX, piminus_PY, piminus_PZ, piminus_PE );
   ppi_vec = p_vec + pi_vec;
   m_ppi= ppi_vec.M();
   
   double tmp_hp_ProbNNp = max(piplus_ProbNNp_corr,piminus_ProbNNp_corr);
   if(!(m_ppi <1100 || m_ppi >1130||(m_ppi >1100 && m_ppi < 1130 && tmp_hp_ProbNNp < 0.05))) continue;
   
   
   min_mu_PIDmu=min(muplus_PIDmu,muminus_PIDmu);
   // piplus_ProbNNpi_k_corr= piplus_ProbNNpi_corr*(1-piplus_ProbNNk_corr);
   // piminus_ProbNNpi_k_corr=piminus_ProbNNpi_corr*(1-piminus_ProbNNk_corr);
   log_Bd_IPCHI2_OWNPV=log(Bd_IPCHI2_OWNPV);
   log_Bd_ENDVERTEX_CHI2NDOF=log(Bd_ENDVERTEX_CHI2NDOF);
   //log_Bd_DTF_NoPV_CHI2NDOF=log(Bd_DTF_NoPV_CHI2NDOF);
   log_Bd_OnlyPV_CHI2NDOF=log(Bd_OnlyPV_CHI2NDOF);
   min_mu_ProbNNmu_corr = min(muplus_ProbNNmu_corr, muminus_ProbNNmu_corr);
   
	// Use the momentumn info. from DTF with constraint on PV and Jpsi mass
	// to caculate helicity angles
	// TLorentzVector lp_vec2,lm_vec2;
	// TLorentzVector hp_vec2,hm_vec2;

	// lp_vec2.SetPxPyPzE( 
	// 	Bd_PVConst_J_psi_1S_muminus_0_PX[0], 
	// 	Bd_PVConst_J_psi_1S_muminus_0_PY[0], 
	// 	Bd_PVConst_J_psi_1S_muminus_0_PZ[0], 
	// 	Bd_PVConst_J_psi_1S_muminus_0_PE[0] );
	// lm_vec2.SetPxPyPzE( 
	// 	Bd_PVConst_J_psi_1S_muminus_PX[0], 
	// 	Bd_PVConst_J_psi_1S_muminus_PY[0], 
	// 	Bd_PVConst_J_psi_1S_muminus_PZ[0], 
	// 	Bd_PVConst_J_psi_1S_muminus_PE[0] );
	// hp_vec2.SetPxPyPzE( 
   //    Ks_PX,
   //    Ks_PY,
   //    Ks_PZ,
	//    Ks_PE );
   // hm_vec2.SetPxPyPzE(
	//    piplus_PX,
	//    piplus_PY,
   //    piplus_PZ,
	//    piplus_PE );

   //    // hp_ID/lp_ID can be postive or negative in a decay with unneutral final states 
   //    cosh  = CalculateHelicityPolarAngle( lp_vec2, lm_vec2, hp_vec2, hm_vec2 );
   //    cosl  = CalculateHelicityPolarAngle( hp_vec2, hm_vec2, lp_vec2, lm_vec2 );
   //    phih  = CalculatePlaneAngle( lp_vec2, lm_vec2, hp_vec2, hm_vec2 );
   
      trigb = ((Bd_Hlt1TrackMuonMVADecision_TOS || Bd_Hlt1TwoTrackMVADecision_TOS) && !Jpsi_Hlt1DiMuonHighMassDecision_TOS);
      trigj = Jpsi_Hlt1DiMuonHighMassDecision_TOS;

      ntree->Fill();
   }

   rootfile->cd();
   ntree->Write("",TObject::kWriteDelete);
   rootfile->Close();

   delete rootfile;

}

