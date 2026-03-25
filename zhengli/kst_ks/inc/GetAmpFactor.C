
Double_t getpR(double m_k,double m_x)
{
   return sqrt(m_x*m_x-4*m_k*m_k)/2.;
}

Double_t getpB(double m_b,double m_jpsi,double m_x)
{
   double m2_b = m_b*m_b;
   return sqrt((m2_b-(m_jpsi+m_x)*(m_jpsi+m_x))*(m2_b-(m_jpsi-m_x)*(m_jpsi-m_x)))/2./m_b;
}

//Blatt-Weisskopf form factors
Double_t getFBW(double r, int L, double p, double p0)
{
   double z = pow(r*p,2);
   double z0 = pow(r*p0,2);
   if(L==0) return 1.0;
   if(L==1) return sqrt((1.+z0)/(1.+z));
   if(L==2) return sqrt((z0*z0+3*z0+9.)/(z*z+3*z+9.));
   if(L==3) return sqrt((z0*z0*z0+6*z0*z0+45*z0+225)/(z*z*z+6*z*z+45*z+225));
   return 1.0;
}

