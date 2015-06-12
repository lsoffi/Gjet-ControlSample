//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr 28 14:48:25 2015 by ROOT version 5.34/26
// from TTree tree/tree
// found on file: rootfiles/photon120to170_tree.root
//////////////////////////////////////////////////////////

#ifndef Analysis_h
#define Analysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Analysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          event;
   UInt_t          run;
   UInt_t          lumi;
   Double_t        wgt;
   Double_t        puwgt;
   Double_t        weight;
   Int_t           puobs;
   Int_t           putrue;
   UInt_t          nvtx;
   UInt_t          hltmet120;
   UInt_t          hltmet95jet80;
   UInt_t          hltmet105jet80;
   UInt_t          hltdoublemu;
   UInt_t          hltsinglemu;
   UInt_t          hltdoubleel;
   UInt_t          hltphoton135;
   UInt_t          hltphoton150;
   UInt_t          nmuons;
   UInt_t          nelectrons;
   UInt_t          nphotons;
   UInt_t          ntightmuons;
   UInt_t          ntightelectrons;
   UInt_t          ntightphotons;
   UInt_t          ntaus;
   UInt_t          njets;
   UInt_t          ncentjets;
   UInt_t          nbjets;
   UInt_t          nfatjets;
   UInt_t          ncentfatjets;
   UInt_t          njetsnotfat;
   UInt_t          ncentjetsnotfat;
   UInt_t          nbjetsnotfat;
   Double_t        pfmet;
   Double_t        pfmetphi;
   Double_t        t1pfmet;
   Double_t        t1pfmetphi;
   Double_t        calomet;
   Double_t        calometphi;
   Double_t        pfmupt;
   Double_t        pfmuphi;
   Double_t        mumet;
   Double_t        mumetphi;
   Double_t        phmet;
   Double_t        phmetphi;
   Double_t        t1mumet;
   Double_t        t1mumetphi;
   Double_t        t1phmet;
   Double_t        t1phmetphi;
   Double_t        fatjetpt;
   Double_t        fatjeteta;
   Double_t        fatjetphi;
   Double_t        fatjetmass;
   Double_t        fatjetprunedmass;
   Double_t        fatjetmassdrop;
   Double_t        fatjettau2;
   Double_t        fatjettau1;
   Double_t        fatjetCHfrac;
   Double_t        fatjetNHfrac;
   Double_t        fatjetEMfrac;
   Double_t        fatjetCEMfrac;
   Double_t        fatjetmetdphi;
   Double_t        signaljetpt;
   Double_t        signaljeteta;
   Double_t        signaljetphi;
   Double_t        signaljetCHfrac;
   Double_t        signaljetNHfrac;
   Double_t        signaljetEMfrac;
   Double_t        signaljetCEMfrac;
   Double_t        signaljetmetdphi;
   Double_t        secondjetpt;
   Double_t        secondjeteta;
   Double_t        secondjetphi;
   Double_t        secondjetCHfrac;
   Double_t        secondjetNHfrac;
   Double_t        secondjetEMfrac;
   Double_t        secondjetCEMfrac;
   Double_t        secondjetmetdphi;
   Double_t        jetjetdphi;
   Double_t        jetmetdphimin;
   Double_t        thirdjetpt;
   Double_t        thirdjeteta;
   Double_t        thirdjetphi;
   Double_t        thirdjetCHfrac;
   Double_t        thirdjetNHfrac;
   Double_t        thirdjetEMfrac;
   Double_t        thirdjetCEMfrac;
   Double_t        thirdjetmetdphi;
   Double_t        ht;
   Double_t        dht;
   Double_t        mht;
   Double_t        alphat;
   Double_t        apcjet;
   Double_t        apcmet;
   Double_t        apcjetmet;
   Double_t        apcjetmax;
   Double_t        apcjetmetmax;
   Double_t        apcjetmin;
   Double_t        apcjetmetmin;
   Int_t           mu1pid;
   Double_t        mu1pt;
   Double_t        mu1eta;
   Double_t        mu1phi;
   Int_t           mu1id;
   Int_t           mu2pid;
   Double_t        mu2pt;
   Double_t        mu2eta;
   Double_t        mu2phi;
   Int_t           mu2id;
   Int_t           el1pid;
   Double_t        el1pt;
   Double_t        el1eta;
   Double_t        el1phi;
   Int_t           el1id;
   Int_t           el2pid;
   Double_t        el2pt;
   Double_t        el2eta;
   Double_t        el2phi;
   Int_t           el2id;
   Double_t        zmass;
   Double_t        zpt;
   Double_t        zeta;
   Double_t        zphi;
   Double_t        wmt;
   Double_t        emumass;
   Double_t        emupt;
   Double_t        emueta;
   Double_t        emuphi;
   Double_t        zeemass;
   Double_t        zeept;
   Double_t        zeeeta;
   Double_t        zeephi;
   Double_t        wemt;
   Double_t        phpt;
   Double_t        pheta;
   Double_t        phphi;
  
   Int_t           wzid;
   Double_t        wzmass;
   Double_t        wzmt;
   Double_t        wzpt;
   Double_t        wzeta;
   Double_t        wzphi;
   Int_t           l1id;
   Double_t        l1pt;
   Double_t        l1eta;
   Double_t        l1phi;
   Int_t           l2id;
   Double_t        l2pt;
   Double_t        l2eta;
   Double_t        l2phi;

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_wgt;   //!
   TBranch        *b_puwgt;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_puobs;   //!
   TBranch        *b_putrue;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_hltmet120;   //!
   TBranch        *b_hltmet95jet80;   //!
   TBranch        *b_hltmet105jet80;   //!
   TBranch        *b_hltdoublemu;   //!
   TBranch        *b_hltsinglemu;   //!
   TBranch        *b_hltdoubleel;   //!
   TBranch        *b_hltphoton135;   //!
   TBranch        *b_hltphoton150;   //!
   TBranch        *b_nmuons;   //!
   TBranch        *b_nelectrons;   //!
   TBranch        *b_nphotons;   //!
   TBranch        *b_ntightmuons;   //!
   TBranch        *b_ntightelectrons;   //!
   TBranch        *b_ntightphotons;   //!
   TBranch        *b_ntaus;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_ncentjets;   //!
   TBranch        *b_nbjets;   //!
   TBranch        *b_nfatjets;   //!
   TBranch        *b_ncentfatjets;   //!
   TBranch        *b_njetsnotfat;   //!
   TBranch        *b_ncentjetsnotfat;   //!
   TBranch        *b_nbjetsnotfat;   //!
   TBranch        *b_pfmet;   //!
   TBranch        *b_pfmetphi;   //!
   TBranch        *b_t1pfmet;   //!
   TBranch        *b_t1pfmetphi;   //!
   TBranch        *b_calomet;   //!
   TBranch        *b_calometphi;   //!
   TBranch        *b_pfmupt;   //!
   TBranch        *b_pfmuphi;   //!
   TBranch        *b_mumet;   //!
   TBranch        *b_mumetphi;   //!
   TBranch        *b_phmet;   //!
   TBranch        *b_phmetphi;   //!
   TBranch        *b_t1mumet;   //!
   TBranch        *b_t1mumetphi;   //!
   TBranch        *b_t1phmet;   //!
   TBranch        *b_t1phmetphi;   //!
   TBranch        *b_fatjetpt;   //!
   TBranch        *b_fatjeteta;   //!
   TBranch        *b_fatjetphi;   //!
   TBranch        *b_fatjetmass;   //!
   TBranch        *b_fatjetprunedmass;   //!
   TBranch        *b_fatjetmassdrop;   //!
   TBranch        *b_fatjettau2;   //!
   TBranch        *b_fatjettau1;   //!
   TBranch        *b_fatjetCHfrac;   //!
   TBranch        *b_fatjetNHfrac;   //!
   TBranch        *b_fatjetEMfrac;   //!
   TBranch        *b_fatjetCEMfrac;   //!
   TBranch        *b_fatjetmetdphi;   //!
   TBranch        *b_signaljetpt;   //!
   TBranch        *b_signaljeteta;   //!
   TBranch        *b_signaljetphi;   //!
   TBranch        *b_signaljetCHfrac;   //!
   TBranch        *b_signaljetNHfrac;   //!
   TBranch        *b_signaljetEMfrac;   //!
   TBranch        *b_signaljetCEMfrac;   //!
   TBranch        *b_signaljetmetdphi;   //!
   TBranch        *b_secondjetpt;   //!
   TBranch        *b_secondjeteta;   //!
   TBranch        *b_secondjetphi;   //!
   TBranch        *b_secondjetCHfrac;   //!
   TBranch        *b_secondjetNHfrac;   //!
   TBranch        *b_secondjetEMfrac;   //!
   TBranch        *b_secondjetCEMfrac;   //!
   TBranch        *b_secondjetmetdphi;   //!
   TBranch        *b_jetjetdphi;   //!
   TBranch        *b_jetmetdphimin;   //!
   TBranch        *b_thirdjetpt;   //!
   TBranch        *b_thirdjeteta;   //!
   TBranch        *b_thirdjetphi;   //!
   TBranch        *b_thirdjetCHfrac;   //!
   TBranch        *b_thirdjetNHfrac;   //!
   TBranch        *b_thirdjetEMfrac;   //!
   TBranch        *b_thirdjetCEMfrac;   //!
   TBranch        *b_thirdjetmetdphi;   //!
   TBranch        *b_ht;   //!
   TBranch        *b_dht;   //!
   TBranch        *b_mht;   //!
   TBranch        *b_alphat;   //!
   TBranch        *b_apcjet;   //!
   TBranch        *b_apcmet;   //!
   TBranch        *b_apcjetmet;   //!
   TBranch        *b_apcjetmax;   //!
   TBranch        *b_apcjetmetmax;   //!
   TBranch        *b_apcjetmin;   //!
   TBranch        *b_apcjetmetmin;   //!
   TBranch        *b_mu1pid;   //!
   TBranch        *b_mu1pt;   //!
   TBranch        *b_mu1eta;   //!
   TBranch        *b_mu1phi;   //!
   TBranch        *b_mu1id;   //!
   TBranch        *b_mu2pid;   //!
   TBranch        *b_mu2pt;   //!
   TBranch        *b_mu2eta;   //!
   TBranch        *b_mu2phi;   //!
   TBranch        *b_mu2id;   //!
   TBranch        *b_el1pid;   //!
   TBranch        *b_el1pt;   //!
   TBranch        *b_el1eta;   //!
   TBranch        *b_el1phi;   //!
   TBranch        *b_el1id;   //!
   TBranch        *b_el2pid;   //!
   TBranch        *b_el2pt;   //!
   TBranch        *b_el2eta;   //!
   TBranch        *b_el2phi;   //!
   TBranch        *b_el2id;   //!
   TBranch        *b_zmass;   //!
   TBranch        *b_zpt;   //!
   TBranch        *b_zeta;   //!
   TBranch        *b_zphi;   //!
   TBranch        *b_wmt;   //!
   TBranch        *b_emumass;   //!
   TBranch        *b_emupt;   //!
   TBranch        *b_emueta;   //!
   TBranch        *b_emuphi;   //!
   TBranch        *b_zeemass;   //!
   TBranch        *b_zeeept;   //!
   TBranch        *b_zeeeta;   //!
   TBranch        *b_zeephi;   //!
   TBranch        *b_wemt;   //!
   TBranch        *b_phpt;   //!
   TBranch        *b_pheta;   //!
   TBranch        *b_phphi;   //!
 
   TBranch        *b_wzid;   //!
   TBranch        *b_wzmass;   //!
   TBranch        *b_wzmt;   //!
   TBranch        *b_wzpt;   //!
   TBranch        *b_wzeta;   //!
   TBranch        *b_wzphi;   //!
   TBranch        *b_l1id;   //!
   TBranch        *b_l1pt;   //!
   TBranch        *b_l1eta;   //!
   TBranch        *b_l1phi;   //!
   TBranch        *b_l2id;   //!
   TBranch        *b_l2pt;   //!
   TBranch        *b_l2eta;   //!
   TBranch        *b_l2phi;   //!

   Analysis(TTree *tree=0);
   virtual ~Analysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(bool isMC,std::string name);
   double ZnunuWeight(double pt, double eta,TH2F* h,TH2F* h2,TH1F* hxsec,TH1F* hewk);
   double EffWeight(double pt, double eta,TH2F* h);
   double AccWeight(double pt, double eta,TH2F* h);
   double XsecWeight(double pt,TH1F* hxsec);
   double EwkWeight(double pt,TH1F* hewk);

   double deltaPhi(double p1,double p2);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Analysis_cxx
Analysis::Analysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("rootfiles/photon120to170_tree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("rootfiles/photon120to170_tree.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("rootfiles/photon120to170_tree.root:/tree");
      dir->GetObject("tree",tree);

   }
   Init(tree);
}

Analysis::~Analysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analysis::LoadTree(Long64_t entry)
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

void Analysis::Init(TTree *tree)
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

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("wgt", &wgt, &b_wgt);
   fChain->SetBranchAddress("puwgt", &puwgt, &b_puwgt);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("puobs", &puobs, &b_puobs);
   fChain->SetBranchAddress("putrue", &putrue, &b_putrue);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("hltmet120", &hltmet120, &b_hltmet120);
   fChain->SetBranchAddress("hltmet95jet80", &hltmet95jet80, &b_hltmet95jet80);
   fChain->SetBranchAddress("hltmet105jet80", &hltmet105jet80, &b_hltmet105jet80);
   fChain->SetBranchAddress("hltdoublemu", &hltdoublemu, &b_hltdoublemu);
   fChain->SetBranchAddress("hltsinglemu", &hltsinglemu, &b_hltsinglemu);
   fChain->SetBranchAddress("hltdoubleel", &hltdoubleel, &b_hltdoubleel);
   fChain->SetBranchAddress("hltphoton135", &hltphoton135, &b_hltphoton135);
   fChain->SetBranchAddress("hltphoton150", &hltphoton150, &b_hltphoton150);
   fChain->SetBranchAddress("nmuons", &nmuons, &b_nmuons);
   fChain->SetBranchAddress("nelectrons", &nelectrons, &b_nelectrons);
   fChain->SetBranchAddress("nphotons", &nphotons, &b_nphotons);
   fChain->SetBranchAddress("ntightmuons", &ntightmuons, &b_ntightmuons);
   fChain->SetBranchAddress("ntightelectrons", &ntightelectrons, &b_ntightelectrons);
   fChain->SetBranchAddress("ntightphotons", &ntightphotons, &b_ntightphotons);
   fChain->SetBranchAddress("ntaus", &ntaus, &b_ntaus);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("ncentjets", &ncentjets, &b_ncentjets);
   fChain->SetBranchAddress("nbjets", &nbjets, &b_nbjets);
   fChain->SetBranchAddress("nfatjets", &nfatjets, &b_nfatjets);
   fChain->SetBranchAddress("ncentfatjets", &ncentfatjets, &b_ncentfatjets);
   fChain->SetBranchAddress("njetsnotfat", &njetsnotfat, &b_njetsnotfat);
   fChain->SetBranchAddress("ncentjetsnotfat", &ncentjetsnotfat, &b_ncentjetsnotfat);
   fChain->SetBranchAddress("nbjetsnotfat", &nbjetsnotfat, &b_nbjetsnotfat);
   fChain->SetBranchAddress("pfmet", &pfmet, &b_pfmet);
   fChain->SetBranchAddress("pfmetphi", &pfmetphi, &b_pfmetphi);
   fChain->SetBranchAddress("t1pfmet", &t1pfmet, &b_t1pfmet);
   fChain->SetBranchAddress("t1pfmetphi", &t1pfmetphi, &b_t1pfmetphi);
   fChain->SetBranchAddress("calomet", &calomet, &b_calomet);
   fChain->SetBranchAddress("calometphi", &calometphi, &b_calometphi);
   fChain->SetBranchAddress("pfmupt", &pfmupt, &b_pfmupt);
   fChain->SetBranchAddress("pfmuphi", &pfmuphi, &b_pfmuphi);
   fChain->SetBranchAddress("mumet", &mumet, &b_mumet);
   fChain->SetBranchAddress("mumetphi", &mumetphi, &b_mumetphi);
   fChain->SetBranchAddress("phmet", &phmet, &b_phmet);
   fChain->SetBranchAddress("phmetphi", &phmetphi, &b_phmetphi);
   fChain->SetBranchAddress("t1mumet", &t1mumet, &b_t1mumet);
   fChain->SetBranchAddress("t1mumetphi", &t1mumetphi, &b_t1mumetphi);
   fChain->SetBranchAddress("t1phmet", &t1phmet, &b_t1phmet);
   fChain->SetBranchAddress("t1phmetphi", &t1phmetphi, &b_t1phmetphi);
   fChain->SetBranchAddress("fatjetpt", &fatjetpt, &b_fatjetpt);
   fChain->SetBranchAddress("fatjeteta", &fatjeteta, &b_fatjeteta);
   fChain->SetBranchAddress("fatjetphi", &fatjetphi, &b_fatjetphi);
   fChain->SetBranchAddress("fatjetmass", &fatjetmass, &b_fatjetmass);
   fChain->SetBranchAddress("fatjetprunedmass", &fatjetprunedmass, &b_fatjetprunedmass);
   fChain->SetBranchAddress("fatjetmassdrop", &fatjetmassdrop, &b_fatjetmassdrop);
   fChain->SetBranchAddress("fatjettau2", &fatjettau2, &b_fatjettau2);
   fChain->SetBranchAddress("fatjettau1", &fatjettau1, &b_fatjettau1);
   fChain->SetBranchAddress("fatjetCHfrac", &fatjetCHfrac, &b_fatjetCHfrac);
   fChain->SetBranchAddress("fatjetNHfrac", &fatjetNHfrac, &b_fatjetNHfrac);
   fChain->SetBranchAddress("fatjetEMfrac", &fatjetEMfrac, &b_fatjetEMfrac);
   fChain->SetBranchAddress("fatjetCEMfrac", &fatjetCEMfrac, &b_fatjetCEMfrac);
   fChain->SetBranchAddress("fatjetmetdphi", &fatjetmetdphi, &b_fatjetmetdphi);
   fChain->SetBranchAddress("signaljetpt", &signaljetpt, &b_signaljetpt);
   fChain->SetBranchAddress("signaljeteta", &signaljeteta, &b_signaljeteta);
   fChain->SetBranchAddress("signaljetphi", &signaljetphi, &b_signaljetphi);
   fChain->SetBranchAddress("signaljetCHfrac", &signaljetCHfrac, &b_signaljetCHfrac);
   fChain->SetBranchAddress("signaljetNHfrac", &signaljetNHfrac, &b_signaljetNHfrac);
   fChain->SetBranchAddress("signaljetEMfrac", &signaljetEMfrac, &b_signaljetEMfrac);
   fChain->SetBranchAddress("signaljetCEMfrac", &signaljetCEMfrac, &b_signaljetCEMfrac);
   fChain->SetBranchAddress("signaljetmetdphi", &signaljetmetdphi, &b_signaljetmetdphi);
   fChain->SetBranchAddress("secondjetpt", &secondjetpt, &b_secondjetpt);
   fChain->SetBranchAddress("secondjeteta", &secondjeteta, &b_secondjeteta);
   fChain->SetBranchAddress("secondjetphi", &secondjetphi, &b_secondjetphi);
   fChain->SetBranchAddress("secondjetCHfrac", &secondjetCHfrac, &b_secondjetCHfrac);
   fChain->SetBranchAddress("secondjetNHfrac", &secondjetNHfrac, &b_secondjetNHfrac);
   fChain->SetBranchAddress("secondjetEMfrac", &secondjetEMfrac, &b_secondjetEMfrac);
   fChain->SetBranchAddress("secondjetCEMfrac", &secondjetCEMfrac, &b_secondjetCEMfrac);
   fChain->SetBranchAddress("secondjetmetdphi", &secondjetmetdphi, &b_secondjetmetdphi);
   fChain->SetBranchAddress("jetjetdphi", &jetjetdphi, &b_jetjetdphi);
   fChain->SetBranchAddress("jetmetdphimin", &jetmetdphimin, &b_jetmetdphimin);
   fChain->SetBranchAddress("thirdjetpt", &thirdjetpt, &b_thirdjetpt);
   fChain->SetBranchAddress("thirdjeteta", &thirdjeteta, &b_thirdjeteta);
   fChain->SetBranchAddress("thirdjetphi", &thirdjetphi, &b_thirdjetphi);
   fChain->SetBranchAddress("thirdjetCHfrac", &thirdjetCHfrac, &b_thirdjetCHfrac);
   fChain->SetBranchAddress("thirdjetNHfrac", &thirdjetNHfrac, &b_thirdjetNHfrac);
   fChain->SetBranchAddress("thirdjetEMfrac", &thirdjetEMfrac, &b_thirdjetEMfrac);
   fChain->SetBranchAddress("thirdjetCEMfrac", &thirdjetCEMfrac, &b_thirdjetCEMfrac);
   fChain->SetBranchAddress("thirdjetmetdphi", &thirdjetmetdphi, &b_thirdjetmetdphi);
   fChain->SetBranchAddress("ht", &ht, &b_ht);
   fChain->SetBranchAddress("dht", &dht, &b_dht);
   fChain->SetBranchAddress("mht", &mht, &b_mht);
   fChain->SetBranchAddress("alphat", &alphat, &b_alphat);
   fChain->SetBranchAddress("apcjet", &apcjet, &b_apcjet);
   fChain->SetBranchAddress("apcmet", &apcmet, &b_apcmet);
   fChain->SetBranchAddress("apcjetmet", &apcjetmet, &b_apcjetmet);
   fChain->SetBranchAddress("apcjetmax", &apcjetmax, &b_apcjetmax);
   fChain->SetBranchAddress("apcjetmetmax", &apcjetmetmax, &b_apcjetmetmax);
   fChain->SetBranchAddress("apcjetmin", &apcjetmin, &b_apcjetmin);
   fChain->SetBranchAddress("apcjetmetmin", &apcjetmetmin, &b_apcjetmetmin);
   fChain->SetBranchAddress("mu1pid", &mu1pid, &b_mu1pid);
   fChain->SetBranchAddress("mu1pt", &mu1pt, &b_mu1pt);
   fChain->SetBranchAddress("mu1eta", &mu1eta, &b_mu1eta);
   fChain->SetBranchAddress("mu1phi", &mu1phi, &b_mu1phi);
   fChain->SetBranchAddress("mu1id", &mu1id, &b_mu1id);
   fChain->SetBranchAddress("mu2pid", &mu2pid, &b_mu2pid);
   fChain->SetBranchAddress("mu2pt", &mu2pt, &b_mu2pt);
   fChain->SetBranchAddress("mu2eta", &mu2eta, &b_mu2eta);
   fChain->SetBranchAddress("mu2phi", &mu2phi, &b_mu2phi);
   fChain->SetBranchAddress("mu2id", &mu2id, &b_mu2id);
   fChain->SetBranchAddress("el1pid", &el1pid, &b_el1pid);
   fChain->SetBranchAddress("el1pt", &el1pt, &b_el1pt);
   fChain->SetBranchAddress("el1eta", &el1eta, &b_el1eta);
   fChain->SetBranchAddress("el1phi", &el1phi, &b_el1phi);
   fChain->SetBranchAddress("el1id", &el1id, &b_el1id);
   fChain->SetBranchAddress("el2pid", &el2pid, &b_el2pid);
   fChain->SetBranchAddress("el2pt", &el2pt, &b_el2pt);
   fChain->SetBranchAddress("el2eta", &el2eta, &b_el2eta);
   fChain->SetBranchAddress("el2phi", &el2phi, &b_el2phi);
   fChain->SetBranchAddress("el2id", &el2id, &b_el2id);
   fChain->SetBranchAddress("zmass", &zmass, &b_zmass);
   fChain->SetBranchAddress("zpt", &zpt, &b_zpt);
   fChain->SetBranchAddress("zeta", &zeta, &b_zeta);
   fChain->SetBranchAddress("zphi", &zphi, &b_zphi);
   fChain->SetBranchAddress("wmt", &wmt, &b_wmt);
   fChain->SetBranchAddress("emumass", &emumass, &b_emumass);
   fChain->SetBranchAddress("emupt", &emupt, &b_emupt);
   fChain->SetBranchAddress("emueta", &emueta, &b_emueta);
   fChain->SetBranchAddress("emuphi", &emuphi, &b_emuphi);
   fChain->SetBranchAddress("zeemass", &zeemass, &b_zeemass);
   fChain->SetBranchAddress("zeept", &zeept, &b_zeeept);
   fChain->SetBranchAddress("zeeeta", &zeeeta, &b_zeeeta);
   fChain->SetBranchAddress("zeephi", &zeephi, &b_zeephi);
   fChain->SetBranchAddress("wemt", &wemt, &b_wemt);
   fChain->SetBranchAddress("phpt", &phpt, &b_phpt);
   fChain->SetBranchAddress("pheta", &pheta, &b_pheta);
   fChain->SetBranchAddress("phphi", &phphi, &b_phphi);
  fChain->SetBranchAddress("wzid", &wzid, &b_wzid);
   fChain->SetBranchAddress("wzmass", &wzmass, &b_wzmass);
   fChain->SetBranchAddress("wzmt", &wzmt, &b_wzmt);
   fChain->SetBranchAddress("wzpt", &wzpt, &b_wzpt);
   fChain->SetBranchAddress("wzeta", &wzeta, &b_wzeta);
   fChain->SetBranchAddress("wzphi", &wzphi, &b_wzphi);
   fChain->SetBranchAddress("l1id", &l1id, &b_l1id);
   fChain->SetBranchAddress("l1pt", &l1pt, &b_l1pt);
   fChain->SetBranchAddress("l1eta", &l1eta, &b_l1eta);
   fChain->SetBranchAddress("l1phi", &l1phi, &b_l1phi);
   fChain->SetBranchAddress("l2id", &l2id, &b_l2id);
   fChain->SetBranchAddress("l2pt", &l2pt, &b_l2pt);
   fChain->SetBranchAddress("l2eta", &l2eta, &b_l2eta);
   fChain->SetBranchAddress("l2phi", &l2phi, &b_l2phi);
   Notify();
}

Bool_t Analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analysis_cxx
