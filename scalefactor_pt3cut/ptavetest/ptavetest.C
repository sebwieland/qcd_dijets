#include "TBranch.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TChain.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TLine.h"
#include "TH1F.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


void ptavetest(TFile *histos){
  //outputfile
  TFile* outfile=new TFile("ptavetest.root","RECREATE");
  TH1F* h_ptave_mc_w_dijetselec = (TH1F*)histos->Get("PtAve_mc_w_dijetselec");
  TH1F* h_ptave_data_w_dijetselec = (TH1F*)histos->Get("PtAve_data_w_dijetselec");

  h_ptave_data_w_dijetselec->Divide(h_ptave_mc_w_dijetselec);

  TCanvas* c=new TCanvas();
  TLine* line=new TLine(0,1,1000,1);
  line->SetLineColor(kBlack);
  c->cd();
  h_ptave_data_w_dijetselec->Draw("histe0");
  line->Draw("same");
  c->SaveAs("ptavetest_w_dijetselec.png");  

  
  outfile->Write();



  outfile->Close();
  
  
  
}
  











int main(){
  TFile* histos=new TFile("../analysetrees/histos.root");
  
  ptavetest(histos);

}