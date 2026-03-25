
// Combine the raw tag
void CombineRawTag(
	int tagos_dec,
	int tagss_dec,
	double tagos_eta,
	double tagss_eta,
	int &tag_dec,
	double &tag_eta
	){
   
   if( tagos_dec==0 && tagss_dec==0 ){
	tag_dec = 0;
	tag_eta = 0.5;
   }
   if( tagos_dec!=0 && tagss_dec==0 ){
	tag_dec = tagos_dec;
	tag_eta = tagos_eta;
   }
   if( tagos_dec==0 && tagss_dec!=0 ){
	tag_dec = tagss_dec;
	tag_eta = tagss_eta;
   }
   
   if( tagos_dec*tagss_dec!=0 ){

	if( tagos_dec == tagss_dec ){
	   tag_dec = tagos_dec;
	   tag_eta = tagos_eta*tagss_eta/(tagos_eta*tagss_eta+(1.-tagos_eta)*(1.-tagss_eta));
	}else{
	   if( tagos_eta < tagss_eta ){
		tag_dec = tagos_dec;
		tag_eta = tagos_eta*(1.-tagss_eta)/(tagos_eta*(1.-tagss_eta)+(1.-tagos_eta)*tagss_eta);
	   }else{
		tag_dec = tagss_dec;
		tag_eta = tagss_eta*(1.-tagos_eta)/(tagos_eta*(1.-tagss_eta)+(1.-tagos_eta)*tagss_eta);
	   }

	}
   }


}

// Calibrate raw eta
double CaliTag(
	double eta,
	double aveta,
	double p0,
	double p1
	)
{
   double omega = p0+p1*(eta-aveta);
   return omega;
}

// Combine the calibrated taggers
void CombineCaliTag(
	int tagos_dec,
	int tagss_dec,
	double tagos_eta,
	double tagss_eta,
	double pos[5], // aveta_os, p0_os, p1_os, dp0_os, dp1_os
	double pss[5], // aveta_ss, p0_ss, p1_ss, dp0_ss, dp1_ss
	int &tag_dec,
	double &avgMistag,
	double &delMistag
	)
{
   if( tagos_dec==0 && tagss_dec==0 ){
	tag_dec = 0;
	avgMistag = 0.5;
	delMistag = 0.0;
   }
   if( tagos_dec!=0 && tagss_dec == 0 ){
	tag_dec = tagos_dec;
	avgMistag = CaliTag( tagos_eta, pos[0], pos[1], pos[2] );
	delMistag = CaliTag( tagos_eta, pos[0], pos[3], pos[4] );
   }
   if( tagos_dec==0 && tagss_dec != 0 ){
	tag_dec = tagss_dec;
	avgMistag = CaliTag( tagss_eta, pss[0], pss[1], pss[2] );
	delMistag = CaliTag( tagss_eta, pss[0], pss[3], pss[4] );
   }
   if( tagos_dec*tagss_dec != 0 ){
	double mistag1= CaliTag( tagos_eta, pos[0], pos[1], pos[2] );
	double mistag2= CaliTag( tagss_eta, pss[0], pss[1], pss[2] );
	double dw1= CaliTag( tagos_eta, pos[0], pos[3], pos[4] );
	double dw2= CaliTag( tagss_eta, pss[0], pss[3], pss[4] );

	double wp1 = mistag1 +dw1/2.;
	double wp2 = mistag2 +dw2/2.;
	double wm1 = mistag1 -dw1/2.;
	double wm2 = mistag2 -dw2/2.;

	double cbwp,cbwm;
	if( tagos_dec == tagss_dec ){
	   tag_dec = tagos_dec;
	   cbwp = wp1*wp2/(wp1*wp2+(1.-wp1)*(1.-wp2));
	   cbwm = wm1*wm2/(wm1*wm2+(1.-wm1)*(1.-wm2));

	}else{
	   if( mistag1 < mistag2 ){
		tag_dec = tagos_dec;
		cbwp = wp1*(1.-wp2)/(wp1*(1.-wp2)+(1.-wp1)*wp2);
		cbwm = wm1*(1.-wm2)/(wm1*(1.-wm2)+(1.-wm1)*wm2);

	   }else{
		tag_dec = tagss_dec;
		cbwp = wp2*(1.-wp1)/(wp1*(1.-wp2)+(1.-wp1)*wp2);
		cbwm = wm2*(1.-wm1)/(wm1*(1.-wm2)+(1.-wm1)*wm2);
	   }

	}
	avgMistag = (cbwp+cbwm)/2.;
	delMistag = cbwp-cbwm;

	if( avgMistag>0.5 ){
	   avgMistag = 1-avgMistag;
	   tag_dec = -1*tag_dec;
	}
   }

}
