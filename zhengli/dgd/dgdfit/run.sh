#!/bin/bash

source /cvmfs/sft.cern.ch/lcg/releases/LCG_102b/ROOT/6.26.08/x86_64-centos9-gcc11-opt/ROOT-env.sh

./fitDgd -m Hesse | tee log_data_fit &
