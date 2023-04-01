void massError()
{
//=========Macro generated from canvas: c1_n2/c1_n2
//=========  (Sun Mar 26 22:23:10 2023) by ROOT version 6.16/00
   TCanvas *c1_n2 = new TCanvas("c1_n2", "c1_n2",10,64,600,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1_n2->Range(-0.07425,-7.5,0.42075,42.5);
   c1_n2->SetFillColor(0);
   c1_n2->SetBorderMode(0);
   c1_n2->SetBorderSize(2);
   c1_n2->SetLeftMargin(0.15);
   c1_n2->SetRightMargin(0.05);
   c1_n2->SetTopMargin(0.05);
   c1_n2->SetBottomMargin(0.15);
   c1_n2->SetFrameBorderMode(0);
   c1_n2->SetFrameBorderMode(0);
   
   Double_t em1_fx1[10] = {
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
   Double_t em1_fy1[10] = {
   5.681325,
   5.925558,
   6.668889,
   7.2131,
   7.64613,
   8.359359,
   8.90319,
   9.577445,
   10.50626,
   11.08792};
   TGraph *graph = new TGraph(10,em1_fx1,em1_fy1);
   graph->SetName("em1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_em11 = new TH1F("Graph_em11","",100,0,0.396);
   Graph_em11->SetMinimum(0);
   Graph_em11->SetMaximum(40);
   Graph_em11->SetDirectory(0);
   Graph_em11->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_em11->SetLineColor(ci);
   Graph_em11->GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
   Graph_em11->GetXaxis()->CenterTitle(true);
   Graph_em11->GetXaxis()->SetLabelFont(42);
   Graph_em11->GetXaxis()->SetLabelSize(0.03);
   Graph_em11->GetXaxis()->SetTitleOffset(1.5);
   Graph_em11->GetXaxis()->SetTitleFont(42);
   Graph_em11->GetYaxis()->SetTitle("Uncertainty of higgs mass [MeV]");
   Graph_em11->GetYaxis()->CenterTitle(true);
   Graph_em11->GetYaxis()->SetLabelFont(42);
   Graph_em11->GetYaxis()->SetLabelSize(0.03);
   Graph_em11->GetYaxis()->SetTitleOffset(1.5);
   Graph_em11->GetYaxis()->SetTitleFont(42);
   Graph_em11->GetZaxis()->SetLabelFont(42);
   Graph_em11->GetZaxis()->SetLabelSize(0.03);
   Graph_em11->GetZaxis()->SetTitleOffset(1.5);
   Graph_em11->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_em11);
   
   graph->Draw("al");
   
   Double_t mm1_fx2[10] = {
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
   Double_t mm1_fy2[10] = {
   4.956271,
   5.019802,
   5.19728,
   5.416358,
   5.591918,
   5.624268,
   5.706263,
   5.852334,
   5.861484,
   5.92536};
   graph = new TGraph(10,mm1_fx2,mm1_fy2);
   graph->SetName("mm1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mm12 = new TH1F("Graph_mm12","",100,0,0.396);
   Graph_mm12->SetMinimum(4.859362);
   Graph_mm12->SetMaximum(6.022268);
   Graph_mm12->SetDirectory(0);
   Graph_mm12->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_mm12->SetLineColor(ci);
   Graph_mm12->GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
   Graph_mm12->GetXaxis()->CenterTitle(true);
   Graph_mm12->GetXaxis()->SetLabelFont(42);
   Graph_mm12->GetXaxis()->SetLabelSize(0.03);
   Graph_mm12->GetXaxis()->SetTitleOffset(1.5);
   Graph_mm12->GetXaxis()->SetTitleFont(42);
   Graph_mm12->GetYaxis()->SetTitle("Uncertainty of higgs mass [MeV]");
   Graph_mm12->GetYaxis()->CenterTitle(true);
   Graph_mm12->GetYaxis()->SetLabelFont(42);
   Graph_mm12->GetYaxis()->SetLabelSize(0.03);
   Graph_mm12->GetYaxis()->SetTitleOffset(1.5);
   Graph_mm12->GetYaxis()->SetTitleFont(42);
   Graph_mm12->GetZaxis()->SetLabelFont(42);
   Graph_mm12->GetZaxis()->SetLabelSize(0.03);
   Graph_mm12->GetZaxis()->SetTitleOffset(1.5);
   Graph_mm12->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_mm12);
   
   graph->Draw(" l");
   
   Double_t em2_fx3[2] = {
   0,
   0.36};
   Double_t em2_fy3[2] = {
   25.6547,
   25.6547};
   graph = new TGraph(2,em2_fx3,em2_fy3);
   graph->SetName("em2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_em23 = new TH1F("Graph_em23","",100,0,0.396);
   Graph_em23->SetMinimum(25.5547);
   Graph_em23->SetMaximum(26.7547);
   Graph_em23->SetDirectory(0);
   Graph_em23->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_em23->SetLineColor(ci);
   Graph_em23->GetXaxis()->SetLabelFont(42);
   Graph_em23->GetXaxis()->SetLabelSize(0.03);
   Graph_em23->GetXaxis()->SetTitleOffset(1.5);
   Graph_em23->GetXaxis()->SetTitleFont(42);
   Graph_em23->GetYaxis()->SetLabelFont(42);
   Graph_em23->GetYaxis()->SetLabelSize(0.03);
   Graph_em23->GetYaxis()->SetTitleOffset(1.5);
   Graph_em23->GetYaxis()->SetTitleFont(42);
   Graph_em23->GetZaxis()->SetLabelFont(42);
   Graph_em23->GetZaxis()->SetLabelSize(0.03);
   Graph_em23->GetZaxis()->SetTitleOffset(1.5);
   Graph_em23->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_em23);
   
   graph->Draw(" l");
   
   Double_t mm2_fx4[2] = {
   0,
   0.36};
   Double_t mm2_fy4[2] = {
   6.434418,
   6.434418};
   graph = new TGraph(2,mm2_fx4,mm2_fy4);
   graph->SetName("mm2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mm24 = new TH1F("Graph_mm24","",100,0,0.396);
   Graph_mm24->SetMinimum(6.334418);
   Graph_mm24->SetMaximum(7.534418);
   Graph_mm24->SetDirectory(0);
   Graph_mm24->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_mm24->SetLineColor(ci);
   Graph_mm24->GetXaxis()->SetLabelFont(42);
   Graph_mm24->GetXaxis()->SetLabelSize(0.03);
   Graph_mm24->GetXaxis()->SetTitleOffset(1.5);
   Graph_mm24->GetXaxis()->SetTitleFont(42);
   Graph_mm24->GetYaxis()->SetLabelFont(42);
   Graph_mm24->GetYaxis()->SetLabelSize(0.03);
   Graph_mm24->GetYaxis()->SetTitleOffset(1.5);
   Graph_mm24->GetYaxis()->SetTitleFont(42);
   Graph_mm24->GetZaxis()->SetLabelFont(42);
   Graph_mm24->GetZaxis()->SetLabelSize(0.03);
   Graph_mm24->GetZaxis()->SetTitleOffset(1.5);
   Graph_mm24->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_mm24);
   
   graph->Draw(" l");
   
   Double_t com_fx5[10] = {
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
   Double_t com_fy5[10] = {
   3.73482,
   3.830177,
   4.099394,
   4.331203,
   4.513638,
   4.666399,
   4.804207,
   4.993817,
   5.118747,
   5.225947};
   graph = new TGraph(10,com_fx5,com_fy5);
   graph->SetName("com");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_com5 = new TH1F("Graph_com5","",100,0,0.396);
   Graph_com5->SetMinimum(3.585708);
   Graph_com5->SetMaximum(5.37506);
   Graph_com5->SetDirectory(0);
   Graph_com5->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_com5->SetLineColor(ci);
   Graph_com5->GetXaxis()->SetLabelFont(42);
   Graph_com5->GetXaxis()->SetLabelSize(0.03);
   Graph_com5->GetXaxis()->SetTitleOffset(1.5);
   Graph_com5->GetXaxis()->SetTitleFont(42);
   Graph_com5->GetYaxis()->SetLabelFont(42);
   Graph_com5->GetYaxis()->SetLabelSize(0.03);
   Graph_com5->GetYaxis()->SetTitleOffset(1.5);
   Graph_com5->GetYaxis()->SetTitleFont(42);
   Graph_com5->GetZaxis()->SetLabelFont(42);
   Graph_com5->GetZaxis()->SetLabelSize(0.03);
   Graph_com5->GetZaxis()->SetTitleOffset(1.5);
   Graph_com5->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_com5);
   
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
