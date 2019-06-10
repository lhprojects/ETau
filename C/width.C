void width()
{
//=========Macro generated from canvas: c1_n2/c1_n2
//=========  (Mon Jun 10 18:34:27 2019) by ROOT version 6.16/00
   TCanvas *c1_n2 = new TCanvas("c1_n2", "c1_n2",0,0,600,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1_n2->Range(-0.07425,-0.15,0.42075,0.85);
   c1_n2->SetFillColor(0);
   c1_n2->SetBorderMode(0);
   c1_n2->SetBorderSize(2);
   c1_n2->SetLeftMargin(0.15);
   c1_n2->SetRightMargin(0.05);
   c1_n2->SetTopMargin(0.05);
   c1_n2->SetBottomMargin(0.15);
   c1_n2->SetFrameBorderMode(0);
   c1_n2->SetFrameBorderMode(0);
   
   Double_t ew1_fx28[10] = {
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
   Double_t ew1_fy28[10] = {
   0.4897868,
   0.4977402,
   0.5189529,
   0.5506855,
   0.5778832,
   0.6071246,
   0.6292717,
   0.6524544,
   0.6699018,
   0.6893452};
   TGraph *graph = new TGraph(10,ew1_fx28,ew1_fy28);
   graph->SetName("ew1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_ew128 = new TH1F("Graph_ew128","",100,0,0.396);
   Graph_ew128->SetMinimum(0);
   Graph_ew128->SetMaximum(0.8);
   Graph_ew128->SetDirectory(0);
   Graph_ew128->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_ew128->SetLineColor(ci);
   Graph_ew128->GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
   Graph_ew128->GetXaxis()->CenterTitle(true);
   Graph_ew128->GetXaxis()->SetLabelFont(42);
   Graph_ew128->GetXaxis()->SetTitleSize(0.05);
   Graph_ew128->GetXaxis()->SetTitleOffset(1.2);
   Graph_ew128->GetXaxis()->SetTitleFont(42);
   Graph_ew128->GetYaxis()->SetTitle("Width of Recoil Mass [GeV]");
   Graph_ew128->GetYaxis()->CenterTitle(true);
   Graph_ew128->GetYaxis()->SetLabelFont(42);
   Graph_ew128->GetYaxis()->SetTitleSize(0.05);
   Graph_ew128->GetYaxis()->SetTitleOffset(1.2);
   Graph_ew128->GetYaxis()->SetTitleFont(42);
   Graph_ew128->GetZaxis()->SetLabelFont(42);
   Graph_ew128->GetZaxis()->SetTitleSize(0.05);
   Graph_ew128->GetZaxis()->SetTitleOffset(1.2);
   Graph_ew128->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_ew128);
   
   graph->Draw("al");
   
   Double_t mw1_fx29[10] = {
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
   Double_t mw1_fy29[10] = {
   0.382578,
   0.3859842,
   0.3919914,
   0.3991334,
   0.4039031,
   0.4079256,
   0.4122444,
   0.4152655,
   0.4176107,
   0.4196368};
   graph = new TGraph(10,mw1_fx29,mw1_fy29);
   graph->SetName("mw1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mw129 = new TH1F("Graph_mw129","",100,0,0.396);
   Graph_mw129->SetMinimum(0.3788721);
   Graph_mw129->SetMaximum(0.4233427);
   Graph_mw129->SetDirectory(0);
   Graph_mw129->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_mw129->SetLineColor(ci);
   Graph_mw129->GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
   Graph_mw129->GetXaxis()->CenterTitle(true);
   Graph_mw129->GetXaxis()->SetLabelFont(42);
   Graph_mw129->GetXaxis()->SetTitleSize(0.05);
   Graph_mw129->GetXaxis()->SetTitleOffset(1.2);
   Graph_mw129->GetXaxis()->SetTitleFont(42);
   Graph_mw129->GetYaxis()->SetTitle("Width of Recoil Mass [GeV]");
   Graph_mw129->GetYaxis()->CenterTitle(true);
   Graph_mw129->GetYaxis()->SetLabelFont(42);
   Graph_mw129->GetYaxis()->SetTitleSize(0.05);
   Graph_mw129->GetYaxis()->SetTitleOffset(1.2);
   Graph_mw129->GetYaxis()->SetTitleFont(42);
   Graph_mw129->GetZaxis()->SetLabelFont(42);
   Graph_mw129->GetZaxis()->SetTitleSize(0.05);
   Graph_mw129->GetZaxis()->SetTitleOffset(1.2);
   Graph_mw129->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_mw129);
   
   graph->Draw(" l");
   
   Double_t ew2_fx30[2] = {
   0,
   0.36};
   Double_t ew2_fy30[2] = {
   0.4443432,
   0.4443432};
   graph = new TGraph(2,ew2_fx30,ew2_fy30);
   graph->SetName("ew2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_ew230 = new TH1F("Graph_ew230","",100,0,0.396);
   Graph_ew230->SetMinimum(0.3443432);
   Graph_ew230->SetMaximum(1.544343);
   Graph_ew230->SetDirectory(0);
   Graph_ew230->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_ew230->SetLineColor(ci);
   Graph_ew230->GetXaxis()->SetLabelFont(42);
   Graph_ew230->GetXaxis()->SetTitleSize(0.05);
   Graph_ew230->GetXaxis()->SetTitleOffset(1.2);
   Graph_ew230->GetXaxis()->SetTitleFont(42);
   Graph_ew230->GetYaxis()->SetLabelFont(42);
   Graph_ew230->GetYaxis()->SetTitleSize(0.05);
   Graph_ew230->GetYaxis()->SetTitleOffset(1.2);
   Graph_ew230->GetYaxis()->SetTitleFont(42);
   Graph_ew230->GetZaxis()->SetLabelFont(42);
   Graph_ew230->GetZaxis()->SetTitleSize(0.05);
   Graph_ew230->GetZaxis()->SetTitleOffset(1.2);
   Graph_ew230->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_ew230);
   
   graph->Draw(" l");
   
   Double_t mw2_fx31[2] = {
   0,
   0.36};
   Double_t mw2_fy31[2] = {
   0.4230631,
   0.4230631};
   graph = new TGraph(2,mw2_fx31,mw2_fy31);
   graph->SetName("mw2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mw231 = new TH1F("Graph_mw231","",100,0,0.396);
   Graph_mw231->SetMinimum(0.3230631);
   Graph_mw231->SetMaximum(1.523063);
   Graph_mw231->SetDirectory(0);
   Graph_mw231->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_mw231->SetLineColor(ci);
   Graph_mw231->GetXaxis()->SetLabelFont(42);
   Graph_mw231->GetXaxis()->SetTitleSize(0.05);
   Graph_mw231->GetXaxis()->SetTitleOffset(1.2);
   Graph_mw231->GetXaxis()->SetTitleFont(42);
   Graph_mw231->GetYaxis()->SetLabelFont(42);
   Graph_mw231->GetYaxis()->SetTitleSize(0.05);
   Graph_mw231->GetYaxis()->SetTitleOffset(1.2);
   Graph_mw231->GetYaxis()->SetTitleFont(42);
   Graph_mw231->GetZaxis()->SetLabelFont(42);
   Graph_mw231->GetZaxis()->SetTitleSize(0.05);
   Graph_mw231->GetZaxis()->SetTitleOffset(1.2);
   Graph_mw231->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_mw231);
   
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
