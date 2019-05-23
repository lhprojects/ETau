{

  //ild TStyle
  TStyle* ildStyle = new  TStyle("ildStyle", "ILD Style");

  //set the background color to white
  ildStyle->SetFillColor(10);
  ildStyle->SetFrameFillColor(10);
  ildStyle->SetCanvasColor(10);
  ildStyle->SetPadColor(10);
  ildStyle->SetTitleFillColor(0);
  //ildStyle->SetStatColor(10);

  //dont put a colored frame around the plots
  ildStyle->SetFrameBorderMode(0);
  ildStyle->SetCanvasBorderMode(0);
  ildStyle->SetPadBorderMode(0);
  ildStyle->SetLegendBorderSize(0);

  //use the primary color palette
  const Int_t NRGBs = 5;
  //const Int_t NCont = 255;
  const Int_t NCont = 200;
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  
  //const int NRGBs = 7, NCont = 999;
  //ildStyle->SetNumberContours(NCont);
  //Double_t stops[NRGBs] = { 0.00, 0.10, 0.25, 0.45, 0.60, 0.75, 1.00 };
  //Double_t red[NRGBs]   = { 1.00, 0.00, 0.00, 0.00, 0.97, 0.97, 0.10 };
  //Double_t green[NRGBs] = { 1.00, 0.97, 0.30, 0.40, 0.97, 0.00, 0.00 };
  //Double_t blue[NRGBs]  = { 1.00, 0.97, 0.97, 0.00, 0.00, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  ildStyle->SetNumberContours(NCont); 
  
  //set the default line color for a histogram to be black
  ildStyle->SetHistLineColor(kBlue+3);
  
  //set the default marker color 
  //ildStyle->SetMarkerColor(kBlue+3);

  //set the default line color for a fit function to be red
  ildStyle->SetFuncColor(kOrange-3);

  //make the axis labels black
  ildStyle->SetLabelColor(kBlack,"xyz");
  
  //set the default title color to be black
  ildStyle->SetTitleColor(kBlack);
  
  //set the margins
  ildStyle->SetPadBottomMargin(0.15);
  ildStyle->SetPadTopMargin(0.15);
  ildStyle->SetPadRightMargin(0.05);
  ildStyle->SetPadLeftMargin(0.15);

  //set axis label and title text sizes
  ildStyle->SetLabelFont(22,"xyz");
  ildStyle->SetLabelSize(0.03,"xyz");
  ildStyle->SetLabelOffset(0.015,"xyz");
  ildStyle->SetTitleFont(22,"xyz");
  ildStyle->SetTitleSize(0.04,"xyz");
  ildStyle->SetTitleOffset(1.0,"yz");
  ildStyle->SetTitleOffset(1.0,"x");
  ildStyle->SetTitleX(0.08);
  ildStyle->SetTitleH(0.08);
  ildStyle->SetTitleW(0.5);
  ildStyle->SetStatFont(42);
  ildStyle->SetStatFontSize(0.07);
  ildStyle->SetTitleBorderSize(0);
  ildStyle->SetStatBorderSize(0);
  ildStyle->SetTextFont(20);
  //ildstyle 
  
  //gStyle->SetStatStyle(1001); // filled
  ildStyle->SetStatBorderSize(0);
  ildStyle->SetStatColor(0);
  ildStyle->SetStatStyle(0);
  ildStyle->SetStatW(0.25);
  ildStyle->SetStatH(0.125);
  //gStyle->SetStatX(0.90);
  //gStyle->SetStatY(0.90);
  //ildStyle->SetStatX(1.0-ildStyle->GetPadRightMargin()-0.02);
  //ildStyle->SetStatY(1.0-ildStyle->GetPadTopMargin()-0.02);
  
  
  //set line widths
  ildStyle->SetFrameLineWidth(3);
  ildStyle->SetFuncWidth(2);
  ildStyle->SetHistLineWidth(2);

  //set the number of divisions to show
  ildStyle->SetNdivisions(506, "xy");
  
  //turn off xy grids
  ildStyle->SetPadGridX(1);
  ildStyle->SetPadGridY(1);
  ildStyle->SetGridColor(kGray);

  
  //set the tick mark style
  ildStyle->SetPadTickX(1);
  ildStyle->SetPadTickY(1);

  
  //turn off stats
  //ildStyle->SetOptStat(11100);
  ildStyle->SetOptStat(1);
  ildStyle->SetOptFit(00100);
  //ildStyle->SetOptFit(01100); // with chi2
  //ildStyle->SetOptTitle(0);
  //marker settings
  ildStyle->SetMarkerStyle(20);
  ildStyle->SetMarkerSize(0.7);
  ildStyle->SetLineWidth(2); 

  //done
  ildStyle->cd();
  gROOT->ForceStyle();
  gStyle->ls();

}
