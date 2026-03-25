#!/bin/bash
if [ ! $# -eq 1  ];then
   echo param error!
   exit 1
fi

mode=$1

num=500000

if [ "$mode" == "mc" ];then
   ./main_massfit -f mc_2016 -m mc_Y2016 -n ${num} &
   # ./main_massfit -f mc_2017 -m mc_Y2017 -n ${num} &
   # ./main_massfit -f mc_2018 -m mc_Y2018 -n ${num} &
   cat parinfor/mc_base_2016.dat >> parinfor/data_base_2016.dat
   # cat parinfor/mc_base_2017.dat >> parinfor/data_base_2017.dat
   # cat parinfor/mc_base_2018.dat >> parinfor/data_base_2018.dat
fi

if [ "$mode" == "data" ];then
   ./main_massfit -f data_2016 -m Y2016 &
    ./main_massfit -f data_2017 -m Y2017 &
    ./main_massfit -f data_2018 -m Y2018 &
fi

if [ "$mode" == "calw" ];then
   ./main_massfit -f data_2016 -m Y2016_Calw &
    ./main_massfit -f data_2017 -m Y2017_Calw &
   ./main_massfit -f data_2018 -m Y2018_Calw &
fi



