from ROOT import *
from myplotscript import plot

from ROOT import *

def def_backhistos(trees_back,nbins,xmin,xmax,backnames,color):
  backhistos=[0]*len(trees_back)
  rnd=TRandom()
  rnd.SetSeed(0)
  for i in xrange(len(trees_back)):  
    backhistos[i]=TH1F("h_back_"+backnames[i]+str(rnd.Rndm()+i),"h_back"+backnames[i],nbins,xmin,xmax)
    backhistos[i].SetFillColor(color[i])
  return backhistos

def def_datahisto(tree_data,nbins,xmin,xmax):
  rnd=TRandom()
  rnd.SetSeed(0)
  datahist=TH1F("datahist"+str(rnd.Rndm()),"datahist",nbins,xmin,xmax)
  datahist.SetMarkerStyle(20)
  datahist.SetMarkerSize(0.7)
  return datahist

def project_back(varname,trees_back,backhistos,mccut,backnames):
  for i in xrange(len(backhistos)):
    trees_back[i].Project(backhistos[i].GetName(),varname,mccut)
    
    
def project_data(varname,tree_data,datahist,datacut):
  tree_data.Project(datahist.GetName(),varname,datacut)
  
def makestack(backhistos,norm):
  stack=THStack()
  if norm==True:
    tmpstack=THStack()
    for i in xrange(len(backhistos)):
      tmpstack.Add(backhistos[i],"hist")
    back=tmpstack.GetStack().Last()
    stackintegral=back.Integral()
  for i in xrange(len(backhistos)):
    #backhistos[i].Sumw2()
    if norm==True and stackintegral !=0:
      backhistos[i].Scale(1/stackintegral)
    print backhistos[i].GetTitle() ,"  ", backhistos[i].Integral()
    stack.Add(backhistos[i],"hist")  
  return stack  
  
def set_stackattributes(stack,ymin,log,norm=False):
  if norm==False:
    stack.SetMinimum(ymin)
  else: stack.SetMinimum(0)
  if log:
    stack.SetMaximum(1.5*stack.GetMaximum())  
  else: stack.SetMaximum(1.2*stack.GetMaximum())
  stack.GetXaxis().SetNdivisions(0)
  stack.GetYaxis().SetTitle("Events")

def makeleg(backhistos,datahist,backnames):
  leg=TLegend(0.75,0.4,0.9,0.8)
  leg.AddEntry(datahist,"data")
  for i in xrange(len(backhistos)):
    leg.AddEntry(backhistos[i],backnames[i],"f")
  leg.SetFillStyle(0)
  leg.SetBorderSize(0)
  return leg

def makeratio(stack,datahist,xtitle):
  back=stack.GetStack().Last()
  ratio=datahist.Clone()
  ratio.SetTitle("")
  ratio.SetXTitle(xtitle)
  ratio.Sumw2()
  ratio.SetStats(0)
  ratio.Divide(back)
  ratio.SetMarkerStyle(20)
  SetOwnership(ratio,0)
  ratio.Draw("E0")
  ratio.SetMaximum(1.6)
  ratio.SetMinimum(0.4)
  return ratio
  
def set_ratioattributes(ratio,xmin,xmax,nbins,xtitle):
  ratio.GetYaxis().SetNdivisions(510)
  ratio.GetYaxis().SetLabelSize(0.1)
  
  ratio.GetXaxis().SetTitle(xtitle)
  ratio.GetXaxis().SetTitleSize(0.11)
  if nbins<15:
    ratio.GetXaxis().SetNdivisions(nbins,0,0)
  else: ratio.GetXaxis().SetNdivisions(nbins/2,0,0)
  ratio.GetXaxis().SetLabelSize(0.1)

def makepadhist(log,norm):
  padhist=TPad("pad_hist","pad_hist",0,0.3,1,1)
  SetOwnership(padhist,0)
  padhist.SetBottomMargin(0)
  padhist.Draw()
  padhist.cd()
  if log==True and norm==False :
    padhist.SetLogy() 
  
def makepadratio():
  pad_ratio=TPad("pad_ratio","pad_ratio",0,0,1,0.3)
  SetOwnership(pad_ratio,0)
  pad_ratio.SetTopMargin(0)
  pad_ratio.SetBottomMargin(0.3)
  pad_ratio.Draw()
  pad_ratio.cd()

def plot(varname,trees_back,tree_data,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log,norm=False):
  backhistos=def_backhistos(trees_back,nbins,xmin,xmax,backnames,color)
  datahist=def_datahisto(tree_data,nbins,xmin,xmax)
  datahist.Sumw2()
  project_back(varname,trees_back,backhistos,mccut,backnames)
  project_data(varname,tree_data,datahist,datacut)
  
  
  stack=makestack(backhistos,norm)  
  leg=makeleg(backhistos,datahist,backnames)
  line=TLine(xmin,1,xmax,1)
  line.SetLineColor(kBlack)
  
  
  back=stack.GetStack().Last()
  #background underflow
  back.SetBinContent(1,back.GetBinContent(0)+back.GetBinContent(1))
  #data underflow
  datahist.SetBinContent(1,datahist.GetBinContent(0)+datahist.GetBinContent(1))
  #background overflow
  back.SetBinContent(back.GetNbinsX(),back.GetBinContent(back.GetNbinsX())+back.GetBinContent(back.GetNbinsX()+1))
  #data overflow
  datahist.SetBinContent(datahist.GetNbinsX(),datahist.GetBinContent(datahist.GetNbinsX())+datahist.GetBinContent(datahist.GetNbinsX()+1))
  
  #normierung  
  
  if norm==True:
    dataintegral=0
    dataintegral=datahist.Integral()
    if dataintegral!=0:
      datahist.Scale(1/dataintegral)    
  
  SetOwnership(stack,0)
  SetOwnership(leg,0)
  SetOwnership(datahist,0)
  SetOwnership(line,0)
  
  c=TCanvas()
  c.cd()  
  makepadhist(log,norm)  
  stack.Draw()
  set_stackattributes(stack,ymin,log,norm)
  datahist.Draw("SAMEE0")
  leg.Draw()  

  text1 = TLatex()
  text1.SetNDC()
  text1.SetTextFont(42)
  text1.SetTextSize(0.05)
  text1.DrawLatex(0.175, 0.863, text)
  #text1.DrawLatex(0.175, 0.76, "#geq 6 Jets, #geq 4 b-tags, 1 tight muon")
  text1.DrawLatex(0.175, 0.815, cutlabel)

  
  
  #SetOwnership(back,0)
  #backtext=TPaveText(0.2,0.9,0.8,1,"NDC")
  #backtext.AddText("MC events: "+str(back.Integral()))
  backevents=back.Integral()
  dataevents=datahist.Integral()
  print "MC Events: ", backevents
  #backtext.AddText("data: " +str(datahist.Integral()))
  print "data Events: ",dataevents
  #backtext.Draw("")
  
  c.cd()
  makepadratio()  
  ratio=makeratio(stack,datahist,xtitle)
  set_ratioattributes(ratio,xmin,xmax,nbins,xtitle)
  line.Draw()    
  
  if norm==True:
    c.Print(varname+cutlabel+"_norm.pdf")
    #c.Print(varname+cutlabel+"_norm.png")
    #c.Print(varname+cutlabel+"_norm.root")
  else:
    c.Print(varname+cutlabel+".pdf")
    #c.Print(varname+cutlabel+".png")
    #c.Print(varname+cutlabel+".root")
 
  return c





    


#####Get trees from files#####

#f_ttbar=TFile("/storage/8/tpfotzer/BEANTrees/2015B_newJEC/MC_Pythia_TTbar_RUN2_Tree.root")
#f_wjets=TFile("/storage/8/tpfotzer/BEANTrees//2015B_newJEC/MC_Pythia_WJets_RUN2_Tree.root")
#f_ww=TFile("/storage/8/tpfotzer/BEANTrees/2015B_newJEC/MC_Pythia_WW_RUN2_Tree.root")
#f_zjets=TFile("/storage/8/tpfotzer/BEANTrees/2015B_newJEC/MC_Pythia_ZJets_RUN2_Tree.root")
#f_data_SingleElectron=TFile("/storage/8/tpfotzer/BEANTrees/2015B_newJEC/SingleElectron_2015B_Tree.root ")
f_data_SingleMuon=TFile("/storage/8/tpfotzer/BEANTrees/2015B_newJEC/SingleMuon_2015B_customJEC_Tree.root ")
f_qcd=TFile("/storage/8/tpfotzer/BEANTrees/2015B_newGT/MC_QCD_MuEnriched_Tree.root")



#tree_ttbar=f_ttbar.Get("MVATree")
#tree_wjets=f_wjets.Get("MVATree")
#tree_ww=f_ww.Get("MVATree")
#tree_zjets=f_zjets.Get("MVATree")  

#singletopfiles=["/storage/8/tpfotzer/BEANTrees/2015B_newJEC/MC_Pythia_ST_tW_RUN2_Tree.root",
		#"/storage/8/tpfotzer/BEANTrees/2015B_newJEC/MC_Pythia_ST_t_RUN2_Tree.root",
		#"/storage/8/tpfotzer/BEANTrees/2015B_newJEC/MC_Pythia_ST_tbarW_RUN2_Tree.root",
		#"/storage/8/tpfotzer/BEANTrees/2015B_newJEC/MC_Pythia_ST_tbar_RUN2_Tree.root"]
		
#singletopchain=TChain("MVATree")
#for file in singletopfiles:
  #singletopchain.AddFile(file)	


tree_qcd=f_qcd.Get("MVATree") 
trees_back=[tree_qcd]
tree_data_SingleMuon=f_data_SingleMuon.Get("MVATree")
########################
backnames=["LF","HF","C"]
color=[kGreen, kRed, kBlue]
#backweight="0.004186*Weight"
backweight="(Weight*Weight_PV)"
cut_lf=backweight+"*((N_Jets>=2)&&(N_TightLeptons==0))"


#mccut=[cut_lf, cut_hf, cut_c]
mccut=cut_lf

##ignore
datacut="(N_TightLeptons>=1)&&(Triggered_HLT_IsoMu24_eta2p1_v2==1)"
#######################
#open canvas to save all plots in 1 files
pdfname="QCD_study.pdf"
canvas=TCanvas()
canvas.Print(pdfname+"[")


text="CMS private work"
cutlabel="QCD-Sample" 


nbins=14
xmin=-0.5
xmax=13.5
ymin=0.05

log=False
xtitle="Number of Jets"
canvas=plot("N_Jets",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
canvas.Print(pdfname)

nbins=8
xmax=8.5
xtitle="Number of B Tags"
canvas=plot("N_BTagsM",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
canvas.Print(pdfname)

nbins=40
xmin=-4
xmax=4
xtitle="Jet #eta"
canvas=plot("Jet_Eta",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
canvas.Print(pdfname)

xmin=-7
xmax=7
#xtitle="Had Top Eta"
#canvas=plot("HadTop_Eta",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
#canvas.Print(pdfname)

nbins=50
xmin=-3
xmax=200
ymin=0.05

log=False
xtitle="p_{T} of all Jets in GeV/c"
canvas=plot("Jet_Pt",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
canvas.Print(pdfname)

xmax=500
#xtitle="p_{T} HadTop in GeV/c"
#canvas=plot("HadTop_Pt",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
#canvas.Print(pdfname)

xmax=180
#xtitle="MET in GeV/c"
#canvas=plot("Evt_Pt_MET",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
#canvas.Print(pdfname)

nbins=50
xmin=-4
xmax=4
#xtitle="MET #Phi"
#canvas=plot("Evt_Phi_MET",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
#canvas.Print(pdfname)

xtitle="Jet #Phi"
canvas=plot("Jet_Phi",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
canvas.Print(pdfname)

xmin=0
xmax=45
nbins=45
xtitle="Number of Primary Vertices"
canvas=plot("N_PrimaryVertices",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
canvas.Print(pdfname)


nbins=50
xmin=0
xmax=200
ymin=0.05


xtitle="p_{T} of  hardest Jet"
canvas=plot("Jet_Pt[0]",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
canvas.Print(pdfname)

xmax=150

xtitle="p_{T} of 2nd hardest Jet"
canvas=plot("Jet_Pt[1]",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
canvas.Print(pdfname)

xmin=-0.2
xmax=1
nbins=11
xtitle="Jet CSV "
canvas=plot("Jet_CSV",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
canvas.Print(pdfname)

xtitle="Jet CSV[0] "
canvas=plot("Jet_CSV[0]",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
canvas.Print(pdfname)


xmax=150

#xtitle="p_{T} of 3rd hardest Jet"
#canvas=plot("Jet_Pt[2]",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
#canvas.Print(pdfname)

xmax=150

#xtitle="p_{T} of 4th hardest Jet"
#canvas=plot("Jet_Pt[3]",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
#canvas.Print(pdfname)


xmax=150
#xtitle="p_{T} of 5th hardest Jet"
#canvas=plot("Jet_Pt[4]",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
#canvas.Print(pdfname)
nbins=50
xmax=150
#xtitle="MET [GeV/c]"
#canvas=plot("Evt_Pt_MET",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
#canvas.Print(pdfname)

nbins=30
xmin=-4
xmax=4
#xtitle="MET #Phi"
#canvas=plot("Evt_Phi_MET",trees_back,tree_data_SingleMuon,backnames,color,mccut,datacut,nbins,xmin,xmax,ymin,xtitle,cutlabel,text,log)
#canvas.Print(pdfname)



canvas.Print(pdfname+"]")
raw_input("Press Enter...")

    