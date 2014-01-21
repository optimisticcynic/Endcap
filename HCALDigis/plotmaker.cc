#include <TLegend.h>
#include <TDirectory.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <math.h> 
#include <map>
#include "TH1.h"
#include "TH2.h"
#include <string>
#include <TFile.h>
#include <iostream>



#include <TMultiGraph.h>
#include <TGraphErrors.h>

#include <cmath> 

struct effandbsurv

{
    double eff;
    double bsurv;
};




//This will hopefully grab the data and make a combined graph of the electron to other junk

void combinhistogram()
{//Carful here, this is copied from another type of code, make sure it is pruined properly

    //since the electron and non electron is in a differnt c directory this is needed to grab the data


    std::string type = ".pdf";
    std::string plotname;
    TFile* theFile = new TFile("digis.root");
    if(!theFile)
    {
        cout << "well it isn't reading the file bro" << endl;
        return;
    }
    std::string ele = "demo/pass/avgAdc";
    std::string background = "demo/nepass/avgAdc";

    TH1F* eAdc;
    TH1F* neAdc;

    //sprintf(hfName,"%d%d%d_%d%d%d" ,parameter1[1],parameter2[1],parameter3[1],nparameter1[1],nparameter2[1],nparameter3[1]);
    eAdc = (TH1F*) theFile->Get(ele.c_str());
    neAdc = (TH1F*) theFile->Get(background.c_str());



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
    plotname = "Electron_vrs_nonelectronadc" + type;
    c1->Print(plotname.c_str());
    delete c1;








    //This does the digital data  

    ele = "demo/pass/avgDigi";
    background = "demo/nepass/avgDigi";

    TH1F* eDigi;
    TH1F* neDigi;


    eDigi = (TH1F*) theFile->Get(ele.c_str());
    neDigi = (TH1F*) theFile->Get(background.c_str());



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
    plotname = "Electron_vrs_nonelectronDigi" + type;
    c2->Print(plotname.c_str());
    delete c2;



    //and finally we have the linear adc

    ele = "demo/pass/avglinAdc";
    background = "demo/nepass/avglinAdc";

    TH1F* elinAdc;
    TH1F* nelinAdc;

    //sprintf(hfName,"%d%d%d_%d%d%d" ,parameter1[1],parameter2[1],parameter3[1],nparameter1[1],nparameter2[1],nparameter3[1]);
    elinAdc = (TH1F*) theFile->Get(ele.c_str());
    nelinAdc = (TH1F*) theFile->Get(background.c_str());



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
    plotname = ("Electron_vrs_nonelectronlinadc" + type);
    c3->Print(plotname.c_str());
    delete c3;


    TCanvas* c4 = new TCanvas("c4", "", 800, 700);
    c4->SetFillColor(10);
    c4->SetFillColor(10);
    c4->cd();

    ele = "demo/pass/linladc_to_gen";

    TH2F * Plladcvrgen;
    //TH2D * noelavrgen;

    Plladcvrgen = (TH2F*) theFile->Get(ele.c_str());

    //gStyle->SetPalette(1);
    cout << "get here? 0" << endl;
    Plladcvrgen->Draw("COLZ");

    cout << "get here? 1" << endl;
    c4->Update();
    plotname = "Electron_linearadc_to_gen" + type;
    c4->Print(plotname.c_str());
    delete c4;


    TCanvas* c5 = new TCanvas("c5", "", 800, 700);
    c5->SetFillColor(10);
    c5->SetFillColor(10);
    c5->cd();

    background = "demo/nepass/linladc_to_gen";

    TH2F * Pnelladcvrgen;
    //TH2D * noelavrgen;

    Pnelladcvrgen = (TH2F*) theFile->Get(background.c_str());

    //gStyle->SetPalette(1);

    Pnelladcvrgen->Draw("COLZ");


    c5->Update();
    plotname = "nonElectron_linadc_to_gen" + type;
    c5->Print(plotname.c_str());
    delete c5;


    TCanvas* c6 = new TCanvas("c6", "", 800, 700);
    c6->SetFillColor(10);
    c6->SetFillColor(10);
    c6->cd();

    ele = "demo/pass/short_fiber_vrs_long_adc";
    //backround = "demo/nepass/linadc_to_gen";
    TH2F * Eshvl;
    //TH2D * noelavrgen;

    Eshvl = (TH2F*) theFile->Get(ele.c_str());
    double sigsrv = Eshvl->Integral(); //////////////////////////////////////////////////////////////////////////////delete these //
    //gStyle->SetPalette(1);

    Eshvl->Draw("COLZ");


    c6->Update();
    plotname = "e_short_fiber_vrs_long_adc" + type;
    c6->Print(plotname.c_str());
    delete c6;


    TCanvas* c7 = new TCanvas("c7", "", 800, 700);
    c7->SetFillColor(10);
    c7->SetFillColor(10);
    c7->cd();

    background = "demo/nepass/short_fiber_vrs_long_adc";
    //backround = "demo/nepass/linadc_to_gen";
    TH2F * nEshvl;
    //TH2D * noelavrgen;

    nEshvl = (TH2F*) theFile->Get(background.c_str());
    double bgsrv = nEshvl->Integral();
    //gStyle->SetPalette(1);

    nEshvl->Draw("COLZ");

    c7->Update();
    plotname = "nteshort_fiber_vrs_long_adc" + type;
    c7->Print(plotname.c_str());
    delete c7;


    TCanvas* c8 = new TCanvas("c8", "", 800, 700);
    c8->SetFillColor(10);
    c8->SetFillColor(10);


    TCanvas* c9 = new TCanvas("c9", "", 800, 700);
    c9->SetFillColor(10);
    c9->SetFillColor(10);
    double slope = 0;
    double yax = 0;

    double bsm = bgsrv;
    double ssm = sigsrv;
    double Mss = sigsrv;
    double Msm = bgsrv;

    ele = "demo/pass/short_fiber_vrs_long_adc";
    //backround = "demo/nepass/linadc_to_gen";
    TH2F * DEshvl;
    //TH2D * noelavrgen;

    DEshvl = (TH2F*) theFile->Get(ele.c_str());


    //gStyle->SetPalette(1);
    background = "demo/nepass/short_fiber_vrs_long_adc";
    //backround = "demo/nepass/linadc_to_gen";
    TH2F * DnEshvl;
    //TH2D * noelavrgen;

    DnEshvl = (TH2F*) theFile->Get(background.c_str());


    for(int k = 80; k < 150; k++)
    {
        for(int p = 80; p < 150; p++)
        {


            // double slop=.045*k;
            //double b=3*p; 
            TF1 f1("myfunc", "(x*[0])-[1]", 0, 140);
            f1.SetParameter(0, .045 * double(k));
            f1.SetParameter(1, 3 * double(p));

            int cut[140][140]; //so if this vaulue is one it means we cut it out first long, second short
            for(int i = 0; i < 140; i++)
            {
                for(int j = 0; j < 140; j++)
                {
                    cut[i][j] = 0;
                }
            }
            //so now all terms will be zero so to do cuts we do cuts, yes it isn't the most effiecient way, just doing it this way for clearity for now.
            for(int i = 0; i < 140; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    cut[i][j] = 1;
                    cut[j][i] = 1;

                }
            }

            for(int i = 0; i < 140; i++)
            {
                //cout<<"hey dumbass this sould be a number that is bigger "<<f1((double)i)<<endl;
                for(int j = 0; j < 140; j++)
                {
                    if(j > f1((double) i)) cut[i][j] = 1;

                }
            }

            TH2F *CEshvl = (TH2F*) DEshvl->Clone("CEshvl2");
            TH2F *CnEshvl = (TH2F*) DnEshvl->Clone("CnEshvl2");



            for(int i = 0; i < 140; i++)
            {
                for(int j = 0; j < 140; j++)
                {

                    if(cut[i][j] == 1)CnEshvl->SetBinContent(i, j, 0);
                    if(cut[i][j] == 1)CEshvl->SetBinContent(i, j, 0);
                }
            }

            Msm = CnEshvl->Integral();
            Mss = CEshvl->Integral();

            //cout << "Mss/(Msm+1): " << Mss/(Msm+1) << endl;

            if(((Mss / (Msm + 1)) > (ssm / (bsm + 1)))&&(Mss / sigsrv) > .9)
            {
                cout << "hey we get in here? " << endl << endl << endl;
                ssm = Mss;
                bsm = Msm;
                slope = (double) k * .045;
                yax = 3 * p;

            }
            delete CnEshvl;
            delete CEshvl;
        }
    }

    TF1 f1("f1", "(x*[0])-[1]", -1, 140); //final function
    f1.SetParameter(0, slope);
    f1.SetParameter(1, yax);
    int cut[140][140]; //so if this vaulue is one it means we cut it out first long, second short
    for(int i = 0; i < 140; i++)
    {
        for(int j = 0; j < 140; j++)
        {
            cut[i][j] = 0;
        }
    }
    //so now all terms will be zero so to do cuts we do cuts, yes it isn't the most effiecient way, just doing it this way for clearity for now.
    for(int i = 0; i < 140; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            cut[i][j] = 1;
            cut[j][i] = 1;

        }
    }
    cout << "crashing here I assume" << endl;
    cout << "this should be 300   " << f1(0.0) << endl << endl;
    for(int i = 0; i < 140; i++)
    {
        for(int j = 0; j < 140; j++)
        {
            if(j > f1((double) i))cut[i][j] = 1;

        }
    }



    ele = "demo/pass/short_fiber_vrs_long_adc";
    //backround = "demo/nepass/linadc_to_gen";
    TH2F * CEshvl;
    //TH2D * noelavrgen;

    CEshvl = (TH2F*) theFile->Get(ele.c_str());

    background = "demo/nepass/short_fiber_vrs_long_adc";
    TH2F * CnEshvl;
    CnEshvl = (TH2F*) theFile->Get(background.c_str());

    //gStyle->SetPalette(1);
    for(int i = 0; i < 140; i++)
    {
        for(int j = 0; j < 140; j++)
        {

            if(cut[i][j] == 1)CnEshvl->SetBinContent(i, j, 0);
            if(cut[i][j] == 1)CEshvl->SetBinContent(i, j, 0);
        }
    }
    c8->cd();
    CEshvl->Draw("COLZ");


    c8->Update();
    plotname = "cut_eshort_fiber_vrs_long_adc" + type;
    c8->Print(plotname.c_str());
    delete c8;
    c9->cd();
    CnEshvl->Draw("COLZ");


    c9->Update();
    plotname = "cutne_eshort_fiber_vrs_long_adc" + type;
    c9->Print(plotname.c_str());
    delete c9;
    cout << "so our final slope is " << slope << " and our final y intercept is -" << yax << endl;
    cout << "dude why you not get here?" << endl;




}

effandbsurv NOTSUREABOUTmacro(double slope, double yintercept, TH1D* want, TH1D* dontwant)
{

    TF1 f1("myfunc", "(x*[0])-[1]", 0, 140);
    f1.SetParameter(0, slope;
            f1.SetParameter(1, yintercept;

            int cut[140][140]; //so if this vaulue is one it means we cut it out first long, second short
    for(int i = 0; i < 140; i++)
    {
        for(int j = 0; j < 140; j++)
        {
            cut[i][j] = 0;
        }
    }
    //so now all terms will be zero so to do cuts we do cuts, yes it isn't the most effiecient way, just doing it this way for clearity for now.
    for(int i = 0; i < 140; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            cut[i][j] = 1;
                    cut[j][i] = 1;

        }
    }


    for(int i = 0; i < 140; i++)
    {
        for(int j = 0; j < 140; j++)
        {
            if(j > f1((double) i))cut[i][j] = 1;

            }
    }


    for(int i = 0; i < 140; i++)
    {
        for(int j = 0; j < 140; j++)
        {

            if(cut[i][j] == 1)dontwant->SetBinContent(i, j, 0);
                if(cut[i][j] == 1)want->SetBinContent(i, j, 0);
                }
    }

    effandbsurv

}