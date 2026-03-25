# Intruoduction

This repository is used to measure the uncertainty of deltaGammad through simultaneous fitting using the Bd2JpsiKstar and Bd2JpsiKshort (signal) decay modes, along with the Bu2JpsiKplus (control) decay mode.

## Structure

- kst_ks: Suppresses background events.
  1. get_root: preselection,
  2. massfit\presel_ks (or presel_kst): sWeight calculation via mass fit,
  3. gbweight: MC kinematic correction using GB Reweighting,
  4. XGBoost: MVA with XGBoost, optimal BDT cut selection based on figure of merit,
  5. massfit\fulsel_ks (or fulsel_kst): final application of the BDT cut,
  6. comp: check time bias on BDT with the time acceptance.

- dgd: Extracts the time acceptance function using triple spline from signal and control samples with fixed τ, then determines ΔΓ_d with the fixed time acceptance after accounting for CP violation effects.

- makeHeadfile: Required header files for compilation.

## Enviroment

- 'source /cvmfs/sft.cern.ch/lcg/releases/LCG_102b/ROOT/6.26.08/x86_64-centos9-gcc11-opt/ROOT-env.sh'

- 'lb-conda default/2024-07-10'
  only for gbweight and XGBoost'— required for GB Reweighting and XGBoost (not needed if packages are already installed)
