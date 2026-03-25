import numpy as np
import uproot
from xgboost import XGBClassifier
import os
import json
import argparse

parser = argparse.ArgumentParser(description="Applies a BDT", formatter_class=argparse.ArgumentDefaultsHelpFormatter)

parser.add_argument('-i', '--InputFile', type=str, default='', help='input file')
parser.add_argument('-o', '--OutputFile', type=str, default='', help='output file')
parser.add_argument('-j', action='store', dest='JsonFile', help='Json file for configuration')
parser.add_argument('-b', '--BDTModels', nargs="+", default="", help='BDT Models generated during training')

options = parser.parse_args()

with open(options.JsonFile) as fInfo:
    jInfo = json.load(fInfo)

kfolds = len(options.BDTModels)

print('Predicting probability for ' + options.InputFile)

def load_data(input_file):
    try:
        tree = uproot.open(input_file, timeout=600)["DecayTree"]
    except Exception:
        print("WARNING: DecayTree not read, copying it to local")
        temp_file = input_file.replace(".root", "_Temp.root")
        os.system(f"xrdcp {input_file} {temp_file}")
        tree = uproot.open(temp_file, timeout=1200)["DecayTree"]
        os.remove(temp_file)

    all_vars = tree.keys()
    data = tree.arrays(expressions=all_vars, library="pd")
    data['rndNumber'] = (data['runNumber'] + data['eventNumber']) % kfolds
    return data

data = load_data(options.InputFile)
datanentry = data.shape[0]

if datanentry:
    preds = np.zeros([kfolds, datanentry])
    rndNumbers = data["rndNumber"].to_numpy()
    tdata = data[jInfo["BDT_vars"]]
    
    for ii, BDTModel in enumerate(options.BDTModels):
        bst = XGBClassifier()
        bst.load_model(BDTModel)
        preds[ii] = bst.predict_proba(tdata)[:, 1]
    
    good_pred = np.zeros(datanentry)
    for i in range(datanentry):
        good_pred[i] = preds[rndNumbers[i]][i]
else:
    good_pred = []

outdir = os.path.dirname(options.OutputFile)
os.makedirs(outdir, exist_ok=True)

with uproot.recreate(options.OutputFile) as f:
    print('Creating BDT response branch for ' + options.OutputFile)
    data['BDT'] = good_pred
    f["DecayTree"] = data
