#include <RooResolutionModel.h>
#include "RooAbsEffResModel.h"

//_____________________________________________________________________________
RooAbsEffResModel::RooAbsEffResModel(const char *name, const char *title, RooAbsRealLValue& convVar) 
//RooAbsEffResModel::RooAbsEffResModel(const char *name, const char *title, RooRealVar& convVar) // For ROOT v6.18 
   : RooResolutionModel(name, title, convVar)
{ }

//_____________________________________________________________________________
RooAbsEffResModel::RooAbsEffResModel(const RooAbsEffResModel& other, const char* name) 
  : RooResolutionModel(other, name)
{ }


//RooAbsEffResModel::~RooAbsEffResModel()
//{ }
