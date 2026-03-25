#include "MyKMatrix.h"
#include <math.h>
#include "Riostream.h"
#include "TComplex.h"
#include "Math/SMatrix.h"
#include "Math/SVector.h"

typedef ROOT::Math::SMatrix<double,5> SMatrix55;
typedef ROOT::Math::SMatrix<double,4> SMatrix44;
typedef ROOT::Math::SMatrix<double,3> SMatrix33;
typedef ROOT::Math::SMatrix<double,2> SMatrix22;
typedef ROOT::Math::SVector<double,2> SVector2;
typedef ROOT::Math::SVector<double,3> SVector3;
typedef ROOT::Math::SVector<double,4> SVector4;
typedef ROOT::Math::SVector<double,5> SVector5;

using namespace std;

void MyKMatrix::SetValues()
{
  m_alpha[0] = 0.65100;
  m_alpha[1] = 1.20360;
  m_alpha[2] = 1.55817;
  m_alpha[3] = 1.21000;
  m_alpha[4] = 1.82206;

  //pipi
  g_alpha[0][0] = 0.22889;
  g_alpha[0][1] = 0.94128;
  g_alpha[0][2] = 0.36856;
  g_alpha[0][3] = 0.33650;
  g_alpha[0][4] = 0.18171;
   
  //kk
  g_alpha[1][0] = -0.55377;
  g_alpha[1][1] = 0.55095;
  g_alpha[1][2] = 0.23888;
  g_alpha[1][3] = 0.40907;
  g_alpha[1][4] = -0.17558;
   
  //4pi
  g_alpha[2][0] = 0.0000;
  g_alpha[2][1] = 0.0000;
  g_alpha[2][2] = 0.55639;
  g_alpha[2][3] = 0.85679;
  g_alpha[2][4] = -0.79658;
  
  //eta tea
  g_alpha[3][0] = -0.39899;
  g_alpha[3][1] = 0.39065;
  g_alpha[3][2] = 0.18340;
  g_alpha[3][3] = 0.19906;
  g_alpha[3][4] = -0.00355;
  
  //eta eta'
  g_alpha[4][0] = -0.34639;
  g_alpha[4][1] = 0.31503;
  g_alpha[4][2] = 0.18681;
  g_alpha[4][3] = -0.00984;
  g_alpha[4][4] = 0.22358;

  //scat
  f_scat[0][0] = 0.23399;
  f_scat[0][1] = 0.15044;
  f_scat[0][2] = -0.20545;
  f_scat[0][3] = 0.32825;
  f_scat[0][4] = 0.35412;
  
  f_scat[1][0] = 0.15044;
  f_scat[2][0] = -0.20545;
  f_scat[3][0] = 0.32825;
  f_scat[4][0] = 0.35412;

  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      if(i!=0 && j!=0) f_scat[i][j] = 0;
    }
  }

  m_pi2 = m_pi*m_pi;
  m_k2 = m_k*m_k;
  m_eta2 = m_eta*m_eta;
  m_etap2 = (m_eta + m_etap)*(m_eta + m_etap);
  for(int i=0;i<5;i++){
    m_alpha2[i] = m_alpha[i]*m_alpha[i];
  }

  _storem = 0;
  for(int i=0;i<10;i++){
    _storefre[i] = 0;
    _storefim[i] = 0;
  }
}

double MyKMatrix::CalRho4pi(double s) const
{
  if(s>=1.){
    return sqrt((s-16.*m_pi2)/s);
  }else{
    double gam = 1.2274;
    double s2 = s*s;
    double s3 = s2*s;
    double s4 = s2*s2;
    
    gam += 0.00370909/s2;
    gam -= 0.111203/s;
    gam -= 6.39017*s;
    gam += 16.8358*s2;
    gam -= 21.8845*s3;
    gam += 11.3153*s4;
    
    return sqrt(1.-16.*m_pi2)*gam;
  
  } 
}


void MyKMatrix::GetValues(double m, double fre[10], double fim[10])
{
  int check = CheckPara(m);
  if(check == 0){
    for(int i=0;i<10;i++){
      fre[i] = _storefre[i];
      fim[i] = _storefim[i];
    }
  }else{

  double s = m*m;
  double factor;
  if(m<=1.0) factor = m_alpha2[0] - s;
  else {
    if(m<=1.207) factor = m_alpha2[1] - s;
    else{
      if(m<=1.4) factor = m_alpha2[3] - s;
      else{
	if(m<=1.7) factor = m_alpha2[2] - s;
	else factor = m_alpha2[4] - s;
      }
    }
  }

  if(fabs(factor)<1e-4){
    factor = 1e-4;
    if(m<=1.0) s = m_alpha2[0] - factor;
    else {
      if(m<=1.207) s = m_alpha2[1] - factor;
      else{
	if(m<=1.4) s = m_alpha2[3] - factor;
	else{
	  if(m<=1.7) s = m_alpha2[2] - factor;
	  else s = m_alpha2[4] - factor;
	}
      }
    }
  }
  m = sqrt(s);
  
  double factor2 = factor*factor;

  double ms[5];
  for(int i=0;i<5;i++){
    if(m<=1.0) {
      if(i == 0) ms[i] = 1.;
      else ms[i] = factor/(m_alpha2[i]-s);
    }else{
      if(m<=1.207){
	if(i==1) ms[i] = 1.;
	else  ms[i] = factor/(m_alpha2[i]-s);
      }else{
	if(m<=1.4){
	  if(i==3) ms[i] = 1.;
	  else ms[i] = factor/(m_alpha2[i]-s);
	}else{
	  if(m<=1.7){
	    if(i==2) ms[i] = 1.;
            else ms[i] = factor/(m_alpha2[i]-s);
	  }else{
	    if(i==4) ms[i] = 1.;
	    else ms[i] = factor/(m_alpha2[i]-s);
	  }
	}
      }  
    }
  }

  double mg[5][5];
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      mg[i][j] = g_alpha[j][i]*ms[i];
    }
  }

  double fs[5][5];
  double ss0 = (1.-sscat)/(s-sscat);
  double ss1 = (1.-sa0)*(s-0.5*sa*pow(m_pi,2))/(s-sa0);
 
  for(int i=0;i<5;i++){
    for(int j=i;j<5;j++){
      fs[i][j] = f_scat[i][j]*ss0*factor;
    }
  } 

  
  SMatrix55 kma;
  for(int i=0;i<5;i++){
    for(int j=i;j<5;j++){
      kma(i,j) = fs[i][j];
      for(int k=0;k<5;k++){
        kma(i,j) += g_alpha[i][k]*mg[k][j];
      }
      kma(i,j) *= ss1;
      kma(j,i) = kma(i,j);
    }
  }

  int ifail(0);

  TComplex pr0[5];
  pr0[0] = sqrt(1.-4.*m_pi2/s);
  pr0[1] = sqrt(fabs(1-4.*m_k2/s));
  pr0[2] = CalRho4pi(s);
  pr0[3] = sqrt(fabs(1-4.*m_eta2/s));
  pr0[4] = sqrt(fabs(1-m_etap2/s));
  if(m<=(2.*m_k)) pr0[1] *= TComplex(0.,1.);  
  if(m<=(2.*m_eta)) pr0[3] *= TComplex(0.,1.);
  if(m<=(m_eta+m_etap)) pr0[4] *= TComplex(0.,1.);
  TComplex KK[5][5];
  for(int i=0; i<5; i++) {
    for(int j=0; j<5; j++) {
       KK[j][i] = -TComplex(0.,1.)*kma(j,i)*pr0[i];
       if(i==j) KK[j][i] += factor;
    }
  }
  SMatrix55 A, IB;
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
      IB(j,i) = KK[j][i].Re();
      A(j,i) = -KK[j][i].Im();
    }
  }
  SMatrix55 IIB = IB.Inverse(ifail);
  if(ifail) cout<<"inverse matrix failed 1"<<endl;           
  SMatrix55 RR = (IB+A*IIB*A);
  SMatrix55 IRR = RR.Inverse(ifail);
  if(ifail) cout<<"inverse matrix failed 2"<<endl;  
  SMatrix55 IM = IIB*A*IRR;
    SVector5 re,im;
//second column for KK    
  for(int i=0; i<5; ++i) {
    re(i) = IRR(1,i);
    im(i) = IM(1,i);
  }
  double p0 = (1.-sprod)/(s-sprod);
  for(int i=0;i<5;i++){
    fre[i+5] = re(i)*p0*factor;
    fim[i+5] = im(i)*p0*factor;
  }
  
  for(int i=0;i<5;i++){
    fre[i] = 0;
    fim[i] = 0;
    for(int j=0;j<5;j++){
      fre[i] += re(j)*g_alpha[j][i];
      fim[i] += im(j)*g_alpha[j][i];
    }
    fre[i] = fre[i]*ms[i];
    fim[i] = fim[i]*ms[i];
  }
//  std::cout << "KM " << m  << " " << fre[0] << " " << fim[0] << std::endl;
  _storem = m;
  for(int i=0;i<10;i++){
    _storefre[i] = fre[i];
    _storefim[i] = fim[i];
  }
  
  }
}

int MyKMatrix::CheckPara(double m)
{
  if(fabs(_storem - m) >  0.5e-4) return 1;
  return 0;
}
