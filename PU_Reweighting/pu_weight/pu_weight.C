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
void PUWeight(TFile *histos){
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

  char xtitle[]="N_PV";  
  
  float mcevents=0;
  float normratio=0;
  float dataevents=0;
  //makelegend
  
  TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
  leg->AddEntry(h_npv_data,"data");
  leg->AddEntry(h_npv_mc,"MC");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  
  TLine* line=new TLine(0,1,1000,1);
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
  padratio->SetBottomMargin(1.1);
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
  ratio->SetMaximum(1.6);
  ratio->SetMinimum(0.4);
  //set_ratioattributes  
  ratio->GetYaxis()->SetNdivisions(510);
  ratio->GetYaxis()->SetLabelSize(0.1);
  ratio->GetXaxis()->SetTitle(xtitle);
  ratio->GetXaxis()->SetTitleSize(0.11);
  ratio->GetXaxis()->SetNdivisions(510);
  ratio->GetXaxis()->SetLabelSize(0.1);    
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
  ratio->SetMaximum(1.6);
  ratio->SetMinimum(0.4);
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