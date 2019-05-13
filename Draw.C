#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TF1.h>

double eff_width(TH1 *h, double *err = NULL) {

        //                                 1
        // eff_width =      ----------------------------------
        //                  integrate  2 sqrt(pi) (p.d.f)^2 dx

        int n = h->GetNbinsX();
        double sum = 0;
        double sum2 = 0;
        for(int i = 1; i <= n; ++i) {
            double pdfw = h->GetBinContent(i); 
            double w = h->GetBinWidth(i); 
            sum += pdfw;
            sum2 += pdfw*pdfw / w; 
        
        }
        double result = sum*sum / ( 2*sqrt(3.14159265359)*sum2);


        if(err) {

            double sum = 0;
            double sum2 = 0;
            double sum3 = 0;
            for (int i = 1; i <= n; ++i)
            {
                double n = h->GetBinContent(i);
                double w = h->GetBinWidth(i);
                sum += n;
                sum2 += n*n/w;
                sum3 += n*n*n/(w*w);
            }
            double e = 2/(sum2*sum)*sqrt(sum*(sum3*sum-sum2*sum2));
            *err = e * result;
        }


        return result;
}

double HalfWidth(TH1 *h) {
        double mean = h->GetMean();
        double tot = h->Integral(1, h->GetNbinsX());
        double width = 0;
        for(int left = 1; left <= h->GetNbinsX(); ++left)
        {
            double cnt = 0;
            double lx = h->GetBinLowEdge(left);
            for (int right = left; left <= h->GetNbinsX(); ++right)
            {
                cnt += h->GetBinContent(right);
                if(cnt >= tot*0.6278) {
                    double rx = h->GetBinLowEdge(right);
                    double remain = cnt - tot*0.6278;
                    rx += std::max(1., remain / h->GetBinContent(right)) * h->GetBinWidth(right);
                    if(left == 1) width = rx - lx;
                    else width = std::min(width, rx - lx);
                    break;
                }
            }
        }
        return width;
}



#include <cmath>

// see math/mathcore/src/PdfFuncMathCore.cxx in ROOT 6.x
double crystalball_function(double x, double alpha, double n, double sigma, double mean) {
  // evaluate the crystal ball function
  if (sigma < 0.)     return 0.;
  double z = (x - mean)/sigma;
  if (alpha < 0) z = -z;
  double abs_alpha = std::abs(alpha);
  // double C = n/abs_alpha * 1./(n-1.) * std::exp(-alpha*alpha/2.);
  // double D = std::sqrt(M_PI/2.)*(1.+ROOT::Math::erf(abs_alpha/std::sqrt(2.)));
  // double N = 1./(sigma*(C+D));
  if (z  > - abs_alpha)
    return std::exp(- 0.5 * z * z);
  else {
    //double A = std::pow(n/abs_alpha,n) * std::exp(-0.5*abs_alpha*abs_alpha);
    double nDivAlpha = n/abs_alpha;
    double AA =  std::exp(-0.5*abs_alpha*abs_alpha);
    double B = nDivAlpha -abs_alpha;
    double arg = nDivAlpha/(B-z);
    return AA * std::pow(arg,n);
  }
}

double crystalball_function(const double *x, const double *p) {
  // if ((!x) || (!p)) return 0.; // just a precaution
  // [Constant] * ROOT::Math::crystalball_function(x, [Alpha], [N], [Sigma], [Mean])
  return (p[0] * crystalball_function(x[0], p[3], p[4], p[2], p[1]));
}


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


double rnd[7];

void SetRnd() {
    for(int i = 0; i < 7; ++i)
        rnd[i] = gRandom->Gaus();
}
void Smear(double a) {


    SmearPhoton(isr1_, isr1, a, rnd[0]);
    SmearPhoton(isr2_, isr2, a, rnd[1]);
    SmearPhoton(fsr_, fsr, a, rnd[2]);
    SmearPhoton(bs1_, bs1, a, rnd[3]);
    SmearPhoton(bs2_, bs2, a, rnd[4]);

    for (int i = 0; i < 4; ++i)
    {
        e1_[i] = e1[i] * (1 + rnd[5] * 5E-3);
        e2_[i] = e2[i] * (1 + rnd[6] * 5E-3);
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

    TH1D hrecEB1("","", 200, 120, 140);
    TH1D hrecEB2("","", 200, 120, 140);
    TH1D hrecEB3("","", 200, 120, 140);
    TH1D hrecEB4("","", 200, 120, 140);
    TH1D hrecEB5("","", 200, 120, 140);

    int Nbins = 200;
    TH1D *hrecEBs[10];
  
    for(int i =0; i < sizeof(hrecEBs)/sizeof(void*); ++i) {
        hrecEBs[i] = new TH1D("", "", Nbins, 120, 140);
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

        hp.Fill(isr1[0] + isr2[0] + fsr[0] + bs1[0] + bs2[0]);
        hfsr.Fill(fsr[0]);
        hbs.Fill(bs1[0] + bs2[0]);
        hisr.Fill(isr1[0] + isr2[0]);

        SetRnd();
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


            Smear(0.00);
            en = e1_[0] + e2_[0]  + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1]  + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2]  + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3]  + bs1_[3] + bs2_[3];
            hrecEB1.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            Smear(0.05);
            en = e1_[0] + e2_[0]  + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1]  + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2]  + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3]  + bs1_[3] + bs2_[3];
            hrecEB2.Fill(TLorentzVector(px, py, pz, Ecms - en).M());


            Smear(0.10);
            en = e1_[0] + e2_[0]  + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1]  + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2]  + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3]  + bs1_[3] + bs2_[3];
            hrecEB3.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            Smear(0.20);
            en = e1_[0] + e2_[0]  + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1]  + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2]  + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3]  + bs1_[3] + bs2_[3];
            hrecEB4.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            Smear(0.40);
            en = e1_[0] + e2_[0]  + bs1_[0] + bs2_[0];
            px = e1_[1] + e2_[1]  + bs1_[1] + bs2_[1];
            py = e1_[2] + e2_[2]  + bs1_[2] + bs2_[2];
            pz = e1_[3] + e2_[3]  + bs1_[3] + bs2_[3];
            hrecEB5.Fill(TLorentzVector(px, py, pz, Ecms - en).M());

            for(int i = 0; i < sizeof(hrecEBs)/sizeof(void*); ++i) {
                Smear(i*da);
                en = e1_[0] + e2_[0] + bs1_[0] + bs2_[0];
                px = e1_[1] + e2_[1] + bs1_[1] + bs2_[1];
                py = e1_[2] + e2_[2] + bs1_[2] + bs2_[2];
                pz = e1_[3] + e2_[3] + bs1_[3] + bs2_[3];
                hrecEBs[i]->Fill(TLorentzVector(px, py, pz, Ecms - en).M());
            }
        }
    }

    {
        TCanvas cvs;
        hrecEB1.GetXaxis()->CenterTitle();
        hrecEB1.GetXaxis()->SetTitle("Recoil(elec.+bream.) (Resolution(electron) = 0.5%) [GeV]");
        hrecEB1.SetMaximum(hrecEB.GetMaximum()*1.4);
        hrecEB1.SetLineColor(kBlue);
        hrecEB2.SetLineColor(kRed);
        hrecEB3.SetLineColor(kGreen);
        hrecEB4.SetLineColor(kViolet);
        hrecEB5.SetLineColor(kBlack);
        
        hrecEB1.SetStats(false);
        hrecEB1.Draw();

        hrecEB1.Draw("SAME");
        hrecEB2.Draw("SAME");
        hrecEB3.Draw("SAME");
        hrecEB4.Draw("SAME");
        hrecEB5.Draw("SAME");


        TLegend leg(0.5, 0.65, 0.89, 0.89);
        leg.SetBorderSize(0);
        leg.SetFillColor(0);
        leg.AddEntry(&hrecEB1, "Resolution(photon)=0.00/#sqrt{E}");
        leg.AddEntry(&hrecEB2, "Resolution(photon)=0.05/#sqrt{E}");
        leg.AddEntry(&hrecEB3, "Resolution(phton)=0.10/#sqrt{E}");
        leg.AddEntry(&hrecEB4, "Resolution(phton)=0.20/#sqrt{E}");
        leg.AddEntry(&hrecEB5, "Resolution(phton)=0.40/#sqrt{E}");
        leg.Draw();


        cvs.Print("res.pdf(");
    }

    {
        TCanvas cvs;
        TGraph gr;
        for (int i = 0; i < sizeof(hrecEBs) / sizeof(void *); ++i)
        {
            TH1D *h = hrecEBs[i];
            //gr.SetPoint(gr.GetN(), i * da, HalfWidth(h));
            //gr.SetPoint(gr.GetN(), i * da, eff_width(hrecEBs[i]));

            //double r, e;
            //r = eff_width(hrecEBs[i], &e);
            //printf("%f +- %f\n", r, e);

            if (i == 0)
            {

                TF1 *ff = new TF1("", crystalball_function, 120, 140, 5);
                ff->SetParNames("Constant", "Mean", "Sigma", "Alpha", "N");

                double max_ = h->GetMaximum();
                ff->SetParameter(0, max_);
                ff->SetParameter(1, 125);
                ff->SetParameter(2, 1);
                ff->SetParameter(3, 1);
                ff->SetParameter(4, 1);

                h->Fit(ff);
                TCanvas cvs;
                h->Draw();
                char b[100];
                sprintf(b, "TryCrystallball%f.png", i * da);
                cvs.Print(b);
            }

            if (1)
            {
                TF1 *ff = new TF1("", "gaus(0)", 120, 126);
                h->Fit(ff, "R");
                gr.SetPoint(gr.GetN(), i * da, 100*ff->GetParameter(2)/125);

                TCanvas cvs;
                h->Draw();
                char b[100];
                sprintf(b, "TryGaus%f.png", i * da);
                cvs.Print(b);
            }
        }
        gr.GetXaxis()->CenterTitle();
        gr.GetXaxis()->SetTitle("a (Resolution(Photon)=a/#sqrt{E})");
        gr.GetYaxis()->CenterTitle();
        gr.GetYaxis()->SetTitle("Resolution of Recoil Mass Against Elec. + BS [%]");
        gr.Draw("APC");
        cvs.Print("res.pdf");
    }

    {
        TCanvas cvs;
        hrec.GetXaxis()->CenterTitle();
        hrec.GetXaxis()->SetTitle("Recoil(elec.+All photons) (Resolution(Photon)=0.17/sqrt(E) && Resolution(e) = 5E-3) [GeV]");
        hrec.Draw();
        cvs.Print("res.pdf");
    }
    {
        TCanvas cvs;
        hrecEB.GetXaxis()->CenterTitle();
        hrecEB.GetXaxis()->SetTitle("Recoil(elec.+BS) (Resolution(Photon)=0.17/sqrt(E) && Resolution(e) = 5E-3) [GeV]");
        hrecEB.SetStats(true);
        hrecEB.Draw();
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
