# Intruduction

## Structure
- hist_sele_gbw2.C:compare variables with sweighted data, mc and gb reweighting mc in same region 
- hist_sele_train.C:compare varibles with data in sideband and gb reweighting mc in the signal region

## Step
- change the tuple path in "./input/sele_optdef.h"
 
 tree1 and tree3 are for "hist_sele_gbw2".

 1. tree1:sweighted data

 2. tree3:gb reweighting mc

 tree2 and tree3 are for "hist_sele_train"

  1. tree2:data without sweight

  2. tree3:gb reweighting mc

- change the model you wanna to perform in the code.

## Command 

  'sh run.sh'

 