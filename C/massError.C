void massError()
{
//=========Macro generated from canvas: c1_n2/c1_n2
//=========  (Mon Jun 10 18:34:27 2019) by ROOT version 6.16/00
   TCanvas *c1_n2 = new TCanvas("c1_n2", "c1_n2",0,0,600,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1_n2->Range(-0.07425,-8.4375,0.42075,47.8125);
   c1_n2->SetFillColor(0);
   c1_n2->SetBorderMode(0);
   c1_n2->SetBorderSize(2);
   c1_n2->SetLeftMargin(0.15);
   c1_n2->SetRightMargin(0.05);
   c1_n2->SetTopMargin(0.05);
   c1_n2->SetBottomMargin(0.15);
   c1_n2->SetFrameBorderMode(0);
   c1_n2->SetFrameBorderMode(0);
   
   Double_t em1_fx32[10] = {
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
   Double_t em1_fy32[10] = {
   7.170276,
   7.352305,
   7.983605,
   8.900609,
   9.592559,
   10.1828,
   10.77161,
   11.23555,
   12.31635,
   12.88253};
   TGraph *graph = new TGraph(10,em1_fx32,em1_fy32);
   graph->SetName("em1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_em132 = new TH1F("Graph_em132","",100,0,0.396);
   Graph_em132->SetMinimum(0);
   Graph_em132->SetMaximum(45);
   Graph_em132->SetDirectory(0);
   Graph_em132->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_em132->SetLineColor(ci);
   Graph_em132->GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
   Graph_em132->GetXaxis()->CenterTitle(true);
   Graph_em132->GetXaxis()->SetLabelFont(42);
   Graph_em132->GetXaxis()->SetTitleSize(0.05);
   Graph_em132->GetXaxis()->SetTitleOffset(1.2);
   Graph_em132->GetXaxis()->SetTitleFont(42);
   Graph_em132->GetYaxis()->SetTitle("Uncertainty of Higgs Mass [MeV]");
   Graph_em132->GetYaxis()->CenterTitle(true);
   Graph_em132->GetYaxis()->SetLabelFont(42);
   Graph_em132->GetYaxis()->SetTitleSize(0.05);
   Graph_em132->GetYaxis()->SetTitleOffset(1.2);
   Graph_em132->GetYaxis()->SetTitleFont(42);
   Graph_em132->GetZaxis()->SetLabelFont(42);
   Graph_em132->GetZaxis()->SetTitleSize(0.05);
   Graph_em132->GetZaxis()->SetTitleOffset(1.2);
   Graph_em132->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_em132);
   
   graph->Draw("al");
   
   Double_t mm1_fx33[10] = {
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
   Double_t mm1_fy33[10] = {
   4.703845,
   4.865472,
   4.967887,
   5.254921,
   5.483663,
   5.2573,
   5.418004,
   5.608323,
   5.727129,
   5.710606};
   graph = new TGraph(10,mm1_fx33,mm1_fy33);
   graph->SetName("mm1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mm133 = new TH1F("Graph_mm133","",100,0,0.396);
   Graph_mm133->SetMinimum(4.601517);
   Graph_mm133->SetMaximum(5.829457);
   Graph_mm133->SetDirectory(0);
   Graph_mm133->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_mm133->SetLineColor(ci);
   Graph_mm133->GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
   Graph_mm133->GetXaxis()->CenterTitle(true);
   Graph_mm133->GetXaxis()->SetLabelFont(42);
   Graph_mm133->GetXaxis()->SetTitleSize(0.05);
   Graph_mm133->GetXaxis()->SetTitleOffset(1.2);
   Graph_mm133->GetXaxis()->SetTitleFont(42);
   Graph_mm133->GetYaxis()->SetTitle("Uncertainty of Higgs Mass [MeV]");
   Graph_mm133->GetYaxis()->CenterTitle(true);
   Graph_mm133->GetYaxis()->SetLabelFont(42);
   Graph_mm133->GetYaxis()->SetTitleSize(0.05);
   Graph_mm133->GetYaxis()->SetTitleOffset(1.2);
   Graph_mm133->GetYaxis()->SetTitleFont(42);
   Graph_mm133->GetZaxis()->SetLabelFont(42);
   Graph_mm133->GetZaxis()->SetTitleSize(0.05);
   Graph_mm133->GetZaxis()->SetTitleOffset(1.2);
   Graph_mm133->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_mm133);
   
   graph->Draw(" l");
   
   Double_t em2_fx34[2] = {
   0,
   0.36};
   Double_t em2_fy34[2] = {
   33.01848,
   33.01848};
   graph = new TGraph(2,em2_fx34,em2_fy34);
   graph->SetName("em2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_em234 = new TH1F("Graph_em234","",100,0,0.396);
   Graph_em234->SetMinimum(32.91848);
   Graph_em234->SetMaximum(34.11848);
   Graph_em234->SetDirectory(0);
   Graph_em234->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_em234->SetLineColor(ci);
   Graph_em234->GetXaxis()->SetLabelFont(42);
   Graph_em234->GetXaxis()->SetTitleSize(0.05);
   Graph_em234->GetXaxis()->SetTitleOffset(1.2);
   Graph_em234->GetXaxis()->SetTitleFont(42);
   Graph_em234->GetYaxis()->SetLabelFont(42);
   Graph_em234->GetYaxis()->SetTitleSize(0.05);
   Graph_em234->GetYaxis()->SetTitleOffset(1.2);
   Graph_em234->GetYaxis()->SetTitleFont(42);
   Graph_em234->GetZaxis()->SetLabelFont(42);
   Graph_em234->GetZaxis()->SetTitleSize(0.05);
   Graph_em234->GetZaxis()->SetTitleOffset(1.2);
   Graph_em234->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_em234);
   
   graph->Draw(" l");
   
   Double_t mm2_fx35[2] = {
   0,
   0.36};
   Double_t mm2_fy35[2] = {
   6.26724,
   6.26724};
   graph = new TGraph(2,mm2_fx35,mm2_fy35);
   graph->SetName("mm2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mm235 = new TH1F("Graph_mm235","",100,0,0.396);
   Graph_mm235->SetMinimum(6.16724);
   Graph_mm235->SetMaximum(7.36724);
   Graph_mm235->SetDirectory(0);
   Graph_mm235->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_mm235->SetLineColor(ci);
   Graph_mm235->GetXaxis()->SetLabelFont(42);
   Graph_mm235->GetXaxis()->SetTitleSize(0.05);
   Graph_mm235->GetXaxis()->SetTitleOffset(1.2);
   Graph_mm235->GetXaxis()->SetTitleFont(42);
   Graph_mm235->GetYaxis()->SetLabelFont(42);
   Graph_mm235->GetYaxis()->SetTitleSize(0.05);
   Graph_mm235->GetYaxis()->SetTitleOffset(1.2);
   Graph_mm235->GetYaxis()->SetTitleFont(42);
   Graph_mm235->GetZaxis()->SetLabelFont(42);
   Graph_mm235->GetZaxis()->SetTitleSize(0.05);
   Graph_mm235->GetZaxis()->SetTitleOffset(1.2);
   Graph_mm235->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_mm235);
   
   graph->Draw(" l");
   
   Double_t com_fx36[10] = {
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
   Double_t com_fy36[10] = {
   3.933055,
   4.05748,
   4.217944,
   4.525109,
   4.760682,
   4.671434,
   4.840208,
   5.017924,
   5.193135,
   5.220666};
   graph = new TGraph(10,com_fx36,com_fy36);
   graph->SetName("com");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_com36 = new TH1F("Graph_com36","",100,0,0.396);
   Graph_com36->SetMinimum(3.804293);
   Graph_com36->SetMaximum(5.349427);
   Graph_com36->SetDirectory(0);
   Graph_com36->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_com36->SetLineColor(ci);
   Graph_com36->GetXaxis()->SetLabelFont(42);
   Graph_com36->GetXaxis()->SetTitleSize(0.05);
   Graph_com36->GetXaxis()->SetTitleOffset(1.2);
   Graph_com36->GetXaxis()->SetTitleFont(42);
   Graph_com36->GetYaxis()->SetLabelFont(42);
   Graph_com36->GetYaxis()->SetTitleSize(0.05);
   Graph_com36->GetYaxis()->SetTitleOffset(1.2);
   Graph_com36->GetYaxis()->SetTitleFont(42);
   Graph_com36->GetZaxis()->SetLabelFont(42);
   Graph_com36->GetZaxis()->SetTitleSize(0.05);
   Graph_com36->GetZaxis()->SetTitleOffset(1.2);
   Graph_com36->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_com36);
   
   graph->Draw(" l");
   
   TLegend *leg = new TLegend(0.52,0.7,0.92,0.92,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("em1","eeH (w/ FSR&BS)","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mm1","#mu#muH (w/ FSR&BS)","L");

   ci = TColor::GetColor("#00ff00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("em2","eeH (w/o FSR&BS)","L");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mm2","#mu#muH (w/o FSR&BS)","L");

   ci = TColor::GetColor("#00ff00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("com","Combined (w/ FSR&BS)","L");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
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
