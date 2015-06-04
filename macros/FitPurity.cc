using namespace RooFit;
using namespace RooStats ;
#include "CMS_lumi.C"
static const Int_t NCAT = 4;  // chiara
//TString mainCut = "(hltphoton150||hltphoton135) && nphotons==1&&signaljetpt>110 && abs(signaljeteta)<2.4 && njets<3 && preselphpt>170 && ((abs(preselpheta)<1.4442)||(abs(preselpheta)>1.566 && abs(preselpheta)<2.5))";
TString mainCut = "nphotons==1&& preselphpt>50 && ((abs(preselpheta)<1.4442)||(abs(preselpheta)>1.566 && abs(preselpheta)<2.5))";

void AddData(RooWorkspace*);

RooFitResult*  ModelFit(RooWorkspace*);


RooArgSet* defineVariables() {
  RooRealVar* ph_iso  = new RooRealVar("preselphcorrPHIso", "PFIsophoton",0.,10,"GeV");
  RooRealVar* ph_sieie  = new RooRealVar("preselphsieie", "PFIsophoton",0.,10,"GeV");
  RooRealVar* ph_eta = new RooRealVar("preselpheta", "eta(g)",-10,10,"");
  RooRealVar* ph_pt = new RooRealVar("preselphpt", "pt(g)",0,1000,"");
  RooRealVar* weight = new RooRealVar("weight","weightings",0,1000,"");

  RooRealVar* nphotons = new RooRealVar("nphotons","nphotons",0,10,"");
  RooRealVar* hltphoton135 = new RooRealVar("hltphoton135","hltphoton135",0,1,"");
  RooRealVar* hltphoton150 = new RooRealVar("hltphoton150","hltphoton150",0,1,"");
  RooRealVar* signaljetpt = new RooRealVar("signaljetpt","signaljetpt",0,2000.,"");
  RooRealVar* signaljeteta = new RooRealVar("signaljeteta","signaljeteta",-5.,5.,"");
  RooRealVar* njets = new RooRealVar("njets","njets",0,20,"");
  RooRealVar* nvtx = new RooRealVar("nvtx", "nvtx", 0, 50, "");

  RooArgSet* ntplVars = new RooArgSet(*ph_iso,*ph_sieie,*ph_eta, *ph_pt, *weight);
  RooArgSet* ntplVarsSpectators = new RooArgSet(*nphotons, *hltphoton135, *hltphoton150,*signaljetpt,*signaljeteta,*njets,*nvtx);
  ntplVars->add(*ntplVarsSpectators);
  return ntplVars;
}




void runfits() {
  
  TString card_name("InitWS.rs");
  HLFactory hlf("HLFactory", card_name, false);
  RooWorkspace* w = hlf.GetWs(); 
  RooFitResult* fitresults;
  // Luminosity:
  Float_t Lum = 19500.0;  
  RooRealVar lumi("lumi","lumi",Lum);
  w->import(lumi); 

  //Add Variables
  RooArgSet* ntplVars = defineVariables();  
  //chain summing up all production modes
  TChain* Tree  = new TChain(); 
  Tree->Add("./rootfiles/photonDataRunAtestPurity.root/tree/tree");////
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
  
  cout << endl; cout << "Now Add Data" << endl;
  AddData(w);   
  AddSignalTemplate(w);   
  AddBkgTemplate(w);   
 
  fitresults = ModelFit(w);

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
  ReducedData = (RooDataSet*) *w->data("Data")->reduce(*w->var("preselphcorrPHIso"),mainCut+TString::Format("&&preselphsieie<0.011"));////
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
  ReducedData = (RooDataSet*) *w->data("Data")->reduce(*w->var("preselphcorrPHIso"),mainCut+TString::Format("&&preselphsieie>0.011&&preselphsieie<0.014"));////
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







RooFitResult* ModelFit(RooWorkspace* w) {
  
  RooFitResult* fitresult;
  RooPlot* plot;
  Float_t minFit, maxFit; 
  minFit = 0;
  maxFit = 10;
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
    
  RooRealVar bkgYield("bkgYield","bkgYield",dataBkg->sumEntries(),0,data->sumEntries());
  RooRealVar sigYield("sigYield","sigYield",dataSignal->sumEntries(),0., data->sumEntries());
  RooRealVar frac("frac","frac",initFrac,0.9, 1);

  RooHistPdf* fitFuncSig =(RooHistPdf*) *w->pdf("SignalDataHistPdf");
  RooHistPdf* fitFuncBkg =(RooHistPdf*) *w->pdf("BkgDataHistPdf");
  
  RooExtendPdf fitFuncSigE("SignalDataHistPdfE", "SignalDataHistPdfE", *fitFuncSig, sigYield);
  RooExtendPdf fitFuncBkgE("BkgDataHistPdfE", "BkgDataHistPdfE", *fitFuncBkg, bkgYield);
    
  //RooAddPdf* fitFunc = new RooAddPdf("fitFunc","fitFunc",RooArgList(fitFuncSigE,fitFuncBkgE));
  RooAddPdf* fitFunc = new RooAddPdf("fitFunc","fitFunc",*fitFuncSig,*fitFuncBkg,frac);
  fitresult = fitFunc->fitTo(*data, Range(minFit,maxFit),RooFit::FitOptions("MHTER"), SumW2Error(kTRUE), Save(kTRUE));   //
  
  std::cout<<"********************************  Fit results  ***********************************"<<std::endl;
  fitresult->Print("V");
  w->import(*fitFunc);
  //************************************************
  // Plot  fit results
  TCanvas* ctmp = new TCanvas("ctmp","Photon Iso Fit ",1);
  Int_t nBins(120);
  plot = ph_iso->frame(minFit, maxFit,nBins);
  data->plotOn(plot,RooFit::Invisible());    
  fitFunc->plotOn(plot,LineColor(kBlue),Range(minFit,maxFit),NormRange("fit range")); 
  fitFunc->plotOn(plot,Components("BkgDataHistPdf"),LineColor(kRed),Range(minFit,maxFit),NormRange("fit range")); 
  fitFunc->plotOn(plot,Components("SignalDataHistPdf"),LineColor(kGreen),Range(minFit,maxFit),NormRange("fit range")); 
  
  double chi2 = plot->chiSquare(2);
  Int_t ndof = nBins;
  std::cout<<"------> "<< ndof<<std::endl;
  double prob = TMath::Prob(chi2*ndof, ndof);
  std::cout<<prob<<std::endl;
  
  data->plotOn(plot,XErrorSize(0));    
  
  TH1F* h_data = new TH1F("h_data","h_data", 120,minFit, maxFit);
  TH1F* h_pdf = new TH1F("h_pdf","h_pdf", 120,minFit, maxFit);
  h_data = (TH1F*) data->createHistogram("preselphcorrPHIso", 120, 0, 0);
  h_pdf =  (TH1F*) fitFunc->createHistogram("preselphcorrPHIso",120,0,0);
  h_pdf ->Scale(h_data->Integral()/h_pdf->Integral());
  ctmp->cd();
  
  //-------pad 1-------//
  //TPad * pad1 = new TPad("pad1", "pad1",0.01256281,0.1304945,0.5741206,1);  
  TPad * pad1 = new TPad("pad1", "pad1",0.01, 0.16, 1., 1.);  
  pad1->SetRightMargin(0.1);  
  pad1->SetLogy();
  pad1->Draw();
  pad1->cd();
  
  plot->GetXaxis()->SetTitle("PFIso - Photon [GeV]");
  plot->GetYaxis()->SetTitle("Events");
  //plot->SetAxisRange(0.001,plotPhotonsMassBkg->GetMaximum()*1.5,"Y");
  plot->Draw();  
  
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
  
  TPaveText* label_chi2= new TPaveText(0.6744355,0.650847,0.80583871,0.705822034,"brNDC");
  label_chi2->SetFillColor(kWhite);
  label_chi2->SetTextSize(0.035);
  label_chi2->SetTextFont(42);
  label_chi2->SetTextAlign(31); // align right
  label_chi2->AddText(TString::Format("Fit #chi^{2}/dof = %.2f", chi2));
  label_chi2->AddText(TString::Format("#chi^{2} Prob = %.2f", prob));
  //label_chi2->Draw("same");
    

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
  

    h1_ratio1->SetStats(0);
    h1_ratio1->Divide(h_pdf);
    h1_ratio2->Divide(h_pdf);
    h1_ratio1->SetMarkerStyle(20);
    h1_ratio1->SetMarkerSize(0.6);
    //  h1_ratio1->GetXaxis()->SetTitle(xAxis.c_str());
    h1_ratio1->GetYaxis()->SetRangeUser(0., 2.); // cwr zoom
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
 ctmp->SaveAs("~/www/MonoJet/PFIsoPhoton_fit.pdf");
 ctmp->SaveAs("~/www/MonoJet/PFIsoPhoton_fit.png");
 ctmp->SetLogy();
 ctmp->SaveAs("~/www/MonoJet/PFIsoPhoton_fit_LOG.pdf");
 ctmp->SaveAs("~/www/MonoJet/PFIsoPhoton_fit_LOG.png");

  RooFitResult* r;
    
  return r;
}



