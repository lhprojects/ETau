void massError()
{
//=========Macro generated from canvas: c1_n2/c1_n2
//=========  (Thu May 23 17:11:56 2019) by ROOT version 6.16/00
   TCanvas *c1_n2 = new TCanvas("c1_n2", "c1_n2",0,0,600,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1_n2->Range(-0.037125,-4.6875,0.210375,26.5625);
   c1_n2->SetFillColor(0);
   c1_n2->SetBorderMode(0);
   c1_n2->SetBorderSize(2);
   c1_n2->SetLeftMargin(0.15);
   c1_n2->SetRightMargin(0.05);
   c1_n2->SetTopMargin(0.05);
   c1_n2->SetBottomMargin(0.15);
   c1_n2->SetFrameBorderMode(0);
   c1_n2->SetFrameBorderMode(0);
   
   Double_t em1_fx5[10] = {
   0,
   0.02,
   0.04,
   0.06,
   0.08,
   0.1,
   0.12,
   0.14,
   0.16,
   0.18};
   Double_t em1_fy5[10] = {
   3.453858,
   3.570025,
   3.943477,
   4.37299,
   4.833636,
   5.323753,
   5.815521,
   6.350463,
   6.839639,
   7.273441};
   TGraph *graph = new TGraph(10,em1_fx5,em1_fy5);
   graph->SetName("em1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_em15 = new TH1F("Graph_em15","",100,0,0.198);
   Graph_em15->SetMinimum(0);
   Graph_em15->SetMaximum(25);
   Graph_em15->SetDirectory(0);
   Graph_em15->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_em15->SetLineColor(ci);
   Graph_em15->GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
   Graph_em15->GetXaxis()->CenterTitle(true);
   Graph_em15->GetXaxis()->SetLabelFont(42);
   Graph_em15->GetXaxis()->SetTitleSize(0.05);
   Graph_em15->GetXaxis()->SetTitleOffset(1.2);
   Graph_em15->GetXaxis()->SetTitleFont(42);
   Graph_em15->GetYaxis()->SetTitle("Uncertainty of Higgs Mass [MeV]");
   Graph_em15->GetYaxis()->CenterTitle(true);
   Graph_em15->GetYaxis()->SetLabelFont(42);
   Graph_em15->GetYaxis()->SetTitleSize(0.05);
   Graph_em15->GetYaxis()->SetTitleOffset(1.2);
   Graph_em15->GetYaxis()->SetTitleFont(42);
   Graph_em15->GetZaxis()->SetLabelFont(42);
   Graph_em15->GetZaxis()->SetTitleSize(0.05);
   Graph_em15->GetZaxis()->SetTitleOffset(1.2);
   Graph_em15->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_em15);
   
   graph->Draw("al");
   
   Double_t mm1_fx6[10] = {
   0,
   0.02,
   0.04,
   0.06,
   0.08,
   0.1,
   0.12,
   0.14,
   0.16,
   0.18};
   Double_t mm1_fy6[10] = {
   4.979554,
   4.987705,
   5.093805,
   5.1529,
   5.265914,
   5.505264,
   5.433621,
   5.492777,
   5.581868,
   5.651869};
   graph = new TGraph(10,mm1_fx6,mm1_fy6);
   graph->SetName("mm1");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mm16 = new TH1F("Graph_mm16","",100,0,0.198);
   Graph_mm16->SetMinimum(4.912323);
   Graph_mm16->SetMaximum(5.7191);
   Graph_mm16->SetDirectory(0);
   Graph_mm16->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_mm16->SetLineColor(ci);
   Graph_mm16->GetXaxis()->SetTitle("a (#sigma(E_{#gamma})/E_{#gamma} = a/#sqrt{E_{#gamma}})");
   Graph_mm16->GetXaxis()->CenterTitle(true);
   Graph_mm16->GetXaxis()->SetLabelFont(42);
   Graph_mm16->GetXaxis()->SetTitleSize(0.05);
   Graph_mm16->GetXaxis()->SetTitleOffset(1.2);
   Graph_mm16->GetXaxis()->SetTitleFont(42);
   Graph_mm16->GetYaxis()->SetTitle("Uncertainty of Higgs Mass [MeV]");
   Graph_mm16->GetYaxis()->CenterTitle(true);
   Graph_mm16->GetYaxis()->SetLabelFont(42);
   Graph_mm16->GetYaxis()->SetTitleSize(0.05);
   Graph_mm16->GetYaxis()->SetTitleOffset(1.2);
   Graph_mm16->GetYaxis()->SetTitleFont(42);
   Graph_mm16->GetZaxis()->SetLabelFont(42);
   Graph_mm16->GetZaxis()->SetTitleSize(0.05);
   Graph_mm16->GetZaxis()->SetTitleOffset(1.2);
   Graph_mm16->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_mm16);
   
   graph->Draw(" l");
   
   Double_t em2_fx7[2] = {
   0,
   0.18};
   Double_t em2_fy7[2] = {
   15.84497,
   15.84497};
   graph = new TGraph(2,em2_fx7,em2_fy7);
   graph->SetName("em2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_em27 = new TH1F("Graph_em27","",100,0,0.198);
   Graph_em27->SetMinimum(15.74497);
   Graph_em27->SetMaximum(16.94497);
   Graph_em27->SetDirectory(0);
   Graph_em27->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_em27->SetLineColor(ci);
   Graph_em27->GetXaxis()->SetLabelFont(42);
   Graph_em27->GetXaxis()->SetTitleSize(0.05);
   Graph_em27->GetXaxis()->SetTitleOffset(1.2);
   Graph_em27->GetXaxis()->SetTitleFont(42);
   Graph_em27->GetYaxis()->SetLabelFont(42);
   Graph_em27->GetYaxis()->SetTitleSize(0.05);
   Graph_em27->GetYaxis()->SetTitleOffset(1.2);
   Graph_em27->GetYaxis()->SetTitleFont(42);
   Graph_em27->GetZaxis()->SetLabelFont(42);
   Graph_em27->GetZaxis()->SetTitleSize(0.05);
   Graph_em27->GetZaxis()->SetTitleOffset(1.2);
   Graph_em27->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_em27);
   
   graph->Draw(" l");
   
   Double_t mm2_fx8[2] = {
   0,
   0.18};
   Double_t mm2_fy8[2] = {
   6.538403,
   6.538403};
   graph = new TGraph(2,mm2_fx8,mm2_fy8);
   graph->SetName("mm2");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#00ff00");
   graph->SetLineColor(ci);
   graph->SetLineStyle(2);
   graph->SetLineWidth(2);
   
   TH1F *Graph_mm28 = new TH1F("Graph_mm28","",100,0,0.198);
   Graph_mm28->SetMinimum(6.438403);
   Graph_mm28->SetMaximum(7.638403);
   Graph_mm28->SetDirectory(0);
   Graph_mm28->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_mm28->SetLineColor(ci);
   Graph_mm28->GetXaxis()->SetLabelFont(42);
   Graph_mm28->GetXaxis()->SetTitleSize(0.05);
   Graph_mm28->GetXaxis()->SetTitleOffset(1.2);
   Graph_mm28->GetXaxis()->SetTitleFont(42);
   Graph_mm28->GetYaxis()->SetLabelFont(42);
   Graph_mm28->GetYaxis()->SetTitleSize(0.05);
   Graph_mm28->GetYaxis()->SetTitleOffset(1.2);
   Graph_mm28->GetYaxis()->SetTitleFont(42);
   Graph_mm28->GetZaxis()->SetLabelFont(42);
   Graph_mm28->GetZaxis()->SetTitleSize(0.05);
   Graph_mm28->GetZaxis()->SetTitleOffset(1.2);
   Graph_mm28->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_mm28);
   
   graph->Draw(" l");
   
   Double_t com_fx9[10] = {
   0,
   0.02,
   0.04,
   0.06,
   0.08,
   0.1,
   0.12,
   0.14,
   0.16,
   0.18};
   Double_t com_fy9[10] = {
   2.838007,
   2.903016,
   3.118235,
   3.334179,
   3.560928,
   3.827022,
   3.970301,
   4.154377,
   4.324524,
   4.462876};
   graph = new TGraph(10,com_fx9,com_fy9);
   graph->SetName("com");
   graph->SetTitle("");
   graph->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_com9 = new TH1F("Graph_com9","",100,0,0.198);
   Graph_com9->SetMinimum(2.67552);
   Graph_com9->SetMaximum(4.625363);
   Graph_com9->SetDirectory(0);
   Graph_com9->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_com9->SetLineColor(ci);
   Graph_com9->GetXaxis()->SetLabelFont(42);
   Graph_com9->GetXaxis()->SetTitleSize(0.05);
   Graph_com9->GetXaxis()->SetTitleOffset(1.2);
   Graph_com9->GetXaxis()->SetTitleFont(42);
   Graph_com9->GetYaxis()->SetLabelFont(42);
   Graph_com9->GetYaxis()->SetTitleSize(0.05);
   Graph_com9->GetYaxis()->SetTitleOffset(1.2);
   Graph_com9->GetYaxis()->SetTitleFont(42);
   Graph_com9->GetZaxis()->SetLabelFont(42);
   Graph_com9->GetZaxis()->SetTitleSize(0.05);
   Graph_com9->GetZaxis()->SetTitleOffset(1.2);
   Graph_com9->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_com9);
   
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
