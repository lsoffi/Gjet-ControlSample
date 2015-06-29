#include <memory>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h" 
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include <TH1F.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TPRegexp.h>

class MonoJetTreeMaker : public edm::EDAnalyzer {
    public:
        explicit MonoJetTreeMaker(const edm::ParameterSet&);
        ~MonoJetTreeMaker();
        
        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
        double getChargedHadronEAForPhotonIso(double eta);     
        double getNeutralHadronEAForPhotonIso(double eta);     
        double getGammaEAForPhotonIso(double eta);     
    
    private:
        virtual void beginJob() ;
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob() ;
        
        virtual void beginRun(edm::Run const&, edm::EventSetup const&);
        virtual void endRun(edm::Run const&, edm::EventSetup const&);
        virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
        virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

        void initPileupWeights();      


        edm::InputTag pileupInfoTag;
        edm::InputTag verticesTag;
        edm::InputTag gensTag;
        edm::InputTag muonsTag;
        edm::InputTag electronsTag;
        edm::InputTag photonsTag;
        edm::InputTag tightmuonsTag;
        edm::InputTag tightelectronsTag;
        edm::InputTag tightphotonsTag;
        edm::InputTag tausTag;
        edm::InputTag jetsTag;
        edm::InputTag fatjetsTag;
        edm::InputTag prunedfatjetsTag;
        edm::InputTag pfmetTag;
        edm::InputTag t1pfmetTag;
        edm::InputTag calometTag;
        edm::InputTag pfmuptTag;
        edm::InputTag mumetTag;
        edm::InputTag phmetTag;
        edm::InputTag t1mumetTag;
        edm::InputTag t1phmetTag;
        edm::InputTag triggerResultsTag;
        edm::InputTag rhoTag;
        std::vector<std::string> triggerPathsVector;
        std::map<std::string, int> triggerPathsMap;
        bool isWorZMCSample;   
        bool cleanPhotonJet;   
        TTree* tree;
        TH1F* puhist;

        uint32_t event, run, lumi;
        int32_t  puobs, putrue; 
        uint32_t nvtx, nmuons, nelectrons, nphotons, ntightmuons, ntightelectrons, ntightphotons, ntaus, njets, ncentjets, nbjets, nfatjets, ncentfatjets, njetsnotfat, ncentjetsnotfat, nbjetsnotfat;
        uint32_t hltmet120, hltmet95jet80, hltmet105jet80, hltdoublemu, hltsinglemu, hltdoubleel, hltphoton135, hltphoton150;
        double   pfmet, pfmetphi, t1pfmet, t1pfmetphi, calomet, calometphi, pfmupt, pfmuphi, mumet, mumetphi, phmet, phmetphi, t1mumet, t1mumetphi, t1phmet, t1phmetphi;
        double   fatjetpt, fatjeteta, fatjetphi, fatjetmass, fatjettau2, fatjettau1, fatjetCHfrac, fatjetNHfrac, fatjetEMfrac, fatjetCEMfrac, fatjetmetdphi, fatjetprunedmass, fatjetmassdrop;
        double   signaljetpt, signaljeteta, signaljetphi, signaljetCHfrac, signaljetNHfrac, signaljetEMfrac, signaljetCEMfrac, signaljetmetdphi;
        double   secondjetpt, secondjeteta, secondjetphi, secondjetCHfrac, secondjetNHfrac, secondjetEMfrac, secondjetCEMfrac, secondjetmetdphi;
        double   thirdjetpt , thirdjeteta , thirdjetphi , thirdjetCHfrac , thirdjetNHfrac , thirdjetEMfrac , thirdjetCEMfrac , thirdjetmetdphi;
        double   jetjetdphi, jetmetdphimin;
        double   ht, dht, mht, alphat, apcjet, apcmet, apcjetmet, apcjetmax, apcjetmetmax, apcjetmin, apcjetmetmin; 
        int32_t  wzid, l1id, l2id, mu1pid, mu2pid, mu1id, mu2id, el1pid, el2pid, el1id, el2id; 
        double   wzmass, wzmt, wzpt, wzeta, wzphi, l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
  double   mu1pt, mu1eta, mu1phi, mu2pt, mu2eta, mu2phi, el1pt, el1eta, el1phi, el2pt, el2eta, el2phi, phpt, pheta, phphi;
  double preselphpt,preselpheta,preselphphi,preselphsieie,preselphr9,preselphcorrCHIso,preselphcorrNHIso,preselphcorrPHIso,preselphhoe;
        double   zmass, zpt, zeta, zphi, wmt, emumass, emupt, emueta, emuphi, zeemass, zeept, zeeeta, zeephi, wemt;
        double   wgt, puwgt, weight;
};

MonoJetTreeMaker::MonoJetTreeMaker(const edm::ParameterSet& iConfig): 
    pileupInfoTag(iConfig.getParameter<edm::InputTag>("pileup")),
    verticesTag(iConfig.getParameter<edm::InputTag>("vertices")),
    gensTag((iConfig.existsAs<edm::InputTag>("gens") ? iConfig.getParameter<edm::InputTag>("gens") : edm::InputTag("genParticles"))),
    muonsTag(iConfig.getParameter<edm::InputTag>("muons")),
    electronsTag(iConfig.getParameter<edm::InputTag>("electrons")),
    photonsTag(iConfig.getParameter<edm::InputTag>("photons")),
    tightmuonsTag(iConfig.getParameter<edm::InputTag>("tightmuons")),
    tightelectronsTag(iConfig.getParameter<edm::InputTag>("tightelectrons")),
    tightphotonsTag(iConfig.getParameter<edm::InputTag>("tightphotons")),
    tausTag(iConfig.getParameter<edm::InputTag>("taus")),
    jetsTag(iConfig.getParameter<edm::InputTag>("jets")),
    fatjetsTag(iConfig.getParameter<edm::InputTag>("fatjets")),
    prunedfatjetsTag(iConfig.getParameter<edm::InputTag>("prunedfatjets")),
    pfmetTag(iConfig.getParameter<edm::InputTag>("pfmet")),
    t1pfmetTag(iConfig.getParameter<edm::InputTag>("t1pfmet")),
    calometTag(iConfig.getParameter<edm::InputTag>("calomet")),
    pfmuptTag(iConfig.getParameter<edm::InputTag>("pfmupt")),
    mumetTag(iConfig.getParameter<edm::InputTag>("mumet")),
    phmetTag(iConfig.getParameter<edm::InputTag>("phmet")),
    t1mumetTag(iConfig.getParameter<edm::InputTag>("t1mumet")),
    t1phmetTag(iConfig.getParameter<edm::InputTag>("t1phmet")),
    triggerResultsTag(iConfig.getParameter<edm::InputTag>("triggerResults")),
    rhoTag(iConfig.getParameter<edm::InputTag>("rho")),
    isWorZMCSample(iConfig.getParameter<bool>("isWorZMCSample")),
    cleanPhotonJet(iConfig.getParameter<bool>("cleanPhotonJet")),
    wgt(iConfig.getParameter<double>("weight"))
    
{
    initPileupWeights();
}


MonoJetTreeMaker::~MonoJetTreeMaker() {
    if (puhist) delete puhist;
}

void MonoJetTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using namespace edm;
    using namespace reco;
    using namespace std;

    // Get handles to all the requisite collections
    Handle<TriggerResults> triggerResultsH;
    iEvent.getByLabel(triggerResultsTag, triggerResultsH);

    Handle<vector<PileupSummaryInfo> > pileupInfoH;
    iEvent.getByLabel(pileupInfoTag, pileupInfoH);

    Handle<vector<Vertex> > verticesH;
    iEvent.getByLabel(verticesTag, verticesH);

    Handle<View<GenParticle> > gensH;
    if (isWorZMCSample) iEvent.getByLabel(gensTag, gensH);

    Handle<MuonRefVector> muonsH;
    iEvent.getByLabel(muonsTag, muonsH);
    MuonRefVector muons = *muonsH;

    Handle<GsfElectronRefVector> electronsH;
    iEvent.getByLabel(electronsTag, electronsH);
    GsfElectronRefVector electrons = *electronsH;

    Handle<PhotonRefVector> photonsH;
    iEvent.getByLabel(photonsTag, photonsH);
    PhotonRefVector photons = *photonsH;

 
    Handle<MuonRefVector> tightmuonsH;
    iEvent.getByLabel(tightmuonsTag, tightmuonsH);
    MuonRefVector tightmuons = *tightmuonsH;

    Handle<GsfElectronRefVector> tightelectronsH;
    iEvent.getByLabel(tightelectronsTag, tightelectronsH);
    GsfElectronRefVector tightelectrons = *tightelectronsH;

    Handle<PhotonRefVector> tightphotonsH;
    iEvent.getByLabel(tightphotonsTag, tightphotonsH);
    PhotonRefVector tightphotons = *tightphotonsH;

    Handle<View<pat::Tau> > tausH;
    iEvent.getByLabel(tausTag, tausH);

    Handle<View<pat::Jet> > jetsH;
    iEvent.getByLabel(jetsTag, jetsH);

    Handle<View<pat::Jet> > fatjetsH;
    iEvent.getByLabel(fatjetsTag, fatjetsH);

    Handle<View<pat::Jet> > prunedfatjetsH;
    iEvent.getByLabel(prunedfatjetsTag, prunedfatjetsH);

    Handle<View<MET> > pfmetH;
    iEvent.getByLabel(pfmetTag, pfmetH);

    Handle<View<MET> > t1pfmetH;
    iEvent.getByLabel(t1pfmetTag, t1pfmetH);

    Handle<View<MET> > calometH;
    iEvent.getByLabel(calometTag, calometH);

    Handle<View<MET> > pfmuptH;
    iEvent.getByLabel(pfmuptTag, pfmuptH);

    Handle<View<MET> > mumetH;
    iEvent.getByLabel(mumetTag, mumetH);

    Handle<View<MET> > phmetH;
    iEvent.getByLabel(phmetTag, phmetH);

    Handle<View<MET> > t1mumetH;
    iEvent.getByLabel(t1mumetTag, t1mumetH);

    Handle<View<MET> > t1phmetH;
    iEvent.getByLabel(t1phmetTag, t1phmetH);


    Handle<double> rhoH;
    iEvent.getByLabel(rhoTag, rhoH);
    double rho = *rhoH;

    // Event, lumi, run info
    event = iEvent.id().event();
    run   = iEvent.id().run();
    lumi  = iEvent.luminosityBlock();

    // Trigger info
    hltdoublemu          = 0;
    hltsinglemu          = 0;
    hltdoubleel          = 0;
    hltmet120            = 0;
    hltmet95jet80        = 0;
    hltmet105jet80       = 0;
    hltphoton135         = 0;   
    hltphoton150         = 0;   
 
    for (size_t i = 0; i < triggerPathsVector.size(); i++) {
        if (triggerPathsMap[triggerPathsVector[i]] == -1) continue;
        if (i == 0 && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) hltdoublemu    = 1; // Double muon triggers
        if (i == 1 && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) hltdoublemu    = 1; // Double muon triggers
        if (i == 2 && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) hltsinglemu    = 1; // Single muon triggers
        if (i == 3 && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) hltdoubleel    = 1; // Double electron triggers
        if (i == 4 && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) hltdoubleel    = 1; // Double electron triggers
        if (i == 5 && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) hltmet120      = 1; // MET trigger trigger
        if (i == 6 && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) hltmet95jet80  = 1; // Jet-MET trigger
        if (i == 7 && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) hltmet105jet80 = 1; // Jet-MET trigger
        if (i == 8 && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) hltphoton135   = 1; // Single Photon trigger
        if (i == 9 && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) hltphoton150   = 1; // Single Photon trigger
    }

    // Pileup info
    nvtx   = verticesH->size();
    puobs  = 0;
    putrue = 0;
    puwgt  = 1.;
    if (pileupInfoH.isValid()) {
        for (vector<PileupSummaryInfo>::const_iterator pileupInfo_iter = pileupInfoH->begin(); pileupInfo_iter != pileupInfoH->end(); ++pileupInfo_iter) {
            if (pileupInfo_iter->getBunchCrossing() == 0) {
                puobs  = pileupInfo_iter->getPU_NumInteractions();
                putrue = pileupInfo_iter->getTrueNumInteractions();
                puwgt = puhist->GetBinContent(puhist->FindBin(putrue));
            }
        }
    }
    weight = wgt * puwgt;

    // MET information 
    calomet    = calometH->front().et();
    calometphi = calometH->front().phi();
 
    pfmet      = pfmetH->front().et();
    pfmetphi   = pfmetH->front().phi();
 
    t1pfmet    = t1pfmetH->front().et();
    t1pfmetphi = t1pfmetH->front().phi();
  
    pfmupt     = pfmuptH->front().et();
    pfmuphi    = pfmuptH->front().phi();
 
    mumet      = mumetH->front().et();
    mumetphi   = mumetH->front().phi();
 
    phmet      = phmetH->front().et();
    phmetphi   = phmetH->front().phi();

    t1mumet    = t1mumetH->front().et();
    t1mumetphi = t1mumetH->front().phi();
 
    t1phmet    = t1phmetH->front().et();
    t1phmetphi = t1phmetH->front().phi();

    // Jet information
    int hardestPhotonIndex = -1;
    double hardestPhotonPt = 0.0;
    for (size_t i = 0; i < tightphotons.size(); i++) {
        if (tightphotons[i]->pt() > hardestPhotonPt) {
            hardestPhotonIndex = i;
            hardestPhotonPt = tightphotons[i]->pt();
        }
    }

    int hardestPreselPhotonIndex = -1;
    double hardestPreselPhotonPt = 0.0;
    for (size_t i = 0; i < photons.size(); i++) {
        if (photons[i]->pt() > hardestPreselPhotonPt) {
            hardestPreselPhotonIndex = i;
            hardestPreselPhotonPt = photons[i]->pt();
        }
    }

    pat::JetCollection jets;
    for (View<pat::Jet>::const_iterator jets_iter = jetsH->begin(); jets_iter != jetsH->end(); ++jets_iter) {
        //if (jets_iter->electronEnergyFraction() > 0.5 || jets_iter->muonEnergyFraction() > 0.5) continue;
        if (fabs(jets_iter->eta()) > 4.5) continue;
        if (cleanPhotonJet && hardestPhotonIndex >= 0 && deltaR(jets_iter->eta(), jets_iter->phi(), tightphotons[hardestPhotonIndex]->eta(), tightphotons[hardestPhotonIndex]->phi()) < 0.5) continue;
        bool muonoverlap = false;
        for (size_t i = 0; i < muons.size(); i++) {
            if (deltaR(jets_iter->eta(), jets_iter->phi(), muons[i]->eta(), muons[i]->phi()) < 0.5) muonoverlap = true;
        }
        if (muonoverlap) continue;
        bool passjetid = false;
        if (jets_iter->neutralHadronEnergyFraction() < 0.99 && jets_iter->neutralEmEnergyFraction() < 0.99 && jets_iter->getPFConstituents().size() > 1) {
            if (fabs(jets_iter->eta()) > 2.4) passjetid = true;
            else if (fabs(jets_iter->eta()) <= 2.4 && jets_iter->chargedHadronEnergyFraction() > 0. && jets_iter->chargedEmEnergyFraction() < 0.99 && jets_iter->chargedMultiplicity() > 0) passjetid = true;
        }
        if (!passjetid) continue;
        jets.push_back(*jets_iter);
    }

    njets     = 0;
    ncentjets = 0;
    nbjets    = 0;
    for (size_t i = 0; i < jets.size(); i++) {
        if (jets[i].pt() > 30) njets++;
        if (jets[i].pt() > 30 && fabs(jets[i].eta()) < 2.5) ncentjets++;
        if (jets[i].pt() > 30 && fabs(jets[i].eta()) < 2.4 && jets[i].bDiscriminator("combinedSecondaryVertexBJetTags") > 0.679) nbjets++;
    }

    int hardestJetIndex = -1;
    double hardestJetPt = 0.0;
    for (size_t i = 0; i < jets.size(); i++) {
        if (jets[i].pt() > hardestJetPt) {
            hardestJetIndex = i;
            hardestJetPt = jets[i].pt();
        }                        
    }

    int secondJetIndex = -1;
    double secondJetPt = 0.0;
    for (size_t i = 0; i < jets.size(); i++) {
        if (hardestJetIndex >= 0 && i != unsigned(hardestJetIndex) && jets[i].pt() > secondJetPt) {
            secondJetIndex = i;
            secondJetPt = jets[i].pt();
        }                        
    }

    int thirdJetIndex = -1;
    double thirdJetPt = 0.0;
    for (size_t i = 0; i < jets.size(); i++) {
        if (hardestJetIndex >= 0 && secondJetIndex >= 0 && i != unsigned(hardestJetIndex) && i != unsigned(secondJetIndex) && jets[i].pt() > thirdJetPt) {
            thirdJetIndex = i;
            thirdJetPt = jets[i].pt();
        }                        
    }

    signaljetpt      = 0.0;
    signaljeteta     = 0.0;
    signaljetphi     = 0.0;
    signaljetCHfrac  = 0.0;
    signaljetNHfrac  = 0.0;
    signaljetEMfrac  = 0.0;
    signaljetCEMfrac = 0.0;
    signaljetmetdphi = 0.0;
    secondjetpt      = 0.0;
    secondjeteta     = 0.0;
    secondjetphi     = 0.0;
    secondjetCHfrac  = 0.0;
    secondjetNHfrac  = 0.0;
    secondjetEMfrac  = 0.0;
    secondjetCEMfrac = 0.0;
    secondjetmetdphi = 0.0;
    thirdjetpt       = 0.0;
    thirdjeteta      = 0.0;
    thirdjetphi      = 0.0;
    thirdjetCHfrac   = 0.0;
    thirdjetNHfrac   = 0.0;
    thirdjetEMfrac   = 0.0;
    thirdjetCEMfrac  = 0.0;
    thirdjetmetdphi  = 0.0;
    jetjetdphi       = 0.0;
    jetmetdphimin    = 0.0;

    if (hardestJetIndex >= 0) {
        signaljetpt      = jets[hardestJetIndex].pt();
        signaljeteta     = jets[hardestJetIndex].eta();
        signaljetphi     = jets[hardestJetIndex].phi();
        signaljetCHfrac  = jets[hardestJetIndex].chargedHadronEnergyFraction();
        signaljetNHfrac  = jets[hardestJetIndex].neutralHadronEnergyFraction();
        signaljetEMfrac  = jets[hardestJetIndex].neutralEmEnergyFraction();
        signaljetCEMfrac = jets[hardestJetIndex].chargedEmEnergyFraction();
    }

    if (secondJetIndex  >= 0) {
        secondjetpt      = jets[secondJetIndex].pt();
        secondjeteta     = jets[secondJetIndex].eta();
        secondjetphi     = jets[secondJetIndex].phi();
        secondjetCHfrac  = jets[secondJetIndex].chargedHadronEnergyFraction();
        secondjetNHfrac  = jets[secondJetIndex].neutralHadronEnergyFraction();
        secondjetEMfrac  = jets[secondJetIndex].neutralEmEnergyFraction();
        secondjetCEMfrac = jets[secondJetIndex].chargedEmEnergyFraction();
    }

    if (thirdJetIndex   >= 0) {
        thirdjetpt       = jets[thirdJetIndex].pt();
        thirdjeteta      = jets[thirdJetIndex].eta();
        thirdjetphi      = jets[thirdJetIndex].phi();
        thirdjetCHfrac   = jets[thirdJetIndex].chargedHadronEnergyFraction();
        thirdjetNHfrac   = jets[thirdJetIndex].neutralHadronEnergyFraction();
        thirdjetEMfrac   = jets[thirdJetIndex].neutralEmEnergyFraction();
        thirdjetCEMfrac  = jets[thirdJetIndex].chargedEmEnergyFraction();
    }

    if (signaljetpt > 0.0 && secondjetpt > 0.0) jetjetdphi       = deltaPhi(signaljetphi, secondjetphi);
    if (signaljetpt > 0.0)                      signaljetmetdphi = deltaPhi(signaljetphi, mumetphi);
    if (secondjetpt > 0.0)                      secondjetmetdphi = deltaPhi(secondjetphi, mumetphi);
    if (thirdjetpt  > 0.0)                      thirdjetmetdphi  = deltaPhi(thirdjetphi , mumetphi);

    std::vector<double> jetmetdphiminvector;
    for (size_t i = 0; i < jets.size(); i++) {
        if (jets[i].pt() > 30) {
            double jetphi = atan2(sin(jets[i].phi()), cos(jets[i].phi()));
            jetmetdphiminvector.push_back(fabs(deltaPhi(jetphi, mumetphi)));
        }
    }
    if (jetmetdphiminvector.size() > 0) jetmetdphimin = *min_element(jetmetdphiminvector.begin(), jetmetdphiminvector.end());

    // Fat jets
    nfatjets = 0;

    fatjetpt         = 0.0;
    fatjeteta        = 0.0;
    fatjetphi        = 0.0;
    fatjetmass       = 0.0;
    fatjettau2       = -1.0;
    fatjettau1       = 1.0;
    fatjetCHfrac     = 0.0;
    fatjetNHfrac     = 0.0;
    fatjetEMfrac     = 0.0;
    fatjetCEMfrac    = 0.0;
    fatjetmetdphi    = 0.0;
    fatjetprunedmass = 0.0;
    fatjetmassdrop   = -1.0;

    pat::JetCollection fatjets;
    for (View<pat::Jet>::const_iterator fatjets_iter = fatjetsH->begin(); fatjets_iter != fatjetsH->end(); ++fatjets_iter) {
        //if (fatjets_iter->electronEnergyFraction() > 0.5 || fatjets_iter->muonEnergyFraction() > 0.5) continue;
        if (fabs(fatjets_iter->eta()) > 4.5) continue;
        if (cleanPhotonJet && hardestPhotonIndex >= 0 && deltaR(fatjets_iter->eta(), fatjets_iter->phi(), tightphotons[hardestPhotonIndex]->eta(), tightphotons[hardestPhotonIndex]->phi()) < 0.5) continue;
        bool muonoverlap = false;
        for (size_t i = 0; i < muons.size(); i++) {
            if (deltaR(fatjets_iter->eta(), fatjets_iter->phi(), muons[i]->eta(), muons[i]->phi()) < 0.5) muonoverlap = true;
        }
        if (muonoverlap) continue;
        bool passjetid = false;
        if (fatjets_iter->neutralHadronEnergyFraction() < 0.99 && fatjets_iter->neutralEmEnergyFraction() < 0.99 && fatjets_iter->getPFConstituents().size() > 1) {
            if (fabs(fatjets_iter->eta()) > 2.4) passjetid = true;
            else if (fabs(fatjets_iter->eta()) <= 2.4 && fatjets_iter->chargedHadronEnergyFraction() > 0. && fatjets_iter->chargedEmEnergyFraction() < 0.99 && fatjets_iter->chargedMultiplicity() > 0) passjetid = true;
        }
        if (!passjetid) continue;
        pat::Jet fatjet = *fatjets_iter;
        fatjets.push_back(fatjet);
    }

    for (size_t i = 0; i < fatjets.size(); i++) {
        if (fatjets[i].pt() > 30) nfatjets++;
        if (fatjets[i].pt() > 30 && fabs(fatjets[i].eta()) < 2.5) ncentfatjets++;
    }

    int hardestFatJetIndex = -1;
    double hardestFatJetPt = 0.0;
    for (size_t i = 0; i < fatjets.size(); i++) {
        if (fatjets[i].pt() > hardestFatJetPt) {
            hardestFatJetIndex = i;
            hardestFatJetPt = fatjets[i].pt();
        }
    }

    if (hardestFatJetIndex >= 0) {
        fatjetpt       = fatjets[hardestFatJetIndex].pt();
        fatjeteta      = fatjets[hardestFatJetIndex].eta();
        fatjetphi      = fatjets[hardestFatJetIndex].phi();
        fatjetmass     = fatjets[hardestFatJetIndex].mass();
        fatjettau2     = fatjets[hardestFatJetIndex].userFloat("ca8PFJetsCleanVMaps:tau2");
        fatjettau1     = fatjets[hardestFatJetIndex].userFloat("ca8PFJetsCleanVMaps:tau1");
        fatjetCHfrac   = fatjets[hardestFatJetIndex].chargedHadronEnergyFraction();
        fatjetNHfrac   = fatjets[hardestFatJetIndex].neutralHadronEnergyFraction();
        fatjetEMfrac   = fatjets[hardestFatJetIndex].neutralEmEnergyFraction();
        fatjetCEMfrac  = fatjets[hardestFatJetIndex].chargedEmEnergyFraction();
        fatjetmetdphi  = deltaPhi(fatjetphi, mumetphi);;
    }

    int closestPrunedJetIndex = -1;
    double closestPrunedJetJetDR = 1000.;
    for (View<pat::Jet>::const_iterator prunedfatjets_iter = prunedfatjetsH->begin(); prunedfatjets_iter != prunedfatjetsH->end(); ++prunedfatjets_iter) {
        if (hardestFatJetIndex >= 0 && deltaR(prunedfatjets_iter->eta(), prunedfatjets_iter->phi(), fatjets[hardestFatJetIndex].eta(), fatjets[hardestFatJetIndex].phi()) < closestPrunedJetJetDR) {
            closestPrunedJetIndex = prunedfatjets_iter - prunedfatjetsH->begin();
            closestPrunedJetJetDR = deltaR(prunedfatjets_iter->eta(), prunedfatjets_iter->phi(), fatjets[hardestFatJetIndex].eta(), fatjets[hardestFatJetIndex].phi());
        }    
    }

    if (hardestFatJetIndex >= 0 && closestPrunedJetIndex >= 0 && closestPrunedJetJetDR < 0.25) {
        fatjetprunedmass = (*prunedfatjetsH)[closestPrunedJetIndex].mass();
        if ((*prunedfatjetsH)[closestPrunedJetIndex].numberOfDaughters() == 2) {
            double subjet1mass = (*prunedfatjetsH)[closestPrunedJetIndex].daughter(0)->mass();
            double subjet2mass = (*prunedfatjetsH)[closestPrunedJetIndex].daughter(1)->mass();
            double subjetmass = (subjet1mass > subjet2mass ? subjet1mass : subjet2mass);
            fatjetmassdrop = subjetmass / fatjetprunedmass;
        }
    }

    // Jets not overlapping with the fat-jet
    nbjetsnotfat    = 0;
    njetsnotfat     = 0;
    ncentjetsnotfat = 0;
    for (size_t i = 0; i < jets.size(); i++) {
        if (hardestFatJetIndex >= 0) {
            if (deltaR(jets[i].eta(), jets[i].phi(), fatjets[hardestFatJetIndex].eta(), fatjets[hardestFatJetIndex].phi()) > 1.0) {
                if (jets[i].pt() > 30) njetsnotfat++; 
                if (jets[i].pt() > 30 && fabs(jets[i].eta()) < 2.5) ncentjetsnotfat++; 
                if (jets[i].pt() > 30 && fabs(jets[i].eta()) < 2.4 && jets[i].bDiscriminator("combinedSecondaryVertexBJetTags") > 0.679) nbjetsnotfat++;
            }
        }                
        else {
            if (jets[i].pt() > 30) njetsnotfat++;
            if (jets[i].pt() > 30 && fabs(jets[i].eta()) < 2.5) ncentjetsnotfat++;
            if (jets[i].pt() > 30 && fabs(jets[i].eta()) < 2.4 && jets[i].bDiscriminator("combinedSecondaryVertexBJetTags") > 0.679) nbjetsnotfat++;
        }
    }

    // QCD suppression handles
    ht     = 0.;
    dht    = -1.;
    mht    = 0.;
    alphat = -1.;

    double mhtx = 0.;
    double mhty = 0.;
    std::vector<double> jetEts;
    for (size_t i = 0; i < jets.size(); i++) {
        if (jets[i].pt() > 30) {
            ht += jets[i].pt();
            mhtx -= jets[i].pt() * cos(jets[i].phi());
            mhty -= jets[i].pt() * sin(jets[i].phi());
            jetEts.push_back(jets[i].pt());
        }
    }

    mht = sqrt(mhtx*mhtx + mhty*mhty);

    if (jetEts.size() > 1 && jetEts.size() < 15) { // Memory consumption explodes with large number of jets -- this should be addressed
        // This code is ripped off from UserCode/SusyAnalysis/HadronicSUSYOverlapExercise/ANALYSIS/src 
        std::vector<double> diff( 1<<(jetEts.size()-1) , 0. );
        for(size_t i = 0; i < diff.size(); i++) {
            for(size_t j = 0; j < jetEts.size(); j++) diff[i] += jetEts[j] * ( 1 - 2 * (int(i>>j)&1) );
        }        
        for(size_t i = 0; i < diff.size(); i++) {
            diff[i] = fabs(diff[i]);
        }        
        dht = *min_element(diff.begin(), diff.end());
        alphat = 0.5 * (ht - dht) / sqrt(ht*ht - mht*mht);
    }
    else alphat = 0.0;

    apcjet       = 0.0;
    apcmet       = 0.0;
    apcjetmet    = 0.0;
    apcjetmax    = 0.0;
    apcjetmetmax = 0.0;
    apcjetmin    = 0.0;
    apcjetmetmin = 0.0;

    for (size_t i = 0; i < jets.size(); i++) {
        if (jets[i].pt() > 30 && hardestJetIndex >= 0) {
            double dphisignaljet = fabs(deltaPhi(jets[i].phi(), jets[hardestJetIndex].phi()));
            double jetphi        = atan2(jets[i].pt()*sin(jets[i].phi()), jets[i].pt()*cos(jets[i].phi()));
            double dphimet       = fabs(deltaPhi(jetphi, mumetphi));

            apcjet    += jets[i].pt() * cos(dphisignaljet/2.0);
            apcmet    += jets[i].pt() * sin(dphimet/2.0);
            apcjetmet += jets[i].pt() * cos(dphisignaljet/2.0) * sin(dphimet/2.0);
        }
    }
    
    std::vector<double> apcjetvector;
    std::vector<double> apcjetmetvector;
    for (size_t j = 0; j < jets.size(); j++) {
        if (jets[j].pt() > 30) {
            apcjetvector.push_back(0.);
            apcjetmetvector.push_back(0.);
            for (size_t i = 0; i < jets.size(); i++) {
                if (jets[i].pt() > 30) {
                    double dphijet = fabs(deltaPhi(jets[i].phi(), jets[j].phi()));
                    double jetphi  = atan2(jets[i].pt()*sin(jets[i].phi()), jets[i].pt()*cos(jets[i].phi()));
                    double dphimet = fabs(deltaPhi(jetphi, mumetphi));

                    apcjetvector.back()    += jets[i].pt() * cos(dphijet/2.0);
                    apcjetmetvector.back() += jets[i].pt() * cos(dphijet/2.0) * sin(dphimet/2.0);
                }
            }
        }
    }
    if (apcjetvector.size() > 0 && apcjetmetvector.size() > 0) {
        apcjetmax    = *max_element(apcjetvector.begin()   , apcjetvector.end());
        apcjetmetmax = *max_element(apcjetmetvector.begin(), apcjetmetvector.end());
        apcjetmin    = *min_element(apcjetvector.begin()   , apcjetvector.end());
        apcjetmetmin = *min_element(apcjetmetvector.begin(), apcjetmetvector.end());
    }    

    if (ht != 0) {
        apcjet       /= ht;
        apcmet       /= ht;
        apcjetmet    /= ht;
        apcjetmax    /= ht;
        apcjetmetmax /= ht;
        apcjetmin    /= ht;
        apcjetmetmin /= ht;
    }

    // Lepton counts
    nmuons          = muonsH->size();
    nelectrons      = electronsH->size();
    ntightmuons     = tightmuonsH->size();
    ntightelectrons = tightelectronsH->size();
    ntaus           = tausH->size();

    // Generator-level information
    wzid   = 0;
    wzmass = 0.0;
    wzpt   = 0.0;
    wzeta  = 0.0;
    wzphi  = 0.0;
    l1id   = 0;
    l1pt   = 0.0;
    l1eta  = 0.0;
    l1phi  = 0.0;
    l2id   = 0;
    l2pt   = 0.0;
    l2eta  = 0.0;
    l2phi  = 0.0;

    if (isWorZMCSample && gensH.isValid()) {
        for (View<GenParticle>::const_iterator gens_iter = gensH->begin(); gens_iter != gensH->end(); ++gens_iter) {
            if ((gens_iter->pdgId() == 23 || abs(gens_iter->pdgId()) == 24) && gens_iter->numberOfDaughters() == 3 && abs(gens_iter->daughter(0)->pdgId()) > 10 && abs(gens_iter->daughter(0)->pdgId()) < 17) {
                wzid   = gens_iter->pdgId();
                wzmass = gens_iter->mass();
                wzpt   = gens_iter->pt();
                wzeta  = gens_iter->eta();
                wzphi  = gens_iter->phi();
                l1id   = gens_iter->daughter(0)->pdgId();
                l1pt   = gens_iter->daughter(0)->pt();
                l1eta  = gens_iter->daughter(0)->eta();
                l1phi  = gens_iter->daughter(0)->phi();
                l2id   = gens_iter->daughter(1)->pdgId();
                l2pt   = gens_iter->daughter(1)->pt();
                l2eta  = gens_iter->daughter(1)->eta();
                l2phi  = gens_iter->daughter(1)->phi();
                wzmt   = sqrt(2.0 * l1pt * l2pt * (1.0 - cos(deltaPhi(l1phi, l2phi)))); 
                break;
            }
            if (gens_iter->pdgId() == 22 && gens_iter->status() == 1 && gens_iter->pt() > 100.) {
                wzid   = gens_iter->pdgId();
                wzpt   = gens_iter->pt();
                wzeta  = gens_iter->eta();
                wzphi  = gens_iter->phi();
            }
            if (gens_iter->pdgId() == 18) {
                l1id   = gens_iter->pdgId();
                l1pt   = gens_iter->pt();
                l1eta  = gens_iter->eta();
                l1phi  = gens_iter->phi();
            }
            if (gens_iter->pdgId() == -18) {
                l2id   = gens_iter->pdgId();
                l2pt   = gens_iter->pt();
                l2eta  = gens_iter->eta();
                l2phi  = gens_iter->phi();
            }
        }
        if (l1id == 18 && l2id == -18) {
            double wzpx = l1pt*cos(l1phi) + l2pt*cos(l2phi);
            double wzpy = l1pt*sin(l1phi) + l2pt*sin(l2phi);
            wzpt = sqrt(wzpx*wzpx + wzpy*wzpy);
            wzphi = atan2(wzpy, wzpx);
        }            
    }

    // Photon, W, Z control sample information
    nphotons      = photonsH->size();
    ntightphotons = tightphotonsH->size();
    phpt          = 0.0;
    pheta         = 0.0;
    phphi         = 0.0;
    preselphpt    = 0.0;
    preselpheta   = 0.0;
    preselphphi   = 0.0;
    preselphsieie = 0.0;
    preselphr9    = 0.0;
    preselphcorrCHIso=0.0;
    preselphcorrNHIso=0.0;
    preselphcorrPHIso=0.0;
    preselphhoe   = 0.0;
    zmass         = 0.0; 
    zpt           = 0.0;
    zeta          = 0.0; 
    zphi          = 0.0;
    zeemass       = 0.0; 
    zeept         = 0.0;
    zeeeta        = 0.0; 
    zeephi        = 0.0;
    wmt           = 0.0;
    wemt          = 0.0;
    emumass       = 0.0;
    emupt         = 0.0;
    emueta        = 0.0;
    emuphi        = 0.0;
    mu1pid        = 0;
    mu1pt         = 0.0;
    mu1eta        = 0.0;
    mu1phi        = 0.0;
    mu1id         = 0;
    mu2pid        = 0;
    mu2pt         = 0.0;
    mu2eta        = 0.0; 
    mu2phi        = 0.0;
    mu2id         = 0;
    el1pid        = 0;
    el1pt         = 0.0;
    el1eta        = 0.0;
    el1phi        = 0.0;
    el1id         = 0;
    el2pid        = 0;
    el2pt         = 0.0;
    el2eta        = 0.0;
    el2phi        = 0.0;
    el2id         = 0;

    if (hardestPhotonIndex >= 0) {
        PhotonRef tightphoton = tightphotons[hardestPhotonIndex];
        phpt    = tightphoton->pt();
        pheta   = tightphoton->eta();
        phphi   = tightphoton->phi();
    }


    if (hardestPreselPhotonIndex >= 0) {
        PhotonRef photon = photons[hardestPreselPhotonIndex];
        preselphpt    = photon->pt();
        preselpheta   = photon->eta();
        preselphphi   = photon->phi();
	preselphsieie = photon->sigmaIetaIeta() ;
	preselphr9 = photon->r9();
	preselphhoe = photon->hadTowOverEm();
	double chiso = photon->chargedHadronIso();
	double nhiso = photon->neutralHadronIso();
	double phiso = photon->photonIso();
	preselphcorrCHIso = chiso - rho * getChargedHadronEAForPhotonIso(photon->eta());
	preselphcorrNHIso = nhiso - rho * getNeutralHadronEAForPhotonIso(photon->eta());
	preselphcorrPHIso = phiso - rho * getGammaEAForPhotonIso(photon->eta());	
	if (preselphcorrCHIso < 0.) preselphcorrCHIso = 0.;
	if (preselphcorrNHIso < 0.) preselphcorrNHIso = 0.;
	if (preselphcorrPHIso < 0.) preselphcorrPHIso = 0.;
  
}

    if (nmuons == 1 || nmuons == 2) {
        MuonRef muon = muons[0];
        mu1pid = muon->pdgId(); 
        mu1pt  = muon->pt(); 
        mu1eta = muon->eta(); 
        mu1phi = muon->phi();

        for (std::size_t i = 0; i < tightmuons.size(); i++) {
            if (muon == tightmuons[i]) mu1id = 1;
        }

        if (nmuons == 1) wmt = sqrt(2.0 * mu1pt * t1pfmet * (1.0 - cos(deltaPhi(mu1phi, t1pfmetphi))));
    }
   

 
    if (nmuons == 2) {        
        MuonRef muon = muons[1];
        mu2pid = muon->pdgId(); 
        mu2pt  = muon->pt(); 
        mu2eta = muon->eta(); 
        mu2phi = muon->phi();
    
        for (std::size_t i = 0; i < tightmuons.size(); i++) {
            if (muon == tightmuons[i]) mu2id = 1;
        }
    
        TLorentzVector mu1vec; mu1vec.SetPtEtaPhiE(mu1pt, mu1eta, mu1phi, muons[0]->p());
        TLorentzVector mu2vec; mu2vec.SetPtEtaPhiE(mu2pt, mu2eta, mu2phi, muon->p());
    
        TLorentzVector zvec(mu1vec);
        zvec += mu2vec;
    
        zmass = zvec.M();
        zpt   = zvec.Pt();
        zeta  = zvec.Eta();            
        zphi  = zvec.Phi();
    }

    if (nelectrons == 1 || nelectrons == 2) {
        GsfElectronRef electron = electrons[0];
        el1pid = electron->pdgId();
        el1pt  = electron->pt();
        el1eta = electron->eta();
        el1phi = electron->phi();
        
        for (std::size_t i = 0; i < tightelectrons.size(); i++) {
            if (electron == tightelectrons[i]) el1id = 1;
        }
        
        if (electrons.size() == 1) wemt = sqrt(2.0 * el1pt * t1pfmet * (1.0 - cos(deltaPhi(el1phi, t1pfmetphi))));
    }

    if (nelectrons == 2) {
        GsfElectronRef electron = electrons[1];
        el2pid = electron->pdgId();
        el2pt  = electron->pt();
        el2eta = electron->eta();
        el2phi = electron->phi();

        for (std::size_t i = 0; i < tightelectrons.size(); i++) {
            if (electron == tightelectrons[i]) el2id = 1;
        }

        TLorentzVector el1vec; el1vec.SetPtEtaPhiE(el1pt, el1eta, el1phi, electrons[0]->p());
        TLorentzVector el2vec; el2vec.SetPtEtaPhiE(el2pt, el2eta, el2phi, electron->p());

        TLorentzVector zvec(el1vec);
        zvec += el2vec;

        zeemass = zvec.M();
        zeept   = zvec.Pt();
        zeeeta  = zvec.Eta();
        zeephi  = zvec.Phi();
    }

    if (nmuons == 1 && nelectrons == 1) {
        TLorentzVector mu1vec; mu1vec.SetPtEtaPhiE(mu1pt, mu1eta, mu1phi, muons[0]->p());
        TLorentzVector el1vec; el1vec.SetPtEtaPhiE(el1pt, el1eta, el1phi, electrons[0]->p());
        
        TLorentzVector emuvec(mu1vec);
        emuvec += el1vec;
        
        emumass = emuvec.M();
        emupt   = emuvec.Pt();
        emueta  = emuvec.Eta();
        emuphi  = emuvec.Phi();
    } 

    tree->Fill();
}


void MonoJetTreeMaker::beginJob() {
    edm::Service<TFileService> fs;
    tree = fs->make<TTree>("tree"      , "tree");
    // Run, Lumi, Event info
    tree->Branch("event"               , &event               , "event/i");
    tree->Branch("run"                 , &run                 , "run/i");
    tree->Branch("lumi"                , &lumi                , "lumi/i");
    // Event weights
    tree->Branch("wgt"                 , &wgt                 , "wgt/D");
    tree->Branch("puwgt"               , &puwgt               , "puwgt/D");
    tree->Branch("weight"              , &weight              , "weight/D");
    // Pileup info
    tree->Branch("puobs"               , &puobs               , "puobs/I");
    tree->Branch("putrue"              , &putrue              , "putrue/I");
    tree->Branch("nvtx"                , &nvtx                , "nvtx/i");
    // Triggers and event filters
    tree->Branch("hltmet120"           , &hltmet120           , "hltmet120/i");
    tree->Branch("hltmet95jet80"       , &hltmet95jet80       , "hltmet95jet80/i");
    tree->Branch("hltmet105jet80"      , &hltmet105jet80      , "hltmet105jet80/i");
    tree->Branch("hltdoublemu"         , &hltdoublemu         , "hltdoublemu/i");
    tree->Branch("hltsinglemu"         , &hltsinglemu         , "hltsinglemu/i");
    tree->Branch("hltdoubleel"         , &hltdoubleel         , "hltdoubleel/i");
    tree->Branch("hltphoton135"        , &hltphoton135        , "hltphoton135/i");
    tree->Branch("hltphoton150"        , &hltphoton150        , "hltphoton150/i");
    // Object counts
    tree->Branch("nmuons"              , &nmuons              , "nmuons/i");
    tree->Branch("nelectrons"          , &nelectrons          , "nelectrons/i");
    tree->Branch("nphotons"            , &nphotons            , "nphotons/i");
    tree->Branch("ntightmuons"         , &ntightmuons         , "ntightmuons/i");
    tree->Branch("ntightelectrons"     , &ntightelectrons     , "ntightelectrons/i");
    tree->Branch("ntightphotons"       , &ntightphotons       , "ntightphotons/i");
    tree->Branch("ntaus"               , &ntaus               , "ntaus/i");
    tree->Branch("njets"               , &njets               , "njets/i");
    tree->Branch("ncentjets"           , &ncentjets           , "ncentjets/i");
    tree->Branch("nbjets"              , &nbjets              , "nbjets/i");
    tree->Branch("nfatjets"            , &nfatjets            , "nfatjets/i");
    tree->Branch("ncentfatjets"        , &ncentfatjets        , "ncentfatjets/i");
    tree->Branch("njetsnotfat"         , &njetsnotfat         , "njetsnotfat/i");
    tree->Branch("ncentjetsnotfat"     , &ncentjetsnotfat     , "ncentjetsnotfat/i");
    tree->Branch("nbjetsnotfat"        , &nbjetsnotfat        , "nbjetsnotfat/i");
    // MET info
    tree->Branch("pfmet"               , &pfmet               , "pfmet/D");
    tree->Branch("pfmetphi"            , &pfmetphi            , "pfmetphi/D");
    tree->Branch("t1pfmet"             , &t1pfmet             , "t1pfmet/D");
    tree->Branch("t1pfmetphi"          , &t1pfmetphi          , "t1pfmetphi/D");
    tree->Branch("calomet"             , &calomet             , "calomet/D");
    tree->Branch("calometphi"          , &calometphi          , "calometphi/D");
    tree->Branch("pfmupt"              , &pfmupt              , "pfmupt/D");
    tree->Branch("pfmuphi"             , &pfmuphi             , "pfmuphi/D");
    tree->Branch("mumet"               , &mumet               , "mumet/D");
    tree->Branch("mumetphi"            , &mumetphi            , "mumetphi/D");
    tree->Branch("phmet"               , &phmet               , "phmet/D");
    tree->Branch("phmetphi"            , &phmetphi            , "phmetphi/D");
    tree->Branch("t1mumet"             , &t1mumet             , "t1mumet/D");
    tree->Branch("t1mumetphi"          , &t1mumetphi          , "t1mumetphi/D");
    tree->Branch("t1phmet"             , &t1phmet             , "t1phmet/D");
    tree->Branch("t1phmetphi"          , &t1phmetphi          , "t1phmetphi/D");
    // Jet info
    tree->Branch("fatjetpt"            , &fatjetpt            , "fatjetpt/D");
    tree->Branch("fatjeteta"           , &fatjeteta           , "fatjeteta/D");
    tree->Branch("fatjetphi"           , &fatjetphi           , "fatjetphi/D");
    tree->Branch("fatjetmass"          , &fatjetmass          , "fatjetmass/D");
    tree->Branch("fatjetprunedmass"    , &fatjetprunedmass    , "fatjetprunedmass/D");
    tree->Branch("fatjetmassdrop"      , &fatjetmassdrop      , "fatjetmassdrop/D");
    tree->Branch("fatjettau2"          , &fatjettau2          , "fatjettau2/D");
    tree->Branch("fatjettau1"          , &fatjettau1          , "fatjettau1/D");
    tree->Branch("fatjetCHfrac"        , &fatjetCHfrac        , "fatjetCHfrac/D");
    tree->Branch("fatjetNHfrac"        , &fatjetNHfrac        , "fatjetNHfrac/D");
    tree->Branch("fatjetEMfrac"        , &fatjetEMfrac        , "fatjetEMfrac/D");
    tree->Branch("fatjetCEMfrac"       , &fatjetCEMfrac       , "fatjetCEMfrac/D");
    tree->Branch("fatjetmetdphi"       , &fatjetmetdphi       , "fatjetmetdphi/D");
    tree->Branch("signaljetpt"         , &signaljetpt         , "signaljetpt/D");
    tree->Branch("signaljeteta"        , &signaljeteta        , "signaljeteta/D");
    tree->Branch("signaljetphi"        , &signaljetphi        , "signaljetphi/D");
    tree->Branch("signaljetCHfrac"     , &signaljetCHfrac     , "signaljetCHfrac/D");
    tree->Branch("signaljetNHfrac"     , &signaljetNHfrac     , "signaljetNHfrac/D");
    tree->Branch("signaljetEMfrac"     , &signaljetEMfrac     , "signaljetEMfrac/D");
    tree->Branch("signaljetCEMfrac"    , &signaljetCEMfrac    , "signaljetCEMfrac/D");
    tree->Branch("signaljetmetdphi"    , &signaljetmetdphi    , "signaljetmetdphi/D");
    tree->Branch("secondjetpt"         , &secondjetpt         , "secondjetpt/D");
    tree->Branch("secondjeteta"        , &secondjeteta        , "secondjeteta/D");
    tree->Branch("secondjetphi"        , &secondjetphi        , "secondjetphi/D");
    tree->Branch("secondjetCHfrac"     , &secondjetCHfrac     , "secondjetCHfrac/D");
    tree->Branch("secondjetNHfrac"     , &secondjetNHfrac     , "secondjetNHfrac/D");
    tree->Branch("secondjetEMfrac"     , &secondjetEMfrac     , "secondjetEMfrac/D");
    tree->Branch("secondjetCEMfrac"    , &secondjetCEMfrac    , "secondjetCEMfrac/D");
    tree->Branch("secondjetmetdphi"    , &secondjetmetdphi    , "secondjetmetdphi/D");
    tree->Branch("jetjetdphi"          , &jetjetdphi          , "jetjetdphi/D");
    tree->Branch("jetmetdphimin"       , &jetmetdphimin       , "jetmetdphimin/D");
    tree->Branch("thirdjetpt"          , &thirdjetpt          , "thirdjetpt/D");
    tree->Branch("thirdjeteta"         , &thirdjeteta         , "thirdjeteta/D");
    tree->Branch("thirdjetphi"         , &thirdjetphi         , "thirdjetphi/D");
    tree->Branch("thirdjetCHfrac"      , &thirdjetCHfrac      , "thirdjetCHfrac/D");
    tree->Branch("thirdjetNHfrac"      , &thirdjetNHfrac      , "thirdjetNHfrac/D");
    tree->Branch("thirdjetEMfrac"      , &thirdjetEMfrac      , "thirdjetEMfrac/D");
    tree->Branch("thirdjetCEMfrac"     , &thirdjetCEMfrac     , "thirdjetCEMfrac/D");
    tree->Branch("thirdjetmetdphi"     , &thirdjetmetdphi     , "thirdjetmetdphi/D");
    // QCD suppression
    tree->Branch("ht"                  , &ht                  , "ht/D");
    tree->Branch("dht"                 , &dht                 , "dht/D");
    tree->Branch("mht"                 , &mht                 , "mht/D");
    tree->Branch("alphat"              , &alphat              , "alphat/D");
    tree->Branch("apcjet"              , &apcjet              , "apcjet/D");
    tree->Branch("apcmet"              , &apcmet              , "apcmet/D");
    tree->Branch("apcjetmet"           , &apcjetmet           , "apcjetmet/D");
    tree->Branch("apcjetmax"           , &apcjetmax           , "apcjetmax/D");
    tree->Branch("apcjetmetmax"        , &apcjetmetmax        , "apcjetmetmax/D");
    tree->Branch("apcjetmin"           , &apcjetmin           , "apcjetmin/D");
    tree->Branch("apcjetmetmin"        , &apcjetmetmin        , "apcjetmetmin/D");
    // Lepton info
    tree->Branch("mu1pid"              , &mu1pid              , "mu1pid/I");
    tree->Branch("mu1pt"               , &mu1pt               , "mu1pt/D");
    tree->Branch("mu1eta"              , &mu1eta              , "mu1eta/D");
    tree->Branch("mu1phi"              , &mu1phi              , "mu1phi/D");
    tree->Branch("mu1id"               , &mu1id               , "mu1id/I");
    tree->Branch("mu2pid"              , &mu2pid              , "mu2pid/I");
    tree->Branch("mu2pt"               , &mu2pt               , "mu2pt/D");
    tree->Branch("mu2eta"              , &mu2eta              , "mu2eta/D");
    tree->Branch("mu2phi"              , &mu2phi              , "mu2phi/D");
    tree->Branch("mu2id"               , &mu2id               , "mu2id/I");
    tree->Branch("el1pid"              , &el1pid              , "el1pid/I");
    tree->Branch("el1pt"               , &el1pt               , "el1pt/D");
    tree->Branch("el1eta"              , &el1eta              , "el1eta/D");
    tree->Branch("el1phi"              , &el1phi              , "el1phi/D");
    tree->Branch("el1id"               , &el1id               , "el1id/I");
    tree->Branch("el2pid"              , &el2pid              , "el2pid/I");
    tree->Branch("el2pt"               , &el2pt               , "el2pt/D");
    tree->Branch("el2eta"              , &el2eta              , "el2eta/D");
    tree->Branch("el2phi"              , &el2phi              , "el2phi/D");
    tree->Branch("el2id"               , &el2id               , "el2id/I");
    // Dilepton info
    tree->Branch("zmass"               , &zmass               , "zmass/D");
    tree->Branch("zpt"                 , &zpt                 , "zpt/D");
    tree->Branch("zeta"                , &zeta                , "zeta/D");
    tree->Branch("zphi"                , &zphi                , "zphi/D");
    tree->Branch("wmt"                 , &wmt                 , "wmt/D");
    tree->Branch("emumass"             , &emumass             , "emumass/D");
    tree->Branch("emupt"               , &emupt               , "emupt/D");
    tree->Branch("emueta"              , &emueta              , "emueta/D");
    tree->Branch("emuphi"              , &emuphi              , "emuphi/D");
    tree->Branch("zeemass"             , &zeemass             , "zeemass/D");
    tree->Branch("zeept"               , &zeept               , "zeeept/D");
    tree->Branch("zeeeta"              , &zeeeta              , "zeeeta/D");
    tree->Branch("zeephi"              , &zeephi              , "zeephi/D");
    tree->Branch("wemt"                , &wemt                , "wemt/D");
    // Photon info
    tree->Branch("phpt"                , &phpt                , "phpt/D");
    tree->Branch("pheta"               , &pheta               , "pheta/D");
    tree->Branch("phphi"               , &phphi               , "phphi/D");

    tree->Branch("preselphpt"      , &preselphpt   , "preselphpt/D");    
    tree->Branch("preselpheta"     , &preselpheta   , "preselpheta/D");    
    tree->Branch("preselphphi"     , &preselphphi    , "preselphphi/D");    
    tree->Branch("preselphsieie"   , &preselphsieie  , "preselphsieie/D");  
    tree->Branch("preselphr9"      , &preselphr9     , "preselphr9/D");     
    tree->Branch("preselphhoe"     , &preselphhoe    , "preselphhoe/D");    
   
    tree->Branch("preselphcorrCHIso",&preselphcorrCHIso,"preselphcorrCHIso/D");
    tree->Branch("preselphcorrNHIso",&preselphcorrNHIso,"preselphcorrNHIso/D");
    tree->Branch("preselphcorrPHIso",&preselphcorrPHIso,"preselphcorrPHIso/D");
    
 
    
    // W/Z gen-level info
    tree->Branch("wzid"                , &wzid                , "wzid/I");
    tree->Branch("wzmass"              , &wzmass              , "wzmass/D");
    tree->Branch("wzmt"                , &wzmt                , "wzmt/D");
    tree->Branch("wzpt"                , &wzpt                , "wzpt/D");
    tree->Branch("wzeta"               , &wzeta               , "wzeta/D");
    tree->Branch("wzphi"               , &wzphi               , "wzphi/D");
    tree->Branch("l1id"                , &l1id                , "l1id/I");
    tree->Branch("l1pt"                , &l1pt                , "l1pt/D");
    tree->Branch("l1eta"               , &l1eta               , "l1eta/D");
    tree->Branch("l1phi"               , &l1phi               , "l1phi/D");
    tree->Branch("l2id"                , &l2id                , "l2id/I");
    tree->Branch("l2pt"                , &l2pt                , "l2pt/D");
    tree->Branch("l2eta"               , &l2eta               , "l2eta/D");
    tree->Branch("l2phi"               , &l2phi               , "l2phi/D");
}

void MonoJetTreeMaker::endJob() {
}

void MonoJetTreeMaker::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup) {
    triggerPathsVector.push_back("HLT_Mu17_Mu8");
    triggerPathsVector.push_back("HLT_Mu17_TkMu8");
    triggerPathsVector.push_back("HLT_IsoMu24_eta2p1");
    triggerPathsVector.push_back("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL"),
    triggerPathsVector.push_back("HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL"),
    triggerPathsVector.push_back("HLT_MET120_HBHENoiseCleaned");
    triggerPathsVector.push_back("HLT_MonoCentralPFJet80_PFMETnoMu95_NHEF0p95");
    triggerPathsVector.push_back("HLT_MonoCentralPFJet80_PFMETnoMu105_NHEF0p95");
    triggerPathsVector.push_back("HLT_Photon135");
    triggerPathsVector.push_back("HLT_Photon150");

    HLTConfigProvider hltConfig;
    bool changedConfig = false;
    hltConfig.init(iRun, iSetup, triggerResultsTag.process(), changedConfig);

    for (size_t i = 0; i < triggerPathsVector.size(); i++) {
        triggerPathsMap[triggerPathsVector[i]] = -1;
    }

    for(size_t i = 0; i < triggerPathsVector.size(); i++){
        TPRegexp pattern(triggerPathsVector[i]);
        for(size_t j = 0; j < hltConfig.triggerNames().size(); j++){
            std::string pathName = hltConfig.triggerNames()[j];
            if(TString(pathName).Contains(pattern)){
                triggerPathsMap[triggerPathsVector[i]] = j;
            }
        }
    }
}

void MonoJetTreeMaker::endRun(edm::Run const&, edm::EventSetup const&) {
}

void MonoJetTreeMaker::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {
}

void MonoJetTreeMaker::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {
}

void MonoJetTreeMaker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(MonoJetTreeMaker);

void MonoJetTreeMaker::initPileupWeights() {
    float puweights[60];
    puweights[0]  = 0.242421;
    puweights[1]  = 0.314567;
    puweights[2]  = 0.328551;
    puweights[3]  = 0.341325;
    puweights[4]  = 0.311977;
    puweights[5]  = 0.560934;
    puweights[6]  = 0.443155;
    puweights[7]  = 0.444942;
    puweights[8]  = 0.625725;
    puweights[9]  = 0.940482;
    puweights[10] = 1.33114;
    puweights[11] = 1.67986;
    puweights[12] = 1.7303;
    puweights[13] = 1.54809;
    puweights[14] = 1.32353;
    puweights[15] = 1.15668;
    puweights[16] = 1.07105;
    puweights[17] = 1.04548;
    puweights[18] = 1.06319;
    puweights[19] = 1.10733;
    puweights[20] = 1.14954;
    puweights[21] = 1.17563;
    puweights[22] = 1.188;
    puweights[23] = 1.18718;
    puweights[24] = 1.16671;
    puweights[25] = 1.121;
    puweights[26] = 1.04977;
    puweights[27] = 0.956974;
    puweights[28] = 0.84729;
    puweights[29] = 0.727003;
    puweights[30] = 0.603974;
    puweights[31] = 0.485796;
    puweights[32] = 0.377733;
    puweights[33] = 0.283343;
    puweights[34] = 0.204364;
    puweights[35] = 0.14118;
    puweights[36] = 0.0934506;
    puweights[37] = 0.059445;
    puweights[38] = 0.0365081;
    puweights[39] = 0.0218306;
    puweights[40] = 0.012844;
    puweights[41] = 0.00753269;
    puweights[42] = 0.00447223;
    puweights[43] = 0.00273386;
    puweights[44] = 0.00175157;
    puweights[45] = 0.00118879;
    puweights[46] = 0.000857334;
    puweights[47] = 0.000653996;
    puweights[48] = 0.000522478;
    puweights[49] = 0.000432433;
    puweights[50] = 0.000367567;
    puweights[51] = 0.000318451;
    puweights[52] = 0.000279865;
    puweights[53] = 0.000248423;
    puweights[54] = 0.000221711;
    puweights[55] = 0.000198398;
    puweights[56] = 0.000177509;
    puweights[57] = 0.000158456;
    puweights[58] = 0.000140801;
    puweights[59] = 0.000261544;

    puhist = new TH1F("puhist", "", 60, 0., 60.);

    for(int k = 0; k < 60; k++) puhist->SetBinContent(k+1, puweights[k]);
}



double MonoJetTreeMaker::getChargedHadronEAForPhotonIso(double eta) {
    if (fabs(eta) < 1.0) return 0.012;
    else if (fabs(eta) >= 1.0   && fabs(eta) < 1.479) return 0.010;
    else if (fabs(eta) >= 1.479 && fabs(eta) < 2.0  ) return 0.014;
    else if (fabs(eta) >= 2.0   && fabs(eta) < 2.2  ) return 0.012;
    else if (fabs(eta) >= 2.2   && fabs(eta) < 2.3  ) return 0.016;
    else if (fabs(eta) >= 2.3   && fabs(eta) < 2.4  ) return 0.020;
    else if (fabs(eta) >= 2.4) return 0.012;
    else return 0.;
}

double MonoJetTreeMaker::getNeutralHadronEAForPhotonIso(double eta) {
    if (fabs(eta) < 1.0) return 0.030;
    else if (fabs(eta) >= 1.0   && fabs(eta) < 1.479) return 0.057;
    else if (fabs(eta) >= 1.479 && fabs(eta) < 2.0  ) return 0.039;
    else if (fabs(eta) >= 2.0   && fabs(eta) < 2.2  ) return 0.015;
    else if (fabs(eta) >= 2.2   && fabs(eta) < 2.3  ) return 0.024;
    else if (fabs(eta) >= 2.3   && fabs(eta) < 2.4  ) return 0.039;
    else if (fabs(eta) >= 2.4) return 0.072;
    else return 0.;
}

double MonoJetTreeMaker::getGammaEAForPhotonIso(double eta) {
    if (fabs(eta) < 1.0) return 0.148;
    else if (fabs(eta) >= 1.0   && fabs(eta) < 1.479) return 0.130;
    else if (fabs(eta) >= 1.479 && fabs(eta) < 2.0  ) return 0.112;
    else if (fabs(eta) >= 2.0   && fabs(eta) < 2.2  ) return 0.216;
    else if (fabs(eta) >= 2.2   && fabs(eta) < 2.3  ) return 0.262;
    else if (fabs(eta) >= 2.3   && fabs(eta) < 2.4  ) return 0.260;
    else if (fabs(eta) >= 2.4) return 0.266;
    else return 0.;
}
