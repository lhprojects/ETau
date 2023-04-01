#include "crystalball.h"
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
#include "Events.h"

bool const FULL_SIMULATION = 1;
bool const SMEAR_SQRTS = 1;
bool GAUS_FIT = 0;
bool const SHIFT = 0;
double const sqrts_sigma1 = 1.34E-3;
double const sqrts_sigma2 = 1.34E-3;


V4 SmearEnergySpread(V4 const &v4, double Ecms, Rand const &rnd)
{
    double const en_ = v4.E();
    double const px = v4.Px();
    double const py = v4.Py();
    double const pz_ = v4.Pz();

    double const delta1 = sqrts_sigma1 * rnd.r1;
    double const delta2 = sqrts_sigma2 * rnd.r2;
    double const beta = (delta1 - delta2) / 2;
    double en = en_ + beta * pz_;
    double pz = pz_ + beta * en_;
    en += 0.5 * (delta1 + delta2) * Ecms;

    return V4(px, py, pz, en);
}

bool Select(V4 e1, V4 e2, double Ecms)
{

    double en = (e1 + e2).E();
    double px = (e1 + e2).Px();
    double py = (e1 + e2).Py();
    double pz = (e1 + e2).Pz();
    if (e1[0] == 0)
        return false;
    if (e2[0] == 0)
        return false;
    if (sqrt(px * px + py * py) < 20)
        return false;
    TLorentzVector v4(px, py, pz, en);
    TLorentzVector inc(0, 0, 0, Ecms);
    if (v4.M() < 80 || v4.M() > 100)
        return false;
    if ((inc - v4).M() < 120 && (inc - v4).M() > 150)
        return false;

    double phi = e1.DeltaPhi(e2);
    if (phi > 175)
        return false;

    return true;
}

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

FitResult Fit(TH1D* h, double bkg_hint_NevtsInGeV,
    bool draw,
    char const* xtitle,
    char const* filename)
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
    h->Fit(ff, "R");

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
    fitResult.Ns = ff->GetParameter(0) * fitResult.width * sqrt(2 * 3.1415);

    if (draw) {

        TCanvas cvs;
        h->GetYaxis()->SetTitle("Events / 0.2GeV");
        h->GetYaxis()->CenterTitle();
        h->GetXaxis()->SetTitle(xtitle);
        h->GetXaxis()->CenterTitle();
        h->SetMinimum(0);
        h->Draw();

        ff->SetLineColor(kBlue);
        ff->SetLineWidth(2);

        TF1* signal_alone = 0;
        if (GAUS_FIT) {
            signal_alone = new TF1("", "gaus(0)", 120, 126);
        } else {
            signal_alone = new TF1("", crystalball_bkg_function, 120, 140, 5);
        }
        signal_alone->SetParameters(ff->GetParameters());
        signal_alone->SetNpx(1000);
        signal_alone->Draw("SAME");

        if(filename&& strlen(filename) > 0) {
            cvs.Print(filename);
        }
        delete signal_alone;
    }
    delete ff;
    return fitResult;
}


void PrintPhoton(char const* name, char const* output) {
    Events evts(name);
    printf("%f GeV\n", evts.Ecms);
    Hists hs(evts.Ecms);
    for (; evts.hasEvent(); evts.next()) {

        Event &evt = evts.getEvt();
        hs.fill(evt);
    }
    printf("print");
    
    hs.print(output);
}

struct Result {
    TGraph* gr_width_w;
    TGraph* gr_width_wo;
    TGraph* gr_massErr_w;
    TGraph* gr_massErr_wo;
};

void Plot(char const* rootname, char const* output, TrackRes trkRes, double bkg, double nExp, Result &res)
{
    PrintPhoton(rootname, output);

    double rc_nevts = 0;
    double tr_nevts = 0;

    Events evts(rootname);

    int Nbins = 100;
    int const NBMR = 10;
    double const Ecms = evts.Ecms;
    V4 whole(0,0,0,Ecms);

    TH1D* hist_recoil_mass_full = new TH1D("hist_recoil_mass_full", "", Nbins, 120, 140);
    TH1D* hist_recoil_mass_fast = new TH1D("hist_recoil_mass_fast", "", Nbins, 120, 140);
    TH1D* hist_recoil_mass_comp[NBMR];
    double as[NBMR];

    for (int i = 0; i < NBMR; ++i) {
        hist_recoil_mass_comp[i] = new TH1D("", "", Nbins, 120, 140);
    }

    double delta_a = 0.04;
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

        cvs.Print((std::string("img/") + output + "_fast_full.pdf").c_str());
    }


    {
        TGraph& sigma = *(new TGraph());
        TGraph& sigma2 = *(new TGraph());
        TGraph& massErr = *(new TGraph());
        TGraph& massErr2 = *(new TGraph());


        res.gr_massErr_w = &massErr;
        res.gr_massErr_wo = &massErr2;
        res.gr_width_w = &sigma;
        res.gr_width_wo = &sigma2;

        if (1) {
            printf("full simulation\n");
            std::string filename = "img/" + std::string(output) + "_full_simulation.pdf";
            FitResult fitResult = Fit(hist_recoil_mass_full, bkg, true, "Full Simulation", filename.c_str());
            fitResult.printInfo();
        }

        if (1) {
            printf("fast simulation\n");
            std::string filename = "img/" + std::string(output) + "_fast_simulation.pdf";
            FitResult fitResult = Fit(hist_recoil_mass_fast, bkg, true, "Recoil mass [GeV]", filename.c_str());
            fitResult.printInfo();

            sigma2.SetPoint(0, 0, fitResult.width);
            sigma2.SetPoint(1, (NBMR - 1) * delta_a, fitResult.width);
            massErr2.SetPoint(0, 0, 1000 * fitResult.mass_error);
            massErr2.SetPoint(1, (NBMR - 1) * delta_a, 1000 * fitResult.mass_error);
        }

        for (int i = 0; i < NBMR; ++i) {
            char av[100];
            sprintf(av, "a%f", as[i]);
            std::string filename = "img/" + std::string(output) + "_fast_simulation_" + av + ".pdf";
            FitResult fitResult = Fit(hist_recoil_mass_comp[i], bkg, true, "Recoil mass [GeV]", filename.c_str());
            sigma.SetPoint(i, delta_a * i, fitResult.width);
            massErr.SetPoint(i, delta_a * i, 1000 * fitResult.mass_error);
        }

        { // Peak width
            TCanvas cvs;
            sigma.GetXaxis()->CenterTitle();
            sigma.GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
            sigma.GetYaxis()->CenterTitle();
            sigma.GetYaxis()->SetTitle("Peak width of recoil mass [GeV]");
            sigma2.SetLineColor(kGray);

            sigma.Draw("AL");
            sigma2.Draw("SAME L");
            cvs.Print((std::string(output) + ".pdf(").c_str());
        }

        { // Higgs mass error vs. a
            TCanvas cvs;
            massErr.GetXaxis()->CenterTitle();
            massErr.GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
            massErr.GetYaxis()->CenterTitle();
            massErr.GetYaxis()->SetTitle("Uncertainty of higgs mass [MeV]");
            massErr2.SetLineColor(kGray);

            massErr.Draw("AL");
            massErr2.Draw("SAME L");
            gPad->SetLeftMargin(2);
            cvs.Print((std::string(output) + ".pdf").c_str());
        }
    }

}


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

void draw(Result res1, Result res2)
{
    TGraph* ew1 = res1.gr_width_w;
    TGraph* ew2 = res1.gr_width_wo;
    TGraph* em1 = res1.gr_massErr_w;
    TGraph* em2 = res1.gr_massErr_wo;
    
    TGraph* mw1 = res2.gr_width_w;
    TGraph* mw2 = res2.gr_width_wo;
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
        cvs.Print("img/result_peak_width.pdf");
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
        cvs.Print("img/result_mass_error.pdf");
        cvs.Print("C/massError.C");
    }
}

void Draw()
{


    SetStyle();
    gRandom->SetSeed(234729479);

    TrackRes trkRes;
    TrackRes trackResMuon;
    Result res1;
    Result res2;

    Plot("root/eeHa.root", "eeH", trkRes, 3500 / 0.8, 7.04 * 5600, res1);
    Plot("root/mumuHa.root", "mumuH", trkRes, 3200 / 0.8, 6.77 * 5600, res2);

    draw(res1, res2);
}
