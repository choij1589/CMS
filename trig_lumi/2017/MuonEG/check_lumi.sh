#!/bin/sh

trig_MuonEG_2017="
HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ_v*
HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v*
HLT_Mu12_DoublePhoton20_v*
HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*
HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*
HLT_Mu17_Photon30_IsoCaloId_v*
HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*
HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*
HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ_v*
HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v*
HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*
HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*
"


for path in $trig_MuonEG_2017
do
	brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json -u /fb --hltpath "$path"  -i ../Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt -o $path.csv	
	echo $path.csv is created
done

mv *.csv result
echo All done
