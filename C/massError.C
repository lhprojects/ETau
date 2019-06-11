void massError()
{
//=========Macro generated from canvas: c1_n2/c1_n2
//=========  (Tue Jun 11 10:37:31 2019) by ROOT version 6.16/00
   TCanvas *c1_n2 = new TCanvas("c1_n2", "c1_n2",10,64,600,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1_n2->Range(-0.07425,-4.6875,0.42075,26.5625);
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
   5.766252,
   5.902995,
   6.318451,
   6.83426,
   7.37934,
   7.897145,
   8.442373,
   8.947475,
   9.454073,
   9.958335};
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
   Graph_em132->SetMaximum(25);
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
   4.305255,
   4.323412,
   4.364613,
   4.394206,
   4.536544,
   4.628868,
   4.715075,
   4.801461,
   4.87429,
   4.948266};
   graph = new TGraph(10,mm1_fx33,mm1_fy33);
   graph->SetName("mm1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mm133 = new TH1F("Graph_mm133","",100,0,0.396);
   Graph_mm133->SetMinimum(4.240954);
   Graph_mm133->SetMaximum(5.012567);
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
   15.14751,
   15.14751};
   graph = new TGraph(2,em2_fx34,em2_fy34);
   graph->SetName("em2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_em234 = new TH1F("Graph_em234","",100,0,0.396);
   Graph_em234->SetMinimum(15.04751);
   Graph_em234->SetMaximum(16.24751);
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
   5.304372,
   5.304372};
   graph = new TGraph(2,mm2_fx35,mm2_fy35);
   graph->SetName("mm2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mm235 = new TH1F("Graph_mm235","",100,0,0.396);
   Graph_mm235->SetMinimum(5.204372);
   Graph_mm235->SetMaximum(6.404372);
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
   3.449777,
   3.487956,
   3.591129,
   3.696126,
   3.864657,
   3.993424,
   4.116559,
   4.230782,
   4.332371,
   4.43135};
   graph = new TGraph(10,com_fx36,com_fy36);
   graph->SetName("com");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_com36 = new TH1F("Graph_com36","",100,0,0.396);
   Graph_com36->SetMinimum(3.35162);
   Graph_com36->SetMaximum(4.529507);
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
