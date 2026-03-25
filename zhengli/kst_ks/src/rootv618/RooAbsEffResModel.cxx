#include <RooResolutionModel.h>
#include "RooAbsEffResModel.h"

//_____________________________________________________________________________
//RooAbsEffResModel::RooAbsEffResModel(const char *name, const char *title, RooAbsRealLValue& convVar) // ROOT higher than v6.20 
RooAbsEffResModel::RooAbsEffResModel(const char *name, const char *title, RooRealVar& convVar) 
   : RooResolutionModel(name, title, convVar)
{ }

//_____________________________________________________________________________
RooAbsEffResModel::RooAbsEffResModel(const RooAbsEffResModel& other, const char* name) 
  : RooResolutionModel(other, name)
{ }


//RooAbsEffResModel::~RooAbsEffResModel()
//{ }
