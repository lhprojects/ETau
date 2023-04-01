void width()
{
//=========Macro generated from canvas: c1_n2/c1_n2
//=========  (Tue Sep 28 07:59:52 2021) by ROOT version 6.16/00
   TCanvas *c1_n2 = new TCanvas("c1_n2", "c1_n2",0,0,600,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1_n2->Range(-0.07425,-0.28125,0.42075,1.59375);
   c1_n2->SetFillColor(0);
   c1_n2->SetBorderMode(0);
   c1_n2->SetBorderSize(2);
   c1_n2->SetLeftMargin(0.15);
   c1_n2->SetRightMargin(0.05);
   c1_n2->SetTopMargin(0.05);
   c1_n2->SetBottomMargin(0.15);
   c1_n2->SetFrameBorderMode(0);
   c1_n2->SetFrameBorderMode(0);
   
   Double_t ew1_fx1[10] = {
   0,
   0.04,
   0.08,
   0.12,
   0.16,
   0.2,
   0.24,
   0.28,
   0.32,
   0.36};
   Double_t ew1_fy1[10] = {
   0.4491246,
   0.4563828,
   0.4802155,
   0.5079921,
   0.5372189,
   0.5604564,
   0.5849136,
   0.6051676,
   0.623366,
   0.6428313};
   TGraph *graph = new TGraph(10,ew1_fx1,ew1_fy1);
   graph->SetName("ew1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_ew11 = new TH1F("Graph_ew11","",100,0,0.396);
   Graph_ew11->SetMinimum(0);
   Graph_ew11->SetMaximum(1.5);
   Graph_ew11->SetDirectory(0);
   Graph_ew11->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_ew11->SetLineColor(ci);
   Graph_ew11->GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
   Graph_ew11->GetXaxis()->CenterTitle(true);
   Graph_ew11->GetXaxis()->SetLabelFont(42);
   Graph_ew11->GetXaxis()->SetTitleSize(0.05);
   Graph_ew11->GetXaxis()->SetTitleOffset(1.2);
   Graph_ew11->GetXaxis()->SetTitleFont(42);
   Graph_ew11->GetYaxis()->SetTitle("Width of Recoil Mass [GeV]");
   Graph_ew11->GetYaxis()->CenterTitle(true);
   Graph_ew11->GetYaxis()->SetLabelFont(42);
   Graph_ew11->GetYaxis()->SetTitleSize(0.05);
   Graph_ew11->GetYaxis()->SetTitleOffset(1.2);
   Graph_ew11->GetYaxis()->SetTitleFont(42);
   Graph_ew11->GetZaxis()->SetLabelFont(42);
   Graph_ew11->GetZaxis()->SetTitleSize(0.05);
   Graph_ew11->GetZaxis()->SetTitleOffset(1.2);
   Graph_ew11->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_ew11);
   
   graph->Draw("al");
   
   Double_t mw1_fx2[10] = {
   0,
   0.04,
   0.08,
   0.12,
   0.16,
   0.2,
   0.24,
   0.28,
   0.32,
   0.36};
   Double_t mw1_fy2[10] = {
   0.4086592,
   0.412834,
   0.4200852,
   0.4259175,
   0.4313245,
   0.4355647,
   0.4386712,
   0.4417663,
   0.4440766,
   0.4464726};
   graph = new TGraph(10,mw1_fx2,mw1_fy2);
   graph->SetName("mw1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mw12 = new TH1F("Graph_mw12","",100,0,0.396);
   Graph_mw12->SetMinimum(0.4048778);
   Graph_mw12->SetMaximum(0.4502539);
   Graph_mw12->SetDirectory(0);
   Graph_mw12->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_mw12->SetLineColor(ci);
   Graph_mw12->GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
   Graph_mw12->GetXaxis()->CenterTitle(true);
   Graph_mw12->GetXaxis()->SetLabelFont(42);
   Graph_mw12->GetXaxis()->SetTitleSize(0.05);
   Graph_mw12->GetXaxis()->SetTitleOffset(1.2);
   Graph_mw12->GetXaxis()->SetTitleFont(42);
   Graph_mw12->GetYaxis()->SetTitle("Width of Recoil Mass [GeV]");
   Graph_mw12->GetYaxis()->CenterTitle(true);
   Graph_mw12->GetYaxis()->SetLabelFont(42);
   Graph_mw12->GetYaxis()->SetTitleSize(0.05);
   Graph_mw12->GetYaxis()->SetTitleOffset(1.2);
   Graph_mw12->GetYaxis()->SetTitleFont(42);
   Graph_mw12->GetZaxis()->SetLabelFont(42);
   Graph_mw12->GetZaxis()->SetTitleSize(0.05);
   Graph_mw12->GetZaxis()->SetTitleOffset(1.2);
   Graph_mw12->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_mw12);
   
   graph->Draw(" l");
   
   Double_t ew2_fx3[2] = {
   0,
   0.36};
   Double_t ew2_fy3[2] = {
   0.4443432,
   0.4443432};
   graph = new TGraph(2,ew2_fx3,ew2_fy3);
   graph->SetName("ew2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_ew23 = new TH1F("Graph_ew23","",100,0,0.396);
   Graph_ew23->SetMinimum(0.3443432);
   Graph_ew23->SetMaximum(1.544343);
   Graph_ew23->SetDirectory(0);
   Graph_ew23->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_ew23->SetLineColor(ci);
   Graph_ew23->GetXaxis()->SetLabelFont(42);
   Graph_ew23->GetXaxis()->SetTitleSize(0.05);
   Graph_ew23->GetXaxis()->SetTitleOffset(1.2);
   Graph_ew23->GetXaxis()->SetTitleFont(42);
   Graph_ew23->GetYaxis()->SetLabelFont(42);
   Graph_ew23->GetYaxis()->SetTitleSize(0.05);
   Graph_ew23->GetYaxis()->SetTitleOffset(1.2);
   Graph_ew23->GetYaxis()->SetTitleFont(42);
   Graph_ew23->GetZaxis()->SetLabelFont(42);
   Graph_ew23->GetZaxis()->SetTitleSize(0.05);
   Graph_ew23->GetZaxis()->SetTitleOffset(1.2);
   Graph_ew23->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_ew23);
   
   graph->Draw(" l");
   
   Double_t mw2_fx4[2] = {
   0,
   0.36};
   Double_t mw2_fy4[2] = {
   0.4230631,
   0.4230631};
   graph = new TGraph(2,mw2_fx4,mw2_fy4);
   graph->SetName("mw2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mw24 = new TH1F("Graph_mw24","",100,0,0.396);
   Graph_mw24->SetMinimum(0.3230631);
   Graph_mw24->SetMaximum(1.523063);
   Graph_mw24->SetDirectory(0);
   Graph_mw24->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_mw24->SetLineColor(ci);
   Graph_mw24->GetXaxis()->SetLabelFont(42);
   Graph_mw24->GetXaxis()->SetTitleSize(0.05);
   Graph_mw24->GetXaxis()->SetTitleOffset(1.2);
   Graph_mw24->GetXaxis()->SetTitleFont(42);
   Graph_mw24->GetYaxis()->SetLabelFont(42);
   Graph_mw24->GetYaxis()->SetTitleSize(0.05);
   Graph_mw24->GetYaxis()->SetTitleOffset(1.2);
   Graph_mw24->GetYaxis()->SetTitleFont(42);
   Graph_mw24->GetZaxis()->SetLabelFont(42);
   Graph_mw24->GetZaxis()->SetTitleSize(0.05);
   Graph_mw24->GetZaxis()->SetTitleOffset(1.2);
   Graph_mw24->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_mw24);
   
   graph->Draw(" l");
   
   TLegend *leg = new TLegend(0.52,0.7,0.92,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("ew1","eeH (w/ FSR&BS)","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mw1","#mu#muH (w/ FSR&BS)","L");

   ci = TColor::GetColor("#00ff00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("ew2","eeH (w/o FSR&BS)","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mw2","#mu#muH (w/o FSR&BS)","L");

   ci = TColor::GetColor("#00ff00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c1_n2->Modified();
   c1_n2->cd();
   c1_n2->SetSelected(c1_n2);
}
