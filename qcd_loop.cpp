// #include "TChain.h"
#include "TBranch.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1F.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;




void qcd_dijet(){
  TH1F::SetDefaultSumw2();
  
  // open files
//   TChain* chain = new TChain("MVATree");
//   char* filenames = getenv ("FILENAMES");
//   char* outfilename = getenv ("OUTFILENAME");
//   string buf;
//   stringstream ss(filenames); 
//   while (ss >> buf){
//     chain->Add(buf.c_str());
//   }
//   chain->SetBranchStatus("*",0);
  TFile* f_qcd= new TFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/DiJets_QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8.root");
  TTree *tree_qcd = (TTree*)f_qcd->Get("MVATree");

  // initialize variables from tree

  int N_Jets;
  tree_qcd->SetBranchAddress("N_Jets",&N_Jets);
  float* Jet_Pt = new float[20];
  tree_qcd->SetBranchAddress("Jet_Pt",Jet_Pt);
  float* Jet_Phi = new float[20];
  tree_qcd->SetBranchAddress("Jet_Phi",Jet_Phi);
  float* dphi;
  tree_qcd->SetBranchAddress("dphi",dphi);
  float* Jet_Eta = new float[20];
  tree_qcd->SetBranchAddress("Jet_Eta",Jet_Eta);  
  float* Jet_CSV = new float[20];
  tree_qcd->SetBranchAddress("Jet_CSV",Jet_CSV);
  float* Jet_Flav = new float[20];
  tree_qcd->SetBranchAddress("Jet_Flav",Jet_Flav);
  
 
  // define histos
  TH1F* h_N_Jets=new TH1F("N_Jets","Number of jets",15,-0.5,14.5);
  TH1F* h_Pt_Jets=new TH1F("Pt_Jets","Pt of all jets",60,0,600);
  TH1F* h_Pt_Jet4=new TH1F("Pt_Jet4","Pt of fourth jet",60,0,300);
  TH1F* h_Dr_Jet1_Jet2=new TH1F("Dr_Jet1_Jet2","DeltaR(jet1,jet2)",60,0,6);

  // loop over all events
  long nentries = chain->GetEntries(); 
  cout << "total number of events: " << nentries << endl;
  for (long iEntry=0;iEntry<nentries;iEntry++) {
    if(iEntry%10000==0) cout << "analyzing event " << iEntry << endl;
    if(iEntry>100000) break;
    chain->GetEntry(iEntry); 

    // Fill histograms
    h_N_Jets->Fill(N_Jets,Weight);
    for(int i=0; i<N_Jets;i++){
      h_Pt_Jets->Fill(Jet_Pt[i]);
    }
    if(N_Jets>3){
      h_Pt_Jet4->Fill(Jet_Pt[3]);
    }
    LV v_jet1;
    LV v_jet2;
    if(N_Jets>0){
      v_jet1=getLV(Jet_Pt[0],Jet_Eta[0],Jet_Phi[0],Jet_E[0]);
    }
    if(N_Jets>1){
      v_jet2=getLV(Jet_Pt[1],Jet_Eta[1],Jet_Phi[1],Jet_E[1]);
    }
    float dr_j1_j2 = v_jet1.DeltaR(v_jet2);
    h_Dr_Jet1_Jet2->Fill(dr_j1_j2);

  } // end of event loop
  // write histos
  TFile* outfile=new TFile(outfilename,"RECREATE");    
  h_N_Jets->Write();
  h_Pt_Jets->Write();
  h_Pt_Jet4->Write();
  h_Dr_Jet1_Jet2->Write();
  outfile->Close();
}

int main(){
  qcd_dijet();
}
