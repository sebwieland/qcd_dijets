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
void Stylestack(THStack* h, const char *xTitle, const char *yTitle)
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
vector<vector<TH1F*>> readhistos(TFile *file, char c){
  int n_ptbins= 10;
  int n_etabins=4;
  TString eta_counter="0";
  TString pt_counter="0";
  vector<vector<TH1F*>> res;
  res.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  if (c=='d'){
    for (int i=0; i<n_ptbins;++i){
    if (i==0) pt_counter="0";
    else if (i==1) pt_counter="1";
    else if (i==2) pt_counter="2";
    else if (i==3) pt_counter="3";
    else if (i==4) pt_counter="4";
    else if (i==5) pt_counter="5";
    else if (i==6) pt_counter="6";
    else if (i==7) pt_counter="7";
    else if (i==8) pt_counter="8";
    else if (i==9) pt_counter="9";
    for ( int j=0; j<n_etabins;++j){   
      if (j==0) eta_counter="0";
      else if (j==1) eta_counter="1";
      else if (j==2) eta_counter="2";
      else if (j==3) eta_counter="3";
	TH1F* h = (TH1F*)file->Get("hCSV_data_ptbin"+pt_counter+"_etabin"+eta_counter);
	res[i][j]=h;
      }
    }
  }
  else if (c=='l'){
    for (int i=0; i<n_ptbins;++i){
    if (i==0) pt_counter="0";
    else if (i==1) pt_counter="1";
    else if (i==2) pt_counter="2";
    else if (i==3) pt_counter="3";
    else if (i==4) pt_counter="4";
    else if (i==5) pt_counter="5";
    else if (i==6) pt_counter="6";
    else if (i==7) pt_counter="7";
    else if (i==8) pt_counter="8";
    else if (i==9) pt_counter="9";
    for ( int j=0; j<n_etabins;++j){   
      if (j==0) eta_counter="0";
      else if (j==1) eta_counter="1";
      else if (j==2) eta_counter="2";
      else if (j==3) eta_counter="3";
	TH1F* h = (TH1F*)file->Get("hCSV_mc_lf_ptbin"+pt_counter+"_etabin"+eta_counter);
	res[i][j]=h;
      }
    }
  }
  else if (c=='b'){
    for (int i=0; i<n_ptbins;++i){
    if (i==0) pt_counter="0";
    else if (i==1) pt_counter="1";
    else if (i==2) pt_counter="2";
    else if (i==3) pt_counter="3";
    else if (i==4) pt_counter="4";
    else if (i==5) pt_counter="5";
    else if (i==6) pt_counter="6";
    else if (i==7) pt_counter="7";
    else if (i==8) pt_counter="8";
    else if (i==9) pt_counter="9";
    for ( int j=0; j<n_etabins;++j){   
      if (j==0) eta_counter="0";
      else if (j==1) eta_counter="1";
      else if (j==2) eta_counter="2";
      else if (j==3) eta_counter="3";
	TH1F* h = (TH1F*)file->Get("hCSV_mc_b_ptbin"+pt_counter+"_etabin"+eta_counter);
	res[i][j]=h;
      }
    }
  }
  else if (c=='c'){
    for (int i=0; i<n_ptbins;++i){
    if (i==0) pt_counter="0";
    else if (i==1) pt_counter="1";
    else if (i==2) pt_counter="2";
    else if (i==3) pt_counter="3";
    else if (i==4) pt_counter="4";
    else if (i==5) pt_counter="5";
    else if (i==6) pt_counter="6";
    else if (i==7) pt_counter="7";
    else if (i==8) pt_counter="8";
    else if (i==9) pt_counter="9";
    for ( int j=0; j<n_etabins;++j){   
      if (j==0) eta_counter="0";
      else if (j==1) eta_counter="1";
      else if (j==2) eta_counter="2";
      else if (j==3) eta_counter="3";
	TH1F* h = (TH1F*)file->Get("hCSV_mc_c_ptbin"+pt_counter+"_etabin"+eta_counter);
	res[i][j]=h;
      }
    }
  }
  return res;  
}

void calculate_sf(TFile *histos){
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
  TFile* outfile=new TFile("scalefactors.root","RECREATE");
  cout << "Reading Histos from file" << endl;
  vector<vector<TH1F*>>h_data=readhistos(histos,'d');
  vector<vector<TH1F*>>h_b=readhistos(histos,'b');
  vector<vector<TH1F*>>h_c=readhistos(histos,'c');
  vector<vector<TH1F*>>h_lf=readhistos(histos,'l');
  
  TH1F* hCSV_mc_b_tag = (TH1F*)histos->Get("hCSV_mc_b_tag");
  TH1F* hCSV_mc_c_tag = (TH1F*)histos->Get("hCSV_mc_c_tag");
  TH1F* hCSV_mc_lf_tag = (TH1F*)histos->Get("hCSV_mc_lf_tag");
  hCSV_mc_b_tag->SetFillColor(kRed);
  hCSV_mc_c_tag->SetFillColor(kBlue);
  hCSV_mc_lf_tag->SetFillColor(kGreen);
  
  TH1F* hCSV_data_tag = (TH1F*)histos->Get("hCSV_data_tag");

  
  TString eta_counter="0";
  TString pt_counter="0";

  //SetColors
  int n_ptbins= 10;
  int n_etabins=4;
  for (int i=0; i<n_ptbins;++i){
    for ( int j=0; j<n_etabins;++j){   
   h_b[i][j]->SetFillColor(kRed);
   h_c[i][j]->SetFillColor(kBlue);
   h_lf[i][j]->SetFillColor(kGreen); 
    }
  }

  float xmin=-0.1;
  float xmax=1;
  //text + line in ratio
  TLine* line=new TLine(xmin,1,xmax,1);
  line->SetLineColor(kBlack);
  char text_cms[]="CMS private Work";
  char cutlabel[]="Dijet selection";
  TLatex* text=new TLatex();
  text-> SetNDC();
  text-> SetTextFont(42);
  text-> SetTextSize(0.05);
  
  char xtitle_hf[]="CSV probe Jet (HF)";
  
  double  n_events_hf;
  float mcevents=0;
  float normratio=0;
  float dataevents=0;
  bool ptnorm=true;
  cout << "calculating SF" << endl;
  
  for (int i=0; i<n_ptbins;++i){
    if (i==0) pt_counter="0";
    else if (i==1) pt_counter="1";
    else if (i==2) pt_counter="2";
    else if (i==3) pt_counter="3";
    else if (i==4) pt_counter="4";
    else if (i==5) pt_counter="5";
    else if (i==6) pt_counter="6";
    else if (i==7) pt_counter="7";
    else if (i==8) pt_counter="8";
    else if (i==9) pt_counter="9";
    for ( int j=0; j<n_etabins;++j){   
      if (j==0) eta_counter="0";
      else if (j==1) eta_counter="1";
      else if (j==2) eta_counter="2";
      else if (j==3) eta_counter="3";
    //makelegend
   
      TLegend* leg_hf=new TLegend(0.75,0.4,0.9,0.8);
      leg_hf->AddEntry(h_data[i][j],"data");
      leg_hf->AddEntry(h_b[i][j],"b");
      leg_hf->AddEntry(h_c[i][j],"c");
      leg_hf->AddEntry(h_lf[i][j],"lf");
      leg_hf->SetFillStyle(0);
      leg_hf->SetBorderSize(0);
      
      TCanvas *c1=new TCanvas();
      c1->cd();
      //makepadhist
      TPad* padhist_hf=new TPad("padhist_hf","padhist_hf",0,0.3,1,1);
      padhist_hf->SetBottomMargin(0);
      padhist_hf->Draw();
      padhist_hf->cd();
      TH1F* mc=(TH1F*)h_b[i][j]->Clone(); 
      mc->Add(h_c[i][j]);
      mc->Add(h_lf[i][j]);
  //     mc_stack[i][j]->Print();
  //     TH1F* mc=(TH1F*)mc_stack[i][j]->GetStack();
      n_events_hf=h_c[i][j]->Integral()+h_b[i][j]->Integral();
      mcevents=mc->Integral();
      cout << "ptbin "<< i <<" etabin " <<j<< endl;
      dataevents=h_data[i][j]->Integral();
      cout << "data events: "<< dataevents  << endl;
      
      cout << "mcevents before normalization: " << mcevents << endl;
      
      if(ptnorm==true){
	if (mcevents!=0) normratio=dataevents/mcevents;
	  else normratio=1;
	h_b[i][j]->Scale(normratio);
	h_c[i][j]->Scale(normratio);
	h_lf[i][j]->Scale(normratio);
      }
      THStack* mc_stack_hf_normalized=new THStack();
      mc_stack_hf_normalized->Add(h_b[i][j]);
      mc_stack_hf_normalized->Add(h_c[i][j]);
      mc_stack_hf_normalized->Add(h_lf[i][j]);
      TH1F* mc_norm=(TH1F*)mc_stack_hf_normalized->GetStack()->Last();
      cout << "mcevents after normalization: " << mc_norm->Integral() << endl;
      cout << "Purity: " << n_events_hf/mcevents << endl;
    
  //     //draw histos
      h_data[i][j]->Sumw2();
      mc_stack_hf_normalized->Draw("histE0");
      mc_stack_hf_normalized->SetMinimum(0.01);
      Stylestack(mc_stack_hf_normalized,"","events");
      h_data[i][j]->SetMarkerStyle(20);
      h_data[i][j]->Draw("SAMEE0");
      leg_hf->Draw();
      text->DrawLatex(0.4, 0.863, text_cms);
      text->DrawLatex(0.4, 0.815, cutlabel);
      c1->cd();
      //makepadratio
      TPad* padratio_hf=new TPad("padratio_hf","padratio_hf",0,0,1,0.3);
      padratio_hf->SetTopMargin(0);
      padratio_hf->Draw();
      padratio_hf->cd();
      
      //makeratio    
      TH1F* ratio_hf=(TH1F*)h_data[i][j]->Clone(); 
      ratio_hf->SetTitle("");
      ratio_hf->SetXTitle(xtitle_hf);
      ratio_hf->Sumw2();
      ratio_hf->SetStats(0);
      ratio_hf->Divide(mc_norm);
      ratio_hf->SetMarkerStyle(20);
      ratio_hf->Draw("SAMEE0");
      ratio_hf->SetMaximum(1.59);
      ratio_hf->SetMinimum(0.39);
      //set_ratioattributes  
      Styleratio(ratio_hf,xtitle_hf,"data/MC");   
      
      line->Draw();
      stringstream ss;
      ss << i;
      TString counter=ss.str();
      c1->SaveAs("CSV_ratio_hf_ptbin"+pt_counter+"_etabin"+eta_counter+"_drcut.pdf");


      //subtract LF contamination
      TCanvas *c2=new TCanvas(); 
      c2->cd(); 
      TH1F *diff_hf=(TH1F*)h_data[i][j]->Clone();
      diff_hf->Sumw2();
      diff_hf->SetTitle("Data-LF");
      diff_hf->Add(h_lf[i][j],-1);
      diff_hf->Draw("E0");       
      diff_hf->SetLineColor(kBlue);
      diff_hf->Write();
	
      TH1F* nonlf_hf=(TH1F*)h_b[i][j]->Clone();
      nonlf_hf->Add(h_c[i][j]);
      nonlf_hf->Draw("SAMEE0");
      nonlf_hf->SetMarkerStyle(20);
      nonlf_hf->SetMarkerSize(0.7);
      nonlf_hf->SetLineColor(kRed);
      nonlf_hf->Write();
      c2->BuildLegend(0.2,0.8,0.7,0.9);
      c2->SaveAs("diff_hf_ptbin"+pt_counter+"_etabin"+eta_counter+"_drcut.pdf");
    
      //calculate hfSF
      TH1F* hfsf=(TH1F*)diff_hf->Clone();
      hfsf->Divide(nonlf_hf);
      //fit with 5th order polnomial
      // gStyle->SetOptFit(000000000);
      // gStyle->SetOptStat(000000000);
      hfsf->Fit("pol6","","",0,1);
      hfsf->Draw("E0");
      hfsf->GetYaxis()->SetLabelSize(0.04);
      hfsf->GetXaxis()->SetTitle("hfSF");
      hfsf->GetXaxis()->SetTitleSize(0.04);
      hfsf->GetXaxis()->SetNdivisions(510);
      hfsf->GetXaxis()->SetLabelSize(0.04);
      line->Draw();
      hfsf->Write();
      hfsf->GetXaxis()->SetTitle("hfSF");
      c2->SaveAs("hfSF_ptbin"+pt_counter+"_etabin"+eta_counter+"_drcut.pdf");

    
      
      
      leg_hf->Delete();
      padhist_hf->Delete();
      mc->Delete();
      mc_stack_hf_normalized->Delete();
      padratio_hf->Delete();
      ratio_hf->Delete();
      diff_hf->Delete();
      nonlf_hf->Delete();
      hfsf->Delete();
      outfile->Write();
    } 
  }
  
    //////////////////////////////////////////////////
  //////////// Plot CSV of TagJet///////////////////
  //////////////////////////////////////////////////
       TLegend* leg_hf=new TLegend(0.75,0.4,0.9,0.8);
      leg_hf->AddEntry(hCSV_data_tag,"data");
      leg_hf->AddEntry(hCSV_mc_b_tag,"b");
      leg_hf->AddEntry(hCSV_mc_c_tag,"c");
      leg_hf->AddEntry(hCSV_mc_lf_tag,"lf");
      leg_hf->SetFillStyle(0);
      leg_hf->SetBorderSize(0);
      
      TLine* line_tag=new TLine(0.98,1,1,1);
      
      TCanvas *c1=new TCanvas();
      c1->cd();
      //makepadhist
      TPad* padhist_hf=new TPad("padhist_hf","padhist_hf",0,0.3,1,1);
      padhist_hf->SetBottomMargin(0);
      padhist_hf->Draw();
      padhist_hf->cd();
      TH1F* mc=(TH1F*)hCSV_mc_b_tag->Clone(); 
      mc->Add(hCSV_mc_c_tag);
      mc->Add(hCSV_mc_lf_tag);
  //     mc_stack[i][j]->Print();
  //     TH1F* mc=(TH1F*)mc_stack[i][j]->GetStack();
      n_events_hf=hCSV_mc_c_tag->Integral()+hCSV_mc_b_tag->Integral();
      mcevents=mc->Integral();
      cout << "TAGJET"<< endl;
      dataevents=hCSV_data_tag->Integral();
      cout << "data events: "<< dataevents  << endl;      
      cout << "mcevents before normalization: " << mcevents << endl;
      
      if(ptnorm==true){
	if (mcevents!=0) normratio=dataevents/mcevents;
	  else normratio=1;
	hCSV_mc_b_tag->Scale(normratio);
	hCSV_mc_c_tag->Scale(normratio);
	hCSV_mc_lf_tag->Scale(normratio);
      }
//       h_b[i][j]->Sumw2();
//       h_c[i][j]->Sumw2();
//       h_lf[i][j]->Sumw2();
      THStack* mc_stack_hf_normalized=new THStack();
      mc_stack_hf_normalized->Add(hCSV_mc_b_tag);
      mc_stack_hf_normalized->Add(hCSV_mc_c_tag);
      mc_stack_hf_normalized->Add(hCSV_mc_lf_tag);
      TH1F* mc_norm=(TH1F*)mc_stack_hf_normalized->GetStack()->Last();
      cout << "mcevents after normalization: " << mc_norm->Integral() << endl;
      cout << "Purity: " << n_events_hf/mcevents << endl;
    
  //     //draw histos
      hCSV_data_tag->Sumw2();
      mc_stack_hf_normalized->Draw("histE0");
      mc_stack_hf_normalized->SetMinimum(0.01);
      Stylestack(mc_stack_hf_normalized,"","events");
      hCSV_data_tag->Draw("sameE0");
      hCSV_data_tag->SetMarkerStyle(20);
   
      leg_hf->Draw();
      text->DrawLatex(0.4, 0.863, text_cms);
      text->DrawLatex(0.4, 0.815, cutlabel);
      c1->cd();
      //makepadratio
      TPad* padratio_hf=new TPad("padratio_hf","padratio_hf",0,0,1,0.3);
      padratio_hf->SetTopMargin(0);
      padratio_hf->Draw();
      padratio_hf->cd();
      
      //makeratio    
      TH1F* ratio_hf=(TH1F*)hCSV_data_tag->Clone(); 
      ratio_hf->SetTitle("");
      ratio_hf->SetXTitle(xtitle_hf);
      ratio_hf->Sumw2();
      ratio_hf->SetStats(0);
      ratio_hf->Divide(mc_norm);
      ratio_hf->SetMarkerStyle(20);
      ratio_hf->Draw("SAMEE0");
      ratio_hf->SetMaximum(1.59);
      ratio_hf->SetMinimum(0.38);
      //set_ratioattributes
      Styleratio(ratio_hf,xtitle_hf,"data/MC"); 
      
      line_tag->Draw();

      c1->SaveAs("CSV_ratio_hf_TagJet.pdf");
 
  outfile->Close();

}



int main(){
  TFile* histos=new TFile("../analysetrees/histos.root");
  
  calculate_sf(histos);

}