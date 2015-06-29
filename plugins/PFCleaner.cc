/*

Notes:

Muon ID and isolation : https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId
Photon ID and isolation : https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonID2012
Electron ID and isolation : https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaCutBasedIdentification

*/


#include <memory>
#include <vector>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "EGamma/EGammaAnalysisTools/interface/EGammaCutBasedEleId.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

class PFCleaner : public edm::EDProducer {
    public:
        explicit PFCleaner(const edm::ParameterSet&);
        ~PFCleaner();
        
        static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    
    private:
        virtual void beginJob() ;
        virtual void produce(edm::Event&, const edm::EventSetup&);
        virtual void endJob() ;
        
        virtual void beginRun(edm::Run&, edm::EventSetup const&);
        virtual void endRun(edm::Run&, edm::EventSetup const&);
        virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
        virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

  double getChargedHadronEAForPhotonIso(double);
  double getNeutralHadronEAForPhotonIso(double);
  double getGammaEAForPhotonIso(double);
  bool testPhotonIsolation(reco::PhotonRef, double, double, double, double);
  bool testPhotonPreselection(reco::PhotonRef, double, double, double);

        edm::InputTag src;
        edm::InputTag beamspot;
        edm::InputTag vertices;
        edm::InputTag pfpu;
        edm::InputTag rhoTag;
        edm::InputTag conversions;
        edm::InputTag electrons;
        edm::InputTag photonsTag;
        edm::InputTag elCHPFIso;
        edm::InputTag elNHPFIso;
        edm::InputTag elPHPFIso;
        edm::InputTag elPUPFIso;
        edm::InputTag phCHPFIso;
        edm::InputTag phNHPFIso;
        edm::InputTag phPHPFIso;

        double d0cut, dzcut;

        bool vetophotons;
};

PFCleaner::PFCleaner(const edm::ParameterSet& iConfig): 
    src(iConfig.getParameter<edm::InputTag>("src")),
    beamspot(iConfig.getParameter<edm::InputTag>("beamspot")),
    vertices(iConfig.getParameter<edm::InputTag>("vertices")),
    pfpu(iConfig.getParameter<edm::InputTag>("pfpileup")),
    rhoTag(iConfig.getParameter<edm::InputTag>("rho")),
    conversions(iConfig.getParameter<edm::InputTag>("conversions")),
    electrons(iConfig.getParameter<edm::InputTag>("electrons")),
    photonsTag(iConfig.getParameter<edm::InputTag>("photons")),
    elCHPFIso(iConfig.getParameter<edm::InputTag>("electronPFIsoCH")),
    elNHPFIso(iConfig.getParameter<edm::InputTag>("electronPFIsoNH")),
    elPHPFIso(iConfig.getParameter<edm::InputTag>("electronPFIsoPH")),
    elPUPFIso(iConfig.getParameter<edm::InputTag>("electronPFIsoPU")),
    phCHPFIso(iConfig.getParameter<edm::InputTag>("photonPFIsoCH")),
    phNHPFIso(iConfig.getParameter<edm::InputTag>("photonPFIsoNH")),
    phPHPFIso(iConfig.getParameter<edm::InputTag>("photonPFIsoPH")),
    d0cut(iConfig.getParameter<double>("d0cut")),
    dzcut(iConfig.getParameter<double>("dzcut")),
    vetophotons(iConfig.getParameter<bool>("vetophotons"))
{
    produces<reco::PFCandidateCollection>("pfcands");
    produces<reco::MuonRefVector>("muons");
    produces<reco::GsfElectronRefVector>("electrons");
    produces<reco::PhotonRefVector>("photons");
    produces<reco::MuonRefVector>("tightmuons");
    produces<reco::GsfElectronRefVector>("tightelectrons");
    produces<reco::PhotonRefVector>("tightphotons");
    produces<reco::PhotonRefVector>("leadingphoton");
}


PFCleaner::~PFCleaner() {
}

void PFCleaner::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using namespace edm;
    using namespace reco;
    using namespace std;

    Handle<PFCandidateCollection> inputH;
    iEvent.getByLabel(src, inputH);
    PFCandidateCollection input = *inputH;    

    Handle<View<PFCandidate> > pfpileupH;
    iEvent.getByLabel(pfpu, pfpileupH);

    Handle<BeamSpot> beamspotH;
    iEvent.getByLabel(beamspot, beamspotH);

    Handle<vector<Vertex> > verticesH;
    iEvent.getByLabel(vertices, verticesH);

    Handle<vector<Conversion> > conversionsH;
    iEvent.getByLabel(conversions, conversionsH);

    Handle<vector<GsfElectron> > electronsH;
    iEvent.getByLabel(electrons, electronsH);

    Handle<PhotonCollection> photonsH;
    iEvent.getByLabel(photonsTag, photonsH);
    PhotonCollection photons = *photonsH;

    Handle<ValueMap<double> > elCHPFIsoH;
    iEvent.getByLabel(elCHPFIso, elCHPFIsoH);

    Handle<ValueMap<double> > elNHPFIsoH;
    iEvent.getByLabel(elNHPFIso, elNHPFIsoH);

    Handle<ValueMap<double> > elPHPFIsoH;
    iEvent.getByLabel(elPHPFIso, elPHPFIsoH);

    Handle<ValueMap<double> > elPUPFIsoH;
    iEvent.getByLabel(elPUPFIso, elPUPFIsoH);

    Handle<ValueMap<double> > phCHPFIsoH;
    iEvent.getByLabel(phCHPFIso, phCHPFIsoH);

    Handle<ValueMap<double> > phNHPFIsoH;
    iEvent.getByLabel(phNHPFIso, phNHPFIsoH);

    Handle<ValueMap<double> > phPHPFIsoH;
    iEvent.getByLabel(phPHPFIso, phPHPFIsoH);

    Handle<double> rhoH;
    iEvent.getByLabel(rhoTag, rhoH);
    double rho = *rhoH;

    std::auto_ptr<PFCandidateCollection> output(new PFCandidateCollection);
    std::auto_ptr<MuonRefVector> outputmuons(new MuonRefVector);
    std::auto_ptr<GsfElectronRefVector> outputelectrons(new GsfElectronRefVector);
    std::auto_ptr<PhotonRefVector> outputphotons(new PhotonRefVector);
    std::auto_ptr<MuonRefVector> outputtightmuons(new MuonRefVector);
    std::auto_ptr<GsfElectronRefVector> outputtightelectrons(new GsfElectronRefVector);
    std::auto_ptr<PhotonRefVector> outputtightphotons(new PhotonRefVector);
    std::auto_ptr<PhotonRefVector> outputleadingphoton(new PhotonRefVector);

    int leadingphotonindex = -1;
    double leadingphotonpt = 0.0;
    for (size_t i = 0; i  < input.size(); i++) {
        bool veto = false;

        for (View<PFCandidate>::const_iterator pfpileup_iter = pfpileupH->begin(); pfpileup_iter != pfpileupH->end(); ++pfpileup_iter) {
            if (input[i].pdgId() == pfpileup_iter->pdgId() && input[i].pt() == pfpileup_iter->pt() && input[i].eta() == pfpileup_iter->eta() && input[i].phi() == pfpileup_iter->phi()) veto = true;
        }

        bool isMu = (abs(input[i].pdgId()) == 13 && input[i].muonRef().isAvailable());
        if (isMu && verticesH->size() > 0) {
            bool passeskincuts = (input[i].muonRef()->pt() > 10 && fabs(input[i].muonRef()->eta()) < 2.4);
            bool passestipcut = false;
            bool passeslipcut = false;
            if (input[i].muonRef()->innerTrack().isAvailable() && fabs(input[i].muonRef()->innerTrack()->dxy(verticesH->begin()->position())) < d0cut) passestipcut = true;
            if (input[i].muonRef()->innerTrack().isAvailable() && fabs(input[i].muonRef()->innerTrack()->dz (verticesH->begin()->position())) < dzcut) passeslipcut = true;
            float isoval = input[i].muonRef()->pfIsolationR04().sumNeutralHadronEt;
            isoval += input[i].muonRef()->pfIsolationR04().sumPhotonEt;
            isoval -= 0.5*input[i].muonRef()->pfIsolationR04().sumPUPt;
            if (isoval < 0.) isoval = 0.;
            isoval += input[i].muonRef()->pfIsolationR04().sumChargedHadronPt;
            isoval /= input[i].muonRef()->pt();
            bool passesselection = (muon::isLooseMuon(*(input[i].muonRef())) && isoval < 0.2);
            if (passeskincuts && passestipcut && passeslipcut && passesselection) {
                veto = true;
                outputmuons->push_back(input[i].muonRef());

                if (muon::isTightMuon(*(input[i].muonRef()), *(verticesH->begin())) && isoval < 0.12) outputtightmuons->push_back(input[i].muonRef());
            }
        }

        bool isEl = (abs(input[i].pdgId()) == 11 && input[i].gsfElectronRef().isAvailable());
        if (isEl && verticesH->size() > 0) {
            bool passeskincuts = (input[i].gsfElectronRef()->pt() > 10 && fabs(input[i].gsfElectronRef()->superCluster()->eta()) < 2.5);
            bool passestipcut = false;
            bool passeslipcut = false;
            if (input[i].gsfElectronRef()->gsfTrack().isAvailable() && fabs(input[i].gsfElectronRef()->gsfTrack()->dxy(verticesH->begin()->position())) < d0cut) passestipcut = true;
            if (input[i].gsfElectronRef()->gsfTrack().isAvailable() && fabs(input[i].gsfElectronRef()->gsfTrack()->dz (verticesH->begin()->position())) < dzcut) passeslipcut = true;
            double chiso = (*elCHPFIsoH)[input[i].gsfElectronRef()];
            double nhiso = (*elNHPFIsoH)[input[i].gsfElectronRef()];
            double phiso = (*elPHPFIsoH)[input[i].gsfElectronRef()];
            bool passesselection = EgammaCutBasedEleId::PassWP(EgammaCutBasedEleId::VETO, input[i].gsfElectronRef(), conversionsH, *(beamspotH.product()), verticesH, chiso, phiso, nhiso, rho);

            if (passeskincuts && passestipcut && passeslipcut && passesselection) {
                veto = true;
                outputelectrons->push_back(input[i].gsfElectronRef());

                bool passestightid = EgammaCutBasedEleId::PassWP(EgammaCutBasedEleId::TIGHT, input[i].gsfElectronRef(), conversionsH, *(beamspotH.product()), verticesH, chiso, phiso, nhiso, rho);
                bool passestighttrig = EgammaCutBasedEleId::PassTriggerCuts(EgammaCutBasedEleId::TRIGGERTIGHT, input[i].gsfElectronRef());
                if (passestightid && passestighttrig) outputtightelectrons->push_back(input[i].gsfElectronRef());
            }
        }

        bool isPh = (input[i].pdgId() == 22 && input[i].photonRef().isAvailable());
        if (isPh) {
            bool passeskincuts = (input[i].photonRef()->pt() > 10 && fabs(input[i].photonRef()->eta()) < 3.0);
            bool isconversionssafe = !ConversionTools::hasMatchedPromptElectron(input[i].photonRef()->superCluster(), electronsH, conversionsH, beamspotH->position());
            double chiso = (*phCHPFIsoH)[input[i].photonRef()];
            double nhiso = (*phNHPFIsoH)[input[i].photonRef()];
            double phiso = (*phPHPFIsoH)[input[i].photonRef()];
            bool passesiso = testPhotonIsolation(input[i].photonRef(), chiso, nhiso, phiso, *rhoH);
	    bool passespreselection = testPhotonPreselection(input[i].photonRef(), chiso, phiso, *rhoH);
            bool passesselection = (passesiso && input[i].photonRef()->hadTowOverEm() < 0.05 &&
				    ((input[i].photonRef()->isEB() && input[i].photonRef()->sigmaIetaIeta() < 0.011) || (input[i].photonRef()->isEE() && input[i].photonRef()->sigmaIetaIeta() < 0.033)));
	    if(passeskincuts && passespreselection){
	      if (vetophotons) veto = true;
	      outputphotons->push_back(input[i].photonRef());
	    }

            if (passeskincuts && isconversionssafe && passesselection) {
	      // if (vetophotons) veto = true;
	      //outputphotons->push_back(input[i].photonRef());
                if (input[i].photonRef()->pt() > 160 && fabs(input[i].photonRef()->eta()) < 2.5) {
                    if (input[i].photonRef()->pt() > leadingphotonpt) {
                        leadingphotonpt = input[i].photonRef()->pt();
                        leadingphotonindex = i;
                    }
                    outputtightphotons->push_back(input[i].photonRef());
                }
            }
        }

        if (!veto) {
            PFCandidatePtr ptrToMother(inputH, i);
            output->push_back(input[i]);
            output->back().setSourceCandidatePtr(ptrToMother);
        }
    }

    if (leadingphotonindex >= 0) outputleadingphoton->push_back(input[leadingphotonindex].photonRef());

    iEvent.put(output, "pfcands");
    iEvent.put(outputmuons, "muons");
    iEvent.put(outputelectrons, "electrons");
    iEvent.put(outputphotons, "photons");
    iEvent.put(outputtightmuons, "tightmuons");
    iEvent.put(outputtightelectrons, "tightelectrons");
    iEvent.put(outputtightphotons, "tightphotons");
    iEvent.put(outputleadingphoton, "leadingphoton");
}

void PFCleaner::beginJob() {
}

void PFCleaner::endJob() {
}

void PFCleaner::beginRun(edm::Run&, edm::EventSetup const&) {
}

void PFCleaner::endRun(edm::Run&, edm::EventSetup const&) {
}

void PFCleaner::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {
}

void PFCleaner::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {
}

void PFCleaner::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

double PFCleaner::getChargedHadronEAForPhotonIso(double eta) {
    if (fabs(eta) < 1.0) return 0.012;
    else if (fabs(eta) >= 1.0   && fabs(eta) < 1.479) return 0.010;
    else if (fabs(eta) >= 1.479 && fabs(eta) < 2.0  ) return 0.014;
    else if (fabs(eta) >= 2.0   && fabs(eta) < 2.2  ) return 0.012;
    else if (fabs(eta) >= 2.2   && fabs(eta) < 2.3  ) return 0.016;
    else if (fabs(eta) >= 2.3   && fabs(eta) < 2.4  ) return 0.020;
    else if (fabs(eta) >= 2.4) return 0.012;
    else return 0.;
}

double PFCleaner::getNeutralHadronEAForPhotonIso(double eta) {
    if (fabs(eta) < 1.0) return 0.030;
    else if (fabs(eta) >= 1.0   && fabs(eta) < 1.479) return 0.057;
    else if (fabs(eta) >= 1.479 && fabs(eta) < 2.0  ) return 0.039;
    else if (fabs(eta) >= 2.0   && fabs(eta) < 2.2  ) return 0.015;
    else if (fabs(eta) >= 2.2   && fabs(eta) < 2.3  ) return 0.024;
    else if (fabs(eta) >= 2.3   && fabs(eta) < 2.4  ) return 0.039;
    else if (fabs(eta) >= 2.4) return 0.072;
    else return 0.;
}

double PFCleaner::getGammaEAForPhotonIso(double eta) {
    if (fabs(eta) < 1.0) return 0.148;
    else if (fabs(eta) >= 1.0   && fabs(eta) < 1.479) return 0.130;
    else if (fabs(eta) >= 1.479 && fabs(eta) < 2.0  ) return 0.112;
    else if (fabs(eta) >= 2.0   && fabs(eta) < 2.2  ) return 0.216;
    else if (fabs(eta) >= 2.2   && fabs(eta) < 2.3  ) return 0.262;
    else if (fabs(eta) >= 2.3   && fabs(eta) < 2.4  ) return 0.260;
    else if (fabs(eta) >= 2.4) return 0.266;
    else return 0.;
}

bool PFCleaner::testPhotonIsolation(reco::PhotonRef photon, double chargedHadronIsolation, double neutralHadronIsolation, double gammaIsolation, double rhoval) {
    double corrCHIso = chargedHadronIsolation - rhoval * getChargedHadronEAForPhotonIso(photon->eta());
    double corrNHIso = neutralHadronIsolation - rhoval * getNeutralHadronEAForPhotonIso(photon->eta());
    double corrPHIso = gammaIsolation - rhoval * getGammaEAForPhotonIso(photon->eta());

   if (corrCHIso < 0.) corrCHIso = 0.;
    if (corrNHIso < 0.) corrNHIso = 0.;
    if (corrPHIso < 0.) corrPHIso = 0.;

    if (photon->isEB()) {
        if (corrCHIso < 1.5 && corrNHIso < 1.0 + 0.04*photon->pt() && corrPHIso < 0.7 + 0.005*photon->pt()) return true;
        else return false;
    }
    else {
        if (corrCHIso < 1.2 && corrNHIso < 1.5 + 0.04*photon->pt() && corrPHIso < 1.0 + 0.005*photon->pt()) return true;
        else return false;
    }
}



bool PFCleaner::testPhotonPreselection(reco::PhotonRef photon, double chargedHadronIsolation,  double gammaIsolation, double rhoval) {
    double corrCHIso = chargedHadronIsolation - rhoval * getChargedHadronEAForPhotonIso(photon->eta());
    double corrPHIso = gammaIsolation - rhoval * getGammaEAForPhotonIso(photon->eta());

    //    if (corrCHIso < 0.) corrCHIso = 0.;
    //if (corrPHIso < 0.) corrPHIso = 0.;
 
    if (photon->r9()>0.9){
      if(corrCHIso<4 && corrPHIso < 10 && photon->sigmaIetaIeta() <0.14 && photon->hadTowOverEm() < 0.082&& photon->hcalTowerSumEtConeDR03()<(50+0.005*photon->pt())&&photon->trkSumPtHollowConeDR03()<(50+0.002*photon->pt())){
	  return true;
	} else return false;
    }else {
        if (corrCHIso<4 && corrPHIso < 10 && photon->sigmaIetaIeta() <0.14 && photon->hadTowOverEm() < 0.075&& photon->hcalTowerSumEtConeDR03()<(4+0.005*photon->pt())&&photon->trkSumPtHollowConeDR03()<(4+0.002*photon->pt())) return true;
        else return false;
    }
}

DEFINE_FWK_MODULE(PFCleaner);
