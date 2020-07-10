#!/bin/sh

trig_DoubleEG_2017="
	HLT_DoublePhoton33_CaloIdL_v*
	HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v*
	HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*
	HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v*
	HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL_v*
	HLT_TriplePhoton_20_20_20_CaloIdLV2_v*
	HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL_v*
	HLT_TriplePhoton_30_30_10_CaloIdLV2_v*
	HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL_v*
"

echo $PWD/..

for path in $trig_DoubleEG_2017
do
	brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json -u /fb --hltpath "$path"  -i ../Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt -o $path.csv	
	echo $path.csv is created
done

mv *.csv result
echo All done
