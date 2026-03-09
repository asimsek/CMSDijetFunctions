//---------------------------------------------------------------------------
#ifndef HiggsAnalysis_CombinedLimit_RooDijet3ParamBinPdf_h
#define HiggsAnalysis_CombinedLimit_RooDijet3ParamBinPdf_h
//---------------------------------------------------------------------------
#include "RooAbsPdf.h"
#include "RooConstVar.h"
#include "RooRealProxy.h"
//---------------------------------------------------------------------------
class RooRealVar;
class RooAbsReal;

#include "Riostream.h"
#include "TMath.h"
#include <TH1.h>
#include "Math/Functor.h"
#include "Math/WrappedFunction.h"
#include "Math/IFunction.h"
#include "Math/Integrator.h"

//---------------------------------------------------------------------------
class RooDijet3ParamBinPdf : public RooAbsPdf {
public:
  RooDijet3ParamBinPdf() {};
  RooDijet3ParamBinPdf(const char *name, const char *title, RooAbsReal &_th1x, RooAbsReal &_p1,
                       RooAbsReal &_p2, RooAbsReal &_sqrts, RooAbsReal &_meff, RooAbsReal &_seff);
  RooDijet3ParamBinPdf(const char *name, const char *title, RooAbsReal &_th1x, RooAbsReal &_p1,
                       RooAbsReal &_p2, RooAbsReal &_sqrts);
  RooDijet3ParamBinPdf(const RooDijet3ParamBinPdf &other, const char *name = 0);
  void setTH1Binning(TH1 *_Hnominal);
  void setAbsTol(double _absTol);
  void setRelTol(double _relTol);
  virtual TObject *clone(const char *newname) const { return new RooDijet3ParamBinPdf(*this, newname); }
  inline virtual ~RooDijet3ParamBinPdf() {}

  Int_t getAnalyticalIntegral(RooArgSet &allVars, RooArgSet &analVars, const char *rangeName = 0) const;
  Double_t analyticalIntegral(Int_t code, const char *rangeName = 0) const;

protected:
  RooRealProxy th1x;  // dependent variable
  RooRealProxy p1;    // p1
  RooRealProxy p2;    // p2
  RooRealProxy sqrts; // sqrts
  RooRealProxy meff;  // meff
  RooRealProxy seff;  // seff
  Int_t xBins;        // X bins
  Double_t xArray[2000];
  Double_t xMax;
  Double_t xMin;
  Double_t relTol; // relative tolerance for numerical integration
  Double_t absTol; // absolute tolerance for numerical integration

  Double_t evaluate() const;

private:
  ClassDef(RooDijet3ParamBinPdf, 1)
};
//---------------------------------------------------------------------------
#endif

#include "Math/IFunction.h"
#include "Math/IParamFunction.h"

class Dijet3ParamFunction : public ROOT::Math::IParametricFunctionOneDim {
private:
  const double *pars;

public:
  double DoEvalPar(double x, const double *p) const {
    double pdf = pow(1 - x / p[0], p[1]) / pow(x / p[0], p[2]);
    double eff = 1.0;
    if (p[3] > 0 && p[4] > 0)
      eff = 0.5 * (1.0 + TMath::Erf((x - p[3]) / p[4]));
    return pdf * eff;
  }

  double DoEval(double x) const {
    double pdf = pow(1 - x / pars[0], pars[1]) / pow(x / pars[0], pars[2]);
    double eff = 1.0;
    if (pars[3] > 0 && pars[4] > 0)
      eff = 0.5 * (1.0 + TMath::Erf((x - pars[3]) / pars[4]));
    return pdf * eff;
  }

  ROOT::Math::IBaseFunctionOneDim *Clone() const { return new Dijet3ParamFunction(); }

  const double *Parameters() const { return pars; }

  void SetParameters(const double *p) { pars = p; }

  unsigned int NPar() const { return 5; }
};


