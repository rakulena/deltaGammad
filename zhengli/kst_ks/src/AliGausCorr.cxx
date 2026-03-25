#include <Riostream.h>
#include <TArrayD.h>
#include <TMath.h>
#include <TRandom.h>

#include "AliGausCorr.h"

//ClassImp(AliGausCorr)

  //_______________________________________________________________________
  AliGausCorr::AliGausCorr():
    fSize(0),
    fCv(0)
{
  //
  // Default constructor
  //
}

//_______________________________________________________________________
AliGausCorr::AliGausCorr(const TMatrixD & vec, Int_t size):
  fSize(size),
  fCv(new TMatrixD(fSize,fSize))
{
  //
  // Standard constructor
  //
  for(Int_t j=0;j<fSize;j++){
    double accum = 0;
    for(Int_t k=0;k<j;k++){
      accum += (*fCv)(j,k)* (*fCv)(j,k);
    }
    (*fCv)(j,j)=TMath::Sqrt(TMath::Abs(vec(j,j)-accum));
    for(Int_t i=j+1;i<fSize;i++){
      accum = 0;
      for(Int_t k=0;k<j;k++){
	accum+=(*fCv)(i,k)* (*fCv)(j,k);
      }
      (*fCv)(i,j) = (vec(i,j)-accum) / (*fCv)(j,j);
    }
  }
}

//_______________________________________________________________________
AliGausCorr::AliGausCorr(const AliGausCorr & tgcorr):
  TObject(tgcorr),
  fSize(tgcorr.fSize),
  fCv(new TMatrixD(fSize,fSize))
{
  //
  // Copy contructor
  //
  for(Int_t i=0;i<fSize;i++){
    for(Int_t j=0;j<fSize;j++)(*fCv)(i,j)=(*tgcorr.fCv)(i,j);
  }
}

//_______________________________________________________________________
AliGausCorr::~AliGausCorr()
{
  // Destructor
  delete fCv;
}

//_______________________________________________________________________
void AliGausCorr::GetGaussN(TArrayD &vec) const
{
  // return fSize correlated gaussian numbers

  TArrayD tmpv(fSize);

  for(Int_t i=0; i<fSize; i++){
    Double_t x, y, z;
    do {
      y = gRandom->Rndm();
    } while (!y);
    z = gRandom->Rndm();
    x = z * 6.283185;
    tmpv[i] = TMath::Sin(x)*TMath::Sqrt(-2*TMath::Log(y));
  }

  for(Int_t i=0;i<fSize;i++){
    vec[i]=0;
    for(Int_t j=0;j<=i;j++)vec[i] += (*fCv)(i,j)* tmpv[j];
  }

}

//_______________________________________________________________________
void AliGausCorr::PrintCv() const
{
  // Printout of the "square root" cov. matrix 
  printf("\n AliGausCorr - triangular matrix \n");
  for(Int_t i=0; i<fSize;i++){
    for(Int_t j=0;j<(fSize-1);j++){
      if(j==0){
        printf("| %12.4f ",(*fCv)(i,j));
      }
      else {
        printf(" %12.4f ",(*fCv)(i,j));
      }
    }
    printf(" %12.4f | \n",(*fCv)(i,fSize-1));
  }
  printf("\n");
}

//_______________________________________________________________________
AliGausCorr & AliGausCorr::operator=(const AliGausCorr & tgcorr)
{
  // Assignment operator
  if(&tgcorr != this && tgcorr.fSize!=fSize){
    if(fCv)delete fCv;
    fSize = tgcorr.fSize;
    fCv = new TMatrixD(fSize,fSize);
  }
  if(&tgcorr != this){
    for(Int_t i=0;i<fSize;i++){
      for(Int_t j=0;j<fSize;j++)(*fCv)(i,j)=(*tgcorr.fCv)(i,j);
    }
  }

  return *this;
}

