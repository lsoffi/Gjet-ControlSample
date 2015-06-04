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
  if(mc=="MC") isMC = true;

      //================ Creating chain 
  
 
  TFile* fin;

  if(isMC)fin= new TFile("/afs/cern.ch/work/s/soffi/CMSSW_5_3_26-MonoJet/src/GJet/rootfiles/photon_MC_tree.root");
  else fin= new TFile("/afs/cern.ch/work/s/soffi/CMSSW_5_3_26-MonoJet/src/GJet/rootfiles/photon_DATA_tree.root");
  //else fin= new TFile("/afs/cern.ch/work/s/soffi/CMSSW_5_3_26-MonoJet/src/GJet/rootfiles/photonDataRunAtestPurity.root");

  TChain* chain =new TChain("tree");
 
    if(isMC){
      chain->Add("/afs/cern.ch/work/s/soffi/CMSSW_5_3_26-MonoJet/src/GJet/rootfiles/photon_MC_tree.root/tree/tree");  
    }else{
      chain->Add("/afs/cern.ch/work/s/soffi/CMSSW_5_3_26-MonoJet/src/GJet/rootfiles/photon_DATA_tree.root/tree/tree");  }
 
  // std::cout<<chain->GetEntries()<<std::endl;      
  //================ Run analysis
  Analysis tree( chain );
  tree.Loop(isMC);
  
  delete fin;
  delete chain;
  return 0;
}
