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

using namespace std;
void qcd_dijet(){
//   TH1F::SetDefaultSumw2();
  
  // open files
TChain* tree_qcd = new TChain("MVATree");

// tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/DiJets_QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8_v2_1.root");
// tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/DiJets_QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8_v2_2-pre.root");

tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_10to15_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_5to10_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8.root");
tree_qcd->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/v2/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8.root");
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
TH1F* h_pt3=new TH1F("h_pt3","h_pt3",175,0,3500);
TH1F* h_pt3overavg=new TH1F("h_pt3overavg","h_pt3overavg",30,0,2);

TH1F* h_flav_probeJet=new TH1F("h_flav_probeJet","h_flav_probeJet",50,0,23);
TH1F* h_partonFlav=new TH1F("h_partonFlav","h_partonFlav",50,0,23);

TH1F* h_ptavg=new TH1F("h_ptavg","h_ptavg",175,0,3500);

TH1F* h_pthardestjet_lf=new TH1F("h_pthardestjet_lf","h_pthardestjet_lf",175,0,3500);
TH1F* h_pthardestjet_b=new TH1F("h_pthardestjet_b","h_pthardestjet_b",175,0,3500);
TH1F* h_pthardestjet_c=new TH1F("h_pthardestjet_c","h_pthardestjet_c",175,0,3500);

TH1F* h_pt_lf=new TH1F("h_pt_lf","h_pt_lf",175,0,3500);
TH1F* h_pt_b=new TH1F("h_pt_b","h_pt_b",175,0,3500);
TH1F* h_pt_c=new TH1F("h_pt_c","h_pt_c",175,0,3500);

TH1F* h_pt2_lf=new TH1F("h_pt2_lf","h_pt_lf",175,0,3500);
TH1F* h_pt2_b=new TH1F("h_pt2_b","h_pt_b",175,0,3500);
TH1F* h_pt2_c=new TH1F("h_pt2_c","h_pt_c",175,0,3500);

TH1F* h_NJets_lf=new TH1F("h_NJets_lf","h_NJets_lf",16,-0.5,15.5);
TH1F* h_NJets_b=new TH1F("h_NJets_b","h_NJets_b",16,-0.5,15.5);
TH1F* h_NJets_c=new TH1F("h_NJets_c","h_NJets_c",16,-0.5,15.5);

TH1F* h_CSV_lf=new TH1F("h_CSV_lf","h_CSV_lf",11,-0.2,1);
TH1F* h_CSV_b=new TH1F("h_CSV_b","h_CSV_b",11,-0.2,1);
TH1F* h_CSV_c=new TH1F("h_CSV_c","h_CSV_c",11,-0.2,1);

TH1F* h_CSV_taggedhigh_lf=new TH1F("h_CSV_taggedhigh_lf","h_CSV_taggedhigh_lf",11,-0.2,1);
TH1F* h_CSV_taggedhigh_b=new TH1F("h_CSV_taggedhigh_b","h_CSV_taggedhigh_b",11,-0.2,1);
TH1F* h_CSV_taggedhigh_c=new TH1F("h_CSV_taggedhigh_c","h_CSV_taggedhigh_c",11,-0.2,1);

TH1F* h_CSV_taggedlow_lf=new TH1F("h_CSV_taggedlow_lf","h_CSV_taggedlow_lf",25,-0.1,1);
TH1F* h_CSV_taggedlow_b=new TH1F("h_CSV_taggedlow_b","h_CSV_taggedlow_b",25,-0.1,1);
TH1F* h_CSV_taggedlow_c=new TH1F("h_CSV_taggedlow_c","h_CSV_taggedlow_c",25,-0.1,1);

TH1F* h_CSV_true_taggedhigh_lf=new TH1F("h_CSV_true_taggedhigh_lf","h_true_CSV_taggedhigh_lf",11,-0.1,1);
TH1F* h_CSV_true_taggedhigh_b=new TH1F("h_CSV_true_taggedhigh_b","h_CSV_true_taggedhigh_b",11,-0.2,1);
TH1F* h_CSV_true_taggedhigh_c=new TH1F("h_CSV_true_taggedhigh_c","h_CSV_true_taggedhigh_c",11,-0.2,1);

TH1F* h_CSV_true_taggedlow_lf=new TH1F("h_CSV_true_taggedlow_lf","h_CSV_true_taggedlow_lf",25,-0.1,1);
TH1F* h_CSV_true_taggedlow_b=new TH1F("h_CSV_true_taggedlow_b","h_CSV_true_taggedlow_b",25,-0.1,1);
TH1F* h_CSV_true_taggedlow_c=new TH1F("h_CSV_true_taggedlow_c","h_CSV_true_taggedlow_c",25,-0.1,1);

TH1F* h_SumSVMass_part21_had5=new TH1F("h_SumSVMass_part21_had5","h_SumSVMass_part21_had5",30,0,8);
TH1F* h_SumSVMass_part5_had5=new TH1F("h_SumSVMass_part5_had5","h_SumSVMass_part5_had5",30,0,8);

TH1F* h_NSV_part21_had5=new TH1F("h_NSV_part21_had5","h_NSV_part21_had5",4,0,4);
TH1F* h_NSV_part5_had5=new TH1F("h_NSV_part5_had5","h_NSV_part5_had5",4,0,4);

TH1F* h_tagjet_partflav=new TH1F("h_tagjet_partflav","h_tagjet_partflav",50,0,23);
TH1F* h_tagjet_hadflav=new TH1F("h_tagjet_hadflav","h_tagjet_hadflav",50,0,23);

TH1F* h_tagjet_partflav_wo_SVMassCut=new TH1F("h_tagjet_partflav_wo_SVMassCut","h_tagjet_partflav_wo_SVMassCut",50,0,23);

TH1F* h_CSV_data_lf=new TH1F("h_CSV_data_lf","h_CSV_data_lf",25,-0.1,1);

bool truetag=false;
float dphi;
float pt_avg;
float pt3cut;
long nentries;
float SVMassCut;
float dphicut=2.7;
SVMassCut=2;
pt3cut=0.1;
// loop over all events
nentries = tree_qcd->GetEntries(); 
cout << "total number of MC events: " << nentries << endl;
for (long iEntry=0;iEntry<nentries;iEntry++) {

  if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//   if(iEntry>2000000) break;
  tree_qcd->GetEntry(iEntry);
  if(N_Jets >=2){
    dphi=DeltaPhi;
    h_dphi->Fill(dphi);
    if(N_Jets>=3){
      h_pt3->Fill(Jet_Pt[2]);
      h_pt3overavg->Fill(Jet_Pt[2]/PtAve);
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
      
    if (dphi> dphicut ){	
      if (abs(Jet_Eta[0])<2.1 && abs(Jet_Eta[1])<2.1){
	pt_avg=PtAve;
	h_ptavg->Fill(pt_avg);
	  
	if (abs(Jet_PartFlav[0])==4){
	  h_pthardestjet_c->Fill(Jet_Pt[0]);
	  h_pt2_c->Fill(Jet_Pt[1]);
	}	    
	else if (abs(Jet_PartFlav[0])==5){ 
	  h_pthardestjet_b->Fill(Jet_Pt[0]);
	  h_pt2_b->Fill(Jet_Pt[1]);
	}	  
	else if ( abs(Jet_PartFlav[0])!=5 && abs(Jet_PartFlav[0])!=4){
	  h_pthardestjet_lf->Fill(Jet_Pt[0]);
	  h_pt2_lf->Fill(Jet_Pt[1]);
	}
      
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
	    else if (j==0 && N_Jets ==2){
		  h_tagjet_partflav_wo_SVMassCut->Fill(abs(Jet_PartFlav[0]));
		}
	    else if (j==1 && N_Jets ==2){
		  h_tagjet_partflav_wo_SVMassCut->Fill(abs(Jet_PartFlav[1]));
		}
		
	    if (Jet_SumSVMass[j]<SVMassCut && Jet_NSV[j]==1){
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
		else if (j==0 && N_Jets ==2){
		  h_tagjet_hadflav->Fill(abs(Jet_HadFlav[0]));
		  h_tagjet_partflav->Fill(abs(Jet_PartFlav[0]));
		  if (abs(Jet_PartFlav[1])==4) h_CSV_taggedhigh_c->Fill(Jet_CSV[1]);
		  else if (abs(Jet_PartFlav[1])==5) h_CSV_taggedhigh_b->Fill(Jet_CSV[1]);
		  else if (abs(Jet_PartFlav[1])!=4 && abs(Jet_PartFlav[1])!=5) h_CSV_taggedhigh_lf->Fill(Jet_CSV[1]);
		}
		else if (j==1 && N_Jets ==2){
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
			if (abs(Jet_HadFlav[1])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[1]);
			else if (abs(Jet_HadFlav[1])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[1]);
			else if (abs(Jet_HadFlav[1])!=4 && abs(Jet_HadFlav[1])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[1]);
		      }
		      else if (j==1){
			if (abs(Jet_HadFlav[0])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[0]);
			else if (abs(Jet_HadFlav[0])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[0]);
			else if (abs(Jet_HadFlav[0])!=4 && abs(Jet_HadFlav[0])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[0]);
		      }
		  }
		}
		if (j==0 && N_Jets ==2 ){
		  if (abs(Jet_HadFlav[1])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[1]);
		  else if (abs(Jet_HadFlav[1])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[1]);
		  else if (abs(Jet_HadFlav[1])!=4 && abs(Jet_PartFlav[1])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[1]);
		}
		else if (j==1 && N_Jets ==2){
		  if (abs(Jet_HadFlav[0])==4) h_CSV_taggedlow_c->Fill(Jet_CSV[0]);
		  else if (abs(Jet_HadFlav[0])==5) h_CSV_taggedlow_b->Fill(Jet_CSV[0]);
		  else if (abs(Jet_HadFlav[0])!=4 && abs(Jet_PartFlav[0])!=5) h_CSV_taggedlow_lf->Fill(Jet_CSV[0]);
		}
	  }
	  //true tagging
	  if (truetag==true){
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
    }
//   cout << iEntry;
  }
// end of event loop
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

h_pt2_lf->SetFillColor(kGreen);
h_pt2_b->SetFillColor(kRed);
h_pt2_c->SetFillColor(kBlue);

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
THStack* stack_pt2ndhardestjet=new THStack();
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

stack_pt2ndhardestjet->Add(h_pt2_b);
stack_pt2ndhardestjet->Add(h_pt2_c);
stack_pt2ndhardestjet->Add(h_pt2_lf);

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
h_ptavg->GetXaxis()->SetTitle("Pt avg (MC)");
h_ptavg->Write();
c1->SaveAs("ptavg_mc.png");

stack_pt2ndhardestjet->Draw("hist");
stack_pt2ndhardestjet->GetXaxis()->SetTitle("Pt of 2nd hardest Jet");
stack_pt2ndhardestjet->Write();
c1->SaveAs("pt_2ndhardestjet.png");

stack_pthardestjet->Draw("hist");
stack_pthardestjet->GetXaxis()->SetTitle("Pt of hardest Jet");
stack_pthardestjet->Write();
c1->SaveAs("pt_hardestjet.png");
cout<< "hardest Jet: " << endl;
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
// tree_qcd->~TChain();

//data selection
TChain* tree_data = new TChain("MVATree");

tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_0.root");
tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_1.root");
tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_2.root");
tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_3.root");
tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_4.root");
tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_5.root");
tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_6.root");
tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_7.root");
tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_8.root");
tree_data->AddFile("/nfs/dust/cms/user/matsch/ttHNtuples/Run2015/v2/JetHT_Run2015D-PromptReco-v4_9.root");

float* Jet_CSV_data = new float[120];
tree_data->SetBranchAddress("Jet_CSV",Jet_CSV_data);
float* Jet_Pt_data = new float[120];
tree_data->SetBranchAddress("Jet_Pt",Jet_Pt_data);
float dphidata;
tree_data->SetBranchAddress("DeltaPhi",&dphidata);
float pt_avg_data;
tree_data->SetBranchAddress("PtAve",&pt_avg_data);
int N_Jets_data;
tree_data->SetBranchAddress("N_Jets",&N_Jets_data);
float* Jet_Eta_data = new float[120];
tree_data->SetBranchAddress("Jet_Eta",Jet_Eta_data); 


float nentries_data = tree_data->GetEntries(); 
cout << "total number of data events: " << nentries_data << endl;
for (long iEntry=0;iEntry<nentries_data;iEntry++) {
  if(iEntry%100000==0) cout << "analyzing event " << iEntry << endl;
//   if(iEntry>2000000) break;
  tree_data->GetEntry(iEntry);
  if (dphidata > dphicut){
    if (abs(Jet_Eta_data[0])<2.1 && abs(Jet_Eta_data[1])<2.1){
      for(int j=0;j<2;j++){      
	    //LF tagging
	if (Jet_CSV_data[j]<0.605){      
	  if (N_Jets_data >=3 ){
	      if (Jet_Pt_data[2]/pt_avg_data < pt3cut){
		if (j==0){h_CSV_data_lf->Fill(Jet_CSV_data[1]);}
		else if (j==1){h_CSV_data_lf->Fill(Jet_CSV_data[0]);}
	      }
	    }
	  if (j==0 && N_Jets_data == 2){
	    h_CSV_data_lf->Fill(Jet_CSV_data[1]);
	  }
	  if (j==1 && N_Jets_data == 2){
	    h_CSV_data_lf->Fill(Jet_CSV_data[0]);
	  }        
	}
      }
    }
  }
}


h_CSV_data_lf->Write();

// plot and define CSV ratio plot
float dataevents_lf=h_CSV_data_lf->Integral();
cout << dataevents_lf  << " events in data  selected" << endl;
float xmin=-0.2;
float xmax=1;
// float nbins=11;
TLine* line=new TLine(xmin,1,xmax,1);
line->SetLineColor(kBlack);
char text_cms[]="CMS private Work";
char cutlabel[]="Dijet selection";
TLatex* text=new TLatex();
text-> SetNDC();
text-> SetTextFont(42);
text-> SetTextSize(0.05);

//LF
char xtitle_lf[]="CSV probe Jet (LF)";
//makelegend
TLegend* leg_lf=new TLegend(0.75,0.4,0.9,0.8);
leg_lf->AddEntry(h_CSV_data_lf,"data");
leg_lf->AddEntry(h_CSV_taggedlow_b,"b");
leg_lf->AddEntry(h_CSV_taggedlow_c,"c");
leg_lf->AddEntry(h_CSV_taggedlow_lf,"lf");
leg_lf->SetFillStyle(0);
leg_lf->SetBorderSize(0);

c1->cd();
//makepadhist
TPad* padhist_lf=new TPad("padhist_lf","padhist_lf",0,0.3,1,1);
padhist_lf->SetBottomMargin(0);
padhist_lf->Draw();
padhist_lf->cd();

//normalize to data event yield
TH1F* mc=(TH1F*)stack_CSVtaggedlow->GetStack()->Last();  
float mcevents_lf=mc->Integral();
cout << "mcevents before normalization: " << mcevents_lf << endl;
float normratio_lf;
if (mcevents_lf!=0) normratio_lf=dataevents_lf/mcevents_lf;
  else normratio_lf=1;
h_CSV_taggedlow_b->Scale(normratio_lf);
h_CSV_taggedlow_c->Scale(normratio_lf);
h_CSV_taggedlow_lf->Scale(normratio_lf);
THStack* mc_stack_lf_normalized=new THStack();
mc_stack_lf_normalized->Add(h_CSV_taggedlow_b);
mc_stack_lf_normalized->Add(h_CSV_taggedlow_c);
mc_stack_lf_normalized->Add(h_CSV_taggedlow_lf);
TH1F* mc_norm=(TH1F*)mc_stack_lf_normalized->GetStack()->Last();
cout << "mcevents after normalization: " << mc_norm->Integral() << endl;

//draw histos
// h_CSV_data_lf->Sumw2();
mc_stack_lf_normalized->Draw("hist");
h_CSV_data_lf->SetMarkerStyle(20);
h_CSV_data_lf->Draw("SAMEE0");
leg_lf->Draw();
text->DrawLatex(0.175, 0.863, text_cms);
text->DrawLatex(0.175, 0.815, cutlabel);
c1->cd();
//makepadratio
TPad* padratio_lf=new TPad("padratio_lf","padratio_lf",0,0,1,0.3);
padratio_lf->SetTopMargin(0);
padratio_lf->SetBottomMargin(1.1);
padratio_lf->Draw();
padratio_lf->cd();

//makeratio    
TH1F* ratio_lf=(TH1F*)h_CSV_data_lf->Clone(); 
ratio_lf->SetTitle("");
ratio_lf->SetXTitle(xtitle_lf);
ratio_lf->Sumw2();
ratio_lf->SetStats(0);
ratio_lf->Divide(mc_norm);
ratio_lf->SetMarkerStyle(20);
ratio_lf->Draw("SAMEE0");
ratio_lf->SetMaximum(1.6);
ratio_lf->SetMinimum(0.4);
//set_ratioattributes//   
ratio_lf->GetYaxis()->SetNdivisions(510);
ratio_lf->GetYaxis()->SetLabelSize(0.1);
ratio_lf->GetXaxis()->SetTitle(xtitle_lf);
ratio_lf->GetXaxis()->SetTitleSize(0.11);
ratio_lf->GetXaxis()->SetNdivisions(510);
ratio_lf->GetXaxis()->SetLabelSize(0.1);

line->Draw();
c1->SaveAs("CSV_ratio_lf.png");
c1->Write(); 

c1->cd();
//subtract HF contamination
TH1F* diff_lf=(TH1F*)h_CSV_data_lf->Clone();
diff_lf->SetTitle("Data-b");
diff_lf->Add(h_CSV_taggedlow_b,-1);
diff_lf->Draw("E0");
diff_lf->SetLineColor(kBlue);
diff_lf->Write();

TH1F* nonb_lf=(TH1F*)h_CSV_data_lf->Clone();
nonb_lf->Add(h_CSV_taggedlow_c);
nonb_lf->Draw("SAMEE0");
nonb_lf->SetMarkerStyle(20);
nonb_lf->SetMarkerSize(0.7);
nonb_lf->SetLineColor(kRed);
nonb_lf->Write();
c1->BuildLegend(0.2,0.8,0.7,0.9);
c1->SaveAs("diff_lf.png");

//calculate LFSF
TH1F* lfsf=(TH1F*)diff_lf->Clone();
lfsf->Divide(nonb_lf);
//fit with 5th order polnomial
// gStyle->SetOptFit(000000000);
// gStyle->SetOptStat(000000000);
lfsf->Fit("pol6","LF","",0,1);
lfsf->Draw("E0");
lfsf->GetYaxis()->SetLabelSize(0.04);
lfsf->GetXaxis()->SetTitle("LFSF");
lfsf->GetXaxis()->SetTitleSize(0.04);
lfsf->GetXaxis()->SetNdivisions(510);
lfsf->GetXaxis()->SetLabelSize(0.04);
line->Draw();
lfsf->Write();
lfsf->GetXaxis()->SetTitle("LFSF");
c1->SaveAs("LFSF.png");


outfile->Close();


}

  int main(){
    qcd_dijet();    
  }
