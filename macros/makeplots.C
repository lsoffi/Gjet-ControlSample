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
#include "CMS_lumi.C"
using namespace std;

void hdensity( TH1F* hout){

   
  for(int i = 1; i<=hout->GetNbinsX(); i++){
   
      double area = hout->GetBinWidth(i);
      
      hout->SetBinContent(i,(double)hout->GetBinContent(i)/area);
      hout->SetBinError(i,(double)hout->GetBinError(i)/area);

      // std::cout << "i: " << i << " j: " << j <<
        //      " val: " << hout->GetBinContent(i,j) << " area: " << area <<std::endl; 

  }

}




void CompareRatioLO(){
  TCanvas* c1 = new TCanvas("c1", "c1", 1);
  c1->cd();

  TFile* fin_mit = TFile::Open("../rootfiles/Photon_Z_NLO_kfactors.root");
  TFile* fin_gjet = TFile::Open("../histos_GJets_MC_Gjet.root");
  TFile* fin_znunu = TFile::Open("../histos_GJets_MC_Znn.root");
 
  TH1F* h_mitLO  =  (TH1F*) fin_mit->Get("Z_pho_LO");
  TH1F* h_mitNLO  =  (TH1F*) fin_mit->Get("Z_pho_NLO");
  TH1F* h_mit_ratio = h_mitNLO->Clone();
  h_mit_ratio->Divide(h_mitLO);
  TH1F* h_gjet  =  (TH1F*) fin_gjet->Get("h_phmetLogX");
  TH1F* h_znunu  =  (TH1F*) fin_znunu->Get("h_met_znunuLogX");
  TH1F* h_ratioLO = h_znunu->Clone();
  // h_gjet->Scale(1.3);
  h_ratioLO->Divide(h_gjet);
  TH1F* h_ratioNLO = h_ratioLO->Clone();
  h_ratioNLO->Multiply(h_mit_ratio);
  h_ratioNLO->SetName("ratioNLO");
  h_ratioNLO->SetTitle("ratioNLO");

  TH1F* h_weightLO = (TH1F*)(((TH2F*)fin_gjet->Get("h2_weightsLO"))->ProfileX());
  h_weightLO->SetLineColor(kRed);
  h_weightLO->SetLineWidth(2);

  TH1F* h_weightNLO = (TH1F*)(((TH2F*)fin_gjet->Get("h2_weightsNLO"))->ProfileX());
  h_weightNLO->SetLineColor(kRed);
  h_weightNLO->SetLineWidth(2);
  h_weightNLO->SetLineStyle(kDashed);

  h_ratioLO->SetLineColor(kAzure+7);
  h_ratioLO->SetLineWidth(2);
 
  h_ratioNLO->SetLineColor(kAzure+7);
  h_ratioNLO->SetLineWidth(2);
  h_ratioNLO->SetLineStyle(kDashed);


  h_mitLO->SetLineWidth(2);
  h_mitLO->SetLineColor(kBlue);
 
  h_mitNLO->SetLineColor(kBlue);
  h_mitNLO->SetLineWidth(2);
  h_mitNLO->SetLineStyle(kDashed);

  TFile* fout =  new TFile("gjetsWeights.root","RECREATE");
  fout->cd();
  h_ratioNLO->Write();
  fout->Write();
  fout->Close();

  c1->SetGrid();
  CMS_lumi( c1,true,0); 
  h_ratioLO->GetXaxis()->SetTitle("MET [GeV]");
  h_ratioLO->Draw("hist");  
  h_ratioNLO->Draw("histsame");  
  h_weightLO->Draw("histsame");
  h_weightNLO->Draw("histsame");
  h_mitLO->Draw("histsame");
  h_mitNLO->Draw("histsame");

  TLegend* legmc;
  legmc = new TLegend(0.5, 0.25, 0.82, 0.39, "", "brNDC");
  legmc->SetTextFont(42);
  legmc->SetBorderSize(0);
  legmc->SetFillStyle(0);
 
  legmc->AddEntry(h_ratioLO, "Yields Ratio LO", "L");
  legmc->AddEntry(h_ratioNLO, "Yields Ratio NLO", "L");
  legmc->AddEntry(h_mitLO, "MIT Z/#gamma LO", "L");
  legmc->AddEntry(h_mitNLO, "MIT Z/#gamma NLO", "L");
  legmc->AddEntry(h_weightLO, "R_{Z/#gamma} LO", "L");
  legmc->AddEntry(h_weightNLO, "R_{Z/#gamma} NLO", "L");
  legmc->Draw("same");
  c1->SaveAs("../plots/RatioFactor.png");
  c1->SaveAs("../plots/RatioFactor.pdf");


}



void PrintYields(){
  TCanvas* c1 = new TCanvas("c1", "c1", 1);
  c1->cd();

  TFile* fin_data = TFile::Open("../histos_GJets_DATA.root");
  TFile* fin_gjet = TFile::Open("../histos_GJets_MC_Gjet.root");
  TFile* fin_znunu = TFile::Open("../histos_GJets_MC_Znn.root");
 
  TH1F* h_data  =  (TH1F*) fin_data->Get("h_yield_gjet");
  TH1F* h_gjet  =  (TH1F*) fin_gjet->Get("h_yield_gjet");
  TH1F* h_znunu  =  (TH1F*) fin_znunu->Get("h_yield_znunu");
  h_gjet->Scale(19.7*1.3);
  h_znunu->Scale(19.7);

  //cut flow table print Gjet Yields
  std::cout<<"------------------------------------------"<<std::endl;
  std::cout<<"\\begin{table}[bthp]"<<std::endl;
  std::cout<<"\\begin{tabular}{||ccc||}"<<std::endl;
  std::cout<<"\\hline"<<std::endl;
  std::cout<<" Selection  Step \& $\\gamma$+jet DATA \& $\\gamma$+jet MC $ \\\\"<<std::endl;
  
  std::cout<< "Trigger (and PhotonOK) \&" <<h_data->GetBinContent(1)<<"\&"<<h_gjet->GetBinContent(1)<<"  \\\\"<<std::endl;
  std::cout<< "Met>200 \&"                <<h_data->GetBinContent(2)<<"\&"<<h_gjet->GetBinContent(2)<<"  \\\\"<<std::endl;
  std::cout<< "Noise OK \&"               <<h_data->GetBinContent(3)<<"\&"<<h_gjet->GetBinContent(3)<<"  \\\\"<<std::endl;
  std::cout<< "Jets OK \&"                <<h_data->GetBinContent(4)<<"\&"<<h_gjet->GetBinContent(4)<<"  \\\\"<<std::endl;
  std::cout<< "Muon Veto \&"              <<h_data->GetBinContent(5)<<"\&"<<h_gjet->GetBinContent(5)<<"  \\\\"<<std::endl;
  std::cout<< "Electron Veto \&"          <<h_data->GetBinContent(6)<<"\&"<<h_gjet->GetBinContent(6)<<"  \\\\"<<std::endl;
  std::cout<< "Tau Veto\& "               <<h_data->GetBinContent(7)<<"\&"<<h_gjet->GetBinContent(7)<<"  \\\\"<<std::endl;
  std::cout<< "Met \\geq 250 \&"          <<h_data->GetBinContent(8)<<"\&"<<h_gjet->GetBinContent(8)<<"  \\\\"<<std::endl;
  std::cout<< "Met \\geq 300 \&"          <<h_data->GetBinContent(9)<<"\&"<<h_gjet->GetBinContent(9)<<"  \\\\"<<std::endl;
  std::cout<< "Met \\geq 350 \&"          <<h_data->GetBinContent(10)<<"\&"<<h_gjet->GetBinContent(10)<< " \\\\"<<std::endl;
  std::cout<< "Met \\geq 400 \&"          <<h_data->GetBinContent(11)<<"\&"<<h_gjet->GetBinContent(11)<< " \\\\"<<std::endl;
  std::cout<< "Met \\geq 450 \&"          <<h_data->GetBinContent(12)<<"\&"<<h_gjet->GetBinContent(12)<< " \\\\"<<std::endl;
  std::cout<< "Met \\geq 500 \&"          <<h_data->GetBinContent(13)<<"\&"<<h_gjet->GetBinContent(13)<< " \\\\"<<std::endl;
  std::cout<< "Met \\geq 550 \&"          <<h_data->GetBinContent(14)<<"\&"<<h_gjet->GetBinContent(14)<< " \\\\"<<std::endl;
  std::cout<<"\\hline"<<std::endl;
  std::cout<<"\\end{tabular}\\end{table}"<<std::endl;
  std::cout<<"------------------------------------------"<<std::endl;





 //cut flow table print Gjet Yields
  std::cout<<"------------------------------------------"<<std::endl;
  std::cout<<"\\begin{table}[bthp]"<<std::endl;
  std::cout<<"\\begin{tabular}{||cc||}"<<std::endl;
  std::cout<<"\\hline"<<std::endl;
  std::cout<<" Selection  Step \&  $Z \rightarrow \nu \nu$ MC $ \\\\"<<std::endl;
  
  std::cout<< "Trigger (and PhotonOK) \&" <<h_znunu->GetBinContent(1)<<"  \\\\"<<std::endl;
  std::cout<< "Met>200 \&"                <<h_znunu->GetBinContent(2)<<"  \\\\"<<std::endl;
  std::cout<< "Noise OK \&"               <<h_znunu->GetBinContent(3)<<"  \\\\"<<std::endl;
  std::cout<< "Jets OK \&"                <<h_znunu->GetBinContent(4)<<"  \\\\"<<std::endl;
  std::cout<< "Muon Veto \&"              <<h_znunu->GetBinContent(5)<<"  \\\\"<<std::endl;
  std::cout<< "Electron Veto \&"          <<h_znunu->GetBinContent(6)<<"  \\\\"<<std::endl;
  std::cout<< "Tau Veto\& "               <<h_znunu->GetBinContent(7)<<"  \\\\"<<std::endl;
  std::cout<< "Met \\geq 250 \&"          <<h_znunu->GetBinContent(8)<<"  \\\\"<<std::endl;
  std::cout<< "Met \\geq 300 \&"          <<h_znunu->GetBinContent(9)<<"  \\\\"<<std::endl;
  std::cout<< "Met \\geq 350 \&"          <<h_znunu->GetBinContent(10)<< " \\\\"<<std::endl;
  std::cout<< "Met \\geq 400 \&"          <<h_znunu->GetBinContent(11)<< " \\\\"<<std::endl;
  std::cout<< "Met \\geq 450 \&"          <<h_znunu->GetBinContent(12)<< " \\\\"<<std::endl;
  std::cout<< "Met \\geq 500 \&"          <<h_znunu->GetBinContent(13)<< " \\\\"<<std::endl;
  std::cout<< "Met \\geq 550 \&"          <<h_znunu->GetBinContent(14)<< " \\\\"<<std::endl;
  std::cout<<"\\hline"<<std::endl;
  std::cout<<"\\end{tabular}\\end{table}"<<std::endl;
  std::cout<<"------------------------------------------"<<std::endl;


h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(0.5),"Trigger");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(1.5),"Met > 200");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(2.5),"NoiseOK");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(3.5),"JetsOK");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(4.5),"Muon Veto");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(5.5),"Electron Veto");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(6.5),"Tau Veto");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(7.5),"Met > 250 ");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(8.5),"Met > 300");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(9.5),"Met > 350");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(10.5),"Met > 400");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(11.5),"Met > 450");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(12.5),"Met > 500");
h_znunu->GetXaxis()->SetBinLabel(h_yield_znunu->FindBin(13.5),"Met > 550");

 CMS_lumi( c1,true,0);
 c1->SetLogy();
 c1->SetGrid();
 h_znunu->Draw("histe");
 c1->SaveAs("../plots/znunuYields.png");
 c1->SaveAs("../plots/znunuYields.pdf");


h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(0.5),"Trigger&&PhotonOK");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(1.5),"Met > 200");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(2.5),"NoiseOK");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(3.5),"JetsOK");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(4.5),"Muon Veto");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(5.5),"Electron Veto");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(6.5),"Tau Veto");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(7.5),"Met > 250 ");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(8.5),"Met > 300");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(9.5),"Met > 350");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(10.5),"Met > 400");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(11.5),"Met > 450");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(12.5),"Met > 500");
h_gjet->GetXaxis()->SetBinLabel(h_yield_gjet->FindBin(13.5),"Met > 550");

 h_gjet->SetLineColor(kAzure+7);
 h_gjet->SetFillColor(kAzure+6);
 h_gjet->SetLineWidth(2);
 h_gjet->Draw("hist");
 h_data->Draw("pesame");
 c1->SaveAs("../plots/gjetsYields.png");
 c1->SaveAs("../plots/gjetsYields.pdf");



 //-----------------//


  TH1F* h_data_met  =  (TH1F*) fin_data->Get("h_t1phmet");
  TH1F* h_gjet_met  =  (TH1F*) fin_gjet->Get("h_t1phmet");
  TH1F* h_data_metW  =  (TH1F*) fin_data->Get("h_phmetW");
  TH1F* h_gjet_metW  =  (TH1F*) fin_gjet->Get("h_phmetW");
  TH1F* h_znunu_met  =  (TH1F*) fin_znunu->Get("h_met_znunu");
  h_gjet_met->Scale(19.7);
  h_gjet_metW->Scale(19.7);
  h_znunu_met->Scale(19.7);

  int bin250= h_data_met->FindBin(250.);
  int bin300= h_data_met->FindBin(300.);
  int bin350= h_data_met->FindBin(350.);
  int bin400= h_data_met->FindBin(400.);
  int bin500= h_data_met->FindBin(500.);
  int bin550= h_data_met->FindBin(550.);

  std::cout<<bin400<<"   "<<bin500<<std::endl;

 std::cout<<"------------------------------------------"<<std::endl;
 std::cout<<"\\begin{table}[bthp]"<<std::endl;
 std::cout<<"\\begin{tabular}{|c|cc|cc|c||}"<<std::endl;
 std::cout<<"\\hline"<<std::endl;
 std::cout<<" Met Range \& $\\gamma$+ jets MC \& $\\gamma$+ jets DATA \& Predicted $Z\\rightarrow \\nu\\nu$ MC \& Predicted $Z\\rightarrow \\nu\\nu$ DATA \& Expected $Z\\rightarrow \\nu\\nu$ MC \\\\"<<std::endl;
 
 std::cout<<" 250-300 \&"<<h_gjet_met->Integral(bin250,bin300)  << " \& "  <<h_data_met->Integral(bin250,bin300)  <<"  \& " <<h_gjet_metW->Integral(bin250,bin300)  << " \& "  <<h_data_metW->Integral(bin250,bin300)  <<"  \& " <<h_znunu_met->Integral(bin250,bin300)  <<  " \\\\"<<std::endl;
 std::cout<<" 300-350 \&"<<h_gjet_met->Integral(bin300+1,bin350)<< " \&  " <<h_data_met->Integral(bin300+1,bin350)<<" \&  " <<h_gjet_metW->Integral(bin300+1,bin350)<< " \&  " <<h_data_metW->Integral(bin300+1,bin350)<<" \&  " <<h_znunu_met->Integral(bin300+1,bin350)<< " \\\\"<<std::endl;
 std::cout<<" 350-400 \&"<<h_gjet_met->Integral(bin350+1,bin400)<< " \&  " <<h_data_met->Integral(bin350+1,bin400)<<" \&  " <<h_gjet_metW->Integral(bin350+1,bin400)<< " \&  " <<h_data_metW->Integral(bin350+1,bin400)<<" \&  " <<h_znunu_met->Integral(bin350+1,bin400)<< " \\\\"<< std::endl;
 std::cout<<" 400-500 \&"<<h_gjet_met->Integral(bin400+1,bin500)<< " \&  " <<h_data_met->Integral(bin400+1,bin500)<<" \&  " <<h_gjet_metW->Integral(bin400+1,bin500)<< " \&  " <<h_data_metW->Integral(bin400+1,bin500)<<" \&  " <<h_znunu_met->Integral(bin400+1,bin500)<< " \\\\"<< std::endl;
 std::cout<<" 500-550 \&"<<h_gjet_met->Integral(bin500+1,bin550)<< " \&  " <<h_data_met->Integral(bin500+1,bin550)<<" \&  " <<h_gjet_metW->Integral(bin500+1,bin550)<< " \&  " <<h_data_metW->Integral(bin500+1,bin550)<<" \&  " <<h_znunu_met->Integral(bin500+1,bin550)<< " \\\\"<< std::endl;
 std::cout<<"\\hline"<<std::endl;
 std::cout<<"\\end{tabular}\\end{table}"<<std::endl;
 std::cout<<"------------------------------------------"<<std::endl;
 



}


void MakePlotDATAMC(std::string var, std::string xlabel){

  TCanvas* c1 = new TCanvas("c1", "c1", 1);
  c1->cd();
  c1->Divide(1,2);
  c1->cd(1);
  TFile* fin_data = TFile::Open("../histos_GJets_DATA.root");
  TFile* fin_bkg = TFile::Open("../histos_GJets_MC.root");
 
  TH1F* h_data  =  (TH1F*) fin_data->Get(("h_"+var).c_str());
  TH1F* h_bkg  =  (TH1F*) fin_bkg->Get(("h_"+var).c_str());
 
 
  h_data->Sumw2();
  h_bkg->Sumw2();
  double data_norm = h_data->Integral();
  double bkg_norm = h_bkg->Integral()*19.7*1.3;
  std::cout<<data_norm<< " "<<bkg_norm<< std::endl;
  //h_bkg->Scale( h_data->Integral()/h_bkg->Integral());
  h_bkg->Scale(bkg_norm/h_bkg->Integral());
  hdensity(h_data);
  hdensity(h_bkg);

  if(var ==  "phmet"){
  std::cout<<"\\begin{table}[bthp]"<<std::endl;
  std::cout<<"\\begin{tabular}{||cc||}"<<std::endl;
  std::cout<<"\\hline"<<std::endl;
  std::cout<<"MET range  \& $#gmma$+jets events \\\\"<<td::endl;
  std::cout<<"\\hline"<<std::endl;
  std::cout<<"250--300 \&"<<h_data->Integral(h_data->FindBin(250),h_data->FindBin(300))<<" \\\\"<<std::endl;
  std::cout<<"300--350 \&"<<h_data->Integral(h_data->FindBin(300)+1,h_data->FindBin(350))<<" \\\\"<<std::endl;
  std::cout<<"350--400 \&"<<h_data->Integral(h_data->FindBin(350)+1,h_data->FindBin(400))<<" \\\\"<<std::endl;
  std::cout<<"400--500 \&"<<h_data->Integral(h_data->FindBin(400)+1,h_data->FindBin(500))<<" \\\\"<<std::endl;
    std::cout<<"500--1000 \&"<<h_data->Integral(h_data->FindBin(500)+1,h_data->FindBin(1000))<<" \\\\"<<std::endl;
  std::cout<<"\\hline"<<std::endl;
  std::cout<<"\\end{tabular}\\end{table}"<<std::endl;
  }
  h_bkg->SetLineColor(kAzure+7);
  h_bkg->SetFillColor(kAzure+6);
  h_bkg->SetLineWidth(2);
 
  h_data->Draw("PE");
  h_bkg->Draw("histsame");
  h_bkg->GetXaxis()->SetTitle(xlabel.c_str());
  h_data->SetMarkerSize(0.7);
  h_data->Draw("PEsame");

  TLegend* legmc;
  legmc = new TLegend(0.6, 0.55, 0.82, 0.89, "", "brNDC");
 
  legmc->SetTextFont(42);
  legmc->SetBorderSize(0);
  legmc->SetFillStyle(0);
 
  legmc->AddEntry(h_data, "Data", "L");
  legmc->AddEntry(h_bkg, "#gamma + jet", "L");
  legmc->Draw("same");

  CMS_lumi( (TPad*)c1->cd(1),true,0);

  c1->cd(2);

  TH1F* hs = (TH1F*) h_data->Clone();
  hs->Divide(h_bkg);
  hs->Draw("pe");
  hs->GetXaxis()->SetTitle(xlabel.c_str()); 
  hs->GetYaxis()->SetTitle("Data/MC");
  hs->GetYaxis()->SetRangeUser(0., 2.);
 
  TLine line(hs->GetBinCenter(1),1,hs->GetBinCenter(hs->GetNbinsX()+1),1);
  line.SetLineColor(kRed);
  line.Draw("same");
  
  int iPos=0 ;
  CMS_lumi( (TPad*)c1->cd(2),true,iPos );
 
  c1->SaveAs(("../plots/MC-DATA_"+var+"_cat.png").c_str());
  c1->SaveAs(("../plots/MC-DATA_"+var+"_cat.pdf").c_str());
  c1->cd(1)->SetLogy();
  c1->SaveAs(("../plots/MC-DATA_"+var+"_LOG_cat.png").c_str());
  c1->SaveAs(("../plots/MC-DATA_"+var+"_LOG_cat.pdf").c_str());

}

void MakeAllPlotDATAMC(){
  MakePlotDATAMC("phpt", "P_{T} [GeV]");
  /* MakePlotDATAMC("nvtx", "Number of primary vertices");

  MakePlotDATAMC("nph", "Number of photons");
  MakePlotDATAMC("njet", "Number of jets");
  MakePlotDATAMC("phmet", "Photon MET [GeV]");*/
  MakePlotDATAMC("phmet", "Photon MET [GeV]");
  
}


void Make2DEffAcc(bool isEff){

TCanvas* c1 = new TCanvas("c1", "c1", 1);
  c1->cd();
  TFile* fin = TFile::Open("../histos_GJets_MC_Gjet.root");
 
  TH2F* h_den;
  if(isEff)h_den  =  (TH2F*) fin->Get("h2_Acc");
  else  h_den  =  (TH2F*) fin->Get("h2_den");
  TH2F* h_num;
  if(isEff)h_num  =  (TH2F*) fin->Get("h2_Eff");
  else  h_num  =  (TH2F*) fin->Get("h2_Acc");
  TH2F* h_ratio = (TH2F*) h_num->Clone();
  h_ratio->Divide(h_den);
  h_ratio->GetXaxis()->SetTitle("#eta (#gamma)");
  h_ratio->GetYaxis()->SetTitle("p_{T} (#gamma) [GeV]");
  // h_ratio->GetZaxis()->SetRangeUser(0.6, 1.);
  TLegend* legmc;
  legmc = new TLegend(0.6, 0.55, 0.82, 0.89, "", "brNDC"); 
  legmc->SetTextFont(42);
  legmc->SetBorderSize(0);
  legmc->SetFillStyle(0); 

 
  gStyle->SetPaintTextFormat("4.2f");
  h_ratio->Draw("COLZTEXT");
 CMS_lumi(c1,true,0);
 if(isEff){
   c1->SaveAs("../plots/2DEff.png");
   c1->SaveAs("../plots/2DEff.pdf");
}else{
  c1->SaveAs("../plots/2DAcc.png");
  c1->SaveAs("../plots/2DAcc.pdf");


 }
}
