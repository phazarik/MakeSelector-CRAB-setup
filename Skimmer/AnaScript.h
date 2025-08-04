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
  /*
  //For NanoAODv12 and beyond:
  using iterator     = Int_t;
  using int_or_char  = UChar_t;
  using int_or_short = Short_t;
  using int_or_ushort = UShort_t;*/
  
  //For NanoAODv11 and below
  using iterator     = UInt_t; 
  using int_or_char  = Int_t;
  using int_or_short = Int_t;
  using int_or_ushort = Int_t;

  //Note: Remove LHE weight branches in case of QCD samples
  
public :
  TTreeReader     fReader_2022;
  TTreeReader     fReader_2022MC;
  TTree          *fChain = 0;

   // Readers to access the data (delete the ones you do not need).
  TTreeReaderValue<UInt_t> run = {fReader_2022, "run"};
  TTreeReaderValue<UInt_t> luminosityBlock = {fReader_2022, "luminosityBlock"};
  TTreeReaderValue<ULong64_t> event = {fReader_2022, "event"};
  //TTreeReaderValue<UInt_t> bunchCrossing = {fReader_2022, "bunchCrossing"};

  //Electrons:
  TTreeReaderValue<iterator> nElectron = {fReader_2022, "nElectron"};
  TTreeReaderArray<int_or_char> Electron_cutBased = {fReader_2022, "Electron_cutBased"};
  TTreeReaderArray<Bool_t> Electron_cutBased_HEEP = {fReader_2022, "Electron_cutBased_HEEP"};
  TTreeReaderArray<UChar_t> Electron_lostHits = {fReader_2022, "Electron_lostHits"};
  //TTreeReaderArray<Bool_t> Electron_mvaIso_WP80 = {fReader_2022, "Electron_mvaIso_WP80"};
  //TTreeReaderArray<Bool_t> Electron_mvaIso_WP90 = {fReader_2022, "Electron_mvaIso_WP90"};
  //TTreeReaderArray<Bool_t> Electron_mvaNoIso_WP80 = {fReader_2022, "Electron_mvaNoIso_WP80"};
  //TTreeReaderArray<Bool_t> Electron_mvaNoIso_WP90 = {fReader_2022, "Electron_mvaNoIso_WP90"};
  TTreeReaderArray<UChar_t> Electron_seedGain = {fReader_2022, "Electron_seedGain"};
  TTreeReaderArray<Int_t> Electron_charge = {fReader_2022, "Electron_charge"};
  TTreeReaderArray<Int_t> Electron_pdgId = {fReader_2022, "Electron_pdgId"};
  TTreeReaderArray<Float_t> Electron_dxy = {fReader_2022, "Electron_dxy"};
  TTreeReaderArray<Float_t> Electron_dxyErr = {fReader_2022, "Electron_dxyErr"};
  TTreeReaderArray<Float_t> Electron_dz = {fReader_2022, "Electron_dz"};
  TTreeReaderArray<Float_t> Electron_dzErr = {fReader_2022, "Electron_dzErr"};
  TTreeReaderArray<Float_t> Electron_eta = {fReader_2022, "Electron_eta"};
  TTreeReaderArray<Float_t> Electron_hoe = {fReader_2022, "Electron_hoe"};
  TTreeReaderArray<Float_t> Electron_ip3d = {fReader_2022, "Electron_ip3d"};
  TTreeReaderArray<Float_t> Electron_mass = {fReader_2022, "Electron_mass"};
  TTreeReaderArray<Float_t> Electron_miniPFRelIso_all = {fReader_2022, "Electron_miniPFRelIso_all"};
  TTreeReaderArray<Float_t> Electron_miniPFRelIso_chg = {fReader_2022, "Electron_miniPFRelIso_chg"};;
  TTreeReaderArray<Float_t> Electron_pfRelIso03_all = {fReader_2022, "Electron_pfRelIso03_all"};
  TTreeReaderArray<Float_t> Electron_pfRelIso03_chg = {fReader_2022, "Electron_pfRelIso03_chg"};
  TTreeReaderArray<Float_t> Electron_phi = {fReader_2022, "Electron_phi"};
  TTreeReaderArray<Float_t> Electron_pt = {fReader_2022, "Electron_pt"};
  TTreeReaderArray<Float_t> Electron_r9 = {fReader_2022, "Electron_r9"};
  TTreeReaderArray<Float_t> Electron_scEtOverPt = {fReader_2022, "Electron_scEtOverPt"};
  TTreeReaderArray<Float_t> Electron_sieie = {fReader_2022, "Electron_sieie"};
  TTreeReaderArray<Float_t> Electron_sip3d = {fReader_2022, "Electron_sip3d"};
  TTreeReaderArray<Int_t> Electron_vidNestedWPBitmap =      {fReader_2022, "Electron_vidNestedWPBitmap"};
  TTreeReaderArray<Int_t> Electron_vidNestedWPBitmapHEEP =  {fReader_2022, "Electron_vidNestedWPBitmapHEEP"};
  TTreeReaderArray<int_or_short> Electron_jetIdx = {fReader_2022, "Electron_jetIdx"};
  
  /*
  //IsoTrack
  TTreeReaderValue<iterator> nIsoTrack = {fReader_2022, "nIsoTrack"};
  TTreeReaderArray<Bool_t> IsoTrack_isHighPurityTrack = {fReader_2022, "IsoTrack_isHighPurityTrack"};
  TTreeReaderArray<Bool_t> IsoTrack_isPFcand = {fReader_2022, "IsoTrack_isPFcand"};
  TTreeReaderArray<Bool_t> IsoTrack_isFromLostTrack = {fReader_2022, "IsoTrack_isFromLostTrack"};
  TTreeReaderArray<Short_t> IsoTrack_charge = {fReader_2022, "IsoTrack_charge"};
  TTreeReaderArray<Short_t> IsoTrack_fromPV = {fReader_2022, "IsoTrack_fromPV"};
  TTreeReaderArray<Int_t> IsoTrack_pdgId = {fReader_2022, "IsoTrack_pdgId"};
  TTreeReaderArray<Float_t> IsoTrack_dxy = {fReader_2022, "IsoTrack_dxy"};
  TTreeReaderArray<Float_t> IsoTrack_dz = {fReader_2022, "IsoTrack_dz"};
  TTreeReaderArray<Float_t> IsoTrack_eta = {fReader_2022, "IsoTrack_eta"};
  TTreeReaderArray<Float_t> IsoTrack_pfRelIso03_all = {fReader_2022, "IsoTrack_pfRelIso03_all"};
  TTreeReaderArray<Float_t> IsoTrack_pfRelIso03_chg = {fReader_2022, "IsoTrack_pfRelIso03_chg"};
  TTreeReaderArray<Float_t> IsoTrack_phi = {fReader_2022, "IsoTrack_phi"};
  TTreeReaderArray<Float_t> IsoTrack_pt = {fReader_2022, "IsoTrack_pt"};
  TTreeReaderArray<Float_t> IsoTrack_miniPFRelIso_all = {fReader_2022, "IsoTrack_miniPFRelIso_all"};
  TTreeReaderArray<Float_t> IsoTrack_miniPFRelIso_chg = {fReader_2022, "IsoTrack_miniPFRelIso_chg"};*/

  //Jets
  TTreeReaderValue<iterator> nJet = {fReader_2022, "nJet"};
  TTreeReaderArray<int_or_char> Jet_jetId = {fReader_2022, "Jet_jetId"};
  TTreeReaderArray<UChar_t> Jet_nConstituents = {fReader_2022, "Jet_nConstituents"};
  TTreeReaderArray<int_or_char> Jet_nElectrons = {fReader_2022, "Jet_nElectrons"};
  TTreeReaderArray<int_or_char> Jet_nMuons = {fReader_2022, "Jet_nMuons"};
  //TTreeReaderArray<int_or_char> Jet_nSVs = {fReader_2022, "Jet_nSVs"};
  TTreeReaderArray<int_or_short> Jet_electronIdx1 = {fReader_2022, "Jet_electronIdx1"};
  TTreeReaderArray<int_or_short> Jet_electronIdx2 = {fReader_2022, "Jet_electronIdx2"};
  TTreeReaderArray<int_or_short> Jet_muonIdx1 = {fReader_2022, "Jet_muonIdx1"};
  TTreeReaderArray<int_or_short> Jet_muonIdx2 = {fReader_2022, "Jet_muonIdx2"};
  //TTreeReaderArray<int_or_short> Jet_svIdx1 = {fReader_2022, "Jet_svIdx1"};
  //TTreeReaderArray<int_or_short> Jet_svIdx2 = {fReader_2022, "Jet_svIdx2"};
  //TTreeReaderArray<Int_t> Jet_hfadjacentEtaStripsSize = {fReader_2022, "Jet_hfadjacentEtaStripsSize"};
  //TTreeReaderArray<Int_t> Jet_hfcentralEtaStripSize = {fReader_2022, "Jet_hfcentralEtaStripSize"};
  //TTreeReaderArray<Float_t> Jet_PNetRegPtRawCorr = {fReader_2022, "Jet_PNetRegPtRawCorr"};
  //TTreeReaderArray<Float_t> Jet_PNetRegPtRawCorrNeutrino = {fReader_2022, "Jet_PNetRegPtRawCorrNeutrino"};
  //TTreeReaderArray<Float_t> Jet_PNetRegPtRawRes = {fReader_2022, "Jet_PNetRegPtRawRes"};
  TTreeReaderArray<Float_t> Jet_area = {fReader_2022, "Jet_area"};
  TTreeReaderArray<Float_t> Jet_btagDeepFlavB = {fReader_2022, "Jet_btagDeepFlavB"};
  //TTreeReaderArray<Float_t> Jet_btagDeepFlavCvB = {fReader_2022, "Jet_btagDeepFlavCvB"};
  //TTreeReaderArray<Float_t> Jet_btagDeepFlavCvL = {fReader_2022, "Jet_btagDeepFlavCvL"};
  //TTreeReaderArray<Float_t> Jet_btagDeepFlavQG = {fReader_2022, "Jet_btagDeepFlavQG"};
  //TTreeReaderArray<Float_t> Jet_btagPNetB = {fReader_2022, "Jet_btagPNetB"};
  //TTreeReaderArray<Float_t> Jet_btagPNetCvB = {fReader_2022, "Jet_btagPNetCvB"};
  //TTreeReaderArray<Float_t> Jet_btagPNetCvL = {fReader_2022, "Jet_btagPNetCvL"};
  //TTreeReaderArray<Float_t> Jet_btagPNetQvG = {fReader_2022, "Jet_btagPNetQvG"};
  //TTreeReaderArray<Float_t> Jet_btagPNetTauVJet = {fReader_2022, "Jet_btagPNetTauVJet"};
  //TTreeReaderArray<Float_t> Jet_btagRobustParTAK4B = {fReader_2022, "Jet_btagRobustParTAK4B"};
  //TTreeReaderArray<Float_t> Jet_btagRobustParTAK4CvB = {fReader_2022, "Jet_btagRobustParTAK4CvB"};
  //TTreeReaderArray<Float_t> Jet_btagRobustParTAK4CvL = {fReader_2022, "Jet_btagRobustParTAK4CvL"};
  //TTreeReaderArray<Float_t> Jet_btagRobustParTAK4QG = {fReader_2022, "Jet_btagRobustParTAK4QG"};
  TTreeReaderArray<Float_t> Jet_chEmEF = {fReader_2022, "Jet_chEmEF"};
  TTreeReaderArray<Float_t> Jet_chHEF = {fReader_2022, "Jet_chHEF"};
  TTreeReaderArray<Float_t> Jet_eta = {fReader_2022, "Jet_eta"};
  //TTreeReaderArray<Float_t> Jet_hfsigmaEtaEta = {fReader_2022, "Jet_hfsigmaEtaEta"};
  //TTreeReaderArray<Float_t> Jet_hfsigmaPhiPhi = {fReader_2022, "Jet_hfsigmaPhiPhi"};
  TTreeReaderArray<Float_t> Jet_mass = {fReader_2022, "Jet_mass"};
  TTreeReaderArray<Float_t> Jet_muEF = {fReader_2022, "Jet_muEF"};
  TTreeReaderArray<Float_t> Jet_muonSubtrFactor = {fReader_2022, "Jet_muonSubtrFactor"};
  TTreeReaderArray<Float_t> Jet_neEmEF = {fReader_2022, "Jet_neEmEF"};
  TTreeReaderArray<Float_t> Jet_neHEF = {fReader_2022, "Jet_neHEF"};
  TTreeReaderArray<Float_t> Jet_phi = {fReader_2022, "Jet_phi"};
  TTreeReaderArray<Float_t> Jet_pt = {fReader_2022, "Jet_pt"};
  TTreeReaderArray<Float_t> Jet_rawFactor = {fReader_2022, "Jet_rawFactor"};

  //FatJets:
  TTreeReaderValue<iterator> nFatJet = {fReader_2022, "nFatJet"};
  TTreeReaderArray<Float_t> FatJet_area = {fReader_2022, "FatJet_area"};
  TTreeReaderArray<Float_t> FatJet_eta = {fReader_2022, "FatJet_eta"};
  TTreeReaderArray<Float_t> FatJet_mass = {fReader_2022, "FatJet_mass"};
  TTreeReaderArray<Float_t> FatJet_phi = {fReader_2022, "FatJet_phi"};
  TTreeReaderArray<Float_t> FatJet_pt = {fReader_2022, "FatJet_pt"};
  TTreeReaderArray<int_or_char> FatJet_jetId = {fReader_2022, "FatJet_jetId"};
  
  //MET
  TTreeReaderValue<Float_t> MET_MetUnclustEnUpDeltaX = {fReader_2022, "MET_MetUnclustEnUpDeltaX"};
  TTreeReaderValue<Float_t> MET_MetUnclustEnUpDeltaY = {fReader_2022, "MET_MetUnclustEnUpDeltaY"};
  TTreeReaderValue<Float_t> MET_covXX = {fReader_2022, "MET_covXX"};
  TTreeReaderValue<Float_t> MET_covXY = {fReader_2022, "MET_covXY"};
  TTreeReaderValue<Float_t> MET_covYY = {fReader_2022, "MET_covYY"};
  TTreeReaderValue<Float_t> MET_phi = {fReader_2022, "MET_phi"};
  TTreeReaderValue<Float_t> MET_pt = {fReader_2022, "MET_pt"};
  TTreeReaderValue<Float_t> MET_significance = {fReader_2022, "MET_significance"};
  TTreeReaderValue<Float_t> MET_sumEt = {fReader_2022, "MET_sumEt"};
  TTreeReaderValue<Float_t> MET_sumPtUnclustered = {fReader_2022, "MET_sumPtUnclustered"};

  //Muon
  TTreeReaderValue<iterator> nMuon = {fReader_2022, "nMuon"};
  TTreeReaderArray<UChar_t> Muon_highPtId = {fReader_2022, "Muon_highPtId"};
  TTreeReaderArray<Bool_t> Muon_highPurity = {fReader_2022, "Muon_highPurity"};
  TTreeReaderArray<Bool_t> Muon_inTimeMuon = {fReader_2022, "Muon_inTimeMuon"};
  TTreeReaderArray<Bool_t> Muon_isGlobal = {fReader_2022, "Muon_isGlobal"};
  TTreeReaderArray<Bool_t> Muon_isPFcand = {fReader_2022, "Muon_isPFcand"};
  TTreeReaderArray<Bool_t> Muon_isStandalone = {fReader_2022, "Muon_isStandalone"};
  TTreeReaderArray<Bool_t> Muon_isTracker = {fReader_2022, "Muon_isTracker"};
  TTreeReaderArray<Bool_t> Muon_looseId = {fReader_2022, "Muon_looseId"};
  TTreeReaderArray<Bool_t> Muon_mediumId = {fReader_2022, "Muon_mediumId"};
  TTreeReaderArray<Bool_t> Muon_mediumPromptId = {fReader_2022, "Muon_mediumPromptId"};
  TTreeReaderArray<Int_t> Muon_charge = {fReader_2022, "Muon_charge"};
  TTreeReaderArray<Int_t> Muon_pdgId = {fReader_2022, "Muon_pdgId"};
  TTreeReaderArray<Float_t> Muon_dxy = {fReader_2022, "Muon_dxy"};
  TTreeReaderArray<Float_t> Muon_dxyErr = {fReader_2022, "Muon_dxyErr"};
  TTreeReaderArray<Float_t> Muon_dxybs = {fReader_2022, "Muon_dxybs"};
  TTreeReaderArray<Float_t> Muon_dz = {fReader_2022, "Muon_dz"};
  TTreeReaderArray<Float_t> Muon_dzErr = {fReader_2022, "Muon_dzErr"};
  TTreeReaderArray<Float_t> Muon_eta = {fReader_2022, "Muon_eta"};
  TTreeReaderArray<Float_t> Muon_ip3d = {fReader_2022, "Muon_ip3d"};
  TTreeReaderArray<Float_t> Muon_mass = {fReader_2022, "Muon_mass"};
  TTreeReaderArray<Float_t> Muon_miniPFRelIso_all = {fReader_2022, "Muon_miniPFRelIso_all"};
  TTreeReaderArray<Float_t> Muon_miniPFRelIso_chg = {fReader_2022, "Muon_miniPFRelIso_chg"};
  //TTreeReaderArray<Float_t> Muon_mvaMuID = {fReader_2022, "Muon_mvaMuID"};
  TTreeReaderArray<Float_t> Muon_pfRelIso03_all = {fReader_2022, "Muon_pfRelIso03_all"};
  TTreeReaderArray<Float_t> Muon_pfRelIso03_chg = {fReader_2022, "Muon_pfRelIso03_chg"};
  TTreeReaderArray<Float_t> Muon_pfRelIso04_all = {fReader_2022, "Muon_pfRelIso04_all"};
  TTreeReaderArray<Float_t> Muon_phi = {fReader_2022, "Muon_phi"};
  TTreeReaderArray<Float_t> Muon_pt = {fReader_2022, "Muon_pt"};
  TTreeReaderArray<Float_t> Muon_ptErr = {fReader_2022, "Muon_ptErr"};
  TTreeReaderArray<Float_t> Muon_sip3d = {fReader_2022, "Muon_sip3d"};
  TTreeReaderArray<int_or_short> Muon_jetIdx = {fReader_2022, "Muon_jetIdx"};
  
  //Photon
  /*
  TTreeReaderValue<iterator> nPhoton = {fReader_2022, "nPhoton"};
  TTreeReaderArray<Char_t> Photon_seediEtaOriX = {fReader_2022, "Photon_seediEtaOriX"};
  TTreeReaderArray<int_or_char> Photon_cutBased = {fReader_2022, "Photon_cutBased"};
  TTreeReaderArray<Bool_t> Photon_electronVeto = {fReader_2022, "Photon_electronVeto"};
  TTreeReaderArray<Bool_t> Photon_hasConversionTracks = {fReader_2022, "Photon_hasConversionTracks"};
  TTreeReaderArray<Bool_t> Photon_isScEtaEB = {fReader_2022, "Photon_isScEtaEB"};
  TTreeReaderArray<Bool_t> Photon_isScEtaEE = {fReader_2022, "Photon_isScEtaEE"};
  TTreeReaderArray<Bool_t> Photon_mvaID_WP80 = {fReader_2022, "Photon_mvaID_WP80"};
  TTreeReaderArray<Bool_t> Photon_mvaID_WP90 = {fReader_2022, "Photon_mvaID_WP90"};
  TTreeReaderArray<Bool_t> Photon_pixelSeed = {fReader_2022, "Photon_pixelSeed"};
  TTreeReaderArray<UChar_t> Photon_seedGain = {fReader_2022, "Photon_seedGain"};
  TTreeReaderArray<int_or_short> Photon_electronIdx = {fReader_2022, "Photon_electronIdx"};
  TTreeReaderArray<int_or_short> Photon_jetIdx = {fReader_2022, "Photon_jetIdx"};
  TTreeReaderArray<Int_t> Photon_seediPhiOriY = {fReader_2022, "Photon_seediPhiOriY"};
  TTreeReaderArray<Int_t> Photon_vidNestedWPBitmap = {fReader_2022, "Photon_vidNestedWPBitmap"};
  TTreeReaderArray<Float_t> Photon_ecalPFClusterIso = {fReader_2022, "Photon_ecalPFClusterIso"};
  TTreeReaderArray<Float_t> Photon_energyErr = {fReader_2022, "Photon_energyErr"};
  TTreeReaderArray<Float_t> Photon_energyRaw = {fReader_2022, "Photon_energyRaw"};
  TTreeReaderArray<Float_t> Photon_esEffSigmaRR = {fReader_2022, "Photon_esEffSigmaRR"};
  TTreeReaderArray<Float_t> Photon_esEnergyOverRawE = {fReader_2022, "Photon_esEnergyOverRawE"};
  TTreeReaderArray<Float_t> Photon_eta = {fReader_2022, "Photon_eta"};
  TTreeReaderArray<Float_t> Photon_etaWidth = {fReader_2022, "Photon_etaWidth"};
  TTreeReaderArray<Float_t> Photon_haloTaggerMVAVal = {fReader_2022, "Photon_haloTaggerMVAVal"};
  TTreeReaderArray<Float_t> Photon_hcalPFClusterIso = {fReader_2022, "Photon_hcalPFClusterIso"};
  TTreeReaderArray<Float_t> Photon_hoe = {fReader_2022, "Photon_hoe"};
  TTreeReaderArray<Float_t> Photon_hoe_PUcorr = {fReader_2022, "Photon_hoe_PUcorr"};
  TTreeReaderArray<Float_t> Photon_mvaID = {fReader_2022, "Photon_mvaID"};
  TTreeReaderArray<Float_t> Photon_pfChargedIso = {fReader_2022, "Photon_pfChargedIso"};
  TTreeReaderArray<Float_t> Photon_pfChargedIsoPFPV = {fReader_2022, "Photon_pfChargedIsoPFPV"};
  TTreeReaderArray<Float_t> Photon_pfChargedIsoWorstVtx = {fReader_2022, "Photon_pfChargedIsoWorstVtx"};
  TTreeReaderArray<Float_t> Photon_pfPhoIso03 = {fReader_2022, "Photon_pfPhoIso03"};
  TTreeReaderArray<Float_t> Photon_pfRelIso03_all_quadratic = {fReader_2022, "Photon_pfRelIso03_all_quadratic"};
  TTreeReaderArray<Float_t> Photon_pfRelIso03_chg_quadratic = {fReader_2022, "Photon_pfRelIso03_chg_quadratic"};
  TTreeReaderArray<Float_t> Photon_phi = {fReader_2022, "Photon_phi"};
  TTreeReaderArray<Float_t> Photon_phiWidth = {fReader_2022, "Photon_phiWidth"};
  TTreeReaderArray<Float_t> Photon_pt = {fReader_2022, "Photon_pt"};
  TTreeReaderArray<Float_t> Photon_r9 = {fReader_2022, "Photon_r9"};
  TTreeReaderArray<Float_t> Photon_s4 = {fReader_2022, "Photon_s4"};
  TTreeReaderArray<Float_t> Photon_sieie = {fReader_2022, "Photon_sieie"};
  TTreeReaderArray<Float_t> Photon_sieip = {fReader_2022, "Photon_sieip"};
  TTreeReaderArray<Float_t> Photon_sipip = {fReader_2022, "Photon_sipip"};
  TTreeReaderArray<Float_t> Photon_trkSumPtHollowConeDR03 = {fReader_2022, "Photon_trkSumPtHollowConeDR03"};
  TTreeReaderArray<Float_t> Photon_trkSumPtSolidConeDR04 = {fReader_2022, "Photon_trkSumPtSolidConeDR04"};
  TTreeReaderArray<Float_t> Photon_x_calo = {fReader_2022, "Photon_x_calo"};
  TTreeReaderArray<Float_t> Photon_y_calo = {fReader_2022, "Photon_y_calo"};
  TTreeReaderArray<Float_t> Photon_z_calo = {fReader_2022, "Photon_z_calo"};*/

  //PuppiMET
  TTreeReaderValue<Float_t> PuppiMET_phi = {fReader_2022, "PuppiMET_phi"};
  TTreeReaderValue<Float_t> PuppiMET_phiJERDown = {fReader_2022, "PuppiMET_phiJERDown"};
  TTreeReaderValue<Float_t> PuppiMET_phiJERUp = {fReader_2022, "PuppiMET_phiJERUp"};
  TTreeReaderValue<Float_t> PuppiMET_phiJESDown = {fReader_2022, "PuppiMET_phiJESDown"};
  TTreeReaderValue<Float_t> PuppiMET_phiJESUp = {fReader_2022, "PuppiMET_phiJESUp"};
  TTreeReaderValue<Float_t> PuppiMET_phiUnclusteredDown = {fReader_2022, "PuppiMET_phiUnclusteredDown"};
  TTreeReaderValue<Float_t> PuppiMET_phiUnclusteredUp = {fReader_2022, "PuppiMET_phiUnclusteredUp"};
  TTreeReaderValue<Float_t> PuppiMET_pt = {fReader_2022, "PuppiMET_pt"};
  TTreeReaderValue<Float_t> PuppiMET_ptJERDown = {fReader_2022, "PuppiMET_ptJERDown"};
  TTreeReaderValue<Float_t> PuppiMET_ptJERUp = {fReader_2022, "PuppiMET_ptJERUp"};
  TTreeReaderValue<Float_t> PuppiMET_ptJESDown = {fReader_2022, "PuppiMET_ptJESDown"};
  TTreeReaderValue<Float_t> PuppiMET_ptJESUp = {fReader_2022, "PuppiMET_ptJESUp"};
  TTreeReaderValue<Float_t> PuppiMET_ptUnclusteredDown = {fReader_2022, "PuppiMET_ptUnclusteredDown"};
  TTreeReaderValue<Float_t> PuppiMET_ptUnclusteredUp = {fReader_2022, "PuppiMET_ptUnclusteredUp"};
  TTreeReaderValue<Float_t> PuppiMET_sumEt = {fReader_2022, "PuppiMET_sumEt"};

  //Tau
  /*
   TTreeReaderValue<iterator> nTau = {fReader_2022, "nTau"};
   TTreeReaderArray<UChar_t> Tau_decayMode = {fReader_2022, "Tau_decayMode"};
   TTreeReaderArray<Bool_t> Tau_idAntiEleDeadECal = {fReader_2022, "Tau_idAntiEleDeadECal"};
   TTreeReaderArray<UChar_t> Tau_idAntiMu = {fReader_2022, "Tau_idAntiMu"};
   TTreeReaderArray<Bool_t> Tau_idDecayModeNewDMs = {fReader_2022, "Tau_idDecayModeNewDMs"};
   TTreeReaderArray<Bool_t> Tau_idDecayModeOldDMs = {fReader_2022, "Tau_idDecayModeOldDMs"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSe = {fReader_2022, "Tau_idDeepTau2017v2p1VSe"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSjet = {fReader_2022, "Tau_idDeepTau2017v2p1VSjet"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2017v2p1VSmu = {fReader_2022, "Tau_idDeepTau2017v2p1VSmu"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2018v2p5VSe = {fReader_2022, "Tau_idDeepTau2018v2p5VSe"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2018v2p5VSjet = {fReader_2022, "Tau_idDeepTau2018v2p5VSjet"};
   TTreeReaderArray<UChar_t> Tau_idDeepTau2018v2p5VSmu = {fReader_2022, "Tau_idDeepTau2018v2p5VSmu"};
   TTreeReaderArray<UChar_t> Tau_nSVs = {fReader_2022, "Tau_nSVs"};
   TTreeReaderArray<int_or_short> Tau_charge = {fReader_2022, "Tau_charge"};
   TTreeReaderArray<Short_t> Tau_decayModePNet = {fReader_2022, "Tau_decayModePNet"};
   TTreeReaderArray<Short_t> Tau_eleIdx = {fReader_2022, "Tau_eleIdx"};
   TTreeReaderArray<Short_t> Tau_jetIdx = {fReader_2022, "Tau_jetIdx"};
   TTreeReaderArray<Short_t> Tau_muIdx = {fReader_2022, "Tau_muIdx"};
   TTreeReaderArray<Short_t> Tau_svIdx1 = {fReader_2022, "Tau_svIdx1"};
   TTreeReaderArray<Short_t> Tau_svIdx2 = {fReader_2022, "Tau_svIdx2"};
   TTreeReaderArray<Float_t> Tau_chargedIso = {fReader_2022, "Tau_chargedIso"};
   TTreeReaderArray<Float_t> Tau_dxy = {fReader_2022, "Tau_dxy"};
   TTreeReaderArray<Float_t> Tau_dz = {fReader_2022, "Tau_dz"};
   TTreeReaderArray<Float_t> Tau_eta = {fReader_2022, "Tau_eta"};
   TTreeReaderArray<Float_t> Tau_leadTkDeltaEta = {fReader_2022, "Tau_leadTkDeltaEta"};
   TTreeReaderArray<Float_t> Tau_leadTkDeltaPhi = {fReader_2022, "Tau_leadTkDeltaPhi"};
   TTreeReaderArray<Float_t> Tau_leadTkPtOverTauPt = {fReader_2022, "Tau_leadTkPtOverTauPt"};
   TTreeReaderArray<Float_t> Tau_mass = {fReader_2022, "Tau_mass"};
   TTreeReaderArray<Float_t> Tau_neutralIso = {fReader_2022, "Tau_neutralIso"};
   TTreeReaderArray<Float_t> Tau_phi = {fReader_2022, "Tau_phi"};
   TTreeReaderArray<Float_t> Tau_photonsOutsideSignalCone = {fReader_2022, "Tau_photonsOutsideSignalCone"};
   TTreeReaderArray<Float_t> Tau_probDM0PNet = {fReader_2022, "Tau_probDM0PNet"};
   TTreeReaderArray<Float_t> Tau_probDM10PNet = {fReader_2022, "Tau_probDM10PNet"};
   TTreeReaderArray<Float_t> Tau_probDM11PNet = {fReader_2022, "Tau_probDM11PNet"};
   TTreeReaderArray<Float_t> Tau_probDM1PNet = {fReader_2022, "Tau_probDM1PNet"};
   TTreeReaderArray<Float_t> Tau_probDM2PNet = {fReader_2022, "Tau_probDM2PNet"};
   TTreeReaderArray<Float_t> Tau_pt = {fReader_2022, "Tau_pt"};
   TTreeReaderArray<Float_t> Tau_ptCorrPNet = {fReader_2022, "Tau_ptCorrPNet"};
   TTreeReaderArray<Float_t> Tau_puCorr = {fReader_2022, "Tau_puCorr"};
   TTreeReaderArray<Float_t> Tau_qConfPNet = {fReader_2022, "Tau_qConfPNet"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2017v2p1VSe = {fReader_2022, "Tau_rawDeepTau2017v2p1VSe"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2017v2p1VSjet = {fReader_2022, "Tau_rawDeepTau2017v2p1VSjet"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2017v2p1VSmu = {fReader_2022, "Tau_rawDeepTau2017v2p1VSmu"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2018v2p5VSe = {fReader_2022, "Tau_rawDeepTau2018v2p5VSe"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2018v2p5VSjet = {fReader_2022, "Tau_rawDeepTau2018v2p5VSjet"};
   TTreeReaderArray<Float_t> Tau_rawDeepTau2018v2p5VSmu = {fReader_2022, "Tau_rawDeepTau2018v2p5VSmu"};
   TTreeReaderArray<Float_t> Tau_rawIso = {fReader_2022, "Tau_rawIso"};
   TTreeReaderArray<Float_t> Tau_rawIsodR03 = {fReader_2022, "Tau_rawIsodR03"};
   TTreeReaderArray<Float_t> Tau_rawPNetVSe = {fReader_2022, "Tau_rawPNetVSe"};
   TTreeReaderArray<Float_t> Tau_rawPNetVSjet = {fReader_2022, "Tau_rawPNetVSjet"};
   TTreeReaderArray<Float_t> Tau_rawPNetVSmu = {fReader_2022, "Tau_rawPNetVSmu"};
  */
  /*
  //TrigObj
  TTreeReaderValue<iterator> nTrigObj = {fReader_2022, "nTrigObj"};
  TTreeReaderArray<int_or_short> TrigObj_l1charge = {fReader_2022, "TrigObj_l1charge"};
  TTreeReaderArray<int_or_ushort> TrigObj_id = {fReader_2022, "TrigObj_id"};
  TTreeReaderArray<Int_t> TrigObj_l1iso = {fReader_2022, "TrigObj_l1iso"};
  TTreeReaderArray<Int_t> TrigObj_filterBits = {fReader_2022, "TrigObj_filterBits"};
  TTreeReaderArray<Float_t> TrigObj_pt = {fReader_2022, "TrigObj_pt"};
  TTreeReaderArray<Float_t> TrigObj_eta = {fReader_2022, "TrigObj_eta"};
  TTreeReaderArray<Float_t> TrigObj_phi = {fReader_2022, "TrigObj_phi"};
  TTreeReaderArray<Float_t> TrigObj_l1pt = {fReader_2022, "TrigObj_l1pt"};
  TTreeReaderArray<Float_t> TrigObj_l1pt_2 = {fReader_2022, "TrigObj_l1pt_2"};
  TTreeReaderArray<Float_t> TrigObj_l2pt = {fReader_2022, "TrigObj_l2pt"};*/

  //Flags
  TTreeReaderValue<Bool_t> Flag_HBHENoiseFilter = {fReader_2022, "Flag_HBHENoiseFilter"};
  TTreeReaderValue<Bool_t> Flag_HBHENoiseIsoFilter = {fReader_2022, "Flag_HBHENoiseIsoFilter"};
  TTreeReaderValue<Bool_t> Flag_CSCTightHaloFilter = {fReader_2022, "Flag_CSCTightHaloFilter"};
  TTreeReaderValue<Bool_t> Flag_CSCTightHaloTrkMuUnvetoFilter = {fReader_2022, "Flag_CSCTightHaloTrkMuUnvetoFilter"};
  TTreeReaderValue<Bool_t> Flag_CSCTightHalo2015Filter = {fReader_2022, "Flag_CSCTightHalo2015Filter"};
  TTreeReaderValue<Bool_t> Flag_globalTightHalo2016Filter = {fReader_2022, "Flag_globalTightHalo2016Filter"};
  TTreeReaderValue<Bool_t> Flag_globalSuperTightHalo2016Filter = {fReader_2022, "Flag_globalSuperTightHalo2016Filter"};
  TTreeReaderValue<Bool_t> Flag_HcalStripHaloFilter = {fReader_2022, "Flag_HcalStripHaloFilter"};
  TTreeReaderValue<Bool_t> Flag_hcalLaserEventFilter = {fReader_2022, "Flag_hcalLaserEventFilter"};
  TTreeReaderValue<Bool_t> Flag_EcalDeadCellTriggerPrimitiveFilter = {fReader_2022, "Flag_EcalDeadCellTriggerPrimitiveFilter"};
  TTreeReaderValue<Bool_t> Flag_EcalDeadCellBoundaryEnergyFilter = {fReader_2022, "Flag_EcalDeadCellBoundaryEnergyFilter"};
  TTreeReaderValue<Bool_t> Flag_ecalBadCalibFilter = {fReader_2022, "Flag_ecalBadCalibFilter"};
  TTreeReaderValue<Bool_t> Flag_goodVertices = {fReader_2022, "Flag_goodVertices"};
  TTreeReaderValue<Bool_t> Flag_eeBadScFilter = {fReader_2022, "Flag_eeBadScFilter"};
  TTreeReaderValue<Bool_t> Flag_ecalLaserCorrFilter = {fReader_2022, "Flag_ecalLaserCorrFilter"};
  TTreeReaderValue<Bool_t> Flag_trkPOGFilters = {fReader_2022, "Flag_trkPOGFilters"};
  TTreeReaderValue<Bool_t> Flag_chargedHadronTrackResolutionFilter = {fReader_2022, "Flag_chargedHadronTrackResolutionFilter"};
  TTreeReaderValue<Bool_t> Flag_muonBadTrackFilter = {fReader_2022, "Flag_muonBadTrackFilter"};
  TTreeReaderValue<Bool_t> Flag_BadChargedCandidateFilter = {fReader_2022, "Flag_BadChargedCandidateFilter"};
  TTreeReaderValue<Bool_t> Flag_BadPFMuonFilter = {fReader_2022, "Flag_BadPFMuonFilter"};
  TTreeReaderValue<Bool_t> Flag_BadPFMuonDzFilter = {fReader_2022, "Flag_BadPFMuonDzFilter"};
  TTreeReaderValue<Bool_t> Flag_hfNoisyHitsFilter = {fReader_2022, "Flag_hfNoisyHitsFilter"};
  TTreeReaderValue<Bool_t> Flag_BadChargedCandidateSummer16Filter = {fReader_2022, "Flag_BadChargedCandidateSummer16Filter"};
  TTreeReaderValue<Bool_t> Flag_BadPFMuonSummer16Filter = {fReader_2022, "Flag_BadPFMuonSummer16Filter"};
  TTreeReaderValue<Bool_t> Flag_trkPOG_manystripclus53X = {fReader_2022, "Flag_trkPOG_manystripclus53X"};
  TTreeReaderValue<Bool_t> Flag_trkPOG_toomanystripclus53X = {fReader_2022, "Flag_trkPOG_toomanystripclus53X"};
  TTreeReaderValue<Bool_t> Flag_trkPOG_logErrorTooManyClusters = {fReader_2022, "Flag_trkPOG_logErrorTooManyClusters"};
  TTreeReaderValue<Bool_t> Flag_METFilters = {fReader_2022, "Flag_METFilters"};
  /*
  //Rho (Run-3)
  TTreeReaderValue<Float_t> Rho_fixedGridRhoAll = {fReader_2022, "Rho_fixedGridRhoAll"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetAll = {fReader_2022, "Rho_fixedGridRhoFastjetAll"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentral = {fReader_2022, "Rho_fixedGridRhoFastjetCentral"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentralCalo = {fReader_2022, "Rho_fixedGridRhoFastjetCentralCalo"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentralChargedPileUp = {fReader_2022, "Rho_fixedGridRhoFastjetCentralChargedPileUp"};
  TTreeReaderValue<Float_t> Rho_fixedGridRhoFastjetCentralNeutral = {fReader_2022, "Rho_fixedGridRhoFastjetCentralNeutral"};*/

  //Rho (Run-2)
  TTreeReaderValue<Float_t> fixedGridRhoFastjetAll =            {fReader_2022, "fixedGridRhoFastjetAll"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentral =        {fReader_2022, "fixedGridRhoFastjetCentral"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentralCalo =    {fReader_2022, "fixedGridRhoFastjetCentralCalo"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentralChargedPileUp = {fReader_2022, "fixedGridRhoFastjetCentralChargedPileUp"};
  TTreeReaderValue<Float_t> fixedGridRhoFastjetCentralNeutral = {fReader_2022, "fixedGridRhoFastjetCentralNeutral"};
  //TTreeReaderArray<Float_t> Photon_pfRelIso03_all = {fReader_2022, "Photon_pfRelIso03_all"};
  //TTreeReaderArray<Float_t> Photon_pfRelIso03_chg = {fReader_2022, "Photon_pfRelIso03_chg"};
  TTreeReaderValue<Float_t> rho = fixedGridRhoFastjetAll;

  //HLT paths
  //TTreeReaderValue<Bool_t> HLT_Ele27_WPTight_Gsf = {fReader_2022, "HLT_Ele27_WPTight_Gsf"};
  //TTreeReaderValue<Bool_t> HLT_Ele28_WPTight_Gsf = {fReader_2022, "HLT_Ele28_WPTight_Gsf"};
  //TTreeReaderValue<Bool_t> HLT_Ele30_WPTight_Gsf = {fReader_2022, "HLT_Ele30_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_Ele32_WPTight_Gsf = {fReader_2022, "HLT_Ele32_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_Ele35_WPTight_Gsf = {fReader_2022, "HLT_Ele35_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_Ele38_WPTight_Gsf = {fReader_2022, "HLT_Ele38_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_Ele40_WPTight_Gsf = {fReader_2022, "HLT_Ele40_WPTight_Gsf"};
  TTreeReaderValue<Bool_t> HLT_IsoMu20 = {fReader_2022, "HLT_IsoMu20"};
  TTreeReaderValue<Bool_t> HLT_IsoMu24 = {fReader_2022, "HLT_IsoMu24"};
  TTreeReaderValue<Bool_t> HLT_IsoMu24_eta2p1 = {fReader_2022, "HLT_IsoMu24_eta2p1"};
  TTreeReaderValue<Bool_t> HLT_IsoMu27 = {fReader_2022, "HLT_IsoMu27"};

  // HLT paths that I am interested in:
  // For 2018 and 2022 and 2023:
  TTreeReaderValue<Bool_t> HLT_SingleMuon  = {fReader_2022, "HLT_IsoMu24"};
  TTreeReaderValue<Bool_t> HLT_SingleEle   = {fReader_2022, "HLT_Ele32_WPTight_Gsf"};

  //--------------------
  // Gen-level branches:
  //--------------------

  //GenJet:
  TTreeReaderValue<iterator> nGenJet = {fReader_2022MC, "nGenJet"};
  TTreeReaderArray<Float_t> GenJet_eta = {fReader_2022MC, "GenJet_eta"};
  TTreeReaderArray<Float_t> GenJet_mass = {fReader_2022MC, "GenJet_mass"};
  TTreeReaderArray<Float_t> GenJet_phi = {fReader_2022MC, "GenJet_phi"};
  TTreeReaderArray<Float_t> GenJet_pt = {fReader_2022MC, "GenJet_pt"};

  //GenPart:
  TTreeReaderValue<iterator> nGenPart = {fReader_2022MC, "nGenPart"};
  TTreeReaderArray<int_or_short> GenPart_genPartIdxMother = {fReader_2022MC, "GenPart_genPartIdxMother"};
  TTreeReaderArray<int_or_ushort> GenPart_statusFlags = {fReader_2022MC, "GenPart_statusFlags"};
  TTreeReaderArray<Int_t> GenPart_pdgId = {fReader_2022MC, "GenPart_pdgId"};
  TTreeReaderArray<Int_t> GenPart_status = {fReader_2022MC, "GenPart_status"};
  TTreeReaderArray<Float_t> GenPart_eta = {fReader_2022MC, "GenPart_eta"};
  TTreeReaderArray<Float_t> GenPart_mass = {fReader_2022MC, "GenPart_mass"};
  TTreeReaderArray<Float_t> GenPart_phi = {fReader_2022MC, "GenPart_phi"};
  TTreeReaderArray<Float_t> GenPart_pt = {fReader_2022MC, "GenPart_pt"};

  //GenWeights:
  TTreeReaderValue<Float_t> Generator_weight = {fReader_2022MC, "Generator_weight"};
  TTreeReaderValue<Float_t> genWeight = {fReader_2022MC, "genWeight"};
  /*
  TTreeReaderValue<Float_t> LHEWeight_originalXWGTUP = {fReader_2022MC, "LHEWeight_originalXWGTUP"};
  TTreeReaderValue<iterator> nLHEPdfWeight = {fReader_2022MC, "nLHEPdfWeight"};
  TTreeReaderArray<Float_t> LHEPdfWeight = {fReader_2022MC, "LHEPdfWeight"};
  TTreeReaderValue<iterator> nLHEReweightingWeight = {fReader_2022MC, "nLHEReweightingWeight"};
  TTreeReaderArray<Float_t> LHEReweightingWeight = {fReader_2022MC, "LHEReweightingWeight"};
  TTreeReaderValue<iterator> nLHEScaleWeight = {fReader_2022MC, "nLHEScaleWeight"};
  TTreeReaderArray<Float_t> LHEScaleWeight = {fReader_2022MC, "LHEScaleWeight"};
  TTreeReaderValue<iterator> nPSWeight = {fReader_2022MC, "nPSWeight"};
  TTreeReaderArray<Float_t> PSWeight = {fReader_2022MC, "PSWeight"};*/

  //GenMET
  TTreeReaderValue<Float_t> GenMET_phi = {fReader_2022MC, "GenMET_phi"};
  TTreeReaderValue<Float_t> GenMET_pt = {fReader_2022MC, "GenMET_pt"};

  //PileUP
  TTreeReaderValue<Int_t> Pileup_nPU = {fReader_2022MC, "Pileup_nPU"};
  TTreeReaderValue<Int_t> Pileup_sumEOOT = {fReader_2022MC, "Pileup_sumEOOT"};
  TTreeReaderValue<Int_t> Pileup_sumLOOT = {fReader_2022MC, "Pileup_sumLOOT"};
  TTreeReaderValue<Float_t> Pileup_nTrueInt = {fReader_2022MC, "Pileup_nTrueInt"};
  TTreeReaderValue<Float_t> Pileup_pudensity = {fReader_2022MC, "Pileup_pudensity"};
  TTreeReaderValue<Float_t> Pileup_gpudensity = {fReader_2022MC, "Pileup_gpudensity"};

  //Jetflavor:
  TTreeReaderArray<int_or_char> Jet_hadronFlavour = {fReader_2022MC, "Jet_hadronFlavour"};
  TTreeReaderArray<int_or_char> FatJet_hadronFlavour = {fReader_2022MC, "FatJet_hadronFlavour"};
  
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
  void SortPt(vector<Particle> part);

  //Others:
  float delta_phi(float phi1, float phi2);
  int  MotherID(int partindex, int momindex);
  float transv_mass(float lepE, float lepphi, float met, float metphi);
  bool clean_from_array(Particle target, vector<Particle> array, float dRcut);
  bool isMatchingWithGen(Particle reco, vector<Particle> gencollection);

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
  int nEvtTotal, nEvtRan, nEvtTrigger, nEvtPass, nEvtBad, nThrown, nEvtVeto;
  float genEventsumw;
  time_t start, end, buffer;
  
  ClassDef(AnaScript,0);

};

#endif

#ifdef AnaScript_cxx
void AnaScript::Init(TTree *tree)
{
  fReader_2022.SetTree(tree);
  fReader_2022MC.SetTree(tree);
  if(_data == 0) fReader_2022MC.SetTree(tree);

  //For skimmer
  _SkimFile = new TFile(_SkimFileName,"recreate");
  skimTree = tree->CloneTree(0);
}

Bool_t AnaScript::Notify()
{
  return kTRUE;
}


#endif // #ifdef AnaScript_cxx
