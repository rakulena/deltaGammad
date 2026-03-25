/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 * Authors:  T. Skwarnicki
 * Gaussian with a flat top (true integral and generator not implemented)    *
 *****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
//
// BEGIN_HTML
// Plain Gaussian p.d.f
// END_HTML
//

#include "Riostream.h"
#include <math.h>

#include "RooTwoMulGaus.h"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooRandom.h"
#include "RooMath.h"

//using namespace std;

//ClassImp(RooTwoMulGaus)


//_____________________________________________________________________________
RooTwoMulGaus::RooTwoMulGaus(const char *name, const char *title,
			 RooAbsReal& _x, 
			 RooAbsReal& _y,
			   RooAbsReal& _mean1,
			   RooAbsReal& _sigma1,
			   RooAbsReal& _mean2,
			   RooAbsReal& _sigma2,
			   RooAbsReal& _rho) :
  RooAbsReal(name,title),
  x("x","Observable 1",this,_x),
  y("y","Observable 2",this,_y),
  mean1("mean1","Mean1",this,_mean1),
  sigma1("sigma1","Sigma1",this,_sigma1),
  mean2("mean2","Mean2",this,_mean2),
  sigma2("sigma2","Sigma2",this,_sigma2),
  rho("rho","correlation",this,_rho)
{
}



//_____________________________________________________________________________
RooTwoMulGaus::RooTwoMulGaus(const RooTwoMulGaus& other, const char* name) : 
  RooAbsReal(other,name), x("x",this,other.x), 
     y("y",this,other.y),
     mean1("mean1",this,other.mean1),
     sigma1("sigma1",this,other.sigma1),
     mean2("mean2",this,other.mean2),
     sigma2("sigma2",this,other.sigma2),
     rho("rho",this, other.rho)
{
}



//_____________________________________________________________________________
Double_t RooTwoMulGaus::evaluate() const
{
  Double_t arg1 = (x - mean1)/sigma1;
  Double_t arg2 = (y - mean2)/sigma2;
  Double_t Cor = 2.*rho*arg1*arg2;
  if(fabs(rho)<1.0) {
    Double_t ret = arg1*arg1+arg2*arg2-Cor;
    ret = 0.5*ret/(1.-rho*rho);
//    std::cout << "penaty " << ret << std::endl;    
    return ret;
  }
    return 0.0;
}



//_____________________________________________________________________________
Double_t RooTwoMulGaus::getLogVal() const 
{
  // calculate and return the negative log-likelihood of the Poisson                                                                                                                                    
  //  return RooAbsPdf::getLogVal(set) ;

//   Double_t prob = getVal(set) ;
//   return log(prob) ;
  Double_t arg1 = (x - mean1)/sigma1;
  Double_t arg2 = (y - mean2)/sigma2;
  Double_t Cor = 2.*rho*arg1*arg2;
  if(fabs(rho)<1.0) {
    Double_t ret = arg1*arg1+arg2*arg2-Cor;
    ret = 0.5*ret/(1.-rho*rho);

    return ret;
  }
    return 0.0;

  
}

#if 0
//_____________________________________________________________________________
Int_t RooTwoMulGaus::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const 
{
  if (matchArgs(allVars,analVars,x)) return 1 ;
  if (matchArgs(allVars,analVars,mean1)) return 2 ;
  return 0 ;
}



//_____________________________________________________________________________
Double_t RooTwoMulGaus::analyticalIntegral(Int_t code, const char* rangeName) const 
{
  return 1.0;
}




//_____________________________________________________________________________
Int_t RooTwoMulGaus::getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t /*staticInitOK*/) const
{
  if (matchArgs(directVars,generateVars,x)) return 1 ;  
  if (matchArgs(directVars,generateVars,mean1)) return 2 ;  
  return 0 ;
}



//_____________________________________________________________________________
void RooTwoMulGaus::generateEvent(Int_t code)
{
#if 0
  assert(code==1 || code==2) ;
  Double_t xgen ;
  if(code==1){
    while(1) {    
      xgen = RooRandom::randomGenerator()->Gaus(mean1,sigma1);
      if (xgen<x.max() && xgen>x.min()) {
	x = xgen ;
	break;
      }
    }
  } else if(code==2){
    while(1) {    
      xgen = RooRandom::randomGenerator()->Gaus(x,sigma1);
      if (xgen<mean.max() && xgen>mean.min()) {
	mean = xgen ;
	break;
      }
    }
  } else {
    cout << "error in RooTwoMulGaus generateEvent"<< endl;
  }
#endif
  return;
}

#endif
