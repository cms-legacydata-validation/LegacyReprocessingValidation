// -*- C++ -*-
//
// Class:      PhysicsObjectsHistos
//
/**\class PhysicsObjectsHistos PhysicsObjectsHistos.cc

*/
//
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

//yop electrones
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

//yop fotones
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

//yop jets
#include "DataFormats/JetReco/interface/PFJet.h"

#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"

//yop taus
#include "DataFormats/TauReco/interface/PFTauDiscriminator.h"
#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/TauReco/interface/PFTauFwd.h"

//missing energy
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/METReco/interface/METCollection.h"
#include "DataFormats/METReco/interface/METFwd.h"

#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/PFMETFwd.h"



//
// class decleration
//

class PhysicsObjectsHistos : public edm::EDAnalyzer {
public:
  explicit PhysicsObjectsHistos(const edm::ParameterSet&);
  ~PhysicsObjectsHistos();


private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // ----------member data ---------------------------
  unsigned int minTracks_;
  TH1D *demohisto;
TH1D *h1;
TH1D *h2;
TH1D *h3;
TH1D *h4;

TH1D *h11;
TH1D *h12;
TH1D *h13;
TH1D *h14;

  //yop histogramas elec
TH1D *h21;
TH1D *h22;
TH1D *h23;
TH1D *h24;

  //histogramas photons
TH1D *h31;
TH1D *h32;
TH1D *h33;
TH1D *h34;

  //histogram jets
TH1D *h41;
TH1D *h42;
TH1D *h43;
TH1D *h44;

  //histograms taus
TH1D *h51;
TH1D *h52;
TH1D *h53;
TH1D *h54;

  //missing transverse energy
TH1D *h61;
TH1D *h62;
TH1D *h63;
TH1D *h64;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

PhysicsObjectsHistos::PhysicsObjectsHistos(const edm::ParameterSet& iConfig) :
  minTracks_(iConfig.getUntrackedParameter<unsigned int>("minTracks",0))
{

  //now do what ever initialization is needed

  // I want to make a histogram of number of tracks in an event

  edm::Service<TFileService> fs;
  demohisto = fs->make<TH1D>("tracks" , "Tracks" , 100 , 0 , 5000 );

h1 = fs->make<TH1D>("TR_momentum", "Track momentum", 100, 0., 20.);
h1->GetXaxis()->SetTitle("Track Momentum (in GeV/c)");
h1->GetYaxis()->SetTitle("Number of Events");

// track Transverse_momentum
h2 = fs->make<TH1D>("TR_Transverse_momentum", "Track transverse momentum", 100, 0., 20.);
h2->GetXaxis()->SetTitle("Transverse Momentum of tracks (in GeV/c)");
h2->GetYaxis()->SetTitle("Number of Events");

// track pseudorapity
h3 = fs->make<TH1D>("TR_eta", "Track eta", 140, -3.5, 3.5);
h3->GetXaxis()->SetTitle("Eta of tracks");
h3->GetYaxis()->SetTitle("Number of Events");

// global muon azimuth angle
h4 = fs->make<TH1D>("TR_phi", "Track phi", 314, -3.15, 3.15);
h4->GetXaxis()->SetTitle("Phi (in radians)");
h4->GetYaxis()->SetTitle("Number of Events");

h11 = fs->make<TH1D>("Mu_momentum", "Muon momentum", 100, 0., 20.);
h11->GetXaxis()->SetTitle("Muon Momentum (in GeV/c)");
h11->GetYaxis()->SetTitle("Number of Events");

//  muon Transverse_momentum
h12 = fs->make<TH1D>("Mu_Transverse_momentum", "Muon transverse momentum", 100, 0., 20.);
h12->GetXaxis()->SetTitle("Transverse Momentum of muons (in GeV/c)");
h12->GetYaxis()->SetTitle("Number of Events");

//  muon pseudorapity
h13 = fs->make<TH1D>("Mu_eta", "Muon eta", 140, -3.5, 3.5);
h13->GetXaxis()->SetTitle("Eta of muons");
h13->GetYaxis()->SetTitle("Number of Events");

//  muon azimuth angle
h14 = fs->make<TH1D>("Mu_phi", "M_phi", 314, -3.15, 3.15);
h14->GetXaxis()->SetTitle("Phi (in radians)");
h14->GetYaxis()->SetTitle("Number of Events");

//electrones his

h21 = fs->make<TH1D>("Ele_momentum", "Electron momentum", 100, 0., 40.);
h21->GetXaxis()->SetTitle("Electron Momentum (in GeV/c)");
h21->GetYaxis()->SetTitle("Number of Events");

//  electron Transverse_momentum
h22 = fs->make<TH1D>("Ele_Transverse_momentum", "Electron transverse momentum", 100, 0., 40.);
h22->GetXaxis()->SetTitle("Transverse Momentum of electrons (in GeV/c)");
h22->GetYaxis()->SetTitle("Number of Events");

//  electon pseudorapity
h23 = fs->make<TH1D>("Ele_eta", "Electron eta", 140, -3.5, 3.5);
h23->GetXaxis()->SetTitle("Eta of electrons");
h23->GetYaxis()->SetTitle("Number of Events");

//  electron azimuth angle
h24 = fs->make<TH1D>("Ele_phi", "Electron phi", 314, -3.15, 3.15);
h24->GetXaxis()->SetTitle("Phi (in radians)");
h24->GetYaxis()->SetTitle("Number of Events");

//photons

//photon his

h31 = fs->make<TH1D>("Gam_momentum", "Photon momentum", 100, 0., 40.);
h31->GetXaxis()->SetTitle("Photon Momentum (in GeV/c)");
h31->GetYaxis()->SetTitle("Number of Events");

//  photon Transverse_momentum
h32 = fs->make<TH1D>("Gam_Transverse_momentum", "Photon transverse momentum", 100, 0., 40.);
h32->GetXaxis()->SetTitle("Transverse Momentum of photons (in GeV/c)");
h32->GetYaxis()->SetTitle("Number of Events");

//  photon  pseudorapity
h33 = fs->make<TH1D>("Gam_eta", "Photon eta", 140, -3.5, 3.5);
h33->GetXaxis()->SetTitle("Eta of photons");
h33->GetYaxis()->SetTitle("Number of Events");

//  photon  azimuth angle
h34 = fs->make<TH1D>("Gam_phi", "Photon phi", 314, -3.15, 3.15);
h34->GetXaxis()->SetTitle("Phi (in radians)");
h34->GetYaxis()->SetTitle("Number of Events");


//jets

//jet his

h41 = fs->make<TH1D>("Jet_momentum", "Jet momentum", 100, 0., 40.);
h41->GetXaxis()->SetTitle("Jet Momentum (in GeV/c)");
h41->GetYaxis()->SetTitle("Number of Events");

//  jet Transverse_momentum
h42 = fs->make<TH1D>("Jet_Transverse_momentum", "Jet transverse momentum", 100, 0., 40.);
h42->GetXaxis()->SetTitle("Transverse Momentum of jets (in GeV/c)");
h42->GetYaxis()->SetTitle("Number of Events");

//  jet  pseudorapity
h43 = fs->make<TH1D>("Jet_eta", "Jet eta", 140, -3.5, 3.5);
h43->GetXaxis()->SetTitle("Eta of jets");
h43->GetYaxis()->SetTitle("Number of Events");

//  jet  azimuth angle
h44 = fs->make<TH1D>("Jet_phi", "Jet phi", 314, -3.15, 3.15);
h44->GetXaxis()->SetTitle("Phi (in radians)");
h44->GetYaxis()->SetTitle("Number of Events");

//taus

// his

h51 = fs->make<TH1D>("Tau_momentum", "Tau momentum", 100, 0., 20.);
h51->GetXaxis()->SetTitle("Tau Momentum (in GeV/c)");
h51->GetYaxis()->SetTitle("Number of Events");

//  Transverse_momentum
h52 = fs->make<TH1D>("Tau_Transverse_momentum", "Tau transverse momentum", 100, 0., 20.);
h52->GetXaxis()->SetTitle("Transverse Momentum of taus (in GeV/c)");
h52->GetYaxis()->SetTitle("Number of Events");

//   pseudorapity
h53 = fs->make<TH1D>("Tau_eta", "Tau eta", 140, -3.5, 3.5);
h53->GetXaxis()->SetTitle("Eta of taus");
h53->GetYaxis()->SetTitle("Number of Events");

//  azimuth angle
h54 = fs->make<TH1D>("Tau_phi", "Tau phi", 314, -3.15, 3.15);
h54->GetXaxis()->SetTitle("Phi (in radians)");
h54->GetYaxis()->SetTitle("Number of Events");

//MET

// his

h61 = fs->make<TH1D>("MET_sumet", "MET Sum Et", 100, 0., 20.);
h61->GetXaxis()->SetTitle("MET Sum Et (in GeV/c)");
h61->GetYaxis()->SetTitle("Number of Events");

//  Transverse_momentum
h62 = fs->make<TH1D>("MET_Transverse_momentum", "MET transverse momentum", 100, 0., 20.);
h62->GetXaxis()->SetTitle("Transverse Momentum of MET (in GeV/c)");
h62->GetYaxis()->SetTitle("Number of Events");

//   pseudorapity
h63 = fs->make<TH1D>("MET_eta", "MET eta", 140, -3.5, 3.5);
h63->GetXaxis()->SetTitle("Eta of MET");
h63->GetYaxis()->SetTitle("Number of Events");

//  azimuth angle
h64 = fs->make<TH1D>("MET_phi", "MET phi", 314, -3.15, 3.15);
h64->GetXaxis()->SetTitle("Phi (in radians)");
h64->GetYaxis()->SetTitle("Number of Events");





}


PhysicsObjectsHistos::~PhysicsObjectsHistos()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
PhysicsObjectsHistos::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;

   Handle<reco::TrackCollection> tracks;
   iEvent.getByLabel("generalTracks", tracks);
   //   LogInfo("Demo") << "number of tracks "<<tracks->size();
   demohisto->Fill(tracks->size());

// WHAT: Loop over all the Global Muons of current Event
// WHY:  to select good candidates to be used in invariant mass calculation
  for (reco::TrackCollection::const_iterator it = tracks->begin();
     it != tracks->end(); it++) {
     h1->Fill(it->p());
     h2->Fill(it->pt());
     h3->Fill(it->eta());
     h4->Fill(it->phi());

   }

   Handle<reco::MuonCollection> mymuons;
   iEvent.getByLabel("muons", mymuons);
     for(reco::MuonCollection::const_iterator itMuon = mymuons->begin();
       itMuon != mymuons->end();
       ++itMuon) {
         h11->Fill(itMuon->p());
    h12->Fill(itMuon->pt());
    h13->Fill(itMuon->eta());
    h14->Fill(itMuon->phi());//  your code
   }

     //electrones
   Handle<reco::GsfElectronCollection> electrons;
   iEvent.getByLabel("gsfElectrons", electrons);
   for(reco::GsfElectronCollection::const_iterator itElectron = electrons->begin();
       itElectron != electrons->end();
       ++itElectron) {
    h21->Fill(itElectron->p());
    h22->Fill(itElectron->pt());
    h23->Fill(itElectron->eta());
    h24->Fill(itElectron->phi());
   }

   //PHOTONS
 Handle<reco::PhotonCollection> photons;
   iEvent.getByLabel("photons", photons);
   // LogInfo("Demo") << "number of photons "<<photons->size();
for(reco::PhotonCollection::const_iterator itphotons = photons->begin();
       itphotons != photons->end();
       ++itphotons) {
    h31->Fill(itphotons->p());
    h32->Fill(itphotons->pt());
    h33->Fill(itphotons->eta());
    h34->Fill(itphotons->phi());
   }

  //jets
 Handle<reco::PFJetCollection> ak5PFJets;
   iEvent.getByLabel("ak5PFJets", ak5PFJets);
   for(reco::PFJetCollection::const_iterator itjets = ak5PFJets->begin();
       itjets != ak5PFJets->end();
       ++itjets) {
    h41->Fill(itjets->p());
    h42->Fill(itjets->pt());
    h43->Fill(itjets->eta());
    h44->Fill(itjets->phi());
   }

   //taus
   Handle<reco::PFTauCollection> taus;
   iEvent.getByLabel("hpsPFTauProducer", taus);
   Handle<reco::PFTauDiscriminator> discr;
   iEvent.getByLabel("hpsPFTauDiscriminationByDecayModeFinding", discr);
   for ( unsigned iTau = 0; iTau < taus->size(); ++iTau ) {
        reco::PFTauRef tauCandidate(taus, iTau);
// check if tau candidate has passed discriminator
        if( (*discr)[tauCandidate] > 0.5 ){
	  h51->Fill((*tauCandidate).p());
	  h52->Fill((*tauCandidate).pt());
	  h53->Fill((*tauCandidate).eta());
	  h54->Fill((*tauCandidate).phi());
        }
    }
   //for(reco::PFTauCollection::const_iterator itTaus = taus->begin();

   //    itTaus != taus->end();
   //    ++itTaus) {
   // h51->Fill(itTaus->p());
   // h52->Fill(itTaus->pt());
   // h53->Fill(itTaus->eta());
   //  h54->Fill(itTaus->phi());
   //}

   // MET
   Handle<reco::PFMETCollection> pfMet;
   iEvent.getByLabel("pfMet", pfMet);
   // for(reco::PFMETCollection::const_iterator itmet = pfMet->begin();
   //  itmet != pfMet->end();
   //  ++itmet) {

  h61->Fill((*pfMet)[0].sumEt());
  h62->Fill((*pfMet)[0].et());
  h63->Fill((*pfMet)[0].eta());
  h64->Fill((*pfMet)[0].phi());
   // }




#ifdef THIS_IS_AN_EVENT_EXAMPLE
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void
PhysicsObjectsHistos::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
PhysicsObjectsHistos::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(PhysicsObjectsHistos);