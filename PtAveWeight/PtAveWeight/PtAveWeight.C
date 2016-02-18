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
vector<TH1F*>readhistos(TFile *file, char c){
  vector<TH1F*> res;
  if (c=='d'){
    for (int i=0; i<7;++i){
    stringstream ss;
    ss << i;
    TString counter=ss.str();
    
    TH1F* h = (TH1F*)file->Get("hptavg_data_bin"+counter);
    res.push_back(h);
    }
  }
  else if (c=='p'){
    for (int i=0; i<7;++i){
    stringstream ss;
    ss << i;
    TString counter=ss.str();
    
    TH1F* h = (TH1F*)file->Get("hptave_mc"+counter);
    res.push_back(h);	
    }
  } 
  return res;  
}

void PtAveWeight(TFile *histos){
  //outputfile
  TFile* outfile=new TFile("ptaveweight.root","RECREATE");
  cout << "Reading Histos from file" << endl;
  vector<TH1F*>h_data=readhistos(histos,'d');
  vector<TH1F*>h_mc=readhistos(histos,'p');
  TH1F* h_PtAveWeight=new TH1F("PtAveWeight","PtAveWeight",7,0,7);
  
  
  char text_cms[]="CMS private Work";
  char cutlabel[]="Dijet selection";
  TLatex* text=new TLatex();
  text-> SetNDC();
  text-> SetTextFont(42);
  text-> SetTextSize(0.05);
  
  float mcevents=0;
  float normratio=0;
  float dataevents=0;

  
  for (int i=0; i<7;++i){
    //makelegend
    gStyle->SetPadLeftMargin(0.18);
    TLegend* leg=new TLegend(0.7,0.5,0.9,0.8);
    leg->AddEntry(h_data.at(i),"data");
    leg->AddEntry(h_mc.at(i),"MC");
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    
    TCanvas *c1=new TCanvas();
    c1->cd();
    mcevents=h_mc.at(i)->Integral();
    cout << "bin "<< i <<endl;
    dataevents=h_data.at(i)->Integral();
    cout << "data events: "<< dataevents  << endl;
    
    cout << "mcevents before normalization: " << mcevents << endl;
    
    
    if (mcevents!=0) normratio=dataevents/mcevents;
      else normratio=1;
    TH1F* mc_norm=(TH1F*)h_mc.at(i)->Clone();
    mc_norm->Scale(normratio);
    cout << "PtAveWeight: "<<normratio<<endl;
    cout << "mcevents after normalization (integral): " << mc_norm->Integral() << endl;

   
//     //draw histos
    h_data.at(i)->Sumw2();
//     h_mc.at(i)->Draw("histE0");
    h_data.at(i)->SetLineColor(kRed);
    h_data.at(i)->Draw("samehistE0");
    h_data.at(i)->SetTitle(" 89.6 GeV/c <= p_{T}^{Avg} < 155.6 GeV/c");
    h_data.at(i)->GetXaxis()->SetTitle("p_{T}^{Avg} in GeV/c");
    h_data.at(i)->GetXaxis()->SetTitleSize(0.05);
    h_data.at(i)->GetXaxis()->SetTitleOffset(0.8);
    h_data.at(i)->GetYaxis()->SetTitle("events");
    h_data.at(i)->GetYaxis()->SetTitleSize(0.08);
    h_data.at(i)->GetYaxis()->SetTitleOffset(0.8);
    h_data.at(i)->SetStats(0);
    
    mc_norm->Draw("samehistE0");
    mc_norm->SetLineColor(kBlack);
    leg->Draw();
//     gPad->SetLogy();
    text->DrawLatex(0.2, 0.85, text_cms);
//     text->DrawLatex(0.175, 0.815, cutlabel);
    
    stringstream ss;
    ss << i;
    TString counter=ss.str();
    c1->SaveAs("PtAve_bin"+counter+".pdf");
    
    h_PtAveWeight->SetBinContent(i+1,normratio);
 
    mc_norm->Write();
    leg->Delete();
    mc_norm->Delete();
    h_mc.at(i)->Write();
    h_data.at(i)->Write();
    
  
  
  }
  TCanvas *c1=new TCanvas();
  gPad->SetLogy();
  h_PtAveWeight->Draw("E0");
  h_PtAveWeight->Write();
  c1->SaveAs("PtAveWeight.png");
  outfile->Close();
  
  
  
}
  











int main(){
  TFile* histos=new TFile("../analysetrees/histos.root");  
  PtAveWeight(histos);

}