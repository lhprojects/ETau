#pragma once
#include <TCanvas.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TTree.h>
#include <cmath>
#include <TROOT.h>


inline double Sqr(double x) { return x*x; }
using V4 = TLorentzVector;



struct Rand
{
    double rnd[8];

    double r1;
    double r2;

    Rand() { set(); }

    void set()
    {

        for (int i = 0; i < 8; ++i) {
            rnd[i] = gRandom->Gaus();
        }

        r1 = gRandom->Gaus();
        r2 = gRandom->Gaus();
    }
};


struct Config {

    Config() {
        eeHExp = 7.04 * 5600;
        mumuHExp =  6.77 * 5600;
        eeHBkg = 3500 / 0.8;
        mumuHBkg = 3200 / 0.8;
        imageFolder = "../img";
        imageFolder2 = "../img2";
        eeHRootFileName = "../root/eeHa.root";
        mumuHRootFileName = "../root/mumuHa.root";
    }

    double eeHExp;
    double mumuHExp;
    double eeHBkg;
    double mumuHBkg;

    char const *eeHRootFileName;
    char const *mumuHRootFileName;
    std::string imageFolder;
    std::string imageFolder2;
};

Config const config;

