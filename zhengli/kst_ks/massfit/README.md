This program performs massfit for Bd2JpsiKstar and Bd2JpsiKshort,divided into two stages:massfit before BDT and massfit after BDT.

massfit before BDT:presel_kst/presel_ks

massfit after BDT:fulsel_kst/fulsel_ks

## Step
- 1.Modify data_xxxx and mc_xxxx:
  
/path/filename.root

Use the samples after preselection

- 2.Modify massfit.cpp
  
Edit the branch name, ofroot,mvacut(after BDT) as needed

- 3.Make headfile massfit.h:
  
Example:/path/makeHeadfile/MakeHeadfile -f mc_2016 -t cla2 -n massfit

- 4.Compile the massfit.cpp through "make"

- 5.Modify and run "sh run.sh mode" as needed .
  
mode=mc:massfit with MC samples after preselection

mode=data:massfit with data samples after preselection

mode=calw:massfit and generate new ROOT file with sWeights

### (massfit after BDT)
- 6.Modify applyBDTCut.C and run the code

