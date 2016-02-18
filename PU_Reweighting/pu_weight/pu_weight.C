#include "TList.h"
#include "TFileInfo.h"
#include "TFileCollection.h"
#include "Rtypes.h"
#include "TLegend.h"
#include "TPad.h"
#include "TLine.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TChain.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1F.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
void Style(TH1* h, const char *xTitle, const char *yTitle)
{
  h->GetXaxis()->SetTitle(xTitle);
  h->GetXaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetTitleColor(1);
  h->GetXaxis()->SetTitleOffset(0.9);
  h->GetXaxis()->SetTitleSize(0.1);
  h->GetXaxis()->SetLabelSize(0.13);
  h->GetXaxis()->SetNdivisions(510);

  h->GetYaxis()->SetTitle(yTitle);
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetYaxis()->SetTitleOffset(0.7);
  h->GetYaxis()->SetTitleSize(0.1);
  h->GetYaxis()->SetLabelSize(0.07);
  h->GetYaxis()->SetNdivisions(510);
}

void Styleratio(TH1* h, const char *xTitle, const char *yTitle)
{
  h->GetXaxis()->SetTitle(xTitle);
  h->GetXaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetTitleColor(1);
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetXaxis()->SetTitleSize(0.18);
  h->GetXaxis()->SetLabelSize(0.13);
  h->GetXaxis()->SetNdivisions(510);

  h->GetYaxis()->SetTitle(yTitle);
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetYaxis()->SetTitleOffset(0.4);
  h->GetYaxis()->SetTitleSize(0.1);
  h->GetYaxis()->SetLabelSize(0.13);
  h->GetYaxis()->SetNdivisions(510);
}
void PUWeight(TFile *histos){
  
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.45);

// Zero horizontal error bars
  gStyle->SetErrorX(0);
 
  //  For the statistics box:
  gStyle->SetOptStat(0);

  //  For the legend
  gStyle->SetLegendBorderSize(0);
  //outputfile
  TFile* outfile=new TFile("PUWeight.root","RECREATE");
  // read histos
  cout << "Reading Histos from file" << endl;  

  TH1F* h_npv_data = (TH1F*)histos->Get("h_npv_data");
  TH1F* h_npv_mc = (TH1F*)histos->Get("h_npv_mc");
  
  
  char text_cms[]="CMS private Work";
  char cutlabel[]="EtaCut";
  TLatex* text=new TLatex();
  text-> SetNDC();
  text-> SetTextFont(42);
  text-> SetTextSize(0.05);  

  char xtitle[]="number of primary vertices";  
  
  float mcevents=0;
  float normratio=0;
  float dataevents=0;
  //makelegend
  
  TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
  leg->AddEntry(h_npv_data,"data");
  leg->AddEntry(h_npv_mc,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
  TLine* line=new TLine(0,1,50,1);
  line->SetLineColor(kBlack);


  
  TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
  TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();   

  
  // ORIGINAL
  mcevents=h_npv_mc->Integral();
  dataevents=h_npv_data->Integral();
  cout << "original:"<<endl;
  cout << "data events: "<< dataevents  << endl;  
  cout << "mcevents : " << mcevents << endl;

  //draw histos
  h_npv_mc->Sumw2();
  h_npv_data->Sumw2();
  h_npv_mc->Draw("histE0");
  h_npv_mc->SetTitle("number of primary vertices");
  h_npv_mc->SetTitleSize(0.08);

  Style(h_npv_mc,"","events");
  h_npv_data->SetMarkerStyle(20);
  h_npv_data->SetMarkerSize(0.5);
  h_npv_data->Draw("SAMEE0");
  leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  TPad* padratio=new TPad("padratio","padratio",0,0,1,0.3);
  padratio->SetTopMargin(0);
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  TH1F* ratio=(TH1F*)h_npv_data->Clone(); 
  ratio->SetTitle("");
  ratio->SetXTitle(xtitle);
  ratio->Sumw2();
  ratio->SetStats(0);
  ratio->Divide(h_npv_mc);
  ratio->SetMarkerStyle(20);
  ratio->SetMarkerSize(0.5);
  ratio->Draw("E0");
  ratio->SetMaximum(2.5);
  ratio->SetMinimum(0);
  
  //set_ratioattributes 
  Styleratio(ratio,"number of primary vertices","data/MC"); 
  line->Draw();  

  c1->SaveAs("h_NPV_original.pdf");
  
  // auf 1 normiert
  mcevents=h_npv_mc->Integral();
  h_npv_mc->Scale(1./mcevents);
  dataevents=h_npv_data->Integral();
  h_npv_data->Scale(1./dataevents);
  cout << "auf 1 normiert:"<<endl;
  cout << "data events: "<< h_npv_data->Integral()  << endl;  
  cout << "mcevents : " << h_npv_mc->Integral() << endl;

  //draw histos
  h_npv_mc->Sumw2();
  h_npv_data->Sumw2();
  h_npv_mc->Draw("histE0");
  h_npv_data->SetMarkerStyle(20);
  h_npv_data->SetMarkerSize(0.5);
  h_npv_data->Draw("SAMEE0");
  leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio
//   TPad* padratio=new TPad("padratio","padratio",0,0,1,0.3);
//   padratio->SetTopMargin(0);
//   padratio->SetBottomMargin(1.1);
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio=(TH1F*)h_npv_data->Clone(); 
  ratio->SetTitle("");
  ratio->SetXTitle(xtitle);
  ratio->Sumw2();
  ratio->SetStats(0);
  ratio->Divide(h_npv_mc);
  ratio->SetMarkerStyle(20);
  ratio->SetMarkerSize(0.5);
  ratio->Draw("E0");
  ratio->SetMaximum(3);
  ratio->SetMinimum(0);
  //set_ratioattributes  
  ratio->GetYaxis()->SetNdivisions(510);
  ratio->GetYaxis()->SetLabelSize(0.1);
  ratio->GetXaxis()->SetTitle(xtitle);
  ratio->GetXaxis()->SetTitleSize(0.11);
  ratio->GetXaxis()->SetNdivisions(510);
  ratio->GetXaxis()->SetLabelSize(0.1);    
  line->Draw();  

  c1->SaveAs("h_NPV_normed.pdf");
  c1->cd();
  ratio->Draw("E0");
  ratio->SetName("PUWeight");
  ratio->GetXaxis()->SetTitleSize(0.01);
  ratio->GetYaxis()->SetTitleSize(0.01);
  ratio->SetMaximum(ratio->GetMaximum()+1);
  ratio->SetMinimum(ratio->GetMinimum()-1);
  c1->SaveAs("PUWeight.pdf");
  outfile->Write();
  
  
  
}
  











int main(){
  TFile* histos=new TFile("../analysetrees/histos.root");  
  PUWeight(histos);

}