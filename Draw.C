
void Draw() {


    TFile *f = new TFile("result.root");
    TTree * tree = (TTree*)f->Get("evts");

    double isr1;
    double isr2;
    double fsr;
    double e1;
    double e2;
    double bs1;
    double bs2;
    tree->SetBranchAddress("EMC_ISR1", &isr1);
    tree->SetBranchAddress("EMC_ISR2", &isr2);
    tree->SetBranchAddress("EMC_FSR", &fsr);
    tree->SetBranchAddress("EMC_P1BS", &bs1);
    tree->SetBranchAddress("EMC_P2BS", &bs2);
    tree->SetBranchAddress("EMC_P1F", &e1);
    tree->SetBranchAddress("EMC_P2F", &e2);

    TH1D htot("","",100, 80, 100);
    TH1D htot2("","",100, 80, 100);

    TH1D hp("","",100, 0, 50);
    TH1D hfsr("","",100, 0, 50);
    TH1D hbs("","",100, 0, 50);
    TH1D hisr("","",100, 0, 50);
    for (int i = 0; i < (int)tree->GetEntries(); ++i)
    {
        tree->GetEntry(i);
        double photon = isr1 + isr2 + fsr + bs1 + bs2;
        double tot = e1 * (1 + 0.005 * gRandom->Gaus()) 
        + e2 * (1 + 0.005 * gRandom->Gaus()) + photon * (1 + 0.17 / sqrt(photon) * gRandom->Gaus());

        double tot2 = e1 * (1 + 0.005 * gRandom->Gaus()) 
        + e2 * (1 + 0.005 * gRandom->Gaus()) + photon * (1 + 0.085 / sqrt(photon) * gRandom->Gaus());

        htot.Fill(tot);
        htot2.Fill(tot2);
        hp.Fill(photon);
        hfsr.Fill(fsr);
        hbs.Fill(bs1 + bs2);
        hisr.Fill(isr1 + isr2);
    }


    {
        TCanvas cvs;
        htot.GetXaxis()->CenterTitle();
        htot.GetXaxis()->SetTitle("Total Energy (With Resolution(Photon)=0.17/sqrt(E) && Resolution(e) = 5E-3) [GeV]");
        htot.Draw();
        cvs.Print("res.pdf(");
    }

    {
        TCanvas cvs;
        htot2.GetXaxis()->CenterTitle();
        htot2.GetXaxis()->SetTitle("Total Energy (With Resolution(Photon)=0.085/sqrt(E) && Resolution(e) = 5E-3) [GeV]");
        htot2.Draw();
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