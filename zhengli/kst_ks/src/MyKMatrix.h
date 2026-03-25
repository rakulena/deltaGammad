#ifndef MYKMATRIX_H
#define MYKMATRIX_H

class MyKMatrix{
 public:
  inline MyKMatrix():m_pi(0.13957),m_k(0.493677),m_eta(0.547853),m_etap(0.95778),sscat(-3.92637),sa0(-0.15),sprod(-3.92637),sa(1.) {};
  virtual ~MyKMatrix() {}

  void SetValues();
  double CalRho4pi(double) const;
  void GetValues(double,double[10],double[10]);
  int CheckPara(double);
private:
  double m_pi;
  double m_k;
  double m_eta;
  double m_etap;
  double m_alpha[5];
  double g_alpha[5][5];
  double f_scat[5][5];
  double sscat;
  double sa0;
  double sprod;
  double sa;
  double _storem;
  double _storefre[10];
  double _storefim[10];
  double m_pi2;
  double m_k2;
  double m_eta2;
  double m_etap2;
  double m_alpha2[5];

};

#endif

