#pragma once
#include "Basics.h"
#include "crystalball.h"

bool const FULL_SIMULATION = 1;
bool const SMEAR_SQRTS = 1;
bool GAUS_FIT = 0;
bool const SHIFT = 0;

struct FitResult {
    double width;
    double mass;
    double width_error;
    double mass_error;
    double Ns;

    void printInfo()
    {
        FitResult& fitResult = *this;
        printf("\twidth uncertainty: %f\n", fitResult.width_error);
        printf("\tmass uncertainty %f\n", fitResult.mass_error);
        printf("\twidth %f\n", fitResult.width);
        printf("\t mass %f\n", fitResult.mass);
        printf("\tNs %f\n", fitResult.Ns);
    }
};

struct FitConfig
{
    FitConfig() {
        draw=false;
        printInfo=false;
        xtitle="";
        filename="";
    }

    bool draw;
    bool printInfo;
    char const* xtitle;
    char const* filename;
};

FitResult Fit(TH1D* h, double bkg_hint_NevtsInGeV, FitConfig const &config)
{
    TF1* ff;
    if (GAUS_FIT) {
        ff = new TF1("", "gaus(0) + [3]", 120, 126);
        ff->SetParNames("C", "Mean", "Sigma", "Bkg");
        ff->SetParameters(1000, 125, 0.4, bkg_hint_NevtsInGeV * 20 / h->GetNbinsX());
        if (bkg_hint_NevtsInGeV == 0)
            ff->FixParameter(3, 0);
    } else {
        ff = new_crystalball_bkg_function("", 120, 140);
        ff->SetParameters(1000, 125.5, 0.4, -0.5, 0.7, bkg_hint_NevtsInGeV * 20 / h->GetNbinsX());
        if (bkg_hint_NevtsInGeV == 0)
            ff->FixParameter(5, 0);
    }

    ff->SetNpx(1000);
    if(config.printInfo) {
        h->Fit(ff, "R");
    } else {
        h->Fit(ff, "R q");
    }

    if (SHIFT) {
        ff->FixParameter(0, ff->GetParameter(0));
        ff->FixParameter(2, ff->GetParameter(2));
        ff->FixParameter(3, ff->GetParameter(3));
        if (!GAUS_FIT) {
            ff->FixParameter(4, ff->GetParameter(4));
            ff->FixParameter(5, ff->GetParameter(5));
        }
    }
    h->Fit(ff, "R Q");

    FitResult fitResult;

    fitResult.width = ff->GetParameter(2);
    fitResult.width_error = ff->GetParError(2);
    fitResult.mass = ff->GetParameter(1);
    fitResult.mass_error = ff->GetParError(1);
    //fitResult.Ns = ff->GetParameter(0) * fitResult.width * sqrt(2 * 3.1415);
    fitResult.Ns = ff->GetParameter(0);

    if (config.draw) {

   
        TCanvas cvs;
        h->GetYaxis()->SetTitle("Events / 0.2GeV");
        h->GetYaxis()->CenterTitle();
        h->GetXaxis()->SetTitle(config.xtitle);
        h->GetXaxis()->CenterTitle();
        h->SetMinimum(0);
        h->SetMarkerColor(kBlack);
        h->SetMarkerStyle(kFullCircle);
        h->SetLineColor(kBlack);
        h->Draw("PE1");

        ff->SetLineColor(kBlue);
        ff->SetLineWidth(2);
        ff->Draw("SAME");

        TF1* signal_alone = 0;
        if (GAUS_FIT) {
            signal_alone = new TF1("", "gaus(0)", 120, 126);
        } else {
            signal_alone = new TF1("", crystalball_bkg_function, 120, 140, 5);
        }
        signal_alone->SetParameters(ff->GetParameters());
        signal_alone->SetNpx(1000);
        signal_alone->Draw("SAME");

        if(config.filename && strlen(config.filename) > 0) {
            cvs.Print(config.filename);
        }
        delete signal_alone;
    }
    delete ff;
    return fitResult;
}

