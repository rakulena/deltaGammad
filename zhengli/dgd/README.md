## Intruoduction

This folder is used to fit the time acceptance and perform a decay-time fit to measure deltagammad with Bd2JpsiKshort and Bd2JpsiKstar

## Struction 
- timeAcc: fit time acceptance by signal and control samples
- dgdfit: fit the decay-time to extract the deltagammad
  
## Enviorment
   'source /cvmfs/sft.cern.ch/lcg/releases/LCG_102b/ROOT/6.26.08/x86_64-centos9-gcc11-opt/ROOT-env.sh'


## Step
- 1.Extract the time acceptance of Bd->JpsiKshort and Bd->JpsiKstar

    path:./dgd/timeAcc/fitTimeAcc.cpp

    1. line 106-109:Set the paths to the signal and control samples.
    2. line 172-186:Adjust input settings and cuts.
    3. line 277-339:Set resolution model depending on the samples you use
    4. line 635-653:Change the plot titles depending on the samples you use 


- 2.Obtain the time acceptance results

    Use the the time acceptance results obtained in step1 to generate './dgd/dgdfit/parinfor_base_allyears.dat',refering to './dgd/update_parameters.cpp'
  
    1. Separately run step1 with Bd2JpsiKs and Bd2JpsiKst and copy the 'parinfor' folder to corresponding directory 'jpsiks' and 'jpsikst'
    2. Set the paths in main function practically in 'update_parameters.cpp'.
    3. run'g++ -o update_parameters update_parameters.cpp'     

- 3.fit decay-time to extract dgd

    path:./dgd/dgdfit/fitTimeAcc.cpp

    1. line 181-182:Set the paths of Bd2JpsiKshort and Bd2JpsiKstar
    2. line 189-198：Shared parameters
           
## Command
    'make clean'
    
    'make'
    
    'sh run.sh'
