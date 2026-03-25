from gbWeight import *
import os
import threading as thd
import random
import string


#style.use('seaborn-muted')
rcParams.update({'font.size': 8})
rcParams['figure.figsize'] = 22, 10
rcParams['xtick.labelsize'] = 8
rcParams['ytick.labelsize'] = 8

# set run number
ininum=0
finnum=3

# set input
columns1 = [
  
  "Bd_P",
  "Bd_PT",
  "nTracks",
  "log_Bd_IPCHI2_OWNPV",
  "log_Bd_OnlyPV_CHI2NDOF",
  "Kplus_ProbNNk_corr",
  "piminus_ProbNNpi_corr",
]
origin_file = [
'/lzufs/user/zhanghy/Sample/mc/Bd2JpsiKstar/Bd2JpsiKstar_2016_MC_selected_fewvars_presel.root',
'/lzufs/user/zhanghy/Sample/mc/Bd2JpsiKstar/Bd2JpsiKstar_2017_MC_selected_fewvars_presel.root',
'/lzufs/user/zhanghy/Sample/mc/Bd2JpsiKstar/Bd2JpsiKstar_2018_MC_selected_fewvars_presel.root',
]

target_file = [
'/lzufs/user/zhanghy/Sample/data/Bd2JpsiKstar/presel_Bd2JpsiKstar_data_2016_sw_base.root',
'/lzufs/user/zhanghy/Sample/data/Bd2JpsiKstar/presel_Bd2JpsiKstar_data_2017_sw_base.root',
'/lzufs/user/zhanghy/Sample/data/Bd2JpsiKstar/presel_Bd2JpsiKstar_data_2018_sw_base.root',
]

output_file = [
'/lzufs/user/zhanghy/Sample/mc/Bd2JpsiKstar/Bd2JpsiKstar_2016_MC_selected_fewvars_presel_gbw.root',
'/lzufs/user/zhanghy/Sample/mc/Bd2JpsiKstar/Bd2JpsiKstar_2017_MC_selected_fewvars_presel_gbw.root',
'/lzufs/user/zhanghy/Sample/mc/Bd2JpsiKstar/Bd2JpsiKstar_2018_MC_selected_fewvars_presel_gbw.root',
]

origin_tree = "DecayTree"
target_tree = "DecayTree"
output_tree = "DecayTree"


origin_cut = "nTracks<600"
target_cut = "nTracks<600"

origin_w = ''
target_w = 'sig_sw'

# set label and output
nrow = 6
ncol = 2

outgbw  = "gbw"
picname = [
	"/lzufs/user/zhanghy/kst_ks/gbweight/plots/sele_gbw_bdjpsikstar_2016.pdf",
  "/lzufs/user/zhanghy/kst_ks/gbweight/plots/sele_gbw_bdjpsikstar_2017.pdf",
  "/lzufs/user/zhanghy/kst_ks/gbweight/plots/sele_gbw_bdjpsikstar_2018.pdf",
	
]

arglist = []
for i in range(ininum,finnum):

   incol = columns1
   arglist.append(( 
        incol, 60, 0.1, 6, 
        origin_file[i], origin_tree, origin_cut, origin_w,
        target_file[i], target_tree, target_cut, target_w, 
        origin_file[i], origin_tree, origin_cut, origin_w,
        #wgtcor_file[i], wgtcor_tree, wgtcor_cut, wgtcor_w,
        output_file[i], output_tree, outgbw, nrow, ncol, picname[i]
        ))
   print("----------------------------------------")
   print(" GBWeight is being peformed for data ", i)
   print("----------------------------------------")
print( arglist )   

muljobs = []
for i in range( len(arglist) ):
    tmpjob = thd.Thread( target=gbWeight, args = arglist[i], name = "line_%i" %(i) )
    muljobs.append( tmpjob )
    tmpjob.start()

for subjob in muljobs: subjob.join()

