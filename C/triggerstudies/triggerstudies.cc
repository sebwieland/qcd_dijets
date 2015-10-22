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
  TH1F* h_ptavg=new TH1F("h_ptavg","h_ptavg",175,0,3500);
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
  float dphi;
  tree_data->SetBranchAddress("DeltaPhi",&dphi);
  float PtAvg;
  tree_data->SetBranchAddress("PtAve",&PtAvg);
  int N_Jets;
  tree_data->SetBranchAddress("N_Jets",&N_Jets);
  float* Jet_Eta_data = new float[120];
  tree_data->SetBranchAddress("Jet_Eta",Jet_Eta_data); 
  
  float dphicut=2.7;

  float nentries_data = tree_data->GetEntries(); 
  cout << "total number of data events: " << nentries_data << endl;
  for (long iEntry=0;iEntry<nentries_data;iEntry++) {
    if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//     if(iEntry>1000000) break;
    tree_data->GetEntry(iEntry);
    //LF tagging
    h_jeteta0->Fill(Jet_Eta_data[0]);
    for(int j=0;j<2;j++){
      if (dphi > dphicut){
	h_ptavg->Fill(PtAvg);
// 	if (Jet_CSV_data[j]<0.605){//      
// 	  if (N_Jets_data >=3 ){
// 	      if (Jet_Pt[2]/pt_avg < pt3cut){
// 		if (j==0){h_CSV_data_lf->Fill(Jet_CSV_data[1]);}
// 		else if (j==1){h_CSV_data_lf->Fill(Jet_CSV_data[0]);}
// 	      }
// 	    }
// 	  if (j==0 && N_Jets_data == 2){
// 	    h_CSV_data_lf->Fill(Jet_CSV_data[1]);
// 	  }
// 	  if (j==1 && N_Jets_data == 2){
// 	    h_CSV_data_lf->Fill(Jet_CSV_data[0]);
// 	  }        
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


outfile->Close();


}

int main(){
triggerstudies();    
}
