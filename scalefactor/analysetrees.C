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

TChain *createTChain(const TString &fileName) {
  TChain* chain = new TChain("MVATree");
  if( fileName.EndsWith(".root") ) {
    chain->Add(fileName);
  }
  else {
    ifstream filelist;
    filelist.open(fileName);
    int nOpenedFiles = 0;
    if( filelist.is_open() ) {
      TString name = "";
      while( !filelist.eof() ) {
	filelist >> name;
	if( filelist.eof() ) break;
	chain->Add(name);
	nOpenedFiles++;
      }
    } else {
      std::cerr << "ERROR opening file '" << fileName << "'\n";
      exit(1);
    }
    filelist.close();
  }

  return chain;
  
}

void analysetrees(const TString &datalist,const TString &mclist){
//   TChain *datachain = createTChain(datalist);
  TChain *mcchain = createTChain(mclist);
  
  ///////////////////////
  /////DATA SELECTION////
  ///////////////////////
  
  
  // initialize variables from tree
  int N_Jets;
  mcchain->SetBranchAddress("N_Jets",&N_Jets);
  float* Jet_Pt = new float[120];
  mcchain->SetBranchAddress("Jet_Pt",Jet_Pt);
  float* Jet_Phi = new float[120];
  mcchain->SetBranchAddress("Jet_Phi",Jet_Phi);
  float DeltaPhi;
  mcchain->SetBranchAddress("DeltaPhi",&DeltaPhi);
  float PtAve;
  mcchain->SetBranchAddress("PtAve",&PtAve);
  float* Jet_Eta = new float[120];
  mcchain->SetBranchAddress("Jet_Eta",Jet_Eta);  
  float* Jet_CSV = new float[120];
  mcchain->SetBranchAddress("Jet_CSV",Jet_CSV);
  float* Jet_HadFlav = new float[120];
  mcchain->SetBranchAddress("Jet_HadronFlav",Jet_HadFlav);
  float* Jet_PartFlav = new float[120];
  mcchain->SetBranchAddress("Jet_PartonFlav",Jet_PartFlav);
  float* Jet_SumSVMass = new float[120];
  mcchain->SetBranchAddress("Jet_SumSVMass",Jet_SumSVMass);
  float* Jet_NSV = new float[120];
  mcchain->SetBranchAddress("Jet_NSV",Jet_NSV);
  
  //define histos
  vector<TH1F*> hCSV_mc_b;
  vector<TH1F*> hCSV_mc_c;
  vector<TH1F*> hCSV_mc_lf;
  
  for (int i=0; i<7;i++){
    stringstream ss;
    ss << i;
    TString counter=ss.str();
    TH1F* hb = new TH1F("hCSV_mc_b_ptavgbin"+counter,"hCSV_mc_b_ptavgbin"+counter,25,-0.1,1);
    hCSV_mc_b.push_back(hb);
    
    TH1F* hc = new TH1F("hCSV_mc_c_ptavgbin"+counter,"hCSV_mc_c_ptavgbin"+counter,25,-0.1,1);
    hCSV_mc_b.push_back(hc);
    
    TH1F* hlf = new TH1F("hCSV_mc_lf_ptavgbin"+counter,"hCSV_mc_lf_ptavgbin"+counter,25,-0.1,1);
    hCSV_mc_b.push_back(hlf);    
  }

}



int main(){
  TString datalist = "datalist";
  TString mclist= "mclist";
    analysetrees(datalist, mclist);    
}
