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

void fillhisto(TH1F* hist,float &ptave, float &var, vector<float>Weight,char option,int hlt40=0,int hlt60=0,int hlt80=0,int hlt140=0,int hlt200=0,int hlt260=0,int hlt320=0,int hlt400=0,int hlt500=0)
{
  if(option=='m')
  {
//     if (ptave < 67.6)				hist->Fill(var,Weight.at(0));
    if (ptave >= 67.6 && ptave < 89.6)   	hist->Fill(var,Weight.at(1));
    else if (ptave >= 89.6 && ptave < 155.6)  	hist->Fill(var,Weight.at(2));
    else if (ptave >= 155.6 && ptave < 221.6) 	hist->Fill(var,Weight.at(3));
    else if (ptave >= 221.6 && ptave < 287.6) 	hist->Fill(var,Weight.at(4));
    else if (ptave >= 287.6 && ptave < 353.6) 	hist->Fill(var,Weight.at(5));
    else if (ptave >= 353.6 ) 			hist->Fill(var,Weight.at(6));
  }
  else if (option=='d')
  {
//     if (ptave<67.6 && hlt40==1)                           hist->Fill(var);
    if (ptave >= 67.6 && ptave < 89.6 && hlt60==1)   hist->Fill(var);
    else if (ptave >= 89.6 && ptave < 155.6 && hlt80==1)  hist->Fill(var);
    else if (ptave >= 155.6 && ptave < 221.6 && hlt140==1)hist->Fill(var);
    else if (ptave >= 221.6 && ptave < 287.6 && hlt200==1)hist->Fill(var);
    else if (ptave >= 287.6 && ptave < 353.6 && hlt260==1)hist->Fill(var);
    else if (ptave >= 353.6  &&  hlt320==1)		  hist->Fill(var);    
  }
}

void fillcsv_mc(int j,TH1F* hCSV_mc_c, TH1F* hCSV_mc_b,TH1F* hCSV_mc_lf, float &ptave,float *Jet_CSV, float *Jet_HadFlav, vector<float>Weight){
   
    if (j==0){		      
      if (abs(Jet_HadFlav[1])==4) {
	fillhisto(hCSV_mc_c,ptave, Jet_CSV[1], Weight,'m');	        
      }	      
      else if (abs(Jet_HadFlav[1])==5){
	fillhisto(hCSV_mc_b,ptave, Jet_CSV[1], Weight,'m');	  		  
      }
      else if (abs(Jet_HadFlav[1])!=4 && abs(Jet_HadFlav[1])!=5 ){
	fillhisto(hCSV_mc_lf,ptave, Jet_CSV[1], Weight,'m');		  		  
      }
    }
    else if (j==1){		
      if (abs(Jet_HadFlav[0])==4) {
	fillhisto(hCSV_mc_c,ptave, Jet_CSV[0], Weight,'m');		        
      }	      
      else if (abs(Jet_HadFlav[0])==5){
	fillhisto(hCSV_mc_b,ptave, Jet_CSV[0], Weight,'m');	  		  
      }
      else if (abs(Jet_HadFlav[0])!=4 && abs(Jet_HadFlav[0])!=50){
	fillhisto(hCSV_mc_lf,ptave, Jet_CSV[0], Weight,'m');		  
      }
    }  
  }

void fillcsv_data(int j,TH1F* hCSV_data, float &ptave,float *Jet_CSV_data, vector<float>Weight,int hlt40=0,int hlt60=0,int hlt80=0,int hlt140=0,int hlt200=0,int hlt260=0,int hlt320=0,int hlt400=0,int hlt500=0){	        
  if (j==0 ){
    fillhisto(hCSV_data,ptave, Jet_CSV_data[1], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);		        
    }
  else if (j==1 ){
    fillhisto(hCSV_data,ptave, Jet_CSV_data[0], Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);				      
  }	    
}
  
void analysetrees(const TString &datalist,const TString &mclist){
  TChain *datachain = createTChain(datalist);
  TChain *mcchain = createTChain(mclist);
  
  
  
  
  
  ///////////////////////
  /////MC SELECTION//////
  ///////////////////////
  //Get PtAveWeights
  TFile* f_ptaveweight=new TFile("ptaveweight.root");
  TH1F* h_ptaveweight = (TH1F*)f_ptaveweight->Get("PtAveWeight");
  TFile* f_PUWeight=new TFile("~/qcd_dijets/PU_Reweighting/pu_weight/PUWeight.root");
  TH1F* h_PUWeight = (TH1F*)f_PUWeight->Get("PUWeight");
  vector<float> PtAveWeight;
  for (int i=0; i<7;++i){
    float tmp=h_ptaveweight->GetBinContent(i);
    PtAveWeight.push_back(tmp); 
//     cout << tmp<<endl;
  }
  f_ptaveweight->Close();
  //outputfile
  TFile* outfile=new TFile("histos.root","RECREATE");
  
  // initialize variables from tree
  int N_PV;
  mcchain->SetBranchAddress("N_PrimaryVertices",&N_PV);
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
  int n_ptbins= 5;
  int n_etabins=4;
  vector<vector<TH1F*>> hCSV_mc_b;
  hCSV_mc_b.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> hCSV_mc_c;
  hCSV_mc_c.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<vector<TH1F*>> hCSV_mc_lf;
  hCSV_mc_lf.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));

  vector<TH1F*>hptave_mc;
  TString eta_counter="0";
  TString pt_counter="0";
  for (int i=0; i<n_ptbins;++i){
    if (i==0) pt_counter="0";
    else if (i==1) pt_counter="1";
    else if (i==2) pt_counter="2";
    else if (i==3) pt_counter="3";
    else if (i==4) pt_counter="4";
    for ( int j=0; j<n_etabins;++j){   
      if (j==0) eta_counter="0";
      else if (j==1) eta_counter="1";
      else if (j==2) eta_counter="2";
      else if (j==3) eta_counter="3";
      
      TH1F* hb = new TH1F("hCSV_mc_b_ptbin"+pt_counter+"_etabin"+eta_counter,"hCSV_mc_b_ptbin"+pt_counter+"_etabin"+eta_counter,25,-0.1,1);
      hb->SetDrawOption("histe0");
      hCSV_mc_b[i][j]=hb;    
      
      TH1F* hc = new TH1F("hCSV_mc_c_ptbin"+pt_counter+"_etabin"+eta_counter,"hCSV_mc_c_ptbin"+pt_counter+"_etabin"+eta_counter,25,-0.1,1);
      hc->SetDrawOption("histe0");
      hCSV_mc_c[i][j]=hc;
      
      TH1F* hlf = new TH1F("hCSV_mc_lf_ptbin"+pt_counter+"_etabin"+eta_counter,"hCSV_mc_lf_ptbin"+pt_counter+"_etabin"+eta_counter,25,-0.1,1);
      hlf->SetDrawOption("histe0");
      hCSV_mc_lf[i][j]=hlf; 
    }
    
    TH1F* ptave=new TH1F("hptave_mc"+pt_counter,"hptave_mc"+pt_counter,80,0,1000);
    ptave->SetDrawOption("histe0");
    hptave_mc.push_back(ptave);
  }

  long nentries=0;
  float dphicut=2.7;
  float pt3cut=0.1;
  float etamin=2.1;
  
  TH1F* h_ptave_mc=new TH1F("PtAve_mc_w_dijetselec","PtAve_mc_w_dijetselec ",80,0,1000);
  h_ptave_mc->SetDrawOption("histe0"); 
  //initialize Weight
   vector<float> Weight;
    for (int i=0; i<7;++i){
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
    if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//     if(iEntry>1000000) break;
    mcchain->GetEntry(iEntry);
    //calculate event weight
    for (int i=0; i<7;++i){      
      Weight.at(i)=Weight_XS*PtAveWeight.at(i)*puweight.at(N_PV);   
    }
    float ptave=PtAve; 
    int etabin=0;
    int ptbin=0;
    if(N_Jets >=2){
      if (abs(Jet_Eta[0])<etamin && abs(Jet_Eta[1])<etamin){
	if (DeltaPhi > dphicut ){
	  if (N_Jets==2){
	    fillhisto(h_ptave_mc,ptave, ptave, Weight,'m');
	    for (int j=0;j<2;j++){
	      if (Jet_CSV[j]<0.605){
		fillcsv_mc(j,hCSV_mc_c[0][0], hCSV_mc_b[0][0], hCSV_mc_lf[0][0],ptave, Jet_CSV,Jet_HadFlav , Weight);
		
		if(j==0){
		  if (abs(Jet_Eta[1])<0.8) etabin=1;
		  else if (abs(Jet_Eta[1])>=0.8 && abs(Jet_Eta[1]<1.6)) etabin=2;
		  else if (abs(Jet_Eta[1])>=1.6 && abs(Jet_Eta[1]<2.4)) etabin=3;
		  if (Jet_Pt[1]<30) ptbin=1;
		  else if (Jet_Pt[1]>=30 && Jet_Pt[1] <40 ) ptbin=2;
		  else if (Jet_Pt[1]>=40 && Jet_Pt[1] <60 ) ptbin=3;
		  else if (Jet_Pt[1]>=60) ptbin=4;		
		}
		else if (j==1){
		  if (abs(Jet_Eta[0])<0.8) etabin=1;
		  else if (abs(Jet_Eta[0])>=0.8 && abs(Jet_Eta[0]<1.6)) etabin=2;
		  else if (abs(Jet_Eta[0])>=1.6 && abs(Jet_Eta[0]<2.4)) etabin=3;
		  if (Jet_Pt[0]<30) ptbin=1;
		  else if (Jet_Pt[0]>=30 && Jet_Pt[0] <40 ) ptbin=2;
		  else if (Jet_Pt[0]>=40 && Jet_Pt[0] <60 ) ptbin=3;
		  else if (Jet_Pt[0]>=60) ptbin=4;			
		}
		fillcsv_mc(j,hCSV_mc_c[ptbin][etabin], hCSV_mc_b[ptbin][etabin], hCSV_mc_lf[ptbin][etabin],ptave, Jet_CSV,Jet_HadFlav , Weight);
	      }
	    }
	  }
	  if (N_Jets>=3 && Jet_Pt[2]/ptave < pt3cut){
	    fillhisto(h_ptave_mc,ptave, ptave, Weight,'m');
	    for (int j=0;j<2;j++){
	      if (Jet_CSV[j]<0.605){
		fillcsv_mc(j,hCSV_mc_c[0][0], hCSV_mc_b[0][0], hCSV_mc_lf[0][0],ptave, Jet_CSV,Jet_HadFlav , Weight);
		
		if(j==0){
		  if (abs(Jet_Eta[1])<0.8) etabin=1;
		  else if (abs(Jet_Eta[1])>=0.8 && abs(Jet_Eta[1]<1.6)) etabin=2;
		  else if (abs(Jet_Eta[1])>=1.6 && abs(Jet_Eta[1]<2.4)) etabin=3;
		  if (Jet_Pt[1]<30) ptbin=1;
		  else if (Jet_Pt[1]>=30 && Jet_Pt[1] <40 ) ptbin=2;
		  else if (Jet_Pt[1]>=40 && Jet_Pt[1] <60 ) ptbin=3;
		  else if (Jet_Pt[1]>=60) ptbin=4;		
		}
		else if (j==1){
		  if (abs(Jet_Eta[0])<0.8) etabin=1;
		  else if (abs(Jet_Eta[0])>=0.8 && abs(Jet_Eta[0]<1.6)) etabin=2;
		  else if (abs(Jet_Eta[0])>=1.6 && abs(Jet_Eta[0]<2.4)) etabin=3;
		  if (Jet_Pt[0]<30) ptbin=1;
		  else if (Jet_Pt[0]>=30 && Jet_Pt[0] <40 ) ptbin=2;
		  else if (Jet_Pt[0]>=40 && Jet_Pt[0] <60 ) ptbin=3;
		  else if (Jet_Pt[0]>=60) ptbin=4;			
		}
		fillcsv_mc(j,hCSV_mc_c[ptbin][etabin], hCSV_mc_b[ptbin][etabin], hCSV_mc_lf[ptbin][etabin],ptave, Jet_CSV,Jet_HadFlav , Weight);
	      }
	    }
	  }
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
  vector<vector<TH1F*>> hCSV_data;
  hCSV_data.resize(n_ptbins, vector<TH1F*>(n_etabins, 0));
  vector<TH1F*> hptave_data;
  for (int i=0; i<n_ptbins;++i){
    if (i==0) pt_counter="0";
    else if (i==1) pt_counter="1";
    else if (i==2) pt_counter="2";
    else if (i==3) pt_counter="3";
    else if (i==4) pt_counter="4";
    for ( int j=0; j<n_etabins;++j){   
      if (j==0) eta_counter="0";
      else if (j==1) eta_counter="1";
      else if (j==2) eta_counter="2";    
      else if (j==3) eta_counter="3";  
      TH1F* h = new TH1F("hCSV_data_ptbin"+pt_counter+"_etabin"+eta_counter,"hCSV_data_ptbin"+pt_counter+"_etabin"+eta_counter,25,-0.1,1);
      h->SetDrawOption("histe0");
      hCSV_data[i][j]=h;    
    }    
    TH1F* hptavg_data = new TH1F("hptavg_data_bin"+pt_counter,"hCSVptavg_bin"+pt_counter,80,0,1000);
    hptavg_data->SetDrawOption("histe0");
    hptave_data.push_back(hptavg_data);
    Weight.at(i)=1;   
  }
  TH1F* h_ptave_data=new TH1F("PtAve_data_w_dijetselec","PtAve_data_w_dijetselec",80,0,1000);
  h_ptave_data->SetDrawOption("histe0");
  //loop over all events
  nentries = datachain->GetEntries(); 
  cout << "total number of data events: " << nentries << endl;
  for (long iEntry=0;iEntry<nentries;iEntry++) {
    if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//     if(iEntry>1000000) break;
    datachain->GetEntry(iEntry);
    float ptave=PtAve_data;
    int etabin=0;
    int ptbin=0;
    if(N_Jets_data >=2){
      if (abs(Jet_Eta_data[0])<etamin && abs(Jet_Eta_data[1])<etamin){ 
	if (DeltaPhi_data> dphicut ){
	  if (N_Jets_data==2){
	    fillhisto(h_ptave_data,ptave, ptave, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	    for (int j=0;j<2;j++){
	      if (Jet_CSV_data[j]<0.605  ){      
		fillcsv_data(j,hCSV_data[0][0], ptave, Jet_CSV_data, Weight, hlt40, hlt60, hlt80, hlt140, hlt200, hlt260, hlt320, hlt400, hlt500);	      
		if(j==0){
		  if (abs(Jet_Eta_data[1])<0.8) etabin=1;
		  else if (abs(Jet_Eta_data[1])>=0.8 && abs(Jet_Eta_data[1]<1.6)) etabin=2;
		  else if (abs(Jet_Eta_data[1])>=1.6 && abs(Jet_Eta_data[1]<2.4)) etabin=3;
		  if (Jet_Pt_data[1]<30) ptbin=1;
		  else if (Jet_Pt_data[1]>=30 && Jet_Pt_data[1] <40 ) ptbin=2;
		  else if (Jet_Pt_data[1]>=40 && Jet_Pt_data[1] <60 ) ptbin=3;
		  else if (Jet_Pt_data[1]>=60) ptbin=4;		
		}
		else if (j==1){
		  if (abs(Jet_Eta_data[0])<0.8) etabin=1;
		  else if (abs(Jet_Eta_data[0])>=0.8 && abs(Jet_Eta_data[0]<1.6)) etabin=2;
		  else if (abs(Jet_Eta_data[0])>=1.6 && abs(Jet_Eta_data[0]<2.4)) etabin=3;
		  if (Jet_Pt_data[0]<30) ptbin=1;
		  else if (Jet_Pt_data[0]>=30 && Jet_Pt_data[0] <40 ) ptbin=2;
		  else if (Jet_Pt_data[0]>=40 && Jet_Pt_data[0] <60 ) ptbin=3;
		  else if (Jet_Pt_data[0]>=60) ptbin=4;	           
		}
		fillcsv_data(j,hCSV_data[ptbin][etabin], ptave, Jet_CSV_data, Weight, hlt40, hlt60, hlt80, hlt140, hlt200, hlt260, hlt320, hlt400, hlt500); 
	      }
	    }
	  }
	  else if (N_Jets_data>=3 && Jet_Pt_data[2]/ptave < pt3cut){	
	    fillhisto(h_ptave_data,ptave, ptave, Weight,'d',hlt40,hlt60,hlt80,hlt140,hlt200,hlt260,hlt320,hlt400,hlt500);
	    for (int j=0;j<2;j++){
	      if (Jet_CSV_data[j]<0.605  ){      
		fillcsv_data(j,hCSV_data[0][0], ptave, Jet_CSV_data, Weight, hlt40, hlt60, hlt80, hlt140, hlt200, hlt260, hlt320, hlt400, hlt500);	      
		if(j==0){
		  if (abs(Jet_Eta_data[1])<0.8) etabin=1;
		  else if (abs(Jet_Eta_data[1])>=0.8 && abs(Jet_Eta_data[1]<1.6)) etabin=2;
		  else if (abs(Jet_Eta_data[1])>=1.6 && abs(Jet_Eta_data[1]<2.4)) etabin=3;
		  if (Jet_Pt_data[1]<30) ptbin=1;
		  else if (Jet_Pt_data[1]>=30 && Jet_Pt_data[1] <40 ) ptbin=2;
		  else if (Jet_Pt_data[1]>=40 && Jet_Pt_data[1] <60 ) ptbin=3;
		  else if (Jet_Pt_data[1]>=60) ptbin=4;		
		}
		else if (j==1){
		  if (abs(Jet_Eta_data[0])<0.8) etabin=1;
		  else if (abs(Jet_Eta_data[0])>=0.8 && abs(Jet_Eta_data[0]<1.6)) etabin=2;
		  else if (abs(Jet_Eta_data[0])>=1.6 && abs(Jet_Eta_data[0]<2.4)) etabin=3;
		  if (Jet_Pt_data[0]<30) ptbin=1;
		  else if (Jet_Pt_data[0]>=30 && Jet_Pt_data[0] <40 ) ptbin=2;
		  else if (Jet_Pt_data[0]>=40 && Jet_Pt_data[0] <60 ) ptbin=3;
		  else if (Jet_Pt_data[0]>=60) ptbin=4;	           
		}
		fillcsv_data(j,hCSV_data[ptbin][etabin], ptave, Jet_CSV_data, Weight, hlt40, hlt60, hlt80, hlt140, hlt200, hlt260, hlt320, hlt400, hlt500); 
	      }
	    }	    
	  }
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
