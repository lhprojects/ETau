#pragma once
#include "Basics.h"
#include "Events.h"


struct Hists {

    Hists(double Ecms) {

        hfsr = new TH1D("fsr", "", 100, 0, 25);
        hbs = new TH1D("bs", "", 100, 0, 25);
        hisr = new TH1D("isr", "", 100, 0, 25);
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
	
private:
    void fmtHist(TH1*hist) {
        hist->SetLineWidth(3);
    }
public:
    void print(std::string const &output)
    {

    	bool logy = true;


        {
            normalize_hist(hisr);
            TCanvas cvs;
            gPad->SetLogy(logy);	
            hisr->GetXaxis()->CenterTitle();
            hisr->GetXaxis()->SetTitle("Initial State Radiation Energy [GeV]");
            hisr->GetYaxis()->CenterTitle();
            hisr->GetYaxis()->SetTitle("A.U. / 0.5GeV");
            fmtHist(hisr);
            //hisr.GetYaxis()->SetTitleOffset(0.1);
            hisr->Draw("hist");

            std::string pdf_name = output + "_ISR_Energy.pdf";
            cvs.Print(pdf_name.c_str());
        }
        {
            normalize_hist(hfsr);
            TCanvas cvs;
            gPad->SetLogy(logy);	
            hfsr->GetXaxis()->CenterTitle();
            hfsr->GetXaxis()->SetTitle("Final State Radiation Energy [GeV]");
            hfsr->GetYaxis()->CenterTitle();
            hfsr->GetYaxis()->SetTitle("A.U. / 0.5GeV");
            fmtHist(hisr);
            //hfsr.GetYaxis()->SetTitleOffset(0.1);
            hfsr->Draw("hist");
            std::string pdf_name =  output + "_FSR_Energy.pdf";
            cvs.Print(pdf_name.c_str());
        }
        {
            normalize_hist(hbs);
            TCanvas cvs;
            gPad->SetLogy(logy);	
            hbs->GetXaxis()->CenterTitle();
            hbs->GetXaxis()->SetTitle("Bresstrahlung Energy [GeV]");
            hbs->GetYaxis()->CenterTitle();
            hbs->GetYaxis()->SetTitle("A.U. / 0.5GeV");
            fmtHist(hisr);
            //hbs.GetYaxis()->SetTitleOffset(0.1);
            hbs->Draw("hist");
            std::string pdf_name = output + "_Bress_Energy.pdf";
            cvs.Print(pdf_name.c_str());
        }
    }

    TH1D*hist_total_mass,*hfsr, *hbs, *hisr;
};




void PlotPhoton(Config const &config, 
    char const* name, char const* output) {
    Events evts(name);
    printf("%f GeV\n", evts.Ecms);
    Hists hs(evts.Ecms);
    for (; evts.hasEvent(); evts.next()) {

        Event &evt = evts.getEvt();
        hs.fill(evt);
    }

    hs.print((config.imageFolder + "/" + output));
}

