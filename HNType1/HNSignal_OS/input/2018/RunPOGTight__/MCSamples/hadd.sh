#!/bin/sh

mkdir samples && mv *.root samples
cd samples

cp HNSignal_OS_DYJets.root ..
cp HNSignal_OS_TTLL_powheg.root ..

# VV
hadd HNSignal_OS_VV.root HNSignal_OS_WZTo3LNu_powheg.root HNSignal_OS_ZZTo4L_powheg.root HNSignal_OS_WWTo2L2Nu_powheg.root
mv HNSignal_OS_VV.root ..

# tX
hadd HNSignal_OS_tX.root HNSignal_OS_tt*.root HNSignal_OS_TTG.root HNSignal_OS_TG.root
mv HNSignal_OS_tX.root ..

# others
hadd HNSignal_OS_others.root HNSignal_OS_WpWp*.root HNSignal_OS_WWW.root HNSignal_OS_WWZ.root HNSignal_OS_WZZ.root HNSignal_OS_ZZZ.root HNSignal_OS_gg*.root HNSignal_OS_V*.root
mv HNSignal_OS_others.root ..
