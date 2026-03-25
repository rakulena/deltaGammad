/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *****************************************************************************/
#ifndef ROO_FGAUSSIAN
#define ROO_FGAUSSIAN

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
//#include "RooTrace.h"
#include "RooAbsReal.h"

class RooFGaussian : public RooAbsReal {
public:
  //  RooFGaussian() {   TRACE_CREATE } ;
  RooFGaussian() {  };
  RooFGaussian(const char *name, const char *title,
	      RooAbsReal& _x, RooAbsReal& _mean1, RooAbsReal& _sigma1 , RooAbsReal& _mean2, RooAbsReal& _sigma2);
  RooFGaussian(const RooFGaussian& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooFGaussian(*this,newname); }
  //  inline virtual ~RooFGaussian() { TRACE_DESTROY };
  inline virtual ~RooFGaussian() {  };

  //Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  //Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

  //Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK=kTRUE) const;
  //void generateEvent(Int_t code);

  Double_t getLogVal() const ;

protected:

  RooRealProxy x ;
  RooRealProxy mean1 ;
  RooRealProxy sigma1 ;
  RooRealProxy mean2 ;
  RooRealProxy sigma2 ;
  
  Double_t evaluate() const ;

private:

  //ClassDef(RooFGaussian,1) // Gaussian PDF
};

#endif
