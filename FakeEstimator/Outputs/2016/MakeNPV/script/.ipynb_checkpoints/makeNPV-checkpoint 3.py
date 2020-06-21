from ROOT import TFile, TDirectory, TH1D
# Basic information
IDs = ("passLoose", "passTight", "FakeLoose", "FakeTight")
Systs = ("BtagDep", "JetPtCut30", "JetPtCut35", "JetPtCut40", "JetPtCut45", "JetPtCut50", "JetPtCut55", "JetPtCut60")

def GetDirectory(id, isData):
	id = id + "ID_Central"
	if isData:
		f = f_data
	else:
		f = f_mc
	return f.GetDirectory(id)

f_data = TFile("/home/choij/Documents/CMS/FakeEstimator/MakeNPV/output/2016/DATA/MakeNPV_DoubleEG_2016.root", "read")
f_mc = TFile("/home/choij/Documents/CMS/FakeEstimator/MakeNPV/output/2016/MakeNPV_WJets_MG.root", "read")

f_out = TFile("nPV_reweight.root", "recreate")

dir_data = GetDirectory(IDs[0], 1)
dir_mc = GetDirectory(IDs[0], 0)
histname = "nPV_" + IDs[0] + "ID_Central_" + Systs[0]

h_data = dir_data.Get(histname)
h_mc = dir_mc.Get(histname)

scale_data = h_data.Integral()
scale_mc = h_mc.Integral()

h_data.Scale(1/scale_data)
h_mc.Scale(1/scale_mc)

h_data.Draw()
h_data.Draw("same")
