//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr  2 13:51:49 2025 by ROOT version 6.26/10
// from TTree Events/Events
// found on file: skimFile_1.root (NanoAODv12)
//////////////////////////////////////////////////////////

#ifndef AnaScript_h
#define AnaScript_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include "TLorentzVector.h"
#include <fstream>
#include <iostream>
#include "TString.h"
#include <bitset>
#include <time.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

class AnaScript : public TSelector {
private:

  //For NanoAODv12+ (example: Run3Summer22 MC)
  using iterator     = Int_t;
  using int_or_char  = UChar_t;
  using int_or_short = Short_t;
  using int_or_ushort = UShort_t;
  /*  
  //For NanoAODv11-
  using iterator     = UInt_t; 
  using int_or_char  = Int_t;
  using int_or_short = Int_t;
  using int_or_ushort = Int_t;
  */

public :
  TTreeReader     fReader;
  TTreeReader     fReader_MC;
  TTreeReader     fReader_nonQCD;
  TTree          *fChain = 0;

  //------------------------------- EXCEPTIONS -------------------------------------
  
  // HLT paths that I am interested in:
  //For 2016:
  //TTreeReaderValue<Bool_t> HLT_SingleMuon = {fReader, "HLT_IsoMu24"};
  //TTreeReaderValue<Bool_t> HLT_SingleEle  = {fReader, "HLT_Ele27_WPTight_Gsf"};
  //For 2017:
  //TTreeReaderValue<Bool_t> HLT_SingleMuon  = {fReader, "HLT_IsoMu27"};
  //TTreeReaderValue<Bool_t> HLT_SingleEle   = {fReader, "HLT_Ele35_WPTight_Gsf"};
  //For 2018, 2022 and 2023:
  TTreeReaderValue<Bool_t> HLT_SingleMuon  = {fReader, "HLT_IsoMu24"};
  TTreeReaderValue<Bool_t> HLT_SingleEle   = {fReader, "HLT_Ele32_WPTight_Gsf"};

  // Jet correction variables:
    
  //Rho (Run-3)
  TTreeReaderValue<Float_t> rho = {fReader, "Rho_fixedGridRhoAll"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoAll = {fReader, "Rho_fixedGridRhoAll"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetAll = {fReader, "Rho_fixedGridRhoFastjetAll"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentral = {fReader, "Rho_fixedGridRhoFastjetCentral"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentralCalo = {fReader, "Rho_fixedGridRhoFastjetCentralCalo"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentralChargedPileUp = {fReader, "Rho_fixedGridRhoFastjetCentralChargedPileUp"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentralNeutral = {fReader, "Rho_fixedGridRhoFastjetCentralNeutral"};
  /*
  //Rho (Run-2)
  TTreeReaderValue<Float_t> rho =            {fReader, "fixedGridRhoFastjetAll"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetAll =            {fReader, "fixedGridRhoFastjetAll"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentral =        {fReader, "fixedGridRhoFastjetCentral"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentralCalo =    {fReader, "fixedGridRhoFastjetCentralCalo"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentralChargedPileUp = {fReader, "fixedGridRhoFastjetCentralChargedPileUp"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentralNeutral = {fReader, "fixedGridRhoFastjetCentralNeutral"};
  TTreeReaderValue<Float_t> rho = fixedGridRhoFastjetAll;*/
  
  //Non-QCD branches:
  TTreeReaderValue<Float_t>  LHEWeight_originalXWGTUP = {fReader_nonQCD, "LHEWeight_originalXWGTUP"};
  TTreeReaderValue<iterator> nLHEPdfWeight            = {fReader_nonQCD, "nLHEPdfWeight"};
  TTreeReaderArray<Float_t>  LHEPdfWeight             = {fReader_nonQCD, "LHEPdfWeight"};
  TTreeReaderValue<iterator> nLHEReweightingWeight    = {fReader_nonQCD, "nLHEReweightingWeight"};
  TTreeReaderArray<Float_t>  LHEReweightingWeight     = {fReader_nonQCD, "LHEReweightingWeight"};
  TTreeReaderValue<iterator> nLHEScaleWeight          = {fReader_nonQCD, "nLHEScaleWeight"};
  TTreeReaderArray<Float_t>  LHEScaleWeight           = {fReader_nonQCD, "LHEScaleWeight"};
  
  //--------------------------------------------------------------------------------

  //Read only the important branches:
  TTreeReaderValue<UInt_t> run = {fReader, "run"};
  TTreeReaderValue<UInt_t> luminosityBlock = {fReader, "luminosityBlock"};
  TTreeReaderValue<ULong64_t> event = {fReader, "event"};

  //Electrons:
  TTreeReaderValue<iterator> nElectron = {fReader, "nElectron"};
  TTreeReaderArray<int_or_char> Electron_cutBased = {fReader, "Electron_cutBased"};
  TTreeReaderArray<Bool_t> Electron_cutBased_HEEP = {fReader, "Electron_cutBased_HEEP"};
  TTreeReaderArray<UChar_t> Electron_lostHits = {fReader, "Electron_lostHits"};
  //TTreeReaderArray<Bool_t> Electron_mvaIso_WP80 = {fReader, "Electron_mvaIso_WP80"};
  //TTreeReaderArray<Bool_t> Electron_mvaIso_WP90 = {fReader, "Electron_mvaIso_WP90"};
  //TTreeReaderArray<Bool_t> Electron_mvaNoIso_WP80 = {fReader, "Electron_mvaNoIso_WP80"};
  //TTreeReaderArray<Bool_t> Electron_mvaNoIso_WP90 = {fReader, "Electron_mvaNoIso_WP90"};
  TTreeReaderArray<UChar_t> Electron_seedGain = {fReader, "Electron_seedGain"};
  TTreeReaderArray<Int_t> Electron_charge = {fReader, "Electron_charge"};
  TTreeReaderArray<Int_t> Electron_pdgId = {fReader, "Electron_pdgId"};
  TTreeReaderArray<Float_t> Electron_dxy = {fReader, "Electron_dxy"};
  TTreeReaderArray<Float_t> Electron_dxyErr = {fReader, "Electron_dxyErr"};
  TTreeReaderArray<Float_t> Electron_dz = {fReader, "Electron_dz"};
  TTreeReaderArray<Float_t> Electron_dzErr = {fReader, "Electron_dzErr"};
  TTreeReaderArray<Float_t> Electron_eta = {fReader, "Electron_eta"};
  TTreeReaderArray<Float_t> Electron_hoe = {fReader, "Electron_hoe"};
  TTreeReaderArray<Float_t> Electron_ip3d = {fReader, "Electron_ip3d"};
  TTreeReaderArray<Float_t> Electron_mass = {fReader, "Electron_mass"};
  TTreeReaderArray<Float_t> Electron_miniPFRelIso_all = {fReader, "Electron_miniPFRelIso_all"};
  TTreeReaderArray<Float_t> Electron_miniPFRelIso_chg = {fReader, "Electron_miniPFRelIso_chg"};;
  TTreeReaderArray<Float_t> Electron_pfRelIso03_all = {fReader, "Electron_pfRelIso03_all"};
  TTreeReaderArray<Float_t> Electron_pfRelIso03_chg = {fReader, "Electron_pfRelIso03_chg"};
  TTreeReaderArray<Float_t> Electron_phi = {fReader, "Electron_phi"};
  TTreeReaderArray<Float_t> Electron_pt = {fReader, "Electron_pt"};
  TTreeReaderArray<Float_t> Electron_r9 = {fReader, "Electron_r9"};
  TTreeReaderArray<Float_t> Electron_scEtOverPt = {fReader, "Electron_scEtOverPt"};
  TTreeReaderArray<Float_t> Electron_sieie = {fReader, "Electron_sieie"};
  TTreeReaderArray<Float_t> Electron_sip3d = {fReader, "Electron_sip3d"};
  TTreeReaderArray<int_or_short> Electron_jetIdx = {fReader, "Electron_jetIdx"};
  TTreeReaderArray<int_or_char> Electron_tightCharge = {fReader, "Electron_tightCharge"};
  
  //Jets:
  TTreeReaderValue<iterator> nJet = {fReader, "nJet"};
  TTreeReaderArray<int_or_char> Jet_jetId = {fReader, "Jet_jetId"};
  TTreeReaderArray<UChar_t> Jet_nConstituents = {fReader, "Jet_nConstituents"};
  TTreeReaderArray<int_or_char> Jet_nElectrons = {fReader, "Jet_nElectrons"};
  TTreeReaderArray<int_or_char> Jet_nMuons = {fReader, "Jet_nMuons"};
  //TTreeReaderArray<int_or_char> Jet_nSVs = {fReader, "Jet_nSVs"};
  TTreeReaderArray<int_or_short> Jet_electronIdx1 = {fReader, "Jet_electronIdx1"};
  TTreeReaderArray<int_or_short> Jet_electronIdx2 = {fReader, "Jet_electronIdx2"};
  TTreeReaderArray<int_or_short> Jet_muonIdx1 = {fReader, "Jet_muonIdx1"};
  TTreeReaderArray<int_or_short> Jet_muonIdx2 = {fReader, "Jet_muonIdx2"};
  //TTreeReaderArray<int_or_short> Jet_svIdx1 = {fReader, "Jet_svIdx1"};
  //TTreeReaderArray<int_or_short> Jet_svIdx2 = {fReader, "Jet_svIdx2"};
  TTreeReaderArray<Float_t> Jet_area = {fReader, "Jet_area"};
  TTreeReaderArray<Float_t> Jet_btagDeepFlavB = {fReader, "Jet_btagDeepFlavB"};
  TTreeReaderArray<Float_t> Jet_btagDeepFlavCvB = {fReader, "Jet_btagDeepFlavCvB"};
  TTreeReaderArray<Float_t> Jet_btagDeepFlavCvL = {fReader, "Jet_btagDeepFlavCvL"};
  TTreeReaderArray<Float_t> Jet_btagDeepFlavQG = {fReader, "Jet_btagDeepFlavQG"};
  TTreeReaderArray<Float_t> Jet_chEmEF = {fReader, "Jet_chEmEF"};
  TTreeReaderArray<Float_t> Jet_chHEF = {fReader, "Jet_chHEF"};
  TTreeReaderArray<Float_t> Jet_eta = {fReader, "Jet_eta"};
  TTreeReaderArray<Float_t> Jet_hfsigmaEtaEta = {fReader, "Jet_hfsigmaEtaEta"};
  TTreeReaderArray<Float_t> Jet_hfsigmaPhiPhi = {fReader, "Jet_hfsigmaPhiPhi"};
  TTreeReaderArray<Float_t> Jet_mass = {fReader, "Jet_mass"};
  TTreeReaderArray<Float_t> Jet_muEF = {fReader, "Jet_muEF"};
  TTreeReaderArray<Float_t> Jet_muonSubtrFactor = {fReader, "Jet_muonSubtrFactor"};
  TTreeReaderArray<Float_t> Jet_neEmEF = {fReader, "Jet_neEmEF"};
  TTreeReaderArray<Float_t> Jet_neHEF = {fReader, "Jet_neHEF"};
  TTreeReaderArray<Float_t> Jet_phi = {fReader, "Jet_phi"};
  TTreeReaderArray<Float_t> Jet_pt = {fReader, "Jet_pt"};
  TTreeReaderArray<Float_t> Jet_rawFactor = {fReader, "Jet_rawFactor"};

  //FatJets:
  TTreeReaderValue<iterator> nFatJet = {fReader, "nFatJet"};
  TTreeReaderArray<Float_t> FatJet_area = {fReader, "FatJet_area"};
  TTreeReaderArray<Float_t> FatJet_eta = {fReader, "FatJet_eta"};
  TTreeReaderArray<Float_t> FatJet_mass = {fReader, "FatJet_mass"};
  TTreeReaderArray<Float_t> FatJet_phi = {fReader, "FatJet_phi"};
  TTreeReaderArray<Float_t> FatJet_pt = {fReader, "FatJet_pt"};
  TTreeReaderArray<int_or_char> FatJet_jetId = {fReader, "FatJet_jetId"};

  //MET
  TTreeReaderValue<Float_t> MET_MetUnclustEnUpDeltaX = {fReader, "MET_MetUnclustEnUpDeltaX"};
  TTreeReaderValue<Float_t> MET_MetUnclustEnUpDeltaY = {fReader, "MET_MetUnclustEnUpDeltaY"};
  TTreeReaderValue<Float_t> MET_covXX = {fReader, "MET_covXX"};
  TTreeReaderValue<Float_t> MET_covXY = {fReader, "MET_covXY"};
  TTreeReaderValue<Float_t> MET_covYY = {fReader, "MET_covYY"};
  TTreeReaderValue<Float_t> MET_phi = {fReader, "MET_phi"};
  TTreeReaderValue<Float_t> MET_pt = {fReader, "MET_pt"};
  TTreeReaderValue<Float_t> MET_significance = {fReader, "MET_significance"};
  TTreeReaderValue<Float_t> MET_sumEt = {fReader, "MET_sumEt"};
  TTreeReaderValue<Float_t> MET_sumPtUnclustered = {fReader, "MET_sumPtUnclustered"};

  //Muon
  TTreeReaderValue<iterator> nMuon = {fReader, "nMuon"};
  TTreeReaderArray<UChar_t> Muon_highPtId = {fReader, "Muon_highPtId"};
  TTreeReaderArray<Bool_t> Muon_highPurity = {fReader, "Muon_highPurity"};
  TTreeReaderArray<Bool_t> Muon_inTimeMuon = {fReader, "Muon_inTimeMuon"};
  TTreeReaderArray<Bool_t> Muon_isGlobal = {fReader, "Muon_isGlobal"};
  TTreeReaderArray<Bool_t> Muon_isPFcand = {fReader, "Muon_isPFcand"};
  TTreeReaderArray<Bool_t> Muon_isStandalone = {fReader, "Muon_isStandalone"};
  TTreeReaderArray<Bool_t> Muon_isTracker = {fReader, "Muon_isTracker"};
  TTreeReaderArray<Bool_t> Muon_looseId = {fReader, "Muon_looseId"};
  TTreeReaderArray<Bool_t> Muon_mediumId = {fReader, "Muon_mediumId"};
  TTreeReaderArray<Bool_t> Muon_mediumPromptId = {fReader, "Muon_mediumPromptId"};
  TTreeReaderArray<Int_t> Muon_charge = {fReader, "Muon_charge"};
  TTreeReaderArray<Int_t> Muon_pdgId = {fReader, "Muon_pdgId"};
  TTreeReaderArray<Float_t> Muon_dxy = {fReader, "Muon_dxy"};
  TTreeReaderArray<Float_t> Muon_dxyErr = {fReader, "Muon_dxyErr"};
  TTreeReaderArray<Float_t> Muon_dxybs = {fReader, "Muon_dxybs"};
  TTreeReaderArray<Float_t> Muon_dz = {fReader, "Muon_dz"};
  TTreeReaderArray<Float_t> Muon_dzErr = {fReader, "Muon_dzErr"};
  TTreeReaderArray<Float_t> Muon_eta = {fReader, "Muon_eta"};
  TTreeReaderArray<Float_t> Muon_ip3d = {fReader, "Muon_ip3d"};
  TTreeReaderArray<Float_t> Muon_mass = {fReader, "Muon_mass"};
  TTreeReaderArray<Float_t> Muon_miniPFRelIso_all = {fReader, "Muon_miniPFRelIso_all"};
  TTreeReaderArray<Float_t> Muon_miniPFRelIso_chg = {fReader, "Muon_miniPFRelIso_chg"};
  //TTreeReaderArray<Float_t> Muon_mvaMuID = {fReader, "Muon_mvaMuID"};
  TTreeReaderArray<Float_t> Muon_pfRelIso03_all = {fReader, "Muon_pfRelIso03_all"};
  TTreeReaderArray<Float_t> Muon_pfRelIso03_chg = {fReader, "Muon_pfRelIso03_chg"};
  TTreeReaderArray<Float_t> Muon_pfRelIso04_all = {fReader, "Muon_pfRelIso04_all"};
  TTreeReaderArray<Float_t> Muon_phi = {fReader, "Muon_phi"};
  TTreeReaderArray<Float_t> Muon_pt = {fReader, "Muon_pt"};
  TTreeReaderArray<Float_t> Muon_ptErr = {fReader, "Muon_ptErr"};
  TTreeReaderArray<Float_t> Muon_sip3d = {fReader, "Muon_sip3d"};
  TTreeReaderArray<int_or_short> Muon_jetIdx = {fReader, "Muon_jetIdx"};
  TTreeReaderArray<int_or_char> Muon_tightCharge = {fReader, "Muon_tightCharge"};
  
  //PuppiMET
  TTreeReaderValue<Float_t> PuppiMET_phi = {fReader, "PuppiMET_phi"};
  TTreeReaderValue<Float_t> PuppiMET_phiJERDown = {fReader, "PuppiMET_phiJERDown"};
  TTreeReaderValue<Float_t> PuppiMET_phiJERUp = {fReader, "PuppiMET_phiJERUp"};
  TTreeReaderValue<Float_t> PuppiMET_phiJESDown = {fReader, "PuppiMET_phiJESDown"};
  TTreeReaderValue<Float_t> PuppiMET_phiJESUp = {fReader, "PuppiMET_phiJESUp"};
  TTreeReaderValue<Float_t> PuppiMET_phiUnclusteredDown = {fReader, "PuppiMET_phiUnclusteredDown"};
  TTreeReaderValue<Float_t> PuppiMET_phiUnclusteredUp = {fReader, "PuppiMET_phiUnclusteredUp"};
  TTreeReaderValue<Float_t> PuppiMET_pt = {fReader, "PuppiMET_pt"};
  TTreeReaderValue<Float_t> PuppiMET_ptJERDown = {fReader, "PuppiMET_ptJERDown"};
  TTreeReaderValue<Float_t> PuppiMET_ptJERUp = {fReader, "PuppiMET_ptJERUp"};
  TTreeReaderValue<Float_t> PuppiMET_ptJESDown = {fReader, "PuppiMET_ptJESDown"};
  TTreeReaderValue<Float_t> PuppiMET_ptJESUp = {fReader, "PuppiMET_ptJESUp"};
  TTreeReaderValue<Float_t> PuppiMET_ptUnclusteredDown = {fReader, "PuppiMET_ptUnclusteredDown"};
  TTreeReaderValue<Float_t> PuppiMET_ptUnclusteredUp = {fReader, "PuppiMET_ptUnclusteredUp"};
  TTreeReaderValue<Float_t> PuppiMET_sumEt = {fReader, "PuppiMET_sumEt"};

  //Flags
  TTreeReaderValue<Bool_t> Flag_HBHENoiseFilter = {fReader, "Flag_HBHENoiseFilter"};
  TTreeReaderValue<Bool_t> Flag_HBHENoiseIsoFilter = {fReader, "Flag_HBHENoiseIsoFilter"};
  TTreeReaderValue<Bool_t> Flag_CSCTightHaloFilter = {fReader, "Flag_CSCTightHaloFilter"};
  TTreeReaderValue<Bool_t> Flag_CSCTightHaloTrkMuUnvetoFilter = {fReader, "Flag_CSCTightHaloTrkMuUnvetoFilter"};
  TTreeReaderValue<Bool_t> Flag_CSCTightHalo2015Filter = {fReader, "Flag_CSCTightHalo2015Filter"};
  TTreeReaderValue<Bool_t> Flag_globalTightHalo2016Filter = {fReader, "Flag_globalTightHalo2016Filter"};
  TTreeReaderValue<Bool_t> Flag_globalSuperTightHalo2016Filter = {fReader, "Flag_globalSuperTightHalo2016Filter"};
  TTreeReaderValue<Bool_t> Flag_HcalStripHaloFilter = {fReader, "Flag_HcalStripHaloFilter"};
  TTreeReaderValue<Bool_t> Flag_hcalLaserEventFilter = {fReader, "Flag_hcalLaserEventFilter"};
  TTreeReaderValue<Bool_t> Flag_EcalDeadCellTriggerPrimitiveFilter = {fReader, "Flag_EcalDeadCellTriggerPrimitiveFilter"};
  TTreeReaderValue<Bool_t> Flag_EcalDeadCellBoundaryEnergyFilter = {fReader, "Flag_EcalDeadCellBoundaryEnergyFilter"};
  TTreeReaderValue<Bool_t> Flag_ecalBadCalibFilter = {fReader, "Flag_ecalBadCalibFilter"};
  TTreeReaderValue<Bool_t> Flag_goodVertices = {fReader, "Flag_goodVertices"};
  TTreeReaderValue<Bool_t> Flag_eeBadScFilter = {fReader, "Flag_eeBadScFilter"};
  TTreeReaderValue<Bool_t> Flag_ecalLaserCorrFilter = {fReader, "Flag_ecalLaserCorrFilter"};
  TTreeReaderValue<Bool_t> Flag_trkPOGFilters = {fReader, "Flag_trkPOGFilters"};
  TTreeReaderValue<Bool_t> Flag_chargedHadronTrackResolutionFilter = {fReader, "Flag_chargedHadronTrackResolutionFilter"};
  TTreeReaderValue<Bool_t> Flag_muonBadTrackFilter = {fReader, "Flag_muonBadTrackFilter"};
  TTreeReaderValue<Bool_t> Flag_BadChargedCandidateFilter = {fReader, "Flag_BadChargedCandidateFilter"};
  TTreeReaderValue<Bool_t> Flag_BadPFMuonFilter = {fReader, "Flag_BadPFMuonFilter"};
  TTreeReaderValue<Bool_t> Flag_BadPFMuonDzFilter = {fReader, "Flag_BadPFMuonDzFilter"};
  TTreeReaderValue<Bool_t> Flag_hfNoisyHitsFilter = {fReader, "Flag_hfNoisyHitsFilter"};
  TTreeReaderValue<Bool_t> Flag_BadChargedCandidateSummer16Filter = {fReader, "Flag_BadChargedCandidateSummer16Filter"};
  TTreeReaderValue<Bool_t> Flag_BadPFMuonSummer16Filter = {fReader, "Flag_BadPFMuonSummer16Filter"};
  TTreeReaderValue<Bool_t> Flag_trkPOG_manystripclus53X = {fReader, "Flag_trkPOG_manystripclus53X"};
  TTreeReaderValue<Bool_t> Flag_trkPOG_toomanystripclus53X = {fReader, "Flag_trkPOG_toomanystripclus53X"};
  TTreeReaderValue<Bool_t> Flag_trkPOG_logErrorTooManyClusters = {fReader, "Flag_trkPOG_logErrorTooManyClusters"};
  TTreeReaderValue<Bool_t> Flag_METFilters = {fReader, "Flag_METFilters"};

  /*
  //HLT paths
  TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf = {fReader, "HLT_Ele27_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_Ele28_WPTight_Gsf = {fReader, "HLT_Ele28_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_Ele30_WPTight_Gsf = {fReader, "HLT_Ele30_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf = {fReader, "HLT_Ele32_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_Ele35_WPTight_Gsf = {fReader, "HLT_Ele35_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_Ele38_WPTight_Gsf = {fReader, "HLT_Ele38_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_Ele40_WPTight_Gsf = {fReader, "HLT_Ele40_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_IsoMu20 = {fReader, "HLT_IsoMu20"};
  TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
  TTreeReaderValue<Bool_t> HLT_IsoMu24_eta2p1 = {fReader, "HLT_IsoMu24_eta2p1"};
  TTreeReaderValue<Bool_t> HLT_IsoMu27 = {fReader, "HLT_IsoMu27"};
  TTreeReaderValue<Bool_t> HLT_Mu15 = {fReader, "HLT_Mu15"};
  TTreeReaderValue<Bool_t> HLT_Mu20 = {fReader, "HLT_Mu20"};
  TTreeReaderValue<Bool_t> HLT_Mu27 = {fReader, "HLT_Mu27"};
  TTreeReaderValue<Bool_t> HLT_Mu50 = {fReader, "HLT_Mu50"};
  TTreeReaderValue<Bool_t> HLT_Mu55 = {fReader, "HLT_Mu55"};*/

  //--------------------
  // Gen-level branches:
  //--------------------

  //GenJet:
  TTreeReaderValue<iterator> nGenJet = {fReader_MC, "nGenJet"};
  TTreeReaderArray<Float_t> GenJet_eta = {fReader_MC, "GenJet_eta"};
  TTreeReaderArray<Float_t> GenJet_mass = {fReader_MC, "GenJet_mass"};
  TTreeReaderArray<Float_t> GenJet_phi = {fReader_MC, "GenJet_phi"};
  TTreeReaderArray<Float_t> GenJet_pt = {fReader_MC, "GenJet_pt"};

  //GenPart:
  TTreeReaderValue<iterator> nGenPart = {fReader_MC, "nGenPart"};
  TTreeReaderArray<int_or_short> GenPart_genPartIdxMother = {fReader_MC, "GenPart_genPartIdxMother"};
  TTreeReaderArray<int_or_ushort> GenPart_statusFlags = {fReader_MC, "GenPart_statusFlags"};
  TTreeReaderArray<Int_t> GenPart_pdgId = {fReader_MC, "GenPart_pdgId"};
  TTreeReaderArray<Int_t> GenPart_status = {fReader_MC, "GenPart_status"};
  TTreeReaderArray<Float_t> GenPart_eta = {fReader_MC, "GenPart_eta"};
  TTreeReaderArray<Float_t> GenPart_mass = {fReader_MC, "GenPart_mass"};
  TTreeReaderArray<Float_t> GenPart_phi = {fReader_MC, "GenPart_phi"};
  TTreeReaderArray<Float_t> GenPart_pt = {fReader_MC, "GenPart_pt"};

  //GenWeights:
  TTreeReaderValue<Float_t> Generator_weight = {fReader_MC, "Generator_weight"};
  //TTreeReaderValue<Float_t> genWeight = {fReader_MC, "genWeight"};

  //GenMET
  TTreeReaderValue<Float_t> GenMET_phi = {fReader_MC, "GenMET_phi"};
  TTreeReaderValue<Float_t> GenMET_pt = {fReader_MC, "GenMET_pt"};

  //PileUP
  TTreeReaderValue<Int_t> Pileup_nPU = {fReader_MC, "Pileup_nPU"};
  TTreeReaderValue<Int_t> Pileup_sumEOOT = {fReader_MC, "Pileup_sumEOOT"};
  TTreeReaderValue<Int_t> Pileup_sumLOOT = {fReader_MC, "Pileup_sumLOOT"};
  TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader_MC, "Pileup_nTrueInt"};
  TTreeReaderValue<Float_t> Pileup_pudensity = {fReader_MC, "Pileup_pudensity"};
  TTreeReaderValue<Float_t> Pileup_gpudensity = {fReader_MC, "Pileup_gpudensity"};

  //Jetflavor:
  TTreeReaderArray<int_or_char> Jet_hadronFlavour = {fReader_MC, "Jet_hadronFlavour"};
  TTreeReaderArray<int_or_char> FatJet_hadronFlavour = {fReader_MC, "FatJet_hadronFlavour"};

  //_____________________________________________________________________________________________________________
  // DONE READING BRANCHES
  
  AnaScript(TTree * /*tree*/ =0) { }
  virtual ~AnaScript() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();
  
  //-------------------------------------------------------------------------------------------------------------
  // User defined features
  //-------------------------------------------------------------------------------------------------------------

  //Structs:
  struct Hists {
    TH1F *nevt;
    TH1F *correction[10];
    TH1F *hist[50];
    TH1F *evt2LSS[50];
  };
  struct Particle {
    TLorentzVector v;
    int id;
    int ind;
    int flavor;
    int charge;
    int momid;
    int status;
    //Isolation:
    float sip3d;
    float reliso03;
    float reliso04;
    //Calorimeter information
    float hovere;
    float r9;
    //MVA/NN Score:
    float btagscore;
    //Gen-level information:
    int pdgid;
    int genindex;
    int hadronflavor;
    int decaymode; //For VLL, 0-stable, 1-W, 2-Z, 3-Higgs
    vector<int> dauind; //indices of the daughters (GenPart only)
    vector<int> dauid; //pdgid of the daughters (GenPart only)
  };
  struct sftxt {
    TString campaign;
    double etalow, etahigh;
    double ptlow, pthigh;
    double philow, phihigh;
    double rholow, rhohigh;
    int flavor; int ntrueInt;
    double sfdown, sf, sfup;
  };

  //Setting parameters:
  void SetHstFileName(const char *HstFileName){ _HstFileName = HstFileName;}
  void SetSkimFileName(const char *SkimFileName){ _SkimFileName = SkimFileName;}
  void SetTreeFileName(const char *TreeFileName){ _TreeFileName = TreeFileName;}
  void SetSumFileName(const char *SumFileName){ _SumFileName = SumFileName;}
  void SetData(int data){_data=data;}
  void SetCampaign(TString campaign){_campaign = campaign;}
  void SetFlag(TString flag){_flag=flag;}
  void SetSampleName(TString samplename){_samplename=samplename;}
  
  //Utility functions:
  void BookHistograms();
  float delta_phi(float phi1, float phi2);
  int  MotherID(int partindex, int momindex);
  float transv_mass(float lepE, float lepphi, float met, float metphi);
  void createLightLeptons();
  void createJets();
  void createFatJets();
  void createGenLightLeptons();
  void createGenJets();
  void createSignalArrays();
  void SortRecoObjects();
  void SortGenObjects();
  void SortVLL();
  void EventSelection();
  float getEventWeight();
  TString ParticleName(int pdgid);
  json loadJson();
  bool checkJson(bool isData, int runno, int lumisection);
  void LoadCorrectionsFromPOG();
  void SortPt(vector<Particle> &part);
  bool clean_from_array(Particle target, vector<Particle> array, float dRcut);
  bool isMatchingWithGen(Particle reco, vector<Particle> gencollection);

  //Object corrections:
  double returnMuonIDSF(Particle muon, TString mode);
  double returnMuonIsoSF(Particle muon, TString mode);
  double returnElectronIDSF(Particle ele, TString mode);
  double returnLeptonSF(Particle lepton, TString mode);
  double returnJetJECSF(Particle jet, TString mode);
  double returnJetJERSF(Particle jet, TString mode);
  double returnJetPtResSF(Particle jet);
  double returnJetResolutionCorrection(Particle jet, TString mode);
  double returnbJetTaggingSFPOG(Particle jet, TString mode);
  double btagMCeff_2016preVFP_UL(Particle jet);
  double btagMCeff_2016postVFP_UL(Particle jet);
  double btagMCeff_2017_UL(Particle jet);
  double btagMCeff_2018_UL(Particle jet);
  double btagMCeff_Run3Summer22(Particle jet);
  double btagMCeff_Run3Summer22EE(Particle jet);
  double btagMCeff_Run3Summer23(Particle jet);
  double btagMCeff_Run3Summer23BPix(Particle jet);
  double returnbJetCorrection(vector<Particle> Jet, TString mode);
  double returnPDFweight(string mode);
  double returnQCDscaleWeight(string mode);
    
  //Trigger corrections:
  /*
  double GetLeptonTriggerEfficiency(Particle lepton);
  double TrigEFF_allCampaign_Isomu24_MC(Particle muon);
  double TrigEFF_allCampaign_Isomu24_Data(Particle muon);
  double TrigEFF_allCampaign_Ele27or32WPTightGSF_MC(Particle electron);
  double TrigEFF_allCampaign_Ele27or32WPTightGSF_Data(Particle electron);*/
  double GetLeptonTriggerEfficiency(Particle lepton, TString mode);
  double TrigEff_HLT_IsoMuXX(Particle lepton, TString mode);
  double TrigEff_HLT_EleXX_WPTight_Gsf(Particle lepton, TString mode);

  //Pileup correction:
  double returnPileUpWt(TString mode);

  //Weights from JSONs:
  double LoadLumiWeights(TString campaign, TString fullsamplename) ;
  double LoadAvgGenWeights(TString campaign, TString fullsamplename);

  //------------------------------------------
  //For Skimmer:
  void ReadBranch();
  void ActivateBranch(TTree *t);

  //For TreeMaker:
  void FillTree(TTree *tree);
  void AddAndCompressBranch(TBranch *br);
  void InitializeBranches(TTree *tree);

  //For 3L/4L veto:
  int electronCustomID(Int_t bitmap,int quality, int skipCut);
  bool Veto3L4L();
  bool VetoHEM(vector<Particle> jet);

  //------------------------------------------------------------------------------------------------------------
  // GLOBAL VARIABLE DECLARATIONS
  //------------------------------------------------------------------------------------------------------------
protected:
  Hists h;

private:
  TFile *_HstFile, *_SkimFile, *_TreeFile;
  TTree *skimTree;
  const char *_HstFileName, *_SkimFileName, *_TreeFileName;
  const char *_SumFileName;
  int _data, _year;
  float metpt, metphi, _btagWP;
  TString _campaign, _flag, _samplename;
  time_t start, end, buffer;

  //Physics objects:
  vector<Particle> genMuon, genElectron, genLightLepton, genJet;
  vector<Particle> vllep, vlnu;
  vector<Particle> Muon, Electron, LightLepton, Photon, Tau, Jet, FatJet, bJet, MediumbJet;
  vector<Particle> LooseLepton, LooseMuon, LooseElectron;
  vector<Particle> yash_llep, yash_looseMuon; //For 3L/4L veto

  //ScaleFactors from POG:
  vector<sftxt> muonIDSF, muonIsoSF, electronIDSF;
  vector<sftxt> jetJERSF, jetJECSF, jetPtResSF;
  vector<sftxt> bJetEffPOG;
  vector<sftxt> pileupwtPOG;

  //Flags::
  bool GoodEvt, GoodEvt2016, GoodEvt2017, GoodEvt2018, GoodEvt2022, GoodEvt2023;
  bool triggerRes, trigger2016, trigger2017, trigger2018, trigger2022, trigger2023;
  bool muon_trigger, electron_trigger, overlapping_events;
  bool evt_trigger;
  bool bad_event;

  //Counters:
  int nEvtTotal,nEvtRan,nEvtTrigger,nEvtPass,nEvtBad,nThrown,nEvtVeto,nEvtGen;

  //json:
  json jsondata;
  double lumiweight, avggenweight;

  //For TreeMaker:
  TTree *_mytree;
  UInt_t  channel;
  UInt_t  trigger;
  UInt_t  nlep;
  UInt_t  njet;
  UInt_t  nfatjet;
  UInt_t  nbjet;
  Float_t lep0_pt;
  Float_t lep0_eta;
  Float_t lep0_phi;
  Float_t lep0_iso;
  Float_t lep0_sip3d;
  Float_t lep0_mt;
  Float_t lep1_pt;
  Float_t lep1_eta;
  Float_t lep1_phi;
  Float_t lep1_iso;
  Float_t lep1_sip3d;
  Float_t lep1_mt;
  Float_t dilep_pt;
  Float_t dilep_eta;
  Float_t dilep_phi;
  Float_t dilep_mass;
  Float_t dilep_mt;
  Float_t dilep_deta;
  Float_t dilep_dphi;
  Float_t dilep_dR;
  Float_t dilep_ptratio;
  Float_t HT, HTfat;
  Float_t LT;
  Float_t STvis, STvisfat;
  Float_t ST, STfat;
  Float_t LTplusMET;
  Float_t HTplusMET, HTfatplusMET;
  Float_t HTMETllpt, HTfatMETllpt;
  Float_t STfrac;
  Float_t dphi_metlep0;
  Float_t dphi_metlep1;
  Float_t dphi_metdilep;
  Float_t dphi_metlep_max;
  Float_t dphi_metlep_min;
  Float_t metpt_tree;
  Float_t metphi_tree;
  Float_t jec;
  Float_t jer;
  Double_t gen_weight;
  Double_t gen_weight_evt;
  Double_t lumi_weight_evt;
  Double_t sf_lepIdIso,   sf_lepIdIso_up,   sf_lepIdIso_down;
  Double_t sf_lepTrigEff, sf_lepTrigEff_up, sf_lepTrigEff_down;
  Double_t sf_pileup,     sf_pileup_up,     sf_pileup_down;
  Double_t sf_btagEff,    sf_btagEff_up,    sf_btagEff_down;
  Double_t sf_pdf,        sf_pdf_up,        sf_pdf_down;
  Double_t sf_qcdscale,   sf_qcdscale_up,   sf_qcdscale_down;

  ClassDef(AnaScript,0);

};

#endif

#ifdef AnaScript_cxx
void AnaScript::Init(TTree *tree)
{
  fReader                  .SetTree(tree);
  if(_data == 0){
    fReader_MC.SetTree(tree);
    if (_flag!="qcd") fReader_nonQCD.SetTree(tree);
  }

  //for TreeMaker:
  _TreeFile = new TFile(_TreeFileName, "RECREATE");
  _TreeFile->SetCompressionAlgorithm(2);
  _TreeFile->SetCompressionLevel(9);
  _TreeFile->SetCompressionSettings(209);

  // Create memory-resident tree to avoid multiple copies
  _mytree = new TTree("myEvents", "myEvents");
  //_mytree->SetDirectory(nullptr); // prevent auto-registration
  _mytree->SetDirectory(_TreeFile); // attach to file
  _mytree->SetAutoSave(300000000);  // autosave every ~300 MB (tune if needed)
  
  InitializeBranches(_mytree);
}

Bool_t AnaScript::Notify()
{
  return kTRUE;
}


#endif // #ifdef AnaScript_cxx
