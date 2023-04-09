#pragma once
#include "Basics.h"
#include "TrackRes.h"
#include "Select.h"
#include "Fit.h"
#include "BeamEnergySmear.h"

enum Costimator {
    COS_VOL,
    COS_SURF,
};

struct CalcRZ
{
    CalcRZ(double R0, double Z0, Costimator calcRZ) :
     R0(R0), Z0(Z0), calcRZ(calcRZ) {
    }

    double const R0;
    double const Z0;
    Costimator calcRZ;

    double calZFromR(double R) const
    {
        double Z = 0;
        switch (calcRZ)
        {
        case COS_VOL:
        {
            double V0 = Sqr(R0) * Z0;
            Z = V0 / Sqr(R);
            break;
        }
        case COS_SURF:
        {
            double S0 = 2. * R0 * (R0 + Z0);
            Z = S0 / (2 * R) - R;
            break;
        }
        default:
            throw "don't know how to calc the Z from R";
        }
        return Z;
    }
};


inline void fmtBaseline(TGraph &g) {
    g.SetMarkerColor(kRed);
    g.SetMarkerStyle(kFullStar);
    g.SetMarkerSize(2);
}

inline void fmtCurve(TGraph &g) {
    g.GetXaxis()->CenterTitle();
    g.GetYaxis()->CenterTitle();
    g.SetLineColor(kBlack);
    g.SetLineWidth(3);
}

void AnaForRZ2(
Config const &config,
char const *filename,
double nExp,
double bkg,
std::string output,
CalcRZ calcRZ)
{
    int const Nbins = 100;
    int const NRZ = 31;
    Events evts(filename);

    double const Ecms = evts.Ecms;
    V4 whole(0,0,0, Ecms);

    TH1D* hist_recoil_mass_full;
    TH1D* hist_recoil_mass_fast[NRZ];
    double Rs[NRZ];
    double Zs[NRZ];


    hist_recoil_mass_full = new TH1D("", "", Nbins, 120, 140);
    for (int i = 0; i < NRZ; ++i) {
        hist_recoil_mass_fast[i] = new TH1D("", "", Nbins, 120, 140);
    }

    double const R1 = 1;
    double const R2 = 2.5;
    for(int i = 0; i < NRZ; ++i) {
        double R = R1 + (R2 - R1) * i / (NRZ - 1);
        double Z = calcRZ.calZFromR(R);
        Rs[i] = R;
        Zs[i] = Z;
        //printf("%f %f\n", R, Z);
    }

    Rand rnd;        
    int NsampleEnergy = 1; // We want to obtain stable result
                             // We indeed need to do many times fit, instead of averaging the hist.
                             // so here is only an adhoc


    for (; evts.hasEvent(); evts.next())
    {
        Event &evt = evts.getEvt();
        for (int i = 0; i < NsampleEnergy; ++i)
        {
            rnd.set();

            for (int i = 0; i < NRZ; ++i)
            {
                double const R = Rs[i];
                double const Z = Zs[i];
                // printf("%f %f\n", R, Z);
                TrackRes trkRes(R, Z);

                evt.smearTracks(trkRes, rnd);
                V4 e1 = evt.e1_;
                V4 e2 = evt.e2_;
                if (Select(evt.rc_e1, evt.rc_e2, Ecms))
                { // don't change the eff.
                    V4 dilep = e1 + e2;
                    dilep = SmearEnergySpread(dilep, Ecms, rnd);
                    hist_recoil_mass_fast[i]->Fill((whole - dilep).M());
                }
            }

            if (1)
            {

                if (Select(evt.rc_e1, evt.rc_e2, Ecms))
                { // don't change the eff.
                    V4 dileprdc = evt.rc_e1 + evt.rc_e2;
                    dileprdc = SmearEnergySpread(dileprdc, Ecms, rnd);
                    hist_recoil_mass_full->Fill((whole - dileprdc).M());
                }
            }
        }
    }

    double scale_for_lumi = nExp / evts.nevts;

    std::vector<TH1D*> hists;
    hists.push_back(hist_recoil_mass_full);
    hists.insert(hists.end(), hist_recoil_mass_fast, hist_recoil_mass_fast + NRZ);


    for(size_t i = 0; i < hists.size(); ++i) {
        hists[i]->Scale(scale_for_lumi);
        hists[i]->Scale(1./NsampleEnergy);
        for(int b = 0; b <= hists[i]->GetNbinsX(); ++b) {
            double nb = bkg * hists[i]->GetBinWidth(b);
            hists[i]->AddBinContent(b, nb);
        }
        hists[i]->Sumw2(false);
    }

    {
        
        TGraph& sigma = *(new TGraph());
        TGraph& sigma2 = *(new TGraph());
        TGraph& massErr = *(new TGraph());
        TGraph& massErr2 = *(new TGraph());
        TGraph& high = *(new TGraph());
        TGraph& high2 = *(new TGraph());

        if (1) {
            printf("full simulation\n");
            std::string filename = config.imageFolder + "/" + output + "_full_simulation.pdf";
            FitConfig conf;
            conf.draw=true;

            conf.filename = filename.c_str();
            conf.xtitle = "Recoil mass [GeV]";
            conf.printInfo = true;
           
            FitResult fitResult = Fit(hist_recoil_mass_full, bkg, conf);
            fitResult.printInfo();

            sigma2.SetPoint(0, TrackerR0 , fitResult.width);
            high2.SetPoint(0, TrackerR0, fitResult.Ns);
            massErr2.SetPoint(0, TrackerR0, 1000 * fitResult.mass_error);
        }

        for (int i = 0; i < NRZ; ++i) {
            char av[100];
            sprintf(av, "R%f", Rs[i]);
            std::string filename = config.imageFolder2 + "/" + output + "_fast_simulation_" + av + ".pdf";
            FitConfig conf;
            conf.draw = near(Rs[i], 1.4) || near(Rs[i], 1.8) || near(Rs[i], 2.2) || near(Rs[i], 2.5);
            conf.filename = filename.c_str();
            conf.xtitle = "Recoil mass [GeV]";

            FitResult fitResult = Fit(hist_recoil_mass_fast[i], bkg, conf);
            //fitResult.printInfo();
            sigma.SetPoint(i, Rs[i], fitResult.width);
            high.SetPoint(i, Rs[i], fitResult.Ns);
            massErr.SetPoint(i, Rs[i], 1000 * fitResult.mass_error);
        }



        char const *hist_title = "R [m]";
        { // Peak width
            TCanvas cvs("","", 400, 400);
            sigma.GetXaxis()->SetTitle(hist_title); 
            sigma.GetYaxis()->SetTitle("Peak width [GeV]");
            fmtCurve(sigma);
            fmtBaseline(sigma2);

            sigma.Draw("AL");
            sigma2.Draw("SAME P");
            cvs.Print((config.imageFolder + "/" + std::string(output) + "_wdith.pdf").c_str());
        }

        { // Peak high
            TCanvas cvs("","", 400, 400);
            high.GetXaxis()->SetTitle(hist_title);
            high.GetYaxis()->SetTitle("Peak high [Events/(0.2GeV)]");
            fmtCurve(high);
            fmtBaseline(high2);

            high.Draw("AL");
            high2.Draw("SAME P");
            cvs.Print((config.imageFolder + "/" + std::string(output) + "_high.pdf").c_str());
        }


        { // Higgs mass error vs. a
            TCanvas cvs("","", 400, 400);
            massErr.GetXaxis()->SetTitle(hist_title);
            massErr.GetYaxis()->SetTitle("Uncertainty of Higgs mass [MeV]");
            fmtCurve(massErr);
            fmtBaseline(massErr2);

            massErr.Draw("AL");
            massErr2.Draw("SAME P");
            //gPad->SetLeftMargin(2);
            cvs.Print((config.imageFolder + "/"  + std::string(output) + "_masserr.pdf").c_str());
        }
    }
}

