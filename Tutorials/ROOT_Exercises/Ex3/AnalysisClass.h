//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 30 00:54:42 2018 by ROOT version 5.34/30
// from TTree OneLeptonMu/test
// found on file: ntuple_WHln125_teste.root
//////////////////////////////////////////////////////////

#ifndef AnalysisClass_h
#define AnalysisClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class AnalysisClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         pTB1;
   Float_t         etaB1;
   Float_t         phiB1;
   Float_t         eB1;
   Float_t         pTB2;
   Float_t         etaB2;
   Float_t         phiB2;
   Float_t         eB2;
   Float_t         pTB1_corr;
   Float_t         etaB1_corr;
   Float_t         phiB1_corr;
   Float_t         eB1_corr;
   Float_t         pTB2_corr;
   Float_t         etaB2_corr;
   Float_t         phiB2_corr;
   Float_t         eB2_corr;
   Float_t         MET;
   Float_t         METx;
   Float_t         METy;
   Float_t         MV2c20B1;
   Float_t         MV2c20B2;
   Float_t         MV2c20B3;
   Float_t         MV2c20B4;
   Float_t         pTV;
   Float_t         mTW;
   Float_t         mBB;
   Float_t         dRBB;
   Float_t         mBB_corr;
   Float_t         dRBB_corr;
   Float_t         dPhiVBB;
   Float_t         dPhiLBmin;
   Float_t         dPhiVBB_corr;
   Float_t         dPhiLBmin_corr;
   Float_t         pTL;
   Float_t         etaL;
   Float_t         phiL;
   Float_t         eL;
   Float_t         pZL;
   Float_t         ChargeL;
   Float_t         pZChargeL;
   Float_t         MtopNoMETShift;
   Float_t         MtopNoMETShift_corr;
   Float_t         MtopSemiMETShift;
   Float_t         MtopSemiMETShift_corr;
   Float_t         MtopFullMETShift;
   Float_t         MtopFullMETShift_corr;
   Float_t         likelihood_ttbar;
   Float_t         mBBJ;
   Float_t         mBBB;
   Float_t         mBJB;
   Float_t         mJBB;
   Float_t         mBBJ_corr;
   Float_t         mBBB_corr;
   Float_t         mBJB_corr;
   Float_t         mJBB_corr;
   Float_t         pTJ3;
   Float_t         etaJ3;
   Float_t         phiJ3;
   Float_t         eJ3;
   Float_t         pTB3;
   Float_t         etaB3;
   Float_t         phiB3;
   Float_t         eB3;
   Float_t         weight;
   Float_t         weight_ptag;
   Int_t           Njets;
   Int_t           Nbtagged;
   Int_t           Nsignaljets;
   Int_t           Nforwardjets;
   Int_t           channelNumber;
   Float_t         lepton_trkIso;
   Float_t         lepton_caloIso;
   Float_t         lepton_flavor;
   Int_t           EventNumber;
   Float_t         btag2TagWeight_MV1c80;
   Float_t         btagSFWeight_MV1c80;
   Float_t         eventWeight;
   Float_t         dPhiBB;
   Float_t         dPhiBB_corr;
   Float_t         averageTopPt;
   Float_t         pileupWeight;
   Float_t         dPhiLMET;
   Float_t         dPhiMETJmin;
   Int_t           flavJet1;
   Int_t           flavJet2;
   Int_t           flavJet3;
   Int_t           isMC;
   Char_t          samplename[8];

   // List of branches
   TBranch        *b_pTB1;   //!
   TBranch        *b_etaB1;   //!
   TBranch        *b_phiB1;   //!
   TBranch        *b_eB1;   //!
   TBranch        *b_pTB2;   //!
   TBranch        *b_etaB2;   //!
   TBranch        *b_phiB2;   //!
   TBranch        *b_eB2;   //!
   TBranch        *b_pTB1_corr;   //!
   TBranch        *b_etaB1_corr;   //!
   TBranch        *b_phiB1_corr;   //!
   TBranch        *b_eB1_corr;   //!
   TBranch        *b_pTB2_corr;   //!
   TBranch        *b_etaB2_corr;   //!
   TBranch        *b_phiB2_corr;   //!
   TBranch        *b_eB2_corr;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METx;   //!
   TBranch        *b_METy;   //!
   TBranch        *b_MV2c20B1;   //!
   TBranch        *b_MV2c20B2;   //!
   TBranch        *b_MV2c20B3;   //!
   TBranch        *b_MV2c20B4;   //!
   TBranch        *b_pTV;   //!
   TBranch        *b_mTW;   //!
   TBranch        *b_mBB;   //!
   TBranch        *b_dRBB;   //!
   TBranch        *b_mBB_corr;   //!
   TBranch        *b_dRBB_corr;   //!
   TBranch        *b_dPhiVBB;   //!
   TBranch        *b_dPhiLBmin;   //!
   TBranch        *b_dPhiVBB_corr;   //!
   TBranch        *b_dPhiLBmin_corr;   //!
   TBranch        *b_pTL;   //!
   TBranch        *b_etaL;   //!
   TBranch        *b_phiL;   //!
   TBranch        *b_eL;   //!
   TBranch        *b_pZL;   //!
   TBranch        *b_ChargeL;   //!
   TBranch        *b_pZChargeL;   //!
   TBranch        *b_MtopNoMETShift;   //!
   TBranch        *b_MtopNoMETShift_corr;   //!
   TBranch        *b_MtopSemiMETShift;   //!
   TBranch        *b_MtopSemiMETShift_corr;   //!
   TBranch        *b_MtopFullMETShift;   //!
   TBranch        *b_MtopFullMETShift_corr;   //!
   TBranch        *b_likelihood_ttbar;   //!
   TBranch        *b_mBBJ;   //!
   TBranch        *b_mBBB;   //!
   TBranch        *b_mBJB;   //!
   TBranch        *b_mJBB;   //!
   TBranch        *b_mBBJ_corr;   //!
   TBranch        *b_mBBB_corr;   //!
   TBranch        *b_mBJB_corr;   //!
   TBranch        *b_mJBB_corr;   //!
   TBranch        *b_pTJ3;   //!
   TBranch        *b_etaJ3;   //!
   TBranch        *b_phiJ3;   //!
   TBranch        *b_eJ3;   //!
   TBranch        *b_pTB3;   //!
   TBranch        *b_etaB3;   //!
   TBranch        *b_phiB3;   //!
   TBranch        *b_eB3;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_weight_ptag;   //!
   TBranch        *b_Njets;   //!
   TBranch        *b_Nbtagged;   //!
   TBranch        *b_Nsignaljets;   //!
   TBranch        *b_Nforwardjets;   //!
   TBranch        *b_channelNumber;   //!
   TBranch        *b_lepton_trkIso;   //!
   TBranch        *b_lepton_caloIso;   //!
   TBranch        *b_lepton_flavor;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_btag2TagWeight_MV1c80;   //!
   TBranch        *b_btagSFWeight_MV1c80;   //!
   TBranch        *b_eventWeight;   //!
   TBranch        *b_dPhiBB;   //!
   TBranch        *b_dPhiBB_corr;   //!
   TBranch        *b_averageTopPt;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_dPhiLMET;   //!
   TBranch        *b_dPhiMETJmin;   //!
   TBranch        *b_flavJet1;   //!
   TBranch        *b_flavJet2;   //!
   TBranch        *b_flavJet3;   //!
   TBranch        *b_isMC;   //!
   TBranch        *b_samplename;   //!

   AnalysisClass(TTree *tree=0);
   virtual ~AnalysisClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef AnalysisClass_cxx
AnalysisClass::AnalysisClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ntuple_WHln125_teste.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ntuple_WHln125_teste.root");
      }
      f->GetObject("OneLeptonMu",tree);

   }
   Init(tree);
}

AnalysisClass::~AnalysisClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnalysisClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnalysisClass::LoadTree(Long64_t entry)
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

void AnalysisClass::Init(TTree *tree)
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

   fChain->SetBranchAddress("pTB1", &pTB1, &b_pTB1);
   fChain->SetBranchAddress("etaB1", &etaB1, &b_etaB1);
   fChain->SetBranchAddress("phiB1", &phiB1, &b_phiB1);
   fChain->SetBranchAddress("eB1", &eB1, &b_eB1);
   fChain->SetBranchAddress("pTB2", &pTB2, &b_pTB2);
   fChain->SetBranchAddress("etaB2", &etaB2, &b_etaB2);
   fChain->SetBranchAddress("phiB2", &phiB2, &b_phiB2);
   fChain->SetBranchAddress("eB2", &eB2, &b_eB2);
   fChain->SetBranchAddress("pTB1_corr", &pTB1_corr, &b_pTB1_corr);
   fChain->SetBranchAddress("etaB1_corr", &etaB1_corr, &b_etaB1_corr);
   fChain->SetBranchAddress("phiB1_corr", &phiB1_corr, &b_phiB1_corr);
   fChain->SetBranchAddress("eB1_corr", &eB1_corr, &b_eB1_corr);
   fChain->SetBranchAddress("pTB2_corr", &pTB2_corr, &b_pTB2_corr);
   fChain->SetBranchAddress("etaB2_corr", &etaB2_corr, &b_etaB2_corr);
   fChain->SetBranchAddress("phiB2_corr", &phiB2_corr, &b_phiB2_corr);
   fChain->SetBranchAddress("eB2_corr", &eB2_corr, &b_eB2_corr);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METx", &METx, &b_METx);
   fChain->SetBranchAddress("METy", &METy, &b_METy);
   fChain->SetBranchAddress("MV2c20B1", &MV2c20B1, &b_MV2c20B1);
   fChain->SetBranchAddress("MV2c20B2", &MV2c20B2, &b_MV2c20B2);
   fChain->SetBranchAddress("MV2c20B3", &MV2c20B3, &b_MV2c20B3);
   fChain->SetBranchAddress("MV2c20B4", &MV2c20B4, &b_MV2c20B4);
   fChain->SetBranchAddress("pTV", &pTV, &b_pTV);
   fChain->SetBranchAddress("mTW", &mTW, &b_mTW);
   fChain->SetBranchAddress("mBB", &mBB, &b_mBB);
   fChain->SetBranchAddress("dRBB", &dRBB, &b_dRBB);
   fChain->SetBranchAddress("mBB_corr", &mBB_corr, &b_mBB_corr);
   fChain->SetBranchAddress("dRBB_corr", &dRBB_corr, &b_dRBB_corr);
   fChain->SetBranchAddress("dPhiVBB", &dPhiVBB, &b_dPhiVBB);
   fChain->SetBranchAddress("dPhiLBmin", &dPhiLBmin, &b_dPhiLBmin);
   fChain->SetBranchAddress("dPhiVBB_corr", &dPhiVBB_corr, &b_dPhiVBB_corr);
   fChain->SetBranchAddress("dPhiLBmin_corr", &dPhiLBmin_corr, &b_dPhiLBmin_corr);
   fChain->SetBranchAddress("pTL", &pTL, &b_pTL);
   fChain->SetBranchAddress("etaL", &etaL, &b_etaL);
   fChain->SetBranchAddress("phiL", &phiL, &b_phiL);
   fChain->SetBranchAddress("eL", &eL, &b_eL);
   fChain->SetBranchAddress("pZL", &pZL, &b_pZL);
   fChain->SetBranchAddress("ChargeL", &ChargeL, &b_ChargeL);
   fChain->SetBranchAddress("pZChargeL", &pZChargeL, &b_pZChargeL);
   fChain->SetBranchAddress("MtopNoMETShift", &MtopNoMETShift, &b_MtopNoMETShift);
   fChain->SetBranchAddress("MtopNoMETShift_corr", &MtopNoMETShift_corr, &b_MtopNoMETShift_corr);
   fChain->SetBranchAddress("MtopSemiMETShift", &MtopSemiMETShift, &b_MtopSemiMETShift);
   fChain->SetBranchAddress("MtopSemiMETShift_corr", &MtopSemiMETShift_corr, &b_MtopSemiMETShift_corr);
   fChain->SetBranchAddress("MtopFullMETShift", &MtopFullMETShift, &b_MtopFullMETShift);
   fChain->SetBranchAddress("MtopFullMETShift_corr", &MtopFullMETShift_corr, &b_MtopFullMETShift_corr);
   fChain->SetBranchAddress("likelihood_ttbar", &likelihood_ttbar, &b_likelihood_ttbar);
   fChain->SetBranchAddress("mBBJ", &mBBJ, &b_mBBJ);
   fChain->SetBranchAddress("mBBB", &mBBB, &b_mBBB);
   fChain->SetBranchAddress("mBJB", &mBJB, &b_mBJB);
   fChain->SetBranchAddress("mJBB", &mJBB, &b_mJBB);
   fChain->SetBranchAddress("mBBJ_corr", &mBBJ_corr, &b_mBBJ_corr);
   fChain->SetBranchAddress("mBBB_corr", &mBBB_corr, &b_mBBB_corr);
   fChain->SetBranchAddress("mBJB_corr", &mBJB_corr, &b_mBJB_corr);
   fChain->SetBranchAddress("mJBB_corr", &mJBB_corr, &b_mJBB_corr);
   fChain->SetBranchAddress("pTJ3", &pTJ3, &b_pTJ3);
   fChain->SetBranchAddress("etaJ3", &etaJ3, &b_etaJ3);
   fChain->SetBranchAddress("phiJ3", &phiJ3, &b_phiJ3);
   fChain->SetBranchAddress("eJ3", &eJ3, &b_eJ3);
   fChain->SetBranchAddress("pTB3", &pTB3, &b_pTB3);
   fChain->SetBranchAddress("etaB3", &etaB3, &b_etaB3);
   fChain->SetBranchAddress("phiB3", &phiB3, &b_phiB3);
   fChain->SetBranchAddress("eB3", &eB3, &b_eB3);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("weight_ptag", &weight_ptag, &b_weight_ptag);
   fChain->SetBranchAddress("Njets", &Njets, &b_Njets);
   fChain->SetBranchAddress("Nbtagged", &Nbtagged, &b_Nbtagged);
   fChain->SetBranchAddress("Nsignaljets", &Nsignaljets, &b_Nsignaljets);
   fChain->SetBranchAddress("Nforwardjets", &Nforwardjets, &b_Nforwardjets);
   fChain->SetBranchAddress("channelNumber", &channelNumber, &b_channelNumber);
   fChain->SetBranchAddress("lepton_trkIso", &lepton_trkIso, &b_lepton_trkIso);
   fChain->SetBranchAddress("lepton_caloIso", &lepton_caloIso, &b_lepton_caloIso);
   fChain->SetBranchAddress("lepton_flavor", &lepton_flavor, &b_lepton_flavor);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("btag2TagWeight_MV1c80", &btag2TagWeight_MV1c80, &b_btag2TagWeight_MV1c80);
   fChain->SetBranchAddress("btagSFWeight_MV1c80", &btagSFWeight_MV1c80, &b_btagSFWeight_MV1c80);
   fChain->SetBranchAddress("eventWeight", &eventWeight, &b_eventWeight);
   fChain->SetBranchAddress("dPhiBB", &dPhiBB, &b_dPhiBB);
   fChain->SetBranchAddress("dPhiBB_corr", &dPhiBB_corr, &b_dPhiBB_corr);
   fChain->SetBranchAddress("averageTopPt", &averageTopPt, &b_averageTopPt);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("dPhiLMET", &dPhiLMET, &b_dPhiLMET);
   fChain->SetBranchAddress("dPhiMETJmin", &dPhiMETJmin, &b_dPhiMETJmin);
   fChain->SetBranchAddress("flavJet1", &flavJet1, &b_flavJet1);
   fChain->SetBranchAddress("flavJet2", &flavJet2, &b_flavJet2);
   fChain->SetBranchAddress("flavJet3", &flavJet3, &b_flavJet3);
   fChain->SetBranchAddress("isMC", &isMC, &b_isMC);
   fChain->SetBranchAddress("samplename", samplename, &b_samplename);
   Notify();
}

Bool_t AnalysisClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnalysisClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AnalysisClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef AnalysisClass_cxx
