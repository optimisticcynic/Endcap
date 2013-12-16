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

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include <TDirectory.h> 
//obviously trying to get directories to work so I could look at the electrons in the correct regions

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"

//
// class declaration
//

class HCALDigis : public edm::EDAnalyzer {
   public:
      explicit HCALDigis(const edm::ParameterSet&);
      ~HCALDigis();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
      TFile* tfile;
      std::string fname;
      TH1 *hAvgDigi, *hAvgadc, *hDigi[26][36][2], *hadc[26][36][2];
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
HCALDigis::HCALDigis(const edm::ParameterSet& iConfig)
{
  edm::Service<TFileService> fs;

   hAvgDigi = fs->make<TH1F>("avgDigi","avgDigi",10, -0.5, 9.5);
   hAvgadc = fs->make<TH1F>("avgAdc","avgAdc",100,-0.5,99.5);
   char ht[256];
   for (int i=0;i<13;i++) for (int j=0;j<36;j++) for (int k=0;k<2;k++) 
   {
      if (i>10 && j%2==0) continue;
      sprintf(ht,"digi_+%d_%d_%d",i+29,j*2+1,k+1);
      hDigi[i][j][k] = fs->make<TH1F>(ht,ht,10,-0.5,9.5);
      sprintf(ht,"digi_-%d_%d_%d",i+29,j*2+1,k+1);
      hDigi[i+13][j][k] = fs->make<TH1F>(ht,ht,10,-0.5,9.5);
      sprintf(ht,"adc_+%d_%d_%d",i+29,j*2+1,k+1);
      hadc[i][j][k] = fs->make<TH1F>(ht,ht,100,-0.5,99.5);
      sprintf(ht,"adc_-%d_%d_%d",i+29,j*2+1,k+1);
      hadc[i+13][j][k] = fs->make<TH1F>(ht,ht,100,-0.5,99.5);

   } 

   printDigi = iConfig.getUntrackedParameter<bool>("printDigi", false);

}


HCALDigis::~HCALDigis()
{
 
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

  edm::Handle<HFDigiCollection> hf_digi;
  iEvent.getByType(hf_digi);

  //std::cout << hf_digi.isValid() << " \t "<< hf_digi->size() << std::endl;

  for (unsigned ihit = 0; ihit < hf_digi->size (); ++ihit) {
    const HFDataFrame& frame = (*hf_digi)[ihit];
    int ieta = frame.id().ieta();
    int iphi = frame.id().iphi();
    int depth = frame.id().depth();

    if(printDigi) std::cout << frame << std::endl;

    //translate from real ieta/iphi/depth to array indicies
    if (ieta>0) ieta = ieta-29;
    else ieta = 13-ieta-29;
    iphi = (iphi - 1)/2;
    depth--;

    //fill digi histograms
    for (int isample = 0; isample < frame.size(); ++isample) {
      int adc = frame[isample].adc();
      hAvgDigi->SetBinContent(isample+1, hAvgDigi->GetBinContent(isample+1) + adc);
      hAvgadc->Fill(adc);
      hDigi[ieta][iphi][depth]->SetBinContent(isample+1, hDigi[ieta][iphi][depth]->GetBinContent(isample+1) + adc);
      hadc[ieta][iphi][depth]->Fill(adc);
    }
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
HCALDigis::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HCALDigis::endJob() 
{
    for (int i=0;i<13;i++) for (int j=0;j<36;j++) for (int k=0;k<2;k++) 
    {
	if (i>10 && j%2==0) continue;
	if(hDigi[i][j][k]->GetEntries()) hDigi[i][j][k]->Scale(1/hDigi[i][j][k]->GetEntries());
	if(hDigi[i+13][j][k]->GetEntries()) hDigi[i+13][j][k]->Scale(1/hDigi[i+13][j][k]->GetEntries());
    }
}

// ------------ method called when starting to processes a run  ------------
void 
HCALDigis::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
HCALDigis::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
HCALDigis::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
HCALDigis::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HCALDigis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HCALDigis);
