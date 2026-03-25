//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 23 15:51:20 2025 by ROOT version 6.32.02
// from TChain /
//////////////////////////////////////////////////////////

#ifndef massfit_h
#define massfit_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class massfit {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Long64_t        index;
   Int_t           year;
   Int_t           runNumber;
   Long64_t        eventNumber;
   Int_t           Bd_BKGCAT;
   Int_t           Bd_TRUEID;
   Int_t           Kshort_TRUEID;
   Int_t           Jpsi_TRUEID;
   Int_t           piplus_TRUEID;
   Double_t        Bd_TRUETAU;
   Double_t        Bd_TRUEP_X;
   Double_t        Bd_TRUEP_Y;
   Double_t        Bd_TRUEP_Z;
   Double_t        Bd_TRUEP_E;
   Double_t        Bd_TRUEPT;
   Double_t        Jpsi_TRUEP_X;
   Double_t        Jpsi_TRUEP_Y;
   Double_t        Jpsi_TRUEP_Z;
   Double_t        Jpsi_TRUEP_E;
   Double_t        Jpsi_TRUEPT;
   Double_t        piplus_ProbNNk_corr;
   Double_t        piplus_ProbNNpi_corr;
   Double_t        piplus_ProbNNp_corr;
   Double_t        piminus_ProbNNk_corr;
   Double_t        piminus_ProbNNpi_corr;
   Double_t        piminus_ProbNNp_corr;
   Double_t        muplus_ProbNNmu_corr;
   Double_t        muminus_ProbNNmu_corr;
   Int_t           nTracks;
   Int_t           nLongTracks;
   Int_t           nPVs;
   Int_t           nSPDHits;
   Long64_t        totCandidates;
   Int_t           L0DUTCK;
   Int_t           HLT1TCK;
   Int_t           HLT2TCK;
   Double_t        Bd_ConstJpsi_tau;
   Double_t        Bd_ConstJpsi_tauErr;
   Float_t         Bd_ConstJpsi_M;
   Float_t         Bd_ConstJpsi_MERR;
   Float_t         Bd_OnlyPV_M;
   Float_t         Bd_OnlyPV_MERR;
   Double_t        Bd_OnlyPV_tau;
   Double_t        Bd_OnlyPV_tauErr;
   Double_t        Bd_ConstJpsi_CHI2NDOF;
   Double_t        Bd_OnlyPV_CHI2NDOF;
   Double_t        Bd_IP_OWNPV;
   Double_t        Bd_IPCHI2_OWNPV;
   Double_t        Bd_FD_OWNPV;
   Double_t        Bd_FDCHI2_OWNPV;
   Double_t        Bd_DIRA_OWNPV;
   Double_t        Bd_TAU;
   Double_t        Bd_TAUERR;
   Char_t          Bd_L0Global_Dec;
   Char_t          Bd_L0MuonDecision_TOS;
   Char_t          Bd_L0DiMuonDecision_TOS;
   Char_t          Bd_Hlt1TrackMuonMVADecision_TOS;
   Char_t          Bd_Hlt1TwoTrackMVADecision_TOS;
   Char_t          Bd_Hlt1DiMuonHighMassDecision_TOS;
   Char_t          Jpsi_Hlt1TrackMuonDecision_TOS;
   Char_t          Jpsi_Hlt1DiMuonHighMassDecision_TOS;
   Char_t          Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS;
   Int_t           hlt1b;
   Double_t        Bd_ENDVERTEX_X;
   Double_t        Bd_ENDVERTEX_Y;
   Double_t        Bd_ENDVERTEX_Z;
   Double_t        Bd_ENDVERTEX_CHI2NDOF;
   Double_t        Bd_OWNPV_X;
   Double_t        Bd_OWNPV_Y;
   Double_t        Bd_OWNPV_Z;
   Double_t        Bd_OWNPV_CHI2NDOF;
   Double_t        Bd_MINIPCHI2NEXTBEST;
   Double_t        Bd_MINIPCHI2;
   Double_t        Bd_MINIP;
   Double_t        Bd_DTF_NoPV_CHI2NDOF;
   Double_t        Jpsi_MM;
   Float_t         Jpsi_ConstJpsiNoPV_M;
   Float_t         Jpsi_OnlyPV_M;
   Double_t        Jpsi_ENDVERTEX_CHI2;
   Int_t           Jpsi_ENDVERTEX_NDOF;
   Double_t        Jpsi_ENDVERTEX_CHI2NDOF;
   Double_t        Bd_ETA;
   Double_t        Bd_PX;
   Double_t        Bd_PY;
   Double_t        Bd_PZ;
   Double_t        Bd_PT;
   Double_t        Bd_PE;
   Double_t        Bd_P;
   Double_t        Bd_M;
   Int_t           Bd_ID;
   Double_t        muplus_TRACK_CHI2NDOF;
   Double_t        muplus_PT;
   Double_t        muplus_P;
   Double_t        muplus_PIDmu;
   Double_t        muminus_TRACK_CHI2NDOF;
   Double_t        muminus_PT;
   Double_t        muminus_P;
   Double_t        muminus_PIDmu;
   Double_t        muplus_TRACK_GhostProb;
   Double_t        muminus_TRACK_GhostProb;
   Double_t        muplus_TRACK_MatchCHI2;
   Double_t        muminus_TRACK_MatchCHI2;
   Double_t        muplus_IPCHI2_OWNPV;
   Double_t        muminus_IPCHI2_OWNPV;
   Double_t        muplus_IP_OWNPV;
   Double_t        muminus_IP_OWNPV;
   Double_t        muplus_MINIP;
   Double_t        muminus_MINIP;
   Double_t        muplus_MINIPCHI2;
   Double_t        muminus_MINIPCHI2;
   Double_t        muplus_PE;
   Double_t        muplus_PX;
   Double_t        muplus_PY;
   Double_t        muplus_PZ;
   Double_t        muminus_PE;
   Double_t        muminus_PX;
   Double_t        muminus_PY;
   Double_t        muminus_PZ;
   Float_t         Jpsi_ConstJpsi_M;
   Double_t        piminus_IPCHI2_OWNPV;
   Double_t        piminus_PE;
   Double_t        piminus_PX;
   Double_t        piminus_PY;
   Double_t        piminus_PZ;
   Double_t        piminus_TRACK_CHI2NDOF;
   Double_t        piminus_PT;
   Double_t        piminus_P;
   Char_t          piminus_isMuon;
   Double_t        piminus_PIDK;
   Double_t        piminus_TRACK_GhostProb;
   Double_t        piminus_TRACK_MatchCHI2;
   Double_t        piminus_MINIPCHI2;
   Double_t        piminus_MINIP;
   Double_t        Bd_D0ToKshort_tau;
   Double_t        Bd_D0ToKshort_tauErr;
   Float_t         Bd_D0ToKshort_M;
   Float_t         Bd_D0ToKshort_MERR;
   Float_t         Bd_D0ToKshort_P;
   Float_t         Bd_D0ToKshort_PERR;
   Float_t         Bd_D0ToKshort_decayLength;
   Float_t         Bd_D0ToKshort_decayLengthErr;
   Float_t         Bd_D0ToKshort_chi2;
   Float_t         Bd_D0ToKshort_nDOF;
   Float_t         Bd_D0ToKshort_chi2ndof;
   Float_t         Bd_D0ToKshort_status;
   Float_t         Kshort_D0ToKshort_M;
   Float_t         Kshort_D0ToKshort_MERR;
   Float_t         Kshort_D0ToKshort_P;
   Float_t         Kshort_D0ToKshort_PERR;
   Float_t         Kshort_D0ToKshort_decayLength;
   Float_t         Kshort_D0ToKshort_decayLengthErr;
   Float_t         Kshort_OnlyPV_M;
   Float_t         Kshort_OnlyPV_MERR;
   Float_t         Kshort_ConstJpsi_M;
   Float_t         Kshort_ConstJpsi_MERR;
   Double_t        Kshort_P;
   Double_t        Kshort_PT;
   Double_t        Kshort_PX;
   Double_t        Kshort_PY;
   Double_t        Kshort_PZ;
   Double_t        Kshort_ETA;
   Double_t        Kshort_DOCA_12;
   Double_t        Kshort_DOCA_12_CHI2;
   Double_t        Kshort_FDS;
   Double_t        Kshort_IPCHI2_OWNPV;
   Double_t        Kshort_FDCHI2_OWNPV;
   Double_t        Kshort_FD_OWNPV;
   Double_t        Kshort_DIRA_OWNPV;
   Double_t        Kshort_OWNPV_CHI2NDOF;
   Double_t        Kshort_OWNPV_X;
   Double_t        Kshort_OWNPV_Y;
   Double_t        Kshort_OWNPV_Z;
   Double_t        Kshort_ENDVERTEX_X;
   Double_t        Kshort_ENDVERTEX_Y;
   Double_t        Kshort_ENDVERTEX_Z;
   Double_t        Kshort_ENDVERTEX_CHI2NDOF;
   Double_t        piplus_IPCHI2_OWNPV;
   Double_t        piplus_MINIPCHI2;
   Double_t        piplus_MINIP;
   Double_t        piplus_PE;
   Double_t        piplus_PX;
   Double_t        piplus_PY;
   Double_t        piplus_PZ;
   Double_t        piplus_TRACK_CHI2NDOF;
   Double_t        piplus_PT;
   Double_t        piplus_P;
   Char_t          piplus_isMuon;
   Double_t        piplus_PIDK;
   Double_t        piplus_TRACK_GhostProb;
   Double_t        piplus_TRACK_MatchCHI2;
   Double_t        min_mu_PIDmu;
   Double_t        log_Bd_IPCHI2_OWNPV;
   Double_t        log_Bd_ENDVERTEX_CHI2NDOF;
   Char_t          trigb;
   Char_t          trigj;
   Double_t        log_Bd_DTF_NoPV_CHI2NDOF;
   Double_t        log_Bd_OnlyPV_CHI2NDOF;
   Double_t        min_mu_ProbNNmu_corr;
   Double_t        gbw;
   Long64_t        rndNumber;
   Double_t        BDT;

   // List of branches
   TBranch        *b_index;   //!
   TBranch        *b_year;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_Bd_BKGCAT;   //!
   TBranch        *b_Bd_TRUEID;   //!
   TBranch        *b_Kshort_TRUEID;   //!
   TBranch        *b_Jpsi_TRUEID;   //!
   TBranch        *b_piplus_TRUEID;   //!
   TBranch        *b_Bd_TRUETAU;   //!
   TBranch        *b_Bd_TRUEP_X;   //!
   TBranch        *b_Bd_TRUEP_Y;   //!
   TBranch        *b_Bd_TRUEP_Z;   //!
   TBranch        *b_Bd_TRUEP_E;   //!
   TBranch        *b_Bd_TRUEPT;   //!
   TBranch        *b_Jpsi_TRUEP_X;   //!
   TBranch        *b_Jpsi_TRUEP_Y;   //!
   TBranch        *b_Jpsi_TRUEP_Z;   //!
   TBranch        *b_Jpsi_TRUEP_E;   //!
   TBranch        *b_Jpsi_TRUEPT;   //!
   TBranch        *b_piplus_ProbNNk_corr;   //!
   TBranch        *b_piplus_ProbNNpi_corr;   //!
   TBranch        *b_piplus_ProbNNp_corr;   //!
   TBranch        *b_piminus_ProbNNk_corr;   //!
   TBranch        *b_piminus_ProbNNpi_corr;   //!
   TBranch        *b_piminus_ProbNNp_corr;   //!
   TBranch        *b_muplus_ProbNNmu_corr;   //!
   TBranch        *b_muminus_ProbNNmu_corr;   //!
   TBranch        *b_nTracks;   //!
   TBranch        *b_nLongTracks;   //!
   TBranch        *b_nPVs;   //!
   TBranch        *b_nSPDHits;   //!
   TBranch        *b_totCandidates;   //!
   TBranch        *b_L0DUTCK;   //!
   TBranch        *b_HLT1TCK;   //!
   TBranch        *b_HLT2TCK;   //!
   TBranch        *b_Bd_ConstJpsi_tau;   //!
   TBranch        *b_Bd_ConstJpsi_tauErr;   //!
   TBranch        *b_Bd_ConstJpsi_M;   //!
   TBranch        *b_Bd_ConstJpsi_MERR;   //!
   TBranch        *b_Bd_OnlyPV_M;   //!
   TBranch        *b_Bd_OnlyPV_MERR;   //!
   TBranch        *b_Bd_OnlyPV_tau;   //!
   TBranch        *b_Bd_OnlyPV_tauErr;   //!
   TBranch        *b_Bd_ConstJpsi_CHI2NDOF;   //!
   TBranch        *b_Bd_OnlyPV_CHI2NDOF;   //!
   TBranch        *b_Bd_IP_OWNPV;   //!
   TBranch        *b_Bd_IPCHI2_OWNPV;   //!
   TBranch        *b_Bd_FD_OWNPV;   //!
   TBranch        *b_Bd_FDCHI2_OWNPV;   //!
   TBranch        *b_Bd_DIRA_OWNPV;   //!
   TBranch        *b_Bd_TAU;   //!
   TBranch        *b_Bd_TAUERR;   //!
   TBranch        *b_Bd_L0Global_Dec;   //!
   TBranch        *b_Bd_L0MuonDecision_TOS;   //!
   TBranch        *b_Bd_L0DiMuonDecision_TOS;   //!
   TBranch        *b_Bd_Hlt1TrackMuonMVADecision_TOS;   //!
   TBranch        *b_Bd_Hlt1TwoTrackMVADecision_TOS;   //!
   TBranch        *b_Bd_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_Jpsi_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_Jpsi_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS;   //!
   TBranch        *b_hlt1b;   //!
   TBranch        *b_Bd_ENDVERTEX_X;   //!
   TBranch        *b_Bd_ENDVERTEX_Y;   //!
   TBranch        *b_Bd_ENDVERTEX_Z;   //!
   TBranch        *b_Bd_ENDVERTEX_CHI2NDOF;   //!
   TBranch        *b_Bd_OWNPV_X;   //!
   TBranch        *b_Bd_OWNPV_Y;   //!
   TBranch        *b_Bd_OWNPV_Z;   //!
   TBranch        *b_Bd_OWNPV_CHI2NDOF;   //!
   TBranch        *b_Bd_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_Bd_MINIPCHI2;   //!
   TBranch        *b_Bd_MINIP;   //!
   TBranch        *b_Bd_DTF_NoPV_CHI2NDOF;   //!
   TBranch        *b_Jpsi_MM;   //!
   TBranch        *b_Jpsi_ConstJpsiNoPV_M;   //!
   TBranch        *b_Jpsi_OnlyPV_M;   //!
   TBranch        *b_Jpsi_ENDVERTEX_CHI2;   //!
   TBranch        *b_Jpsi_ENDVERTEX_NDOF;   //!
   TBranch        *b_Jpsi_ENDVERTEX_CHI2NDOF;   //!
   TBranch        *b_Bd_ETA;   //!
   TBranch        *b_Bd_PX;   //!
   TBranch        *b_Bd_PY;   //!
   TBranch        *b_Bd_PZ;   //!
   TBranch        *b_Bd_PT;   //!
   TBranch        *b_Bd_PE;   //!
   TBranch        *b_Bd_P;   //!
   TBranch        *b_Bd_M;   //!
   TBranch        *b_Bd_ID;   //!
   TBranch        *b_muplus_TRACK_CHI2NDOF;   //!
   TBranch        *b_muplus_PT;   //!
   TBranch        *b_muplus_P;   //!
   TBranch        *b_muplus_PIDmu;   //!
   TBranch        *b_muminus_TRACK_CHI2NDOF;   //!
   TBranch        *b_muminus_PT;   //!
   TBranch        *b_muminus_P;   //!
   TBranch        *b_muminus_PIDmu;   //!
   TBranch        *b_muplus_TRACK_GhostProb;   //!
   TBranch        *b_muminus_TRACK_GhostProb;   //!
   TBranch        *b_muplus_TRACK_MatchCHI2;   //!
   TBranch        *b_muminus_TRACK_MatchCHI2;   //!
   TBranch        *b_muplus_IPCHI2_OWNPV;   //!
   TBranch        *b_muminus_IPCHI2_OWNPV;   //!
   TBranch        *b_muplus_IP_OWNPV;   //!
   TBranch        *b_muminus_IP_OWNPV;   //!
   TBranch        *b_muplus_MINIP;   //!
   TBranch        *b_muminus_MINIP;   //!
   TBranch        *b_muplus_MINIPCHI2;   //!
   TBranch        *b_muminus_MINIPCHI2;   //!
   TBranch        *b_muplus_PE;   //!
   TBranch        *b_muplus_PX;   //!
   TBranch        *b_muplus_PY;   //!
   TBranch        *b_muplus_PZ;   //!
   TBranch        *b_muminus_PE;   //!
   TBranch        *b_muminus_PX;   //!
   TBranch        *b_muminus_PY;   //!
   TBranch        *b_muminus_PZ;   //!
   TBranch        *b_Jpsi_ConstJpsi_M;   //!
   TBranch        *b_piminus_IPCHI2_OWNPV;   //!
   TBranch        *b_piminus_PE;   //!
   TBranch        *b_piminus_PX;   //!
   TBranch        *b_piminus_PY;   //!
   TBranch        *b_piminus_PZ;   //!
   TBranch        *b_piminus_TRACK_CHI2NDOF;   //!
   TBranch        *b_piminus_PT;   //!
   TBranch        *b_piminus_P;   //!
   TBranch        *b_piminus_isMuon;   //!
   TBranch        *b_piminus_PIDK;   //!
   TBranch        *b_piminus_TRACK_GhostProb;   //!
   TBranch        *b_piminus_TRACK_MatchCHI2;   //!
   TBranch        *b_piminus_MINIPCHI2;   //!
   TBranch        *b_piminus_MINIP;   //!
   TBranch        *b_Bd_D0ToKshort_tau;   //!
   TBranch        *b_Bd_D0ToKshort_tauErr;   //!
   TBranch        *b_Bd_D0ToKshort_M;   //!
   TBranch        *b_Bd_D0ToKshort_MERR;   //!
   TBranch        *b_Bd_D0ToKshort_P;   //!
   TBranch        *b_Bd_D0ToKshort_PERR;   //!
   TBranch        *b_Bd_D0ToKshort_decayLength;   //!
   TBranch        *b_Bd_D0ToKshort_decayLengthErr;   //!
   TBranch        *b_Bd_D0ToKshort_chi2;   //!
   TBranch        *b_Bd_D0ToKshort_nDOF;   //!
   TBranch        *b_Bd_D0ToKshort_chi2ndof;   //!
   TBranch        *b_Bd_D0ToKshort_status;   //!
   TBranch        *b_Kshort_D0ToKshort_M;   //!
   TBranch        *b_Kshort_D0ToKshort_MERR;   //!
   TBranch        *b_Kshort_D0ToKshort_P;   //!
   TBranch        *b_Kshort_D0ToKshort_PERR;   //!
   TBranch        *b_Kshort_D0ToKshort_decayLength;   //!
   TBranch        *b_Kshort_D0ToKshort_decayLengthErr;   //!
   TBranch        *b_Kshort_OnlyPV_M;   //!
   TBranch        *b_Kshort_OnlyPV_MERR;   //!
   TBranch        *b_Kshort_ConstJpsi_M;   //!
   TBranch        *b_Kshort_ConstJpsi_MERR;   //!
   TBranch        *b_Kshort_P;   //!
   TBranch        *b_Kshort_PT;   //!
   TBranch        *b_Kshort_PX;   //!
   TBranch        *b_Kshort_PY;   //!
   TBranch        *b_Kshort_PZ;   //!
   TBranch        *b_Kshort_ETA;   //!
   TBranch        *b_Kshort_DOCA_12;   //!
   TBranch        *b_Kshort_DOCA_12_CHI2;   //!
   TBranch        *b_Kshort_FDS;   //!
   TBranch        *b_Kshort_IPCHI2_OWNPV;   //!
   TBranch        *b_Kshort_FDCHI2_OWNPV;   //!
   TBranch        *b_Kshort_FD_OWNPV;   //!
   TBranch        *b_Kshort_DIRA_OWNPV;   //!
   TBranch        *b_Kshort_OWNPV_CHI2NDOF;   //!
   TBranch        *b_Kshort_OWNPV_X;   //!
   TBranch        *b_Kshort_OWNPV_Y;   //!
   TBranch        *b_Kshort_OWNPV_Z;   //!
   TBranch        *b_Kshort_ENDVERTEX_X;   //!
   TBranch        *b_Kshort_ENDVERTEX_Y;   //!
   TBranch        *b_Kshort_ENDVERTEX_Z;   //!
   TBranch        *b_Kshort_ENDVERTEX_CHI2NDOF;   //!
   TBranch        *b_piplus_IPCHI2_OWNPV;   //!
   TBranch        *b_piplus_MINIPCHI2;   //!
   TBranch        *b_piplus_MINIP;   //!
   TBranch        *b_piplus_PE;   //!
   TBranch        *b_piplus_PX;   //!
   TBranch        *b_piplus_PY;   //!
   TBranch        *b_piplus_PZ;   //!
   TBranch        *b_piplus_TRACK_CHI2NDOF;   //!
   TBranch        *b_piplus_PT;   //!
   TBranch        *b_piplus_P;   //!
   TBranch        *b_piplus_isMuon;   //!
   TBranch        *b_piplus_PIDK;   //!
   TBranch        *b_piplus_TRACK_GhostProb;   //!
   TBranch        *b_piplus_TRACK_MatchCHI2;   //!
   TBranch        *b_min_mu_PIDmu;   //!
   TBranch        *b_log_Bd_IPCHI2_OWNPV;   //!
   TBranch        *b_log_Bd_ENDVERTEX_CHI2NDOF;   //!
   TBranch        *b_trigb;   //!
   TBranch        *b_trigj;   //!
   TBranch        *b_log_Bd_DTF_NoPV_CHI2NDOF;   //!
   TBranch        *b_log_Bd_OnlyPV_CHI2NDOF;   //!
   TBranch        *b_min_mu_ProbNNmu_corr;   //!
   TBranch        *b_gbw;   //!
   TBranch        *b_rndNumber;   //!
   TBranch        *b_BDT;   //!

   massfit(TTree *tree=0);
   virtual ~massfit();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop( Long64_t runevt, const char *runmode );
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef massfit_cxx
massfit::massfit(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("","");
      chain->Add("/lzufs/user/zhanghy/Sample/Train/Bd2JpsiKshort_mc_2016_BDT.root/DecayTree");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

massfit::~massfit()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t massfit::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t massfit::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void massfit::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("index", &index, &b_index);
   fChain->SetBranchAddress("year", &year, &b_year);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("Bd_BKGCAT", &Bd_BKGCAT, &b_Bd_BKGCAT);
   fChain->SetBranchAddress("Bd_TRUEID", &Bd_TRUEID, &b_Bd_TRUEID);
   fChain->SetBranchAddress("Kshort_TRUEID", &Kshort_TRUEID, &b_Kshort_TRUEID);
   fChain->SetBranchAddress("Jpsi_TRUEID", &Jpsi_TRUEID, &b_Jpsi_TRUEID);
   fChain->SetBranchAddress("piplus_TRUEID", &piplus_TRUEID, &b_piplus_TRUEID);
   fChain->SetBranchAddress("Bd_TRUETAU", &Bd_TRUETAU, &b_Bd_TRUETAU);
   fChain->SetBranchAddress("Bd_TRUEP_X", &Bd_TRUEP_X, &b_Bd_TRUEP_X);
   fChain->SetBranchAddress("Bd_TRUEP_Y", &Bd_TRUEP_Y, &b_Bd_TRUEP_Y);
   fChain->SetBranchAddress("Bd_TRUEP_Z", &Bd_TRUEP_Z, &b_Bd_TRUEP_Z);
   fChain->SetBranchAddress("Bd_TRUEP_E", &Bd_TRUEP_E, &b_Bd_TRUEP_E);
   fChain->SetBranchAddress("Bd_TRUEPT", &Bd_TRUEPT, &b_Bd_TRUEPT);
   fChain->SetBranchAddress("Jpsi_TRUEP_X", &Jpsi_TRUEP_X, &b_Jpsi_TRUEP_X);
   fChain->SetBranchAddress("Jpsi_TRUEP_Y", &Jpsi_TRUEP_Y, &b_Jpsi_TRUEP_Y);
   fChain->SetBranchAddress("Jpsi_TRUEP_Z", &Jpsi_TRUEP_Z, &b_Jpsi_TRUEP_Z);
   fChain->SetBranchAddress("Jpsi_TRUEP_E", &Jpsi_TRUEP_E, &b_Jpsi_TRUEP_E);
   fChain->SetBranchAddress("Jpsi_TRUEPT", &Jpsi_TRUEPT, &b_Jpsi_TRUEPT);
   fChain->SetBranchAddress("piplus_ProbNNk_corr", &piplus_ProbNNk_corr, &b_piplus_ProbNNk_corr);
   fChain->SetBranchAddress("piplus_ProbNNpi_corr", &piplus_ProbNNpi_corr, &b_piplus_ProbNNpi_corr);
   fChain->SetBranchAddress("piplus_ProbNNp_corr", &piplus_ProbNNp_corr, &b_piplus_ProbNNp_corr);
   fChain->SetBranchAddress("piminus_ProbNNk_corr", &piminus_ProbNNk_corr, &b_piminus_ProbNNk_corr);
   fChain->SetBranchAddress("piminus_ProbNNpi_corr", &piminus_ProbNNpi_corr, &b_piminus_ProbNNpi_corr);
   fChain->SetBranchAddress("piminus_ProbNNp_corr", &piminus_ProbNNp_corr, &b_piminus_ProbNNp_corr);
   fChain->SetBranchAddress("muplus_ProbNNmu_corr", &muplus_ProbNNmu_corr, &b_muplus_ProbNNmu_corr);
   fChain->SetBranchAddress("muminus_ProbNNmu_corr", &muminus_ProbNNmu_corr, &b_muminus_ProbNNmu_corr);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
   fChain->SetBranchAddress("nLongTracks", &nLongTracks, &b_nLongTracks);
   fChain->SetBranchAddress("nPVs", &nPVs, &b_nPVs);
   fChain->SetBranchAddress("nSPDHits", &nSPDHits, &b_nSPDHits);
   fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
   fChain->SetBranchAddress("L0DUTCK", &L0DUTCK, &b_L0DUTCK);
   fChain->SetBranchAddress("HLT1TCK", &HLT1TCK, &b_HLT1TCK);
   fChain->SetBranchAddress("HLT2TCK", &HLT2TCK, &b_HLT2TCK);
   fChain->SetBranchAddress("Bd_ConstJpsi_tau", &Bd_ConstJpsi_tau, &b_Bd_ConstJpsi_tau);
   fChain->SetBranchAddress("Bd_ConstJpsi_tauErr", &Bd_ConstJpsi_tauErr, &b_Bd_ConstJpsi_tauErr);
   fChain->SetBranchAddress("Bd_ConstJpsi_M", &Bd_ConstJpsi_M, &b_Bd_ConstJpsi_M);
   fChain->SetBranchAddress("Bd_ConstJpsi_MERR", &Bd_ConstJpsi_MERR, &b_Bd_ConstJpsi_MERR);
   fChain->SetBranchAddress("Bd_OnlyPV_M", &Bd_OnlyPV_M, &b_Bd_OnlyPV_M);
   fChain->SetBranchAddress("Bd_OnlyPV_MERR", &Bd_OnlyPV_MERR, &b_Bd_OnlyPV_MERR);
   fChain->SetBranchAddress("Bd_OnlyPV_tau", &Bd_OnlyPV_tau, &b_Bd_OnlyPV_tau);
   fChain->SetBranchAddress("Bd_OnlyPV_tauErr", &Bd_OnlyPV_tauErr, &b_Bd_OnlyPV_tauErr);
   fChain->SetBranchAddress("Bd_ConstJpsi_CHI2NDOF", &Bd_ConstJpsi_CHI2NDOF, &b_Bd_ConstJpsi_CHI2NDOF);
   fChain->SetBranchAddress("Bd_OnlyPV_CHI2NDOF", &Bd_OnlyPV_CHI2NDOF, &b_Bd_OnlyPV_CHI2NDOF);
   fChain->SetBranchAddress("Bd_IP_OWNPV", &Bd_IP_OWNPV, &b_Bd_IP_OWNPV);
   fChain->SetBranchAddress("Bd_IPCHI2_OWNPV", &Bd_IPCHI2_OWNPV, &b_Bd_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Bd_FD_OWNPV", &Bd_FD_OWNPV, &b_Bd_FD_OWNPV);
   fChain->SetBranchAddress("Bd_FDCHI2_OWNPV", &Bd_FDCHI2_OWNPV, &b_Bd_FDCHI2_OWNPV);
   fChain->SetBranchAddress("Bd_DIRA_OWNPV", &Bd_DIRA_OWNPV, &b_Bd_DIRA_OWNPV);
   fChain->SetBranchAddress("Bd_TAU", &Bd_TAU, &b_Bd_TAU);
   fChain->SetBranchAddress("Bd_TAUERR", &Bd_TAUERR, &b_Bd_TAUERR);
   fChain->SetBranchAddress("Bd_L0Global_Dec", &Bd_L0Global_Dec, &b_Bd_L0Global_Dec);
   fChain->SetBranchAddress("Bd_L0MuonDecision_TOS", &Bd_L0MuonDecision_TOS, &b_Bd_L0MuonDecision_TOS);
   fChain->SetBranchAddress("Bd_L0DiMuonDecision_TOS", &Bd_L0DiMuonDecision_TOS, &b_Bd_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("Bd_Hlt1TrackMuonMVADecision_TOS", &Bd_Hlt1TrackMuonMVADecision_TOS, &b_Bd_Hlt1TrackMuonMVADecision_TOS);
   fChain->SetBranchAddress("Bd_Hlt1TwoTrackMVADecision_TOS", &Bd_Hlt1TwoTrackMVADecision_TOS, &b_Bd_Hlt1TwoTrackMVADecision_TOS);
   fChain->SetBranchAddress("Bd_Hlt1DiMuonHighMassDecision_TOS", &Bd_Hlt1DiMuonHighMassDecision_TOS, &b_Bd_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt1TrackMuonDecision_TOS", &Jpsi_Hlt1TrackMuonDecision_TOS, &b_Jpsi_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt1DiMuonHighMassDecision_TOS", &Jpsi_Hlt1DiMuonHighMassDecision_TOS, &b_Jpsi_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS", &Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS, &b_Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS);
   fChain->SetBranchAddress("hlt1b", &hlt1b, &b_hlt1b);
   fChain->SetBranchAddress("Bd_ENDVERTEX_X", &Bd_ENDVERTEX_X, &b_Bd_ENDVERTEX_X);
   fChain->SetBranchAddress("Bd_ENDVERTEX_Y", &Bd_ENDVERTEX_Y, &b_Bd_ENDVERTEX_Y);
   fChain->SetBranchAddress("Bd_ENDVERTEX_Z", &Bd_ENDVERTEX_Z, &b_Bd_ENDVERTEX_Z);
   fChain->SetBranchAddress("Bd_ENDVERTEX_CHI2NDOF", &Bd_ENDVERTEX_CHI2NDOF, &b_Bd_ENDVERTEX_CHI2NDOF);
   fChain->SetBranchAddress("Bd_OWNPV_X", &Bd_OWNPV_X, &b_Bd_OWNPV_X);
   fChain->SetBranchAddress("Bd_OWNPV_Y", &Bd_OWNPV_Y, &b_Bd_OWNPV_Y);
   fChain->SetBranchAddress("Bd_OWNPV_Z", &Bd_OWNPV_Z, &b_Bd_OWNPV_Z);
   fChain->SetBranchAddress("Bd_OWNPV_CHI2NDOF", &Bd_OWNPV_CHI2NDOF, &b_Bd_OWNPV_CHI2NDOF);
   fChain->SetBranchAddress("Bd_MINIPCHI2NEXTBEST", &Bd_MINIPCHI2NEXTBEST, &b_Bd_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("Bd_MINIPCHI2", &Bd_MINIPCHI2, &b_Bd_MINIPCHI2);
   fChain->SetBranchAddress("Bd_MINIP", &Bd_MINIP, &b_Bd_MINIP);
   fChain->SetBranchAddress("Bd_DTF_NoPV_CHI2NDOF", &Bd_DTF_NoPV_CHI2NDOF, &b_Bd_DTF_NoPV_CHI2NDOF);
   fChain->SetBranchAddress("Jpsi_MM", &Jpsi_MM, &b_Jpsi_MM);
   fChain->SetBranchAddress("Jpsi_ConstJpsiNoPV_M", &Jpsi_ConstJpsiNoPV_M, &b_Jpsi_ConstJpsiNoPV_M);
   fChain->SetBranchAddress("Jpsi_OnlyPV_M", &Jpsi_OnlyPV_M, &b_Jpsi_OnlyPV_M);
   fChain->SetBranchAddress("Jpsi_ENDVERTEX_CHI2", &Jpsi_ENDVERTEX_CHI2, &b_Jpsi_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("Jpsi_ENDVERTEX_NDOF", &Jpsi_ENDVERTEX_NDOF, &b_Jpsi_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("Jpsi_ENDVERTEX_CHI2NDOF", &Jpsi_ENDVERTEX_CHI2NDOF, &b_Jpsi_ENDVERTEX_CHI2NDOF);
   fChain->SetBranchAddress("Bd_ETA", &Bd_ETA, &b_Bd_ETA);
   fChain->SetBranchAddress("Bd_PX", &Bd_PX, &b_Bd_PX);
   fChain->SetBranchAddress("Bd_PY", &Bd_PY, &b_Bd_PY);
   fChain->SetBranchAddress("Bd_PZ", &Bd_PZ, &b_Bd_PZ);
   fChain->SetBranchAddress("Bd_PT", &Bd_PT, &b_Bd_PT);
   fChain->SetBranchAddress("Bd_PE", &Bd_PE, &b_Bd_PE);
   fChain->SetBranchAddress("Bd_P", &Bd_P, &b_Bd_P);
   fChain->SetBranchAddress("Bd_M", &Bd_M, &b_Bd_M);
   fChain->SetBranchAddress("Bd_ID", &Bd_ID, &b_Bd_ID);
   fChain->SetBranchAddress("muplus_TRACK_CHI2NDOF", &muplus_TRACK_CHI2NDOF, &b_muplus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("muplus_PT", &muplus_PT, &b_muplus_PT);
   fChain->SetBranchAddress("muplus_P", &muplus_P, &b_muplus_P);
   fChain->SetBranchAddress("muplus_PIDmu", &muplus_PIDmu, &b_muplus_PIDmu);
   fChain->SetBranchAddress("muminus_TRACK_CHI2NDOF", &muminus_TRACK_CHI2NDOF, &b_muminus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("muminus_PT", &muminus_PT, &b_muminus_PT);
   fChain->SetBranchAddress("muminus_P", &muminus_P, &b_muminus_P);
   fChain->SetBranchAddress("muminus_PIDmu", &muminus_PIDmu, &b_muminus_PIDmu);
   fChain->SetBranchAddress("muplus_TRACK_GhostProb", &muplus_TRACK_GhostProb, &b_muplus_TRACK_GhostProb);
   fChain->SetBranchAddress("muminus_TRACK_GhostProb", &muminus_TRACK_GhostProb, &b_muminus_TRACK_GhostProb);
   fChain->SetBranchAddress("muplus_TRACK_MatchCHI2", &muplus_TRACK_MatchCHI2, &b_muplus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("muminus_TRACK_MatchCHI2", &muminus_TRACK_MatchCHI2, &b_muminus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("muplus_IPCHI2_OWNPV", &muplus_IPCHI2_OWNPV, &b_muplus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("muminus_IPCHI2_OWNPV", &muminus_IPCHI2_OWNPV, &b_muminus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("muplus_IP_OWNPV", &muplus_IP_OWNPV, &b_muplus_IP_OWNPV);
   fChain->SetBranchAddress("muminus_IP_OWNPV", &muminus_IP_OWNPV, &b_muminus_IP_OWNPV);
   fChain->SetBranchAddress("muplus_MINIP", &muplus_MINIP, &b_muplus_MINIP);
   fChain->SetBranchAddress("muminus_MINIP", &muminus_MINIP, &b_muminus_MINIP);
   fChain->SetBranchAddress("muplus_MINIPCHI2", &muplus_MINIPCHI2, &b_muplus_MINIPCHI2);
   fChain->SetBranchAddress("muminus_MINIPCHI2", &muminus_MINIPCHI2, &b_muminus_MINIPCHI2);
   fChain->SetBranchAddress("muplus_PE", &muplus_PE, &b_muplus_PE);
   fChain->SetBranchAddress("muplus_PX", &muplus_PX, &b_muplus_PX);
   fChain->SetBranchAddress("muplus_PY", &muplus_PY, &b_muplus_PY);
   fChain->SetBranchAddress("muplus_PZ", &muplus_PZ, &b_muplus_PZ);
   fChain->SetBranchAddress("muminus_PE", &muminus_PE, &b_muminus_PE);
   fChain->SetBranchAddress("muminus_PX", &muminus_PX, &b_muminus_PX);
   fChain->SetBranchAddress("muminus_PY", &muminus_PY, &b_muminus_PY);
   fChain->SetBranchAddress("muminus_PZ", &muminus_PZ, &b_muminus_PZ);
   fChain->SetBranchAddress("Jpsi_ConstJpsi_M", &Jpsi_ConstJpsi_M, &b_Jpsi_ConstJpsi_M);
   fChain->SetBranchAddress("piminus_IPCHI2_OWNPV", &piminus_IPCHI2_OWNPV, &b_piminus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("piminus_PE", &piminus_PE, &b_piminus_PE);
   fChain->SetBranchAddress("piminus_PX", &piminus_PX, &b_piminus_PX);
   fChain->SetBranchAddress("piminus_PY", &piminus_PY, &b_piminus_PY);
   fChain->SetBranchAddress("piminus_PZ", &piminus_PZ, &b_piminus_PZ);
   fChain->SetBranchAddress("piminus_TRACK_CHI2NDOF", &piminus_TRACK_CHI2NDOF, &b_piminus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("piminus_PT", &piminus_PT, &b_piminus_PT);
   fChain->SetBranchAddress("piminus_P", &piminus_P, &b_piminus_P);
   fChain->SetBranchAddress("piminus_isMuon", &piminus_isMuon, &b_piminus_isMuon);
   fChain->SetBranchAddress("piminus_PIDK", &piminus_PIDK, &b_piminus_PIDK);
   fChain->SetBranchAddress("piminus_TRACK_GhostProb", &piminus_TRACK_GhostProb, &b_piminus_TRACK_GhostProb);
   fChain->SetBranchAddress("piminus_TRACK_MatchCHI2", &piminus_TRACK_MatchCHI2, &b_piminus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("piminus_MINIPCHI2", &piminus_MINIPCHI2, &b_piminus_MINIPCHI2);
   fChain->SetBranchAddress("piminus_MINIP", &piminus_MINIP, &b_piminus_MINIP);
   fChain->SetBranchAddress("Bd_D0ToKshort_tau", &Bd_D0ToKshort_tau, &b_Bd_D0ToKshort_tau);
   fChain->SetBranchAddress("Bd_D0ToKshort_tauErr", &Bd_D0ToKshort_tauErr, &b_Bd_D0ToKshort_tauErr);
   fChain->SetBranchAddress("Bd_D0ToKshort_M", &Bd_D0ToKshort_M, &b_Bd_D0ToKshort_M);
   fChain->SetBranchAddress("Bd_D0ToKshort_MERR", &Bd_D0ToKshort_MERR, &b_Bd_D0ToKshort_MERR);
   fChain->SetBranchAddress("Bd_D0ToKshort_P", &Bd_D0ToKshort_P, &b_Bd_D0ToKshort_P);
   fChain->SetBranchAddress("Bd_D0ToKshort_PERR", &Bd_D0ToKshort_PERR, &b_Bd_D0ToKshort_PERR);
   fChain->SetBranchAddress("Bd_D0ToKshort_decayLength", &Bd_D0ToKshort_decayLength, &b_Bd_D0ToKshort_decayLength);
   fChain->SetBranchAddress("Bd_D0ToKshort_decayLengthErr", &Bd_D0ToKshort_decayLengthErr, &b_Bd_D0ToKshort_decayLengthErr);
   fChain->SetBranchAddress("Bd_D0ToKshort_chi2", &Bd_D0ToKshort_chi2, &b_Bd_D0ToKshort_chi2);
   fChain->SetBranchAddress("Bd_D0ToKshort_nDOF", &Bd_D0ToKshort_nDOF, &b_Bd_D0ToKshort_nDOF);
   fChain->SetBranchAddress("Bd_D0ToKshort_chi2ndof", &Bd_D0ToKshort_chi2ndof, &b_Bd_D0ToKshort_chi2ndof);
   fChain->SetBranchAddress("Bd_D0ToKshort_status", &Bd_D0ToKshort_status, &b_Bd_D0ToKshort_status);
   fChain->SetBranchAddress("Kshort_D0ToKshort_M", &Kshort_D0ToKshort_M, &b_Kshort_D0ToKshort_M);
   fChain->SetBranchAddress("Kshort_D0ToKshort_MERR", &Kshort_D0ToKshort_MERR, &b_Kshort_D0ToKshort_MERR);
   fChain->SetBranchAddress("Kshort_D0ToKshort_P", &Kshort_D0ToKshort_P, &b_Kshort_D0ToKshort_P);
   fChain->SetBranchAddress("Kshort_D0ToKshort_PERR", &Kshort_D0ToKshort_PERR, &b_Kshort_D0ToKshort_PERR);
   fChain->SetBranchAddress("Kshort_D0ToKshort_decayLength", &Kshort_D0ToKshort_decayLength, &b_Kshort_D0ToKshort_decayLength);
   fChain->SetBranchAddress("Kshort_D0ToKshort_decayLengthErr", &Kshort_D0ToKshort_decayLengthErr, &b_Kshort_D0ToKshort_decayLengthErr);
   fChain->SetBranchAddress("Kshort_OnlyPV_M", &Kshort_OnlyPV_M, &b_Kshort_OnlyPV_M);
   fChain->SetBranchAddress("Kshort_OnlyPV_MERR", &Kshort_OnlyPV_MERR, &b_Kshort_OnlyPV_MERR);
   fChain->SetBranchAddress("Kshort_ConstJpsi_M", &Kshort_ConstJpsi_M, &b_Kshort_ConstJpsi_M);
   fChain->SetBranchAddress("Kshort_ConstJpsi_MERR", &Kshort_ConstJpsi_MERR, &b_Kshort_ConstJpsi_MERR);
   fChain->SetBranchAddress("Kshort_P", &Kshort_P, &b_Kshort_P);
   fChain->SetBranchAddress("Kshort_PT", &Kshort_PT, &b_Kshort_PT);
   fChain->SetBranchAddress("Kshort_PX", &Kshort_PX, &b_Kshort_PX);
   fChain->SetBranchAddress("Kshort_PY", &Kshort_PY, &b_Kshort_PY);
   fChain->SetBranchAddress("Kshort_PZ", &Kshort_PZ, &b_Kshort_PZ);
   fChain->SetBranchAddress("Kshort_ETA", &Kshort_ETA, &b_Kshort_ETA);
   fChain->SetBranchAddress("Kshort_DOCA_12", &Kshort_DOCA_12, &b_Kshort_DOCA_12);
   fChain->SetBranchAddress("Kshort_DOCA_12_CHI2", &Kshort_DOCA_12_CHI2, &b_Kshort_DOCA_12_CHI2);
   fChain->SetBranchAddress("Kshort_FDS", &Kshort_FDS, &b_Kshort_FDS);
   fChain->SetBranchAddress("Kshort_IPCHI2_OWNPV", &Kshort_IPCHI2_OWNPV, &b_Kshort_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Kshort_FDCHI2_OWNPV", &Kshort_FDCHI2_OWNPV, &b_Kshort_FDCHI2_OWNPV);
   fChain->SetBranchAddress("Kshort_FD_OWNPV", &Kshort_FD_OWNPV, &b_Kshort_FD_OWNPV);
   fChain->SetBranchAddress("Kshort_DIRA_OWNPV", &Kshort_DIRA_OWNPV, &b_Kshort_DIRA_OWNPV);
   fChain->SetBranchAddress("Kshort_OWNPV_CHI2NDOF", &Kshort_OWNPV_CHI2NDOF, &b_Kshort_OWNPV_CHI2NDOF);
   fChain->SetBranchAddress("Kshort_OWNPV_X", &Kshort_OWNPV_X, &b_Kshort_OWNPV_X);
   fChain->SetBranchAddress("Kshort_OWNPV_Y", &Kshort_OWNPV_Y, &b_Kshort_OWNPV_Y);
   fChain->SetBranchAddress("Kshort_OWNPV_Z", &Kshort_OWNPV_Z, &b_Kshort_OWNPV_Z);
   fChain->SetBranchAddress("Kshort_ENDVERTEX_X", &Kshort_ENDVERTEX_X, &b_Kshort_ENDVERTEX_X);
   fChain->SetBranchAddress("Kshort_ENDVERTEX_Y", &Kshort_ENDVERTEX_Y, &b_Kshort_ENDVERTEX_Y);
   fChain->SetBranchAddress("Kshort_ENDVERTEX_Z", &Kshort_ENDVERTEX_Z, &b_Kshort_ENDVERTEX_Z);
   fChain->SetBranchAddress("Kshort_ENDVERTEX_CHI2NDOF", &Kshort_ENDVERTEX_CHI2NDOF, &b_Kshort_ENDVERTEX_CHI2NDOF);
   fChain->SetBranchAddress("piplus_IPCHI2_OWNPV", &piplus_IPCHI2_OWNPV, &b_piplus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("piplus_MINIPCHI2", &piplus_MINIPCHI2, &b_piplus_MINIPCHI2);
   fChain->SetBranchAddress("piplus_MINIP", &piplus_MINIP, &b_piplus_MINIP);
   fChain->SetBranchAddress("piplus_PE", &piplus_PE, &b_piplus_PE);
   fChain->SetBranchAddress("piplus_PX", &piplus_PX, &b_piplus_PX);
   fChain->SetBranchAddress("piplus_PY", &piplus_PY, &b_piplus_PY);
   fChain->SetBranchAddress("piplus_PZ", &piplus_PZ, &b_piplus_PZ);
   fChain->SetBranchAddress("piplus_TRACK_CHI2NDOF", &piplus_TRACK_CHI2NDOF, &b_piplus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("piplus_PT", &piplus_PT, &b_piplus_PT);
   fChain->SetBranchAddress("piplus_P", &piplus_P, &b_piplus_P);
   fChain->SetBranchAddress("piplus_isMuon", &piplus_isMuon, &b_piplus_isMuon);
   fChain->SetBranchAddress("piplus_PIDK", &piplus_PIDK, &b_piplus_PIDK);
   fChain->SetBranchAddress("piplus_TRACK_GhostProb", &piplus_TRACK_GhostProb, &b_piplus_TRACK_GhostProb);
   fChain->SetBranchAddress("piplus_TRACK_MatchCHI2", &piplus_TRACK_MatchCHI2, &b_piplus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("min_mu_PIDmu", &min_mu_PIDmu, &b_min_mu_PIDmu);
   fChain->SetBranchAddress("log_Bd_IPCHI2_OWNPV", &log_Bd_IPCHI2_OWNPV, &b_log_Bd_IPCHI2_OWNPV);
   fChain->SetBranchAddress("log_Bd_ENDVERTEX_CHI2NDOF", &log_Bd_ENDVERTEX_CHI2NDOF, &b_log_Bd_ENDVERTEX_CHI2NDOF);
   fChain->SetBranchAddress("trigb", &trigb, &b_trigb);
   fChain->SetBranchAddress("trigj", &trigj, &b_trigj);
   fChain->SetBranchAddress("log_Bd_DTF_NoPV_CHI2NDOF", &log_Bd_DTF_NoPV_CHI2NDOF, &b_log_Bd_DTF_NoPV_CHI2NDOF);
   fChain->SetBranchAddress("log_Bd_OnlyPV_CHI2NDOF", &log_Bd_OnlyPV_CHI2NDOF, &b_log_Bd_OnlyPV_CHI2NDOF);
   fChain->SetBranchAddress("min_mu_ProbNNmu_corr", &min_mu_ProbNNmu_corr, &b_min_mu_ProbNNmu_corr);
   fChain->SetBranchAddress("gbw", &gbw, &b_gbw);
   fChain->SetBranchAddress("rndNumber", &rndNumber, &b_rndNumber);
   fChain->SetBranchAddress("BDT", &BDT, &b_BDT);
   Notify();
}

bool massfit::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return true;
}

void massfit::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t massfit::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef massfit_cxx
