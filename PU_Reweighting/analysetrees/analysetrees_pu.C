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
#include "TH2F.h"
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

void fillhisto(TH1F* hist,float &ptave, int  &var, vector<float>Weight,char option,int hlt40=0,int hlt60=0,int hlt80=0,int hlt140=0,int hlt200=0,int hlt260=0,int hlt320=0,int hlt400=0,int hlt500=0)
{
  if(option=='m')
  {
//     if (ptave < 67.6)				hist->Fill(var,Weight.at(0));
    if (ptave >= 77 && ptave < 99)   	 	hist->Fill(var,Weight.at(0));
    else if (ptave >= 99 && ptave < 165)  	hist->Fill(var,Weight.at(1));
    else if (ptave >= 165 && ptave < 231)	hist->Fill(var,Weight.at(2));
    else if (ptave >= 231 && ptave < 298) 	hist->Fill(var,Weight.at(3));
    else if (ptave >= 298 && ptave < 365) 	hist->Fill(var,Weight.at(4));
    else if (ptave >= 365 		) 	hist->Fill(var,Weight.at(5));
  }
  else if (option=='d')
  {
//     if (ptave<67.6 && hlt40==1)                          	hist->Fill(var);
  if (ptave >= 77 && ptave < 99 && hlt60==1)   		hist->Fill(var);
    else if (ptave >= 99 && ptave < 165 && hlt80==1)  	hist->Fill(var);
    else if (ptave >= 165 && ptave < 231 && hlt140==1)	hist->Fill(var);
    else if (ptave >= 231 && ptave < 298 && hlt200==1)	hist->Fill(var);
    else if (ptave >= 298 && ptave < 365 && hlt260==1)	hist->Fill(var);
    else if (ptave >= 365 && hlt320==1)			hist->Fill(var);
  }
}

void analysetrees(const TString &datalist,const TString &mclist){
  TChain *datachain = createTChain(datalist);
  TChain *mcchain = createTChain(mclist);  
  ///////////////////////
  /////MC SELECTION//////
  ///////////////////////
  
  //Get PtAveWeights
  TFile* f_ptaveweight=new TFile("~/qcd_dijets/PtAveWeight/PtAveWeight/ptaveweight.root");
  TH1F* h_ptaveweight = (TH1F*)f_ptaveweight->Get("PtAveWeight");
  vector<float> PtAveWeight;
  for (int i=1; i<=6;++i){
    float tmp=h_ptaveweight->GetBinContent(i);
    PtAveWeight.push_back(tmp); 
    cout << tmp<<endl;
  }
  f_ptaveweight->Close();
  //outputfile
  TFile* outfile=new TFile("histos.root","RECREATE");
  
  // initialize variables from tree
  int N_Jets;
  mcchain->SetBranchAddress("N_Jets",&N_Jets);
  int N_PV;
  mcchain->SetBranchAddress("N_PrimaryVertices",&N_PV);
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
  float Weight_XS;
  mcchain->SetBranchAddress("Weight_XS",&Weight_XS);
//   float* Jet_SumSVMass = new float[120];
//   mcchain->SetBranchAddress("Jet_SumSVMass",Jet_SumSVMass);
//   float* Jet_NSV = new float[120];
//   mcchain->SetBranchAddress("Jet_NSV",Jet_NSV); 

  long nentries=0;
  float dphicut=2.7;
  float pt3cut=0.1;
  float etamin=2.1;
    //define histos
  TH1F* h_npv_mc=new TH1F("h_npv_mc","h_npv_mc ",50,0,50);
  
  
  //initialize Weight
   vector<float> Weight;
    for (int i=0; i<6;++i){
      float tmp=PtAveWeight.at(i);
      Weight.push_back(tmp);    
    }
 //loop over all events
  nentries = mcchain->GetEntries(); 
  cout << "total number of MC events: " << nentries << endl;
  for (long iEntry=0;iEntry<nentries;iEntry++) {
    if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//     if(iEntry>1000000) break;
    mcchain->GetEntry(iEntry);
    //calculate event weight
    for (int i=0; i<6;++i){
      Weight.at(i)=Weight_XS*PtAveWeight.at(i);   
    }
    float ptave=PtAve;  
    if(abs(Jet_Eta[0])<etamin && abs(Jet_Eta[1])<etamin ){
      fillhisto(h_npv_mc,ptave, N_PV, Weight, 'm');
    }           
  }  
  
  ///////////////////////
  /////DATA SELECTION////
  ///////////////////////
  

  // initialize variables from tree
  int N_Jets_data;
  datachain->SetBranchAddress("N_Jets",&N_Jets_data);
  int N_PV_data;
  datachain->SetBranchAddress("N_PrimaryVertices",&N_PV_data);
  float* Jet_Pt_data = new float[120];
  datachain->SetBranchAddress("Jet_Pt",Jet_Pt_data);
  float* Jet_Phi_data = new float[120];
  datachain->SetBranchAddress("Jet_Phi",Jet_Phi_data);
  float DeltaPhi_data;
  datachain->SetBranchAddress("DeltaPhi",&DeltaPhi_data);
  float PtAve_data;
  datachain->SetBranchAddress("PtAve",&PtAve_data);
  float* Jet_Eta_data = new float[120];
  datachain->SetBranchAddress("Jet_Eta",Jet_Eta_data);  
  float* Jet_CSV_data = new float[120];
  datachain->SetBranchAddress("Jet_CSV",Jet_CSV_data);
//   float* Jet_SumSVMass_data = new float[120];
//   datachain->SetBranchAddress("Jet_SumSVMass",Jet_SumSVMass_data);
//   float* Jet_NSV_data = new float[120];
//   datachain->SetBranchAddress("Jet_NSV",Jet_NSV_data);
  
  //Triggers
  int hlt40 = false; 
  int hlt60 = false; 
  int hlt80 = false; 
  int hlt140 = false;
  int hlt200 = false;
  int hlt260 = false;
  int hlt320 = false;
  int hlt400 = false;
  int hlt500 = false;

  datachain->SetBranchAddress("Triggered_HLT_DiPFJetAve40_vX",&hlt40); 
  datachain->SetBranchAddress("Triggered_HLT_DiPFJetAve60_vX",&hlt60); 
  datachain->SetBranchAddress("Triggered_HLT_DiPFJetAve80_vX",&hlt80); 
  datachain->SetBranchAddress("Triggered_HLT_DiPFJetAve140_vX",&hlt140);
  datachain->SetBranchAddress("Triggered_HLT_DiPFJetAve200_vX",&hlt200);
  datachain->SetBranchAddress("Triggered_HLT_DiPFJetAve260_vX",&hlt260);
  datachain->SetBranchAddress("Triggered_HLT_DiPFJetAve320_vX",&hlt320);
  datachain->SetBranchAddress("Triggered_HLT_DiPFJetAve400_vX",&hlt400);
  datachain->SetBranchAddress("Triggered_HLT_DiPFJetAve500_vX",&hlt500);

 
  //define histos

  TH1F* h_npv_data=new TH1F("h_npv_data","h_npv_data",50,0,50);
  
  //loop over all events
  nentries = datachain->GetEntries(); 
  cout << "total number of data events: " << nentries << endl;
  for (long iEntry=0;iEntry<nentries;iEntry++) {
    if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//     if(iEntry>1000000) break;
    datachain->GetEntry(iEntry);
    float ptave=PtAve_data;  
    if(abs(Jet_Eta_data[0])<etamin && abs(Jet_Eta_data[1])<etamin ){
      fillhisto(h_npv_data, ptave, N_PV_data, Weight,'d', hlt40, hlt60, hlt80, hlt140, hlt200, hlt260, hlt320, hlt400, hlt500);
    }
  } 
  
  outfile -> Write(); 
  outfile -> Close(); 
}



int main(){
  TString datalist = "datalist";
  TString mclist= "mclist2";
  analysetrees(datalist, mclist);    
}
