This repository is used to measure the uncertainty of ΔΓ_d through simultaneous fitting using the Bd → J/ψ K* and Bd → J/ψ Ks0 (signal) decay modes, along with the B+ → J/ψ K⁺ (control) decay mode.

## Struction 

- kst_ks: Suppresses background events. Includes preselection, sWeight calculation via mass fit, MC kinematic correction using GB Reweighting, MVA with XGBoost, optimal BDT cut selection based on figure of merit, and final application of the BDT cut.

- dgd: Extracts the time acceptance function using triple spline from signal and control samples with fixed τ, then determines ΔΓ_d with the fixed time acceptance after accounting for CP violation effects.

- makeHeadfile: Required header files for compilation.

## Enviroment

- 'source /cvmfs/sft.cern.ch/lcg/releases/LCG_102b/ROOT/6.26.08/x86_64-centos9-gcc11-opt/ROOT-env.sh'

- 'lb-conda default/2024-07-10'
  for gbweight and XGBoost'— required for GB Reweighting and XGBoost (not needed if packages are already installed)
