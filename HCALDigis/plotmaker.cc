#include <TLegend.h>
#include <TDirectory.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <math.h> 
#include <map>
#include "TH1.h"
#include <string>
#include <TFile.h>
#include <iostream>






//This will hopefully grab the data and make a combined graph of the electron to other junk

void combinhistogram()
{//Carful here, this is copied from another type of code, make sure it is pruined properly

    //since the electron and none electron is in a differnt c directory this is needed to grab the data
     
    
    std::string type = ".pdf";
    std::string plotname;
    TFile* theFile = new TFile("digis.root");
    if(!theFile) 
    {
        cout<<"well it isn't reading the file bro"<<endl;
        return;
    }
    std::string ele = "demo/pass/avgAdc";
    std::string background = "demo/nepass/avgAdc";

    TH1D* eAdc;
    TH1D* neAdc;

    //sprintf(hfName,"%d%d%d_%d%d%d" ,parameter1[1],parameter2[1],parameter3[1],nparameter1[1],nparameter2[1],nparameter3[1]);
    eAdc = (TH1D*) theFile->Get(ele.c_str());
    neAdc = (TH1D*) theFile->Get(background.c_str());



    std::cout << " Done opening. " << eAdc << std::endl;

    // this should draw the graphs
    TCanvas* c1 = new TCanvas("c1", "", 800, 700);
    c1->SetFillColor(10);
    c1->SetFillColor(10);
    c1->cd();

    float max1 = eAdc->GetMaximum();
    float max2 = neAdc->GetMaximum();

    eAdc->SetMaximum(1.1 * max(max1, max2));
    eAdc->Draw();
    neAdc->SetLineColor(8);
    neAdc->Draw("same");

    gStyle->SetOptStat("eoumi");
    gStyle->SetOptStat("");
    c1->SetLogy();




    TLegend* leg = new TLegend(0.6, 0.7, 0.9, 0.9); // lets make a legend to tell everything apart
    leg->SetHeader("combo of hits");
    leg-> SetFillColor(kWhite);
    leg-> SetShadowColor(kWhite);

    leg->AddEntry(neAdc, ("not an electron"));
    leg->AddEntry(eAdc, ("is an electron"));
    leg->Draw();

    c1->Update();
    plotname="Electron_vrs_nonelectronadc"+type;
    c1->Print(plotname.c_str());
    delete c1;








    //This does the digital data  
    
     ele = "demo/pass/avgDigi";
    background = "demo/nepass/avgDigi";

    TH1D* eDigi;
    TH1D* neDigi;


    eDigi = (TH1D*) theFile->Get(ele.c_str());
    neDigi = (TH1D*) theFile->Get(background.c_str());



    std::cout << " Done opening. " << eDigi << std::endl;

    // this should draw the graphs
    TCanvas* c2 = new TCanvas("c1", "", 800, 700);
    c2->SetFillColor(10);
    c2->SetFillColor(10);
    c2->cd();

    max1 = eDigi->GetMaximum();
    max2 = neDigi->GetMaximum();

    eDigi->SetMaximum(1.1 * max(max1, max2));
    eDigi->Draw();
    neDigi->SetLineColor(8);
    neDigi->Draw("same");

    gStyle->SetOptStat("eoumi");
    gStyle->SetOptStat("");
    c2->SetLogy();




    TLegend* leg1 = new TLegend(0.6, 0.7, 0.9, 0.9); // lets make a legend to tell everything apart
    leg1->SetHeader("combo of hits");
    leg1-> SetFillColor(kWhite);
    leg1-> SetShadowColor(kWhite);
    //leg->AddEntry(h1.at(0),(typ1 calElectron/+ " dr of " + dr1 + " layers " + lay1 + lay2 + lay3 ).c_str(), "l");
    leg1->AddEntry(neDigi, ("not an electron"));
    leg1->AddEntry(eDigi, ("is an electron"));
    leg1->Draw();

    c2->Update();
    plotname="Electron_vrs_nonelectronDigi"+type;
    c2->Print(plotname.c_str());
    delete c2;



    //and finally we have the linear adc
   
    ele = "demo/pass/avglinAdc";
    background = "demo/nepass/avglinAdc";

    TH1D* elinAdc;
    TH1D* nelinAdc;

    //sprintf(hfName,"%d%d%d_%d%d%d" ,parameter1[1],parameter2[1],parameter3[1],nparameter1[1],nparameter2[1],nparameter3[1]);
    elinAdc = (TH1D*) theFile->Get(ele.c_str());
    nelinAdc = (TH1D*) theFile->Get(background.c_str());



    std::cout << " Done opening. " << elinAdc << std::endl;

    // this should draw the graphs
    TCanvas* c3 = new TCanvas("c1", "", 800, 700);
    c3->SetFillColor(10);
    c3->SetFillColor(10);
    c3->cd();

     max1 = elinAdc->GetMaximum();
     max2 = nelinAdc->GetMaximum();

    elinAdc->SetMaximum(1.1 * max(max1, max2));
    elinAdc->Draw();
    nelinAdc->SetLineColor(8);
    nelinAdc->Draw("same");

    gStyle->SetOptStat("eoumi");
    gStyle->SetOptStat("");
    c3->SetLogy();
    TLegend* leg2 = new TLegend(0.6, 0.7, 0.9, 0.9); // lets make a legend to tell everything apart
    leg2->SetHeader("combo of hits");
    leg2-> SetFillColor(kWhite);
    leg2-> SetShadowColor(kWhite);
    
    leg2->AddEntry(nelinAdc, ("not an electron"));
    leg2->AddEntry(elinAdc, ("is an electron"));
    leg2->Draw();

    c3->Update();
    plotname=("Electron_vrs_nonelectronlinadc"+type);
    c3->Print(plotname.c_str());
    delete c3;





}
