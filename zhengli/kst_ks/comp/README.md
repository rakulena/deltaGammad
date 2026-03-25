This program calculates time acceptance using the formula 1./exp(-1/1.519*Bd_ConstJpsi_tau) to evaluate the impact of different BDT cuts on the acceptance.It is divided into Bd2JpsiKstar and Bd2JpsiKshort.
Bd2JpsiKstar:hist_comp_accp_mva_kst.C
Bd2JpsiKshort:hist_comp_accp_mva_ks.C

# Step

- 1.Modify hist_comp_accp_mva_kst.C/hist_comp_accp_mva_ks.C

Edit intree1,cut1,tpoint,selcut1 and so on

- 2.Run hist_comp_accp_mva_kst.C/hist_comp_accp_mva_ks.C

Example:root -l hist_comp_accp_mva_kst.C

root -l hist_comp_accp_mva_ks.C
