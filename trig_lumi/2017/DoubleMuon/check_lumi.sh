#!/bin/sh

trig_DoubleMuon_2017="
HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v*
HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*
HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*
HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v*
HLT_Mu18_Mu9_SameSign_DZ_v*
HLT_Mu18_Mu9_SameSign_v*
HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8_v*
HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8_v*
HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_v*
HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_v*
HLT_Mu20_Mu10_SameSign_DZ_v*
HLT_Mu20_Mu10_SameSign_v*
HLT_Mu23_Mu12_SameSign_DZ_v*
HLT_Mu23_Mu12_SameSign_v*
HLT_Mu37_TkMu27_v*
HLT_TripleMu_10_5_5_DZ_v*
HLT_TripleMu_12_10_5_v*
HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx_v*
HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx_v*
HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx_v*
"


for path in $trig_DoubleMuon_2017
do
	brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json -u /fb --hltpath "$path"  -i ../Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt -o $path.csv	
	echo $path.csv is created
done

mv *.csv result
echo All done
