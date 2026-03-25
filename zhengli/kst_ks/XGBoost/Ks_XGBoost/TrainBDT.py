import numpy as np
import uproot
import xgboost as xgb
from xgboost import XGBClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import roc_auc_score, roc_curve
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import pandas as pd
import argparse
import seaborn as sn
import os
import sys
import json
from lhcbstyle import LHCbStyle
LHCbStyle()
 
parser = argparse.ArgumentParser()

parser.add_argument('-m', action='store',
                    dest='MCFiles', nargs="+",
                    help='MC Input tuple')

parser.add_argument('-d', action='store',
                    dest='DataFiles', nargs="+",
                    help='Data Input tuple')

parser.add_argument('-j', action='store',
                    dest='JsonFile',
                    help='Json file for configuration')

parser.add_argument('-s', action='store',
                    dest='SelJsonFile',
                    help='Json file for selection')

parser.add_argument('-o', action='store',
                    default='', nargs="+",
                    dest='OutputFiles',
                    help='Output File with for the BDT model')

parser.add_argument('-p', action='store',
                    default='',
                    dest='PlotDir',
                    help='Output Directory for plotting')

parser.add_argument('-l', action='store',
                    default='',
                    dest='LumiJsonFile',
                    help='Json file with the luminosity information')

options = parser.parse_args()

def plot_loss(evals, saveDir, n):
    fig = plt.figure()
    train_metric = evals['validation_0']['logloss']
    plt.plot(train_metric, label='train logloss')
    eval_metric = evals['validation_1']['logloss']
    plt.plot(eval_metric, label='eval logloss')
    plt.grid()
    plt.legend()
    plt.xlabel('rounds')
    plt.ylabel('logloss')
    decay = jInfo["decay"]
    fig.savefig(f"{saveDir}/{decay}_loss{n}.png")

def plot_importance(bst, var, saveDir, n):
    bst.get_booster().feature_names = var
    ax = xgb.plot_importance(bst)
    ax.figure.subplots_adjust(left=0.4)
    decay = jInfo["decay"]
    ax.figure.savefig(f"{saveDir}/{decay}_importance{n}.png")

def plot_roc(y_true, y_score, saveDir, n):
    fpr, tpr, threshold = roc_curve(y_true=y_true, y_score=y_score)
    fig = plt.figure()
    plt.plot(fpr, tpr)
    plt.xlim([-0.05, 1.0])
    plt.ylim([0.0, 1.05])
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('ROC curve')
    decay = jInfo["decay"]
    fig.savefig(f"{saveDir}/{decay}_ROC{n}.png")
    roc_data = np.column_stack((fpr, tpr))
    np.savetxt(f"{saveDir}/{decay}_ROC_data{n}.txt", roc_data, header="FPR TPR", fmt='%.6f')

def plot_train_test(y_pred_train, y_train, y_pred, y_test, saveDir, n, high_low=(0, 1), bins=30):
    fig = plt.figure()
    plt.hist(y_pred_train[y_train == 0],
             color='r', alpha=0.5, range=high_low, bins=bins,
             histtype='stepfilled', density=True,
             label='B (train)')
    plt.hist(y_pred_train[y_train == 1],
             color='b', alpha=0.5, range=high_low, bins=bins,
             histtype='stepfilled', density=True,
             label='S (train)')

    hist, bins = np.histogram(y_pred[y_test == 0],
                              bins=bins, range=high_low, density=True)
    scale = len(y_pred[y_test == 0]) / sum(hist)
    err = np.sqrt(hist * scale) / scale

    center = (bins[:-1] + bins[1:]) / 2
    plt.errorbar(center, hist, yerr=err, fmt='o', c='r', label='B (test)')

    hist, bins = np.histogram(y_pred[y_test == 1],
                              bins=bins, range=high_low, density=True)
    scale = len(y_pred[y_test == 1]) / sum(hist)
    err = np.sqrt(hist * scale) / scale

    center = (bins[:-1] + bins[1:]) / 2
    plt.errorbar(center, hist, yerr=err, fmt='o', c='b', label='S (test)')

    plt.title('XGBoost')
    plt.xlabel('XGBoost score')
    plt.ylabel('Arbitrary units')
    plt.legend(loc='best')
    #plt.yscale('log')
    decay = jInfo["decay"]
    fig.savefig(f"{saveDir}/{decay}_train_test{n}.png")
    plt.yscale("log")
    fig.savefig(f"{saveDir}/{decay}_train_test{n}_log.png")
    fig.clear()

def TrainSplit(dataset, param, fold):
    # Create a subdataset with (rndNumber == kfold)
    subdataset = dataset.query(f"rndNumber != {fold}", engine='python')
    #subdataset = dataset[dataset.rndNumber != fold]
    # For X removes catlabel and rndNumber
    X = subdataset.drop(labels=["rndNumber", "label", "gbw"], axis=1)
    y = subdataset["label"].astype(int)
    w = subdataset["gbw"]
    print("X shape", X.shape, "y shape", y.shape,"w shape", w.shape)
    X_train, X_test, y_train, y_test, ws_train, ws_test = train_test_split(X, y, w, test_size=0.25, random_state=0, stratify=y)
    catCount = y.value_counts()  # [Number of zeroes (bkg events), Number of ones (signal events)]
    print(catCount)
    pos_weight = float(1.0 * catCount[0] / catCount[1])
    print("pos_weight:", pos_weight)
    bst = XGBClassifier(**param, tree_method='hist', objective='binary:logistic', use_label_encoder=False, scale_pos_weight=pos_weight, n_jobs=20, eval_metric='logloss')
    print("Starting training")
    bst.fit(X_train, y_train, sample_weight=ws_train,
            eval_set=[(X_train, y_train), (X_test, y_test)],
            verbose=False)

    preds_test = bst.predict_proba(X_test)[:, 1]
    preds_train = bst.predict_proba(X_train)[:, 1]
    auc_test = roc_auc_score(y_true=y_test, y_score=preds_test)
    auc_train = roc_auc_score(y_true=y_train, y_score=preds_train)
    print(f'auc_test{fold+1}:', auc_test)
    print(f'auc_train{fold+1}:', auc_train)

    if True:
        #saveDir = f"{workDir}/fig/{run}" #workDir + '/fig/D2' + mode + '_' + run
        #os.makedirs(saveDir, exist_ok=True)
        plot_loss(evals=bst.evals_result(), saveDir=options.PlotDir, n=fold + 1)
        plot_importance(bst=bst, var=jInfo["BDT_vars"], saveDir=options.PlotDir, n=fold + 1)
        plot_roc(y_true=y_test, y_score=preds_test, saveDir=options.PlotDir, n=fold + 1)
        plot_train_test(preds_train, y_train, preds_test, y_test, saveDir=options.PlotDir, n=fold + 1)

    return bst

with open(options.JsonFile) as fInfo:
    jInfo = json.load(fInfo)

with open(options.SelJsonFile) as fSel:
    jSel = json.load(fSel)

with open(options.LumiJsonFile) as fLumi:
    jLumi = json.load(fLumi)

def GetYearPol(FileName):
    years = ["2016", "2017", "2018"]
    pols = ["MagUp", "MagDown", "magud"]
    magnet = year = None
    for yr in years:
        if yr in FileName:
            year = yr
            break
    for pol in pols:
        if pol in FileName:
            magnet = pol
            break
    if magnet and year:
        return year, magnet
    sys.exit(f"ERROR: Year and Magnet polarity not identifed from {FileName}")

kfolds = len(options.OutputFiles)
vars = jInfo["BDT_vars"] + ["rndNumber", "gbw", "BKGCAT"]
alias = {'rndNumber': '(runNumber + eventNumber)%{0}'.format(kfolds),
         'BKGCAT' : jSel["MC"].replace("||", "|").replace("&&", "&")}

#vars += ["hplus_TRACK_Type", "Xipi_TRACK_Type"]
print("Loading signal (MC)")
sig = uproot.concatenate(files=options.MCFiles, expressions=vars, aliases = alias, library="pd")

# Concatenate the MC files with a weight according to their luminosity
#sig_pds = []
#for FileName in options.MCFiles:
#    sig_pds.append(uproot.concatenate(files=FileName, expressions=vars, aliases = alias, library="pd"))
#    year, magnet = GetYearPol(FileName)
#    sig_pds[-1]["gbw"] *= jLumi[year][magnet]
#sig = pd.concat(sig_pds)

#sig["gbw"] = sig["gbw"]*sig["wLumi"]

vars.remove("gbw")
vars.remove("BKGCAT")
#RemoveSubEntries(sig)
sig["label"] = 1
sig.query("BKGCAT==1", inplace=True)
sig.drop("BKGCAT", axis=1, inplace=True)

print("Loading background (data)")
mass_var = "{mother}_ConstJpsi_M".format(mother=jInfo["mother"])#massvar
bkgcut = "(({mass_var} > {min_mass}) & ({mass_var} < {max_mass})) |(({mass_var}<{max_mass_left}) & ({mass_var}>{min_mass_left}))".format(
    mass_var = mass_var, min_mass = jInfo["bkg_range_right"][0], max_mass = jInfo["bkg_range_right"][1],
    min_mass_left = jInfo["bkg_range_left"][0], max_mass_left= jInfo["bkg_range_left"][1]
)
#bg = uproot.concatenate(files=options.DataFiles, expressions=vars, aliases = alias, cut=bkgcut, library="pd")
bg = uproot.concatenate(files=options.DataFiles, expressions=vars+[mass_var], aliases = alias, library="pd")
bg.query(bkgcut, inplace=True)
bg.drop(mass_var, axis=1, inplace=True)
print(bg)
#RemoveSubEntries(bg)
bg["label"] = 0
bg["gbw"] = 1.0

os.makedirs(options.PlotDir, exist_ok=True)
decay = jInfo["decay"]

# Plot the distribution of variables for signal and background
for feature in bg.columns[:-3]:  # Exclude the 'label', 'gbw' and 'rndNumber' columns
    #plt.figure(figsize=(8, 6))
    fig = plt.figure()
    sig[feature] = sig[feature].fillna(0)
    bg[feature] = bg[feature].fillna(0)
    print(sig[feature], bg[feature])
    maxrange = np.quantile(np.hstack([sig[feature], bg[feature]]), 0.97)
    print("Max range:", maxrange)
    bins = np.histogram(np.hstack([sig[feature], bg[feature]]), bins=30, range=(0, maxrange))[1]
    plt.hist(sig[feature], bins=bins, alpha=0.5, label='Signal', weights=sig["gbw"], density=True, color='blue')
    plt.hist(bg[feature], bins=bins, alpha=0.5, label='Background', density=True, color='orange')
    #plt.title(f'Distribution of {feature} for Signal and Background')
    plt.xlabel(feature)
    plt.ylabel('Frequency')
    plt.legend(loc='best')
    fig.savefig(f"{options.PlotDir}/{decay}_{feature}.png")

if True:
    fig, ax = plt.subplots(figsize=(9, 8))
    fig.subplots_adjust(bottom=0.28)
    fig.subplots_adjust(left=0.25)
    fig.subplots_adjust(right=1.)
    sn.set(font_scale=0.7)
    sn.heatmap(bg.drop(["gbw", "label", "rndNumber"], axis=1).corr(), ax=ax, center=0, vmin=-1.0, vmax=1.0, annot=True, fmt='.2f', cmap='bwr', linewidth=.2,cbar_kws={"format": "%.2f"})
    ax.set_title('Correlations - background', fontsize=15)
    fig.savefig(options.PlotDir + f"/{decay}_corr_bg_final.png")
    fig, ax = plt.subplots(figsize=(9, 8))
    fig.subplots_adjust(bottom=0.28)
    fig.subplots_adjust(left=0.25)
    fig.subplots_adjust(right=1.)
    sn.set(font_scale=0.7)
    sn.heatmap(sig.drop(["gbw", "label", "rndNumber"], axis=1).corr(), ax=ax, center=0, vmin=-1.0, vmax=1.0, annot=True, fmt='.2f', cmap='bwr', linewidth=.2,cbar_kws={"format": "%.2f"})
    ax.set_title('Correlations - signal', fontsize=15)
    fig.savefig(options.PlotDir + f'/{decay}_corr_sig_final.png')

print('Background nentry:', bg.shape)
print('Signal nentry:    ', sig.shape)

dataset = pd.concat([sig, bg])

# Remove rndNumber as this is not a feature
#var = var[:-1]
# np.random.shuffle(dataset)

"""
num_round = args.ntree
eta = args.eta

param = {
    'max_depth': 3,
    'subsample': 0.6,
    'colsample_bytree': 1,
    'reg_lambda': 1,
    'reg_alpha': 10,
    'min_child_weight': 1,
    'gamma': 5
}
"""

bst_array = []
os.makedirs(os.path.dirname(options.OutputFiles[0]), exist_ok=True)
for ii, OutputFile in enumerate(options.OutputFiles):
    print(f"Training BDT {ii+1} out of {kfolds}")
    bst_array.append(TrainSplit(dataset, jInfo["BDT_conf"], ii))
    bst_array[ii].save_model(OutputFile)
    plt.close('all')
