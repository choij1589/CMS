#!/bin/sh

# 
root -l -q 'Macro_param.cpp("2016", "RunPOGTight", "preselection", "METv", "pt")'
root -l -q 'Macro_param.cpp("2016", "RunPOGTight", "preselection", "METv", "eta")'
root -l -q 'Macro_param.cpp("2016", "RunPOGTight", "preselection", "METv", "phi")'

cd *.png ../output/preselection/METv/
