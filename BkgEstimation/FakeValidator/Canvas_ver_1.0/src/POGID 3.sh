#!/bin/bash
#root -l -q 'Canvas_param.C(0, "p_{T}^{e}(1)", "Events / 10GeV", 800, 2)'
#root -l -q 'Canvas_param.C(1, "#eta^{e}(1)", "Events", 300, 2)'
#root -l -q 'Canvas_param.C(2, "#phi^{e}(1)", "Events", 300, 2)'
#root -l -q 'Canvas_param.C(3, "p_{T}^{e}(2)", "Events / 10GeV", 1000, 2)'
#root -l -q 'Canvas_param.C(4, "#eta^{e}(2)", "Events", 300, 2)'
#root -l -q 'Canvas_param.C(5, "#phi}^{e}(2)", "Events", 300, 2)'
#root -l -q 'Canvas_param.C(6, "p_{T}^{e}(3)", "Events / 10GeV", 1600, 2)'
#root -l -q 'Canvas_param.C(7, "#eta^{e}(3)", "Events", 300, 2)'
#root -l -q 'Canvas_param.C(8, "#phi^{e}(3)", "Events", 300, 2)'
#root -l -q 'Canvas_param.C(9, "E_{T}^{miss}", "Events / 10GeV", 800, 2)'
#root -l -q 'Canvas_param.C(10, "Nj", "Events", 1200, 2)'
root -l -q 'Canvas_param.C(11, "M(ee)", "Events / 2GeV", 800, 2)'

mv *.pdf ../plots/POGID/
