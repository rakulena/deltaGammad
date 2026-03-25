import ROOT as rt
#import numpy as np
#import uproot as ur
from array import array


# Add weight to original using TChain
# Seems this method is stabler than TTree
def add_weight_byChain(
	aimtree, wgttree, treecut,
	wgtname, outname, 
        outroot, outtree
	):
   
   print ("--------------------------------------")
   print (" Input tree1   :", aimtree ) 
   print (" Input tree2   :", wgttree ) 
   print (" Tree  cut     :", treecut ) 
   print (" Input weight  :", wgtname ) 
   print (" Output weight :", outname ) 
   print (" Output root   :", outroot ) 
   print (" Output tree   :", outtree ) 
   print ("--------------------------------------")
   
   chain1 = rt.TChain()
   chain2 = rt.TChain()
   chain1.Add( aimtree )
   chain2.Add( wgttree )
   
   if( chain1.GetEntries(treecut) != chain2.GetEntries() ) :
      print ( "--------------------------------------" ) 
      print ( " The number of events is not matched  " )
      print ( "--------------------------------------" )
      return 0
   else :
      print ( "--------------------------------------" ) 
      print ( " The number of events is matched      " )
      print ( "--------------------------------------" )
   
   seltree = rt.TTree();
   if( treecut!='' and chain1.GetEntries()!=chain1.GetEntries(treecut) ):
      seltree = chain1.CopyTree( treecut )
   else:
      seltree = chain1
   
   wgt = array('d',[0])
   chain2.SetBranchAddress( wgtname, wgt )
   
   newfile = rt.TFile( outroot, "recreate" )
   newtree = chain1.CloneTree(0)
   newtree.SetName( outtree )
   newtree.Branch(outname, wgt, outname+"/D")
   
   for i in range(0,chain2.GetEntries()):
      if( i%50000 == 0 ) : print ( ' Processing {0} k events. '.format(str(i/1000)) )
      seltree.GetEntry(i)
      chain2.GetEntry(i)
      newtree.Fill()
   
   newfile.cd()
   newtree.Write()
   newfile.Close()


# Add weight to original tuple using RDataFrame
def add_weight_byRDF(
        origin_file, origin_tree, origin_cut, 
        output_file, output_tree, weight_file 
        ):

    # Do not change the orders of following codes
    file_gbw = rt.TFile( weight_file )
    file_ori = rt.TFile( origin_file )

    tree_gbw = file_gbw.Get( origin_tree )
    tree_ori = file_ori.Get( origin_tree )

    if origin_cut != 0: tree_ori = tree_ori.CopyTree( origin_cut )

    tree_ori.ResetBit(rt.TTree.EStatusBits.kEntriesReshuffled)
    tree_gbw.AddFriend(tree_ori)
    dataframe = rt.RDataFrame(tree_gbw)

    dataframe.Snapshot( output_tree, output_file )
    file_gbw.Close()
    file_ori.Close()


# Add weight to original using TTree
def add_weight_byTree(
        origin_file, origin_tree, origin_cut, 
        gb_weights, output_file, outgbw 
        ):
    intree = rt.TChain()
    intree.Add( origin_file+'/'+origin_tree )
    #infile = rt.TFile( origin_file )
    #intree = infile.Get( origin_tree )

    seltree = intree
    if( origin_cut!='' and intree.GetEntries()!=intree.GetEntries( origin_cut ) ):
        seltree = intree.CopyTree( origin_cut )

    if( seltree.GetEntries() == len(gb_weights) ):
        print( "----------------------------------" )
        print( " The number of events is matched. " )
        print( "----------------------------------" )
    else:
        print( "--------------------------------------" )
        print( " The number of events is not matched. " )
        print( "--------------------------------------" )
        return

    newfile = rt.TFile( output_file, "recreate" )
    #newtree = seltree.CloneTree(0)

    wgt = array('d',[0])
    br_wgt = seltree.Branch( outgbw, wgt, outgbw+"/D" )
    #newtree.Branch( outgbw, wgt, outgbw+"/D" )

    for i in range( 0, len(gb_weights) ):
        if( i%50000 == 0 ) : print ( ' Processing {0} k events. '.format(str(i/1000)) )
        wgt[0] = gb_weights[i]
        br_wgt.Fill()
        #seltree.GetEntry(i)
        #newtree.Fill()

    newfile.cd()
    seltree.Write()
    newfile.Close()

#def add_weight_byUproot(
#        origin_file, origin_tree, origin_cut, gb_weights,
#        out_columns, outgbw, output_file 
#        ):
#    intree = ur.open( origin_file )[origin_tree]
#    dict_ary = {}
#
#    if origin_cut=='':
#        dict_ary = intree.arrays( out_columns, library="np" )
#    else:
#        dict_ary = intree.arrays( out_columns, origin_cut, library="np" )
#
#    if( len(gb_weights) == len(dict_ary[ origin_columns[0] ]) ):
#        print( " The number of events are matched! " )
#
#        # Add weight to dict
#        dict_ary.update( {outgbw:gb_weights} )
#
#        # Write final data to a new file which is automatically closed
#        with ur.recreate( output_file ) as newfile:
#            newfile[output_tree] = dict_ary
#    else:
#        print( " The number of events are not matched! " )

