#!/bin/bash
root -l -q 'Canvas_param.C(0, "p_{T}^{e}(1)", "Events / 5GeV", 130, 2)' 
root -l -q 'Canvas_param.C(1, "#eta^{e}(1)", "Events", 60, 2)'
root -l -q 'Canvas_param.C(2, "#phi^{e}(1)", "Events", 40, 2)'
root -l -q 'Canvas_param.C(3, "p_{T}^{e}(2)", "Events / 5GeV", 150, 2)'
root -l -q 'Canvas_param.C(4, "#eta^{e}(2)", "Events", 50, 2)'
root -l -q 'Canvas_param.C(5, "#phi^{e}(2)", "Events", 40, 2)'
root -l -q 'Canvas_param.C(6, "p_{T}^{e}(3)", "Events / 5GeV", 300, 2)'
root -l -q 'Canvas_param.C(7, "#eta^{e}(3)", "Events", 50, 2)'
root -l -q 'Canvas_param.C(8, "#phi^{e}(3)", "Events", 40, 2)'
root -l -q 'Canvas_param.C(9, "M(eee)", "Events / 5GeV", 140, 2)'
root -l -q 'Canvas_param.C(10, "M(e^{+}e^{-})", "Events / 5GeV", 140, 2)'
root -l -q 'Canvas_param.C(11, "E_{T}^{miss}", "Events / 5GeV", 80, 2)'
root -l -q 'Canvas_param.C(12, "Nj", "Events", 180, 2)'
root -l -q 'Canvas_param.C(13, "passEvents", "Events", 400, 2)'
root -l -q 'Canvas_param.C(14, "N_{pairs}", "Events", 350, 2)'

mv *.pdf ../plots/FakeID/
