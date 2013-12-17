// -*- C++ -*-
//
// Package:    HCALDigis
// Class:      HCALDigis
// 
/**\class HCALDigis HCALDigis.cc HCALDFT/HCALDigis/src/HCALDigis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
 */
//
// Original Author:  Nathaniel Joseph Pastika,40 R-A08,+41227675312,
//         Created:  Thu Dec  8 11:03:34 CET 2011
// $Id$
//
//


// system include files
#include <memory>
#include <vector>
#include <map>
#include <utility>
#define _USE_MATH_DEFINES 
#include <math.h>
//not sure if this will work need to change this bloody into 
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <TDirectory.h> 
//obviously trying to get directories to work so I could look at the electrons in the correct regions

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"

//
// class declaration
//

class HCALDigis : public edm::EDAnalyzer
{
public:
    explicit HCALDigis(const edm::ParameterSet&);
    ~HCALDigis();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void beginJob();
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob();

    virtual void beginRun(edm::Run const&, edm::EventSetup const&);
    virtual void endRun(edm::Run const&, edm::EventSetup const&);
    virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
    virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

    int etatoieta(double angle);

    // ----------member data ---------------------------
    TFile* tfile;
    std::string fname;
    TH1 *PhAvgDigi, *PhAvgadc, *PhDigi[26][36][2], *Phadc[26][36][2]; //So for now this is histograms that do have eta with test range
    TH1 *FhAvgDigi, *FhAvgadc, *FhDigi[26][36][2], *Fhadc[26][36][2]; //these graph data that does not pass the eta test
    TH1 *PnehAvgDigi, *PnehAvgadc, *PnehDigi[26][36][2], *Pnehadc[26][36][2]; //So this is particles that pass the tests but arn't electrons
    TH1 *FnehAvgDigi, *FnehAvgadc, *FnehDigi[26][36][2], *Fnehadc[26][36][2]; //these graph data that fail but are not electrons
    bool printDigi;
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
//SOOO we are doing a burn to the ground thing at this point
//not quite sure how the files are orginized so I am going to attempt to make my own system to save files

HCALDigis::HCALDigis(const edm::ParameterSet& iConfig)
{
    edm::Service<TFileService> fs;
    TFileDirectory passed = fs->mkdir("pass");


    TFileDirectory notep = fs->mkdir("nepass");
    PhAvgDigi = passed.make<TH1F>("avgDigi", "avgDigi", 10, -0.5, 9.5);
    PhAvgadc = passed.make<TH1F>("avgAdc", "avgAdc", 100, -0.5, 99.5);
    PnehAvgDigi = notep.make<TH1F>("avgDigi", "avgDigi", 10, -0.5, 9.5);
    PnehAvgadc = notep.make<TH1F>("avgAdc", "avgAdc", 100, -0.5, 99.5);
    char ht[256];


    for(int i = 0; i < 13; i++) for(int j = 0; j < 36; j++) for(int k = 0; k < 2; k++)
            {

                if(i > 10 && j % 2 == 0) continue;
                sprintf(ht, "digi_+%d_%d_%d", i + 29, j * 2 + 1, k + 1);
                PhDigi[i][j][k] = passed.make<TH1F>(ht, ht, 10, -0.5, 9.5);
                sprintf(ht, "digi_-%d_%d_%d", i + 29, j * 2 + 1, k + 1);
                PhDigi[i + 13][j][k] = passed.make<TH1F>(ht, ht, 10, -0.5, 9.5);
                sprintf(ht, "adc_+%d_%d_%d", i + 29, j * 2 + 1, k + 1);
                Phadc[i][j][k] = passed.make<TH1F>(ht, ht, 100, -0.5, 99.5);
                sprintf(ht, "adc_-%d_%d_%d", i + 29, j * 2 + 1, k + 1);
                Phadc[i + 13][j][k] = passed.make<TH1F>(ht, ht, 100, -0.5, 99.5);


                sprintf(ht, "digi_+%d_%d_%d", i + 29, j * 2 + 1, k + 1);
                PnehDigi[i][j][k] = notep.make<TH1F>(ht, ht, 10, -0.5, 9.5);
                sprintf(ht, "digi_-%d_%d_%d", i + 29, j * 2 + 1, k + 1);
                PnehDigi[i + 13][j][k] = notep.make<TH1F>(ht, ht, 10, -0.5, 9.5);
                sprintf(ht, "adc_+%d_%d_%d", i + 29, j * 2 + 1, k + 1);
                Pnehadc[i][j][k] = notep.make<TH1F>(ht, ht, 100, -0.5, 99.5);
                sprintf(ht, "adc_-%d_%d_%d", i + 29, j * 2 + 1, k + 1);
                Pnehadc[i + 13][j][k] = notep.make<TH1F>(ht, ht, 100, -0.5, 99.5);


            }



    printDigi = iConfig.getUntrackedParameter<bool>("printDigi", false);

}

HCALDigis::~HCALDigis() {

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called for each event  ------------

void
HCALDigis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;

    edm::Handle<HFDigiCollection> hf_digi;
    iEvent.getByType(hf_digi);


    //vector <int> giphi;
    //map<pair<int, int>,  vector<reco::GenParticle*> > gparts; 
    set<pair<int, int> > gparts; //makes a set that contains locations of all generated electrons
    edm::Handle<reco::GenParticleCollection> genInfo;
    iEvent.getByLabel("genParticles", genInfo);
    //genInfo.pdgid no


    for(unsigned ighit = 0; ighit < genInfo->size(); ++ighit)// so this function goes and figures out the location of all electron location to allow matching4
    { //int i; delete? no idea what this was supposed to do
        const reco::GenParticle& genin = (* genInfo)[ighit];
        int giphi;
        if(genin.phi() >= 0)
        {
            giphi = ((int) ((genin.phi())*180 / M_PI) / 10)*2 + 1; //so this converts into degrees since everything is nicer there. followed by conversion it iphi
        } else
        {
            giphi = ((int) ((genin.phi())*180 / M_PI + 360) / 10)*2 + 1;
        }


        int gieta = etatoieta(genin.eta()); //the function that gets ieta from eta(genin.eta());
        int pdgid = genin.pdgId();

        if(pdgid == 11 && genin.numberOfDaughters() > 0)
        {

            gparts.insert(make_pair(gieta, giphi));
        }


    }


    //std::cout << hf_digi.isValid() << " \t "<< hf_digi->size() << std::endl;

    for(unsigned ihit = 0; ihit < hf_digi->size(); ++ihit)
    {
        const HFDataFrame& frame = (*hf_digi)[ihit];
        int ieta = frame.id().ieta();
        int iphi = frame.id().iphi();
        int depth = frame.id().depth();



        if(printDigi) std::cout << frame << std::endl;

        //translate from real ieta/iphi/depth to array indicies
        if(ieta > 0) ieta = ieta - 29;
        else ieta = 13 - ieta - 29;
        iphi = (iphi - 1) / 2;
        depth--;

        //fill digi histograms
        if(gparts.find(make_pair(frame.id().ieta(), frame.id().iphi())) != gparts.end())
        //if(true)
        {
            //cout << "so electron id has ieta=" << frame.id().ieta() << "  and a iphi of =" << frame.id().iphi() << endl;
            for(int isample = 0; isample < frame.size(); ++isample)//time in particulare. 5 times
            {
                //ADC
                int adc = frame[isample].adc();
                PhAvgDigi->SetBinContent(isample + 1, PhAvgDigi->GetBinContent(isample + 1) + adc);
                PhAvgadc->Fill(adc);
                PhDigi[ieta][iphi][depth]->SetBinContent(isample + 1, PhDigi[ieta][iphi][depth]->GetBinContent(isample + 1) + adc);
                Phadc[ieta][iphi][depth]->Fill(adc);
            }
        }
        //so this following piece should be things that are not electrons that are passing at this moment. since right now I am not doing any cuts it is obviously a graph of all non electrons
        //if(gparts.find(make_pair(frame.id().ieta(), frame.id().iphi())) == gparts.end())
        else
        {
            for(int isample = 0; isample < frame.size(); ++isample)//ask joe about this?????????????????????
            {

                //linearadc? maybe...
                int adc = frame[isample].adc();
                PnehAvgDigi->SetBinContent(isample + 1, PnehAvgDigi->GetBinContent(isample + 1) + adc);
                PnehAvgadc->Fill(adc);
                PnehDigi[ieta][iphi][depth]->SetBinContent(isample + 1, PnehDigi[ieta][iphi][depth]->GetBinContent(isample + 1) + adc);
                Pnehadc[ieta][iphi][depth]->Fill(adc);
            }
        }
    }
}


// ------------ method called once each job just before starting event loop  ------------

void
HCALDigis::beginJob() { }

// ------------ method called once each job just after ending the event loop  ------------

void
HCALDigis::endJob()
{
    for(int i = 0; i < 13; i++) for(int j = 0; j < 36; j++) for(int k = 0; k < 2; k++)
            {
                if(i > 10 && j % 2 == 0) continue;
                if(PhDigi[i][j][k]->GetEntries())
                {
                    PhDigi[i][j][k]->Scale(1 / PhDigi[i][j][k]->GetEntries());
                }
                if(PhDigi[i + 13][j][k]->GetEntries())
                {
                    PhDigi[i + 13][j][k]->Scale(1 / PhDigi[i + 13][j][k]->GetEntries());
                }
            }


    for(int i = 0; i < 13; i++) for(int j = 0; j < 36; j++) for(int k = 0; k < 2; k++)
            {
                if(i > 10 && j % 2 == 0) continue;
                if(PnehDigi[i][j][k]->GetEntries())
                {
                    PnehDigi[i][j][k]->Scale(1 / PhDigi[i][j][k]->GetEntries());
                }
                if(PnehDigi[i + 13][j][k]->GetEntries())
                {
                    PnehDigi[i + 13][j][k]->Scale(1 / PhDigi[i + 13][j][k]->GetEntries());
                }
            }
}

// ------------ method called when starting to processes a run  ------------

void
HCALDigis::beginRun(edm::Run const&, edm::EventSetup const&) { }

// ------------ method called when ending the processing of a run  ------------

void
HCALDigis::endRun(edm::Run const&, edm::EventSetup const&) { }

// ------------ method called when starting to processes a luminosity block  ------------

void
HCALDigis::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) { }

// ------------ method called when ending the processing of a luminosity block  ------------

void
HCALDigis::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) { }

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------

void
HCALDigis::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
{
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HCALDigis);

int HCALDigis::etatoieta(double angle)
{
    using namespace std;
    int anglesign = (int) (fabs(angle) / angle);
    angle = fabs(angle);
    int tower = 0;


    if(2.853 > angle) tower = 0;
    else if(angle <= 2.964) tower = 29;
    else if(angle <= 3.139) tower = 30;
    else if(angle <= 3.314) tower = 31;
    else if(angle <= 3.489) tower = 32;
    else if(angle <= 3.664) tower = 33;
    else if(angle <= 3.839) tower = 34;
    else if(angle <= 4.013) tower = 35;
    else if(angle <= 4.191) tower = 36;
    else if(angle <= 4.363) tower = 37;
    else if(angle <= 4.538) tower = 38;
    else if(angle <= 4.716) tower = 39;
    else if(angle <= 4.889) tower = 40;
    else if(angle <= 5.191) tower = 41;

    tower *= anglesign;



    return tower;
}
