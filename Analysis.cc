#define Analysis_cxx
#include "Analysis.h"
#include "TLorentzVector.h"
#include"TPaveText.h"
#include "TChain.h"
#include "TH1F.h"
#include <vector>
#include <cmath>
#include "TFile.h"
#include "TLegend.h"
#include "TPad.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TStyle.h"
#include <stdio.h>
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "THStack.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TColor.h"
#include "TLatex.h"
double Analysis::deltaPhi(double phi1, double phi2) { 
  double pi = 3.1415926535;
  double result = phi1 - phi2;
  while (result > pi) result -= 2*pi;
  while (result <= -pi) result += 2*pi;
  return result;
}

double Analysis::ZnunuWeight(double pt, double eta,TH2F* H_eff,TH2F* H_acc,TH1F* h_xsec, TH1F* h_ewk){
  double wgt = 1;
  double purity = 1.;
  double acceptance = AccWeight(pt,eta,H_acc);
  double efficiency = EffWeight(pt,eta,H_eff);
  double thxsec = XsecWeight(pt,h_xsec);
  double thewk = 1.;//EwkWeight(pt,h_ewk) ;
  
  wgt=thxsec; //purity*thxsec*thewk/(acceptance*efficiency);
  //std::cout<< " pt: "<<pt<<" eta: "<<eta<<" purity: " <<purity<< " acceptance: " <<acceptance<<" Efficiency: " <<efficiency<< " xsec: " <<thxsec<< "   ewk: "<<thewk<<"  wgt: "<<wgt<<std::endl;
  //std::cout<<wgt<<" znunu"<<std::endl;
  return wgt;
}


double Analysis::EwkWeight(double pt, TH1F* h_ewk){
  double wgt = 1;
  double thewk = h_ewk->GetBinContent(h_ewk->FindBin(pt));
  wgt=thewk; 
  return wgt;
}


double Analysis::XsecWeight(double pt, TH1F* h_xsec){
  double wgt = 1;
  double thxsec = h_xsec->GetBinContent(h_xsec->FindBin(pt));
  wgt=thxsec;
  // std::cout<<wgt<<" xsec"<<std::endl;
  return wgt;
}


double Analysis::EffWeight(double pt, double eta,TH2F* H_eff){
  double wgt = 1; 
  double efficiency = H_eff->GetBinContent(H_eff->FindBin(abs(eta), pt));
  wgt=efficiency;
   return wgt;
}

double Analysis::AccWeight(double pt, double eta,TH2F* H_acc){
  double wgt = 1; 
  double acceptance = H_acc->GetBinContent(H_acc->FindBin(abs(eta), pt));
  wgt=acceptance;
   return 1;
}





void Analysis::Loop(bool isMC,std::string name)
{

  TH1F* h_nvtx = new TH1F("h_nvtx", "h_nvtx", 50,0.,50.);
  h_nvtx->Sumw2();

  //weights
  TH1F* h_znunuW = new TH1F("h_znunuW", "h_znunuW", 20, 0., 2);
  h_znunuW->Sumw2();
  TH1F* h_effW = new TH1F("h_effW", "h_effW", 20, 0., 1);
  h_effW->Sumw2();
  TH1F* h_accW = new TH1F("h_accW", "h_accW", 20, 0., 1);
  h_accW->Sumw2();
  TH1F* h_xsecW = new TH1F("h_xsecW", "h_xsecW", 20, 0., 1);
  h_xsecW->Sumw2();
  TH1F* h_ewkW = new TH1F("h_ewkW", "h_ewkW", 20, 0., 1);
  h_ewkW->Sumw2();


  //met
  double metbin[13] = {100, 150, 175, 200, 225, 250, 275, 300, 350, 400, 450, 500, 1000};
  double ptbin[11] = {100, 175, 200, 225, 250, 275, 300, 350, 400, 550, 1200};
  TH1F* h_phmetLogX = new TH1F("h_phmetLogX", "h_phmetLogX",10,ptbin );
  h_phmetLogX->Sumw2();
  
  TH1F* h_phmet = new TH1F("h_phmet", "h_phmet",320,0,1000 );
  h_phmet->Sumw2();
  TH1F* h_t1phmet = new TH1F("h_t1phmet", "h_t1phmet",320,0,1000 );
  h_t1phmet->Sumw2();
  TH1F* h_t1phmetLivia = new TH1F("h_t1phmetLivia", "h_t1phmetLivia",320,0,1000 );
  h_t1phmetLivia->Sumw2();
  TH1F* h_pfmet = new TH1F("h_pfmet", "h_pfmet",320, 0, 1000 );
  h_pfmet->Sumw2();
  TH1F* h_pfmetLivia = new TH1F("h_pfmetLivia", "h_pfmetLivia",320, 0, 1000 );
  h_pfmetLivia->Sumw2();
  TH1F* h_t1pfmet = new TH1F("h_t1pfmet", "h_t1pfmet",320, 0, 1000 );
  h_t1pfmet->Sumw2();
  TH1F* h_t1pfmetLivia = new TH1F("h_t1pfmetLivia", "h_t1pfmetLivia",320, 0, 1000 );
  h_t1pfmetLivia->Sumw2();
  
  TH1F* h_phmetW = new TH1F("h_phmetW", "h_phmetW",320, 0,1000);
  h_phmetW->Sumw2();

  

  //photons
  TH1F* h_phpt = new TH1F("h_phpt", "h_phpt",12,metbin );
  h_phpt->Sumw2();
  TH1F* h_phptLinX = new TH1F("h_phptLinX", "h_phptLinX",120, 0, 1000 );
  h_phptLinX->Sumw2();
  
  TH1F* h_pheta = new TH1F("h_pheta", "h_pheta", 30, -3.,3.);
  h_pheta->Sumw2();
 
  TH1F* h_nph = new TH1F("h_nph", "h_nph", 10,0.,10.);
  h_nph->Sumw2();

  //jets
  TH1F* h_1jetpt = new TH1F("h_1jetpt", "h_1jetpt", 120,0.,1000.);
  h_1jetpt->Sumw2();

  TH1F* h_2jetpt = new TH1F("h_2jetpt", "h_2jetpt", 120,0.,1000.);
  h_2jetpt->Sumw2();

  TH1F* h_1jeteta = new TH1F("h_1jeteta", "h_1jeteta", 30, -3.,3.);
  h_1jeteta->Sumw2();

  TH1F* h_2jeteta = new TH1F("h_2jeteta", "h_2jeteta", 30,-3.,3.);
  h_2jeteta->Sumw2();

  TH1F* h_njet = new TH1F("h_njet", "h_njet", 10,0.,10.);
  h_njet->Sumw2();

  TH1F* h_deltaPhi12 = new TH1F("h_deltaPhi12", "h_deltaPhi12", 10,0.,10.);
  h_deltaPhi12->Sumw2();


  TH1F* h_deltaRjet1 = new TH1F("h_deltaRjet1", "h_deltaRjet1", 10,0.,5.);
  h_deltaRjet1->Sumw2();
   TH1F* h_deltaRjet2 = new TH1F("h_deltaRjet2", "h_deltaRjet2", 10,0.,5.);
  h_deltaRjet2->Sumw2();
   TH1F* h_deltaRjet3 = new TH1F("h_deltaRjet3", "h_deltaRjet3", 10,0.,5.);
  h_deltaRjet3->Sumw2();
  


  TH1F* counter_all = new TH1F("counter_all", "counter_all", 40,100.,1000.);
  counter_all->Sumw2();
  TH1F* counter_atleastonephoton= new TH1F("counter_atleastonephoton", "counter_atleastonephoton",40,100,1000);
  counter_atleastonephoton->Sumw2();
  TH1F* counter_triggerOK= new TH1F("counter_triggerOK", "counter_triggerOK",40,100,1000);
  counter_triggerOK->Sumw2();
  TH1F* counter_passed = new TH1F("counter_passed", "counter_passed", 40,100.,1000.);
  counter_passed->Sumw2();

  double etabin [7] = {0., 1., 1.479,2., 2.2, 2.3,4.};
  
  TH2F* h2_Acc = new TH2F("h2_Acc","h2_Acc",6, etabin, 10, ptbin);
  h2_Acc ->Sumw2();
  TH2F* h2_Eff = new TH2F("h2_Eff","h2_Eff",6, etabin, 10, ptbin);
  h2_Eff ->Sumw2();
  TH2F* h2_den = new TH2F("h2_den","h2_den",6, etabin, 10, ptbin);
  h2_den ->Sumw2();



  //book histos to compute weights
  TFile* f_eff = TFile::Open("rootfiles/effAcc.root");
  TH2F* num_eff = (TH2F*)f_eff->Get("h2_Eff");
  TH2F* den_eff = (TH2F*)f_eff->Get("h2_Acc");
  TH2F* H_eff =(TH2F*) num_eff->Clone();
  H_eff->Divide(den_eff);

  TH2F* num_acc = (TH2F*)f_eff->Get("h2_Acc");
  TH2F* den_acc = (TH2F*)f_eff->Get("h2_den");
  TH2F* H_acc =(TH2F*) num_acc->Clone();
  H_acc->Divide(den_acc);
 

  
  TFile* f_xsec1 = TFile::Open("rootfiles/Photon_Z_NLO_kfactors.root");
  // TH1F* h_xsecNLO = (TH1F*)f_xsec1->Get("Z_pho_NLO");
  TH1F* h_xsecLO = (TH1F*)f_xsec1->Get("Z_pho_LO");
  TH1F* h_ewk = (TH1F*)f_xsec1->Get("EWK_Dwon");
  
  TFile* f_xsec = TFile::Open("gjetsWeights.root");
  TH1F* h_xsecNLO = (TH1F*)f_xsec->Get("ratioNLO");


  TH2D* h2_weightsLO =  new TH2D("h2_weightsLO","h2_weightsLO",10,ptbin, 60, 0., 1.);
  h2_weightsLO->Sumw2();
  TH2D* h2_weightsNLO =  new TH2D("h2_weightsNLO","h2_weightsNLO",10,ptbin, 60, 0., 1.);
  h2_weightsNLO->Sumw2();
  TH2D* h2_effs =  new TH2D("h2_effs","h2_effs",10,ptbin, 60, 0., 1.);
  h2_effs->Sumw2();
  TH2D* h2_theosLO =  new TH2D("h2_theosLO","h2_theosLO",10,ptbin, 60, 0., 1.);
  h2_theosLO->Sumw2();
  TH2D* h2_theosNLO =  new TH2D("h2_theosNLO","h2_theosNLO",10,ptbin, 60, 0., 1.);
  h2_theosNLO->Sumw2();


  TH1F* h_yield_znunu = new TH1F("h_yield_znunu","h_yield_znunu",14,0,14);
  h_yield_znunu->Sumw2();
  TH1F* h_met_znunuLogX = new TH1F("h_met_znunuLogX","h_met_znunuLogX",10,ptbin);
  h_met_znunuLogX->Sumw2();
  TH1F* h_met_znunu = new TH1F("h_met_znunu","h_met_znunu",320,0,1000);
  h_met_znunu->Sumw2();

  TH1F* h_yield_gjet = new TH1F("h_yield_gjet","h_yield_gjet",14,0,14);
  h_yield_gjet->Sumw2();

  
  TFile* f_out;
 
  if(isMC) f_out = new TFile(("histos_GJets_MC_"+name+".root").c_str(), "RECREATE");
  if(!isMC) f_out = new TFile("histos_GJets_DATA.root", "RECREATE");

  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      //  if(phpt<100)continue;
      if(jentry%10000 == 0) std::cout<<jentry<<std::endl;
   
     
      bool noiseOK = signaljetNHfrac < 0.7 && signaljetEMfrac < 0.7 && signaljetCHfrac > 0.2 && (njets < 2 || (secondjetNHfrac < 0.7 && secondjetEMfrac < 0.9));
      double deltaPhi12 = deltaPhi(signaljetphi,secondjetphi);
      bool isJetsOK =((signaljetpt>110 && abs(signaljeteta)<2.5 && njets==1) || (signaljetpt>110 && abs(signaljeteta)<2.4 && deltaPhi12 < 2.5 &&  secondjetpt>30 && abs(secondjeteta)<2.5 && njets==2));   
      bool phetaOK = (abs(pheta)<1.4442 || (abs(pheta)>1.566 && abs(pheta)<2.5));     
      bool isPhotonOK;
     isPhotonOK= phpt>160 && phetaOK && (hltphoton150||hltphoton135)&& ntightphotons==1;
     double deltaRjet1 = sqrt((deltaPhi(signaljetphi,phphi))*(deltaPhi(signaljetphi,phphi))+(signaljeteta-pheta)*(signaljeteta-pheta));

     double deltaRjet2 = sqrt((deltaPhi(secondjetphi,phphi))*(deltaPhi(secondjetphi,phphi))+(secondjeteta-pheta)*(secondjeteta-pheta));
     double deltaRjet3 = sqrt((deltaPhi(thirdjetphi,phphi))*(deltaPhi(thirdjetphi,phphi))+(thirdjeteta-pheta)*(thirdjeteta-pheta));

     if(ntightphotons==1&&(deltaRjet1<0.5 || deltaRjet2<0.5 || deltaRjet3<0.5)) std::cout<<deltaRjet1<<"  "<<deltaRjet2<<" "<<deltaRjet3<<" "<<phpt<<" "<<pheta<<" "<<phphi<<std::endl;
     h_deltaRjet1->Fill(deltaRjet1,weight);
     h_deltaRjet2->Fill(deltaRjet2,weight);
     h_deltaRjet3->Fill(deltaRjet3,weight);
      
      //computing Znunu Yield
      if((hltmet120||hltmet95jet80||hltmet105jet80)) h_yield_znunu->Fill(0.5, weight);
      if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>200) h_yield_znunu->Fill(1.5, weight);
      if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>200&&noiseOK) h_yield_znunu->Fill(2.5, weight);     
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=200&&noiseOK&&isJetsOK) h_yield_znunu->Fill(3.5, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=200&&noiseOK&&isJetsOK&&nmuons==0) h_yield_znunu->Fill(4.5, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=200&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0) h_yield_znunu->Fill(5.5, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=200&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0) h_yield_znunu->Fill(6.5, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=250&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0) h_yield_znunu->Fill(7.5, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=300&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0) h_yield_znunu->Fill(8.5, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=350&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0) h_yield_znunu->Fill(9.5, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=400&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0) h_yield_znunu->Fill(10.5, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=450&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0) h_yield_znunu->Fill(11.5, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=500&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0) h_yield_znunu->Fill(12.5, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=550&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0) h_yield_znunu->Fill(13.5, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0) h_met_znunu->Fill(t1mumet, weight);
     if((hltmet120||hltmet95jet80||hltmet105jet80)&&t1mumet>=200&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0) h_met_znunuLogX->Fill(t1mumet, weight);
     
     //------------------------------------//

     if((hltphoton150||hltphoton135)&&isPhotonOK) h_yield_gjet->Fill(0.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=200&&isPhotonOK) h_yield_gjet->Fill(1.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=200&&noiseOK&&isPhotonOK) h_yield_gjet->Fill(2.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=200&&noiseOK&&isJetsOK&&isPhotonOK) h_yield_gjet->Fill(3.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=200&&noiseOK&&isJetsOK&&nmuons==0&&isPhotonOK) h_yield_gjet->Fill(4.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=200&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&isPhotonOK) h_yield_gjet->Fill(5.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=200&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0&&isPhotonOK) h_yield_gjet->Fill(6.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=250&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0&&isPhotonOK) h_yield_gjet->Fill(7.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=300&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0&&isPhotonOK) h_yield_gjet->Fill(8.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=350&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0&&isPhotonOK) h_yield_gjet->Fill(9.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=400&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0&&isPhotonOK) h_yield_gjet->Fill(10.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=450&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0&&isPhotonOK) h_yield_gjet->Fill(11.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=500&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0&&isPhotonOK) h_yield_gjet->Fill(12.5, weight);
     if((hltphoton150||hltphoton135)&&t1phmet>=550&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0&&isPhotonOK) h_yield_gjet->Fill(13.5, weight);
     
     //------------------//
     bool isGJetOK= isJetsOK&&noiseOK;
     if(!isGJetOK) continue;    
     h2_den->Fill(wzeta,wzpt,weight);
     bool genphetaOK = (abs(wzeta)<1.4442 || (abs(wzeta)>1.566 && abs(wzeta)<2.5));      
     if(isMC &&wzpt>160 && genphetaOK)h2_Acc->Fill(wzeta,wzpt,weight);
     if(isMC &&wzpt>160 &&  genphetaOK&&(hltphoton150||hltphoton135)&&isPhotonOK)	h2_Eff->Fill(pheta,phpt,weight);
     //-----------------//

     double znunuweightLO= ZnunuWeight(phpt,pheta,H_eff,H_acc,h_xsecLO, h_ewk);
     double znunuweightNLO= ZnunuWeight(phpt,pheta,H_eff,H_acc,h_xsecNLO, h_ewk);
     double cutMet;
     cutMet=t1phmet;
     
     if(znunuweightLO>0 && znunuweightLO < 1000.){
       if((hltphoton150||hltphoton135)&&t1phmet>=200&&noiseOK&&isJetsOK&&nmuons==0&&nelectrons==0&&ntaus==0&&isPhotonOK){
	 h_nvtx->Fill(nvtx, weight);
	 h_nph->Fill(nphotons, weight);
	 h_phpt->Fill(phpt, weight);
	 h_phptLinX->Fill(phpt, weight);
	 h_pheta->Fill(pheta, weight);    
	 h_deltaPhi12 ->Fill(deltaPhi12,weight);	
	 h_1jetpt ->Fill(signaljetpt,weight);
	 h_2jetpt ->Fill(secondjetpt,weight);
	 h_1jeteta ->Fill(signaljeteta,weight);
	 h_2jeteta ->Fill(secondjeteta,weight);
	 h_njet->Fill(njets, weight);
	 h_phmetLogX->Fill(t1phmet, weight);
	 
	 
	 double phptx=phpt*cos(phphi);
	 double phpty=phpt*sin(phphi);
	 
	 double pfmetx = pfmet*cos(pfmetphi)+phptx;
	 double pfmety = pfmet*sin(pfmetphi)+phpty;
	 double t1pfmetx = t1pfmet*cos(t1pfmetphi)+phptx;
	 double t1pfmety = t1pfmet*sin(t1pfmetphi)+phpty;
	 double pfmetLivia = sqrt(pfmetx*pfmetx+pfmety*pfmety);
	 double t1pfmetLivia = sqrt(t1pfmetx*t1pfmetx+t1pfmety*t1pfmety);
	 h_phmet->Fill(phmet, weight);
	 h_t1phmet->Fill(t1phmet, weight);
	 h_pfmet->Fill(pfmet, weight);
	 h_t1pfmet->Fill(t1pfmet, weight);
	 h_pfmetLivia->Fill(pfmetLivia, weight);
	 h_t1pfmetLivia->Fill(t1pfmetLivia, weight);


	 h_znunuW->Fill(znunuweightLO);
	 h_effW->Fill(EffWeight(phpt,pheta,H_eff));
	 h_accW->Fill(AccWeight(phpt,pheta,H_acc));
	 h_xsecW->Fill(XsecWeight(phpt,h_xsecLO));
	 h_ewkW->Fill(EwkWeight(phpt,h_ewk));
	
	 h2_weightsLO->Fill(cutMet,znunuweightLO );
	 h2_weightsNLO->Fill(cutMet,znunuweightNLO );

	 h2_effs->Fill(cutMet,EffWeight(phpt,pheta,H_eff) );
	 // std::cout<<phpt<<" "<<cutMet<<" "<< XsecWeight(phpt,h_xsec)<<" "<<znunuweight<<std::endl;
	 h2_theosLO->Fill(phpt,XsecWeight(phpt,h_xsecLO) );
	 h2_theosNLO->Fill(phpt,XsecWeight(phpt,h_xsecNLO) );
	 h_phmetW->Fill(cutMet, weight*znunuweightNLO);
	 
	 
       }
     }
     
   }	
   
      double lumi = 19.7*1.3;
     
   f_out->cd();
   h_yield_znunu->Write();
   h_yield_gjet->Write();
   h_met_znunuLogX->Write();
   h_met_znunu->Write();
   h_nvtx->Write();
   h_nph->Write();
   h_phpt->Write();
   h_phptLinX->Write();
   h_pheta->Write();    
   h_deltaPhi12 ->Write();
   h_1jetpt -> Write();
   h_2jetpt -> Write();
   h_1jeteta -> Write();
   h_2jeteta -> Write();
   h_njet-> Write();
   h_phmetLogX->Write();
   h_phmet->Write();
   h_t1phmet->Write();
   h_pfmet->Write();
   h_t1pfmet->Write();
   h_pfmetLivia->Write();
   h_t1pfmetLivia->Write();
   h_phmetW->Write();
   h_znunuW->Write();
   h_effW->Write();
   h_accW->Write();
   h_xsecW->Write();
   h_ewkW->Write();
  
   h2_effs->Write();
   h2_theosLO->Write();
   h2_theosNLO->Write();
   h2_weightsLO->Write();
   h2_weightsNLO->Write();
   counter_all->Write();
   counter_atleastonephoton->Write();
   counter_triggerOK->Write();
   counter_passed->Write();
   h2_Acc->Write();
   h2_Eff->Write();
   h2_den->Write();

   h_deltaRjet1->Write();
   h_deltaRjet2->Write();
   h_deltaRjet3->Write();

   f_out->Write();
   f_out->Close();
 
   h_nvtx->Delete();
   h_nph->Delete();
   h_phpt->Delete();
   h_pheta->Delete();    
   h_deltaPhi12 ->Delete();
   h_1jetpt -> Delete();
   h_2jetpt -> Delete();
   h_1jeteta -> Delete();
   h_2jeteta -> Delete();
   h_njet-> Delete();
 
}
