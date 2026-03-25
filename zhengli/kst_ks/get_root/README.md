This project performs preselection on Bd2Jpsikstar and Bd2Jpsikstar samples to reduce background events. The process is divided into two parts:
kst_reduce and ks_reduce

## Step
- 1.Modify data_xxxx and mc_xxxx:
Line 1: /Path/filename.root/TTree
Line 2: /Path/filename.root

- 2.Modify reduce.cpp:
Add or delete branches and cut as needed.

- 3.Make headfile reduce.h:
Example:
/path/makeHeadfile/MakeHeadfile -f filelist/mc_2016 -n reduce .

If data and MC branches differ, manually adjust the generated headfile to match your data structure.

- 4.Compile the reduce.cpp through "make"

- 5.Modify and run "sh run.sh" .


