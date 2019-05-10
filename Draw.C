#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TLegend.h>

double isr1[4];
double isr2[4];
double fsr[4];
double e1[4];
double e2[4];
double bs1[4];
double bs2[4];


double isr1_[4];
double isr2_[4];
double fsr_[4];
double e1_[4];
double e2_[4];
double bs1_[4];
double bs2_[4];


void SmearPhoton(double *to, double *from, double a) {

    if(from[0] > 0) {
        double r = gRandom->Gaus();
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

void Smear(double a) {

    double r4 = gRandom->Gaus();
    double r5 = gRandom->Gaus();

    SmearPhoton(isr1_, isr1, a);
    SmearPhoton(isr2_, isr2, a);
    SmearPhoton(fsr_, fsr, a);
    SmearPhoton(bs1_, bs1, a);
    SmearPhoton(bs2_, bs2, a);

    for (int i = 0; i < 4; ++i)
    {
        e1_[i] = e1[i] * (1 + r4 * 5E-3);
        e2_[i] = e2[i] * (1 + r5 * 5E-3);
    }
}

void Plot(char const *name) {


    TFile *f = new TFile(name);
    TTree * tree = (TTree*)f->Get("evts");

    double Ecms;
    tree->SetBranchAddress("ISR1", isr1);
    tree->SetBranchAddress("ISR2", isr2);
    tree->SetBranchAddress("FSR", fsr);
    tree->SetBranchAddress("P1F", e1);
    tree->SetBranchAddress("P2F", e2);
    tree->SetBranchAddress("P1BS", bs1);
    tree->SetBranchAddress("P2BS", bs2);
    tree->SetBranchAddress("EMC_cms", &Ecms);
    
    tree->GetEntry(0);

    TH1D htot("","", 2*(int)(Ecms + 20), 0, Ecms + 20);
    TH1D hrec("","", 200, 120, 140);
    TH1D hrecE("","", 200, 120, 140);
    TH1D hrecEB("","", 200, 120, 140);

    TH1D hrecEB2("","", 200, 120, 140);
    TH1D hrecEB3("","", 200, 120, 140);

    TH1D hp("","",100, 0, 50);
    TH1D hfsr("","",100, 0, 50);
    TH1D hbs("","",100, 0, 25);
    TH1D hisr("","",100, 0, 25);
    for (int i = 0; i < (int)tree->GetEntries(); ++i)
    {
        tree->GetEntry(i);

        hp.Fill(isr1[0] + isr2[0] + fsr[0] + bs1[0] + bs2[0]);
        hfsr.Fill(fsr[0]);
        hbs.Fill(bs1[0] + bs2[0]);
        hisr.Fill(isr1[0] + isr2[0]);

        {

            Smear(0.17);

            double en = e1_[0] + e2_[0] + isr1_[0] + isr2_[0] + fsr_[0] + bs1_[0] + bs2_[0];
            double px = e1_[1] + e2_[1] + isr1_[1] + isr2_[1] + fsr_[1] + bs1_[1] + bs2_[1];
            double py = e1_[2] + e2_[2] + isr1_[2] + isr2_[2] + fsr_[2] + bs1_[2] + bs2_[2];
            double pz = e1_[3] + e2_[3] + isr1_[3] + isr2_[3] + fsr_[3] + bs1_[3] + bs2_[3];

            htot.Fill(TLorentzVector(px, py, pz, en).M());
            hrec.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            en = e1_[0] + e2_[0] + fsr_[0] + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1] + fsr_[1] + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2] + fsr_[2] + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3] + fsr_[3] + bs1_[3] + bs2_[3];
            hrecEB.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            en = e1_[0] + e2_[0];
            px = e1_[1] + e2_[1];
            py = e1_[2] + e2_[2];
            pz = e1_[3] + e2_[3];
            hrecE.Fill(TLorentzVector(px, py, pz, Ecms - en).M());





            Smear(0.05);
            en = e1_[0] + e2_[0]  + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1]  + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2]  + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3]  + bs1_[3] + bs2_[3];
            hrecEB2.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            Smear(0.5);
            en = e1_[0] + e2_[0]  + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1]  + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2]  + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3]  + bs1_[3] + bs2_[3];
            hrecEB3.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

        }
    }

    {
        TCanvas cvs;
        hrecEB.GetXaxis()->CenterTitle();
        hrecEB.GetXaxis()->SetTitle("Recoil(elec.+bream.) (Resolution(electron) = 0.5%) [GeV]");
        hrecEB.SetMaximum(hrecEB.GetMaximum()*1.4);
        hrecEB.SetLineColor(kBlue);
        hrecEB2.SetLineColor(kRed);
        hrecEB3.SetLineColor(kGreen);
        
        hrecEB.SetStats(false);
        hrecEB.Draw();
        hrecEB2.Draw("SAME");
        hrecEB3.Draw("SAME");


        TLegend leg(0.5, 0.65, 0.89, 0.89);
        leg.SetBorderSize(0);
        leg.SetFillColor(0);
        leg.AddEntry(&hrecEB2, "Resolution(photon)=0.05/#sqrt{E}");
        leg.AddEntry(&hrecEB, "Resolution(photon)=0.17/#sqrt{E}");
        leg.AddEntry(&hrecEB3, "Resolution(phton)=0.5/#sqrt{E}");
        leg.Draw();


        cvs.Print("res.pdf(");
    }

    {
        TCanvas cvs;
        hrec.GetXaxis()->CenterTitle();
        hrec.GetXaxis()->SetTitle("Recoil(elec.+photons) (Resolution(Photon)=0.17/sqrt(E) && Resolution(e) = 5E-3) [GeV]");
        hrec.Draw();
        cvs.Print("res.pdf");
    }
    {
        TCanvas cvs;
        hrecE.GetXaxis()->CenterTitle();
        hrecE.GetXaxis()->SetTitle("Recoil(elec.) (Resolution(Photon)=0.17/sqrt(E) && Resolution(e) = 5E-3) [GeV]");
        hrecE.Draw();
        cvs.Print("res.pdf");
    }
    {
        TCanvas cvs;
        hfsr.GetXaxis()->CenterTitle();
        hfsr.GetXaxis()->SetTitle("Final State Radiation Energy [GeV]");
        hfsr.Draw();
        cvs.Print("res.pdf");
    }
    
    {
        TCanvas cvs;
        hbs.GetXaxis()->CenterTitle();
        hbs.GetXaxis()->SetTitle("Bresstrahlung Energy [GeV]");
        hbs.Draw();
        cvs.Print("res.pdf");
    }
    {
        TCanvas cvs;
        hisr.GetXaxis()->CenterTitle();
        hisr.GetXaxis()->SetTitle("Initial State Radiation Energy [GeV]");
        hisr.Draw();
        cvs.Print("res.pdf");
    }

    {
        TCanvas cvs;
        hp.GetXaxis()->CenterTitle();
        hp.GetXaxis()->SetTitle("All Photons Energy [GeV]");
        hp.Draw();
        cvs.Print("res.pdf)");
    }
}


void Draw() {
    Plot("eeH.root");
}