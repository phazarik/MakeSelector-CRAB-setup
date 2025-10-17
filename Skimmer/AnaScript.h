//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 18 14:29:52 2025 by ROOT version 6.26/10
// from TTree Events/Events
// found on file: DYto2L-4Jets_MLL-50.root (NanoAODv12)
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

class AnaScript : public TSelector {
private:
  
  //For NanoAODv12 and beyond:
  using iterator     = Int_t;
  using int_or_char  = UChar_t;
  using int_or_short = Short_t;
  using int_or_ushort = UShort_t;
  /*
  //For NanoAODv11 and below
  using iterator     = UInt_t; 
  using int_or_char  = Int_t;
  using int_or_short = Int_t;
  using int_or_ushort = Int_t;
  */
  //Note: Remove LHE weight branches in case of QCD samples
  
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
  TTreeReaderValue<Float_t> Rho_fixedGridRhoAll = {fReader, "Rho_fixedGridRhoAll"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetAll = {fReader, "Rho_fixedGridRhoFastjetAll"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentral = {fReader, "Rho_fixedGridRhoFastjetCentral"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentralCalo = {fReader, "Rho_fixedGridRhoFastjetCentralCalo"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentralChargedPileUp = {fReader, "Rho_fixedGridRhoFastjetCentralChargedPileUp"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentralNeutral = {fReader, "Rho_fixedGridRhoFastjetCentralNeutral"};
  /*
  //Rho (Run-2)
  TTreeReaderValue<Float_t> fixedGridRhoFastjetAll =            {fReader, "fixedGridRhoFastjetAll"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentral =        {fReader, "fixedGridRhoFastjetCentral"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentralCalo =    {fReader, "fixedGridRhoFastjetCentralCalo"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentralChargedPileUp = {fReader, "fixedGridRhoFastjetCentralChargedPileUp"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentralNeutral = {fReader, "fixedGridRhoFastjetCentralNeutral"};
  TTreeReaderValue<Float_t> rho = fixedGridRhoFastjetAll;
  */
  //Non-QCD branches:
  TTreeReaderValue<Float_t>  LHEWeight_originalXWGTUP = {fReader_nonQCD, "LHEWeight_originalXWGTUP"};
  TTreeReaderValue<iterator> nLHEPdfWeight            = {fReader_nonQCD, "nLHEPdfWeight"};
  TTreeReaderArray<Float_t>  LHEPdfWeight             = {fReader_nonQCD, "LHEPdfWeight"};
  TTreeReaderValue<iterator> nLHEReweightingWeight    = {fReader_nonQCD, "nLHEReweightingWeight"};
  TTreeReaderArray<Float_t>  LHEReweightingWeight     = {fReader_nonQCD, "LHEReweightingWeight"};
  TTreeReaderValue<iterator> nLHEScaleWeight          = {fReader_nonQCD, "nLHEScaleWeight"};
  TTreeReaderArray<Float_t>  LHEScaleWeight           = {fReader_nonQCD, "LHEScaleWeight"};
  
  //--------------------------------------------------------------------------------

  TTreeReaderValue<UInt_t> run = {fReader, "run"};
  TTreeReaderValue<UInt_t> luminosityBlock = {fReader, "luminosityBlock"};
  TTreeReaderValue<ULong64_t> event = {fReader, "event"};
  //TTreeReaderValue<UInt_t> bunchCrossing = {fReader, "bunchCrossing"};

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
  TTreeReaderArray<Int_t> Electron_vidNestedWPBitmap =      {fReader, "Electron_vidNestedWPBitmap"};
  TTreeReaderArray<Int_t> Electron_vidNestedWPBitmapHEEP =  {fReader, "Electron_vidNestedWPBitmapHEEP"};
  TTreeReaderArray<int_or_short> Electron_jetIdx = {fReader, "Electron_jetIdx"};
  TTreeReaderArray<int_or_char> Electron_tightCharge = {fReader, "Electron_tightCharge"};
  
  /*
  //IsoTrack
  TTreeReaderValue<iterator> nIsoTrack = {fReader, "nIsoTrack"};
  TTreeReaderArray<Bool_t> IsoTrack_isHighPurityTrack = {fReader, "IsoTrack_isHighPurityTrack"};
  TTreeReaderArray<Bool_t> IsoTrack_isPFcand = {fReader, "IsoTrack_isPFcand"};
  TTreeReaderArray<Bool_t> IsoTrack_isFromLostTrack = {fReader, "IsoTrack_isFromLostTrack"};
  TTreeReaderArray<Short_t> IsoTrack_charge = {fReader, "IsoTrack_charge"};
  TTreeReaderArray<Short_t> IsoTrack_fromPV = {fReader, "IsoTrack_fromPV"};
  TTreeReaderArray<Int_t> IsoTrack_pdgId = {fReader, "IsoTrack_pdgId"};
  TTreeReaderArray<Float_t> IsoTrack_dxy = {fReader, "IsoTrack_dxy"};
  TTreeReaderArray<Float_t> IsoTrack_dz = {fReader, "IsoTrack_dz"};
  TTreeReaderArray<Float_t> IsoTrack_eta = {fReader, "IsoTrack_eta"};
  TTreeReaderArray<Float_t> IsoTrack_pfRelIso03_all = {fReader, "IsoTrack_pfRelIso03_all"};
  TTreeReaderArray<Float_t> IsoTrack_pfRelIso03_chg = {fReader, "IsoTrack_pfRelIso03_chg"};
  TTreeReaderArray<Float_t> IsoTrack_phi = {fReader, "IsoTrack_phi"};
  TTreeReaderArray<Float_t> IsoTrack_pt = {fReader, "IsoTrack_pt"};
  TTreeReaderArray<Float_t> IsoTrack_miniPFRelIso_all = {fReader, "IsoTrack_miniPFRelIso_all"};
  TTreeReaderArray<Float_t> IsoTrack_miniPFRelIso_chg = {fReader, "IsoTrack_miniPFRelIso_chg"};*/

  //Jets
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
  //TTreeReaderArray<Int_t> Jet_hfadjacentEtaStripsSize = {fReader, "Jet_hfadjacentEtaStripsSize"};
  //TTreeReaderArray<Int_t> Jet_hfcentralEtaStripSize = {fReader, "Jet_hfcentralEtaStripSize"};
  //TTreeReaderArray<Float_t> Jet_PNetRegPtRawCorr = {fReader, "Jet_PNetRegPtRawCorr"};
  //TTreeReaderArray<Float_t> Jet_PNetRegPtRawCorrNeutrino = {fReader, "Jet_PNetRegPtRawCorrNeutrino"};
  //TTreeReaderArray<Float_t> Jet_PNetRegPtRawRes = {fReader, "Jet_PNetRegPtRawRes"};
  TTreeReaderArray<Float_t> Jet_area = {fReader, "Jet_area"};
  TTreeReaderArray<Float_t> Jet_btagDeepFlavB = {fReader, "Jet_btagDeepFlavB"};
  //TTreeReaderArray<Float_t> Jet_btagDeepFlavCvB = {fReader, "Jet_btagDeepFlavCvB"};
  //TTreeReaderArray<Float_t> Jet_btagDeepFlavCvL = {fReader, "Jet_btagDeepFlavCvL"};
  //TTreeReaderArray<Float_t> Jet_btagDeepFlavQG = {fReader, "Jet_btagDeepFlavQG"};
  //TTreeReaderArray<Float_t> Jet_btagPNetB = {fReader, "Jet_btagPNetB"};
  //TTreeReaderArray<Float_t> Jet_btagPNetCvB = {fReader, "Jet_btagPNetCvB"};
  //TTreeReaderArray<Float_t> Jet_btagPNetCvL = {fReader, "Jet_btagPNetCvL"};
  //TTreeReaderArray<Float_t> Jet_btagPNetQvG = {fReader, "Jet_btagPNetQvG"};
  //TTreeReaderArray<Float_t> Jet_btagPNetTauVJet = {fReader, "Jet_btagPNetTauVJet"};
  //TTreeReaderArray<Float_t> Jet_btagRobustParTAK4B = {fReader, "Jet_btagRobustParTAK4B"};
  //TTreeReaderArray<Float_t> Jet_btagRobustParTAK4CvB = {fReader, "Jet_btagRobustParTAK4CvB"};
  //TTreeReaderArray<Float_t> Jet_btagRobustParTAK4CvL = {fReader, "Jet_btagRobustParTAK4CvL"};
  //TTreeReaderArray<Float_t> Jet_btagRobustParTAK4QG = {fReader, "Jet_btagRobustParTAK4QG"};
  TTreeReaderArray<Float_t> Jet_chEmEF = {fReader, "Jet_chEmEF"};
  TTreeReaderArray<Float_t> Jet_chHEF = {fReader, "Jet_chHEF"};
  TTreeReaderArray<Float_t> Jet_eta = {fReader, "Jet_eta"};
  //TTreeReaderArray<Float_t> Jet_hfsigmaEtaEta = {fReader, "Jet_hfsigmaEtaEta"};
  //TTreeReaderArray<Float_t> Jet_hfsigmaPhiPhi = {fReader, "Jet_hfsigmaPhiPhi"};
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
  
  //Photon
  /*
  TTreeReaderValue<iterator> nPhoton = {fReader, "nPhoton"};
  TTreeReaderArray<Char_t> Photon_seediEtaOriX = {fReader, "Photon_seediEtaOriX"};
  TTreeReaderArray<int_or_char> Photon_cutBased = {fReader, "Photon_cutBased"};
  TTreeReaderArray<Bool_t> Photon_electronVeto = {fReader, "Photon_electronVeto"};
  TTreeReaderArray<Bool_t> Photon_hasConversionTracks = {fReader, "Photon_hasConversionTracks"};
  TTreeReaderArray<Bool_t> Photon_isScEtaEB = {fReader, "Photon_isScEtaEB"};
  TTreeReaderArray<Bool_t> Photon_isScEtaEE = {fReader, "Photon_isScEtaEE"};
  TTreeReaderArray<Bool_t> Photon_mvaID_WP80 = {fReader, "Photon_mvaID_WP80"};
  TTreeReaderArray<Bool_t> Photon_mvaID_WP90 = {fReader, "Photon_mvaID_WP90"};
  TTreeReaderArray<Bool_t> Photon_pixelSeed = {fReader, "Photon_pixelSeed"};
  TTreeReaderArray<UChar_t> Photon_seedGain = {fReader, "Photon_seedGain"};
  TTreeReaderArray<int_or_short> Photon_electronIdx = {fReader, "Photon_electronIdx"};
  TTreeReaderArray<int_or_short> Photon_jetIdx = {fReader, "Photon_jetIdx"};
  TTreeReaderArray<Int_t> Photon_seediPhiOriY = {fReader, "Photon_seediPhiOriY"};
  TTreeReaderArray<Int_t> Photon_vidNestedWPBitmap = {fReader, "Photon_vidNestedWPBitmap"};
  TTreeReaderArray<Float_t> Photon_ecalPFClusterIso = {fReader, "Photon_ecalPFClusterIso"};
  TTreeReaderArray<Float_t> Photon_energyErr = {fReader, "Photon_energyErr"};
  TTreeReaderArray<Float_t> Photon_energyRaw = {fReader, "Photon_energyRaw"};
  TTreeReaderArray<Float_t> Photon_esEffSigmaRR = {fReader, "Photon_esEffSigmaRR"};
  TTreeReaderArray<Float_t> Photon_esEnergyOverRawE = {fReader, "Photon_esEnergyOverRawE"};
  TTreeReaderArray<Float_t> Photon_eta = {fReader, "Photon_eta"};
  TTreeReaderArray<Float_t> Photon_etaWidth = {fReader, "Photon_etaWidth"};
  TTreeReaderArray<Float_t> Photon_haloTaggerMVAVal = {fReader, "Photon_haloTaggerMVAVal"};
  TTreeReaderArray<Float_t> Photon_hcalPFClusterIso = {fReader, "Photon_hcalPFClusterIso"};
  TTreeReaderArray<Float_t> Photon_hoe = {fReader, "Photon_hoe"};
  TTreeReaderArray<Float_t> Photon_hoe_PUcorr = {fReader, "Photon_hoe_PUcorr"};
  TTreeReaderArray<Float_t> Photon_mvaID = {fReader, "Photon_mvaID"};
  TTreeReaderArray<Float_t> Photon_pfChargedIso = {fReader, "Photon_pfChargedIso"};
  TTreeReaderArray<Float_t> Photon_pfChargedIsoPFPV = {fReader, "Photon_pfChargedIsoPFPV"};
  TTreeReaderArray<Float_t> Photon_pfChargedIsoWorstVtx = {fReader, "Photon_pfChargedIsoWorstVtx"};
  TTreeReaderArray<Float_t> Photon_pfPhoIso03 = {fReader, "Photon_pfPhoIso03"};
  TTreeReaderArray<Float_t> Photon_pfRelIso03_all_quadratic = {fReader, "Photon_pfRelIso03_all_quadratic"};
  TTreeReaderArray<Float_t> Photon_pfRelIso03_chg_quadratic = {fReader, "Photon_pfRelIso03_chg_quadratic"};
  TTreeReaderArray<Float_t> Photon_phi = {fReader, "Photon_phi"};
  TTreeReaderArray<Float_t> Photon_phiWidth = {fReader, "Photon_phiWidth"};
  TTreeReaderArray<Float_t> Photon_pt = {fReader, "Photon_pt"};
  TTreeReaderArray<Float_t> Photon_r9 = {fReader, "Photon_r9"};
  TTreeReaderArray<Float_t> Photon_s4 = {fReader, "Photon_s4"};
  TTreeReaderArray<Float_t> Photon_sieie = {fReader, "Photon_sieie"};
  TTreeReaderArray<Float_t> Photon_sieip = {fReader, "Photon_sieip"};
  TTreeReaderArray<Float_t> Photon_sipip = {fReader, "Photon_sipip"};
  TTreeReaderArray<Float_t> Photon_trkSumPtHollowConeDR03 = {fReader, "Photon_trkSumPtHollowConeDR03"};
  TTreeReaderArray<Float_t> Photon_trkSumPtSolidConeDR04 = {fReader, "Photon_trkSumPtSolidConeDR04"};
  TTreeReaderArray<Float_t> Photon_x_calo = {fReader, "Photon_x_calo"};
  TTreeReaderArray<Float_t> Photon_y_calo = {fReader, "Photon_y_calo"};
  TTreeReaderArray<Float_t> Photon_z_calo = {fReader, "Photon_z_calo"};*/

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

  //Tau
  /*
   TTreeReaderValue<iterator> nTau = {fReader, "nTau"};
   TTreeReaderArray<UChar_t> Tau_decayMode = {fReader, "Tau_decayMode"};
   TTreeReaderArray<Bool_t> Tau_idAntiEleDeadECal = {fReader, "Tau_idAntiEleDeadECal"};
   TTreeReaderArray<UChar_t> Tau_idAntiMu = {fReader, "Tau_idAntiMu"};
   TTreeReaderArray<Bool_t> Tau_idDecayModeNewDMs = {fReader, "Tau_idDecayModeNewDMs"};
   TTreeReaderArray<Bool_t> Tau_idDecayModeOldDMs = {fReader, "Tau_idDecayModeOldDMs"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSe = {fReader, "Tau_idDeepTau2017v2p1VSe"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSjet = {fReader, "Tau_idDeepTau2017v2p1VSjet"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSmu = {fReader, "Tau_idDeepTau2017v2p1VSmu"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2018v2p5VSe = {fReader, "Tau_idDeepTau2018v2p5VSe"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2018v2p5VSjet = {fReader, "Tau_idDeepTau2018v2p5VSjet"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2018v2p5VSmu = {fReader, "Tau_idDeepTau2018v2p5VSmu"};
   TTreeReaderArray<UChar_t> Tau_nSVs = {fReader, "Tau_nSVs"};
   TTreeReaderArray<int_or_short> Tau_charge = {fReader, "Tau_charge"};
   TTreeReaderArray<Short_t> Tau_decayModePNet = {fReader, "Tau_decayModePNet"};
   TTreeReaderArray<Short_t> Tau_eleIdx = {fReader, "Tau_eleIdx"};
   TTreeReaderArray<Short_t> Tau_jetIdx = {fReader, "Tau_jetIdx"};
   TTreeReaderArray<Short_t> Tau_muIdx = {fReader, "Tau_muIdx"};
   TTreeReaderArray<Short_t> Tau_svIdx1 = {fReader, "Tau_svIdx1"};
   TTreeReaderArray<Short_t> Tau_svIdx2 = {fReader, "Tau_svIdx2"};
   TTreeReaderArray<Float_t> Tau_chargedIso = {fReader, "Tau_chargedIso"};
   TTreeReaderArray<Float_t> Tau_dxy = {fReader, "Tau_dxy"};
   TTreeReaderArray<Float_t> Tau_dz = {fReader, "Tau_dz"};
   TTreeReaderArray<Float_t> Tau_eta = {fReader, "Tau_eta"};
   TTreeReaderArray<Float_t> Tau_leadTkDeltaEta = {fReader, "Tau_leadTkDeltaEta"};
   TTreeReaderArray<Float_t> Tau_leadTkDeltaPhi = {fReader, "Tau_leadTkDeltaPhi"};
   TTreeReaderArray<Float_t> Tau_leadTkPtOverTauPt = {fReader, "Tau_leadTkPtOverTauPt"};
   TTreeReaderArray<Float_t> Tau_mass = {fReader, "Tau_mass"};
   TTreeReaderArray<Float_t> Tau_neutralIso = {fReader, "Tau_neutralIso"};
   TTreeReaderArray<Float_t> Tau_phi = {fReader, "Tau_phi"};
   TTreeReaderArray<Float_t> Tau_photonsOutsideSignalCone = {fReader, "Tau_photonsOutsideSignalCone"};
   TTreeReaderArray<Float_t> Tau_probDM0PNet = {fReader, "Tau_probDM0PNet"};
   TTreeReaderArray<Float_t> Tau_probDM10PNet = {fReader, "Tau_probDM10PNet"};
   TTreeReaderArray<Float_t> Tau_probDM11PNet = {fReader, "Tau_probDM11PNet"};
   TTreeReaderArray<Float_t> Tau_probDM1PNet = {fReader, "Tau_probDM1PNet"};
   TTreeReaderArray<Float_t> Tau_probDM2PNet = {fReader, "Tau_probDM2PNet"};
   TTreeReaderArray<Float_t> Tau_pt = {fReader, "Tau_pt"};
   TTreeReaderArray<Float_t> Tau_ptCorrPNet = {fReader, "Tau_ptCorrPNet"};
   TTreeReaderArray<Float_t> Tau_puCorr = {fReader, "Tau_puCorr"};
   TTreeReaderArray<Float_t> Tau_qConfPNet = {fReader, "Tau_qConfPNet"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2017v2p1VSe = {fReader, "Tau_rawDeepTau2017v2p1VSe"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2017v2p1VSjet = {fReader, "Tau_rawDeepTau2017v2p1VSjet"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2017v2p1VSmu = {fReader, "Tau_rawDeepTau2017v2p1VSmu"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2018v2p5VSe = {fReader, "Tau_rawDeepTau2018v2p5VSe"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2018v2p5VSjet = {fReader, "Tau_rawDeepTau2018v2p5VSjet"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2018v2p5VSmu = {fReader, "Tau_rawDeepTau2018v2p5VSmu"};
   TTreeReaderArray<Float_t> Tau_rawIso = {fReader, "Tau_rawIso"};
   TTreeReaderArray<Float_t> Tau_rawIsodR03 = {fReader, "Tau_rawIsodR03"};
   TTreeReaderArray<Float_t> Tau_rawPNetVSe = {fReader, "Tau_rawPNetVSe"};
   TTreeReaderArray<Float_t> Tau_rawPNetVSjet = {fReader, "Tau_rawPNetVSjet"};
   TTreeReaderArray<Float_t> Tau_rawPNetVSmu = {fReader, "Tau_rawPNetVSmu"};
  */
  /*
  //TrigObj
  TTreeReaderValue<iterator> nTrigObj = {fReader, "nTrigObj"};
  TTreeReaderArray<int_or_short> TrigObj_l1charge = {fReader, "TrigObj_l1charge"};
  TTreeReaderArray<int_or_ushort> TrigObj_id = {fReader, "TrigObj_id"};
  TTreeReaderArray<Int_t> TrigObj_l1iso = {fReader, "TrigObj_l1iso"};
  TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader, "TrigObj_filterBits"};
  TTreeReaderArray<Float_t> TrigObj_pt = {fReader, "TrigObj_pt"};
  TTreeReaderArray<Float_t> TrigObj_eta = {fReader, "TrigObj_eta"};
  TTreeReaderArray<Float_t> TrigObj_phi = {fReader, "TrigObj_phi"};
  TTreeReaderArray<Float_t> TrigObj_l1pt = {fReader, "TrigObj_l1pt"};
  TTreeReaderArray<Float_t> TrigObj_l1pt_2 = {fReader, "TrigObj_l1pt_2"};
  TTreeReaderArray<Float_t> TrigObj_l2pt = {fReader, "TrigObj_l2pt"};*/

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

  //HLT paths
  //TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf = {fReader, "HLT_Ele27_WPTight_Gsf"};
  //TTreeReaderValue<Bool_t> HLT_Ele28_WPTight_Gsf = {fReader, "HLT_Ele28_WPTight_Gsf"};
  //TTreeReaderValue<Bool_t> HLT_Ele30_WPTight_Gsf = {fReader, "HLT_Ele30_WPTight_Gsf"};
  //TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf = {fReader, "HLT_Ele32_WPTight_Gsf"};
  //TTreeReaderValue<Bool_t> HLT_Ele35_WPTight_Gsf = {fReader, "HLT_Ele35_WPTight_Gsf"};
  //TTreeReaderValue<Bool_t> HLT_Ele38_WPTight_Gsf = {fReader, "HLT_Ele38_WPTight_Gsf"};
  //TTreeReaderValue<Bool_t> HLT_Ele40_WPTight_Gsf = {fReader, "HLT_Ele40_WPTight_Gsf"};
  //TTreeReaderValue<Bool_t> HLT_IsoMu20 = {fReader, "HLT_IsoMu20"};
  //TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader, "HLT_IsoMu24"};
  //TTreeReaderValue<Bool_t> HLT_IsoMu24_eta2p1 = {fReader, "HLT_IsoMu24_eta2p1"};
  //TTreeReaderValue<Bool_t> HLT_IsoMu27 = {fReader, "HLT_IsoMu27"};

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
  TTreeReaderValue<Float_t> genWeight = {fReader_MC, "genWeight"};

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

  //Setting parameters:
  void SetSkimFileName(const char *SkimFileName){ _SkimFileName = SkimFileName;}
  void SetData(int data){_data=data;}
  void SetCampaign(TString campaign){_campaign = campaign;}
  void SetFlag(TString flag){_flag=flag;}
  void SetSampleName(TString samplename){_samplename=samplename;}
  
public:
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

  //-------------------------------------------------------------------------
  //User defined functions:

  //Array creators:
  void createLightLeptons();
  //void createPhotons();
  //void createTaus();
  void createJets();
  void createFatJets();
  void createGenLightLeptons();
  void createGenJets();
  void createSignalArrays();

  //Sorting:
  void SortRecoObjects();
  void SortGenObjects();
  void SortVLL();
  void SortPt(vector<Particle> &part);

  //Others:
  float delta_phi(float phi1, float phi2);
  int   MotherID(int partindex, int momindex);
  float transv_mass(float lepE, float lepphi, float met, float metphi);
  bool  clean_from_array(Particle target, vector<Particle> array, float dRcut);
  bool  isMatchingWithGen(Particle reco, vector<Particle> gencollection);

  //Object Corrections:
  //Put here

  //For skimmer:
  void ReadBranch();
  void ActivateBranch(TTree *t);

  //For 3L/4L veto:
  int electronCustomID(Int_t bitmap,int quality, int skipCut);
  bool Veto3L4L();
  bool VetoHEM(vector<Particle> jet);
  
  //-------------------------------------------------------------------------
  // Global variable declarations:
  //protected:
  //Hists h;

private:
  //Parametes fed from outside:
  TFile *_SkimFile; TTree *skimTree;
  const char *_SkimFileName;
  int _data, _year;
  float metpt, metphi;
  TString _flag, _samplename, _campaign;

  vector<Particle> genMuon, genElectron, genLightLepton, genJet;
  vector<Particle> vllep, vlnu;
  vector<Particle> Muon, Electron, LightLepton, Photon, Tau, Jet, FatJet, bJet, MediumbJet;
  vector<Particle> LooseLepton, LooseMuon, LooseElectron;
  vector<Particle> yash_llep, yash_looseMuon; //For 3L/4L veto
  
  //Flags:
  bool bad_event;
  bool GoodEvt, GoodEvt2016, GoodEvt2017, GoodEvt2018, GoodEvt2022, GoodEvt2023;
  bool triggerRes, muon_trigger, electron_trigger, overlapping_events;
  
  //Counters:
  int nEvtTotal, nEvtRan, nEvtTrigger, nEvtPass, nEvtBad, nThrown, nEvtVeto, nEvtGen;
  int nevt_mm, nevt_me, nevt_em, nevt_ee;
  float genEventsumw;
  time_t start, end, buffer;
  
  ClassDef(AnaScript,0);

};

#endif

#ifdef AnaScript_cxx
void AnaScript::Init(TTree *tree)
{
  fReader.SetTree(tree);
  if(_data == 0){
    fReader_MC.SetTree(tree);
    if (_flag!="qcd") fReader_nonQCD.SetTree(tree);
  }

  //For skimmer
  _SkimFile = new TFile(_SkimFileName,"recreate");
  skimTree = tree->CloneTree(0);
}

Bool_t AnaScript::Notify()
{
  return kTRUE;
}


#endif // #ifdef AnaScript_cxx
