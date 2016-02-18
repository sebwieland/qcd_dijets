
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

void ratioplot(TFile *histos){

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
  
/////BEGIN HERE:  
  TH1F* h_pt3_pt3cut_data = (TH1F*)histos->Get("h_pt3_pt3cut_data");
  TH1F* h_pt3_pt3cut = (TH1F*)histos->Get("h_pt3_pt3cut");
  TH1F* h_pt3 = (TH1F*)histos->Get("h_pt3");
  TH1F* h_pt3_data = (TH1F*)histos->Get("h_pt3_data");

    TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
  leg->AddEntry(h_pt3_pt3cut_data,"data");
  leg->AddEntry(h_pt3_pt3cut,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
  TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
  TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  float mcevents=h_pt3_pt3cut->Integral();
  float dataevents=h_pt3_pt3cut_data->Integral();
  cout << "pt3 with pt3 Cut"<<endl;
  cout << "data events: "<< dataevents  << endl;  
  cout << "mcevents : " << mcevents << endl;  
  
  TLine* line=new TLine(0,1,1000,1);
  line->SetLineColor(kBlack);
  char text_cms[]="CMS private Work";
  char cutlabel[]="Dijet selection";
  TLatex* text=new TLatex();
  text-> SetNDC();
  text-> SetTextFont(42);
  text-> SetTextSize(0.05);
  
  char xtitle[]="p_{T}^{Avg}";
//     //draw histos
  h_pt3_pt3cut->Sumw2();
  h_pt3_pt3cut_data->Sumw2();
  h_pt3_pt3cut->Draw("histE0");
  Style(h_pt3_pt3cut,"","events");
  h_pt3_pt3cut_data->SetMarkerStyle(20);
  h_pt3_pt3cut_data->SetMarkerSize(0.5);
  h_pt3_pt3cut_data->Draw("SAMEE0");
  
  leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  
  c1->cd();
  //makepadratio
  TPad* padratio=new TPad("padratio","padratio",0,0,1,0.3);
  padratio->SetTopMargin(0);
//   padratio->SetBottomMargin(0.3);
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  TH1F* ratio=(TH1F*)h_pt3_pt3cut_data->Clone(); 
  ratio->SetTitle("");
  ratio->SetXTitle(xtitle);
  ratio->Sumw2();
  ratio->Divide(h_pt3_pt3cut);
  ratio->Draw("E0");
  ratio->SetMaximum(1.6);
  ratio->SetMinimum(0.4);
  //set_ratioattributes  
  Styleratio(ratio,xtitle,"data/MC");
  line->Draw();  
  c1->SaveAs("h_pt3_pt3cut.pdf");

  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_pt3_data,"data");
//   leg->AddEntry(h_pt3,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_pt3->Integral();
  dataevents=h_pt3_data->Integral();
  cout << "pt3"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl; 
  
//   xtitle="Pt 3rd Jet";
//     //draw histos
  h_pt3->Sumw2();
  h_pt3_data->Sumw2();
  h_pt3->Draw("histE0");
  h_pt3_data->SetMarkerStyle(20);
  h_pt3_data->SetMarkerSize(0.5);
  h_pt3_data->Draw("SAMEE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio

  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  TH1F* ratio2=(TH1F*)h_pt3_data->Clone(); 
  ratio2->SetTitle("");
  ratio2->SetXTitle(xtitle);
  ratio2->Sumw2();
  ratio2->SetStats(0);
  ratio2->Divide(h_pt3);
  ratio2->SetMarkerStyle(20);
  ratio2->SetMarkerSize(0.5);
  ratio2->Draw("E0");
  ratio2->SetMaximum(1.6);
  ratio2->SetMinimum(0.4);
  //set_ratioattributes  
  ratio2->GetYaxis()->SetNdivisions(510);
  ratio2->GetYaxis()->SetLabelSize(0.1);
  ratio2->GetXaxis()->SetTitle(xtitle);
  ratio2->GetXaxis()->SetTitleSize(0.2);
  ratio2->GetXaxis()->SetNdivisions(510);
  ratio2->GetXaxis()->SetLabelSize(0.1);    
  line->Draw();  
  c1->SaveAs("h_pt3.pdf");
  
  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  TH1F* h_pt3overavg_data = (TH1F*)histos->Get("h_pt3overavg_data");
  TH1F* h_pt3overavg = (TH1F*)histos->Get("h_pt3overavg");
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_pt3overavg_data,"data");
//   leg->AddEntry(h_pt3overavg,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_pt3overavg->Integral();
  dataevents=h_pt3overavg_data->Integral();
  cout << "pt3overavg"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl;  
//   xtitle="Pt 3rd Jet";
//     //draw histos
//   h_pt3overavg->Sumw2();
//   h_pt3overavg_data->Sumw2();
  h_pt3overavg->Draw("histE0");
  h_pt3overavg_data->SetMarkerStyle(20);
  h_pt3overavg_data->SetMarkerSize(0.5);
  h_pt3overavg_data->Draw("sameE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio

  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  TH1F* ratio3=(TH1F*)h_pt3overavg_data->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_pt3overavg);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
//   ratio3->GetYaxis()->SetNdivisions(510);
//   ratio3->GetYaxis()->SetLabelSize(0.1);
//   ratio3->GetXaxis()->SetTitle(xtitle);
//   ratio3->GetXaxis()->SetTitleSize(0.2);
//   ratio3->GetXaxis()->SetNdivisions(510);
//   ratio3->GetXaxis()->SetLabelSize(0.1);    
  line->Draw();  
  c1->SaveAs("h_pt3overavg.pdf");
  
  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  TLine* lineeta=new TLine(-5,1,5,1);
  line->SetLineColor(kBlack);
  TH1F* h_eta0_data = (TH1F*)histos->Get("h_eta0_data");
  TH1F* h_eta0 = (TH1F*)histos->Get("h_eta0");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_eta0->Integral();
  dataevents=h_eta0_data->Integral();
  cout << "eta0"<<endl;
  cout << "data events: "<< dataevents  << endl;  
  cout << "mcevents : " << mcevents << endl;  
  h_eta0->Draw("histE0");
  Style(h_eta0,"","events");
  h_eta0->SetTitle("#eta of hardest Jet");
  h_eta0->SetStats(0);
  
  h_eta0_data->SetMarkerStyle(20);
  h_eta0_data->SetMarkerSize(0.5);
  h_eta0_data->Draw("sameE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio

  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio3=(TH1F*)h_eta0_data->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_eta0);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
  Styleratio(ratio3,"#eta of hardest Jet","data/MC");  
  lineeta->Draw();  
  c1->SaveAs("h_eta0.pdf");
  
    ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  line->SetLineColor(kBlack);
  TH1F* h_eta1_data = (TH1F*)histos->Get("h_eta1_data");
  TH1F* h_eta1 = (TH1F*)histos->Get("h_eta1");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

  c1->cd();
  //makepadhist
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_eta1->Integral();
  dataevents=h_eta1_data->Integral();
  cout << "eta1"<<endl;
  cout << "data events: "<< dataevents  << endl;  
  cout << "mcevents : " << mcevents << endl;  
  
  h_eta1->Draw("histE0");
  Style(h_eta1,"","events"); 
  h_eta1->SetTitle("#eta of 2nd-hardest Jet");
  h_eta1->SetStats(0);  
  h_eta1_data->SetMarkerStyle(20);
  h_eta1_data->SetMarkerSize(0.5);
  h_eta1_data->Draw("sameE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio

  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio3=(TH1F*)h_eta1_data->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_eta1);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
  Styleratio(ratio3,"#eta of 2nd-hardest Jet","data/MC");

  
  lineeta->Draw();  
  c1->SaveAs("h_eta1.pdf");
  
   ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/

  line->SetLineColor(kBlack);
  TH1F* h_eta2_data = (TH1F*)histos->Get("h_eta2_data");
  TH1F* h_eta2 = (TH1F*)histos->Get("h_eta2");
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_eta2_data,"data");
//   leg->AddEntry(h_eta2,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_eta2->Integral();
  dataevents=h_eta2_data->Integral();
  cout << "eta2"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl;  
//   xtitle="Pt 3rd Jet";
//     //draw histos
//   h_eta2->Sumw2();
//   h_eta2_data->Sumw2();
  h_eta2->Draw("histE0");
  h_eta2_data->SetMarkerStyle(20);
  h_eta2_data->SetMarkerSize(0.5);
  h_eta2_data->Draw("sameE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio

  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio3=(TH1F*)h_eta2_data->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_eta2);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
  ratio3->GetYaxis()->SetNdivisions(510);
  ratio3->GetYaxis()->SetLabelSize(0.1);
  ratio3->GetXaxis()->SetTitle(xtitle);
  ratio3->GetXaxis()->SetTitleSize(0.2);
  ratio3->GetXaxis()->SetNdivisions(510);
  ratio3->GetXaxis()->SetLabelSize(0.1);    
  lineeta->Draw();  
  c1->SaveAs("h_eta2.pdf");
  
  //////////////////////////////
  ////////////Etacut////////////
  //////////////////////////////
  TH1F* h_pt3_pt3cut_data_etacut = (TH1F*)histos->Get("h_pt3_pt3cut_data_etacut");
  TH1F* h_pt3_pt3cut_etacut = (TH1F*)histos->Get("h_pt3_pt3cut_etacut");


//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_pt3_pt3cut_data_etacut,"data");
//   leg->AddEntry(h_pt3_pt3cut_etacut,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  

  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_pt3_pt3cut_etacut->Integral();
  dataevents=h_pt3_pt3cut_data_etacut->Integral();
  cout << "pt3 with pt3 Cut and etacut"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl;
  
  

  text-> SetNDC();
  text-> SetTextFont(42);
  text-> SetTextSize(0.05);
  
//   char xtitle[]="Pt 3rd Jet";
//     //draw histos
  h_pt3_pt3cut_etacut->Sumw2();
  h_pt3_pt3cut_data_etacut->Sumw2();
  h_pt3_pt3cut_etacut->Draw("histE0");
  h_pt3_pt3cut_data_etacut->SetMarkerStyle(20);
  h_pt3_pt3cut_data_etacut->SetMarkerSize(0.5);
  h_pt3_pt3cut_data_etacut->Draw("SAMEE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio

  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio=(TH1F*)h_pt3_pt3cut_data_etacut->Clone(); 
  ratio->SetTitle("");
  ratio->SetXTitle(xtitle);
  ratio->Sumw2();
  ratio->SetStats(0);
  ratio->Divide(h_pt3_pt3cut_etacut);
  ratio->SetMarkerStyle(20);
  ratio->SetMarkerSize(0.5);
  ratio->Draw("E0");
  ratio->SetMaximum(1.6);
  ratio->SetMinimum(0.4);
  //set_ratioattributes  
  ratio->GetYaxis()->SetNdivisions(510);
  ratio->GetYaxis()->SetLabelSize(0.1);
  ratio->GetXaxis()->SetTitle(xtitle);
  ratio->GetXaxis()->SetTitleSize(0.2);
  ratio->GetXaxis()->SetNdivisions(510);
  ratio->GetXaxis()->SetLabelSize(0.1);    
  line->Draw();  

  c1->SaveAs("h_pt3_pt3cut_etacut.pdf");

  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  TH1F* h_pt3_etacut = (TH1F*)histos->Get("h_pt3_etacut");
  TH1F* h_pt3_data_etacut = (TH1F*)histos->Get("h_pt3_data_etacut");
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_pt3_data_etacut,"data");
//   leg->AddEntry(h_pt3_etacut,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_pt3_etacut->Integral();
  dataevents=h_pt3_data_etacut->Integral();
  cout << "pt3_etacut"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl; 
  
//   xtitle="Pt 3rd Jet";
//     //draw histos
  h_pt3_etacut->Sumw2();
  h_pt3_data_etacut->Sumw2();
  h_pt3_etacut->Draw("histE0");
  h_pt3_data_etacut->SetMarkerStyle(20);
  h_pt3_data_etacut->SetMarkerSize(0.5);
  h_pt3_data_etacut->Draw("SAMEE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio

  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio2=(TH1F*)h_pt3_data_etacut->Clone(); 
  ratio2->SetTitle("");
  ratio2->SetXTitle(xtitle);
  ratio2->Sumw2();
  ratio2->SetStats(0);
  ratio2->Divide(h_pt3_etacut);
  ratio2->SetMarkerStyle(20);
  ratio2->SetMarkerSize(0.5);
  ratio2->Draw("E0");
  ratio2->SetMaximum(1.6);
  ratio2->SetMinimum(0.4);
  //set_ratioattributes  
  ratio2->GetYaxis()->SetNdivisions(510);
  ratio2->GetYaxis()->SetLabelSize(0.1);
  ratio2->GetXaxis()->SetTitle(xtitle);
  ratio2->GetXaxis()->SetTitleSize(0.2);
  ratio2->GetXaxis()->SetNdivisions(510);
  ratio2->GetXaxis()->SetLabelSize(0.1);    
  line->Draw();  
  c1->SaveAs("h_pt3_etacut.pdf");
  
  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  TH1F* h_pt3overavg_data_etacut = (TH1F*)histos->Get("h_pt3overavg_data_etacut");
  TH1F* h_pt3overavg_etacut = (TH1F*)histos->Get("h_pt3overavg_etacut");
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_pt3overavg_data_etacut,"data");
//   leg->AddEntry(h_pt3overavg_etacut,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_pt3overavg_etacut->Integral();
  dataevents=h_pt3overavg_data_etacut->Integral();
  cout << "pt3overavg_etacut"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl;  
//   xtitle="Pt 3rd Jet";
//     //draw histos
//   h_pt3overavg->Sumw2();
//   h_pt3overavg_data->Sumw2();
  h_pt3overavg_etacut->Draw("histE0");
  h_pt3overavg_data_etacut->SetMarkerStyle(20);
  h_pt3overavg_data_etacut->SetMarkerSize(0.5);
  h_pt3overavg_data_etacut->Draw("sameE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio
//   TPad* padratio=new TPad("padratio","padratio",0,0,1,0.3);

  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio3=(TH1F*)h_pt3overavg_data_etacut->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_pt3overavg_etacut);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
  ratio3->GetYaxis()->SetNdivisions(510);
  ratio3->GetYaxis()->SetLabelSize(0.1);
  ratio3->GetXaxis()->SetTitle(xtitle);
  ratio3->GetXaxis()->SetTitleSize(0.2);
  ratio3->GetXaxis()->SetNdivisions(510);
  ratio3->GetXaxis()->SetLabelSize(0.1);    
  line->Draw();  
  c1->SaveAs("h_pt3overavg_etacut.pdf");
  
  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
//   TLine* lineeta=new TLine(-5,1,5,1);
  line->SetLineColor(kBlack);
  TH1F* h_eta0_data_etacut = (TH1F*)histos->Get("h_eta0_data_etacut");
  TH1F* h_eta0_etacut = (TH1F*)histos->Get("h_eta0_etacut");
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_eta0_data_etacut,"data");
//   leg->AddEntry(h_eta0_etacut,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_eta0_etacut->Integral();
  dataevents=h_eta0_data_etacut->Integral();
  cout << "eta0_etacut"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl;  
//   xtitle="Pt 3rd Jet";
//     //draw histos
//   h_eta0->Sumw2();
//   h_eta0_data->Sumw2();
  h_eta0_etacut->Draw("histE0");
  h_eta0_data_etacut->SetMarkerStyle(20);
  h_eta0_data_etacut->SetMarkerSize(0.5);
  h_eta0_data_etacut->Draw("sameE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio3=(TH1F*)h_eta0_data_etacut->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_eta0_etacut);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
  ratio3->GetYaxis()->SetNdivisions(510);
  ratio3->GetYaxis()->SetLabelSize(0.1);
  ratio3->GetXaxis()->SetTitle(xtitle);
  ratio3->GetXaxis()->SetTitleSize(0.2);
  ratio3->GetXaxis()->SetNdivisions(510);
  ratio3->GetXaxis()->SetLabelSize(0.1);    
  lineeta->Draw();  
  c1->SaveAs("h_eta0_etacut.pdf");
  
    ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  line->SetLineColor(kBlack);
  TH1F* h_eta1_data_etacut = (TH1F*)histos->Get("h_eta1_data_etacut");
  TH1F* h_eta1_etacut = (TH1F*)histos->Get("h_eta1_etacut");
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_eta1_data_etacut,"data");
//   leg->AddEntry(h_eta1_etacut,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_eta1_etacut->Integral();
  dataevents=h_eta1_data_etacut->Integral();
  cout << "eta1"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl;  
//   xtitle="Pt 3rd Jet";
//     //draw histos
//   h_eta1->Sumw2();
//   h_eta1_data->Sumw2();
  h_eta1_etacut->Draw("histE0");
  h_eta1_data_etacut->SetMarkerStyle(20);
  h_eta1_data_etacut->SetMarkerSize(0.5);
  h_eta1_data_etacut->Draw("sameE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio3=(TH1F*)h_eta1_data_etacut->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_eta1_etacut);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
  ratio3->GetYaxis()->SetNdivisions(510);
  ratio3->GetYaxis()->SetLabelSize(0.1);
  ratio3->GetXaxis()->SetTitle(xtitle);
  ratio3->GetXaxis()->SetTitleSize(0.2);
  ratio3->GetXaxis()->SetNdivisions(510);
  ratio3->GetXaxis()->SetLabelSize(0.1);    
  lineeta->Draw();  
  c1->SaveAs("h_eta1_etacut.pdf");
  
   ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/

  line->SetLineColor(kBlack);
  TH1F* h_eta2_data_etacut = (TH1F*)histos->Get("h_eta2_data_etacut");
  TH1F* h_eta2_etacut = (TH1F*)histos->Get("h_eta2_etacut");
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_eta2_data_etacut,"data");
//   leg->AddEntry(h_eta2_etacut,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_eta2_etacut->Integral();
  dataevents=h_eta2_data_etacut->Integral();
  cout << "eta2_etacut"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl;  
//   xtitle="Pt 3rd Jet";
//     //draw histos
//   h_eta2->Sumw2();
//   h_eta2_data->Sumw2();
  h_eta2_etacut->Draw("histE0");
  h_eta2_data_etacut->SetMarkerStyle(20);
  h_eta2_data_etacut->SetMarkerSize(0.5);
  h_eta2_data_etacut->Draw("sameE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio3=(TH1F*)h_eta2_data_etacut->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_eta2_etacut);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
  ratio3->GetYaxis()->SetNdivisions(510);
  ratio3->GetYaxis()->SetLabelSize(0.1);
  ratio3->GetXaxis()->SetTitle(xtitle);
  ratio3->GetXaxis()->SetTitleSize(0.2);
  ratio3->GetXaxis()->SetNdivisions(510);
  ratio3->GetXaxis()->SetLabelSize(0.1);    
  lineeta->Draw();  
  c1->SaveAs("h_eta2_etacut.pdf");
  
     ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  char cutlabel_npv[]="EtaCut";
  TLine* line_npv=new TLine(0,1,30,1);
  line_npv->SetLineColor(kBlack);
  TH1F* h_npv_data = (TH1F*)histos->Get("h_npv_data");
  TH1F* h_npv = (TH1F*)histos->Get("h_npv");
//   leg->Delete();
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_npv_data,"data");
//   leg->AddEntry(h_npv,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_npv->Integral();
  dataevents=h_npv_data->Integral();
  cout << "N_PV"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl;  
//   xtitle="Pt 3rd Jet";
//     //draw histos
//   h_eta2->Sumw2();
//   h_eta2_data->Sumw2();
  h_npv->Draw("histE0");
  h_npv->SetTitle("Number of primary vertices");
  h_npv->GetYaxis()->SetTitle("events");
  Style(h_npv,"","events");
  h_npv_data->SetMarkerStyle(20);
  h_npv_data->SetMarkerSize(0.5);
  h_npv_data->Draw("sameE0");
  leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel_npv);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio3=(TH1F*)h_npv_data->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_npv);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
  Styleratio(ratio3,"number of primary vertices","data/MC");
  line_npv->Draw();  
  c1->SaveAs("h_npv.pdf");
  


  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////
  line->SetLineColor(kBlack);
  TH1F* h_ptave3_data = (TH1F*)histos->Get("PtAve_data_w_dijetselec");
  TH1F* h_ptave3_mc = (TH1F*)histos->Get("PtAve_mc_w_dijetselec");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
  padhist->Draw();
  padhist->cd();

  mcevents=h_ptave3_mc->Integral();
  dataevents=h_ptave3_data->Integral();
  cout << "PtAve w/ Dijetselec"<<endl;
  cout << "data events: "<< dataevents  << endl;  
  cout << "mcevents : " << mcevents << endl;  

  h_ptave3_mc->Draw("histE0");
  Style(h_ptave3_mc,"","events");
  h_ptave3_mc->SetTitle("");
  h_ptave3_data->SetMarkerStyle(20);
  h_ptave3_data->SetMarkerSize(0.5);
  h_ptave3_data->Draw("sameE0");
//   leg->Draw();
  text->DrawLatex(0.23, 0.863, text_cms);
  text->DrawLatex(0.23, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio3=(TH1F*)h_ptave3_data->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_ptave3_mc);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
  Styleratio(ratio3,"p_{T}^{Avg} with Dijetselection","data/MC");   
  line->Draw();  
  c1->SaveAs("h_ptave_w_dijetselec.pdf");

  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////
  line->SetLineColor(kBlack);
  TH1F* h_ptave3_data_etacut = (TH1F*)histos->Get("PtAve_data_w_dijetselec_etacut");
  TH1F* h_ptave3_mc_etacut = (TH1F*)histos->Get("PtAve_mc_w_dijetselec_etacut");
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_ptave3_data_etacut,"data");
//   leg->AddEntry(h_ptave3_mc_etacut,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_ptave3_mc_etacut->Integral();
  dataevents=h_ptave3_data_etacut->Integral();
  cout << "PtAve w/ Dijetselec_etacut"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl;  
//   xtitle="Pt 3rd Jet";
//     //draw histos
//   h_eta1->Sumw2();
//   h_eta1_data->Sumw2();
  h_ptave3_mc_etacut->Draw("histE0");
  h_ptave3_data_etacut->SetMarkerStyle(20);
  h_ptave3_data_etacut->SetMarkerSize(0.5);
  h_ptave3_data_etacut->Draw("sameE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio3=(TH1F*)h_ptave3_data_etacut->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_ptave3_mc_etacut);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
  ratio3->GetYaxis()->SetNdivisions(510);
  ratio3->GetYaxis()->SetLabelSize(0.1);
  ratio3->GetXaxis()->SetTitle(xtitle);
  ratio3->GetXaxis()->SetTitleSize(0.2);
  ratio3->GetXaxis()->SetNdivisions(510);
  ratio3->GetXaxis()->SetLabelSize(0.1);    
  line->Draw();  
  c1->SaveAs("h_ptave_w_dijetselec_etacut.pdf");

  
  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////
  line->SetLineColor(kBlack);
  TH1F* h_ptave2_data = (TH1F*)histos->Get("PtAve_data_wo_dijetselec");
  TH1F* h_ptave2_mc = (TH1F*)histos->Get("PtAve_mc_wo_dijetselec");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_ptave2_mc->Integral();
  dataevents=h_ptave2_data->Integral();
  cout << "PtAve w/p Dijetselec"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl;  
  h_ptave2_mc->Draw("histE0");
  h_ptave2_mc->SetStats(0);
  Style(h_ptave2_mc,"","events");
  h_ptave2_mc->SetTitle("p_{T}^{Avg} without Dijetselection");  
  h_ptave2_data->SetMarkerStyle(20);
  h_ptave2_data->SetMarkerSize(0.5);  
  h_ptave2_data->Draw("sameE0");
  leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);

  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio3=(TH1F*)h_ptave2_data->Clone(); 
  ratio3->SetTitle("");
  ratio3->SetXTitle(xtitle);
  ratio3->Sumw2();
  ratio3->SetStats(0);
  ratio3->Divide(h_ptave2_mc);
  ratio3->SetMarkerStyle(20);
  ratio3->SetMarkerSize(0.5);
  ratio3->Draw("E0");
  ratio3->SetMaximum(1.6);
  ratio3->SetMinimum(0.4);
  //set_ratioattributes  
  Styleratio(ratio3,"p_{T}^{Avg} in GeV/c","data/MC") ;
//   padratio->SetBottomMargin(0.3);
  line->Draw();  
  c1->SaveAs("h_ptave_wo_dijetselec.pdf");
  
  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  TH1F* h_pt0_data = (TH1F*)histos->Get("h_pt0_data");
  TH1F* h_pt0 = (TH1F*)histos->Get("h_pt0");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

  c1->cd();
  //makepadhist
  padhist->Draw();
  padhist->cd();

  mcevents=h_pt0->Integral();
  dataevents=h_pt0_data->Integral();
  cout << "pt0"<<endl;
  cout << "data events: "<< dataevents  << endl;  
  cout << "mcevents : " << mcevents << endl; 

  h_pt0->Sumw2();
  h_pt0_data->Sumw2();
  h_pt0->Draw("histE0");
  Style(h_pt0,"","events");
  h_pt0->SetTitle("");
  h_pt0_data->SetMarkerStyle(20);
  h_pt0_data->SetMarkerSize(0.5);
  h_pt0_data->Draw("SAMEE0");
//   leg->Draw();
  text->DrawLatex(0.23, 0.863, text_cms);
  text->DrawLatex(0.23, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio2=(TH1F*)h_pt0_data->Clone(); 
  ratio2->SetTitle("");
  ratio2->SetXTitle(xtitle);
  ratio2->Sumw2();
  ratio2->SetStats(0);
  ratio2->Divide(h_pt0);
  ratio2->SetMarkerStyle(20);
  ratio2->SetMarkerSize(0.5);
  ratio2->Draw("E0");
  ratio2->SetMaximum(1.6);
  ratio2->SetMinimum(0.4);
  //set_ratioattributes  
  Styleratio(ratio2,"p_{T} of hardest Jet","data/MC");    
  line->Draw();  
  c1->SaveAs("h_pt0.pdf");
  
  
  
    ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  TH1F* h_pt1_data = (TH1F*)histos->Get("h_pt1_data");
  TH1F* h_pt1 = (TH1F*)histos->Get("h_pt1");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

  c1->cd();
//makepadhist
  padhist->Draw();
  padhist->cd();

  mcevents=h_pt1->Integral();
  dataevents=h_pt1_data->Integral();
  cout << "pt1"<<endl;
  cout << "data events: "<< dataevents  << endl;  
  cout << "mcevents : " << mcevents << endl; 

  h_pt1->Sumw2();
  h_pt1_data->Sumw2();
  h_pt1->Draw("histE0");
  Style(h_pt1,"","events");
  h_pt1->SetTitle("");
  h_pt1_data->SetMarkerStyle(20);
  h_pt1_data->SetMarkerSize(0.5);
  h_pt1_data->Draw("SAMEE0");
//   leg->Draw();
  text->DrawLatex(0.23, 0.863, text_cms);
  text->DrawLatex(0.23, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio2=(TH1F*)h_pt1_data->Clone(); 
  ratio2->SetTitle("");
  ratio2->SetXTitle(xtitle);
  ratio2->Sumw2();
  ratio2->SetStats(0);
  ratio2->Divide(h_pt1);
  ratio2->SetMarkerStyle(20);
  ratio2->SetMarkerSize(0.5);
  ratio2->Draw("E0");
  ratio2->SetMaximum(1.6);
  ratio2->SetMinimum(0.4);
  //set_ratioattributes  
  Styleratio(ratio2,"p_{T} of 2nd-hardest Jet","data/MC");   
  line->Draw();  
  c1->SaveAs("h_pt1.pdf");
  
   ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  TH1F* h_dphi_data = (TH1F*)histos->Get("h_dphi_data");
  TH1F* h_dphi = (TH1F*)histos->Get("h_dphi");
  TLine* dphiline=new TLine(0,1,3.5,1);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
  padhist->Draw();
  padhist->cd();

  mcevents=h_dphi->Integral();
  dataevents=h_dphi_data->Integral();
  cout << "dphi"<<endl;
  cout << "data events: "<< dataevents  << endl;  
  cout << "mcevents : " << mcevents << endl; 
  
  //draw histos
  h_dphi->Sumw2();
  h_dphi_data->Sumw2();
  h_dphi->Draw("histE0");
  Style(h_dphi,"","events");
  h_dphi->SetTitle("#Delta #Phi between two hardest Jets");
  h_dphi->SetStats(0);  
  h_dphi_data->SetMarkerStyle(20);
  h_dphi_data->SetMarkerSize(0.5);
  h_dphi_data->Draw("SAMEE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
//   text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();  
  //makeratio    
  ratio2=(TH1F*)h_dphi_data->Clone(); 
  ratio2->SetTitle("");
  ratio2->SetXTitle(xtitle);
  ratio2->Sumw2();
  ratio2->SetStats(0);
  ratio2->Divide(h_dphi);
  ratio2->SetMarkerStyle(20);
  ratio2->SetMarkerSize(0.5);
  ratio2->Draw("E0");
  ratio2->SetMaximum(1.6);
  ratio2->SetMinimum(0.4);
  //set_ratioattributes  
  Styleratio(ratio2,"#Delta #Phi","data/MC"); 
  dphiline->Draw();  
  c1->SaveAs("h_dphi.pdf");
  
  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  TH1F* h_ptave1_data = (TH1F*)histos->Get("PtAve_data_w_dijetselec_1");
  TH1F* h_ptave1_mc = (TH1F*)histos->Get("PtAve_mc_w_dijetselec_1");
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_ptave1_data,"data");
//   leg->AddEntry(h_ptave1_mc,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_ptave1_mc->Integral();
  dataevents=h_ptave1_data->Integral();
  cout << "ptave"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl; 
  
//   xtitle="Pt 3rd Jet";
//     //draw histos
  h_ptave1_mc->Sumw2();
  h_ptave1_data->Sumw2();
  h_ptave1_mc->Draw("histE0");
  h_ptave1_data->SetMarkerStyle(20);
  h_ptave1_data->SetMarkerSize(0.5);
  h_ptave1_data->Draw("SAMEE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio2=(TH1F*)h_ptave1_data->Clone(); 
  ratio2->SetTitle("");
  ratio2->SetXTitle(xtitle);
  ratio2->Sumw2();
  ratio2->SetStats(0);
  ratio2->Divide(h_ptave1_mc);
  ratio2->SetMarkerStyle(20);
  ratio2->SetMarkerSize(0.5);
  ratio2->Draw("E0");
  ratio2->SetMaximum(1.6);
  ratio2->SetMinimum(0.4);
  //set_ratioattributes  
  ratio2->GetYaxis()->SetNdivisions(510);
  ratio2->GetYaxis()->SetLabelSize(0.1);
  ratio2->GetXaxis()->SetTitle(xtitle);
  ratio2->GetXaxis()->SetTitleSize(0.2);
  ratio2->GetXaxis()->SetNdivisions(510);
  ratio2->GetXaxis()->SetLabelSize(0.1);    
  line->Draw();  
  c1->SaveAs("h_ptave1.pdf");
  
  ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  TH1F* h_pt0_data_dijet = (TH1F*)histos->Get("h_pt0_data_dijet");
  TH1F* h_pt0_dijet = (TH1F*)histos->Get("h_pt0_dijet");
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_pt0_data_dijet,"data");
//   leg->AddEntry(h_pt0_dijet,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_pt0_dijet->Integral();
  dataevents=h_pt0_data_dijet->Integral();
  cout << "pt0_dijet"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl; 
  
//   xtitle="Pt 3rd Jet";
//     //draw histos
  h_pt0_dijet->Sumw2();
  h_pt0_data_dijet->Sumw2();
  h_pt0_dijet->Draw("histE0");
  h_pt0_data_dijet->SetMarkerStyle(20);
  h_pt0_data_dijet->SetMarkerSize(0.5);
  h_pt0_data_dijet->Draw("SAMEE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio2=(TH1F*)h_pt0_data_dijet->Clone(); 
  ratio2->SetTitle("");
  ratio2->SetXTitle(xtitle);
  ratio2->Sumw2();
  ratio2->SetStats(0);
  ratio2->Divide(h_pt0_dijet);
  ratio2->SetMarkerStyle(20);
  ratio2->SetMarkerSize(0.5);
  ratio2->Draw("E0");
  ratio2->SetMaximum(1.6);
  ratio2->SetMinimum(0.4);
  //set_ratioattributes  
  ratio2->GetYaxis()->SetNdivisions(510);
  ratio2->GetYaxis()->SetLabelSize(0.1);
  ratio2->GetXaxis()->SetTitle(xtitle);
  ratio2->GetXaxis()->SetTitleSize(0.2);
  ratio2->GetXaxis()->SetNdivisions(510);
  ratio2->GetXaxis()->SetLabelSize(0.1);    
  line->Draw();  
  c1->SaveAs("h_pt0_dijet.pdf");
  
    ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  TH1F* h_pt1_data_dijet = (TH1F*)histos->Get("h_pt1_data_dijet");
  TH1F* h_pt1_dijet = (TH1F*)histos->Get("h_pt1_dijet");
//   TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
//   leg->AddEntry(h_pt1_data_dijet,"data");
//   leg->AddEntry(h_pt1_dijet,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
//   TCanvas *c1=new TCanvas();
  c1->cd();
  //makepadhist
//   TPad* padhist=new TPad("padhist","padhist",0,0.3,1,1);
  padhist->SetBottomMargin(0);
  padhist->Draw();
  padhist->cd();

  mcevents=h_pt1_dijet->Integral();
  dataevents=h_pt1_data_dijet->Integral();
  cout << "pt1_dijet"<<endl;
  cout << "data events: "<< dataevents  << endl;
  
  cout << "mcevents : " << mcevents << endl; 
  
//   xtitle="Pt 3rd Jet";
//     //draw histos
  h_pt1_dijet->Sumw2();
  h_pt1_data_dijet->Sumw2();
  h_pt1_dijet->Draw("histE0");
  h_pt1_data_dijet->SetMarkerStyle(20);
  h_pt1_data_dijet->SetMarkerSize(0.5);
  h_pt1_data_dijet->Draw("SAMEE0");
//   leg->Draw();
  text->DrawLatex(0.175, 0.863, text_cms);
  text->DrawLatex(0.175, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio2=(TH1F*)h_pt1_data_dijet->Clone(); 
  ratio2->SetTitle("");
  ratio2->SetXTitle(xtitle);
  ratio2->Sumw2();
  ratio2->SetStats(0);
  ratio2->Divide(h_pt1_dijet);
  ratio2->SetMarkerStyle(20);
  ratio2->SetMarkerSize(0.5);
  ratio2->Draw("E0");
  ratio2->SetMaximum(1.6);
  ratio2->SetMinimum(0.4);
  //set_ratioattributes  
  ratio2->GetYaxis()->SetNdivisions(510);
  ratio2->GetYaxis()->SetLabelSize(0.1);
  ratio2->GetXaxis()->SetTitle(xtitle);
  ratio2->GetXaxis()->SetTitleSize(0.2);
  ratio2->GetXaxis()->SetNdivisions(510);
  ratio2->GetXaxis()->SetLabelSize(0.1);    
  line->Draw();  
  c1->SaveAs("h_pt1_dijet.pdf");
  
      ////////////////////////
  /////////////////////////
  ////////////////////////
  ///////////////////////7/
  TH1F* h_ptassym_data = (TH1F*)histos->Get("h_ptassym_data");
  TH1F* h_ptassym = (TH1F*)histos->Get("h_ptassym");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
  c1->cd();
  //makepadhist
  padhist->Draw();
  padhist->cd();

  mcevents=h_ptassym->Integral();
  dataevents=h_ptassym_data->Integral();
  cout << "ptassym"<<endl;
  cout << "data events: "<< dataevents  << endl;  
  cout << "mcevents : " << mcevents << endl; 

  h_ptassym->Sumw2();
  h_ptassym_data->Sumw2();
  h_ptassym->Draw("histE0");
  Style(h_ptassym,"","events");
  h_ptassym->SetTitle("p_{T} asymmetry");
  h_ptassym_data->SetMarkerStyle(20);
  h_ptassym_data->SetMarkerSize(0.5);
  h_ptassym_data->Draw("SAMEE0");
//   leg->Draw();
  text->DrawLatex(0.23, 0.863, text_cms);
  text->DrawLatex(0.23, 0.815, cutlabel);
  c1->cd();
  //makepadratio
  padratio->Draw();
  padratio->cd();
  
  //makeratio    
  ratio2=(TH1F*)h_ptassym_data->Clone(); 
  ratio2->SetTitle("");
  ratio2->SetXTitle(xtitle);
  ratio2->Sumw2();
  ratio2->SetStats(0);
  ratio2->Divide(h_ptassym);
  ratio2->SetMarkerStyle(20);
  ratio2->SetMarkerSize(0.5);
  ratio2->Draw("E0");
  ratio2->SetMaximum(1.6);
  ratio2->SetMinimum(0.4);
  //set_ratioattributes  
  Styleratio(ratio2,"p_{T} asymmetry","data/MC");   
  line->Draw();  
  c1->SaveAs("h_ptassym.pdf");
  
}
int main(){
  TFile* histos=new TFile("../histos.root");
  
  ratioplot(histos);

}