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
  TChain *datachain = createTChain(datalist);
  TChain *mcchain = createTChain(mclist);
  
  //outputfile
  TFile* outfile=new TFile("histos.root","RECREATE");
  
  ///////////////////////
  /////MC SELECTION//////
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
  float Weight_XS;
  mcchain->SetBranchAddress("Weight_XS",&Weight_XS);
//   float* Jet_SumSVMass = new float[120];
//   mcchain->SetBranchAddress("Jet_SumSVMass",Jet_SumSVMass);
//   float* Jet_NSV = new float[120];
//   mcchain->SetBranchAddress("Jet_NSV",Jet_NSV);
  
  //define histos
  vector<TH1F*> hCSV_mc_b;
  vector<TH1F*> hCSV_mc_c;
  vector<TH1F*> hCSV_mc_lf;  
  
  vector<TH1F*>hptave_mc;
  for (int i=0; i<7;++i){
    stringstream ss;
    ss << i;
    TString counter=ss.str();
    
    TH1F* ptave=new TH1F("hptave_mc"+counter,"hptave_mc"+counter,175,0,1000);
    hptave_mc.push_back(ptave);
  }

  long nentries=0;
  float dphicut=2.7;
  float pt3cut=0.1;
  float etamin=2.1;
  TH1F* h_ptave_mc=new TH1F("PtAve_mc","PtAve_mc",80,0,250);
  TH1F* h_ptave_data=new TH1F("PtAve_data","PtAve_data",80,0,250);
  TH1F* h_ptave2_mc=new TH1F("PtAve2_mc","PtAve2_mc",80,0,250);
  TH1F* h_dphi=new TH1F("h_dphi","h_dphi",45,0,3.5);
  TH1F* h_pt3=new TH1F("h_pt3","h_pt3",80,0,220);
  TH1F* h_pt3overavg=new TH1F("h_pt3overavg","h_pt3overavg",30,0,2);
  
 //loop over all events
  nentries = mcchain->GetEntries(); 
  cout << "total number of MC events: " << nentries << endl;
  for (long iEntry=0;iEntry<nentries;iEntry++) {
    if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//     if(iEntry>1000000) break;
    mcchain->GetEntry(iEntry);
    double ptave=PtAve;    
      h_dphi->Fill(DeltaPhi,Weight_XS);
      if (abs(Jet_Eta[0])<etamin && abs(Jet_Eta[1])<etamin){
	if (DeltaPhi> dphicut ){
	  if (ptave >= 55 && ptave < 67.6)   		hptave_mc.at(0)->Fill(ptave,Weight_XS);
	  else if (ptave >= 67.6 && ptave < 89.6)   	hptave_mc.at(1)->Fill(ptave,Weight_XS);
	  else if (ptave >= 89.6 && ptave < 155.6)  	hptave_mc.at(2)->Fill(ptave,Weight_XS);
	  else if (ptave >= 155.6 && ptave < 221.6)	hptave_mc.at(3)->Fill(ptave,Weight_XS);
	  else if (ptave >= 221.6 && ptave < 287.6) 	hptave_mc.at(4)->Fill(ptave,Weight_XS);
	  else if (ptave >= 287.6 && ptave < 353.6) 	hptave_mc.at(5)->Fill(ptave,Weight_XS);
	  else if (ptave >= 353.6 		) 	hptave_mc.at(6)->Fill(ptave,Weight_XS);
	  h_ptave2_mc->Fill(ptave,Weight_XS); 
	  if (N_Jets >=3){
	    h_pt3->Fill(Jet_Pt[2],Weight_XS);
	    h_pt3overavg->Fill(Jet_Pt[2]/ptave,Weight_XS);
		if (Jet_Pt[2]/ptave < pt3cut){
		  h_ptave_mc->Fill(ptave,Weight_XS);		  
		}
	  }
	}
	else if (N_Jets==2) h_ptave_mc->Fill(ptave,Weight_XS);
      }
    }


  
  ///////////////////////
  /////DATA SELECTION////
  ///////////////////////
  
  
  // initialize variables from tree
  int N_Jets_data;
  datachain->SetBranchAddress("N_Jets",&N_Jets_data);
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
//   chain->SetBranchAddress("JetCorrL1",jetCorrL1);
//   chain->SetBranchAddress("JetCorrL2L3",jetCorrL2L3);
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
  vector<TH1F*> hCSV_data;
  vector<TH1F*> hptave_data;
  for (int i=0; i<8;++i){
    stringstream ss;
    ss << i;
    TString counter=ss.str();
    TH1F* hdata = new TH1F("hCSV_data_ptavgbin"+counter,"hCSV_data_ptavgbin"+counter,25,-0.1,1);
    hCSV_data.push_back(hdata);
    
    TH1F* hptavg_data = new TH1F("hptavg_data_bin"+counter,"hptavg_bin"+counter,175,0,1000);
    hptave_data.push_back(hptavg_data);
  }
  
  //loop over all events
  nentries = datachain->GetEntries(); 
  cout << "total number of data events: " << nentries << endl;
  for (long iEntry=0;iEntry<nentries;iEntry++) {
    if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//     if(iEntry>1000000) break;
    datachain->GetEntry(iEntry);
    double ptave=PtAve_data;
    
    if (abs(Jet_Eta_data[0])<etamin && abs(Jet_Eta_data[1])<etamin){
      if (DeltaPhi_data> dphicut ){
	if (ptave >= 55 && ptave < 67.6 && hlt40==1)            hptave_data.at(0)->Fill(ptave);
	else if (ptave >= 67.6 && ptave < 89.6 && hlt60==1)   	hptave_data.at(1)->Fill(ptave);
	else if (ptave >= 89.6 && ptave < 155.6 && hlt80==1)  	hptave_data.at(2)->Fill(ptave);
	else if (ptave >= 155.6 && ptave < 221.6 && hlt140==1)	hptave_data.at(3)->Fill(ptave);
	else if (ptave >= 221.6 && ptave < 287.6 && hlt200==1)	hptave_data.at(4)->Fill(ptave);
	else if (ptave >= 287.6 && ptave < 353.6 && hlt260==1)	hptave_data.at(5)->Fill(ptave);
	else if (ptave >= 353.6 && hlt320==1)			hptave_data.at(6)->Fill(ptave);
	if (N_Jets_data >=3){	  
		if (Jet_Pt_data[2]/PtAve_data < pt3cut){
		  h_ptave_data->Fill(PtAve_data);  
		}
	  }
      }
      else if (N_Jets_data==2) h_ptave_data->Fill(PtAve_data);   
      
      }
    } 
  outfile ->Write(); 
  outfile -> Close();
}



int main(){
  TString datalist = "datalist";
  TString mclist= "mclist2";
    analysetrees(datalist, mclist);    
}
