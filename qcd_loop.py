from ROOT import *
import math
#f_qcd=TFile("/storage/8/tpfotzer/BEANTrees/2015B_newGT/MC_QCD_MuEnriched_Tree.root")
f_qcd=TFile("/nfs/dust/cms/user/matsch/ttHNtuples/Spring15/DiJets_QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8.root")
f_histos=TFile("histos.root","RECREATE")
pt3cut=0.05

h_dphi=TH1F("h_dphi","h_dphi",45,0,3.5)
h_pt3=TH1F("h_pt3","h_pt3",80,0,350)
h_pt3overavg=TH1F("h_pt3overavg","h_pt3overavg",20,0,2)

h_flav_probeJet=TH1F("h_flav_probeJet","h_flav_probeJet",50,0,23)

h_ptavg=TH1F("h_ptavg","h_ptavg",80,0,500)

h_pthardestjet_lf=TH1F("h_pthardestjet_lf","h_pthardestjet_lf",80,0,500)
h_pthardestjet_b=TH1F("h_pthardestjet_b","h_pthardestjet_b",80,0,500)
h_pthardestjet_c=TH1F("h_pthardestjet_c","h_pthardestjet_c",80,0,500)

h_pt_lf=TH1F("h_pt_lf","h_pt_lf",80,0,500)
h_pt_b=TH1F("h_pt_b","h_pt_b",80,0,500)
h_pt_c=TH1F("h_pt_c","h_pt_c",80,0,500)

h_NJets_lf=TH1F("h_NJets_lf","h_NJets_lf",16,-0.5,15.5)
h_NJets_b=TH1F("h_NJets_b","h_NJets_b",16,-0.5,15.5)
h_NJets_c=TH1F("h_NJets_c","h_NJets_c",16,-0.5,15.5)

h_CSV_lf=TH1F("h_CSV_lf","h_NCSV_lf",11,-0.2,1)
h_CSV_b=TH1F("h_CSV_b","h_NCSV_b",11,-0.2,1)
h_CSV_c=TH1F("h_CSV_c","h_NCSVM_c",11,-0.2,1)

h_CSV_taggedhigh_lf=TH1F("h_CSV_taggedhigh_lf","h_CSV_taggedhigh_lf",11,-0.2,1)
h_CSV_taggedhigh_b=TH1F("h_CSV_taggedhigh_b","h_CSV_taggedhigh_b",11,-0.2,1)
h_CSV_taggedhigh_c=TH1F("h_CSV_taggedhigh_c","h_CSV_taggedhigh_c",11,-0.2,1)

h_CSV_taggedlow_lf=TH1F("h_CSV_taggedlow_lf","h_CSV_taggedlow_lf",11,-0.2,1)
h_CSV_taggedlow_b=TH1F("h_CSV_taggedlow_b","h_CSV_taggedlow_b",11,-0.2,1)
h_CSV_taggedlow_c=TH1F("h_CSV_taggedlow_c","h_CSV_taggedlow_c",11,-0.2,1)

h_CSV_true_taggedhigh_lf=TH1F("h_CSV_true_taggedhigh_lf","h_true_CSV_taggedhigh_lf",11,-0.2,1)
h_CSV_true_taggedhigh_b=TH1F("h_CSV_true_taggedhigh_b","h_CSV_true_taggedhigh_b",11,-0.2,1)
h_CSV_true_taggedhigh_c=TH1F("h_CSV_true_taggedhigh_c","h_CSV_true_taggedhigh_c",11,-0.2,1)

h_CSV_true_taggedlow_lf=TH1F("h_CSV_true_taggedlow_lf","h_CSV_true_taggedlow_lf",11,-0.2,1)
h_CSV_true_taggedlow_b=TH1F("h_CSV_true_taggedlow_b","h_CSV_true_taggedlow_b",11,-0.2,1)
h_CSV_true_taggedlow_c=TH1F("h_CSV_true_taggedlow_c","h_CSV_true_taggedlow_c",11,-0.2,1)

tree_qcd=f_qcd.Get("MVATree")
n=tree_qcd.GetEntries()

print n, " Events to Analyse"
for i in xrange(n):
  if i%10000==0: print "analyzing event Nr. ", i
  #if i >20000: break
  tree_qcd.GetEntry(i)  
  
  if tree_qcd.N_Jets >=2:
    dphi=tree_qcd.DeltaPhi
    h_dphi.Fill(dphi)
    pt_avg=tree_qcd.PtAve
    h_ptavg.Fill(pt_avg)
    if tree_qcd.N_Jets>=3:
      h_pt3.Fill(tree_qcd.Jet_Pt[2])
      h_pt3overavg.Fill(tree_qcd.Jet_Pt[2]/pt_avg)
    
    
    
    for j in xrange(tree_qcd.N_Jets):
      if abs(tree_qcd.Jet_Flav[j])==4:  
	h_NJets_c.Fill(tree_qcd.N_Jets)
	h_CSV_c.Fill(tree_qcd.Jet_CSV[j])	
	    
      elif abs(tree_qcd.Jet_Flav[j])==5: 
	h_NJets_b.Fill(tree_qcd.N_Jets)
	h_CSV_b.Fill(tree_qcd.Jet_CSV[j])
	    
      elif abs(tree_qcd.Jet_Flav[j])!=5 and abs(tree_qcd.Jet_Flav[j])!=4:
	h_NJets_lf.Fill(tree_qcd.N_Jets)
	h_CSV_lf.Fill(tree_qcd.Jet_CSV[j])
 
      
    if dphi> 2.7:
      
      if abs(tree_qcd.Jet_Eta[0])<2.1 and abs(tree_qcd.Jet_Eta[1])<2.1 :
	  
	if abs(tree_qcd.Jet_Flav[0])==4:
	      h_pthardestjet_c.Fill(tree_qcd.Jet_Pt[0])	    
	elif abs(tree_qcd.Jet_Flav[0])==5: 
	      h_pthardestjet_b.Fill(tree_qcd.Jet_Pt[0])	  
	elif abs(tree_qcd.Jet_Flav[0])!=5 and abs(tree_qcd.Jet_Flav[0])!=4:
	      h_pthardestjet_lf.Fill(tree_qcd.Jet_Pt[0])
	#pt_avg=tree_qcd.PtAve
      #csv tagging
      for j in xrange(2):	    
	if abs(tree_qcd.Jet_Flav[j])==4:h_pt_c.Fill(tree_qcd.Jet_Pt[j])
	elif abs(tree_qcd.Jet_Flav[j])==5:h_pt_b.Fill(tree_qcd.Jet_Pt[j])
	elif abs(tree_qcd.Jet_Flav[j])!=5 and abs(tree_qcd.Jet_Flav[j])!=4:h_pt_lf.Fill(tree_qcd.Jet_Pt[j])
	if tree_qcd.Jet_CSV[j]>0.97:	      
	      if tree_qcd.N_Jets >=3:
		if tree_qcd.Jet_Pt[2]/pt_avg < pt3cut:
		    if j==0:
		      if abs(tree_qcd.Jet_Flav[1])==4: h_CSV_taggedhigh_c.Fill(tree_qcd.Jet_CSV[1])
		      elif abs(tree_qcd.Jet_Flav[1])==5: h_CSV_taggedhigh_b.Fill(tree_qcd.Jet_CSV[1])
		      elif abs(tree_qcd.Jet_Flav[1])!=4 and abs(tree_qcd.Jet_Flav[1])!=5: h_CSV_taggedhigh_lf.Fill(tree_qcd.Jet_CSV[1])
		    elif j==1:
		      if abs(tree_qcd.Jet_Flav[0])==4: h_CSV_taggedhigh_c.Fill(tree_qcd.Jet_CSV[0])
		      elif abs(tree_qcd.Jet_Flav[0])==5: h_CSV_taggedhigh_b.Fill(tree_qcd.Jet_CSV[0])
		      elif abs(tree_qcd.Jet_Flav[0])!=4 and abs(tree_qcd.Jet_Flav[0])!=5: h_CSV_taggedhigh_lf.Fill(tree_qcd.Jet_CSV[0])
	      elif j==0:
		if abs(tree_qcd.Jet_Flav[1])==4: h_CSV_taggedhigh_c.Fill(tree_qcd.Jet_CSV[1])
		elif abs(tree_qcd.Jet_Flav[1])==5: h_CSV_taggedhigh_b.Fill(tree_qcd.Jet_CSV[1])
		elif abs(tree_qcd.Jet_Flav[1])!=4 and abs(tree_qcd.Jet_Flav[1])!=5: h_CSV_taggedhigh_lf.Fill(tree_qcd.Jet_CSV[1])
	      elif j==1:
		if abs(tree_qcd.Jet_Flav[0])==4: h_CSV_taggedhigh_c.Fill(tree_qcd.Jet_CSV[0])
		elif abs(tree_qcd.Jet_Flav[0])==5: h_CSV_taggedhigh_b.Fill(tree_qcd.Jet_CSV[0])
		elif abs(tree_qcd.Jet_Flav[0])!=4 and abs(tree_qcd.Jet_Flav[0])!=5: h_CSV_taggedhigh_lf.Fill(tree_qcd.Jet_CSV[0])
		
	if tree_qcd.Jet_CSV[j]<0.605:		      
	      if tree_qcd.N_Jets >=3:
		if tree_qcd.Jet_Pt[2]/pt_avg < pt3cut:
		    if j==0:
		      if abs(tree_qcd.Jet_Flav[1])==4: h_CSV_taggedlow_c.Fill(tree_qcd.Jet_CSV[1])
		      elif abs(tree_qcd.Jet_Flav[1])==5: h_CSV_taggedlow_b.Fill(tree_qcd.Jet_CSV[1])
		      elif abs(tree_qcd.Jet_Flav[1])!=4 and abs(tree_qcd.Jet_Flav[1])!=5: h_CSV_taggedlow_lf.Fill(tree_qcd.Jet_CSV[1])
		    elif j==1:
		      if abs(tree_qcd.Jet_Flav[0])==4: h_CSV_taggedlow_c.Fill(tree_qcd.Jet_CSV[0])
		      elif abs(tree_qcd.Jet_Flav[0])==5: h_CSV_taggedlow_b.Fill(tree_qcd.Jet_CSV[0])
		      elif abs(tree_qcd.Jet_Flav[0])!=4 and abs(tree_qcd.Jet_Flav[0])!=5: h_CSV_taggedlow_lf.Fill(tree_qcd.Jet_CSV[0])
	      elif j==0:
		if abs(tree_qcd.Jet_Flav[1])==4: h_CSV_taggedlow_c.Fill(tree_qcd.Jet_CSV[1])
		elif abs(tree_qcd.Jet_Flav[1])==5: h_CSV_taggedlow_b.Fill(tree_qcd.Jet_CSV[1])
		elif abs(tree_qcd.Jet_Flav[1])!=4 and abs(tree_qcd.Jet_Flav[1])!=5: h_CSV_taggedlow_lf.Fill(tree_qcd.Jet_CSV[1])
	      elif j==1:
		if abs(tree_qcd.Jet_Flav[0])==4: h_CSV_taggedlow_c.Fill(tree_qcd.Jet_CSV[0])
		elif abs(tree_qcd.Jet_Flav[0])==5: h_CSV_taggedlow_b.Fill(tree_qcd.Jet_CSV[0])
		elif abs(tree_qcd.Jet_Flav[0])!=4 and abs(tree_qcd.Jet_Flav[0])!=5: h_CSV_taggedlow_lf.Fill(tree_qcd.Jet_CSV[0])
	#True tagging	
	if abs(tree_qcd.Jet_Flav[j])==5:	      
	      if tree_qcd.N_Jets >=3:
		if tree_qcd.Jet_Pt[2]/pt_avg < pt3cut:
		    if j==0:
		      h_flav_probeJet.Fill(abs(tree_qcd.Jet_Flav[1]))
		      if abs(tree_qcd.Jet_Flav[1])==4: h_CSV_true_taggedhigh_c.Fill(tree_qcd.Jet_CSV[1])
		      elif abs(tree_qcd.Jet_Flav[1])==5: h_CSV_true_taggedhigh_b.Fill(tree_qcd.Jet_CSV[1])
		      elif abs(tree_qcd.Jet_Flav[1])!=4 and abs(tree_qcd.Jet_Flav[1])!=5: h_CSV_true_taggedhigh_lf.Fill(tree_qcd.Jet_CSV[1])
		    elif j==1:
		      h_flav_probeJet.Fill(abs(tree_qcd.Jet_Flav[0]))
		      if abs(tree_qcd.Jet_Flav[0])==4: h_CSV_true_taggedhigh_c.Fill(tree_qcd.Jet_CSV[0])
		      elif abs(tree_qcd.Jet_Flav[0])==5: h_CSV_true_taggedhigh_b.Fill(tree_qcd.Jet_CSV[0])
		      elif abs(tree_qcd.Jet_Flav[0])!=4 and abs(tree_qcd.Jet_Flav[0])!=5: h_CSV_true_taggedhigh_lf.Fill(tree_qcd.Jet_CSV[0])
	      elif j==0:
		h_flav_probeJet.Fill(abs(tree_qcd.Jet_Flav[1]))
		if abs(tree_qcd.Jet_Flav[1])==4: h_CSV_true_taggedhigh_c.Fill(tree_qcd.Jet_CSV[1])
		elif abs(tree_qcd.Jet_Flav[1])==5: h_CSV_true_taggedhigh_b.Fill(tree_qcd.Jet_CSV[1])
		elif abs(tree_qcd.Jet_Flav[1])!=4 and abs(tree_qcd.Jet_Flav[1])!=5: h_CSV_true_taggedhigh_lf.Fill(tree_qcd.Jet_CSV[1])
	      elif j==1:
		h_flav_probeJet.Fill(abs(tree_qcd.Jet_Flav[0]))
		if abs(tree_qcd.Jet_Flav[0])==4: h_CSV_true_taggedhigh_c.Fill(tree_qcd.Jet_CSV[0])
		elif abs(tree_qcd.Jet_Flav[0])==5: h_CSV_true_taggedhigh_b.Fill(tree_qcd.Jet_CSV[0])
		elif abs(tree_qcd.Jet_Flav[0])!=4 and abs(tree_qcd.Jet_Flav[0])!=5: h_CSV_true_taggedhigh_lf.Fill(tree_qcd.Jet_CSV[0])
		
	if abs(tree_qcd.Jet_Flav[j])!=5:		      
	      if tree_qcd.N_Jets >=3:
		if tree_qcd.Jet_Pt[2]/pt_avg < pt3cut:
		    if j==0:
		      if abs(tree_qcd.Jet_Flav[1])==4: h_CSV_true_taggedlow_c.Fill(tree_qcd.Jet_CSV[1])
		      elif abs(tree_qcd.Jet_Flav[1])==5: h_CSV_true_taggedlow_b.Fill(tree_qcd.Jet_CSV[1])
		      elif abs(tree_qcd.Jet_Flav[1])!=4 and abs(tree_qcd.Jet_Flav[1])!=5: h_CSV_true_taggedlow_lf.Fill(tree_qcd.Jet_CSV[1])
		    elif j==1:
		      if abs(tree_qcd.Jet_Flav[0])==4: h_CSV_true_taggedlow_c.Fill(tree_qcd.Jet_CSV[0])
		      elif abs(tree_qcd.Jet_Flav[0])==5: h_CSV_true_taggedlow_b.Fill(tree_qcd.Jet_CSV[0])
		      elif abs(tree_qcd.Jet_Flav[0])!=4 and abs(tree_qcd.Jet_Flav[0])!=5: h_CSV_true_taggedlow_lf.Fill(tree_qcd.Jet_CSV[0])
	      elif j==0:
		if abs(tree_qcd.Jet_Flav[1])==4: h_CSV_true_taggedlow_c.Fill(tree_qcd.Jet_CSV[1])
		elif abs(tree_qcd.Jet_Flav[1])==5: h_CSV_true_taggedlow_b.Fill(tree_qcd.Jet_CSV[1])
		elif abs(tree_qcd.Jet_Flav[1])!=4 and abs(tree_qcd.Jet_Flav[1])!=5: h_CSV_true_taggedlow_lf.Fill(tree_qcd.Jet_CSV[1])
	      elif j==1:
		if abs(tree_qcd.Jet_Flav[0])==4: h_CSV_true_taggedlow_c.Fill(tree_qcd.Jet_CSV[0])
		elif abs(tree_qcd.Jet_Flav[0])==5: h_CSV_true_taggedlow_b.Fill(tree_qcd.Jet_CSV[0])
		elif abs(tree_qcd.Jet_Flav[0])!=4 and abs(tree_qcd.Jet_Flav[0])!=5: h_CSV_true_taggedlow_lf.Fill(tree_qcd.Jet_CSV[0])
		
		
 
    
	    

      

h_NJets_lf.SetFillColor(kGreen)
h_NJets_b.SetFillColor(kRed)
h_NJets_c.SetFillColor(kBlue)

h_CSV_lf.SetFillColor(kGreen)
h_CSV_b.SetFillColor(kRed)
h_CSV_c.SetFillColor(kBlue)

h_CSV_taggedhigh_lf.SetFillColor(kGreen)
h_CSV_taggedhigh_b.SetFillColor(kRed)
h_CSV_taggedhigh_c.SetFillColor(kBlue)

h_CSV_taggedlow_lf.SetFillColor(kGreen)
h_CSV_taggedlow_b.SetFillColor(kRed)
h_CSV_taggedlow_c.SetFillColor(kBlue)

h_CSV_true_taggedhigh_lf.SetFillColor(kGreen)
h_CSV_true_taggedhigh_b.SetFillColor(kRed)
h_CSV_true_taggedhigh_c.SetFillColor(kBlue)

h_CSV_true_taggedlow_lf.SetFillColor(kGreen)
h_CSV_true_taggedlow_b.SetFillColor(kRed)
h_CSV_true_taggedlow_c.SetFillColor(kBlue)

h_pt_lf.SetFillColor(kGreen)
h_pt_b.SetFillColor(kRed)
h_pt_c.SetFillColor(kBlue)

h_pthardestjet_lf.SetFillColor(kGreen)
h_pthardestjet_b.SetFillColor(kRed)
h_pthardestjet_c.SetFillColor(kBlue)


stack_NJets=THStack()
stack_NBTagsM=THStack()
stack_CSV=THStack()
stack_CSVtagged=THStack()
stack_Jet_Pt=THStack()
stack_CSVtaggedlow=THStack()
stack_CSVtaggedhigh=THStack()
stack_pthardestjet=THStack()
stack_true_CSVtaggedlow=THStack()
stack_true_CSVtaggedhigh=THStack()


stack_NJets.Add(h_NJets_b)
stack_NJets.Add(h_NJets_c)
stack_NJets.Add(h_NJets_lf)

stack_CSV.Add(h_CSV_b)
stack_CSV.Add(h_CSV_c)
stack_CSV.Add(h_CSV_lf)

stack_CSVtaggedhigh.Add(h_CSV_taggedhigh_b)
stack_CSVtaggedhigh.Add(h_CSV_taggedhigh_c)
stack_CSVtaggedhigh.Add(h_CSV_taggedhigh_lf)

stack_CSVtaggedlow.Add(h_CSV_taggedlow_b)
stack_CSVtaggedlow.Add(h_CSV_taggedlow_c)
stack_CSVtaggedlow.Add(h_CSV_taggedlow_lf)

stack_Jet_Pt.Add(h_pt_b)
stack_Jet_Pt.Add(h_pt_c)
stack_Jet_Pt.Add(h_pt_lf)

stack_pthardestjet.Add(h_pthardestjet_b)
stack_pthardestjet.Add(h_pthardestjet_c)
stack_pthardestjet.Add(h_pthardestjet_lf)

stack_true_CSVtaggedhigh.Add(h_CSV_true_taggedhigh_b)
stack_true_CSVtaggedhigh.Add(h_CSV_true_taggedhigh_c)
stack_true_CSVtaggedhigh.Add(h_CSV_true_taggedhigh_lf)

stack_true_CSVtaggedlow.Add(h_CSV_true_taggedlow_b)
stack_true_CSVtaggedlow.Add(h_CSV_true_taggedlow_c)
stack_true_CSVtaggedlow.Add(h_CSV_true_taggedlow_lf)

c1=TCanvas()
c2=TCanvas()
c3=TCanvas()
c4=TCanvas()
c5=TCanvas()
c6=TCanvas()
c7=TCanvas()
c8=TCanvas()
c9=TCanvas()
c10=TCanvas()
c11=TCanvas()
c12=TCanvas()
c13=TCanvas()


c1.cd()
stack_CSV.Draw()
stack_CSV.GetXaxis().SetTitle("CSV of all Jets (>=2 jets, w/o dphi and PtAvg cut) ")
stack_CSV.Write()
c1.SaveAs("CSV_alljets.png")

c2.cd()
h_dphi.Draw()
h_dphi.GetXaxis().SetTitle("d_phi of 2 hardest Jets (>=2 jets)")
h_dphi.Write()
c2.SaveAs("d_phi.png")

c3.cd()
stack_NJets.Draw()
stack_NJets.GetXaxis().SetTitle("N Jets (w/o dphi and PtAvg cut)")
stack_NJets.Write()
c3.SaveAs("N_Jets.png")

c4.cd()
stack_CSVtaggedhigh.Draw()
stack_CSVtaggedhigh.GetXaxis().SetTitle("CSV probe Jet (HF)")
stack_CSVtaggedhigh.Write()
c4.SaveAs("CSV_probejet_HF.png")

c5.cd()
stack_CSVtaggedlow.Draw()
stack_CSVtaggedlow.GetXaxis().SetTitle("CSV probe Jet (LF)")
stack_CSVtaggedlow.Write()
c5.SaveAs("CSV_probejet_LF.png")

c6.cd()
h_pt3.Draw()
h_pt3.GetXaxis().SetTitle("Jet_Pt[2]")
h_pt3.Write()
c6.SaveAs("Jet_Pt2.png")

c7.cd()
h_pt3overavg.Draw()
h_pt3overavg.GetXaxis().SetTitle("pt3 over pt_avg")
h_pt3overavg.Write()
c7.SaveAs("pt3overavg.png")

c8.cd()
stack_Jet_Pt.Draw()
stack_Jet_Pt.GetXaxis().SetTitle("Pt two hardest Jets")
stack_Jet_Pt.Write()
c8.SaveAs("pt_2hardestjets.png")

c9.cd()
h_ptavg.Draw()
h_ptavg.GetXaxis().SetTitle("Pt avg (>=2 jets)")
h_ptavg.Write()
c9.SaveAs("ptavg.png")

c10.cd()
stack_pthardestjet.Draw()
stack_pthardestjet.GetXaxis().SetTitle("Pt of hardest Jet")
stack_pthardestjet.Write()
c10.SaveAs("pt_hardestjet.png")
print "b: ", h_pthardestjet_b.Integral()
print "lf: ", h_pthardestjet_lf.Integral()
print "c: ", h_pthardestjet_c.Integral()

c11.cd()
stack_true_CSVtaggedhigh.Draw()
stack_true_CSVtaggedhigh.GetXaxis().SetTitle("CSV probe Jet (HF, truth tagged)")
stack_true_CSVtaggedhigh.Write()
c11.SaveAs("CSV_probejet_HF_truthtagged.png")

c12.cd()
stack_true_CSVtaggedlow.Draw()
stack_true_CSVtaggedlow.GetXaxis().SetTitle("CSV probe Jet (LF, truth tagged)")
stack_true_CSVtaggedlow.Write()
c12.SaveAs("CSV_probejet_LF_truthtagged.png")

c13.cd()
h_flav_probeJet.Draw()
h_flav_probeJet.GetXaxis().SetTitle("Flav of probe Jet (HF, truth tagged)")
h_flav_probeJet.Write()
c13.SaveAs("flav_probejet.png")


raw_input("Press a Key...")

f_histos.Close()



