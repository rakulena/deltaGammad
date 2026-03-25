This program performs GB reweighting on MC samples using sWeighted data samples from massfit,divided into two parts:Bd2JpsiKstar and Bd2JpsiKshort.

JpsiKstar:weight_sele_bdjpsikstar.py

JpsiKshort：weight_sele_bdjpsikshort.py

## Step
- 1.Set enviroment configuration

Example:lb-conda default/2024-07-10 

or use other compatible environment configurations that can execute the code.

- 2.Modify weight_sele_bdjpsikstar/weight_sele_bdjpsikshort.py
  
Edit run number,"gbw varaible",file,tree,"picname"

origin_file:MC samples after preselection

target_file:sWeighted data samples 

output_file:gb reweighting MC samples

- 3.Run weight_sele_bdjpsikstar/weight_sele_bdjpsikshort.py
  
Example：python weight_sele_bdjpsikstar

python weight_sele_bdjpsikshort.py

