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
#include "DataFormats/HcalDetId/interface/HcalFrontEndId.h"

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
    TH1 *PhAvglinadc, *PhAvgDigi, *PhAvgadc, *PhDigi[26][36][2], *Phadc[26][36][2]; //So for now this is histograms that do have eta with test range

    TH1 *PnehAvglinadc, *PnehAvgDigi, *PnehAvgadc, *PnehDigi[26][36][2], *Pnehadc[26][36][2]; //So this is particles that pass the tests but arn't electrons

    TH2 *Psvrsladc, *Plladcvrgen; // psvrsladc is the short vrs long adc and plladcvrsgen is simply long linadc to generated energy with
    //the p stands for electrons

    TH2 *Pnesvrsladc, *Pnelladcvrgen; // psvrsladc is the short vrs long adc and plladcvrsgen is simply long linadc to generated energy with
    //the pne stands for non electrons electrons


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

    //so this should be for loop makes an array of possible charges that the command  HFDataFram nominal give us
    //subtracting small amount so that the values fall inside the bins
    const float orginal[128] = {-0.5f, 0.5f, 1.5f,
        2.5f, 3.5f, 4.5f,
        5.5f, 6.5f, 7.5f,
        8.5f, 9.5f, 10.5f,
        11.5f, 12.5f, 13.5f,
        15.0f, 17.0f, 19.0f,
        21.0f, 23.0f, 25.0f,
        27.0f, 29.5f, 32.5f,
        35.5f, 38.5f, 42.0f, 46.0f, 50.0f,
        54.5f, 59.5f, 64.5f,
        69.5f, 74.5f, 79.5f, 84.5f, 89.5f, 94.5f, 99.5f, 104.5f, 109.5f, 114.5f, 119.5f, 124.5f, 129.5f,
        137.0f, 147.0f, 157.0f, 167.0f, 177.0f, 187.0f, 197.0f,
        209.5f, 224.5f, 239.5f, 254.5f,
        272.0f, 292.0f, 312.0f,
        334.5f, 359.5f, 384.5f,
        409.5f, 434.5f, 459.5f, 484.5f, 509.5f, 534.5f, 559.5f, 584.5f, 609.5f, 634.5f, 659.5f, 684.5f, 709.5f,
        747.0f, 797.0f, 847.0f, 897.0f, 947.0f, 997.0f, 1047.0f,
        1109.5f, 1184.5f, 1259.5f, 1334.5f,
        1422.0f, 1522.0f, 1622.0f,
        1734.5f, 1859.5f, 1984.5f,
        2109.5f, 2234.5f, 2359.5f, 2484.5f, 2609.5f, 2734.5f, 2859.5f, 2984.5f, 3109.5f, 3234.5f, 3359.5f, 3484.5f, 3609.5f,
        3797.0f, 4047.0f, 4297.0f, 4547.0f, 4797.0f, 5047.0f, 5297.0f,
        5609.5f, 5984.5f, 6359.5f, 6734.5f,
        7172.0f, 7672.0f, 8172.0f,
        8734.5f, 9359.5f, 9984.5f};



    PhAvglinadc = passed.make<TH1F>("avglinAdc", "avglinAdc", 121, orginal);
    PnehAvglinadc = notep.make<TH1F>("avglinAdc", "avglinAdc", 121, orginal);

    Psvrsladc = passed.make<TH2F>("short_fiber_vrs_long_adc", "short fiber vrs long; long fiber adc; short fiber adc", 150, -0.5, 150.5, 150, -0.5, 150.5);
    Pnesvrsladc = notep.make<TH2F>("short_fiber_vrs_long_adc", "short fiber vrs long; long fiber adc; short fiber adc", 150, -0.5, 150.5, 150, -0.5, 150.5);
    // psvrsladc is the short vrs long adc and plladcvrsgen is simply long linadc to generated energy with
    //the p stands for electrons


    float bins[101];
    for(int i = 1; i <= 100; i++)
    {
        bins[i] = (float) (-.5 + i * 20);
    }



    Plladcvrgen = passed.make<TH2F>("linladc_to_gen", "linadc to generated energy; genenergy Gev; linear adc fc", 100, bins, 121, orginal);
    Pnelladcvrgen = notep.make<TH2F>("linladc_to_gen", "linadc to generated energy; genenergy Gev; linear adc fc", 100, bins, 121, orginal);




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


    double genE[26][74];
    for(int q = 0; q < 26; q++)
    {
        for(int w = 0; w < 74; w++)
        {
            genE[q][w] = -1; //so this should make it so that if a generated particle didn't hit there it wont go on the histogram
        }
    }

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

        int ietag;
        int iphig;
        if(gieta > 0) ietag = gieta - 29;
        else ietag = 13 - gieta - 29;
        iphig = (giphi - 1) / 2;





        if(pdgid == 11 && genin.numberOfDaughters() > 0)
        {

            gparts.insert(make_pair(gieta, giphi));
        }
        if(genE[ietag][iphig] < genin.energy())//hopfully gives us translation for the max gen energy that goes into this bloody cell
        {
            genE[ietag][iphig] = genin.energy();
        }



    }


    //std::cout << hf_digi.isValid() << " \t "<< hf_digi->size() << std::endl;



    for(unsigned ihit = 0; ihit < hf_digi->size(); ++ihit)
    {
        const HFDataFrame& frame = (*hf_digi)[ihit];
        int ieta = frame.id().ieta();
        int iphi = frame.id().iphi();
        int depth = frame.id().depth();
        int adc1M = 0; // max adc for long
        int adc2M = 0; //so this is the max adc for short 

        //so change this up one value to go from long to short
        HcalDetId bob(frame.id().subdet(), ieta, iphi, 2);

        //Grabs  from entire digital collection
        HFDigiCollection::const_iterator theit = hf_digi->find(bob);

        //grabs adc information
        //theit->adc();

        for(int isample = 0; isample < theit->size(); ++isample)//here is how I am finding the info in theit. 
        { //I couldn't fire out how to grab it staight from theit
            if(adc2M < (*theit)[isample].adc()) //so I simply turned used a * to make it not a pointer 
            { //probably overcomplicated it ask joe about it
                adc2M = (*theit)[isample].adc();
            }

        }


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
            int Mladc = 0;
            double max = 0; //should be max charge deposited
            int adc = 0;
            for(int isample = 0; isample < frame.size(); ++isample)//time in particulare. 5 times
            {

                //ADC
                if(adc < frame[isample].adc())
                {
                    adc = frame[isample].adc();
                }



                if(Mladc < frame[isample].adc())
                {
                    Mladc = frame[isample].adc();
                }

                if(frame[isample].nominal_fC() > max) max = frame[isample].nominal_fC();
                PhAvgDigi->SetBinContent(isample + 1, PhAvgDigi->GetBinContent(isample + 1) + adc);

                PhDigi[ieta][iphi][depth]->SetBinContent(isample + 1, PhDigi[ieta][iphi][depth]->GetBinContent(isample + 1) + adc);
                Phadc[ieta][iphi][depth]->Fill(adc);

                if(adc1M < frame[isample].adc())
                {
                    adc1M = frame[isample].adc();
                }
            }
            PhAvgadc->Fill(adc);

            if(depth == 0)//so this should hopefully just fill it with the max adc and be done...
            {

                Plladcvrgen->Fill(genE[ieta][iphi], max);
                Psvrsladc->Fill(adc1M, adc2M);

            }
            PhAvglinadc->Fill(max);
        }//so this following piece should be things that are not electrons that are passing at this moment. since right now I am not doing any cuts it is obviously a graph of all non electrons

        else
        {


            double max = 0;

            for(int isample = 0; isample < frame.size(); ++isample)
            {


                if(adc < frame[isample].adc())
                {
                    adc = frame[isample].adc();
                }

                //linearadc? maybe...
                int adc = frame[isample].adc();
                if(frame[isample].nominal_fC() > max) max = frame[isample].nominal_fC();
                PnehAvgDigi->SetBinContent(isample + 1, PnehAvgDigi->GetBinContent(isample + 1) + adc);
                PnehAvgadc->Fill(adc);

                PnehDigi[ieta][iphi][depth]->SetBinContent(isample + 1, PnehDigi[ieta][iphi][depth]->GetBinContent(isample + 1) + adc);
                Pnehadc[ieta][iphi][depth]->Fill(adc);

                if(adc1M < frame[isample].adc())
                {
                    adc1M = frame[isample].adc();
                }


            }
            if(depth == 0)//so this should hopefully just fill it with the max adc and be done...
            {

                Pnelladcvrgen->Fill(genE[ieta][iphi], max);
                Pnesvrsladc->Fill(adc1M, adc2M);

            }
            PnehAvgadc->Fill(adc);
            PnehAvglinadc->Fill(max);
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


