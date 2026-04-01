#!/bin/bash

year=( 2016 2017 2018)

for i in $(seq 0 2)
do
   root -l -b -q hist_sele_gbw2.C\(${year[i]}\)  &
   root -l -b -q hist_sele_train.C\(${year[i]}\) &
done

