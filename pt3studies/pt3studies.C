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

void fillhisto(TH1F* hist,float &ptave, float var, vector<float>Weight,char option,int hlt40=0,int hlt60=0,int hlt80=0,int hlt140=0,int hlt200=0,int hlt260=0,int hlt320=0,int hlt400=0,int hlt500=0)
{
  if(option=='m')
  {
//     if (ptave < 67.6)				hist->Fill(var,Weight.at(0));
    if (ptave >= 67.6 && ptave < 89.6)   	hist->Fill(var,Weight.at(0));
    else if (ptave >= 89.6 && ptave < 155.6)  	hist->Fill(var,Weight.at(1));
    else if (ptave >= 155.6 && ptave < 221.6) 	hist->Fill(var,Weight.at(2));
    else if (ptave >= 221.6 && ptave < 287.6) 	hist->Fill(var,Weight.at(3));
    else if (ptave >= 287.6 && ptave < 353.6) 	hist->Fill(var,Weight.at(4));
    else if (ptave >= 353.6 ) 			hist->Fill(var,Weight.at(5));
  }
  else if (option=='d')
  {
//     if (ptave<67.6 && hlt40==1)                          	hist->Fill(var);
    if (ptave >= 67.6 && ptave < 89.6 && hlt60==1)   	hist->Fill(var);
    else if (ptave >= 89.6 && ptave < 155.6 && hlt80==1)  	hist->Fill(var);
    else if (ptave >= 155.6 && ptave < 221.6 && hlt140==1)	hist->Fill(var);
    else if (ptave >= 221.6 && ptave < 287.6 && hlt200==1)	hist->Fill(var);
    else if (ptave >= 287.6 && ptave < 353.6 && hlt260==1)	hist->Fill(var);
    else if (ptave >= 353.6 && hlt320==1)			hist->Fill(var);
  }
}

void analysetrees(const TString &datalist,const TString &mclist){
  TChain *datachain = createTChain(datalist);
  TChain *mcchain = createTChain(mclist);
  
  
  
  
  
  ///////////////////////
  /////MC SELECTION//////
  ///////////////////////
  //Get PtAveWeights
  TFile* f_ptaveweight=new TFile("../PtAveWeight/PtAveWeight/ptaveweight.root");
  TH1F* h_ptaveweight = (TH1F*)f_ptaveweight->Get("PtAveWeight");
  TFile* f_PUWeight=new TFile("../PU_Reweighting/pu_weight/PUWeight.root");
  TH1F* h_PUWeight = (TH1F*)f_PUWeight->Get("PUWeight");
  vector<float> PtAveWeight;
  for (int i=1; i<=6;++i){
    float tmp=h_ptaveweight->GetBinContent(i);
    PtAveWeight.push_back(tmp); 
    cout << tmp<<endl;
  }
//   f_ptaveweight->Close();
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
  float tmp=0;
    //define histos
  TH1F* h_ptave2_mc=new TH1F("PtAve_mc_wo_dijetselec","PtAve2_mc_wo_dijetselec ",80,0,1000);
  TH1F* h_ptave3_mc=new TH1F("PtAve_mc_w_dijetselec","PtAve2_mc_w_dijetselec",80,0,1000);
  TH1F* h_ptave1_mc=new TH1F("PtAve_mc_w_dijetselec_1","PtAve1_mc_w_dijetselec",80,0,1000);
  TH1F* h_dphi=new TH1F("h_dphi","h_dphi w/ all Weights",45,0,3.5);
  TH1F* h_pt0=new TH1F("h_pt0","h_pt0 w/ all Weights",120,0,1000);
  TH1F* h_pt1=new TH1F("h_pt1","h_pt1 w/ all Weights",120,0,1000);
  TH1F* h_pt0_dijet=new TH1F("h_pt0_dijet","h_pt0_dijet w/ all Weights",120,0,1000);
  TH1F* h_pt1_dijet=new TH1F("h_pt1_dijet","h_pt1_dijet w/ all Weights",120,0,1000);
  TH1F* h_pt3=new TH1F("h_pt3","h_pt3 w/ all Weights",80,0,220);
  TH1F* h_pt3_pt3cut=new TH1F("h_pt3_pt3cut","h_pt3 w/ all Weights and pt3cut",80,0,220);
  TH1F* h_pt3overavg=new TH1F("h_pt3overavg","h_pt3overavg w/ all Weights",60,0,1.5);
  TH2F* h_pt3overdphi=new TH2F("h_pt3overdphi","pt3vs dphi w/o PtAveWeight",80,0,220,45,0,3.5);
  
  TH1F* h_ptassym=new TH1F("h_ptassym","Pt assymetry",50,0,1);
  
  TH1F* h_eta0=new TH1F("h_eta0","h_eta0 w/ all Weights",50,-5,5);
  TH1F* h_eta1=new TH1F("h_eta1","h_eta1 w/ all Weights",50,-5,5);
  TH1F* h_eta2=new TH1F("h_eta2","h_eta2 w/ all Weights",50,-5,5);
  
  TH1F* h_npv=new TH1F("h_npv","h_npv",30,0,30);  
  
  TH1F* h_ptave2_mc_etacut=new TH1F("PtAve_mc_wo_dijetselec_etacut","PtAve2_mc_wo_dijetselec_etacut ",80,0,1000);
  TH1F* h_ptave3_mc_etacut=new TH1F("PtAve_mc_w_dijetselec_etacut","PtAve2_mc_w_dijetselec_etacut",80,0,1000); 
  TH1F* h_dphi_etacut=new TH1F("h_dphi_etacut","h_dphi w/ all Weights_etacut  ;",45,0,3.5);
  TH1F* h_pt3_etacut=new TH1F("h_pt3_etacut","h_pt3 w/ all Weights_etacut",80,0,220);
  TH1F* h_pt3_pt3cut_etacut=new TH1F("h_pt3_pt3cut_etacut","h_pt3 w/ all Weights and dijetselec_etacut",80,0,220);
  TH1F* h_pt3overavg_etacut=new TH1F("h_pt3overavg_etacut","h_pt3overavg w/ all Weights_etacut",60,0,1.5);
  TH2F* h_pt3overdphi_etacut=new TH2F("h_pt3overdphi_etacut","pt3vs dphi w/o PtAveWeight_etacut",80,0,220,45,0,3.5);
  
  TH1F* h_eta0_etacut=new TH1F("h_eta0_etacut","h_eta0 w/ all Weights_etacut",50,-5,5);
  TH1F* h_eta1_etacut=new TH1F("h_eta1_etacut","h_eta1 w/ all Weights_etacut",50,-5,5);
  TH1F* h_eta2_etacut=new TH1F("h_eta2_etacut","h_eta2 w/ all Weights_etacut",50,-5,5);
  
  //initialize Weight
   vector<float> Weight;
    for (int i=0; i<6;++i){
      float tmp=PtAveWeight.at(i);
      Weight.push_back(tmp);    
    }
  vector<float>puweight;
  for ( int i=1; i<=50; ++i){
    puweight.push_back(h_PUWeight->GetBinContent(i));
  }
 //loop over all events
  nentries = mcchain->GetEntries(); 
  cout << "total number of MC events: " << nentries << endl;
  for (long iEntry=0;iEntry<nentries;iEntry++) {
    if(iEntry%100000==0) {cout << "analyzing event " << iEntry << endl;}
//     if(iEntry>1000000) break;
    mcchain->GetEntry(iEntry);
    //calculate event weight
    for (int i=0; i<6;++i){      
      Weight.at(i)=Weight_XS*PtAveWeight.at(i)*puweight.at(N_PV); 
    }
    float ptave=PtAve;  
      if(abs(Jet_Eta[0])<etamin && abs(Jet_Eta[1])<etamin ){
	fillhisto( h_npv,ptave, N_PV, Weight, 'm');
	fillhisto( h_dphi,ptave, DeltaPhi, Weight,'m');
	fillhisto( h_eta0,ptave, Jet_Eta[0], Weight,'m');
	fillhisto( h_eta1,ptave, Jet_Eta[1], Weight,'m');
	fillhisto( h_ptave2_mc,ptave, ptave, Weight,'m');
	fillhisto( h_pt0,ptave, Jet_Pt[0], Weight,'m'); 
	fillhisto( h_pt1,ptave, Jet_Pt[1], Weight,'m'); 
	fillhisto( h_ptassym,ptave, abs(Jet_Pt[0]-Jet_Pt[1])/(Jet_Pt[0]+Jet_Pt[1]), Weight,'m'); 
	if (DeltaPhi > dphicut ){
	  fillhisto(h_ptave1_mc,ptave, ptave, Weight,'m');
	  fillhisto( h_pt0_dijet,ptave, Jet_Pt[0], Weight,'m'); 
	  fillhisto( h_pt1_dijet,ptave, Jet_Pt[1], Weight,'m'); 
	}
    
	if(N_Jets==2 && DeltaPhi > dphicut){	
	  fillhisto(h_ptave3_mc,ptave, ptave, Weight,'m');
	}
	else if(N_Jets>=3){
	  fillhisto(h_eta2,ptave, Jet_Eta[2], Weight,'m');
	  fillhisto(h_pt3,ptave, Jet_Pt[2], Weight,'m'); 
	  h_pt3overdphi->Fill(Jet_Pt[2],DeltaPhi,Weight_XS*puweight.at(N_PV));
	  tmp=Jet_Pt[2]/ptave;
	  fillhisto(h_pt3overavg,ptave, tmp, Weight,'m');
	  if (DeltaPhi > dphicut ){
// 	  if (DeltaPhi > dphicut && tmp<pt3cut){
// 	  if (DeltaPhi > dphicut && Jet_Pt[2]<30){
	      fillhisto(h_ptave3_mc,ptave, ptave, Weight,'m');
	      fillhisto(h_pt3_pt3cut,ptave,Jet_Pt[2], Weight,'m');
	  }
	}      
      }
      //Etacut on 3rd Jet
      if(abs(Jet_Eta[0])<etamin && abs(Jet_Eta[1])<etamin){
	fillhisto( h_eta0_etacut,ptave, Jet_Eta[0], Weight,'m');
	fillhisto( h_eta1_etacut,ptave, Jet_Eta[1], Weight,'m');
	fillhisto( h_dphi_etacut,ptave, DeltaPhi, Weight,'m');
	fillhisto( h_ptave2_mc_etacut,ptave, ptave, Weight,'m');
	if(N_Jets ==2 && DeltaPhi > dphicut){
	  fillhisto(h_ptave3_mc_etacut,ptave, ptave, Weight,'m');
	}
	else if(N_Jets>=3 ){
	  if (abs(Jet_Eta[2])<etamin){
	    fillhisto( h_eta2_etacut,ptave, Jet_Eta[2], Weight,'m');
	    fillhisto( h_pt3_etacut,ptave, Jet_Pt[2], Weight,'m');
	    tmp=Jet_Pt[2]/ptave;
	    fillhisto(h_pt3overavg_etacut,ptave, tmp, Weight,'m');
	  }
	  h_pt3overdphi_etacut->Fill(Jet_Pt[2],DeltaPhi,Weight_XS*puweight.at(N_PV));
	  if (DeltaPhi > dphicut  && abs(Jet_Eta[2])<etamin){
// 	  if (DeltaPhi > dphicut && tmp<pt3cut  && abs(Jet_Eta[2])<etamin){
// 	  if (DeltaPhi > dphicut && Jet_Pt[2]<30 && abs(Jet_Eta[2])<etamin){
	      fillhisto(h_ptave3_mc_etacut,ptave, ptave, Weight,'m');
	      fillhisto(h_pt3_pt3cut_etacut,ptave,Jet_Pt[2], Weight,'m');
	  }
	}
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

  TH1F* h_ptave2_data=new TH1F("PtAve_data_wo_dijetselec","PtAve_data_wo_dijetselec",80,0,1000);
  TH1F* h_ptave3_data=new TH1F("PtAve_data_w_dijetselec","PtAve_data_w_dijetselec",80,0,1000);
  TH1F* h_ptave1_data=new TH1F("PtAve_data_w_dijetselec_1","PtAve_data_w_dijetselec",80,0,1000);
  TH1F* h_pt0_data=new TH1F("h_pt0_data","h_pt0_data ",120,0,1000);
  TH1F* h_pt1_data=new TH1F("h_pt1_data","h_pt1_data ",120,0,1000);
  TH1F* h_pt0_data_dijet=new TH1F("h_pt0_data_dijet","h_pt0_data_dijet",120,0,1000);
  TH1F* h_pt1_data_dijet=new TH1F("h_pt1_data_dijet","h_pt1_data_dijet",120,0,1000);
  TH1F* h_pt3_data=new TH1F("h_pt3_data","h_pt3_data w/o pt3cut",80,0,220);
  TH1F* h_pt3_pt3cut_data=new TH1F("h_pt3_pt3cut_data","h_pt3_data  /w pt3cut",80,0,220);
  TH1F* h_pt3overavg_data=new TH1F("h_pt3overavg_data","h_pt3overavg_data",60,0,1.5);
  TH1F* h_dphi_data=new TH1F("h_dphi_data","h_dphi_data ",45,0,3.5);
  
  TH1F* h_ptassym_data=new TH1F("h_ptassym_data","Pt assymetry",50,0,1);
  
  TH1F* h_eta0_data=new TH1F("h_eta0_data","h_eta0 data",50,-5,5);
  TH1F* h_eta1_data=new TH1F("h_eta1_data","h_eta1 data",50,-5,5);
  TH1F* h_eta2_data=new TH1F("h_eta2_data","h_eta2 data",50,-5,5);
  
  TH1F* h_npv_data=new TH1F("h_npv_data","h_npv_data",30,0,30);   
  
  TH1F* h_ptave2_data_etacut=new TH1F("PtAve_data_wo_dijetselec_etacut","PtAve_data_wo_dijetselec_etacut",80,0,1000);
  TH1F* h_ptave3_data_etacut=new TH1F("PtAve_data_w_dijetselec_etacut","PtAve_data_w_dijetselec_etacut",80,0,1000);
//   TH1F* h_ptave3_mc_etacut=new TH1F("PtAve_mc_w_dijetselec_etacut","PtAve2_mc_w_dijetselec_etacut",80,0,1000); 
  TH1F* h_pt3_data_etacut=new TH1F("h_pt3_data_etacut","h_pt3_data w/o pt3cut_etacut",80,0,220);
  TH1F* h_pt3_pt3cut_data_etacut=new TH1F("h_pt3_pt3cut_data_etacut","h_pt3_data  /w dijetselec_etacut",80,0,220);
  TH1F* h_pt3overavg_data_etacut=new TH1F("h_pt3overavg_data_etacut","h_pt3overavg_data_etacut",60,0,1.5);
  TH1F* h_dphi_data_etacut=new TH1F("h_dphi_data_etacut","h_dphi_data_etacut",45,0,3.5);
  
  TH1F* h_eta0_data_etacut=new TH1F("h_eta0_data_etacut","h_eta0 data_etacut",50,-5,5);
  TH1F* h_eta1_data_etacut=new TH1F("h_eta1_data_etacut","h_eta1 data_etacut",50,-5,5);
  TH1F* h_eta2_data_etacut=new TH1F("h_eta2_data_etacut","h_eta2 data_etacut",50,-5,5);
  
  //loop over all events
  nentries = datachain->GetEntries(); 
  cout << "total number of data events: " << nentries << endl;
  for (long iEntry=0;iEntry<nentries;iEntry++) {
    if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//     if(iEntry>100000) break;
    datachain->GetEntry(iEntry);
    float ptave=PtAve_data;   
  
    if(abs(Jet_Eta_data[0])<etamin && abs(Jet_Eta_data[1])<etamin ){
      fillhisto( h_npv_data, ptave, N_PV_data, Weight,'d', hlt40, hlt60, hlt80, hlt140, hlt200, hlt260, hlt320, hlt400, hlt500);
      fillhisto( h_dphi_data,ptave, DeltaPhi_data, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      fillhisto( h_eta0_data,ptave, Jet_Eta_data[0], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      fillhisto( h_eta1_data,ptave, Jet_Eta_data[1], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      fillhisto( h_ptave2_data,ptave, ptave, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      fillhisto( h_pt0_data,ptave, Jet_Pt_data[0], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      fillhisto( h_pt1_data,ptave, Jet_Pt_data[1], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      fillhisto( h_ptassym_data,ptave, abs(Jet_Pt_data[0]-Jet_Pt_data[1])/(Jet_Pt_data[0]+Jet_Pt_data[1]), Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      if (DeltaPhi_data > dphicut ){
	fillhisto(h_ptave1_data,ptave, ptave, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	fillhisto( h_pt0_data_dijet,ptave, Jet_Pt_data[0], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	fillhisto( h_pt1_data_dijet,ptave, Jet_Pt_data[1], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      }
      
      if(N_Jets_data == 2){	
	if (DeltaPhi_data > dphicut ){
	  fillhisto(h_ptave3_data,ptave, ptave, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	}
      }
      else if(N_Jets_data>=3){
	fillhisto( h_eta2_data,ptave, Jet_Eta_data[2], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	fillhisto(h_pt3_data,ptave, Jet_Pt_data[2], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	tmp=Jet_Pt_data[2]/ptave;
	fillhisto(h_pt3overavg_data,ptave, tmp, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	if (DeltaPhi_data > dphicut ){
// 	if (DeltaPhi_data > dphicut && tmp<pt3cut){
// 	if (DeltaPhi_data > dphicut && Jet_Pt_data[2]<30){
	    fillhisto(h_ptave3_data,ptave, ptave, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	    fillhisto(h_pt3_pt3cut_data,ptave,Jet_Pt_data[2], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	}
      }
    }
	
     //Etacut on 3rd Jet
    if(abs(Jet_Eta_data[0])<etamin && abs(Jet_Eta_data[1])<etamin  ){      
      fillhisto( h_eta0_data_etacut,ptave, Jet_Eta_data[0], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      fillhisto( h_eta1_data_etacut,ptave, Jet_Eta_data[1], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      fillhisto( h_dphi_data_etacut,ptave, DeltaPhi_data, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      fillhisto( h_ptave2_data_etacut,ptave, ptave, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      if(N_Jets_data == 2 && DeltaPhi_data > dphicut){
	  fillhisto(h_ptave3_data_etacut,ptave, ptave, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
      }
      else if(N_Jets_data>=3){
	if (abs(Jet_Eta_data[2])<etamin){
	  fillhisto( h_eta2_data_etacut,ptave, Jet_Eta_data[2], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);	
	  fillhisto( h_pt3_data_etacut,ptave, Jet_Pt_data[2], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	  tmp=Jet_Pt_data[2]/ptave;
	  fillhisto(h_pt3overavg_data_etacut,ptave, tmp, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	}	
// 	if (DeltaPhi_data > dphicut && tmp<pt3cut  && abs(Jet_Eta_data[2])<etamin){
// 	if (DeltaPhi_data > dphicut && Jet_Pt_data[2]<30 && abs(Jet_Eta_data[2])<etamin){
      if (DeltaPhi_data > dphicut  && abs(Jet_Eta_data[2])<etamin){
	    fillhisto(h_ptave3_data_etacut,ptave, ptave, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	    fillhisto(h_pt3_pt3cut_data_etacut,ptave,Jet_Pt_data[2], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	}
      }
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
