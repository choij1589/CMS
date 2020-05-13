from ROOT import TFile, TDirectory, TH1D

# Basic information
IDs = ("passLoose", "passTight", "FakeLoose", "FakeTight")
Systs = ("BtagDep", "JetPtCut30", "JetPtCut35", "JetPtCut40", "JetPtCut45", "JetPtCut50", "JetPtCut55", "JetPtCut60")

path_data = "/home/choij/Documents/CMS/FakeEstimator/MakeNPV/output/2016/DATA/MakeNPV_DoubleEG_2016.root"
path_mc = "/home/choij/Documents/CMS/FakeEstimator/MakeNPV/output/2016/MakeNPV_WJets_MG.root"

def GetDirectory(id, isData):
	id = id + "ID_Central"
	if isData:
		f = f_data
	else:
		f = f_mc
	return f.GetDirectory(id)

# prepare i/o root files
f_data = TFile(path_data, "read")
f_mc = TFile(path_mc, "read")

f_out = TFile("nPV_reweight.root", "recreate")
f_out.cd()

for id in IDs:
    dir = f_out.mkdir(id + "ID_Central")

# Write histograms in output root file
for id in IDs:
    dir_data = GetDirectory(id, 1)
    dir_mc = GetDirectory(id, 0)

    dir_out = f_out.GetDirectory(id + "ID_Central")
    dir_out.cd()
    for syst in Systs:
        # Get histograms for mc anc data
        histname = "nPV_" + id + "ID_Central_" + syst
        h_data = dir_data.Get(histname)
        h_mc = dir_mc.Get(histname)

        # Scale histograms to get shape
        h_data.Scale(1 / h_data.Integral())
        h_mc.Scale(1 / h_mc.Integral())

        # Make histogram to get distribution of nPV_reweight
        h = h_data.Clone("nPV_reweight_" + id + "ID_" + syst)
        h.Divide(h_mc)

        h.Write()

f_data.Close()
f_mc.Close()
f_out.Close()


