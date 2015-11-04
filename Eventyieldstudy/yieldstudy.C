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

long selectevents(const TString &fileName){
  TChain* chain = new TChain("MVATree");
  if( fileName.EndsWith(".root") ) {
    chain->Add(fileName);
  }
  
  int N_Jets;
  chain->SetBranchAddress("N_Jets",&N_Jets);
  float* Jet_Pt = new float[120];
  chain->SetBranchAddress("Jet_Pt",Jet_Pt);
  float* Jet_Phi = new float[120];
  chain->SetBranchAddress("Jet_Phi",Jet_Phi);
  float DeltaPhi;
  chain->SetBranchAddress("DeltaPhi",&DeltaPhi);
  float PtAve;
  chain->SetBranchAddress("PtAve",&PtAve);
  float* Jet_Eta = new float[120];
  chain->SetBranchAddress("Jet_Eta",Jet_Eta);  
  float* Jet_CSV = new float[120];
  chain->SetBranchAddress("Jet_CSV",Jet_CSV);
  float* Jet_HadFlav = new float[120];
  chain->SetBranchAddress("Jet_HadronFlav",Jet_HadFlav);
  float* Jet_PartFlav = new float[120];
  chain->SetBranchAddress("Jet_PartonFlav",Jet_PartFlav);
  float Weight_XS;
  chain->SetBranchAddress("Weight_XS",&Weight_XS);
  
  long nentries=0;
  long n_selected=0;
  float dphicut=2.7;
  float pt3cut=0.1;
  float etamin=2.1;
  
  nentries = chain->GetEntries(); 
  cout <<"counting events in "<< fileName << endl;
  cout << "total number of MC events: " << nentries << endl;
  for (long iEntry=0;iEntry<nentries;iEntry++) {
    if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//     if(iEntry>1000000) break;
    chain->GetEntry(iEntry);
    double ptave=PtAve;    
    if(N_Jets >=2){
      if (DeltaPhi> dphicut ){
	if (abs(Jet_Eta[0])<etamin && abs(Jet_Eta[1])<etamin){
	  if (N_Jets >=3){
		if (Jet_Pt[2]/ptave < pt3cut) n_selected++;  
	  }
	  else if (N_Jets==2) n_selected++; 
	}
      }
    }
  }
  cout << n_selected<< " Events selected" << endl;
  return n_selected;
}



int main(){
TFile* outfile=new TFile("yields.root","RECREATE");
long n0=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_5to10_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n1=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_10to15_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n2=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n3=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n4=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n5=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n6=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n7=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n8=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n9=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n10=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n11=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n12=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n13=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n14=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8_v3.root");
long n15=selectevents("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v3/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8_v3.root");


TH1F* h_yields=new TH1F("selected Events","selected Events",16,-0.5,15.5);
h_yields->SetBinContent(0,n0);
h_yields->SetBinContent(1,n1);
h_yields->SetBinContent(2,n2);
h_yields->SetBinContent(3,n3);
h_yields->SetBinContent(4,n4);
h_yields->SetBinContent(5,n5);
h_yields->SetBinContent(6,n6);
h_yields->SetBinContent(7,n7);
h_yields->SetBinContent(8,n8);
h_yields->SetBinContent(9,n9);
h_yields->SetBinContent(10,n10);
h_yields->SetBinContent(11,n11);
h_yields->SetBinContent(12,n12);
h_yields->SetBinContent(13,n13);
h_yields->SetBinContent(14,n14);
h_yields->SetBinContent(15,n15);

TCanvas* c1=new TCanvas();
h_yields->Draw();
c1->SaveAs("yields.png");
outfile->Write();
outfile->Close();


}





