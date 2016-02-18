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
#include "TH1D.h"
#include "TF1.h"
#include "TVirtualFitter.h"
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
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetXaxis()->SetLabelSize(0.05);
  h->GetXaxis()->SetNdivisions(510);

  h->GetYaxis()->SetTitle(yTitle);
  h->GetYaxis()->SetTitleFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetYaxis()->SetTitleOffset(1);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetLabelSize(0.05);
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
  //outputfile
//   TFile* outfile=new TFile("scalefactors.root","RECREATE");
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
  

  cout << "Reading Histos from file" << endl;
  vector<vector<TH1F*>>h_data=readhistos(histos,'d');
  vector<vector<TH1F*>>h_b=readhistos(histos,'b');
  vector<vector<TH1F*>>h_c=readhistos(histos,'c');
  vector<vector<TH1F*>>h_lf=readhistos(histos,'l');
  
  TString eta_counter="0";
  TString pt_counter="0";
  bool comp=false;
  bool normpt=false;
  //read official SF
  TFile* officialfile=new TFile("~/qcd_dijets/comparison_lf/csv_rwt_fit_lf_2015_11_20.root");
  int n_ptbins= 10;
  int n_etabins=3;
  vector<vector<TH1F*>> official;
  official.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  if(comp==true){
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
	TH1F* h = (TH1F*)officialfile->Get("csv_ratio_Pt"+pt_counter+"_Eta"+eta_counter+"_final");
	official[i][j]=h;
      }
    }      
  }
//   officialfile->Close();
  TFile* result=new TFile("result.root","RECREATE");
  //SetColors
//   n_ptbins= 10;
  n_etabins=4;
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
  
  char xtitle_lf[]="CSV probe Jet (LF)";
  
  double  n_events_lf;
  float mcevents=0;
  float normratio=0;
  float dataevents=0;
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
   
      TLegend* leg_lf=new TLegend(0.75,0.4,0.9,0.8);
      leg_lf->AddEntry(h_data[i][j],"data");
      leg_lf->AddEntry(h_b[i][j],"b");
      leg_lf->AddEntry(h_c[i][j],"c");
      leg_lf->AddEntry(h_lf[i][j],"lf");
      leg_lf->SetFillStyle(0);
      leg_lf->SetBorderSize(0);
      
      TCanvas *c1=new TCanvas();
      c1->cd();
      //makepadhist
      TPad* padhist_lf=new TPad("padhist_lf","padhist_lf",0,0.3,1,1);
      padhist_lf->SetBottomMargin(0);
      padhist_lf->Draw();
      padhist_lf->cd();
      TH1F* mc=(TH1F*)h_b[i][j]->Clone(); 
      mc->Add(h_c[i][j]);
      mc->Add(h_lf[i][j]);
  //     mc_stack[i][j]->Print();
  //     TH1F* mc=(TH1F*)mc_stack[i][j]->GetStack();
      n_events_lf=h_lf[i][j]->Integral();
      mcevents=mc->Integral();
      cout << "pt bin "<< i << ", eta bin "<< j <<endl;
      dataevents=h_data[i][j]->Integral();
      cout << "data events: "<< dataevents  << endl;
      
      cout << "mcevents before normalization: " << mcevents << endl;
      
      if(normpt==true){
	if (mcevents!=0) normratio=dataevents/mcevents;
	  else normratio=1;
	h_b[i][j]->Scale(normratio);
	h_c[i][j]->Scale(normratio);
	h_lf[i][j]->Scale(normratio);
	h_b[i][j]->Sumw2();
	h_c[i][j]->Sumw2();
	h_lf[i][j]->Sumw2();
      }
      
      THStack* mc_stack_lf_normalized=new THStack();
      mc_stack_lf_normalized->Add(h_b[i][j]);
      mc_stack_lf_normalized->Add(h_c[i][j]);
      mc_stack_lf_normalized->Add(h_lf[i][j]);
      TH1F* mc_norm=(TH1F*)mc_stack_lf_normalized->GetStack()->Last();
      cout << "mcevents after normalization: " << mc_norm->Integral() << endl;
      cout << "Purity: " << n_events_lf/mcevents << endl;
    
  //     //draw histos
      h_data[i][j]->Sumw2();
      mc_stack_lf_normalized->Draw("histE0");
      Stylestack(mc_stack_lf_normalized,"","events");
      h_data[i][j]->SetMarkerStyle(20);
      h_data[i][j]->Draw("SAMEE0");
      leg_lf->Draw();
      text->DrawLatex(0.4, 0.863, text_cms);
      text->DrawLatex(0.4, 0.815, cutlabel);
      c1->cd();
      //makepadratio
      TPad* padratio_lf=new TPad("padratio_lf","padratio_lf",0,0,1,0.3);
      padratio_lf->SetTopMargin(0);
//       padratio_lf->SetBottomMargin(1.1);
      padratio_lf->Draw();
      padratio_lf->cd();
      
      //makeratio    
      TH1F* ratio_lf=(TH1F*)h_data[i][j]->Clone(); 
      ratio_lf->SetTitle("");
      ratio_lf->SetXTitle(xtitle_lf);
      ratio_lf->Sumw2();
      ratio_lf->SetStats(0);
      ratio_lf->Divide(mc_norm);
      ratio_lf->SetMarkerStyle(20);
      ratio_lf->Draw("SAMEE0");
      ratio_lf->SetMaximum(1.6);
      ratio_lf->SetMinimum(0.4);
      //set_ratioattributes  
      Styleratio(ratio_lf,xtitle_lf,"data/MC");  
      
      line->Draw();
      stringstream ss;
      ss << i;
      TString counter=ss.str();
      c1->SaveAs("CSV_ratio_lf_ptbin"+pt_counter+"_etabin"+eta_counter+".pdf");


      //subtract HF contamination
      TCanvas *c2=new TCanvas(); 
      c2->cd(); 
      c2->SetBottomMargin(0.15);
      TH1F *diff_lf=(TH1F*)h_data[i][j]->Clone();
      diff_lf->Sumw2();
      diff_lf->SetTitle("Data-HF");
      diff_lf->Add(h_b[i][j],-1);
      diff_lf->Add(h_c[i][j],-1);
      diff_lf->Draw("E0");    
      diff_lf->SetMarkerStyle(20);
      diff_lf->SetLineColor(kBlue);
      Style(diff_lf,xtitle_lf,"events");
//       diff_lf->Write();
	
      TH1F* lf=(TH1F*)h_lf[i][j]->Clone();
//       nonb_lf->Add(h_c[i][j]);
      lf->Draw("SAMEE0");
      lf->SetTitle("LF");
      lf->SetMarkerStyle(4);
//       lf->SetMarkerSize(0.7);
      lf->SetFillColor(0);
      lf->SetLineColor(kRed);
//       lf->Write();
      c2->BuildLegend(0.5,0.8,0.9,0.9);
      c2->SaveAs("diff_lf_ptbin"+pt_counter+"_etabin"+eta_counter+".pdf");
    
      //calculate LFSF
      TH1F* lfsf=(TH1F*)diff_lf->Clone("clone_diff_lf_ptbin"+pt_counter+"_etabin"+eta_counter);
      lfsf->Divide(lf);
      //fit with 6th order polnomial
      // gStyle->SetOptFit(000000000);
      // gStyle->SetOptStat(000000000);
      lfsf->Write();
      TF1* pol=new TF1("LFSF_ptbin"+pt_counter+"_etabin"+eta_counter,"pol6",0,1);
      lfsf->Fit(pol,"S","",0,1);
      lfsf->Draw("E0");
      Style(lfsf,xtitle_lf,"LFSF");
      
      if ( i!=0 && j!=0 ){
	TH1D *hint = new TH1D("hint_ptbin"+pt_counter+"_etabin"+eta_counter,"Fitted gaussian with .95 conf.band", 1000, 0, 1);
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint);
	hint->Write();
      }
      
      if ( i!=0 && j!=0 && comp==true){
	official[i-1][j-1]-> Draw("SAME");
      }
//       lfsf->GetYaxis()->SetLabelSize(0.04);
//       lfsf->GetXaxis()->SetTitle("LFSF");
//       lfsf->GetXaxis()->SetTitleSize(0.04);
//       lfsf->GetXaxis()->SetNdivisions(510);
//       lfsf->GetXaxis()->SetLabelSize(0.04);
//       line->Draw();
//       lfsf->Write();
//       lfsf->GetXaxis()->SetTitle("LFSF");
      lfsf->SetMaximum(2);
      lfsf->SetMinimum(0);
     
      c2->SaveAs("LFSF_ptbin"+pt_counter+"_etabin"+eta_counter+".pdf");
      

      c2->cd();
      //Transform to Histogram
      if ( i!=0 && j!=0){
	TH1F* sf=new TH1F("LFSF_pt"+pt_counter+"_eta"+eta_counter,"LFSF_pt"+pt_counter+"_eta"+eta_counter,100000,0,1);
	for (int k=1; k<=100000; ++k){
	  sf->SetBinContent(k,pol->Eval((k-1)*0.00001));
	}
	sf->Write();
      }
      
//       pol->Draw();
//       pol->Write();
      
      leg_lf->Delete();
      padhist_lf->Delete();
      mc->Delete();
      mc_stack_lf_normalized->Delete();
      padratio_lf->Delete();
      ratio_lf->Delete();
      diff_lf->Delete();
      lf->Delete();
      lfsf->Delete();
//       outfile->Write();

    } 
  }
//   outfile->Close();
  
  
  
}
  











int main(){
  TFile* histos=new TFile("../analysetrees/histos.root");
  
  calculate_sf(histos);

}