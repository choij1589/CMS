#!/bin/zsh

# DY
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/M(mumu)", "M(#mu#mu)", "Events", 4000000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/METv", "E_{T}^{miss}", "Events", 1200000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/METv_phi", "#phi(E_{T}^{miss})", "Events", 1000000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/METv_xyCorr_pt", "E_{T}^{miss}", "Events", 1200000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/METv_xyCorr_phi", "#phi(E_{T}^{miss})", "Events", 1000000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/dR(mumu)", "#Delta R(#mu#mu)", "Events", 1500000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/nJets", "N(j)", "Events", 40000000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/nBJets", "N(b)", "Events", 40000000, 1.5, 0.5)'

mv *.png ../Plots/2017/POGTight/DY

# DY/mu1
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu1/pt", "p_T(#mu1)", "Events", 1500000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu1/eta", "#eta(#mu1)", "Events", 1200000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu1/phi", "#phi(#mu1)", "Events", 1200000, 1.5, 0.5)'
mv *.png ../Plots/2017/POGTight/DY/mu1

# DY/mu1/IDvar
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu1/IDvar/Chi2", "#chi^2(#mu1)", "Events", 3500000, 2.0, 0.)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu1/IDvar/RelIso", "I_{rel}(#mu1)", "Events", 8000000, 2.0, 0.)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu1/IDvar/SIP2D", "SIP_{2D}(#mu1)", "Events", 6000000, 2.0, 0.)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu1/IDvar/dXY", "d_{XY}(#mu1)", "Events", 12000000, 2.0, 0.)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu1/IDvar/dXYerr", "d_{XY}^{err}(#mu1)", "Events", 12000000, 2.0, 0.)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu1/IDvar/dZ", "d_{Z}(#mu1)", "Events", 8000000, 2.0, 0.)'

mv *.png ../Plots/2017/POGTight/DY/mu1/IDvar

# DY/mu2
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu2/pt", "p_T(#mu2)", "Events", 2500000, 2.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu2/eta", "#eta(#mu2)", "Events", 2200000, 2.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu2/phi", "#phi(#mu2)", "Events", 2200000, 2.5, 0.5)'

mv *.png ../Plots/2017/POGTight/DY/mu2

# DY/mu2/IDvar
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu2/IDvar/Chi2", "#chi^2(#mu2)", "Events", 3500000, 2.0, 0.)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu2/IDvar/RelIso", "I_{rel}(#mu2)", "Events", 8000000, 2.0, 0.)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu2/IDvar/SIP2D", "SIP_{2D}(#mu2)", "Events", 6000000, 2.0, 0.)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu2/IDvar/dXY", "d_{XY}(#mu2)", "Events", 12000000, 2.0, 0.)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu2/IDvar/dXYerr", "d_{XY}^{err}(#mu2)", "Events", 12000000, 2.0, 0.)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/mu2/IDvar/dZ", "d_{Z}(#mu2)", "Events", 8000000, 2.0, 0.)'

mv *.png ../Plots/2017/POGTight/DY/mu2/IDvar

# DY/j1
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/j1/pt", "p_{T}(j1)", "Events", 200000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/j1/eta", "#eta(j1)", "Events", 200000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/j1/phi", "#phi(j1)", "Events", 200000, 1.5, 0.5)'

mv *.png ../Plots/2017/POGTight/DY/j1

# DY/j2
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/j2/pt", "p_{T}(j2)", "Events", 150000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/j2/eta", "#eta(j2)", "Events", 150000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2017, "POGTight_Central/DY/j2/phi", "#phi(j2)", "Events", 150000, 1.5, 0.5)'

mv *.png ../Plots/2017/POGTight/DY/j2
