#include "TBranch.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TChain.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TLine.h"
#include "TH1F.h"
#include "TF1.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TVirtualFitter.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


void compare_lf(){
  //outputfile

  TFile* nominalfile=new TFile("~/qcd_dijets/scalefactor_lf_nominal/scalefactor/result.root");
  TFile* HFupfile=new TFile("~/qcd_dijets/scalefactor_lf_HFup/result_HFup.root");
  TFile* HFdownfile=new TFile("~/qcd_dijets/scalefactor_lf_HFdown/result_HFdown.root");
  TFile* JECupfile=new TFile("~/qcd_dijets/JEC-uncertainty/JEC_up/scalefactor_lf_JECup/scalefactor_JECup/result_JECup.root");
  TFile* JECdownfile=new TFile("~/qcd_dijets/JEC-uncertainty/JEC_down/scalefactor_lf_JECdown/scalefactor_JECdown/result_JECdown.root");

  int n_ptbins=10;
  int n_etabins=3;
  
  TString eta_counter="0";
  TString pt_counter="0";
  
  vector<vector<TH1F*>> nominal;
  nominal.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> nominaldots;
  nominaldots.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  
  vector<vector<TH1D*>> staterror;
  staterror.resize(n_ptbins, vector<TH1D*>(n_etabins, 0));
  
  vector<vector<TH1F*>> JECup;
  JECup.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> JECdown;
  JECdown.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  
  vector<vector<TH1F*>> HFup;
  HFup.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> HFdown;
  HFdown.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  
  vector<vector<TH1F*>> uncover;
  uncover.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> unclower;
  unclower.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  cout << "read histos" << endl;
  for (int i=1; i<n_ptbins;++i){
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
      for ( int j=1; j<n_etabins;++j){   
	if (j==0) eta_counter="0";
	else if (j==1) eta_counter="1";
	else if (j==2) eta_counter="2";   
	else if (j==3) eta_counter="3"; 
	TH1F* dots = (TH1F*)nominalfile->Get("clone_diff_lf_ptbin"+pt_counter+"_etabin"+eta_counter);
	nominaldots[i][j]=dots;
	nominaldots[i][j]->SetStats(0);
	
	TH1D* h_stat = (TH1D*)nominalfile->Get("hint_ptbin"+pt_counter+"_etabin"+eta_counter);
	staterror[i][j]=h_stat;
	staterror[i][j]->SetStats(0);
	
	TH1F* hist = (TH1F*)nominalfile->Get("LFSF_pt"+pt_counter+"_eta"+eta_counter);
	nominal[i][j]=hist;
	nominal[i][j]->SetStats(0);
	
	TH1F* h_JECup = (TH1F*)JECupfile->Get("LFSF_pt"+pt_counter+"_eta"+eta_counter+"_JECup");
	JECup[i][j]=h_JECup;
	TH1F* h_JECdown = (TH1F*)JECdownfile->Get("LFSF_pt"+pt_counter+"_eta"+eta_counter+"_JECdown");
	JECdown[i][j]=h_JECdown;
	
	TH1F* h_hfup = (TH1F*)HFupfile->Get("LFSF_pt"+pt_counter+"_eta"+eta_counter+"_HFup");
	HFup[i][j]=h_hfup;
	TH1F* h_hfdown = (TH1F*)HFdownfile->Get("LFSF_pt"+pt_counter+"_eta"+eta_counter+"_HFdown");
	HFdown[i][j]=h_hfdown;
	cout << "histos read" << endl;

	
	h_JECup->Add(hist,-1);
	h_JECdown->Add(hist,-1);
	h_hfup->Add(hist,-1);
	h_hfdown->Add(hist,-1);
	TH1F* tmpover=(TH1F*)HFup[i][j]->Clone();
	TH1F* tmplower=(TH1F*)HFup[i][j]->Clone();
	for (int k=1; k<= hist->GetNbinsX();++k){
	  float over_JECup=0;
	  float lower_JECup=0;
	  
	  float over_JECdown=0;
	  float lower_JECdown=0;
	  
	  float over_hfup=0;
	  float lower_hfup=0;
	  
	  float over_hfdown=0;
	  float lower_hfdown=0;
	  if (h_JECup->GetBinContent(k)>0) 	over_JECup=h_JECup->GetBinContent(k); 	  
	  else if (h_JECup->GetBinContent(k)<0)  lower_JECup=h_JECup->GetBinContent(k); 
	  else if (h_JECup->GetBinContent(k)==0) {lower_JECup=0; over_JECup=0;} 
	  
	  if (h_JECdown->GetBinContent(k)>0)	 over_JECdown=h_JECdown->GetBinContent(k); 	  
	  else if (h_JECdown->GetBinContent(k)<0) lower_JECdown=h_JECdown->GetBinContent(k); 
	  else if (h_JECdown->GetBinContent(k)==0)  {lower_JECdown=0; over_JECdown=0;}
	  
	  
	  if (h_hfup->GetBinContent(k)>0)  	over_hfup=h_hfup->GetBinContent(k); 	  
	  else if (h_hfup->GetBinContent(k)<0)   lower_hfup=h_hfup->GetBinContent(k); 
	  else if (h_hfup->GetBinContent(k)==0) {lower_hfup=0;over_hfup=0;} 
	  
	  if (h_hfdown->GetBinContent(k)>0)  	over_hfdown=h_hfdown->GetBinContent(k); 	  
	  else if (h_hfdown->GetBinContent(k)<0) lower_hfdown=h_hfdown->GetBinContent(k);
	  else if (h_hfdown->GetBinContent(k)==0)  {lower_hfdown=0;over_hfdown=0;}
	  
	  float over_JEC=over_JECup+over_JECdown;
	  float lower_JEC=lower_JECup+lower_JECdown;
	  float over_hf=over_hfup+over_hfdown;
	  float lower_hf=lower_hfup+lower_hfdown;
	  float over=pow(over_hf,2)+pow(over_JEC,2);
	  float lower=pow(lower_hf,2)+pow(lower_JEC,2);
	  
	  tmpover->SetBinContent(k,sqrt(over));
	  tmplower->SetBinContent(k,sqrt(lower));
	}
	tmpover->Add(hist);
	tmplower->Add(hist,-1);
	tmplower->Scale(-1);
	
	uncover[i][j]=tmpover;
	unclower[i][j]=tmplower;
	uncover[i][j]->SetLineColor(kGray);
	unclower[i][j]->SetLineColor(kGray);	
      }
    }
    
    
  TFile* outfile=new TFile("RESULT.root","RECREATE"); 
  TCanvas* c=new TCanvas();
  TLine* line=new TLine(-0.02,1,1,1);
  line->SetLineColor(kBlack);
  TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
  c->cd();  
  for (int i=1; i<n_ptbins;++i){
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
      for ( int j=1; j<n_etabins;++j){   
	if (j==0) eta_counter="0";
	else if (j==1) eta_counter="1";
	else if (j==2) eta_counter="2";   
	else if (j==3) eta_counter="3"; 
      TLegend* leg=new TLegend(0.1,0.7,0.48,0.9);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);  
      
      nominal[i][j]->SetMarkerStyle(5);
      nominal[i][j]->SetMarkerSize(0.7); 
      nominal[i][j]->Draw("");      
      nominal[i][j]->SetMaximum(2);
      nominal[i][j]->SetMinimum(0);
//       nominal[i][j]->SetLineWidth(6);
      
      staterror[i][j]->Draw("same");
      staterror[i][j]->SetLineColor(kGreen);
      
      nominaldots[i][j]->Draw("sameeo");
      uncover[i][j]->Draw("same");
      unclower[i][j]->Draw("same");
      
      
      
      line->Draw("same");
      leg->AddEntry(nominal[i][j],"nominal LFSF");
      leg->AddEntry(uncover[i][j],"combined systematic uncertainty");
      leg->AddEntry(staterror[i][j],"statistical uncertainty");
      leg->Draw("same");
      c->SaveAs("LFSF_pt"+pt_counter+"_eta"+eta_counter+"_final.png"); 
      c->Write();
      leg->Delete();
    }
  }

  
  




  
  

//   outfile->Write();



  outfile->Close();
  
  
  
}
  











int main(){
  
  compare_lf();

}