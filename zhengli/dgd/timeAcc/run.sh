#!/bin/bash
#source /cvmfs/sft.cern.ch/lcg/releases/LCG_102b/ROOT/6.26.08/x86_64-centos9-gcc11-opt/ROOT-env.sh
if [ ! $# -eq 1  ];then
   echo param error!
   exit 1
fi
#./fitTimeAcc -m Hesse
mode=$1

if [ "$mode" == "runBase" ];then
 # ./fitTimeAcc -m Y1516_Hesse | tee log_data_1516 &  
   ./fitTimeAcc -m Y2016_Hesse | tee log_data_2016 &
   ./fitTimeAcc -m Y2017_Hesse | tee log_data_2017 &  
   ./fitTimeAcc -m Y2018_Hesse | tee log_data_2018 &  
fi

if [ "$mode" == "runVali" ];then
   ./fitTimeAcc -m Y2016_Vali_Hesse | tee log_vali_2016 &  
   # ./fitTimeAcc -m Y1516_Vali_Hesse | tee log_vali_1516 &  
   ./fitTimeAcc -m Y2017_Vali_Hesse | tee log_vali_2017 &  
   ./fitTimeAcc -m Y2018_Vali_Hesse | tee log_vali_2018 &  
fi

if [ "$mode" == "runDg" ];then
   cp parinfor/parinfor_base_1516.dat parinfor/parinfor_dg_1516.dat
   cp parinfor/parinfor_base_2017.dat parinfor/parinfor_dg_2017.dat
   cp parinfor/parinfor_base_2018.dat parinfor/parinfor_dg_2018.dat
   ./fitTimeAcc -m Y1516_Dg_Hesse | tee log_dg_1516 &  
   ./fitTimeAcc -m Y2017_Dg_Hesse | tee log_dg_2017 &  
   ./fitTimeAcc -m Y2018_Dg_Hesse | tee log_dg_2018 &  
fi

if [ "$mode" == "runBaseChck" ];then
   ./fitTimeAcc -m Y1516_Nfit_Chck &  
   ./fitTimeAcc -m Y2017_Nfit_Chck &  
   ./fitTimeAcc -m Y2018_Nfit_Chck &  
fi

if [ "$mode" == "runValiChck" ];then
   ./fitTimeAcc -m Y1516_Vali_Nfit_Chck &  
   ./fitTimeAcc -m Y2017_Vali_Nfit_Chck &  
   ./fitTimeAcc -m Y2018_Vali_Nfit_Chck &  
fi

if [ "$mode" == "PlotBase" ];then
   ./fitTimeAcc -m Y1516_Nfit &  
   ./fitTimeAcc -m Y2017_Nfit &  
   ./fitTimeAcc -m Y2018_Nfit &  
fi

if [ "$mode" == "PlotVali" ];then
   ./fitTimeAcc -m Y1516_Vali_Nfit &  
   ./fitTimeAcc -m Y2017_Vali_Nfit &  
   ./fitTimeAcc -m Y2018_Vali_Nfit &  
fi
