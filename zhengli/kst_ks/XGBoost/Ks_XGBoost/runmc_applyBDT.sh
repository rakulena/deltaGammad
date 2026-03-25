#!/bash/sh
years=("2016" "2017" "2018")

baseInputMC="/lzufs/user/zhanghy/Sample/mc/Bd2JpsiKshort/Bd2JpsiKshort_"
inputconf="/lzufs/user/zhanghy/kst_ks/Ks_XGBoost/Bd2JpsiKshort.json"
basemodel="/lzufs/user/zhanghy/kst_ks/Ks_XGBoost/models/Bd2JpsiKshort_"
baseoutputMC="/lzufs/user/zhanghy/Sample/Train/Bd2JpsiKshort_mc_"

for year in "${years[@]}"
do
    inputMC="${baseInputMC}${year}_MC_selected_fewvars_presel_gbw.root"
    model="${basemodel}${year}_0.model ${basemodel}${year}_1.model ${basemodel}${year}_2.model ${basemodel}${year}_3.model ${basemodel}${year}_4.model"
    outputMC="${baseoutputMC}${year}_BDT.root"
### apply BDT 
python ApplyBDTmc.py -i ${inputMC} -b ${model} -j ${inputconf} -o ${outputMC} 
done