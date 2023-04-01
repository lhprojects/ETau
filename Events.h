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


using V4 = TLorentzVector;

struct PhotonRes {
    double a;
    double res(V4 const& v4)
    {
        if (v4.E() > 0)
            return a / sqrt(v4.E());
        else
            return 0;
    }

    V4 smear(V4 const &from, double r  ){
        return from * (1 + res(from) * r);
    }
};

struct TrackRes
{
    double pars[6];

    TrackRes()
    {

        double lpars[] = { -6.53193064e+00, -1.70098932e-01, 7.13246936e-02,
            9.86062092e-04,
            -4.67288223e-04, 1.10435253e-05 };
        for (size_t i = 0; i < sizeof(lpars) / sizeof(double); ++i) {
            pars[i] = lpars[i];
        }
    }

    double res(TLorentzVector const& trk)
    {
        if(1) {
            double const R = 1.8;
            double const Z = 4.7;
            double const costhetac = cos(atan(2 * R / Z));
            double const sinthetac = sqrt(1 - costhetac * costhetac);
            double const xc = costhetac;
            double const xc2 = xc * xc;

            double const pt = trk.Pt();
            double const logpt = log(pt);
            double const b0 = pars[0] + logpt * pars[1] + logpt * logpt * pars[2];
            double const b1 = pars[3] + logpt * pars[4] + logpt * logpt * pars[5];

            double const costheta = trk.CosTheta();
            double const sintheta = sin(trk.Theta());
            double x = fabs(costheta);
            x = std::max(1E-6, x);
            double const x2 = x*x;
            double r = (fabs(x) < xc) ? R : sintheta / x *  (Z/2);
            r = std::max(1E-6, r);
            double res = (exp(b0) + b1 * x2) * (R / r) * (R / r);
            //printf("res: %f\n", res);
            return res;
        }
    }

    V4 smear(V4 const & from, double r)
    {
        return from * (1 + res(from) * r);
    }
};

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

struct Event
{
    TLorentzVector e1;
    TLorentzVector e2;
    TLorentzVector bs1;
    TLorentzVector bs2;
    TLorentzVector isr1;
    TLorentzVector isr2;
    TLorentzVector fsr1;
    TLorentzVector fsr2;

    TLorentzVector e1_;
    TLorentzVector e2_;
    TLorentzVector bs1_;
    TLorentzVector bs2_;
    TLorentzVector isr1_;
    TLorentzVector isr2_;
    TLorentzVector fsr1_;
    TLorentzVector fsr2_;

    V4 total;
    V4 photon;
    V4 isr;
    V4 fsr;
    V4 bs;
    V4 lep;

    void init() {
        e1 = E1 - bs1;
        e2 = E2 - bs2;

        lep = e1 + e2;
        isr = isr1 + isr2;
        fsr = fsr1 + fsr2;
        bs = bs1 + bs2;
        photon = fsr + isr + bs;
        total = photon + lep;
    }

    // smear photon and track resolution
    void smear(PhotonRes phoRes, TrackRes trkRes, Rand const &rnd)
    {
        isr1_ = phoRes.smear(isr1, rnd.rnd[0]);
        isr2_ = phoRes.smear(isr2, rnd.rnd[1]);
        fsr1_ = phoRes.smear(fsr1, rnd.rnd[2]);
        fsr2_ = phoRes.smear(fsr2, rnd.rnd[3]);
        bs1_ = phoRes.smear(bs1, rnd.rnd[4]);
        bs2_ = phoRes.smear(bs2, rnd.rnd[5]);
        e1_ = trkRes.smear(E1 - bs1, rnd.rnd[6]);
        e2_ = trkRes.smear(E2 - bs2, rnd.rnd[7]);
    }


    TLorentzVector E1;
    TLorentzVector E2;
    TLorentzVector rc_e1;
    TLorentzVector rc_e2;
};

V4 asV4(double const *v4) {
    return V4(v4[1], v4[2], v4[3], v4[0]);
}


bool print(bool a) {
    printf("TF %d\n", a);
    return a;
}

struct Events {

    double Ecms;
    double isr1[4];
    double isr2[4];
    double fsr1[4];
    double fsr2[4];
    double E1[4];
    double E2[4];
    double bs1[4];
    double bs2[4];
    double rc_e1[4];
    double rc_e2[4];
    bool RCAvaliable;
    TTree *tree;

    long long index;
    Event evt;
    long long nevts;

    void reset() {
        index = 0;
    }

    Events(char const *name)
    {
        TFile* f = new TFile(name);
        tree = (TTree*)f->Get("evts");
        if(!tree){
            throw "tree not exist";
        }
        nevts = tree->GetEntries();
        index = 0;

        printf("%d events\n", (int)nevts);

        tree->SetBranchAddress("ISR1", isr1);
        tree->SetBranchAddress("ISR2", isr2);
        tree->SetBranchAddress("FSR1", fsr1);
        tree->SetBranchAddress("FSR2", fsr2);
        tree->SetBranchAddress("P1F", E1); // the final state electron
        tree->SetBranchAddress("P2F", E2);
        tree->SetBranchAddress("P1BS", bs1);
        tree->SetBranchAddress("P2BS", bs2);
        tree->SetBranchAddress("EMC_cms", &Ecms);
        RCAvaliable = tree->GetBranch("RC_P1") && tree->GetBranch("RC_P2");
        if (RCAvaliable) {
            tree->SetBranchAddress("RC_P1", rc_e1);
            tree->SetBranchAddress("RC_P2", rc_e2);
        }
        // set Ecms
        tree->GetEntry(0);
    }

    bool hasEvent() const {
        bool hasEvt = index < tree->GetEntries();
        //printf("index %d\n", (int)index);
        return hasEvt;
    }

    Event &getEvt() {
        //printf("get");

        tree->GetEntry(index);
        evt.fsr1 = asV4(fsr1);
        evt.fsr2 = asV4(fsr2);
        evt.isr1 = asV4(isr1);
        evt.isr2 = asV4(isr2);
        evt.bs1 = asV4(bs1);
        evt.bs2 = asV4(bs2);
        evt.E1 = asV4(E1);
        evt.E2 = asV4(E2);
        evt.rc_e1 = asV4(rc_e1);
        evt.rc_e2 = asV4(rc_e2);
        evt.init();
        return evt;
    }

    void next() {
        ++index;
    }

};

void normalize_hist(TH1D* h)
{
    int nbins = h->GetNbinsX();
    h->Scale(1. / h->Integral(0, nbins + 1));
}


struct Hists {

    Hists(double Ecms) {

        hfsr = new TH1D("fsr", "", 100, 0, 50);
        hbs = new TH1D("bs", "", 50, 0, 25);
        hisr = new TH1D("isr", "", 50, 0, 25);
        hist_total_mass = new TH1D("hist_total_mass", "hist_total_mass",
            2 * (int)(Ecms + 20), 0, Ecms + 20);
    }

    void fill(Event &evt) {
        //printf("fill");
        hfsr->Fill(evt.fsr1.E());
        hfsr->Fill(evt.fsr2.E());
        hbs->Fill(evt.bs1.E());
        hbs->Fill(evt.bs2.E());
        hisr->Fill(evt.isr1.E());
        hisr->Fill(evt.isr2.E());
        hist_total_mass->Fill(evt.total.M());
    }

    void print(char const*output)
    {
        
        {
            normalize_hist(hisr);
            TCanvas cvs;
            hisr->GetXaxis()->CenterTitle();
            hisr->GetXaxis()->SetTitle("Initial State Radiation Energy [GeV]");
            hisr->GetYaxis()->CenterTitle();
            hisr->GetYaxis()->SetTitle("A.U. / 0.5GeV");
            //hisr.GetYaxis()->SetTitleOffset(0.1);
            hisr->Draw("hist");
            std::string pdf_name = std::string() + "img/" + output + "_ISR_Energy.pdf";
            cvs.Print(pdf_name.c_str());
        }
        {
            normalize_hist(hfsr);
            TCanvas cvs;
            hfsr->GetXaxis()->CenterTitle();
            hfsr->GetXaxis()->SetTitle("Final State Radiation Energy [GeV]");
            hfsr->GetYaxis()->CenterTitle();
            hfsr->GetYaxis()->SetTitle("A.U. / 0.5GeV");
            //hfsr.GetYaxis()->SetTitleOffset(0.1);
            hfsr->Draw("hist");
            std::string pdf_name = std::string() + "img/" + output + "_FSR_Energy.pdf";
            cvs.Print(pdf_name.c_str());
        }
        {
            normalize_hist(hbs);
            TCanvas cvs;
            hbs->GetXaxis()->CenterTitle();
            hbs->GetXaxis()->SetTitle("Bresstrahlung Energy [GeV]");
            hbs->GetYaxis()->CenterTitle();
            hbs->GetYaxis()->SetTitle("A.U. / 0.5GeV");
            //hbs.GetYaxis()->SetTitleOffset(0.1);
            hbs->Draw("hist");
            std::string pdf_name = std::string() + "img/" + output + "_Bress_Energy.pdf";
            cvs.Print(pdf_name.c_str());
        }
    }

    TH1D*hist_total_mass,*hfsr, *hbs, *hisr;
};
