/**
 * \file ButterworthFilter.h
 */

#ifndef ATK_EQ_BUTTERWORTHFILTER_H
#define ATK_EQ_BUTTERWORTHFILTER_H

#include <ATK/Core/TypedBaseFilter.h>

namespace ATK
{
  template<typename DataType_>
  class ButterworthLowPassCoefficients: public TypedBaseFilter<DataType_>
  {
  public:
    typedef TypedBaseFilter<DataType_> Parent;
    using typename Parent::DataType;
    using Parent::input_sampling_rate;
  protected:
    DataType cut_frequency;
    
    int in_order;
    int out_order;
    
    void setup();
    
    std::vector<DataType> coefficients_in;
    std::vector<DataType> coefficients_out;
    
  public:
    ButterworthLowPassCoefficients();
    
    void set_cut_frequency(DataType cut_frequency);
    DataType get_cut_frequency() const;
    
    void set_order(int order);
  };
}

#endif
