#!/bin/bash

#./main_reduce -f filelist/data_2015 -y 2015 &
./main_reduce -f filelist/data_2016 -y 2016 &
./main_reduce -f filelist/data_2017 -y 2017 &
./main_reduce -f filelist/data_2018 -y 2018 &  

./main_reduce -f  filelist/mc_2016 -y 2016 -m sig_mc &
#./main_reduce -f filelist/mc_2016_magu -y 2016 -m sig_mc &
#./main_reduce -f filelist/mc_2016_magd -y 2016 -m sig_mc &
./main_reduce -f filelist/mc_2017 -y 2017 -m sig_mc &
#./main_reduce -f filelist/mc_2017_magd -y 2017 -m sig_mc &
./main_reduce -f filelist/mc_2018 -y 2018 -m sig_mc &
#./main_reduce -f filelist/mc_2018_magd -y 2018 -m sig_mc &