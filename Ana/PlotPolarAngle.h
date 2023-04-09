#pragma once
#include "Basics.h"
#include "Events.h"



void DrawLepton(Config const &config, 
    char const* name, char const* output)
    {

    Events evts(name);
    TH1D *electron = new TH1D("","", 20, -1, 1);
    TH1D *positron = new TH1D("","", 20, -1, 1);

    for (; evts.hasEvent(); evts.next()) {
        Event &evt = evts.getEvt();
        electron->Fill(evt.E1.CosTheta());
        positron->Fill(evt.E2.CosTheta());
    }

    normalize_hist(electron);
    normalize_hist(positron);
    electron->Scale(10);
    positron->Scale(10);

    if(1) {
        TCanvas cvs("","", 500, 500);

        electron->SetLineWidth(3);
        electron->SetLineColor(kBlue);
        electron->GetXaxis()->SetTitle("cos#theta");
        electron->GetXaxis()->CenterTitle();
        electron->GetYaxis()->SetTitle("p.d.f");
        electron->GetYaxis()->CenterTitle();
        electron->GetXaxis()->SetRangeUser(-1.01, 1.01);
        electron->GetXaxis()->SetLabelSize(0.05);
        electron->GetYaxis()->SetLabelSize(0.05);
        electron->GetXaxis()->SetTitleSize(0.05);
        electron->GetYaxis()->SetTitleSize(0.05);

        positron->SetLineWidth(3);
        positron->SetLineColor(kRed);

        
        electron->Draw("Hist");
        positron->Draw("HIST SAME");
        TLegend leg = TLegend(0.47, 0.8, 0.87, 0.92);
        leg.SetTextSize(0.05);
        leg.AddEntry(electron, "e^{-}", "l");
        leg.AddEntry(positron, "e^{+}", "l");
        //leg.SetTextAlign(12);
        leg.SetBorderSize(0);
        leg.SetFillStyle(0);

        leg.Draw();

        cvs.Print( (config.imageFolder + "/" + output + "_costheta.pdf").c_str()  );

    }

}


