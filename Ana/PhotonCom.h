#pragma once
#include "Basics.h"
#include "crystalball.h"
#include "BeamEnergySmear.h"

struct Result {
    TGraph* gr_width_w;
    TGraph* gr_width_wo;
    TGraph* gr_massErr_w;
    TGraph* gr_massErr_wo;
    TGraph* gr_peakh_w;
    TGraph* gr_peakh_wo;
};


void PhotonCom(
    Config const &config,
    char const* rootname, char const* output, TrackRes trkRes, double bkg, double nExp, Result &res)
{

    double rc_nevts = 0;
    double tr_nevts = 0;

    Events evts(rootname);

    int Nbins = 100;
    int const NBMR = 20;
    double delta_a = 0.02;

    double const Ecms = evts.Ecms;
    V4 whole(0,0,0,Ecms);

    TH1D* hist_recoil_mass_full = new TH1D("hist_recoil_mass_full", "", Nbins, 120, 140);
    TH1D* hist_recoil_mass_fast = new TH1D("hist_recoil_mass_fast", "", Nbins, 120, 140);
    TH1D* hist_recoil_mass_comp[NBMR];
    double as[NBMR];

    for (int i = 0; i < NBMR; ++i) {
        hist_recoil_mass_comp[i] = new TH1D("", "", Nbins, 120, 140);
    }

    for(int i = 0; i < NBMR; ++i) {
        as[i] = delta_a*i;
    }

    for (; evts.hasEvent(); evts.next())
    {
        Event &evt = evts.getEvt();
        Rand rnd;        

        for(int i = 0; i < NBMR; ++i)
        {
            double const a  = as[i];
            PhotonRes phoRes;
            phoRes.a = a;
            evt.smear(phoRes, trkRes, rnd);
            V4 e1 = evt.e1_ + evt.fsr1_ + evt.bs1_;
            V4 e2 = evt.e2_ + evt.fsr2_ + evt.bs2_;
            if (Select(evt.rc_e1, evt.rc_e2, Ecms)) { // don't change the eff.
                V4 dilep = e1 + e2;
                dilep = SmearEnergySpread(dilep, Ecms, rnd);
                hist_recoil_mass_comp[i]->Fill((whole-dilep).M());
            }
        }

        if (1) {
            V4 e1 = evt.e1_;
            V4 e2 = evt.e2_; // fast simulation
            if (Select(evt.rc_e1, evt.rc_e2, Ecms)) {
                V4 dilep = e1 + e2;
                dilep = SmearEnergySpread(dilep, Ecms, rnd);
                hist_recoil_mass_fast->Fill((whole-dilep).M());
                tr_nevts += 1;
            }
        }

        if (evts.RCAvaliable) {
            V4 e1 = evt.rc_e1; // full simulation
            V4 e2 = evt.rc_e2;
            if (Select(e1, e2, Ecms)) {
                V4 dilep = e1 + e2;
                dilep = SmearEnergySpread(dilep, Ecms, rnd);
                hist_recoil_mass_full->Fill((whole-dilep).M());
                rc_nevts += 1;
            }
        }
    }


    printf("rc eff. %f\n", rc_nevts / evts.nevts);
    printf("tr eff. %f\n", tr_nevts / evts.nevts);

    double scale_for_lumi = nExp / evts.nevts;

    std::vector<TH1D*> hists;
    hists.push_back(hist_recoil_mass_full);
    hists.push_back(hist_recoil_mass_fast);
    hists.insert(hists.end(), hist_recoil_mass_comp, hist_recoil_mass_comp + NBMR);


    for(size_t i = 0; i < hists.size(); ++i) {
        hists[i]->Scale(scale_for_lumi);
        for(int b = 0; b <= hists[i]->GetNbinsX(); ++b) {
            double nb = bkg * hists[i]->GetBinWidth(b);
            hists[i]->AddBinContent(b, nb);
        }
        hists[i]->Sumw2(false);
    }

    // compare fast and full
    {
        TCanvas cvs;
        hist_recoil_mass_fast->GetXaxis()->SetTitle("Recoil mass [GeV]");
        hist_recoil_mass_fast->GetYaxis()->SetTitle("Events / 0.2GeV");
        hist_recoil_mass_fast->GetYaxis()->CenterTitle();
        hist_recoil_mass_fast->GetXaxis()->CenterTitle();
        hist_recoil_mass_fast->SetMinimum(0);

        hist_recoil_mass_full->SetLineColor(kRed);
        hist_recoil_mass_fast->SetLineColor(kBlue);

        hist_recoil_mass_fast->Draw("hist");
        hist_recoil_mass_full->Draw("same");
        TLegend* leg = new TLegend(0.5, 0.7, 0.9, 0.9);
        leg->SetBorderSize(0);
        leg->AddEntry(hist_recoil_mass_full, "full simulation", "l");
        leg->AddEntry(hist_recoil_mass_fast, "fast simulation", "l");
        leg->Draw();

        cvs.Print((config.imageFolder + "/" + output + "_fast_full.pdf").c_str());
    }


    {
        TGraph& sigma = *(new TGraph());
        TGraph& sigma2 = *(new TGraph());
        TGraph& massErr = *(new TGraph());
        TGraph& massErr2 = *(new TGraph());
        TGraph& high = *(new TGraph());
        TGraph& high2 = *(new TGraph());

        res.gr_massErr_w = &massErr;
        res.gr_massErr_wo = &massErr2;
        res.gr_width_w = &sigma;
        res.gr_width_wo = &sigma2;
        res.gr_peakh_w = &high;
        res.gr_peakh_wo = &high2;




        if (1) {
            printf("full simulation\n");
            std::string filename = config.imageFolder + "/"  + std::string(output) + "_full_simulation.pdf";
            FitConfig conf;
            conf.draw = true;
            conf.filename = filename.c_str();
            conf.xtitle = "Recoil mass [GeV]";
            FitResult fitResult = Fit(hist_recoil_mass_full, bkg, conf);
            fitResult.printInfo();
        }

        if (1) {
            printf("fast simulation\n");
            std::string filename = config.imageFolder + "/"  + std::string(output) + "_fast_simulation.pdf";
            FitConfig conf;
            conf.draw = true;
            conf.filename = filename.c_str();
            conf.xtitle = "Recoil mass [GeV]";

            FitResult fitResult = Fit(hist_recoil_mass_fast, bkg, conf);
            fitResult.printInfo();

            sigma2.SetPoint(0, 0, fitResult.width);
            sigma2.SetPoint(1, (NBMR - 1) * delta_a, fitResult.width);
            massErr2.SetPoint(0, 0, 1000 * fitResult.mass_error);
            massErr2.SetPoint(1, (NBMR - 1) * delta_a, 1000 * fitResult.mass_error);
            high2.SetPoint(0, 0, fitResult.Ns);
            high2.SetPoint(1, (NBMR - 1) * delta_a, fitResult.Ns);
        }

        for (int i = 0; i < NBMR; ++i) {
            char av[100];
            sprintf(av, "a%f", as[i]);
            std::string filename = config.imageFolder2 + "/" + std::string(output) + "_fast_simulation_" + av + ".pdf";
            FitConfig conf;
            conf.draw = near(as[i], 0) || near(as[i], 0.04) || near(as[i], 0.16) || near(as[i], 0.36);
            conf.filename = filename.c_str();
            conf.xtitle = "Recoil mass [GeV]";
            FitResult fitResult = Fit(hist_recoil_mass_comp[i], bkg, conf);
            sigma.SetPoint(i, delta_a * i, fitResult.width);
            massErr.SetPoint(i, delta_a * i, 1000 * fitResult.mass_error);
            high.SetPoint(i, delta_a* i, fitResult.Ns);
        }
        char const *hist_title = "a [#sqrt{GeV}]";
        { // Peak width
            TCanvas cvs;
            sigma.GetXaxis()->CenterTitle();
            sigma.GetXaxis()->SetTitle(hist_title); 
            sigma.GetYaxis()->SetTitle("Peak width [GeV]");
            sigma.GetYaxis()->CenterTitle();
            sigma2.SetLineColor(kGray);

            sigma.Draw("AL");
            sigma2.Draw("SAME L");
            cvs.Print((config.imageFolder2 + "/" + output + "_wdith.pdf(").c_str());
        }

        { // Peak high
            TCanvas cvs;
            high.GetXaxis()->CenterTitle();
            high.GetXaxis()->SetTitle(hist_title);
            high.GetYaxis()->CenterTitle();
            high.GetYaxis()->SetTitle("Peak high [Events/(0.2GeV)]");
            high2.SetLineColor(kGray);

            high.Draw("AL");
            high2.Draw("SAME L");
            cvs.Print((config.imageFolder2 + "/" + output + "_high.pdf(").c_str());
        }


        { // Higgs mass error vs. a
            TCanvas cvs;
            massErr.GetXaxis()->CenterTitle();
            massErr.GetXaxis()->SetTitle(hist_title);
            massErr.GetYaxis()->CenterTitle();
            massErr.GetYaxis()->SetTitle("Uncertainty of higgs mass [MeV]");
            massErr2.SetLineColor(kGray);

            massErr.Draw("AL");
            massErr2.Draw("SAME L");
            gPad->SetLeftMargin(2);
            cvs.Print((config.imageFolder2 + "/" + output + "_masserr.pdf").c_str());
        }
    }

}


void DrawFroPhotonCom(Result res1, Result res2)
{
    TGraph* ew1 = res1.gr_width_w;
    TGraph* ew2 = res1.gr_width_wo;
    TGraph* eh1 = res1.gr_peakh_w;
    TGraph* eh2 = res1.gr_peakh_wo;
    TGraph* em1 = res1.gr_massErr_w;
    TGraph* em2 = res1.gr_massErr_wo;
    
    TGraph* mw1 = res2.gr_width_w;
    TGraph* mw2 = res2.gr_width_wo;
    TGraph* mh1 = res2.gr_peakh_w;
    TGraph* mh2 = res2.gr_peakh_wo;
    TGraph* mm1 = res2.gr_massErr_w;
    TGraph* mm2 = res2.gr_massErr_wo;

    // peak_with
    if (ew1 && ew2 && mw1 && mw2) {
        TCanvas cvs;

        ew1->SetLineColor(kRed);
        ew1->SetLineWidth(2);
        mw1->SetLineColor(kGreen);
        mw1->SetLineWidth(2);

        ew2->SetLineColor(kRed);
        ew2->SetLineWidth(2);
        ew2->SetLineStyle(2);

        mw2->SetLineColor(kGreen);
        mw2->SetLineWidth(2);
        mw2->SetLineStyle(2);

        ew1->SetMaximum(1.4);
        ew1->SetMinimum(0);

        ew1->Draw("AL");
        mw1->Draw("SAME L");
        ew2->Draw("SAME L");
        mw2->Draw("SAME L");

        ew1->SetName("ew1");
        mw1->SetName("mw1");
        ew2->SetName("ew2");
        mw2->SetName("mw2");

        TLegend leg(0.52, 0.70, 0.92, 0.9);
        leg.AddEntry(ew1, "eeH (w/ FSR&BS)", "L");
        leg.AddEntry(mw1, "#mu#muH (w/ FSR&BS)", "L");
        leg.AddEntry(ew2, "eeH (w/o FSR&BS)", "L");
        leg.AddEntry(mw2, "#mu#muH (w/o FSR&BS)", "L");
        leg.SetBorderSize(0);
        leg.Draw();
        cvs.Print( (config.imageFolder + "/" + "result_peak_width.pdf").c_str() );
    }


    // peak_high
    if (eh1 && eh2 && mh1 && mh2) {
        TCanvas cvs;

        eh1->SetLineColor(kRed);
        eh1->SetLineWidth(2);
        mh1->SetLineColor(kGreen);
        mh1->SetLineWidth(2);

        eh2->SetLineColor(kRed);
        eh2->SetLineWidth(2);
        eh2->SetLineStyle(2);

        mh2->SetLineColor(kGreen);
        mh2->SetLineWidth(2);
        mh2->SetLineStyle(2);

        eh1->SetMaximum(8E3);
        eh1->SetMinimum(0);

        eh1->Draw("AL");
        mh1->Draw("SAME L");
        eh2->Draw("SAME L");
        mh2->Draw("SAME L");

        eh1->SetName("eh1");
        mh1->SetName("mh1");
        eh2->SetName("eh2");
        mh2->SetName("mh2");

        TLegend leg(0.52, 0.70, 0.92, 0.9);
        leg.AddEntry(eh1, "eeH (w/ FSR&BS)", "L");
        leg.AddEntry(mh1, "#mu#muH (w/ FSR&BS)", "L");
        leg.AddEntry(eh2, "eeH (w/o FSR&BS)", "L");
        leg.AddEntry(mh2, "#mu#muH (w/o FSR&BS)", "L");
        leg.SetBorderSize(0);
        leg.Draw();
        cvs.Print( (config.imageFolder + "/" + "result_peak_high.pdf").c_str() );
    }


    // mass_error
    if (em1 && mm1 && em2 && mm2) {
        TCanvas cvs;

        TGraph com;
        for (int i = 0; i < em1->GetN(); ++i) {
            double x, y1, y2;
            em1->GetPoint(i, x, y1);
            mm1->GetPoint(i, x, y2);
            com.SetPoint(i, x, 1. / sqrt(1 / (y1 * y1) + 1 / (y2 * y2)));
        }

        em1->SetLineColor(kRed);
        em1->SetLineWidth(2);
        mm1->SetLineColor(kGreen);
        mm1->SetLineWidth(2);

        com.SetLineWidth(2);
        com.SetLineColor(kBlue);

        em2->SetLineColor(kRed);
        em2->SetLineWidth(2);
        em2->SetLineStyle(2);
        mm2->SetLineColor(kGreen);
        mm2->SetLineWidth(2);
        mm2->SetLineStyle(2);

        em1->SetMaximum(40);
        em1->SetMinimum(0);
        em1->Draw("AL");
        mm1->Draw("SAME L");
        em2->Draw("SAME L");
        mm2->Draw("SAME L");
        com.Draw("SAME L");

        em1->SetName("em1");
        mm1->SetName("mm1");
        em2->SetName("em2");
        mm2->SetName("mm2");
        com.SetName("com");

        TLegend leg(0.52, 0.70, 0.92, 0.92);
        leg.AddEntry(em1, "eeH (w/ FSR&BS)", "L");
        leg.AddEntry(mm1, "#mu#muH (w/ FSR&BS)", "L");
        leg.AddEntry(em2, "eeH (w/o FSR&BS)", "L");
        leg.AddEntry(mm2, "#mu#muH (w/o FSR&BS)", "L");
        leg.AddEntry(&com, "Combined (w/ FSR&BS)", "L");
        leg.SetBorderSize(0);
        leg.Draw();
        cvs.Print( (config.imageFolder + "/" + "result_mass_error.pdf").c_str() );
    }
}

