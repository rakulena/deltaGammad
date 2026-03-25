#!/bin/bash

years=("2016" "2017" "2018")

# Define the base paths
baseInputMC="/lzufs/user/zhanghy/Sample/mc/Bd2JpsiKshort/Bd2JpsiKshort_"
baseInputData="/lzufs/user/zhanghy/Sample/data/Bd2JpsiKshort/Bd2JpsiKshort_"
inputconf="/lzufs/user/zhanghy/kst_ks/Ks_XGBoost/Bd2JpsiKshort.json"
selJson="/lzufs/user/zhanghy/kst_ks/Ks_XGBoost/Selection/Bd2JpsiKshort.json"
lumiJson="/lzufs/user/zhanghy/kst_ks/Ks_XGBoost/lumi.json"
baseOutput="/lzufs/user/zhanghy/kst_ks/Ks_XGBoost/models/Bd2JpsiKshort_"
basePlotDir="/lzufs/user/zhanghy/kst_ks/Ks_XGBoost/figs"

for year in "${years[@]}"
do
    inputMC="${baseInputMC}${year}_MC_selected_fewvars_presel_gbw.root"
    inputData="${baseInputData}${year}_data_selected_fewvars_presel.root"
    output="${baseOutput}${year}_0.model ${baseOutput}${year}_1.model ${baseOutput}${year}_2.model ${baseOutput}${year}_3.model ${baseOutput}${year}_4.model"
    plotDir="${basePlotDir}${year}/"

    ### train BDT 
    python TrainBDT.py -m ${inputMC} -d ${inputData} -j ${inputconf} -s ${selJson} -o ${output} -p ${plotDir} -l ${lumiJson}
done
