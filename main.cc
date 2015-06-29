// last commit by $Id: analysis.cc,v 1.1 2013/01/31 15:32:00 soffi Exp $
//
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TVector2.h>
#include <TVector3.h>
#include <TAxis.h>

#include "Analysis.h"

using namespace std;



int main(int argc, char* argv[]) {

  std::string mc = argv[1];
  bool isMC = false;
  if(mc=="Gjet") isMC = true;
  if(mc=="Znn") isMC = true;

      //================ Creating chain 
  
 
  TFile* fin;

  if(mc=="Gjet")fin= new TFile("/t3/users/lsoffi/CMSSW_5_3_26/src/rootfiles/photonMC_TestPurity.root");
  if(mc=="Znn")fin= new TFile("rootfiles/znn.root");
  //else fin= new TFile("/afs/cern.ch/work/s/soffi/CMSSW_5_3_26-MonoJet/src/GJet/rootfiles/photon_DATA_tree.root");
  else fin= new TFile("/t3/users/lsoffi/CMSSW_5_3_26/src/rootfiles/Reduced_photonData_TestPurity.root");

  TChain* chain =new TChain("tree");
 
    if(mc=="Gjet"){
      chain->Add("/t3/users/lsoffi/CMSSW_5_3_26/src/rootfiles/photonMC_TestPurity.root/tree/tree");  
    }else if(mc=="Znn"){
      chain->Add("rootfiles/znn.root/tree/tree"); 
    }else{
      chain->Add("/t3/users/lsoffi/CMSSW_5_3_26/src/rootfiles/Reduced_photonData_TestPurity.root/tree/tree");  }
 
  // std::cout<<chain->GetEntries()<<std::endl;      
  //================ Run analysis
  Analysis tree( chain );
  tree.Loop(isMC,mc);
  
  delete fin;
  delete chain;
  return 0;
}
