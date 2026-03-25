## Intruoduction

This program trains BDT classifiers using XGBoost to distinguish signal from background events, aiming to find the optimal BDT cut by maximizing the figure of merit (F.O.M). The analysis is divided into two channels

Bd2JpsiKstar:Kst_XGBoost

Bd2JpsiKshort:Ks_XGBoost

# Step(exampled as Bd2JpsiKstar)

- 1.Set enviroment configuration
  
Example:lb-conda default/2024-07-10 

or use other compatible environment configurations that can execute the code.

- 2.Modify Bd2JpsiKstar.json,lumi.json and ./Selection/Bd2JpsiKstar.json
  
Bd2JpsiKstar.json:signal_range,bkg_range,BDT_vars,BDT_conf

lumi.json:luminance in the different years

./Selection/Bd2JpsiKstar.json:Bd_BKGCAT and so on

- 3.Modify run_trainBDT.sh
  
Edit the input path and output path

- 4.Execute run_trainBDT.sh

- 5.Modify rundata_applyBDT.sh and runmc_applyBDT.sh
  
Edit the input path and output path

- 6.Execute rundata_applyBDT.sh and runmc_applyBDT.sh

- 7.Modify and execute fom.C to calculate F.O.M and get optimal BDT cut

