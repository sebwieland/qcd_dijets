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

using namespace std;

void triggerstudies(){
  TH1F* h_ptavg=new TH1F("h_ptavg","h_ptavg",175,0,1500);
  
  TH1F* h_ptavg_DiPFJetAve60_vX=new TH1F("h_ptavg_DiPFJetAve60_vX","h_ptavg_DiPFJetAve60_vX",100,0,200);
  TH1F* h_ptavg_PFJet60_vX=new TH1F("h_ptavg_PFJet60_vX","h_ptavg_PFJet60_vX",100,0,200);
  TH1F* h_ptavg_DiPFJetAve60_HFJEC_vX=new TH1F("h_ptavg_DiPFJetAve60_HFJEC_vX","h_ptavg_DiPFJetAve60_HFJEC_vX",100,0,200);
  TH1F* h_ptavg_DiPFJetAve80_vX=new TH1F("h_ptavg_PFJetAve80_vX","h_ptavg_PFJetAve80_vX",100,0,200);
  
  TH1F* h_pt0_DiPFJetAve60_vX=new TH1F("h_pt0_DiPFJetAve60_vX","h_pt0_DiPFJetAve60_vX",100,0,200);
  TH1F* h_pt0_DiPFJetAve60_HFJEC_vX=new TH1F("h_pt0_DiPFJetAve60_HFJEC_vX","h_pt0_DiPFJetAve60_HFJEC_vX",100,0,200);
  TH1F* h_pt0_PFJet60_vX=new TH1F("h_pt0_PFJet60_vX","h_pt0_PFJet60_vX",100,0,200);
  TH1F* h_pt0_DiPFJetAve80_vX=new TH1F("h_pt0_PFJetAve80_vX","h_pt0_PFJetAve80_vX",100,0,200);
  
  
  
  TH1F* h_jeteta0=new TH1F("h_jeteta0","jeteta0",50,-6,6);
    
  TChain* tree_data = new TChain("MVATree");

  tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_0.root");
  tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_1.root");
  tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_2.root");
  tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_3.root");
  tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_4.root");
  tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_5.root");
  tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_6.root");
  tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_7.root");
  tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_8.root");
  tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_9.root");

  float* Jet_CSV = new float[120];
  tree_data->SetBranchAddress("Jet_CSV",Jet_CSV);
  float* Jet_Pt = new float[120];
  tree_data->SetBranchAddress("Jet_Pt",Jet_Pt);
  float dphi;
  tree_data->SetBranchAddress("DeltaPhi",&dphi);
  float PtAvg;
  tree_data->SetBranchAddress("PtAve",&PtAvg);
  int N_Jets;
  tree_data->SetBranchAddress("N_Jets",&N_Jets);
  float* Jet_Eta_data = new float[120];
  tree_data->SetBranchAddress("Jet_Eta",Jet_Eta_data); 
  int trigg_DiPFJetAve60_vX;
  tree_data->SetBranchAddress("Triggered_HLT_DiPFJetAve60_vX",&trigg_DiPFJetAve60_vX);
  int trigg_DiPFJetAve60_HFJEC_vX;
  tree_data->SetBranchAddress("Triggered_HLT_DiPFJetAve60_HFJEC_vX",&trigg_DiPFJetAve60_HFJEC_vX);
  int trigg_PFJet60_vX;
  tree_data->SetBranchAddress("Triggered_HLT_PFJet60_vX",&trigg_PFJet60_vX);
  int trigg_DiPFJetAve80_vX=0;
  tree_data->SetBranchAddress("Triggered_HLT_DiPFJetAve80_vX",&trigg_DiPFJetAve80_vX);
  
  
  
  float dphicut=2.7;

  float nentries_data = tree_data->GetEntries(); 
  cout << "total number of data events: " << nentries_data << endl;
  for (long iEntry=0;iEntry<nentries_data;iEntry++) {
    if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//     if(iEntry>1000000) break;
    tree_data->GetEntry(iEntry);
    h_jeteta0->Fill(Jet_Eta_data[0]);
    if (dphi > dphicut){
      if (abs(Jet_Eta_data[0])<2.1 && abs(Jet_Eta_data[1])<2.1){
	h_ptavg->Fill(PtAvg);	
	if (trigg_DiPFJetAve60_vX==1) {
	  h_ptavg_DiPFJetAve60_vX->Fill(PtAvg);
	  h_pt0_DiPFJetAve60_vX->Fill(Jet_Pt[0]);
	}
	if (trigg_DiPFJetAve60_HFJEC_vX==1){
	  h_ptavg_DiPFJetAve60_HFJEC_vX->Fill(PtAvg);
	  h_pt0_DiPFJetAve60_HFJEC_vX->Fill(Jet_Pt[0]);
	}
	if (trigg_PFJet60_vX==1){
	  h_ptavg_PFJet60_vX->Fill(PtAvg);
	  h_pt0_PFJet60_vX->Fill(Jet_Pt[0]);	  
	}
	if (trigg_DiPFJetAve80_vX==1){
	  h_ptavg_DiPFJetAve80_vX->Fill(PtAvg);
	  h_pt0_DiPFJetAve80_vX->Fill(Jet_Pt[0]);	  
	}
      }
    }
  }
TCanvas* c1=new TCanvas();
TFile* outfile=new TFile("triggerstudies.root","RECREATE"); 
c1->cd();
h_ptavg->Draw("hist");
h_ptavg->GetXaxis()->SetTitle("Pt Avg");
h_ptavg->Write();
c1->SaveAs("PtAvg.png");

h_jeteta0->Draw("hist");
h_jeteta0->GetXaxis()->SetTitle("Eta[0]");
h_jeteta0->Write();
c1->SaveAs("jeteta0.png");

h_ptavg_DiPFJetAve60_vX->Draw("hist");
h_ptavg_DiPFJetAve60_vX->GetXaxis()->SetTitle("triggered DiPFJetAve60_vX");
h_ptavg_DiPFJetAve60_vX->Write();
c1->SaveAs("ptavg_triggered DiPFJetAve60_vX.png");

h_ptavg_DiPFJetAve60_HFJEC_vX->Draw("hist");
h_ptavg_DiPFJetAve60_HFJEC_vX->GetXaxis()->SetTitle("triggered DiPFJetAve60_HFJEC_vX");
h_ptavg_DiPFJetAve60_HFJEC_vX->Write();
c1->SaveAs("ptavg_triggered DiPFJetAve60_HFJEC_vX.png");

h_ptavg_PFJet60_vX->Draw("hist");
h_ptavg_PFJet60_vX->GetXaxis()->SetTitle("triggered PFJet60_vX");
h_ptavg_PFJet60_vX->Write();
c1->SaveAs("ptavg_triggered PFJet60_vX.png");

h_ptavg_DiPFJetAve80_vX->Draw("hist");
h_ptavg_DiPFJetAve80_vX->GetXaxis()->SetTitle("triggered DiPFJetAve80_vX");
h_ptavg_DiPFJetAve80_vX->Write();
c1->SaveAs("ptavg_triggeredDiPFJetAve80_vX.png");




h_pt0_DiPFJetAve60_vX->Draw("hist");
h_pt0_DiPFJetAve60_vX->GetXaxis()->SetTitle("pt hardest Jet, DiPFJetAve60_vX triggered");
h_pt0_DiPFJetAve60_vX->Write();
c1->SaveAs("h_pt0_DiPFJetAve60_vX.png");

h_pt0_DiPFJetAve60_HFJEC_vX->Draw("hist");
h_pt0_DiPFJetAve60_HFJEC_vX->GetXaxis()->SetTitle("pt hardest Jet, DiPFJetAve60_HFJEC_vX triggered");
h_pt0_DiPFJetAve60_HFJEC_vX->Write();
c1->SaveAs("h_pt0_DiPFJetAve60_HFJEC_vX.png");

h_pt0_PFJet60_vX->Draw("hist");
h_pt0_PFJet60_vX->GetXaxis()->SetTitle("pt hardest Jet, PFJet60_vX triggered");
h_pt0_PFJet60_vX->Write();
c1->SaveAs("h_pt0_PFJet60_vX.png");

h_pt0_DiPFJetAve80_vX->Draw("hist");
h_pt0_DiPFJetAve80_vX->GetXaxis()->SetTitle("pt hardest Jet, DiPFJetAve80_vX triggered");
h_pt0_DiPFJetAve80_vX->Write();
c1->SaveAs("h_pt0_DiPFJetAve80_vX.png");


outfile->Close();


}

int main(){
triggerstudies();    
}
