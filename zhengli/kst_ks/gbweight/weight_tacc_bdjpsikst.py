from gbWeight import *
import os
import threading as thd
import random
import string

style.use('seaborn-muted')
rcParams.update({'font.size': 8})
rcParams['figure.figsize'] = 22, 10
rcParams['xtick.labelsize'] = 8
rcParams['ytick.labelsize'] = 8


# Set the year
year = '1516'
if ( len(sys.argv)>1 ) :
    tmp_year = str(sys.argv[1])
    if( tmp_year == '1516' or tmp_year == '2017' or tmp_year == '2018' ):
        year = str( sys.argv[1] )

ininum=0
finnum=3

# set input
columns1 = [
 "B_PT",
 "B_y",
 "nTracks",
]

columns2 = [
 "B_PT",
 "B_y",
 "nTracks",
]

origin_file = [
'/lzufs/home/lipl/userfs/LHCb/deltaGd/samples/Bd2JpsiKshort_2016_MC_selected.root'
]

target_file = [
'/lzufs/home/lipl/userfs/LHCb/deltaGd/samples/Bd2JpsiKshort_2016_data_selected.root'
]

output_file = [
'/lzufs/user/zhanghy/kshort/Bd2JpsiKshort_2016_mc_trig.root']

origin_tree = "DecayTree"
target_tree = "DecayTree"
output_tree = "DecayTree"

origin_cut = ""
target_cut = ""

origin_w = [
'',
]

target_w = [ 
'sig_sw',
]

# set label and output
nrow = 5
ncol = 2

outgbw  = "taccw"
picname = [
"/lzufs/user/zhanghy/kshort/gbweight/plots/tacc_gbw_mc_bdjpsirho_2016_trigj.pdf",
]

arglist = []
for i in range(ininum,finnum):

   incol = columns1
   if i==2 or i==3 : incol = columns2
   if i%2 == 0 : origin_cut = "trigj"
   if i%2 == 1 : origin_cut = "trigb"
   target_cut = origin_cut

   tmp_origin_file = origin_file[i].format(year)
   tmp_target_file = target_file[i].format(year)
   tmp_output_file = output_file[i].format(year)
   tmp_picname     = picname[i].format(year)

   tmp_origin_w = origin_w[0]
   tmp_target_w = target_w[0] 
   tmp_origin_cut = origin_cut
   tmp_target_cut = target_cut

   print("----------------------------------------")
   print(" GBWeight is being performed for data [%s,%i]" %(year,i) )
   print("----------------------------------------")
   arglist.append(( 
   #gbWeight(
        incol, 70, 0.1, 7, 
        tmp_origin_file, origin_tree, tmp_origin_cut, tmp_origin_w,
        tmp_target_file, target_tree, tmp_target_cut, tmp_target_w, 
        tmp_origin_file, origin_tree, tmp_origin_cut, tmp_origin_w,
        tmp_output_file, output_tree, outgbw, nrow, ncol, tmp_picname
   #     )
   ))
   
print( arglist )   


muljobs = []
for i in range( len(arglist) ):
    tmpjob = thd.Thread( target=gbWeight, args = arglist[i], name = "line_%i" %(i) )
    muljobs.append( tmpjob )
    tmpjob.start()

for subjob in muljobs: subjob.join()
'''
'''
