using namespace RooFit;
using namespace RooStats ;
#include "./macros/CMS_lumi.C"
static const Int_t NCAT = 4;  // chiara
//TString mainCut = "(hltphoton150||hltphoton135) && nphotons==1&&signaljetpt>110 && abs(signaljeteta)<2.4 && njets<3 && preselphpt>170 && ((abs(preselpheta)<1.4442)||(abs(preselpheta)>1.566 && abs(preselpheta)<2.5))";
TString mainCut = "nphotons==1&& preselphpt>160 && (abs(preselpheta)<1.4442)"; //||(abs(preselpheta)>1.566 && abs(preselpheta)<2.5)";
Float_t minFit= 0;
Float_t maxFit = 4;
void AddData(RooWorkspace*);
//TTree* dataset2tree(RooDataSet *dataset, RooArgSet* args);
RooFitResult*  ModelFit(RooWorkspace*);




TTree* dataset2tree(RooDataSet dataset, RooArgSet* args){
  
  RooArgList argList(*args);
  argList.Print();
  Double_t variables[50];
  Long64_t nEntries= dataset.numEntries();
  
  TTree *tree = new TTree("tree","tree");
  tree->SetDirectory(0);
  TIterator *it1=NULL; 
  it1 = argList.createIterator();
  int index1=0;
  for(RooRealVar *var = (RooRealVar *) it1->Next(); var!=NULL;
      var = (RooRealVar *) it1->Next(),index1++){
    TString name(var->GetName());
    name.ReplaceAll("-","_");
    
    tree->Branch(name, &(variables[index1]), name+"/F");
  }

  Double_t isMatched;
  tree->Branch("isMatched", &isMatched, "isMatched/I");
  tree->Print();
 
  for(Long64_t jentry=0; jentry<nEntries; jentry++){
    
    TIterator *it=NULL; 
    RooArgList argList1(*(dataset.get(jentry)));
    it = argList1.createIterator();
    int index=0;
    double pt=999.;
    double eta=999.;
    double phi=999.;
    double ptg=999.;
    double etag=999.;
    double phig=999.;

    for(RooRealVar *var = (RooRealVar *) it->Next(); var!=NULL;
	var = (RooRealVar *) it->Next(), index++){
      variables[index]=var->getVal();
      std::string nameVar = var->GetName(); 
      // std::cout<<nameVar<<" "<<var->getVal()<<std::endl; 
      if(nameVar=="preselphpt")  pt=var->getVal(); 
      if(nameVar=="preselpheta")  eta=var->getVal(); 
      if(nameVar=="preselphphi")  phi=var->getVal(); 
      if(nameVar=="wzpt")  std::cout<<var->getVal()<<std::endl;//ptg=var->getVal(); 
      if(nameVar=="wzeta")  etag=var->getVal(); 
      if(nameVar=="wzphi")  phig=var->getVal(); 

    }
    // std::cout<<pt<<"  "<<ptg<<std::endl;
    isMatched = false;
    if(pt!=0){
    TLorentzVector* phop4 = new TLorentzVector();
    phop4->SetPtEtaPhiM(pt,eta,phi,0);
    TLorentzVector* p4 = new TLorentzVector();
    p4->SetPtEtaPhiM(ptg,etag,phig,0);
    if( p4->Pt() < 10. || fabs(p4->Eta()) > 3. ) continue;
    float dr = phop4->DeltaR(*p4);
    //std::cout<<dr<<std::endl;
    if (dr<0.3&&fabs((p4->Pt()-phop4->Pt())/p4->Pt()) < 0.5 ) isMatched=true;
    }
  
    // std::cout<<jentry<<std::endl;
    delete it;
    tree->Fill();
    std::cout<<jentry<<std::endl;
  }
  
  tree->ResetBranchAddresses();
  return tree;
}



RooArgSet* defineVariables() {
  RooRealVar* ph_iso  = new RooRealVar("preselphcorrPHIso", "PFIsophoton",minFit,maxFit,"GeV");
  RooRealVar* ph_sieie  = new RooRealVar("preselphsieie", "PFIsophoton",0.,10,"GeV");
  RooRealVar* ph_eta = new RooRealVar("preselpheta", "eta(g)",-10,10,"");
  RooRealVar* ph_phi = new RooRealVar("preselphphi", "pt(g)",-5,5,"");
  RooRealVar* ph_pt = new RooRealVar("preselphpt", "pt(g)",0,1000,"");
  RooRealVar* weight = new RooRealVar("weight","weightings",0,1000,"");

  RooRealVar* nphotons = new RooRealVar("nphotons","nphotons",0,10,"");
  RooRealVar* hltphoton135 = new RooRealVar("hltphoton135","hltphoton135",0,1,"");
  RooRealVar* hltphoton150 = new RooRealVar("hltphoton150","hltphoton150",0,1,"");
  RooRealVar* signaljetpt = new RooRealVar("signaljetpt","signaljetpt",0,2000.,"");
  RooRealVar* signaljeteta = new RooRealVar("signaljeteta","signaljeteta",-5.,5.,"");
  RooRealVar* njets = new RooRealVar("njets","njets",0,20,"");
  RooRealVar* nvtx = new RooRealVar("nvtx", "nvtx", 0, 50, "");

  RooRealVar* wzpt   = new RooRealVar("wzpt", "wzpt", 0, 1000, "");
  RooRealVar* wzeta  = new RooRealVar("wzeta", "wzeta", -10, 10, "");
  RooRealVar* wzphi  = new RooRealVar("wzphi", "wzphi", -5, 5, "");

  RooArgSet* ntplVars = new RooArgSet(*ph_iso,*ph_sieie,*ph_eta, *ph_pt,*ph_phi, *weight);
  RooArgSet* ntplVarsSpectators = new RooArgSet(*nphotons, *hltphoton135, *hltphoton150,*signaljetpt,*signaljeteta,*njets,*nvtx);
  RooArgSet* ntplVarsGen = new RooArgSet(*wzpt,*wzeta, *wzphi);
  ntplVars->add(*ntplVarsSpectators);
  ntplVars->add(*ntplVarsGen);
  return ntplVars;
}




RooArgSet* defineVariables_match() {
 RooRealVar* ph_iso  = new RooRealVar("preselphcorrPHIso", "PFIsophoton",minFit,maxFit,"GeV");
  RooRealVar* ph_sieie  = new RooRealVar("preselphsieie", "PFIsophoton",0.,10,"GeV");
  RooRealVar* ph_eta = new RooRealVar("preselpheta", "eta(g)",-10,10,"");
  RooRealVar* ph_phi = new RooRealVar("preselphphi", "pt(g)",-5,5,"");
  RooRealVar* ph_pt = new RooRealVar("preselphpt", "pt(g)",0,1000,"");
  RooRealVar* weight = new RooRealVar("weight","weightings",0,1000,"");

  RooRealVar* nphotons = new RooRealVar("nphotons","nphotons",0,10,"");
  RooRealVar* hltphoton135 = new RooRealVar("hltphoton135","hltphoton135",0,1,"");
  RooRealVar* hltphoton150 = new RooRealVar("hltphoton150","hltphoton150",0,1,"");
  RooRealVar* signaljetpt = new RooRealVar("signaljetpt","signaljetpt",0,2000.,"");
  RooRealVar* signaljeteta = new RooRealVar("signaljeteta","signaljeteta",-5.,5.,"");
  RooRealVar* njets = new RooRealVar("njets","njets",0,20,"");
  RooRealVar* nvtx = new RooRealVar("nvtx", "nvtx", 0, 50, "");

  RooRealVar* wzpt   = new RooRealVar("wzpt", "wzpt", 0, 1000, "");
  RooRealVar* wzeta  = new RooRealVar("wzeta", "wzeta", -10, 10, "");
  RooRealVar* wzphi  = new RooRealVar("wzphi", "wzphi", -5, 5, "");

  RooRealVar* isMatched = new RooRealVar("isMatched", "isMatched", 0, 2, "");

  RooArgSet* ntplVars = new RooArgSet(*ph_iso,*ph_sieie,*ph_eta, *ph_pt,*ph_phi, *weight);
  RooArgSet* ntplVarsSpectators = new RooArgSet(*nphotons, *hltphoton135, *hltphoton150,*signaljetpt,*signaljeteta,*njets,*nvtx,*isMatched);
  RooArgSet* ntplVarsGen = new RooArgSet(*wzpt,*wzeta, *wzphi);
  ntplVars->add(*ntplVarsSpectators);
  ntplVars->add(*ntplVarsGen);
 
  return ntplVars;
}




void runfits() {
  
  TString card_name("./macros/InitWS.rs");
  HLFactory hlf("HLFactory", card_name, false);
  RooWorkspace* w = hlf.GetWs(); 
  RooFitResult* fitresults;
  // Luminosity:
  Float_t Lum = 19500.0;  
  RooRealVar lumi("lumi","lumi",Lum);
  w->import(lumi); 

  //Add Variables
  RooArgSet* ntplVars = defineVariables();  
  RooArgSet* ntplVars_match = defineVariables_match();  
  //chain summing up all production modes
   TChain* Tree  = new TChain(); 
  Tree->Add("./rootfiles/photonDataRunAtestPurity.root/tree/tree");////
  Tree->Add("./rootfiles/photonDataRUNBTestPurity0.root/tree/tree");////
  Tree->Add("./rootfiles/photonDataRUNBTestPurity1.root/tree/tree");////
  Tree->Add("./rootfiles/photonDataRUNBTestPurity2.root/tree/tree");////
  Tree->Add("./rootfiles/photonDataRUNCTestPurity0.root/tree/tree");////
  Tree->Add("./rootfiles/photonDataRUNCTestPurity1.root/tree/tree");////
  Tree->Add("./rootfiles/photonDataRUNCTestPurity2.root/tree/tree");////
  Tree->Add("./rootfiles/photonDataRUNCTestPurity3.root/tree/tree");////
  Tree->Add("./rootfiles/photonDataRUNDTestPurity0.root/tree/tree");////
  Tree->Add("./rootfiles/photonDataRUNDTestPurity1.root/tree/tree");////
  Tree->Add("./rootfiles/photonDataRUNDTestPurity3.root/tree/tree");////
  Tree->Add("./rootfiles/photonDataRUNDTestPurity2.root/tree/tree");////
  Tree->SetTitle("Tree");
  Tree->SetName("Tree");
  // common preselection cut

  
    // livia  
  // Create dataset composed with different productions, the weight is already applied in our ntuples
  RooDataSet Data("Data","dataset",Tree,*ntplVars,mainCut,"weight");
  w->import(Data);
  cout << endl;
  cout << "Data:" << endl;
  Data.Print("v");
  cout << "---- nX:  " <<Data.sumEntries() << endl;   
  cout << endl;  
 

  /*TTree* newTree=(TTree*)dataset2tree(Data_nomatch,ntplVars);
  RooDataSet Data("Data","dataset",newTree,*ntplVars_match,mainCut,"weight");
  w->import(Data);
  cout << endl;
  cout << "Data:" << endl;
  Data.Print("v");
  cout << "---- nX:  " <<Data.sumEntries() << endl;   
  cout << endl;  */
 
  cout << endl; cout << "Now Add Data" << endl;
  
  AddData(w); 
  AddSignalMC(w);  
  AddSignalTemplate(w);   
  AddBkgTemplate(w);    
   fitresults = ModelFit(w);

   // PlotSignalTemplates(w);

  return;
}



// Add Data Set
void AddData(RooWorkspace* w) {  
  RooDataSet* ReducedData;  
  ReducedData = (RooDataSet*) *w->data("Data")->reduce(*w->var("preselphcorrPHIso"),mainCut);////
  w->import(*ReducedData);  
  cout << "Reduced Data: " << endl;
  ReducedData->Print("v");
  cout << " nX for ReducedData:  " << ReducedData->sumEntries() << endl; 
  cout << endl;
  RooDataHist* ReducedDataHist = (RooDataHist*)ReducedData->binnedClone("DataHist","DataHist");
  w->import(*ReducedDataHist);  
  }



// Add Signal Template
void AddSignalTemplate(RooWorkspace* w) {  
  RooDataSet* ReducedData;  
  ReducedData = (RooDataSet*) *w->data("Data")->reduce(*w->var("preselphcorrPHIso"),mainCut+TString::Format("&&preselphsieie<0.017"));////
  ReducedData->SetNameTitle("SignalData","SignalData");
  w->import(*ReducedData);  
  cout << "Signal Data: " << endl;
  ReducedData->Print("v");
  cout << " nX for SignalData:  " << ReducedData->sumEntries() << endl; 
  cout << endl;
  RooDataHist* ReducedDataHist = (RooDataHist*)ReducedData->binnedClone("SignalDataHist","SignalDataHist");
  RooHistPdf* ReducedHistPdf = new RooHistPdf("SignalDataHistPdf","SignalDataHistPdf",*w->var("preselphcorrPHIso"),*ReducedDataHist);
  w->import(*ReducedDataHist);  
  w->import(*ReducedHistPdf);  
  }




// Add Signal Template
void AddBkgTemplate(RooWorkspace* w) {  
  RooDataSet* ReducedData;  
  ReducedData = (RooDataSet*) *w->data("Data")->reduce(*w->var("preselphcorrPHIso"),mainCut+TString::Format("&&preselphsieie>0.017&&preselphsieie<0.02"));////
  ReducedData->SetNameTitle("BkgData","BkgData");
  w->import(*ReducedData);  
  cout << "Bkg Data: " << endl;
  ReducedData->Print("v");
  cout << " nX for BkgData:  " << ReducedData->sumEntries() << endl; 
  cout << endl;
  RooDataHist* ReducedDataHist = (RooDataHist*)ReducedData->binnedClone("BkgDataHist","BkgDataHist");
  RooHistPdf* ReducedHistPdf = new RooHistPdf("BkgDataHistPdf","BkgDataHistPdf",*w->var("preselphcorrPHIso"),*ReducedDataHist);
  w->import(*ReducedDataHist);  
  w->import(*ReducedHistPdf);  

  }


void AddSignalMC(RooWorkspace* w){

  //Add Variables
  RooArgSet* ntplVars = defineVariables();  
  //chain summing up all production modes
  TChain* Tree  = new TChain(); 
  //Tree->Add("./rootfiles/photon300to470TestPurity.root/tree/tree");////
  Tree->Add("./rootfiles/photon_MC_tree_TestPurity.root/tree/tree");////
  Tree->SetTitle("TreeMC");
  Tree->SetName("TreeMC");
  RooDataSet SignalMC("MC","SignalMC",Tree,*ntplVars,mainCut,"weight");
  w->import(SignalMC);
  cout << endl;
  cout << "SignalMC:" << endl;
  SignalMC.Print("v");
  cout << "---- nX:  " <<SignalMC.sumEntries() << endl;   
  cout << endl; 
  RooDataSet* ReducedMC;  
  ReducedMC = (RooDataSet*) *w->data("MC")->reduce(*w->var("preselphcorrPHIso"),mainCut+TString::Format("&&preselphsieie<0.017"));//// 
  RooDataHist* ReducedMCHist = (RooDataHist*)ReducedMC->binnedClone("SignalMCHist","SignalMCHist");
  RooHistPdf* ReducedHistPdf = new RooHistPdf("SignalMCHistPdf","SignalMCHistPdf",*w->var("preselphcorrPHIso"),*ReducedMCHist);
  w->import(*ReducedMCHist);  
  w->import(*ReducedHistPdf);  


}

void PlotSignalTemplates(RooWorkspace* w){

  RooDataHist* Data =(RooDataHist*) *w->data("SignalDataHist");
  RooHistPdf* MC =(RooHistPdf*) *w->pdf("SignalMCHistPdf");
  TCanvas* ctmp = new TCanvas("ctmp","Signal Shape",1);
  RooPlot* plot;
  RooRealVar* ph_iso = w->var("preselphcorrPHIso");  
  ph_iso->setUnit("GeV");
  ph_iso->setRange("fit range", minFit, maxFit); 
  plot = ph_iso->frame(minFit, maxFit,40);
  Data->plotOn(plot,MarkerSize(0.6)); 
  MC->plotOn(plot,LineColor(8));
  plot->GetXaxis()->SetTitle("PFIso - Photon [GeV]");
  plot->GetYaxis()->SetTitle("Events");
  plot->Draw();
  TLegend *legdata = new TLegend(0.5334677,0.680339,0.8245968,0.8958475, "","brNDC");
  legdata->AddEntry(plot->getObject(2),"Data Signal","LP");
  legdata->AddEntry(plot->getObject(1),"MC Signal","L");
  legdata->SetTextSize(0.035);
  legdata->SetTextFont(42);
  legdata->SetBorderSize(0);
  legdata->SetFillStyle(0);
  legdata->Draw("same");
  
  ctmp->cd();
  ctmp->SetLogy(0);
  ctmp->SaveAs("plots/PFIsoPhoton_SignalShape.pdf");
  ctmp->SaveAs("plots/PFIsoPhoton_SignalShape.png");
  ctmp->SetLogy(1);
  ctmp->SaveAs("plots/PFIsoPhoton_SignalShape_LOG.pdf");
  ctmp->SaveAs("plots/PFIsoPhoton_SignalShape_LOG.png");

}


RooFitResult* ModelFit(RooWorkspace* w) {
  
  RooFitResult* fitresult;
  RooPlot* plot;
  
  TLatex *text = new TLatex();
  text->SetNDC();
  text->SetTextSize(0.04);
  
  
  // Fit data with background pdf for data limit
  RooRealVar* ph_iso = w->var("preselphcorrPHIso");  
  ph_iso->setUnit("GeV");
  ph_iso->setRange("fit range", minFit, maxFit); 
  RooDataHist* data;
  data = (RooDataHist*) w->data("DataHist");
  RooDataHist* dataSignal;
  dataSignal = (RooDataHist*) w->data("SignalDataHist");
  RooDataHist* dataBkg;
  dataBkg = (RooDataHist*) w->data("BkgDataHist");
  double initFrac = 1-dataBkg->sumEntries()/dataSignal->sumEntries();
    
  RooRealVar bkgYield("bkgYield","bkgYield",dataBkg->sumEntries(),0.,data->sumEntries());
  RooRealVar sigYield("sigYield","sigYield",dataSignal->sumEntries(),0., data->sumEntries());
  RooRealVar frac("frac","frac",initFrac,0.5, 1);

  RooHistPdf* fitFuncSig =(RooHistPdf*) *w->pdf("SignalDataHistPdf");
  RooHistPdf* fitFuncBkg =(RooHistPdf*) *w->pdf("BkgDataHistPdf");
  
  // RooExtendPdf fitFuncSigE("SignalDataHistPdfE", "SignalDataHistPdfE", *fitFuncSig, sigYield);
  //RooExtendPdf fitFuncBkgE("BkgDataHistPdfE", "BkgDataHistPdfE", *fitFuncBkg, bkgYield);
    
  // RooAddPdf* fitFunc = new RooAddPdf("fitFunc","fitFunc",RooArgList(fitFuncSigE,fitFuncBkgE));
  RooAddPdf* fitFunc = new RooAddPdf("fitFunc","fitFunc",*fitFuncSig,*fitFuncBkg,frac);
  fitresult = fitFunc->fitTo(*data, Range(minFit,maxFit),RooFit::FitOptions("MHTER"), SumW2Error(kTRUE), Save(kTRUE));   //
  
  std::cout<<"********************************  Fit results  ***********************************"<<std::endl;
  fitresult->Print("V");
  w->import(*fitFunc);
  //************************************************
  // Plot  fit results
  TCanvas* ctmp = new TCanvas("ctmp","Photon Iso Fit ",1);
  Int_t nbinsx(10);
 
  TH1F* h_data;// = new TH1F("h_data","h_data", nbinsx,minFit, maxFit);
  TH1F* h_pdf;
  TH1F* h_sig;
  TH1F* h_bkg;
  h_data = (TH1F*) data->createHistogram("preselphcorrPHIso");
  h_pdf =  (TH1F*) fitFunc->createHistogram("preselphcorrPHIso");
  h_sig =  (TH1F*) fitFuncSig->createHistogram("preselphcorrPHIso");
  h_bkg =  (TH1F*) fitFuncBkg->createHistogram("preselphcorrPHIso");
  //  h_data = (TH1F*) data->createHistogram("h_data",*w->var("preselphcorrPHIso"),Binning(nbinsx,minFit, maxFit));
  //h_pdf =  (TH1F*) fitFunc->createHistogram("h_pdf",*w->var("preselphcorrPHIso"),Binning(nbinsx,minFit, maxFit));
  std::cout<<h_pdf->GetNbinsX()<<std::endl;
  h_pdf ->Scale(h_data->Integral()/h_pdf->Integral());
  h_sig ->Scale(frac.getVal()*h_data->Integral()/h_sig->Integral());
  h_bkg ->Scale((1-frac.getVal())*h_data->Integral()/h_bkg->Integral());

  h_data->Rebin(2);
  h_pdf->Rebin(2);
  h_sig->Rebin(2);
  h_bkg->Rebin(2);
  h_data->SetMarkerSize(0.5);
  h_pdf->SetLineColor(kBlue);
  h_sig->SetLineColor(8);
  h_bkg->SetLineColor(kRed);
  h_pdf->SetLineWidth(2);
  h_sig->SetLineWidth(2);
  h_bkg->SetLineWidth(2);

  ctmp->cd();
  plot = ph_iso->frame(minFit, maxFit,nbinsx);
  data->plotOn(plot,RooFit::Invisible());    
  fitFunc->plotOn(plot,LineColor(kBlue),Range(minFit,maxFit),NormRange("fit range")); 
  fitFunc->plotOn(plot,Components("BkgDataHistPdf"),LineColor(kRed),Range(minFit,maxFit),NormRange("fit range")); 
  fitFunc->plotOn(plot,Components("SignalDataHistPdf"),LineColor(8),Range(minFit,maxFit),NormRange("fit range")); 
  
  double chi2 = plot->chiSquare(2);
  Int_t ndof = nbinsx;
  std::cout<<"------> "<< ndof<<std::endl;
  double prob = TMath::Prob(chi2*ndof, ndof);
  std::cout<<prob<<std::endl;
  
  data->plotOn(plot,MarkerSize(0.5));    
  

  
  //-------pad 1-------//
  //TPad * pad1 = new TPad("pad1", "pad1",0.01256281,0.1304945,0.5741206,1);  
  TPad * pad1 = new TPad("pad1", "pad1",0.01, 0.16, 1., 1.);  
  pad1->SetRightMargin(0.1);  
  pad1->SetLogy();
  pad1->Draw();
  pad1->cd();
  
  h_pdf->GetXaxis()->SetTitle("PFIso - Photon [GeV]");
  h_pdf->GetYaxis()->SetTitle("Events");
  h_pdf->GetYaxis()->SetRangeUser(0.01,h_data->GetMaximum()*10);
  //plot->Draw(); 
  h_pdf->Draw("hist");
  h_sig->Draw("histsame");
  h_bkg->Draw("histsame");
  h_data->Draw("pesame");
  TLegend *legdata = new TLegend(0.5334677,0.680339,0.8245968,0.8958475, "","brNDC");
  legdata->AddEntry(plot->getObject(4),"Data","LP");
  legdata->AddEntry(plot->getObject(3),"Signal Component","L");
  legdata->AddEntry(plot->getObject(2),"Background Component","L");
  legdata->AddEntry(plot->getObject(1),"Fit Model","L");
  legdata->SetTextSize(0.035);
  legdata->SetTextFont(42);
  legdata->SetBorderSize(0);
  legdata->SetFillStyle(0);
  legdata->Draw("same");
  
  int iPos=11 ;
  CMS_lumi( pad1,false,iPos );
    
  //write down the chi2 of the fit on the
  
  TPaveText* label_chi2= new TPaveText(0.644355,0.547,0.80583871,0.65822034,"brNDC");
  label_chi2->SetFillColor(kWhite);
  label_chi2->SetTextSize(0.035);
  label_chi2->SetTextFont(42);
  label_chi2->SetTextAlign(31); // align right
  label_chi2->AddText(TString::Format("Fit #chi^{2}/dof = %.2f", chi2));
  label_chi2->AddText(TString::Format("#chi^{2} Prob = %.2f", prob));
  // label_chi2->Draw("same");
    

    ctmp->cd();
    
    //-------pad 2------//
    TPad * pad2 = new TPad("pad2", "pad2",0.01,0.02,1.,0.23);

    pad2->SetLeftMargin(0.1789709);
    pad2->SetRightMargin(0.01565995);
    pad2->SetGrid();
    pad2->SetBottomMargin(0.4);
    pad2->SetRightMargin(0.1);
    pad2->Draw();
   
    pad2->cd();
    h_data->Sumw2();
    h_pdf->Sumw2();
    TH1F* h1_ratio1 = (TH1F*) h_data->Clone();
    TH1F* h1_ratio2 = (TH1F*)h_pdf->Clone();
    h1_ratio2->SetFillColor(kBlack);
    h1_ratio2->SetFillStyle(3003);
    h1_ratio2->SetMarkerSize(0);

    Double_t xmax = h1_ratio1->GetXaxis()->GetXmax();
    Double_t xmin = h1_ratio1->GetXaxis()->GetXmin();
    TLine* line = new TLine(xmin,1.,xmax,1.);
  
    std::cout<<h1_ratio1->GetXaxis()->GetXmax()<< "  " << h1_ratio1->GetXaxis()->GetXmin()<<std::endl;

    h1_ratio1->SetStats(0);
    h1_ratio1->Divide(h_pdf);
    h1_ratio2->Divide(h_pdf);
    h1_ratio1->SetMarkerStyle(20);
    h1_ratio1->SetMarkerSize(0.5);
    //  h1_ratio1->GetXaxis()->SetTitle(xAxis.c_str());
    h1_ratio1->GetYaxis()->SetRangeUser(0.5, 1.5); //
    h1_ratio1->GetXaxis()->SetRangeUser(plot->GetMinimum(),plot->GetMaximum()); //
    std::cout<<h1_ratio1->GetXaxis()->GetXmax()<< "  " << h1_ratio1->GetXaxis()->GetXmin()<<std::endl; 
    h1_ratio1->GetYaxis()->SetNdivisions(2,false);
    h1_ratio1->GetYaxis()->SetTitle("Data/Fit");
    h1_ratio1->GetYaxis()->SetTitleFont(42);
    h1_ratio1->GetXaxis()->SetTitleFont(42);
    h1_ratio1->GetXaxis()->SetTitle("PFIso - Photon [GeV]");
    
    h1_ratio1->GetXaxis()->SetTitleSize(0.18);
    h1_ratio1->GetXaxis()->SetLabelSize(0.16);
    h1_ratio1->GetXaxis()->SetLabelOffset(5.16);
    h1_ratio1->GetXaxis()->SetTitleOffset(0.6);

    h1_ratio1->GetYaxis()->SetLabelSize(0.16);
    h1_ratio1->GetYaxis()->SetTitleSize(0.18);
    h1_ratio1->GetYaxis()->SetTitleOffset(0.35);
    
    
  for(int j = 0;j<=h1_ratio1->GetNbinsX();j++){
      
      if(h_pdf->GetBinContent(j))  h1_ratio1->SetBinError(j,sqrt(pow(h_data->GetBinError(j)/h_pdf->GetBinContent(j), 2)+ pow(h_data->GetBinContent(j)*h_pdf->GetBinError(j)/(h_pdf->GetBinContent(j)*h_pdf->GetBinContent(j)),2)));
      else h1_ratio1->SetBinError(j,0.);
    }
    h1_ratio1->Draw("PEX0");
  
for(int j = 0;j<=h1_ratio2->GetNbinsX();j++){
      if(h_pdf->GetBinContent(j)) h1_ratio2->SetBinError(j,h_pdf->GetBinError(j)/h_pdf->GetBinContent(j));
      else h1_ratio2->SetBinError(j,0.);
    }
//   h1_ratio2->Draw("E2same");

 line->SetLineWidth(1.);
 line->Draw("same");

 ctmp->cd();
 pad1->SetLogy(0);
 ctmp->SaveAs("plots/PFIsoPhoton_fit.pdf");
 ctmp->SaveAs("plots/PFIsoPhoton_fit.png");
 pad1->SetLogy(1);
 ctmp->SaveAs("plots/PFIsoPhoton_fit_LOG.pdf");
 ctmp->SaveAs("plots/PFIsoPhoton_fit_LOG.png");

  RooFitResult* r;
    
  return r;
}



