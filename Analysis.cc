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
  double purity = 0.9678;
  double acceptance = AccWeight(pt,eta,H_acc);
  double efficiency = EffWeight(pt,eta,H_eff);
  double thxsec = XsecWeight(pt,h_xsec);
  double thewk = EwkWeight(pt,h_ewk) ;
  
  wgt=purity*thxsec*thewk/(acceptance*efficiency);
  //if(pt>400&&pt<500&&acceptance <0.6)std::cout<< " pt: "<<pt<<" eta: "<<eta<<" purity: " <<purity<< " acceptance: " <<acceptance<<" Efficiency: " <<efficiency<< " xsec: " <<thxsec<< "   ewk: "<<thewk<<"  wgt: "<<wgt<<std::endl;
 
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





void Analysis::Loop(bool isMC)
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
  TH1F* h_phmet = new TH1F("h_phmet", "h_phmet",12,metbin );
  h_phmet->Sumw2();
  
  TH1F* h_phmetW = new TH1F("h_phmetW", "h_phmetW",12,metbin );
  h_phmetW->Sumw2();

  TH1F* h_pfmet = new TH1F("h_pfmet", "h_pfmet",12,metbin );
  h_pfmet->Sumw2();

  //photons
  TH1F* h_phpt = new TH1F("h_phpt", "h_phpt",12,metbin );
  h_phpt->Sumw2();
  
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

  TH1F* counter_all = new TH1F("counter_all", "counter_all", 40,100.,1000.);
  counter_all->Sumw2();
  TH1F* counter_atleastonephoton= new TH1F("counter_atleastonephoton", "counter_atleastonephoton",40,100,1000);
  counter_atleastonephoton->Sumw2();
  TH1F* counter_triggerOK= new TH1F("counter_triggerOK", "counter_triggerOK",40,100,1000);
  counter_triggerOK->Sumw2();
  TH1F* counter_passed = new TH1F("counter_passed", "counter_passed", 40,100.,1000.);
  counter_passed->Sumw2();

  double etabin [7] = {0., 1., 1.479,2., 2.2, 2.3,4.};
  double ptbin[13] = {100, 150, 175, 200, 225, 250, 275, 300, 350, 400, 450, 500, 1000};
  TH2F* h2_Acc = new TH2F("h2_Acc","h2_Acc",6, etabin, 12, ptbin);
  h2_Acc ->Sumw2();
  TH2F* h2_Eff = new TH2F("h2_Eff","h2_Eff",6, etabin, 12, ptbin);
  h2_Eff ->Sumw2();
  TH2F* h2_den = new TH2F("h2_den","h2_den",6, etabin, 12, ptbin);
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
 

  
  TFile* f_xsec = TFile::Open("rootfiles/Photon_Z_NLO_kfactors.root");
  TH1F* h_xsec = (TH1F*)f_xsec->Get("Z_pho_NLO");
  TH1F* h_ewk = (TH1F*)f_xsec->Get("EWK_Dwon");

  double count250300W=0;
  double count300350W=0;
  double count350400W=0;
  double count400500W=0;

  double count400500=0;

  TFile* f_out;
 
  if(isMC) f_out = new TFile("histos_GJets_MC.root", "RECREATE");
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
    
     
      //apply g+jets control sample selection   
      double deltaPhi12 = deltaPhi(signaljetphi,secondjetphi);
      bool phetaOK = (abs(pheta)<1.4442 || (abs(pheta)>1.566 && abs(pheta)<2.5));
      bool genphetaOK = (abs(wzeta)<1.4442 || (abs(wzeta)>1.566 && abs(wzeta)<2.5));
      bool isGJetOK =((signaljetpt>110 && abs(signaljeteta)<2.4 && njets==1) || (signaljetpt>110 && abs(signaljeteta)<2.4 && deltaPhi12 < 2.5 &&  secondjetpt>30 && abs(secondjeteta)<4.5 && njets==2)); 
   //bool isGJetOK =(signaljetpt>110 && abs(signaljeteta)<2.4 && njets<3); 
      //if(isGJetOK) 
      h2_den->Fill(wzeta,wzpt,weight);
      if(isGJetOK && wzpt>160 && genphetaOK)h2_Acc->Fill(wzeta,wzpt,weight);
      
      bool isPhotonOK;
      isPhotonOK= phpt>160 && phetaOK && (hltphoton150||hltphoton135)&& ntightphotons==1&&isGJetOK;
      //if(!isMC) isPhotonOK= phpt>170 && phetaOK && (hltphoton150||hltphoton135)&& nphotons==1&&isGJetOK;

        
      if(isPhotonOK){
	h_nvtx->Fill(nvtx, weight);
	h_nph->Fill(nphotons, weight);
	h_phpt->Fill(phpt, weight);
	h_pheta->Fill(pheta, weight);    
	h_deltaPhi12 ->Fill(deltaPhi12,weight);	
	h_1jetpt ->Fill(signaljetpt,weight);
	h_2jetpt ->Fill(secondjetpt,weight);
	h_1jeteta ->Fill(signaljeteta,weight);
	h_2jeteta ->Fill(secondjeteta,weight);
	h_njet->Fill(njets, weight);
	h_phmet->Fill(phmet, weight);
	h_pfmet->Fill(pfmet, weight);
	if(isMC &&wzpt>160 &&  genphetaOK)	h2_Eff->Fill(pheta,phpt,weight);
	double znunuweight= ZnunuWeight(phpt,pheta,H_eff,H_acc,h_xsec, h_ewk);
	//	std::cout<<weight<<"   "<<znunuweight<<std::endl;
	if(znunuweight>0 && znunuweight < 1000.){
	  h_phmetW->Fill(phmet, weight*znunuweight);
	  if(t1phmet>=400&&t1phmet<=500){
	    count400500+=weight;
	    count400500W+=znunuweight*weight;
	    h_znunuW->Fill(znunuweight);
	    h_effW->Fill(EffWeight(phpt,pheta,H_eff));
	    //   if(AccWeight(phpt,pheta,H_acc)<0.6)std::cout<<pfmet<<"  "<<phmet<<"  "<<phpt<<"  "<<pheta<<std::endl;
	    h_accW->Fill(AccWeight(phpt,pheta,H_acc));
	    h_xsecW->Fill(XsecWeight(phpt,h_xsec));
	    h_ewkW->Fill(EwkWeight(phpt,h_ewk));
	  }
	  if(t1phmet>=250&&t1phmet<=300){
	    count250300W+=znunuweight*weight;
	  }
	  if(t1phmet>=300&&t1phmet<=350){
	    count300350W+=znunuweight*weight;
	  }
	  if(t1phmet>=350&&t1phmet<=400){
	    count350400W+=znunuweight*weight;
	  }

	}
      }

     
    
   }


   std::cout<<count250300W<< " count250300W " << std::endl;
   std::cout<<count300350W<< " count300350W " << std::endl;
   std::cout<<count350400W<< " count350400W " << std::endl;
   std::cout<<count400500W<< " count400500W " << std::endl;

   std::cout<<count400500<<std::endl;
   f_out->cd();
 
   h_nvtx->Write();
   h_nph->Write();
   h_phpt->Write();
   h_pheta->Write();    
   h_deltaPhi12 ->Write();
   h_1jetpt -> Write();
   h_2jetpt -> Write();
   h_1jeteta -> Write();
   h_2jeteta -> Write();
   h_njet-> Write();
   h_phmet->Write();
   h_phmetW->Write();
   h_znunuW->Write();
   h_effW->Write();
   h_accW->Write();
   h_xsecW->Write();
   h_ewkW->Write();
   h_pfmet->Write();
   counter_all->Write();
   counter_atleastonephoton->Write();
   counter_triggerOK->Write();
   counter_passed->Write();
   h2_Acc->Write();
   h2_Eff->Write();
   h2_den->Write();

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
