/**
 * \file RobertBristowJohnsonFilter.cpp
*/

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <ATK/EQ/RobertBristowJohnsonFilter.h>

#include "MainFilter.h"

namespace py = pybind11;

using namespace ATK;

namespace
{
}

void populate_RobertBristowJohnsonFilter(pybind11::module& m, const pybind11::object& f1, const pybind11::object& f2)
{
  populate_QCoefficients<RobertBristowJohnsonLowPassCoefficients<float>>(m, "FloatRobertBristowJohnsonLowPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonLowPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonLowPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonHighPassCoefficients<float>>(m, "FloatRobertBristowJohnsonHighPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonHighPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonHighPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonBandPassCoefficients<float>>(m, "FloatRobertBristowJohnsonBandPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonBandPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonBandPass2Coefficients<float>>(m, "FloatRobertBristowJohnsonBandPass2Coefficients");
  populate_QCoefficients<RobertBristowJohnsonBandPass2Coefficients<double>>(m, "DoubleRobertBristowJohnsonBandPass2Coefficients");
  populate_QCoefficients<RobertBristowJohnsonBandStopCoefficients<float>>(m, "FloatRobertBristowJohnsonBandStopCoefficients");
  populate_QCoefficients<RobertBristowJohnsonBandStopCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandStopCoefficients");
  populate_QCoefficients<RobertBristowJohnsonAllPassCoefficients<float>>(m, "FloatRobertBristowJohnsonAllPassCoefficients");
  populate_QCoefficients<RobertBristowJohnsonAllPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonAllPassCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonBandPassPeakCoefficients<float>>(m, "FloatRobertBristowJohnsonBandPassPeakCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonBandPassPeakCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandPassPeakCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonLowShelvingCoefficients<float>>(m, "FloatRobertBristowJohnsonLowShelvingCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonLowShelvingCoefficients<double>>(m, "DoubleRobertBristowJohnsonLowShelvingCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonHighShelvingCoefficients<float>>(m, "FloatRobertBristowJohnsonHighShelvingCoefficients");
  populate_QshelfCoefficients<RobertBristowJohnsonHighShelvingCoefficients<double>>(m, "DoubleRobertBristowJohnsonHighShelvingCoefficients");
  
  populate_IIRFilter<RobertBristowJohnsonLowPassCoefficients<float>>(m, "FloatRobertBristowJohnsonLowPassFilter");
  populate_IIRFilter<RobertBristowJohnsonLowPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonLowPassFilter");
  populate_IIRFilter<RobertBristowJohnsonHighPassCoefficients<float>>(m, "FloatRobertBristowJohnsonHighPassFilter");
  populate_IIRFilter<RobertBristowJohnsonHighPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonHighPassFilter");
  populate_IIRFilter<RobertBristowJohnsonBandPassCoefficients<float>>(m, "FloatRobertBristowJohnsonBandPassFilter");
  populate_IIRFilter<RobertBristowJohnsonBandPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandPassFilter");
  populate_IIRFilter<RobertBristowJohnsonBandPass2Coefficients<float>>(m, "FloatRobertBristowJohnsonBandPass2Filter");
  populate_IIRFilter<RobertBristowJohnsonBandPass2Coefficients<double>>(m, "DoubleRobertBristowJohnsonBandPass2Filter");
  populate_IIRFilter<RobertBristowJohnsonBandStopCoefficients<float>>(m, "FloatRobertBristowJohnsonBandStopFilter");
  populate_IIRFilter<RobertBristowJohnsonBandStopCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandStopFilter");
  populate_IIRFilter<RobertBristowJohnsonAllPassCoefficients<float>>(m, "FloatRobertBristowJohnsonAllPassFilter");
  populate_IIRFilter<RobertBristowJohnsonAllPassCoefficients<double>>(m, "DoubleRobertBristowJohnsonAllPassFilter");
  populate_IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<float>>(m, "FloatRobertBristowJohnsonBandPassPeakFilter");
  populate_IIRFilter<RobertBristowJohnsonBandPassPeakCoefficients<double>>(m, "DoubleRobertBristowJohnsonBandPassPeakFilter");
  populate_IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<float>>(m, "FloatRobertBristowJohnsonLowShelvingFilter");
  populate_IIRFilter<RobertBristowJohnsonLowShelvingCoefficients<double>>(m, "DoubleRobertBristowJohnsonLowShelvingkFilter");
  populate_IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<float>>(m, "FloatRobertBristowJohnsonHighShelvingFilter");
  populate_IIRFilter<RobertBristowJohnsonHighShelvingCoefficients<double>>(m, "DoubleRobertBristowJohnsonHighShelvingFilter");
}
