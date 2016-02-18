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
#include "TStyle.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

void compare_lf(){
  

    gStyle->SetErrorX(0); 
  //outputfile

  TFile* nominalfile=new TFile("~/qcd_dijets/scalefactor_lf_nominal/scalefactor/result.root");
  TFile* HFupfile=new TFile("~/qcd_dijets/scalefactor_lf_HFup/result_HFup.root");
  TFile* HFdownfile=new TFile("~/qcd_dijets/scalefactor_lf_HFdown/result_HFdown.root");
  TFile* JECupfile=new TFile("~/qcd_dijets/JEC-uncertainty/JEC_up/scalefactor_lf_JECup/scalefactor_JECup/result_JECup.root");
  TFile* JECdownfile=new TFile("~/qcd_dijets/JEC-uncertainty/JEC_down/scalefactor_lf_JECdown/scalefactor_JECdown/result_JECdown.root");

  int n_ptbins=10;
  int n_etabins=4;
  
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
  
  vector<vector<TH1F*>> JECover;
  JECover.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> JEClower;
  JEClower.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  
  vector<vector<TH1F*>> HFover;
  HFover.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> HFlower;
  HFlower.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  
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
	TH1F* tmpJECover=(TH1F*)JECup[i][j]->Clone();
	TH1F* tmpJEClower=(TH1F*)JECup[i][j]->Clone();
	TH1F* tmpHFover=(TH1F*)JECup[i][j]->Clone();
	TH1F* tmpHFlower=(TH1F*)JECup[i][j]->Clone();
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
	  tmpJECover->SetBinContent(k,over_JEC);
	  tmpJEClower->SetBinContent(k,lower_JEC);
	  tmpHFover->SetBinContent(k,over_hf);
	  tmpHFlower->SetBinContent(k,lower_hf);
	}
	tmpover->Add(hist);
	tmplower->Add(hist,-1);
	tmplower->Scale(-1);
	
	tmpJECover->Add(hist);
	tmpJEClower->Add(hist,1);
// 	tmpJEClower->Scale(-1);
	
	tmpHFover->Add(hist);
	tmpHFlower->Add(hist,1);
// 	tmpHFlower->Scale(-1);
	
	uncover[i][j]=tmpover;
	unclower[i][j]=tmplower;
	uncover[i][j]->SetLineColor(kViolet);
	unclower[i][j]->SetLineColor(kViolet);

	JECover[i][j]=tmpJECover;
	JEClower[i][j]=tmpJEClower;
	JECover[i][j]->SetLineColor(kViolet);
	JEClower[i][j]->SetLineColor(kViolet);
	
	HFover[i][j]=tmpHFover;
	HFlower[i][j]=tmpHFlower;
	HFover[i][j]->SetLineColor(kCyan);
	HFlower[i][j]->SetLineColor(kCyan);
      }
    }
    
  cout << "all histos rdy"<< endl;
  TFile* outfile=new TFile("RESULT.root","RECREATE"); 
  TCanvas* c=new TCanvas();
  TCanvas* c2=new TCanvas();
  TCanvas* c3=new TCanvas();
  TCanvas* c4=new TCanvas();
  TLine* line=new TLine(-0.02,1,1,1);
  line->SetLineColor(kBlack);
  TLegend* leg=new TLegend(0.75,0.4,0.9,0.8);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
  
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
      c->cd(); 
      TLegend* leg=new TLegend(0.1,0.6,0.48,0.9);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);  
      leg->SetTextSize(0.05),
      
      nominal[i][j]->SetMarkerStyle(5);
      nominal[i][j]->SetMarkerSize(0.7);
      nominal[i][j]->SetTitle("");
      nominal[i][j]->GetXaxis()->SetTitle("CSV");
      nominal[i][j]->GetXaxis()->SetTitleSize(0.05);
      nominal[i][j]->GetXaxis()->SetTitleOffset(0.8);
      nominal[i][j]->GetYaxis()->SetTitle("SF");
      nominal[i][j]->GetYaxis()->SetTitleSize(0.08);
      nominal[i][j]->GetYaxis()->SetTitleOffset(0.45);
      nominal[i][j]->Draw("");   
      nominal[i][j]->SetLineColor(kRed);
      nominal[i][j]->SetMaximum(2);
      nominal[i][j]->SetMinimum(0);
      nominal[i][j]->SetLineWidth(3);
      
      staterror[i][j]->Draw("same e3");
      staterror[i][j]->SetLineColor(kGreen);
      staterror[i][j]->SetFillColorAlpha(kGreen,0.35);
      
      nominaldots[i][j]->Draw("sameeo");
      uncover[i][j]->Draw("same");
      unclower[i][j]->Draw("same");      
      
      line->Draw("same");
      leg->AddEntry(nominal[i][j],"nominal LFSF","L");
      leg->AddEntry(uncover[i][j],"combined systematic uncertainty","L");
      leg->AddEntry(staterror[i][j],"statistical uncertainty","L");
      leg->Draw("same");
      c->SaveAs("LFSF_pt"+pt_counter+"_eta"+eta_counter+"_final.pdf"); 
      c->Write();
      leg->Delete();
      
      //plot only JEC 
      c2->cd();
      TLegend* leg2=new TLegend(0.1,0.7,0.48,0.9);
      leg2->SetFillStyle(0);
      leg2->SetBorderSize(0);  
      nominal[i][j]->Draw("");
      nominaldots[i][j]->Draw("sameeo");
 
      JECover[i][j]->Draw("same");
      JEClower[i][j]->Draw("same");    
      
      line->Draw("same");
      leg2->AddEntry(nominal[i][j],"nominal LFSF");
      leg2->AddEntry(JECover[i][j],"JEC uncertainty");
      leg2->Draw("same");
      c2->SaveAs("LFSF_pt"+pt_counter+"_eta"+eta_counter+"_JEConly.pdf"); 
      c2->Write();
      leg2->Delete();
      
      //plot only HF 
      c3->cd();
      TLegend* leg3=new TLegend(0.1,0.7,0.48,0.9);
      leg3->SetFillStyle(0);
      leg3->SetBorderSize(0);  
      nominal[i][j]->Draw("");
      nominaldots[i][j]->Draw("sameeo");
 
      HFover[i][j]->Draw("same");
      HFlower[i][j]->Draw("same");    
      
      line->Draw("same");
      leg3->AddEntry(nominal[i][j],"nominal LFSF");
      leg3->AddEntry(HFover[i][j],"HF uncertainty");
      leg3->Draw("same");
      c3->SaveAs("LFSF_pt"+pt_counter+"_eta"+eta_counter+"_HFonly.pdf"); 
      c3->Write();
      leg3->Delete();
      
      //plot only Statistical
      c4->cd();
      TLegend* leg4=new TLegend(0.1,0.7,0.48,0.9);
      leg4->SetFillStyle(0);
      leg4->SetBorderSize(0);    
      nominal[i][j]->Draw("");
      staterror[i][j]->Draw("same e3"); 
      nominaldots[i][j]->Draw("sameeo");      
      line->Draw("same");
      leg4->AddEntry(nominal[i][j],"nominal LFSF");
      leg4->AddEntry(staterror[i][j],"statistical uncertainty");
      leg4->Draw("same");
      c4->SaveAs("LFSF_pt"+pt_counter+"_eta"+eta_counter+"_statonly.pdf"); 
      c4->Write();
      leg4->Delete();
    }
  }

  
  




  
  

//   outfile->Write();



  outfile->Close();
  
  
  
}
  











int main(){
  
  compare_lf();

}