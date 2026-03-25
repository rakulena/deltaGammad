
//double m_B  = 5.27950;
double m_B  = 5.2795801;
double m_pi  = 0.13957061;
double m_jpsi = 3.096900;
double m2_bs = m_B*m_B;
double m2_pi = m_pi*m_pi;
double m2_jpsi = m_jpsi*m_jpsi;

double getpB(double mpp)
{
   return sqrt((m2_bs-(m_jpsi+mpp)*(m_jpsi+mpp))*(m2_bs-(m_jpsi-mpp)*(m_jpsi-mpp)))/2./m_B;
}

double getpR(double mpp)
{
   return sqrt(mpp*mpp-4*m2_pi)/2.;
}

Double_t phsp(double mpp)
{
   if(mpp<2*m_pi) return 0.;
   if(mpp>m_B-m_jpsi) return 0.;
   return 1./getpB(mpp)/getpR(mpp);
}

bool kine_limits(double mpp)
{
   if(mpp<2*m_pi) return false;
   if(mpp>m_B-m_jpsi) return false;
   return true;
}

