#include "Events.h"
#include "RZ.h"
#include "PlotPhoton.h"
#include "PlotPolarAngle.h"
#include "PhotonCom.h"

void SetStyle()
{
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetCanvasDefH(500);
    gStyle->SetCanvasDefW(500);
    gStyle->SetLabelSize(0.045, "xyz");
    gStyle->SetTitleSize(0.045, "xyz");
    gStyle->SetTitleOffset(1.55, "yz");
    gStyle->SetTitleOffset(1.1, "x");
    gStyle->SetHistLineWidth(3);
    gStyle->SetLineWidth(2);

    gStyle->SetEndErrorSize(3);
    gStyle->SetErrorX(0.1);
    gStyle->SetMarkerSize(0.8);

    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadTopMargin(0.05);
    gStyle->SetPadRightMargin(0.05);
    gStyle->SetPadLeftMargin(0.15);
}

void AnaPhoton(Config const & config)
{
    PlotPhoton(config, config.eeHRootFileName, "eeH");
    PlotPhoton(config, config.mumuHRootFileName, "mumuH");
}

void AnaForPhotonResolution(Config const &config) 
{
    TrackRes trkRes;
    TrackRes trackResMuon;
    Result res1;
    Result res2;

    PhotonCom(config, config.eeHRootFileName, "eeH", trkRes, config.eeHBkg, config.eeHExp, res1);
    PhotonCom(config, config.mumuHRootFileName, "mumuH", trkRes, config.mumuHBkg, config.mumuHExp, res2);

    DrawFroPhotonCom(res1, res2);

}


void AnaForRZ(Config const &config)
{    
    {
        CalcRZ calcRz(TrackerR0, TrackerZ0, COS_VOL);
        AnaForRZ2(config,
        config.mumuHRootFileName,
            config.mumuHExp,
            config.mumuHBkg,
            "fixvol",
            calcRz);
    }
    {
        CalcRZ calcRz(TrackerR0, TrackerZ0, COS_SURF);
        AnaForRZ2(config,
            config.mumuHRootFileName,
            config.mumuHExp,
            config.mumuHBkg,
            "fixsurf",
            calcRz);
    }
}

void Main()
{
    SetStyle();
    gRandom->SetSeed(234729479);
    gROOT->SetBatch(true);

    AnaPhoton(config);
    AnaForPhotonResolution(config);
    DrawLepton(config, config.mumuHRootFileName, "mumu");
    AnaForRZ(config);
}

