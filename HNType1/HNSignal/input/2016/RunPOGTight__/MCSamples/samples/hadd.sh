#!/bin/sh

hadd HNSignal_VV.root HNSignal_*_powheg.root
mv HNSignal_VV.root ..
hadd HNSignal_tX.root HNSignal_tt*.root HNSignal_T*.root
mv HNSignal_tX.root ..
hadd HNSignal_others.root HNSignal_WpWp*.root HNSignal_WWW.root HNSignal_WWZ.root HNSignal_WZZ.root HNSignal_ZZZ.root HNSignal_gg*.root HNSignal_VBF*.root HNSignal_VH*.root
mv HNSignal_others.root ..
