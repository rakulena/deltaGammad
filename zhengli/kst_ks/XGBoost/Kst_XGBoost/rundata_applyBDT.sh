#!/bash/sh
years=("2016" "2017" "2018")

baseInputData="/lzufs/user/zhanghy/Sample/data/Bd2JpsiKstar/Bd2JpsiKstar_"
inputconf="/lzufs/user/zhanghy/kst_ks/Kst_XGBoost/Bd2JpsiKstar.json"
basemodel="/lzufs/user/zhanghy/kst_ks/Kst_XGBoost/models/Bd2JpsiKstar_"
baseoutputData="/lzufs/user/zhanghy/Sample/Train/Bd2JpsiKstar_data_"

for year in "${years[@]}"
do
    inputData="${baseInputData}${year}_data_selected_fewvars_presel.root"
    model="${basemodel}${year}_0.model ${basemodel}${year}_1.model ${basemodel}${year}_2.model ${basemodel}${year}_3.model ${basemodel}${year}_4.model"
    outputData="${baseoutputData}${year}_BDT.root"

### apply BDT 
python ApplyBDTdata.py -i ${inputData} -b ${model} -j ${inputconf} -o ${outputData} 
done