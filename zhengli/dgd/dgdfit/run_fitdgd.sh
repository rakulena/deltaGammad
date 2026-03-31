#!/bin/bash

if [ $# -ne 1 ]; then
    echo param error!
    exit 1
fi

MODE="$1"
#alltrig trigA trigB
case $MODE in
    alltrig)
        KST_PATH="~/Sample/afterBDT/after_Bd2JpsiKstar_data_%s_sw_base.root/DecayTree"
        KS_PATH="~/Sample/afterBDT/after_Bd2JpsiKshort_data_%s_sw_base.root/DecayTree"
        ;;
    trigA)
        KST_PATH="~/Sample/afterBDT_jpsi/after_Bd2JpsiKstar_data_%s_sw_base.root/DecayTree"
        KS_PATH="~/Sample/afterBDT_jpsi/after_Bd2JpsiKshort_data_%s_sw_base.root/DecayTree"
        ;;
    trigB)
        KST_PATH="~/Sample/afterBDT_Bd/after_Bd2JpsiKstar_data_%s_sw_base.root/DecayTree"
        KS_PATH="~/Sample/afterBDT_Bd/after_Bd2JpsiKshort_data_%s_sw_base.root/DecayTree"
        ;;
esac

FILE="fitDgd.cpp"

sed -i "s|string path_sigD_kst_template = .*|string path_sigD_kst_template = \"${KST_PATH}\";|" $FILE
sed -i "s|string path_sigD_ks_template = .*|string path_sigD_ks_template = \"${KS_PATH}\";|" $FILE

echo "change to ${MODE}"