#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TStyle.h>
#include <cmath>
#include "crystalball.h"



bool const FULL_SIMULATION = 1;
bool const SMEAR_SQRTS = 1;
bool GAUS_FIT = 0;
double const sqrts_sigma1 = 1.34E-3;
double const sqrts_sigma2 = 1.34E-3;

double isr1[4];
double isr2[4];
double fsr1[4];
double fsr2[4];
double E1[4];
double E2[4];
double e1[4];
double e2[4];
double bs1[4];
double bs2[4];
double rc_e1[4];
double rc_e2[4];

double isr1_[4];
double isr2_[4];
double fsr1_[4];
double fsr2_[4];
double e1_[4];
double e2_[4];
double bs1_[4];
double bs2_[4];


void SmearPhoton(double *to, double *from, double a, double r) {

    if(from[0] > 0) {
        to[0] = from[0] * (1 + a / sqrt(from[0]) * r);
        to[1] = from[1] * (1 + a / sqrt(from[0]) * r);
        to[2] = from[2] * (1 + a / sqrt(from[0]) * r);
        to[3] = from[3] * (1 + a / sqrt(from[0]) * r);
    } else {
        to[0] = from[0];
        to[1] = from[1];
        to[2] = from[2];
        to[3] = from[3];
    }
}


double rnd[8];
double r1;
double r2;
void SetRnd() {
    for(int i = 0; i < 8; ++i)
        rnd[i] = gRandom->Gaus();
    r1 = gRandom->Gaus();
    r2 = gRandom->Gaus();
}

void SmearEnergySpread(double &en, double &px, double &py, double &pz, double Ecms) {

    double const delta1 = sqrts_sigma1 * r1;
    double const delta2 = sqrts_sigma2 * r2;
    double const beta = (delta1 - delta2) / 2;
    double const en_ = en;
    double const pz_ = pz;
    en = en_ + beta * pz_;
    pz = pz_ + beta * en_;
    en += 0.5 * (delta1 + delta2) * Ecms;
}

void Smear(double a, double trkRes) {


    SmearPhoton(isr1_, isr1, a, rnd[0]);
    SmearPhoton(isr2_, isr2, a, rnd[1]);
    SmearPhoton(fsr1_, fsr1, a, rnd[2]);
    SmearPhoton(fsr2_, fsr2, a, rnd[3]);
    SmearPhoton(bs1_, bs1, a, rnd[4]);
    SmearPhoton(bs2_, bs2, a, rnd[5]);

    for (int i = 0; i < 4; ++i)
    {
        e1_[i] = (E1[i] - bs1[i]) * (1 + rnd[6] * trkRes);
        e2_[i] = (E2[i] - bs2[i]) * (1 + rnd[7] * trkRes);
    }
}


void Fit(TH1D *h, char const *output,
 char const *xtitle, double bkg_hint_NevtsInGeV,
 double &width, double &mass_uncertainty, double &Ns, bool first_call, bool last_call)
{
    TF1 *ff;
    if(GAUS_FIT) {
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
    h->Fit(ff, "R Q");
    width = ff->GetParameter(2);
    mass_uncertainty = ff->GetParError(1);
    Ns = ff->GetParameter(0) * width * sqrt(2 * 3.1415);

    TCanvas cvs;
    h->GetYaxis()->SetTitle("Events / 0.2GeV");
    h->GetXaxis()->SetTitle(xtitle);
    h->SetMinimum(0);
    h->Draw();
    ff->SetLineColor(kBlue);
    ff->SetLineWidth(2);

    TF1 *signal_alone = 0;
    if (GAUS_FIT)
    {
        signal_alone = new TF1("", "gaus(0)", 120, 126);
    }
    else
    {
        signal_alone = new TF1("", crystalball_bkg_function, 120, 140, 5);
    }
    signal_alone->SetParameters(ff->GetParameters());
    signal_alone->SetNpx(1000);
    signal_alone->Draw("SAME");

    if (first_call)
        cvs.Print(("FitCurve_" + std::string(output) + ".pdf(").c_str());
    else if (last_call)
        cvs.Print(("FitCurve_" + std::string(output) + ".pdf)").c_str());
    else
        cvs.Print(("FitCurve_" + std::string(output) + ".pdf").c_str());
    delete signal_alone;
    delete ff;
}

void Plot(char const *name, char const *output, double trkRes, double bkg, double nExp, TGraph *&grWidth, TGraph *&grWidth2, TGraph *&grMassErr, TGraph *&grMassErr2) {


    TFile *f = new TFile(name);
    TTree * tree = (TTree*)f->Get("evts");
    double nevts = tree->GetEntries();
    double rc_nevts = 0;
    double tr_nevts = 0;

    double Ecms;
    bool RCAvaliable = false;
    tree->SetBranchAddress("ISR1", isr1);
    tree->SetBranchAddress("ISR2", isr2);
    tree->SetBranchAddress("FSR1", fsr1);
    tree->SetBranchAddress("FSR2", fsr2);
    tree->SetBranchAddress("P1F", E1); // the final state electron
    tree->SetBranchAddress("P2F", E2);
    // E1 + fsr1 + E2 + fsr2 + isr1 + isr2 + Higgs = Ecms
    // E1 = e1 + bs1
    // E2 = e2 + bs2
    tree->SetBranchAddress("P1BS", bs1);
    tree->SetBranchAddress("P2BS", bs2);
    tree->SetBranchAddress("EMC_cms", &Ecms); 
    RCAvaliable = tree->GetBranch("RC_P1") && tree->GetBranch("RC_P2");
    if(RCAvaliable) {
        tree->SetBranchAddress("RC_P1", rc_e1);
        tree->SetBranchAddress("RC_P2", rc_e2);
    }

    tree->GetEntry(0);

    TH1D htot("","", 2*(int)(Ecms + 20), 0, Ecms + 20);

    int Nbins = 100;
    TH1D hrec("","", Nbins, 120, 140);
    TH1D hrecE("","", Nbins, 120, 140);
    TH1D hrecEB("","", Nbins, 120, 140);

    TH2D hdrecd1("","", 100, -5E-3, +5E-3, 100, -1, 1);

    int const NBMR = 10;
    TH1D *hrecEBs[NBMR];
    TH1D *hrecRCE = new TH1D("","", Nbins, 120, 140);

    TH1D *hrecEs = new TH1D("", "", Nbins, 120, 140);

    for(int i =0; i < sizeof(hrecEBs)/sizeof(void*); ++i) {
        hrecEBs[i] = new TH1D("", "", Nbins, 120, 140);
    }

    double da = 0.04;

    TH1D hp("","",100, 0, 50);
    TH1D hfsr("","",100, 0, 50);
    TH1D hbs("","",100, 0, 25);
    TH1D hisr("","",100, 0, 25);
    
    for (int i = 0; i < (int)tree->GetEntries(); ++i)
    {
        tree->GetEntry(i);
        for(int i = 0; i < 4; ++i) {
            e1[i] = E1[i] - bs1[i];
            e2[i] = E2[i] - bs2[i];
        }
        //if(i%2 == 0) continue;

        hp.Fill(isr1[0] + isr2[0] + fsr1[0] + fsr2[0] + bs1[0] + bs2[0]);
        hfsr.Fill(fsr1[0] + fsr2[0]);
        hbs.Fill(bs1[0] + bs2[0]);
        hisr.Fill(isr1[0] + isr2[0]);

        SetRnd();

        {
            
            Smear(0.17, trkRes);

            double en = e1_[0] + e2_[0] + isr1_[0] + isr2_[0] + fsr1_[0] + fsr2_[0] + bs1_[0] + bs2_[0];
            double px = e1_[1] + e2_[1] + isr1_[1] + isr2_[1] + fsr1_[1] + fsr2_[1] + bs1_[1] + bs2_[1];
            double py = e1_[2] + e2_[2] + isr1_[2] + isr2_[2] + fsr1_[2] + fsr2_[2] + bs1_[2] + bs2_[2];
            double pz = e1_[3] + e2_[3] + isr1_[3] + isr2_[3] + fsr1_[3] + fsr2_[3] + bs1_[3] + bs2_[3];

            htot.Fill(TLorentzVector(px, py, pz, en).M());
            hrec.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            en = e1_[0] + e2_[0] + fsr1_[0] + fsr2_[0] + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1] + fsr1_[1] + fsr2_[1] + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2] + fsr1_[2] + fsr2_[2] + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3] + fsr1_[3] + fsr2_[3] + bs1_[3] + bs2_[3];
            hrecEB.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            en = e1_[0] + e2_[0];
            px = e1_[1] + e2_[1];
            py = e1_[2] + e2_[2];
            pz = e1_[3] + e2_[3];
            hrecE.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            do
            {
                Smear(0, trkRes);
                en = e1_[0] + e2_[0];
                px = e1_[1] + e2_[1];
                py = e1_[2] + e2_[2];
                pz = e1_[3] + e2_[3];

                if (e1[0] == 0)
                    continue;
                if (e2[0] == 0)
                    continue;
                if (sqrt(px * px + py * py) < 20)
                    continue;
                TLorentzVector v4(px, py, pz, en);
                TLorentzVector inc(0, 0, 0, Ecms);
                if (v4.M() < 80 || v4.M() > 100)
                    continue;
                if ((inc - v4).M() < 120 && (inc - v4).M() > 150)
                    continue;
                double phi1 = TVector3(e1_[1], e1_[2], e1_[3]).Phi();
                double phi2 = TVector3(e2_[1], e2_[2], e2_[3]).Phi();
                double phi = fabs(phi2 - phi1);
                phi *= 180 / 3.1415926;
                if (phi > 180)
                    phi -= 180;
                if (phi > 175)
                    continue;

                tr_nevts += 1;

                if (SMEAR_SQRTS)
                    SmearEnergySpread(en, px, py, pz, Ecms);

                hrecEs->Fill(TLorentzVector(px, py, pz, Ecms - en).M());
                for (int i = 0; i < sizeof(hrecEBs) / sizeof(void *); ++i)
                {
                    Smear(da * i, trkRes);
                    en = e1_[0] + e2_[0] + fsr1_[0] + fsr2_[0] + bs1_[0] + bs2_[0];
                    px = e1_[1] + e2_[1] + fsr1_[1] + fsr2_[1] + bs1_[1] + bs2_[1];
                    py = e1_[2] + e2_[2] + fsr1_[2] + fsr2_[2] + bs1_[2] + bs2_[2];
                    pz = e1_[3] + e2_[3] + fsr1_[3] + fsr2_[3] + bs1_[3] + bs2_[3];
                    if (SMEAR_SQRTS)
                        SmearEnergySpread(en, px, py, pz, Ecms);
                    hrecEBs[i]->Fill(TLorentzVector(px, py, pz, Ecms - en).M());
                }

            } while (false);

            if(RCAvaliable) {
                en = rc_e1[0] + rc_e2[0];
                px = rc_e1[1] + rc_e2[1];
                py = rc_e1[2] + rc_e2[2];
                pz = rc_e1[3] + rc_e2[3];

                do {
                    if (rc_e1[0] == 0)
                        continue;
                    if (rc_e2[0] == 0)
                        continue;
                    if (sqrt(px * px + py * py) < 20)
                        continue;
                    TLorentzVector v4(px, py, pz, en);
                    TLorentzVector inc(0, 0, 0, Ecms);
                    if (v4.M() < 80 || v4.M() > 100)
                        continue;
                    if ((inc-v4).M() < 120 && (inc-v4).M() > 150)
                        continue;
                    double phi1 = TVector3(rc_e1[1], rc_e1[2], rc_e1[3]).Phi();
                    double phi2 = TVector3(rc_e2[1], rc_e2[2], rc_e2[3]).Phi();
                    double phi = fabs(phi2-phi1);
                    phi *= 180/3.1415926;
                    if(phi > 180) phi -= 180;
                    if(phi > 175) continue;

                    if (SMEAR_SQRTS)
                    {

                        double m1 = TLorentzVector(px, py, pz, Ecms - en).M();
                        SmearEnergySpread(en, px, py, pz, Ecms);
                        double delta1 = sqrts_sigma1 * r1;
                        double delta2 = sqrts_sigma2 * r2;
                        double dm = -2 * Ecms * (0.5 * (delta1 + delta2) * (Ecms - en) + 0.5 * (delta1 - delta2) * pz) / (2 * m1);

                        double m2 = TLorentzVector(px, py, pz, Ecms - en).M();
                        //printf("%f %f %f\n", m1, dm, m2 - m1);
                        hdrecd1.Fill(delta1, m2 - m1);
                    }

                    hrecRCE->Fill(TLorentzVector(px, py, pz, Ecms - en).M());
                    rc_nevts += 1;

                } while(false);
            }
        }
    }


    if(SMEAR_SQRTS) {
        TCanvas cvs;
        hdrecd1.GetXaxis()->SetTitle("#delta_{1}");
        hdrecd1.Draw();
        cvs.Print("DRecD1.pdf");
    }
    // scale the signal

    //double weight = 1;
    hrecRCE->Scale(nExp / nevts);

    double eff = rc_nevts / nevts;
    printf("rc eff. %f\n", eff);
    printf("tr eff. %f\n", tr_nevts / nevts);

    hrec.Scale(nExp * eff / nevts);
    hrecE.Scale(nExp * eff / nevts);
    hrecEB.Scale(nExp * eff / nevts);
    hrecEs->Scale(nExp * eff / tr_nevts);
    for (int i = 0; i < sizeof(hrecEBs) / sizeof(void *); ++i)
    {
        hrecEBs[i]->Scale(nExp * eff / tr_nevts);
    }

    // add fake backgrounds
    for (int b = 1; b <= hrecEBs[0]->GetNbinsX(); ++b)
    {
        //double nb = gRandom->Poisson(bkg * hrecEBs[0]->GetBinWidth(b));
        double nb = bkg * hrecEBs[0]->GetBinWidth(b);
        for (int i = 0; i < sizeof(hrecEBs) / sizeof(void *); ++i)
        {
            hrecEBs[i]->AddBinContent(b, nb);
        }
    }
    for (int b = 1; b <= hrecEs->GetNbinsX(); ++b)
    {
        //double nb = gRandom->Poisson(bkg * hrecEs[0]->GetBinWidth(b));
        double nb = bkg * hrecEBs[0]->GetBinWidth(b);
        hrecEs->AddBinContent(b, nb);
        hrecRCE->AddBinContent(b, nb);
    }

    // let error = sqrt(value)
    for (int i = 0; i < sizeof(hrecEBs) / sizeof(void *); ++i)
    {
        hrecEBs[i]->Sumw2(false);
    }
    hrecEs->Sumw2(false);
    hrecRCE->Sumw2(false);

    {
        TGraph &sigma = *(new TGraph());
        grWidth = &sigma;
        TGraph &sigma2 = *(new TGraph());
        grWidth2 = &sigma2;

        TGraph &massErr = *(new TGraph());
        grMassErr = &massErr;

        TGraph &massErr2 = *(new TGraph());
        grMassErr2 = &massErr2;

        TGraph mass;

        double width;
        double mass_uncertainty;
        double Ns;
        Fit(hrecRCE, output, "Full Simulation", bkg, width, mass_uncertainty, Ns, true, false);
        if(FULL_SIMULATION) {
            sigma2.SetPoint(0, 0, width);
            sigma2.SetPoint(1, (sizeof(hrecEBs) / sizeof(void *) - 1) * da, width);
            massErr2.SetPoint(0, 0, 1000 * mass_uncertainty);
            massErr2.SetPoint(1, (sizeof(hrecEBs) / sizeof(void *) - 1) * da, 1000 * mass_uncertainty);

        }
        printf("mass uncertainty %f\n", mass_uncertainty);
        printf("width %f\n", width);
        printf("Ns %f\n", Ns);
        Fit(hrecEs, output, "Fast Simulation", bkg, width, mass_uncertainty, Ns, false, false);
        
        if(!FULL_SIMULATION) {
            sigma2.SetPoint(0, 0, width);
            sigma2.SetPoint(1, (sizeof(hrecEBs) / sizeof(void *) - 1) * da, width);
            massErr2.SetPoint(0, 0, 1000 * mass_uncertainty);
            massErr2.SetPoint(1, (sizeof(hrecEBs) / sizeof(void *) - 1) * da, 1000 * mass_uncertainty);
        }
        printf("mass uncertainty %f\n", mass_uncertainty);
        printf("width %f\n", width);
        printf("Ns %f\n", Ns);

        for (int i = 0; i < sizeof(hrecEBs) / sizeof(void *); ++i)
        {
            Fit(hrecEBs[i], output, "Fast Simulation", bkg, width, mass_uncertainty, Ns, false, i + 1 == sizeof(hrecEBs) / sizeof(void *));
            sigma.SetPoint(i, da*i, width);
            massErr.SetPoint(i, da*i, 1000*mass_uncertainty);
        }

        {
            TCanvas cvs;
            sigma.GetXaxis()->CenterTitle();
            sigma.GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
            sigma.GetYaxis()->CenterTitle();
            sigma.GetYaxis()->SetTitle("Width of Recoil Mass [GeV]");
            sigma2.SetLineColor(kGray);

            sigma.Draw("AL");
            sigma.Draw("SAME L");
            cvs.Print((std::string(output) + ".pdf(").c_str());
        }

        if(0) {
            TCanvas cvs;
            mass.GetXaxis()->CenterTitle();
            mass.GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
            mass.GetYaxis()->CenterTitle();
            mass.GetYaxis()->SetTitle("Higgs Mass [GeV]");
            mass.Draw("ALP");
            cvs.Print((std::string(output) + ".pdf").c_str());
        }

        {
            TCanvas cvs;
            massErr.GetXaxis()->CenterTitle();
            massErr.GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
            massErr.GetYaxis()->CenterTitle();
            massErr.GetYaxis()->SetTitle("Uncertainty of Higgs Mass [MeV]");
            massErr2.SetLineColor(kGray);
            massErr.Draw("AL");
            massErr2.Draw("SAME L");
            gPad->SetLeftMargin(2);
            cvs.Print((std::string(output) + ".pdf").c_str());
        }

    }

    {
        TCanvas cvs;
        hrec.GetXaxis()->CenterTitle();
        hrec.GetXaxis()->SetTitle("Recoil(Lep.+BS+FSR+ISR) (#sigma(E_{#gamma})/E_{#gamma}=0.17/sqrt(E)) [GeV]");
        hrec.Draw();
        cvs.Print((std::string(output) + ".pdf").c_str());
    }
    {
        TCanvas cvs;
        hrecEB.GetXaxis()->CenterTitle();
        hrecEB.GetXaxis()->SetTitle("Recoil(Lep.+BS+FSR) (#sigma(E_{#gamma})/E_{#gamma}=0.17/sqrt(E)) [GeV]");
        hrecEB.SetStats(true);
        hrecEB.Draw();
        cvs.Print((std::string(output) + ".pdf").c_str());
    }
    {
        TCanvas cvs;
        hrecE.GetXaxis()->CenterTitle();
        hrecE.GetXaxis()->SetTitle("Recoil(Lep.) (#sigma(E_{#gamma})/E_{#gamma}=0.17/sqrt(E)) [GeV]");
        hrecE.Draw();
        cvs.Print((std::string(output) + ".pdf").c_str());
    }
    {
        TCanvas cvs;
        hisr.GetXaxis()->CenterTitle();
        hisr.GetXaxis()->SetTitle("Initial State Radiation Energy [GeV]");
        hisr.Draw();
        cvs.Print((std::string(output) + ".pdf").c_str());
    }
    {
        TCanvas cvs;
        hfsr.GetXaxis()->CenterTitle();
        hfsr.GetXaxis()->SetTitle("Final State Radiation Energy [GeV]");
        hfsr.Draw();
        cvs.Print((std::string(output) + ".pdf").c_str());
    }
    {
        TCanvas cvs;
        hbs.GetXaxis()->CenterTitle();
        hbs.GetXaxis()->SetTitle("Bresstrahlung Energy [GeV]");
        hbs.Draw();
        cvs.Print((std::string(output) + ".pdf").c_str());
    }

    {
        TCanvas cvs;
        hp.GetXaxis()->CenterTitle();
        hp.GetXaxis()->SetTitle("ISR+FSR+BS [GeV]");
        hp.Draw();
        cvs.Print((std::string(output) + ".pdf)").c_str());
    }
}
void SetStyle() {
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetCanvasDefH(600);
    gStyle->SetCanvasDefW(600);
    gStyle->SetLabelSize(0.04,"xyz");
    gStyle->SetTitleSize(0.05,"xyz");
    gStyle->SetTitleOffset(1.2,"yz");
    gStyle->SetTitleOffset(1.2,"x");

    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadTopMargin(0.05);
    gStyle->SetPadRightMargin(0.05);
    gStyle->SetPadLeftMargin(0.15);

}


void Draw() {
    SetStyle();
    TGraph *ew1 = NULL;
    TGraph *ew2 = NULL;
    TGraph *em1 = NULL;
    TGraph *em2 = NULL;
    TGraph *mw1 = NULL;
    TGraph *mw2 = NULL;
    TGraph *mm1 = NULL;
    TGraph *mm2 = NULL;


    gRandom->SetSeed(234729479);
    Plot("root/eeHa.root", "eeH", 3.8E-3, 3500/0.8, 7.04*5600, ew1, ew2, em1, em2);
    Plot("root/mumuHa.root", "mumuH", 2.40E-3, 3200/0.8, 6.77*5600, mw1, mw2, mm1, mm2);
    //Plot("root/eeHa.root", "eeH", 2.64E-3, 0, 7.04*5600*0.63/0.77, ew1, ew2, em1, em2);
    //Plot("root/mumuHa.root", "mumuH", 2.64E-3, 0, 7.04*5600*0.63/0.77, mw1, mw2, mm1, mm2);

    if(ew1 && ew2 && mw1 && mw2) {
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

        ew1->SetMaximum(0.8);
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
        cvs.Print("width.pdf");
        cvs.Print("C/width.C");
    }

    if(em1 && mm1 && em2 && mm2) {
        TCanvas cvs;


        TGraph com;
        for(int i = 0; i < em1->GetN(); ++i) {
            double x,y1,y2;
            em1->GetPoint(i, x, y1);
            mm1->GetPoint(i, x, y2);
            com.SetPoint(i, x, 1./sqrt(1/(y1*y1)+1/(y2*y2)));
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
        
        em1->SetMaximum(45);
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
        cvs.Print("massError.pdf");
        cvs.Print("C/massError.C");
    }
    if(0) printf("%p %p %p %p %p %p %p %p\n", ew1, ew2, mw1, mw2, em1, em2, mm1, mm2);

}
