#!/bin/sh

conda activate CMS

hadd ConvEstimator_MC.root ConvEstimator_*.root
hadd ConvEstimator_VV.root ConvEstimator_*_pythia.root
hadd ConvEstimator_ttVorH.root ConvEstimator_ttWToLNu.root ConvEstimator_ttZToLLNuNu.root ConvEstimator_ttHToNonbb.root
hadd ConvEstimator_rare.root ConvEstimator_VBF_HToZZTo4L.root ConvEstimator_WWW.root ConvEstimator_WWZ.root ConvEstimator_WZZ.root ConvEstimator_ZZZ.root ConvEstimator_ggHToZZTo4L.root
cp ConvEstimator_ZGTo2LG.root ConvEstimator_conv.root

mv ConvEstimator_MC.root Samples
mv ConvEstimator_VV.root Samples
mv ConvEstimator_ttVorH.root Samples
mv ConvEstimator_rare.root Samples
mv ConvEstimator_conv.root Samples
