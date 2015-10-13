// #include "TChain.h"
#include "TBranch.h"
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

// TChain* tree_qcd = new TChain("MVATree");
TTree* tree_qcd = (TTree*)f_qcd->Get("MVATree");
// tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/DiJets_QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8_v2_1.root");
// tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/DiJets_QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8_v2_2-pre.root");
// tree_qcd-> SetBranchStatus("*",0);

// initialize variables from tree

int N_Jets;
tree_qcd->SetBranchAddress("N_Jets",&N_Jets);
float* Jet_Pt = new float[50];
tree_qcd->SetBranchAddress("Jet_Pt",Jet_Pt);
float* Jet_Phi = new float[50];
tree_qcd->SetBranchAddress("Jet_Phi",Jet_Phi);
float DeltaPhi;
tree_qcd->SetBranchAddress("DeltaPhi",&DeltaPhi);
float PtAve;
tree_qcd->SetBranchAddress("PtAve",&PtAve);
float* Jet_Eta = new float[50];
tree_qcd->SetBranchAddress("Jet_Eta",Jet_Eta);  
float* Jet_CSV = new float[50];
tree_qcd->SetBranchAddress("Jet_CSV",Jet_CSV);
float* Jet_Flav = new float[50];
tree_qcd->SetBranchAddress("Jet_Flav",Jet_Flav);


// define histos  
TH1F* h_dphi=new TH1F("h_dphi","h_dphi",45,0,3.5);
TH1F* h_pt3=new TH1F("h_pt3","h_pt3",80,0,350);
TH1F* h_pt3overavg=new TH1F("h_pt3overavg","h_pt3overavg",20,0,2);

TH1F* h_flav_probeJet=new TH1F("h_flav_probeJet","h_flav_probeJet",50,0,23);

TH1F* h_ptavg=new TH1F("h_ptavg","h_ptavg",80,0,500);

TH1F* h_pthardestjet_lf=new TH1F("h_pthardestjet_lf","h_pthardestjet_lf",80,0,500);
TH1F* h_pthardestjet_b=new TH1F("h_pthardestjet_b","h_pthardestjet_b",80,0,500);
TH1F* h_pthardestjet_c=new TH1F("h_pthardestjet_c","h_pthardestjet_c",80,0,500);

TH1F* h_pt_lf=new TH1F("h_pt_lf","h_pt_lf",80,0,500);
TH1F* h_pt_b=new TH1F("h_pt_b","h_pt_b",80,0,500);
TH1F* h_pt_c=new TH1F("h_pt_c","h_pt_c",80,0,500);

TH1F* h_NJets_lf=new TH1F("h_NJets_lf","h_NJets_lf",16,-0.5,15.5);
TH1F* h_NJets_b=new TH1F("h_NJets_b","h_NJets_b",16,-0.5,15.5);
TH1F* h_NJets_c=new TH1F("h_NJets_c","h_NJets_c",16,-0.5,15.5);

TH1F* h_CSV_lf=new TH1F("h_CSV_lf","h_CSV_lf",11,-0.2,1);
TH1F* h_CSV_b=new TH1F("h_CSV_b","h_CSV_b",11,-0.2,1);
TH1F* h_CSV_c=new TH1F("h_CSV_c","h_CSV_c",11,-0.2,1);

TH1F* h_CSV_taggedhigh_lf=new TH1F("h_CSV_taggedhigh_lf","h_CSV_taggedhigh_lf",11,-0.2,1);
TH1F* h_CSV_taggedhigh_b=new TH1F("h_CSV_taggedhigh_b","h_CSV_taggedhigh_b",11,-0.2,1);
TH1F* h_CSV_taggedhigh_c=new TH1F("h_CSV_taggedhigh_c","h_CSV_taggedhigh_c",11,-0.2,1);

TH1F* h_CSV_taggedlow_lf=new TH1F("h_CSV_taggedlow_lf","h_CSV_taggedlow_lf",11,-0.2,1);
TH1F* h_CSV_taggedlow_b=new TH1F("h_CSV_taggedlow_b","h_CSV_taggedlow_b",11,-0.2,1);
TH1F* h_CSV_taggedlow_c=new TH1F("h_CSV_taggedlow_c","h_CSV_taggedlow_c",11,-0.2,1);

TH1F* h_CSV_true_taggedhigh_lf=new TH1F("h_CSV_true_taggedhigh_lf","h_true_CSV_taggedhigh_lf",11,-0.2,1);
TH1F* h_CSV_true_taggedhigh_b=new TH1F("h_CSV_true_taggedhigh_b","h_CSV_true_taggedhigh_b",11,-0.2,1);
TH1F* h_CSV_true_taggedhigh_c=new TH1F("h_CSV_true_taggedhigh_c","h_CSV_true_taggedhigh_c",11,-0.2,1);

TH1F* h_CSV_true_taggedlow_lf=new TH1F("h_CSV_true_taggedlow_lf","h_CSV_true_taggedlow_lf",11,-0.2,1);
TH1F* h_CSV_true_taggedlow_b=new TH1F("h_CSV_true_taggedlow_b","h_CSV_true_taggedlow_b",11,-0.2,1);
TH1F* h_CSV_true_taggedlow_c=new TH1F("h_CSV_true_taggedlow_c","h_CSV_true_taggedlow_c",11,-0.2,1);
float dphi;
float pt_avg;
float pt3cut;
long nentries ;
pt3cut=0.1;
// loop over all events
nentries = tree_qcd->GetEntries(); 
cout << "total number of events: " << nentries << endl;
for (long iEntry=0;iEntry<nentries;iEntry++) {

  if(iEntry%10000==0) cout << "analyzing event " << iEntry << endl;
//   if(iEntry>100000) break;
  tree_qcd->GetEntry(iEntry);
  if(N_Jets >=2){
    dphi=DeltaPhi;
    h_dphi->Fill(dphi);
    pt_avg=PtAve;
    h_ptavg->Fill(pt_avg);
    if(N_Jets>=3){
      h_pt3->Fill(Jet_Pt[2]);
      h_pt3overavg->Fill(Jet_Pt[2]/pt_avg);
      }  
    for (int j=0;j< N_Jets;j++){
      if (abs(Jet_Flav[j])==4){  
	h_NJets_c->Fill(N_Jets);
	h_CSV_c->Fill(Jet_CSV[j]);
	}
	    
      else if (abs(Jet_Flav[j])==5){ 
	h_NJets_b->Fill(N_Jets);
	h_CSV_b->Fill(Jet_CSV[j]);
	}
	    
      else if (abs(Jet_Flav[j])!=5 && abs(Jet_Flav[j])!=4){
	h_NJets_lf->Fill(N_Jets);
	h_CSV_lf->Fill(Jet_CSV[j]);
	}
      }
      
    if (dphi> 2.7){	
      if (abs(Jet_Eta[0])<2.1 && abs(Jet_Eta[1])<2.1){
	  
	if (abs(Jet_Flav[0])==4){
	      h_pthardestjet_c->Fill(Jet_Pt[0]);}	    
	else if (abs(Jet_Flav[0])==5){ 
	      h_pthardestjet_b->Fill(Jet_Pt[0]);}	  
	else if ( abs(Jet_Flav[0])!=5 && abs(Jet_Flav[0])!=4){
	      h_pthardestjet_lf->Fill(Jet_Pt[0]);}
      //csv tagging
	for (int j=0;j<2;j++){	    
	  if (abs(Jet_Flav[j])==4) h_pt_c->Fill(Jet_Pt[j]);
	  else if (abs(Jet_Flav[j])==5) h_pt_b->Fill(Jet_Pt[j]);
	  else if (abs(Jet_Flav[j])!=5 && abs(Jet_Flav[j])!=4) h_pt_lf->Fill(Jet_Pt[j]);
	  if (Jet_CSV[j]>0.97){
		if (N_Jets >=3){
		  if (Jet_Pt[2]/pt_avg < pt3cut){
		      if (j==0){
			if (abs(Jet_Flav[1])==4) h_CSV_taggedhigh_c->Fill(Jet_CSV[1]);
			else if (abs(Jet_Flav[1])==5) h_CSV_taggedhigh_b->Fill(Jet_CSV[1]);
			else if (abs(Jet_Flav[1])!=4 && abs(Jet_Flav[1])!=5) h_CSV_taggedhigh_lf->Fill(Jet_CSV[1]);
		      }
		      else if (j==1){
			if (abs(Jet_Flav[0])==4) h_CSV_taggedhigh_c->Fill(Jet_CSV[0]);
			else if (abs(Jet_Flav[0])==5) h_CSV_taggedhigh_b->Fill(Jet_CSV[0]);
			else if (abs(Jet_Flav[0])!=4 && abs(Jet_Flav[0])!=5) h_CSV_taggedhigh_lf->Fill(Jet_CSV[0]);
		      }
		}
		}
		else if (j==0){
		  if (abs(Jet_Flav[1])==4) h_CSV_taggedhigh_c->Fill(Jet_CSV[1]);
		  else if (abs(Jet_Flav[1])==5) h_CSV_taggedhigh_b->Fill(Jet_CSV[1]);
		  else if (abs(Jet_Flav[1])!=4 && abs(Jet_Flav[1])!=5) h_CSV_taggedhigh_lf->Fill(Jet_CSV[1]);
		}
		else if (j==1){
		  if (abs(Jet_Flav[0])==4) h_CSV_taggedhigh_c->Fill(Jet_CSV[0]);
		  else if (abs(Jet_Flav[0])==5) h_CSV_taggedhigh_b->Fill(Jet_CSV[0]);
		  else if (abs(Jet_Flav[0])!=4 && abs(Jet_Flav[0])!=5) h_CSV_taggedhigh_lf->Fill(Jet_CSV[0]);
		}
	  }
		  
	  else if (Jet_CSV[j]<0.605){
		if (N_Jets >=3){
		  if (Jet_Pt[2]/pt_avg < pt3cut){
		      if (j==0){
			if (abs(Jet_Flav[1])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[1]);
			else if (abs(Jet_Flav[1])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[1]);
			else if (abs(Jet_Flav[1])!=4 && abs(Jet_Flav[1])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[1]);
		      }
		      else if (j==1){
			if (abs(Jet_Flav[0])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[0]);
			else if (abs(Jet_Flav[0])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[0]);
			else if (abs(Jet_Flav[0])!=4 && abs(Jet_Flav[0])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[0]);
		      }
		  }
		}
		else if (j==0){
		  if (abs(Jet_Flav[1])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[1]);
		  else if (abs(Jet_Flav[1])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[1]);
		  else if (abs(Jet_Flav[1])!=4 && abs(Jet_Flav[1])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[1]);
		}
		else if (j==1){
		  if (abs(Jet_Flav[0])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[0]);
		  else if (abs(Jet_Flav[0])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[0]);
		  else if (abs(Jet_Flav[0])!=4 && abs(Jet_Flav[0])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[0]);
		}
	  }
	  //true tagging	  
	  if (abs(Jet_Flav[j])==5){
		if (N_Jets >=3){
		  if (Jet_Pt[2]/pt_avg < pt3cut){
		      if (j==0){
			if (abs(Jet_Flav[1])==4) h_CSV_true_taggedhigh_c->Fill(Jet_CSV[1]);
			else if (abs(Jet_Flav[1])==5) h_CSV_true_taggedhigh_b->Fill(Jet_CSV[1]);
			else if (abs(Jet_Flav[1])!=4 && abs(Jet_Flav[1])!=5) h_CSV_true_taggedhigh_lf->Fill(Jet_CSV[1]);
		      }
		      else if (j==1){
			if (abs(Jet_Flav[0])==4) h_CSV_true_taggedhigh_c->Fill(Jet_CSV[0]);
			else if (abs(Jet_Flav[0])==5) h_CSV_true_taggedhigh_b->Fill(Jet_CSV[0]);
			else if (abs(Jet_Flav[0])!=4 && abs(Jet_Flav[0])!=5) h_CSV_true_taggedhigh_lf->Fill(Jet_CSV[0]);
		      }
		}
		}
		else if (j==0){
		  if (abs(Jet_Flav[1])==4) h_CSV_true_taggedhigh_c->Fill(Jet_CSV[1]);
		  else if (abs(Jet_Flav[1])==5) h_CSV_true_taggedhigh_b->Fill(Jet_CSV[1]);
		  else if (abs(Jet_Flav[1])!=4 && abs(Jet_Flav[1])!=5) h_CSV_true_taggedhigh_lf->Fill(Jet_CSV[1]);
		}
		else if (j==1){
		  if (abs(Jet_Flav[0])==4) h_CSV_true_taggedhigh_c->Fill(Jet_CSV[0]);
		  else if (abs(Jet_Flav[0])==5) h_CSV_true_taggedhigh_b->Fill(Jet_CSV[0]);
		  else if (abs(Jet_Flav[0])!=4 && abs(Jet_Flav[0])!=5) h_CSV_true_taggedhigh_lf->Fill(Jet_CSV[0]);
		}
	  }
		  
	  else if (abs(Jet_Flav[j])!=5){
		if (N_Jets >=3){
		  if (Jet_Pt[2]/pt_avg < pt3cut){
		      if (j==0){
			if (abs(Jet_Flav[1])==4) h_CSV_true_taggedlow_c->Fill(Jet_CSV[1]);
			else if (abs(Jet_Flav[1])==5) h_CSV_true_taggedlow_b->Fill(Jet_CSV[1]);
			else if (abs(Jet_Flav[1])!=4 && abs(Jet_Flav[1])!=5) h_CSV_true_taggedlow_lf->Fill(Jet_CSV[1]);
		      }
		      else if (j==1){
			if (abs(Jet_Flav[0])==4) h_CSV_true_taggedlow_c->Fill(Jet_CSV[0]);
			else if (abs(Jet_Flav[0])==5) h_CSV_true_taggedlow_b->Fill(Jet_CSV[0]);
			else if (abs(Jet_Flav[0])!=4 && abs(Jet_Flav[0])!=5) h_CSV_true_taggedlow_lf->Fill(Jet_CSV[0]);
		      }
		  }
		}
		else if (j==0){
		  if (abs(Jet_Flav[1])==4) h_CSV_true_taggedlow_c->Fill(Jet_CSV[1]);
		  else if (abs(Jet_Flav[1])==5) h_CSV_true_taggedlow_b->Fill(Jet_CSV[1]);
		  else if (abs(Jet_Flav[1])!=4 && abs(Jet_Flav[1])!=5) h_CSV_true_taggedlow_lf->Fill(Jet_CSV[1]);
		}
		else if (j==1){
		  if (abs(Jet_Flav[0])==4) h_CSV_true_taggedlow_c->Fill(Jet_CSV[0]);
		  else if (abs(Jet_Flav[0])==5) h_CSV_true_taggedlow_b->Fill(Jet_CSV[0]);
		  else if (abs(Jet_Flav[0])!=4 && abs(Jet_Flav[0])!=5) h_CSV_true_taggedlow_lf->Fill(Jet_CSV[0]);
		}
	}
	}
	}
    }
//   cout << iEntry;
  } // end of event loop
}
// write histos
  
cout << "write histos to file";
TFile* outfile=new TFile("outfile.root","RECREATE");    

h_dphi->Write();
h_pt3->Write();
h_pt3overavg->Write();

h_flav_probeJet->Write();

h_ptavg->Write();

h_pthardestjet_lf->Write();
h_pthardestjet_b->Write();
h_pthardestjet_c->Write();

h_pt_lf->Write();
h_pt_b->Write();
h_pt_c->Write();

h_NJets_lf->Write();
h_NJets_b->Write();
h_NJets_c->Write();

h_CSV_lf->Write();
h_CSV_b->Write();
h_CSV_c->Write();

h_CSV_taggedhigh_lf->Write();
h_CSV_taggedhigh_b->Write();
h_CSV_taggedhigh_c->Write();

h_CSV_taggedlow_lf->Write();
h_CSV_taggedlow_b->Write();
h_CSV_taggedlow_c->Write();

h_CSV_true_taggedhigh_lf->Write();
h_CSV_true_taggedhigh_b->Write();
h_CSV_true_taggedhigh_c->Write();

h_CSV_true_taggedlow_lf->Write();
h_CSV_true_taggedlow_b->Write();
h_CSV_true_taggedlow_c->Write();

outfile->Close();


  }

  int main(){
    qcd_dijet();
  }
