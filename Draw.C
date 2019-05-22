#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>

#include <cmath>


double isr1[4];
double isr2[4];
double fsr1[4];
double fsr2[4];
double E1[4];
double E2[4];
double bs1[4];
double bs2[4];


double isr1_[4];
double isr2_[4];
double fsr1_[4];
double fsr2_[4];
double e1_[4];
double e2_[4];
double bs1_[4];
double bs2_[4];

double const trkRes = 3.85E-3;

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

void SetRnd() {
    for(int i = 0; i < 8; ++i)
        rnd[i] = gRandom->Gaus();
}
void Smear(double a) {


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

void Plot(char const *name, char const *output, double bkg, double nExp, TGraph *&grWidth, TGraph *&grWidth2, TGraph *&grMassErr, TGraph *&grMassErr2) {


    TFile *f = new TFile(name);
    TTree * tree = (TTree*)f->Get("evts");

    double Ecms;
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
    
    tree->GetEntry(0);

    TH1D htot("","", 2*(int)(Ecms + 20), 0, Ecms + 20);

    int Nbins = 100;
    TH1D hrec("","", Nbins, 120, 140);
    TH1D hrecE("","", Nbins, 120, 140);
    TH1D hrecEB("","", Nbins, 120, 140);

    TH1D hrecEB1("","", Nbins, 120, 140);
    TH1D hrecEB2("","", Nbins, 120, 140);
    TH1D hrecEB3("","", Nbins, 120, 140);
    TH1D hrecEB4("","", Nbins, 120, 140);
    TH1D hrecEB5("","", Nbins, 120, 140);

    TH1D *hrecEBs[10];
    TH1D *hrecEs[10];
  
    for(int i =0; i < sizeof(hrecEBs)/sizeof(void*); ++i) {
        hrecEBs[i] = new TH1D("", "", Nbins, 120, 140);
        hrecEs[i] = new TH1D("", "", Nbins, 120, 140);
    }

    double da = 0.02;

    TH1D hp("","",100, 0, 50);
    TH1D hfsr("","",100, 0, 50);
    TH1D hbs("","",100, 0, 25);
    TH1D hisr("","",100, 0, 25);
    
    for (int i = 0; i < (int)tree->GetEntries(); ++i)
    {
        tree->GetEntry(i);
        //if(i%2 == 0) continue;

        hp.Fill(isr1[0] + isr2[0] + fsr1[0] + fsr2[0] + bs1[0] + bs2[0]);
        hfsr.Fill(fsr1[0] + fsr2[0]);
        hbs.Fill(bs1[0] + bs2[0]);
        hisr.Fill(isr1[0] + isr2[0]);

        SetRnd();
        {


            Smear(0.17);

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


            Smear(0.00);
            en = e1_[0] + e2_[0] + fsr1_[0] + fsr2_[0] + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1] + fsr1_[1] + fsr2_[1] + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2] + fsr1_[2] + fsr2_[2] + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3] + fsr1_[3] + fsr2_[3] + bs1_[3] + bs2_[3];
            hrecEB1.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            Smear(0.05);
            en = e1_[0] + e2_[0] + fsr1_[0] + fsr2_[0] + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1] + fsr1_[1] + fsr2_[1] + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2] + fsr1_[2] + fsr2_[2] + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3] + fsr1_[3] + fsr2_[3] + bs1_[3] + bs2_[3];
            hrecEB2.Fill(TLorentzVector(px, py, pz, Ecms - en).M());


            Smear(0.10);
            en = e1_[0] + e2_[0] + fsr1_[0] + fsr2_[0] + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1] + fsr1_[1] + fsr2_[1] + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2] + fsr1_[2] + fsr2_[2] + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3] + fsr1_[3] + fsr2_[3] + bs1_[3] + bs2_[3];
            hrecEB3.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            Smear(0.20);
            en = e1_[0] + e2_[0] + fsr1_[0] + fsr2_[0] + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1] + fsr1_[1] + fsr2_[1] + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2] + fsr1_[2] + fsr2_[2] + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3] + fsr1_[3] + fsr2_[3] + bs1_[3] + bs2_[3];
            hrecEB4.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            Smear(0.40);
            en = e1_[0] + e2_[0] + fsr1_[0] + fsr2_[0] + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1] + fsr1_[1] + fsr2_[1] + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2] + fsr1_[2] + fsr2_[2] + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3] + fsr1_[3] + fsr2_[3] + bs1_[3] + bs2_[3];
            hrecEB5.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            for (int i = 0; i < sizeof(hrecEBs) / sizeof(void *); ++i)
            {
                Smear(i * da);
                en = e1_[0] + e2_[0] + fsr1_[0] + fsr2_[0] + bs1_[0] + bs2_[0];
                px = e1_[1] + e2_[1] + fsr1_[1] + fsr2_[1] + bs1_[1] + bs2_[1];
                py = e1_[2] + e2_[2] + fsr1_[2] + fsr2_[2] + bs1_[2] + bs2_[2];
                pz = e1_[3] + e2_[3] + fsr1_[3] + fsr2_[3] + bs1_[3] + bs2_[3];
                hrecEBs[i]->Fill(TLorentzVector(px, py, pz, Ecms - en).M());
                en = e1_[0] + e2_[0];
                px = e1_[1] + e2_[1];
                py = e1_[2] + e2_[2];
                pz = e1_[3] + e2_[3];
                hrecEs[i]->Fill(TLorentzVector(px, py, pz, Ecms - en).M());
            }
        }
    }

    // scale the signal
    double nevts = tree->GetEntries();
    //double scale = sqrt(nevts/nExp);
    //double weight = 1;
    double scale = 1;
    double weight = nExp/nevts;

    hrec.Scale(weight);
    hrecE.Scale(weight);
    hrecEB.Scale(weight);
    hrecEB1.Scale(weight);
    hrecEB2.Scale(weight);
    hrecEB3.Scale(weight);
    hrecEB4.Scale(weight);
    hrecEB5.Scale(weight);

    for (int i = 0; i < sizeof(hrecEBs) / sizeof(void *); ++i)
    {
        hrecEBs[i]->Scale(weight);
        hrecEs[i]->Scale(weight);
    }

    // add fake backgrounds
    // add fake backgrounds
    for (int b = 1; b <= hrecEBs[0]->GetNbinsX(); ++b)
    {
        double nb = gRandom->Poisson(bkg * hrecEBs[0]->GetBinWidth(b));
        for (int i = 0; i < sizeof(hrecEBs) / sizeof(void *); ++i)
        {
            hrecEBs[i]->AddBinContent(b, nb);
        }
    }
    for (int b = 1; b <= hrecEs[0]->GetNbinsX(); ++b)
    {
        double nb = gRandom->Poisson(bkg * hrecEs[0]->GetBinWidth(b));
        for (int i = 0; i < sizeof(hrecEs) / sizeof(void *); ++i)
        {
            hrecEs[i]->AddBinContent(b, nb);
        }
    }

    // let error = sqrt(value)
    for (int i = 0; i < sizeof(hrecEBs) / sizeof(void *); ++i)
    {
        hrecEBs[i]->Sumw2(false);
        hrecEs[i]->Sumw2(false);
    }


    {
        TCanvas cvs;
        hrecEB1.GetXaxis()->CenterTitle();
        hrecEB1.GetXaxis()->SetTitle("Recoil(elec.+BS+FSR) (Resolution(electron) = 0.5%) [GeV]");
        hrecEB1.SetMaximum(hrecEB.GetMaximum()*1.6);
        hrecEB1.SetLineColor(kBlue);
        hrecEB2.SetLineColor(kRed);
        hrecEB3.SetLineColor(kGreen);
        hrecEB4.SetLineColor(kViolet);
        hrecEB5.SetLineColor(kBlack);
        
        hrecEB1.SetStats(false);
        hrecEB1.Draw("HIST");

        hrecEB1.Draw("HIST SAME");
        hrecEB2.Draw("HIST SAME");
        hrecEB3.Draw("HIST SAME");
        hrecEB4.Draw("HIST SAME");
        hrecEB5.Draw("HIST SAME");


        TLegend leg(0.5, 0.65, 0.89, 0.89);
        leg.SetBorderSize(0);
        leg.SetFillColor(0);
        leg.AddEntry(&hrecEB1, "Resolution(photon)=0.00/#sqrt{E}");
        leg.AddEntry(&hrecEB2, "Resolution(photon)=0.05/#sqrt{E}");
        leg.AddEntry(&hrecEB3, "Resolution(phton)=0.10/#sqrt{E}");
        leg.AddEntry(&hrecEB4, "Resolution(phton)=0.20/#sqrt{E}");
        leg.AddEntry(&hrecEB5, "Resolution(phton)=0.40/#sqrt{E}");
        leg.Draw();


        cvs.Print((std::string(output) + ".pdf(").c_str());
    }

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


        for (int i = 0; i < sizeof(hrecEBs) / sizeof(void *); ++i)
        {

            {
                TH1D *h = hrecEBs[i];
                TF1 *ff = new TF1("", "gaus(0) + [3]", 120, 126);
                ff->SetParameters(100, 125, 1, bkg*20/Nbins);
                ff->SetParNames("C", "Mean", "Sigma", "Bkg");
                h->Fit(ff, "R Q");
                int n = sigma.GetN();
                sigma.SetPoint(n, i * da, ff->GetParameter(2));
                mass.SetPoint(n, i * da, ff->GetParameter(1));
                massErr.SetPoint(n, i * da, scale*1000*ff->GetParError(1));

                TCanvas cvs;
                h->GetYaxis()->SetTitle("Events / 0.2GeV");
                h->SetMinimum(0);
                h->Draw();
                ff->SetLineColor(kBlue);
                ff->SetLineWidth(2);
                char b[100];
                sprintf(b, "%sTryGaus_a%f.png", output, i * da);
                cvs.Print(b);

            }

            if(i == 0) {
                TH1D *h = hrecEs[i];
                TF1 *ff = new TF1("", "gaus(0) + [3]", 120, 126);
                ff->SetParameters(100, 125, 1, bkg*20/Nbins);
                ff->SetParNames("C", "Mean", "Sigma", "Bkg");
                h->Fit(ff, "R");

                sigma2.SetPoint(0, 0, ff->GetParameter(2));
                sigma2.SetPoint(1, (sizeof(hrecEBs) / sizeof(void *)-1)*da, ff->GetParameter(2));
                massErr2.SetPoint(0, 0, scale*1000*ff->GetParError(1));
                massErr2.SetPoint(1, (sizeof(hrecEBs) / sizeof(void *)-1)*da, scale*1000*ff->GetParError(1));
                
                TCanvas cvs;
                //h->Scale(nExp/nevts);
                h->GetYaxis()->SetTitle("Events / 0.2GeV");
                h->SetMinimum(0);
                h->Draw();
                ff->SetLineColor(kBlue); 
                ff->SetLineWidth(2);

                TF1 gaus("", "gaus(0)", 120, 126);
                gaus.SetParameters(ff->GetParameters());
                gaus.Draw("SAME");

                cvs.Print(("TryGaus2_" + std::string(output) + ".png").c_str());
            }
        }

        {
            TCanvas cvs;
            sigma.GetXaxis()->CenterTitle();
            sigma.GetXaxis()->SetTitle("a (Resolution(Photon) = a/#sqrt{E})");
            sigma.GetYaxis()->CenterTitle();
            sigma.GetYaxis()->SetTitle("Width of Recoil Mass [GeV]");
            sigma2.SetLineColor(kGray);

            sigma.Draw("AL");
            sigma.Draw("SAME L");
            cvs.Print((std::string(output) + ".pdf").c_str());
        }

        if(0) {
            TCanvas cvs;
            mass.GetXaxis()->CenterTitle();
            mass.GetXaxis()->SetTitle("a (Resolution(Photon)=a/#sqrt{E})");
            mass.GetYaxis()->CenterTitle();
            mass.GetYaxis()->SetTitle("Higgs Mass [GeV]");
            mass.Draw("ALP");
            cvs.Print((std::string(output) + ".pdf").c_str());
        }

        {
            TCanvas cvs;
            massErr.GetXaxis()->CenterTitle();
            massErr.GetXaxis()->SetTitle("a (Resolution(Photon)=a/#sqrt{E})");
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
        hrec.GetXaxis()->SetTitle("Recoil(elec.+BS+FSR+ISR) (Resolution(Photon)=0.17/sqrt(E) && Resolution(e) = 5E-3) [GeV]");
        hrec.Draw();
        cvs.Print((std::string(output) + ".pdf").c_str());
    }
    {
        TCanvas cvs;
        hrecEB.GetXaxis()->CenterTitle();
        hrecEB.GetXaxis()->SetTitle("Recoil(elec.+BS+FSR) (Resolution(Photon)=0.17/sqrt(E) && Resolution(e) = 5E-3) [GeV]");
        hrecEB.SetStats(true);
        hrecEB.Draw();
        cvs.Print((std::string(output) + ".pdf").c_str());
    }
    {
        TCanvas cvs;
        hrecE.GetXaxis()->CenterTitle();
        hrecE.GetXaxis()->SetTitle("Recoil(elec.) (Resolution(Photon)=0.17/sqrt(E) && Resolution(e) = 5E-3) [GeV]");
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


void Draw() {
    TGraph *ew1 = NULL;
    TGraph *ew2 = NULL;
    TGraph *em1 = NULL;
    TGraph *em2 = NULL;
    TGraph *mw1 = NULL;
    TGraph *mw2 = NULL;
    TGraph *mm1 = NULL;
    TGraph *mm2 = NULL;

    Plot("eeH.root", "eeH", 1100*5, 7.04*5000*0.28, ew1, ew2, em1, em2);
    Plot("mumuH.root", "mumuH", 600*5, 6.77*5000*0.62, mw1, mw2, mm1, mm2);

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

        ew1->Draw("AL");
        mw1->Draw("SAME L");
        ew2->Draw("SAME L");
        mw2->Draw("SAME L");

        TLegend leg(0.2, 0.70, 0.59, 0.89);
        leg.AddEntry(ew1, "eeH (w/ FSR&BS)");
        leg.AddEntry(mw1, "#mu#muH (w/ FSR&BS)");
        leg.AddEntry(ew2, "eeH (w/o FSR&BS)");
        leg.AddEntry(mw2, "#mu#muH (w/o FSR&BS)");
        leg.SetBorderSize(0);
        leg.Draw();
        cvs.Print("width.pdf");
    }

    if(em1 && mm1 && em2 && mm2) {
        TCanvas cvs;
        em1->SetLineColor(kRed);
        em1->SetLineWidth(2);
        mm1->SetLineColor(kGreen);        
        mm1->SetLineWidth(2);

        em2->SetLineColor(kRed);
        em2->SetLineWidth(2);
        em2->SetLineStyle(2);
        mm2->SetLineColor(kGreen);        
        mm2->SetLineWidth(2);
        mm2->SetLineStyle(2);
        
        em1->SetMaximum(50);
        em1->SetMinimum(0);
        em1->Draw("AL");
        mm1->Draw("SAME L");
        em2->Draw("SAME L");
        mm2->Draw("SAME L");

        TLegend leg(0.2, 0.70, 0.59, 0.89);
        leg.AddEntry(em1, "eeH (w/ FSR&BS)");
        leg.AddEntry(mm1, "#mu#muH (w/ FSR&BS)");
        leg.AddEntry(em2, "eeH (w/o FSR&BS)");
        leg.AddEntry(mm2, "#mu#muH (w/o FSR&BS)");
        leg.SetBorderSize(0);
        leg.Draw();
        cvs.Print("massError.pdf");
    }
    if(0) printf("%p %p %p %p %p %p %p %p\n", ew1, ew2, mw1, mw2, em1, em2, mm1, mm2);

}
