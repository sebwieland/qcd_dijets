// #include "TChain.h"
#include "Rtypes.h"
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




void qcd_dijet(){
  TH1F::SetDefaultSumw2();
  
  // open files
TChain* tree_qcd = new TChain("MVATree");

tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/DiJets_QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8_v2_1.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/DiJets_QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8_v2_2-pre.root");
// tree_qcd-> SetBranchStatus("*",0);

// initialize variables from tree

int N_Jets;
tree_qcd->SetBranchAddress("N_Jets",&N_Jets);
float* Jet_Pt = new float[120];
tree_qcd->SetBranchAddress("Jet_Pt",Jet_Pt);
float* Jet_Phi = new float[120];
tree_qcd->SetBranchAddress("Jet_Phi",Jet_Phi);
float DeltaPhi;
tree_qcd->SetBranchAddress("DeltaPhi",&DeltaPhi);
float PtAve;
tree_qcd->SetBranchAddress("PtAve",&PtAve);
float* Jet_Eta = new float[120];
tree_qcd->SetBranchAddress("Jet_Eta",Jet_Eta);  
float* Jet_CSV = new float[120];
tree_qcd->SetBranchAddress("Jet_CSV",Jet_CSV);
float* Jet_HadFlav = new float[120];
tree_qcd->SetBranchAddress("Jet_HadronFlav",Jet_HadFlav);
float* Jet_PartFlav = new float[120];
tree_qcd->SetBranchAddress("Jet_PartonFlav",Jet_PartFlav);
float* Jet_SumSVMass = new float[120];
tree_qcd->SetBranchAddress("Jet_SumSVMass",Jet_SumSVMass);
float* Jet_NSV = new float[120];
tree_qcd->SetBranchAddress("Jet_NSV",Jet_NSV);


// define histos  
TH1F* h_dphi=new TH1F("h_dphi","h_dphi",45,0,3.5);
TH1F* h_pt3=new TH1F("h_pt3","h_pt3",80,0,350);
TH1F* h_pt3overavg=new TH1F("h_pt3overavg","h_pt3overavg",20,0,2);

TH1F* h_flav_probeJet=new TH1F("h_flav_probeJet","h_flav_probeJet",50,0,23);
TH1F* h_partonFlav=new TH1F("h_partonFlav","h_partonFlav",50,0,23);

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

TH1F* h_SumSVMass_part21_had5=new TH1F("h_SumSVMass_part21_had5","h_SumSVMass_part21_had5",30,0,8);
TH1F* h_SumSVMass_part5_had5=new TH1F("h_SumSVMass_part5_had5","h_SumSVMass_part5_had5",30,0,8);

TH1F* h_NSV_part21_had5=new TH1F("h_NSV_part21_had5","h_NSV_part21_had5",4,0,4);
TH1F* h_NSV_part5_had5=new TH1F("h_NSV_part5_had5","h_NSV_part5_had5",4,0,4);

TH1F* h_tagjet_partflav=new TH1F("h_tagjet_partflav","h_tagjet_partflav",50,0,23);
TH1F* h_tagjet_hadflav=new TH1F("h_tagjet_hadflav","h_tagjet_hadflav",50,0,23);

TH1F* h_tagjet_partflav_wo_SVMassCut=new TH1F("h_tagjet_partflav_wo_SVMassCut","h_tagjet_partflav_wo_SVMassCut",50,0,23);

float dphi;
float pt_avg;
float pt3cut;
long nentries;
float SVMassCut;
SVMassCut=2;
pt3cut=0.1;
// loop over all events
nentries = tree_qcd->GetEntries(); 
cout << "total number of events: " << nentries << endl;
for (long iEntry=0;iEntry<nentries;iEntry++) {

  if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
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
       h_partonFlav->Fill(Jet_PartFlav[j]);
      if (abs(Jet_PartFlav[j])==4){  
	h_NJets_c->Fill(N_Jets);
	h_CSV_c->Fill(Jet_CSV[j]);
	}
	    
      else if (abs(Jet_PartFlav[j])==5){ 
	h_NJets_b->Fill(N_Jets);
	h_CSV_b->Fill(Jet_CSV[j]);
	}
	    
      else if (abs(Jet_PartFlav[j])!=5 && abs(Jet_PartFlav[j])!=4){
	h_NJets_lf->Fill(N_Jets);
	h_CSV_lf->Fill(Jet_CSV[j]);
	}
      }
      
    if (dphi> 2.7 ){	
      if (abs(Jet_Eta[0])<2.1 && abs(Jet_Eta[1])<2.1){
	  
	if (abs(Jet_PartFlav[0])==4){
	      h_pthardestjet_c->Fill(Jet_Pt[0]);}	    
	else if (abs(Jet_PartFlav[0])==5){ 
	      h_pthardestjet_b->Fill(Jet_Pt[0]);}	  
	else if ( abs(Jet_PartFlav[0])!=5 && abs(Jet_PartFlav[0])!=4){
	      h_pthardestjet_lf->Fill(Jet_Pt[0]);}
      
	for (int j=0;j<2;j++){	
	  if (abs(Jet_PartFlav[j])==5 && abs(Jet_HadFlav[j]==5)) {
	    h_SumSVMass_part5_had5->Fill(Jet_SumSVMass[j]);
	    h_NSV_part5_had5->Fill(Jet_NSV[j]);
	  }
	  if (abs(Jet_PartFlav[j])==21 && abs(Jet_HadFlav[j]==5)){
	    h_SumSVMass_part21_had5->Fill(Jet_SumSVMass[j]);
	    h_NSV_part21_had5->Fill(Jet_NSV[j]);
	  }
	  if (abs(Jet_PartFlav[j])==4) h_pt_c->Fill(Jet_Pt[j]);
	  else if (abs(Jet_PartFlav[j])==5) h_pt_b->Fill(Jet_Pt[j]);
	  else if (abs(Jet_PartFlav[j])!=5 && abs(Jet_PartFlav[j])!=4) h_pt_lf->Fill(Jet_Pt[j]);
	  //csv tagging
	  if (Jet_CSV[j]>0.97){
	    if (N_Jets >=3){
		  if (Jet_Pt[2]/pt_avg < pt3cut){
		      if (j==0){
			h_tagjet_partflav_wo_SVMassCut->Fill(abs(Jet_PartFlav[0]));
		      }
		      else if (j==1){
			h_tagjet_partflav_wo_SVMassCut->Fill(abs(Jet_PartFlav[1]));
		      }
		}
	    }
	    else if (j==0){
		  h_tagjet_partflav_wo_SVMassCut->Fill(abs(Jet_PartFlav[0]));
		}
	    else if (j==1){
		  h_tagjet_partflav_wo_SVMassCut->Fill(abs(Jet_PartFlav[1]));
		}
		
	    if (Jet_SumSVMass[j]<SVMassCut){
		if (N_Jets >=3){
		  if (Jet_Pt[2]/pt_avg < pt3cut){
		      if (j==0){
			h_tagjet_hadflav->Fill(abs(Jet_HadFlav[0]));
			h_tagjet_partflav->Fill(abs(Jet_PartFlav[0]));
			if (abs(Jet_PartFlav[1])==4) h_CSV_taggedhigh_c->Fill(Jet_CSV[1]);
			else if (abs(Jet_PartFlav[1])==5) h_CSV_taggedhigh_b->Fill(Jet_CSV[1]);
			else if (abs(Jet_PartFlav[1])!=4 && abs(Jet_PartFlav[1])!=5) h_CSV_taggedhigh_lf->Fill(Jet_CSV[1]);
		      }
		      else if (j==1){
			h_tagjet_hadflav->Fill(abs(Jet_HadFlav[1]));
			h_tagjet_partflav->Fill(abs(Jet_PartFlav[1]));
			if (abs(Jet_PartFlav[0])==4) h_CSV_taggedhigh_c->Fill(Jet_CSV[0]);
			else if (abs(Jet_PartFlav[0])==5) h_CSV_taggedhigh_b->Fill(Jet_CSV[0]);
			else if (abs(Jet_PartFlav[0])!=4 && abs(Jet_PartFlav[0])!=5) h_CSV_taggedhigh_lf->Fill(Jet_CSV[0]);
		      }
		}
		}
		else if (j==0){
		  h_tagjet_hadflav->Fill(abs(Jet_HadFlav[0]));
		  h_tagjet_partflav->Fill(abs(Jet_PartFlav[0]));
		  if (abs(Jet_PartFlav[1])==4) h_CSV_taggedhigh_c->Fill(Jet_CSV[1]);
		  else if (abs(Jet_PartFlav[1])==5) h_CSV_taggedhigh_b->Fill(Jet_CSV[1]);
		  else if (abs(Jet_PartFlav[1])!=4 && abs(Jet_PartFlav[1])!=5) h_CSV_taggedhigh_lf->Fill(Jet_CSV[1]);
		}
		else if (j==1){
		  h_tagjet_hadflav->Fill(abs(Jet_HadFlav[1]));
		  h_tagjet_partflav->Fill(abs(Jet_PartFlav[1]));
		  if (abs(Jet_PartFlav[0])==4) h_CSV_taggedhigh_c->Fill(Jet_CSV[0]);
		  else if (abs(Jet_PartFlav[0])==5) h_CSV_taggedhigh_b->Fill(Jet_CSV[0]);
		  else if (abs(Jet_PartFlav[0])!=4 && abs(Jet_PartFlav[0])!=5) h_CSV_taggedhigh_lf->Fill(Jet_CSV[0]);
		}	  
	    }
	  }
		  
	  else if (Jet_CSV[j]<0.605){
		if (N_Jets >=3){
		  if (Jet_Pt[2]/pt_avg < pt3cut){
		      if (j==0){
			if (abs(Jet_PartFlav[1])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[1]);
			else if (abs(Jet_PartFlav[1])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[1]);
			else if (abs(Jet_PartFlav[1])!=4 && abs(Jet_PartFlav[1])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[1]);
		      }
		      else if (j==1){
			if (abs(Jet_PartFlav[0])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[0]);
			else if (abs(Jet_PartFlav[0])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[0]);
			else if (abs(Jet_PartFlav[0])!=4 && abs(Jet_PartFlav[0])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[0]);
		      }
		  }
		}
		else if (j==0){
		  if (abs(Jet_PartFlav[1])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[1]);
		  else if (abs(Jet_PartFlav[1])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[1]);
		  else if (abs(Jet_PartFlav[1])!=4 && abs(Jet_PartFlav[1])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[1]);
		}
		else if (j==1){
		  if (abs(Jet_PartFlav[0])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[0]);
		  else if (abs(Jet_PartFlav[0])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[0]);
		  else if (abs(Jet_PartFlav[0])!=4 && abs(Jet_PartFlav[0])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[0]);
		}
	  }
	  //true tagging	  
	  if (abs(Jet_PartFlav[j])==5){
		if (N_Jets >=3){
		  if (Jet_Pt[2]/pt_avg < pt3cut){
		      if (j==0){
			if (abs(Jet_PartFlav[1])==4) h_CSV_true_taggedhigh_c->Fill(Jet_CSV[1]);
			else if (abs(Jet_PartFlav[1])==5) h_CSV_true_taggedhigh_b->Fill(Jet_CSV[1]);
			else if (abs(Jet_PartFlav[1])!=4 && abs(Jet_PartFlav[1])!=5) h_CSV_true_taggedhigh_lf->Fill(Jet_CSV[1]);
		      }
		      else if (j==1){
			if (abs(Jet_PartFlav[0])==4) h_CSV_true_taggedhigh_c->Fill(Jet_CSV[0]);
			else if (abs(Jet_PartFlav[0])==5) h_CSV_true_taggedhigh_b->Fill(Jet_CSV[0]);
			else if (abs(Jet_PartFlav[0])!=4 && abs(Jet_PartFlav[0])!=5) h_CSV_true_taggedhigh_lf->Fill(Jet_CSV[0]);
		      }
		}
		}
		else if (j==0){
		  if (abs(Jet_PartFlav[1])==4) h_CSV_true_taggedhigh_c->Fill(Jet_CSV[1]);
		  else if (abs(Jet_PartFlav[1])==5) h_CSV_true_taggedhigh_b->Fill(Jet_CSV[1]);
		  else if (abs(Jet_PartFlav[1])!=4 && abs(Jet_PartFlav[1])!=5) h_CSV_true_taggedhigh_lf->Fill(Jet_CSV[1]);
		}
		else if (j==1){
		  if (abs(Jet_PartFlav[0])==4) h_CSV_true_taggedhigh_c->Fill(Jet_CSV[0]);
		  else if (abs(Jet_PartFlav[0])==5) h_CSV_true_taggedhigh_b->Fill(Jet_CSV[0]);
		  else if (abs(Jet_PartFlav[0])!=4 && abs(Jet_PartFlav[0])!=5) h_CSV_true_taggedhigh_lf->Fill(Jet_CSV[0]);
		}
	  }
		  
	  else if (abs(Jet_PartFlav[j])!=5){
		if (N_Jets >=3){
		  if (Jet_Pt[2]/pt_avg < pt3cut){
		      if (j==0){
			if (abs(Jet_PartFlav[1])==4) h_CSV_true_taggedlow_c->Fill(Jet_CSV[1]);
			else if (abs(Jet_PartFlav[1])==5) h_CSV_true_taggedlow_b->Fill(Jet_CSV[1]);
			else if (abs(Jet_PartFlav[1])!=4 && abs(Jet_PartFlav[1])!=5) h_CSV_true_taggedlow_lf->Fill(Jet_CSV[1]);
		      }
		      else if (j==1){
			if (abs(Jet_PartFlav[0])==4) h_CSV_true_taggedlow_c->Fill(Jet_CSV[0]);
			else if (abs(Jet_PartFlav[0])==5) h_CSV_true_taggedlow_b->Fill(Jet_CSV[0]);
			else if (abs(Jet_PartFlav[0])!=4 && abs(Jet_PartFlav[0])!=5) h_CSV_true_taggedlow_lf->Fill(Jet_CSV[0]);
		      }
		  }
		}
		else if (j==0){
		  if (abs(Jet_PartFlav[1])==4) h_CSV_true_taggedlow_c->Fill(Jet_CSV[1]);
		  else if (abs(Jet_PartFlav[1])==5) h_CSV_true_taggedlow_b->Fill(Jet_CSV[1]);
		  else if (abs(Jet_PartFlav[1])!=4 && abs(Jet_PartFlav[1])!=5) h_CSV_true_taggedlow_lf->Fill(Jet_CSV[1]);
		}
		else if (j==1){
		  if (abs(Jet_PartFlav[0])==4) h_CSV_true_taggedlow_c->Fill(Jet_CSV[0]);
		  else if (abs(Jet_PartFlav[0])==5) h_CSV_true_taggedlow_b->Fill(Jet_CSV[0]);
		  else if (abs(Jet_PartFlav[0])!=4 && abs(Jet_PartFlav[0])!=5) h_CSV_true_taggedlow_lf->Fill(Jet_CSV[0]);
		}
	}
	}
	}
    }
//   cout << iEntry;
  } // end of event loop
}
// write histos
  
cout << "write histos to file"<<endl;
TFile* outfile=new TFile("outfile.root","RECREATE");    
gStyle->SetFillStyle(1001);




h_flav_probeJet->Write();

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

h_partonFlav->Write();




h_NJets_lf->SetFillColor(kGreen);
h_NJets_b->SetFillColor(kRed);
h_NJets_c->SetFillColor(kBlue);

h_CSV_lf->SetFillColor(kGreen);
h_CSV_b->SetFillColor(kRed);
h_CSV_c->SetFillColor(kBlue);

h_CSV_taggedhigh_lf->SetFillColor(kGreen);
h_CSV_taggedhigh_b->SetFillColor(kRed);
h_CSV_taggedhigh_c->SetFillColor(kBlue);

h_CSV_taggedlow_lf->SetFillColor(kGreen);
h_CSV_taggedlow_b->SetFillColor(kRed);
h_CSV_taggedlow_c->SetFillColor(kBlue);

h_CSV_true_taggedhigh_lf->SetFillColor(kGreen);
h_CSV_true_taggedhigh_b->SetFillColor(kRed);
h_CSV_true_taggedhigh_c->SetFillColor(kBlue);

h_CSV_true_taggedlow_lf->SetFillColor(kGreen);
h_CSV_true_taggedlow_b->SetFillColor(kRed);
h_CSV_true_taggedlow_c->SetFillColor(kBlue);

h_pt_lf->SetFillColor(kGreen);
h_pt_b->SetFillColor(kRed);
h_pt_c->SetFillColor(kBlue);

h_pthardestjet_lf->SetFillColor(kGreen);
h_pthardestjet_b->SetFillColor(kRed);
h_pthardestjet_c->SetFillColor(kBlue);


THStack* stack_NJets=new THStack();
// THStack* stack_NBTagsM=new THStack();
THStack* stack_CSV=new THStack();
// THStack* stack_CSVtagged=new THStack();
THStack* stack_Jet_Pt=new THStack();
THStack* stack_CSVtaggedlow=new THStack();
THStack* stack_CSVtaggedhigh=new THStack();
THStack* stack_pthardestjet=new THStack();
THStack* stack_true_CSVtaggedlow=new THStack();
THStack* stack_true_CSVtaggedhigh=new THStack();


stack_NJets->Add(h_NJets_b);
stack_NJets->Add(h_NJets_c);
stack_NJets->Add(h_NJets_lf);

stack_CSV->Add(h_CSV_b);
stack_CSV->Add(h_CSV_c);
stack_CSV->Add(h_CSV_lf);

stack_CSVtaggedhigh->Add(h_CSV_taggedhigh_b);
stack_CSVtaggedhigh->Add(h_CSV_taggedhigh_c);
stack_CSVtaggedhigh->Add(h_CSV_taggedhigh_lf);

stack_CSVtaggedlow->Add(h_CSV_taggedlow_b);
stack_CSVtaggedlow->Add(h_CSV_taggedlow_c);
stack_CSVtaggedlow->Add(h_CSV_taggedlow_lf);

stack_Jet_Pt->Add(h_pt_b);
stack_Jet_Pt->Add(h_pt_c);
stack_Jet_Pt->Add(h_pt_lf);

stack_pthardestjet->Add(h_pthardestjet_b);
stack_pthardestjet->Add(h_pthardestjet_c);
stack_pthardestjet->Add(h_pthardestjet_lf);

stack_true_CSVtaggedhigh->Add(h_CSV_true_taggedhigh_b);
stack_true_CSVtaggedhigh->Add(h_CSV_true_taggedhigh_c);
stack_true_CSVtaggedhigh->Add(h_CSV_true_taggedhigh_lf);

stack_true_CSVtaggedlow->Add(h_CSV_true_taggedlow_b);
stack_true_CSVtaggedlow->Add(h_CSV_true_taggedlow_c);
stack_true_CSVtaggedlow->Add(h_CSV_true_taggedlow_lf);


TCanvas* c1=new TCanvas();

c1->cd();
stack_CSV->Draw("hist");
stack_CSV->GetXaxis()->SetTitle("CSV of all Jets (>=2 jets, w/o dphi and PtAvg cut) ");
stack_CSV->Write();
c1->SaveAs("CSV_alljets.png");


h_dphi->Draw("HIST");
h_dphi->GetXaxis()->SetTitle("d_phi of 2 hardest Jets (>=2 jets)");
h_dphi->Write();
c1->SaveAs("d_phi.png");


stack_NJets->Draw("HIST");
stack_NJets->GetXaxis()->SetTitle("N Jets (w/o dphi and PtAvg cut)");
stack_NJets->Write();
c1->SaveAs("N_Jets.png");


stack_CSVtaggedhigh->Draw("HIST");
stack_CSVtaggedhigh->GetXaxis()->SetTitle("CSV probe Jet (HF)");
stack_CSVtaggedhigh->Write();
c1->SaveAs("CSV_probejet_HF.png");


stack_CSVtaggedlow->Draw("HIST");
stack_CSVtaggedlow->GetXaxis()->SetTitle("CSV probe Jet (LF)");
stack_CSVtaggedlow->Write();
c1->SaveAs("CSV_probejet_LF.png");

;
h_pt3->Draw("HIST");
h_pt3->GetXaxis()->SetTitle("Jet_Pt[2]");
h_pt3->Write();
c1->SaveAs("Jet_Pt2.png");


h_pt3overavg->Draw("HIST");
h_pt3overavg->GetXaxis()->SetTitle("pt3 over pt_avg");
h_pt3overavg->Write();
c1->SaveAs("pt3overavg.png");


stack_Jet_Pt->Draw("HIST");
stack_Jet_Pt->GetXaxis()->SetTitle("Pt two hardest Jets");
stack_Jet_Pt->Write();
c1->SaveAs("pt_2hardestjets.png");


h_ptavg->Draw("HIST");
h_ptavg->GetXaxis()->SetTitle("Pt avg (>=2 jets)");
h_ptavg->Write();
c1->SaveAs("ptavg.png");


stack_pthardestjet->Draw("hist");
stack_pthardestjet->GetXaxis()->SetTitle("Pt of hardest Jet");
stack_pthardestjet->Write();
c1->SaveAs("pt_hardestjet.png");
cout << "b: "<< h_pthardestjet_b->Integral()<<endl;
cout <<  "lf: "<< h_pthardestjet_lf->Integral()<<endl;
cout << "c: "<< h_pthardestjet_c->Integral()<<endl;


stack_true_CSVtaggedhigh->Draw("HIST");
stack_true_CSVtaggedhigh->GetXaxis()->SetTitle("CSV probe Jet (HF, truth tagged)");
stack_true_CSVtaggedhigh->Write();
c1->SaveAs("CSV_probejet_HF_truthtagged.png");


stack_true_CSVtaggedlow->Draw("HIST");
stack_true_CSVtaggedlow->GetXaxis()->SetTitle("CSV probe Jet (LF, truth tagged)");
stack_true_CSVtaggedlow->Write();
c1->SaveAs("CSV_probejet_LF_truthtagged.png");


h_flav_probeJet->Draw("HIST");
h_flav_probeJet->GetXaxis()->SetTitle("Flav of probe Jet (HF, truth tagged)");
h_flav_probeJet->Write();
c1->SaveAs("flav_probejet.png");


h_SumSVMass_part21_had5->Draw("HIST");
h_SumSVMass_part21_had5->Write();
h_SumSVMass_part21_had5->GetXaxis()->SetTitle("SumSVMass part21, had5");
c1->SaveAs("SumSVMass_part21_had5.png");


h_SumSVMass_part5_had5->Draw("HIST");
h_SumSVMass_part5_had5->Write();
h_SumSVMass_part5_had5->GetXaxis()->SetTitle("SumSVMass part5, had5");
c1->SaveAs("SumSVMass_part5_had5.png");


h_NSV_part21_had5->Draw("HIST");
h_NSV_part21_had5->Write();
h_NSV_part21_had5->GetXaxis()->SetTitle("NSV part21, had5");
c1->SaveAs("NSV_part21_had5.png");


h_NSV_part5_had5->Draw("HIST");
h_NSV_part5_had5->Write();
h_NSV_part5_had5->GetXaxis()->SetTitle("NSV part5, had5");
c1->SaveAs("NSV_part5_had5.png");


h_tagjet_hadflav->Draw("HIST");
h_tagjet_hadflav->Write();
h_tagjet_hadflav->GetXaxis()->SetTitle("tag Jet hadron flavor");
c1->SaveAs("tagjet_hadflav.png");

h_tagjet_partflav->Draw("HIST");
h_tagjet_partflav->Write();
h_tagjet_partflav->GetXaxis()->SetTitle("tag Jet parton flavor");
c1->SaveAs("tagjet_partflav.png");

h_tagjet_partflav_wo_SVMassCut->Draw("HIST");
h_tagjet_partflav_wo_SVMassCut->Write();
h_tagjet_partflav_wo_SVMassCut->GetXaxis()->SetTitle("tag Jet parton flavor w/o SVMassCut");
c1->SaveAs("tagjet_partflav_wo_SVMassCut.png");


//HF SVMassCut eff and purity
float b_w_SVMassCut;
float b_wo_SVMassCut;
float purity_w_SVMassCut;
float purity_wo_SVMassCut;
float eff;
b_w_SVMassCut=h_tagjet_partflav->GetBinContent(h_tagjet_partflav->FindBin(4));
b_wo_SVMassCut=h_tagjet_partflav_wo_SVMassCut->GetBinContent(h_tagjet_partflav_wo_SVMassCut->FindBin(4));
purity_w_SVMassCut=b_w_SVMassCut/h_tagjet_partflav->Integral();
purity_wo_SVMassCut=b_wo_SVMassCut/h_tagjet_partflav_wo_SVMassCut->Integral();
eff=b_w_SVMassCut/b_wo_SVMassCut;

cout << "HF:" <<endl;
cout <<"purity with SVMassCut @ "<<SVMassCut<<": "<< purity_w_SVMassCut << endl;
cout <<"purity without SVMassCut @ "<<SVMassCut<<": "<< purity_wo_SVMassCut << endl;
cout <<"efficiency for SVMassCut @ "<<SVMassCut<<": "<< eff << endl;

//LF Purity 
float purity_lf;
float lf;
lf=h_CSV_taggedlow_c->Integral()+h_CSV_taggedlow_lf->Integral();
purity_lf=lf/(h_CSV_taggedlow_c->Integral()+h_CSV_taggedlow_lf->Integral()+h_CSV_taggedlow_b->Integral());

cout << "LF:" << endl;
cout <<"purity: "<< purity_lf <<endl;
outfile->Close();

  }

  int main(){
    qcd_dijet();    
  }
