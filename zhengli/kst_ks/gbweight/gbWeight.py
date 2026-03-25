import os
import sys
import ROOT as rt
import numpy as np
import uproot as ur
import pandas
from hep_ml import reweight
from array import array
from add_weight import *

import time
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import rcParams, style
matplotlib.use('pdf')

from hep_ml.metrics_utils import ks_2samp_weighted
hist_settings = {'bins': 50, 'density': True, 'alpha': 0.8, 'histtype': 'step', 'lw': 2}
#hist_settings = {'bins': 50, 'normed': True, 'alpha': 0.8, 'histtype': 'step', 'lw': 2}

def get_pdsdata(
        in_file, in_tree, in_cut, in_column, in_weight
        ):
    # Read data samples
    in_rdf = rt.RDataFrame( in_tree, in_file )
    # in_rdf = in_rdf.Define("fmin_piplus_piminus", "fmin(piplus_PT, piminus_PT)")
    # in_rdf = in_rdf.Define("fmin_muminus_muplus", "fmin(muminus_MINIP, muplus_MINIP)")
    # Transform samples to arrays 
    in_var = in_column
    if in_weight != '' : in_var = in_column+[in_weight]

    if in_cut =='' : 
        in_data = in_rdf.AsNumpy( in_var )
    else: 
        in_data = in_rdf.Filter( in_cut ).AsNumpy( in_var )

    in_data = pandas.DataFrame(in_data)

    return in_data 

def get_dataw( in_data, in_weight ):
    if in_weight=="":
        dataw = np.ones(len(in_data))
    else:
        dataw = in_data[in_weight]
    return dataw

def gbWeight(
      columns, nEstimators, Rate, nDepth, 
      origin_file, origin_tree, origin_cut, origin_w, 
      target_file, target_tree, target_cut, target_w, 
      wgtcor_file, wgtcor_tree, wgtcor_cut, wgtcor_w,  
      output_file, output_tree, 
      output_gbw, nrow, ncol, picname  
      ):
 
    # Fix ~/ as home path
    if "~/" in origin_file: origin_file = origin_file.replace("~", os.getenv("HOME"))
    if "~/" in target_file: target_file = target_file.replace("~", os.getenv("HOME"))
    if "~/" in wgtcor_file: wgtcor_file = wgtcor_file.replace("~", os.getenv("HOME"))
    if "~/" in output_file: output_file = output_file.replace("~", os.getenv("HOME"))

    print("----------------------------------------")
    print( columns )
    print("origin file : ", origin_file)
    print("target file : ", target_file)
    print("wgtcor file : ", wgtcor_file)
    print("output file : ", output_file)
    #print("tmpwgt file : ", tmpwgt_file)
    print("origin cut : ", origin_cut)
    print("target cut : ", target_cut)
    print("wgtcor cut : ", wgtcor_cut)
    print("----------------------------------------")

    # Do not use this function which causes a bug at present
    # Enable ROOT's implicit multi-threading
    # rt.EnableImplicitMT()
    
    origin_all = get_pdsdata( origin_file, origin_tree, origin_cut, columns, origin_w )
    target_all = get_pdsdata( target_file, target_tree, target_cut, columns, target_w )
    wgtcor_all = get_pdsdata( wgtcor_file, wgtcor_tree, wgtcor_cut, columns, wgtcor_w )

    origin = origin_all[columns]
    target = target_all[columns]
    wgtcor = wgtcor_all[columns]

    origin_sw = get_dataw( origin_all, origin_w )
    target_sw = get_dataw( target_all, target_w )
    wgtcor_sw = get_dataw( wgtcor_all, wgtcor_w )

    #print( type(origin_all)," ",type(origin)," ",type(origin_sw) )
    
    # Perform reweighting
    reweighter = reweight.GBReweighter(
        n_estimators=nEstimators, learning_rate=Rate, max_depth=nDepth, 
        min_samples_leaf=1000, gb_args={'subsample': 0.6} )
    reweighter.fit( origin, target, original_weight=origin_sw, target_weight=target_sw )
    gb_weights = reweighter.predict_weights( wgtcor, wgtcor_sw )
    
    # Save weights to a tmp file
    tmpwgt_file = output_file.split(".root")[0] +"_tmpweight.root"

    #columns.append( output_gbw )
    origin.update
    with ur.recreate( tmpwgt_file ) as gbwfile:
        gbwfile[origin_tree] = {output_gbw:gb_weights}

    # Add weights to original file
    add_weight_byChain( 
      wgtcor_file+"/"+wgtcor_tree, tmpwgt_file+"/"+wgtcor_tree, 
      wgtcor_cut, output_gbw, output_gbw, output_file, output_tree  )

    #add_weight_byRDF(
    #    origin_file, origin_tree, origin_cut, 
    #    output_file, output_tree, tmpwgt_file )
    
    os.system( "rm %s" %(tmpwgt_file) )

    #add_weight_byTree( wgtcor_file, wgtcor_tree, wgtcor_cut, gb_weights, output_file, output_gbw )

    # Draw plots
    def draw_distributions( wgtcor_weights, gb_weights, name, i):
        (fig, ax) = plt.subplots( nrows=nrow, ncols=ncol, figsize = (20,20) )
        for id, column in enumerate(columns, 0):
            print (id)
            i = int(id / 2)
            j = int(id % 2)

            xlim = np.percentile(np.hstack([target_all[column]]), [0.01, 99.9])
            data = wgtcor_all[column]
            ax[i,j].hist(data, weights=wgtcor_weights, range=xlim,  label="Origin", **hist_settings)
            ax[i,j].hist(target_all[column], weights=target_sw, range=xlim, label="Target", **hist_settings)
            ax[i,j].hist(data, weights=gb_weights, range=xlim,  label="GB Weighted", **hist_settings)
            ax[i,j].set_title(column)
            legend = ax[i,j].legend(loc='upper right')
            print ( 'KS std', column, ' = ', ks_2samp_weighted(data, target_all[column],
                  weights1=wgtcor_weights, weights2=target_sw) )
            print ( 'KS GB ', column, ' = ', ks_2samp_weighted(data, target_all[column],
                  weights1=gb_weights, weights2=target_sw) )
            fig.savefig(name)
    draw_distributions( wgtcor_sw, gb_weights, picname, 3 )
'''
'''
