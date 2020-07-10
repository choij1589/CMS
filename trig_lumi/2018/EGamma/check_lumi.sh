#!/bin/sh

trig_EGamma_2018="
HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v*
HLT_Ele23_CaloIdM_TrackIdM_PFJet30_v*
HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*
HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*
HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v*
"


for path in $trig_EGamma_2018
do
	brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json -u /fb --hltpath "$path"  -i ../Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt -o $path.csv 
	echo $path.csv is created
done

mv *.csv result
echo All done
