#include "Events.h"
#include "RZ.h"
#include "PlotPhoton.h"
#include "PhotonCom.h"

void SetStyle()
{
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetCanvasDefH(600);
    gStyle->SetCanvasDefW(600);
    gStyle->SetLabelSize(0.03, "xyz");
    gStyle->SetTitleSize(0.04, "xyz");
    gStyle->SetTitleOffset(1.5, "yz");
    gStyle->SetTitleOffset(1.5, "x");

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
    AnaForRZ(config);
}

