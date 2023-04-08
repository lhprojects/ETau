#pragma once
#include "Basics.h"
#include "TrackRes.h"


struct PhotonRes {
    double a;

    double res(V4 const& v4) const
    {
        if (v4.E() > 0)
            return a / sqrt(v4.E());
        else
            return 0;
    }

    V4 smear(V4 const &from, double r  ) const
    {
        return from * (1 + res(from) * r);
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
    void smearTracks(TrackRes const &trkRes, Rand const &rnd)
    {
        e1_ = trkRes.smear(E1 - bs1, rnd.rnd[6]);
        e2_ = trkRes.smear(E2 - bs2, rnd.rnd[7]);
    }
    
    void smearPhotons(PhotonRes const &phoRes, Rand const &rnd)
    {
        isr1_ = phoRes.smear(isr1, rnd.rnd[0]);
        isr2_ = phoRes.smear(isr2, rnd.rnd[1]);
        fsr1_ = phoRes.smear(fsr1, rnd.rnd[2]);
        fsr2_ = phoRes.smear(fsr2, rnd.rnd[3]);
        bs1_ = phoRes.smear(bs1, rnd.rnd[4]);
        bs2_ = phoRes.smear(bs2, rnd.rnd[5]);
    }

    // smear photon and track resolution
    void smear(PhotonRes const &phoRes,
     TrackRes const &trkRes,
      Rand const &rnd)
    {
        smearPhotons(phoRes, rnd);
        smearTracks(trkRes, rnd);
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
