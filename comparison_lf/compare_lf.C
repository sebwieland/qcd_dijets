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
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


void compare_lf(){
  //outputfile

  TFile* qcdfile=new TFile("../scalefactor_lf/scalefactor/result.root");
  int n_ptbins= 5;
  int n_etabins=4;
  TString eta_counter="0";
  TString pt_counter="0";
  vector<vector<TH1F*>> qcd;
  qcd.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> qcd_hist;
  qcd_hist.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  cout << "read QCD histos" << endl;
  for (int i=0; i<n_ptbins;++i){
      if (i==0) pt_counter="0";
      else if (i==1) pt_counter="1";
      else if (i==2) pt_counter="2";
      else if (i==3) pt_counter="3";
      else if (i==4) pt_counter="4";
      for ( int j=0; j<n_etabins;++j){   
	if (j==0) eta_counter="0";
	else if (j==1) eta_counter="1";
	else if (j==2) eta_counter="2";   
	else if (j==3) eta_counter="3"; 
	TH1F* h = (TH1F*)qcdfile->Get("clone_diff_lf_ptbin"+pt_counter+"_etabin"+eta_counter);
	qcd[i][j]=h;
	qcd[i][j]->SetStats(0);
	if ( i!=0 && j!=0){
	  TH1F* hist = (TH1F*)qcdfile->Get("LFSF_pt"+pt_counter+"_eta"+eta_counter);
	  qcd_hist[i][j]=hist;
	  qcd_hist[i][j]->SetLineColor(kRed);
	}
      }
    }
    
  TFile* officialfile=new TFile("csv_rwt_fit_lf_2015_11_20.root");
  n_ptbins= 4;
  n_etabins=3;
  vector<vector<TH1F*>> official;
  official.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> official_jesup;
  official_jesup.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> official_jesdown;
  official_jesdown.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> official_hfup;
  official_hfup.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> official_hfdown;
  official_hfdown.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  
  vector<vector<TH1F*>> official_uncover;
  official_uncover.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> official_unclower;
  official_unclower.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  cout << "read official histos" << endl;
  for (int i=0; i<n_ptbins;++i){
      if (i==0) pt_counter="0";
      else if (i==1) pt_counter="1";
      else if (i==2) pt_counter="2";
      else if (i==3) pt_counter="3";
      for ( int j=0; j<n_etabins;++j){   
	if (j==0) eta_counter="0";
	else if (j==1) eta_counter="1";
	else if (j==2) eta_counter="2";   
	TH1F* h = (TH1F*)officialfile->Get("csv_ratio_Pt"+pt_counter+"_Eta"+eta_counter+"_final");
	official[i][j]=h;
	official[i][j]->SetStats(0);
	
	TH1F* h_jesup = (TH1F*)officialfile->Get("csv_ratio_Pt"+pt_counter+"_Eta"+eta_counter+"_final_JESUp");
	official_jesup[i][j]=h_jesup;
	TH1F* h_jesdown = (TH1F*)officialfile->Get("csv_ratio_Pt"+pt_counter+"_Eta"+eta_counter+"_final_JESDown");
	official_jesdown[i][j]=h_jesdown;
	
	TH1F* h_hfup = (TH1F*)officialfile->Get("csv_ratio_Pt"+pt_counter+"_Eta"+eta_counter+"_final_HFUp");
	official_hfup[i][j]=h_hfup;
	TH1F* h_hfdown = (TH1F*)officialfile->Get("csv_ratio_Pt"+pt_counter+"_Eta"+eta_counter+"_final_HFDown");
	official_hfdown[i][j]=h_hfdown;

	
	h_jesup->Add(h,-1);
	h_jesdown->Add(h,-1);
	h_hfup->Add(h,-1);
	h_hfdown->Add(h,-1);
	TH1F* tmpover=(TH1F*)official_hfup[i][j]->Clone();
	TH1F* tmplower=(TH1F*)official_hfup[i][j]->Clone();
	for (int k=1; k<= h->GetNbinsX();++k){
	  float over_jesup=0;
	  float lower_jesup=0;
	  
	  float over_jesdown=0;
	  float lower_jesdown=0;
	  
	  float over_hfup=0;
	  float lower_hfup=0;
	  
	  float over_hfdown=0;
	  float lower_hfdown=0;
	  if (h_jesup->GetBinContent(k)>0) 	over_jesup=h_jesup->GetBinContent(k); 	  
	  else if (h_jesup->GetBinContent(k)<0)  lower_jesup=h_jesup->GetBinContent(k); 
	  else if (h_jesup->GetBinContent(k)==0) {lower_jesup=0; over_jesup=0;} 
	  
	  if (h_jesdown->GetBinContent(k)>0)	 over_jesdown=h_jesdown->GetBinContent(k); 	  
	  else if (h_jesdown->GetBinContent(k)<0) lower_jesdown=h_jesdown->GetBinContent(k); 
	  else if (h_jesdown->GetBinContent(k)==0)  {lower_jesdown=0; over_jesdown=0;}
	  
	  
	  if (h_hfup->GetBinContent(k)>0)  	over_hfup=h_hfup->GetBinContent(k); 	  
	  else if (h_hfup->GetBinContent(k)<0)   lower_hfup=h_hfup->GetBinContent(k); 
	  else if (h_hfup->GetBinContent(k)==0) {lower_hfup=0;over_hfup=0;} 
	  
	  if (h_hfdown->GetBinContent(k)>0)  	over_hfdown=h_hfdown->GetBinContent(k); 	  
	  else if (h_hfdown->GetBinContent(k)<0) lower_hfdown=h_hfdown->GetBinContent(k);
	  else if (h_hfdown->GetBinContent(k)==0)  {lower_hfdown=0;over_hfdown=0;}
	  
	  float over_jes=over_jesup+over_jesdown;
	  float lower_jes=lower_jesup+lower_jesdown;
	  float over_hf=over_hfup+over_hfdown;
	  float lower_hf=lower_hfup+lower_hfdown;
	  float over=pow(over_hf,2)+pow(over_jes,2);
	  float lower=pow(lower_hf,2)+pow(lower_jes,2);
	  
	  tmpover->SetBinContent(k,sqrt(over));
	  tmplower->SetBinContent(k,sqrt(lower));
	}
	tmpover->Add(h);
	tmplower->Add(h,-1);
	tmplower->Scale(-1);
	
	official_uncover[i][j]=tmpover;
	official_unclower[i][j]=tmplower;
	official_uncover[i][j]->SetLineColor(kGray);
	official_unclower[i][j]->SetLineColor(kGray);	
      }
    }
    
    
  TFile* outfile=new TFile("comparison_lf.root","RECREATE"); 
  TCanvas* c=new TCanvas();
  TLine* line=new TLine(-0.02,1,1,1);
  line->SetLineColor(kBlack);
  TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
  c->cd();  
  for (int i=0; i<n_ptbins;++i){
    
    if (i==0) pt_counter="0";
    else if (i==1) pt_counter="1";
    else if (i==2) pt_counter="2";
    else if (i==3) pt_counter="3";
    for ( int j=0; j<n_etabins;++j){ 
      TLegend* leg=new TLegend(0.75,0.65,0.9,0.8);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
      if (j==0) eta_counter="0";
      else if (j==1) eta_counter="1";
      else if (j==2) eta_counter="2";   
      official[i][j]->Draw();
      official_uncover[i][j]->Draw("same");
      official_unclower[i][j]->Draw("same");
      qcd[i+1][j+1]->Draw("samee0");
      qcd_hist[i+1][j+1]->Draw("same");
      line->Draw("same");
      leg->AddEntry(official[i][j],"official LFSF");
      leg->AddEntry(qcd_hist[i+1][j+1],"QCD based LFSF");
      leg->Draw("same");
      c->SaveAs("LFSF_comparison_pt"+pt_counter+"_eta"+eta_counter+".png"); 
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