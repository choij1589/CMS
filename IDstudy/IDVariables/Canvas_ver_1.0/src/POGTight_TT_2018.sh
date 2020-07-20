#!/bin/sh

# TT
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/METv", "E_{T}^{miss}", "Events", 3000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/METv_phi", "#phi(E_{T}^{miss})", "Events", 4500, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/METv_xyCorr_pt", "E_{T}^{miss}", "Events", 3000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/METv_xyCorr_phi", "#phi(E_{T}^{miss})", "Events", 4500, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/dR(mumu)", "#Delta R(#mu#mu)", "Events", 2000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/nJets", "N(j)", "Events", 100000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/nBJets", "N(b)", "Events", 120000, 1.5, 0.5)'

mv *.png ../Plots/2018/POGTight/TT

# TT/j1
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/j1/pt", "p_{T}(j1)", "Events", 4000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/j1/eta", "#eta(j1)", "Events", 12000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/j1/phi", "#phi(j1)", "Events", 9000, 1.5, 0.5)'

mv *.png ../Plots/2018/POGTight/TT/j1

# TT/j2
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/j2/pt", "p_{T}(j2)", "Events", 7000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/j2/eta", "#eta(j2)", "Events", 10000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/j2/phi", "#phi(j2)", "Events", 6000, 1.5, 0.5)'

mv *.png ../Plots/2018/POGTight/TT/j2

# TT/mu1
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu1/pt", "p_{T}(#mu1)", "Events", 3000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu1/eta", "#eta(#mu1)", "Events", 7000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu1/phi", "#phi(#mu1)", "Events", 3500, 1.5, 0.5)'

mv *.png ../Plots/2018/POGTight/TT/mu1

# TT/mu1/IDvar
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu1/IDvar/Chi2", "#chi^2(#mu1)", "Events", 12000, 2.0, 0.)';
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu1/IDvar/RelIso", "I_{rel}(#mu1)", "Events", 70000, 2.0, 0.)';
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu1/IDvar/SIP2D", "SIP_{2D}(#mu1)", "Events", 16000, 2.0, 0.)';
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu1/IDvar/dXY", "d_{XY}(#mu1)", "Events", 80000, 2.0, 0.)';
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu1/IDvar/dXYerr", "d_{XY}^{err}(#mu1)", "Events", 100000, 2.0, 0.)';
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu1/IDvar/dZ", "d_{Z}(#mu1)", "Events", 30000, 2.0, 0.)';

mv *.png ../Plots/2018/POGTight/TT/mu1/IDvar

# TT/mu2
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu2/pt", "p_{T}(#mu2)", "Events", 12000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu2/eta", "#eta(#mu2)", "Events", 7000, 1.5, 0.5)'
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu2/phi", "#phi(#mu2)", "Events", 4000, 1.5, 0.5)'

mv *.png ../Plots/2018/POGTight/TT/mu2

# TT/mu2/IDvar
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu2/IDvar/Chi2", "#chi^2(#mu2)", "Events", 12000, 2.0, 0.)';
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu2/IDvar/RelIso", "I_{rel}(#mu2)", "Events", 60000, 2.0, 0.)';
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu2/IDvar/SIP2D", "SIP_{2D}(#mu2)", "Events", 14000, 2.0, 0.)';
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu2/IDvar/dXY", "d_{XY}(#mu2)", "Events", 70000, 2.0, 0.)';
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu2/IDvar/dXYerr", "d_{XY}^{err}(#mu2)", "Events", 90000, 2.0, 0.)';
root -l -q 'Canvas.cpp(2018, "POGTight_Central/TT/mu2/IDvar/dZ", "d_{Z}(#mu2)", "Events", 40000, 2.0, 0.)';

mv *.png ../Plots/2018/POGTight/TT/mu2/IDvar
