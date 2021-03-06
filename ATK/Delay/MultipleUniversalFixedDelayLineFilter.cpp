/**
 * \file MultipleUniversalFixedDelayLineFilter.cpp
 */

#include <ATK/Delay/MultipleUniversalFixedDelayLineFilter.h>

#include <cmath>
#include <cstring>
#include <complex>
#include <stdexcept>

#include <ATK/Core/TypeTraits.h>

namespace ATK
{
  template<class DataType, int nb_channels>
  class MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::SUFDLF_Impl
  {
  public:
    std::array<std::vector<DataType>, nb_channels> processed_input;
    int64_t index;

    SUFDLF_Impl(std::size_t max_delay)
      :index(0)
    {
      // reset the delay line
      for (unsigned int channel = 0; channel < nb_channels; ++channel)
      {
        processed_input[channel].assign(max_delay, 0);
      }
    }
  };

  template<class DataType, int nb_channels>
  MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::MultipleUniversalFixedDelayLineFilter(std::size_t max_delay)
    :Parent(nb_channels, 2 * nb_channels), impl(new SUFDLF_Impl(max_delay)), max_delay(max_delay)
  {
    delay.fill(max_delay - 1);
    blend.fill(0);
    feedback.fill(0);
    feedforward.fill(0);
  }

  template<class DataType, int nb_channels>
  MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::~MultipleUniversalFixedDelayLineFilter()
  {
  }

  template<class DataType, int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::set_delay(unsigned int channel, std::size_t delay)
  {
    if (delay == 0)
    {
      throw std::out_of_range("Delay must be strictly positive");
    }
    if (delay >= max_delay)
    {
      throw std::out_of_range("Delay must be less than delay line size");
    }

    this->delay[channel] = delay;
  }

  template<class DataType, int nb_channels>
  std::size_t MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::get_delay(unsigned int channel) const
  {
    return delay[channel];
  }

  template<class DataType_, int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::set_blend(unsigned int channel, DataType_ blend)
  {
    this->blend[channel] = blend;
  }

  template<class DataType_, int nb_channels>
  DataType_ MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::get_blend(unsigned int channel) const
  {
    return blend[channel];
  }

  template<class DataType_, int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::set_feedback(unsigned int from_channel, unsigned int to_channel, DataType_ feedback)
  {
    if (std::abs(feedback) >= 1)
    {
      throw std::out_of_range("Feedback must be between -1 and 1 to avoid divergence");
    }
    this->feedback[from_channel * nb_channels + to_channel] = feedback;
  }

  template<class DataType_, int nb_channels>
  DataType_ MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::get_feedback(unsigned int from_channel, unsigned int to_channel) const
  {
    return feedback[from_channel * nb_channels + to_channel];
  }

  template<class DataType_, int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::set_feedforward(unsigned int from_channel, unsigned int to_channel, DataType_ feedforward)
  {
    this->feedforward[from_channel * nb_channels + to_channel] = feedforward;
  }

  template<class DataType_, int nb_channels>
  DataType_ MultipleUniversalFixedDelayLineFilter<DataType_, nb_channels>::get_feedforward(unsigned int from_channel, unsigned int to_channel) const
  {
    return feedforward[from_channel * nb_channels + to_channel];
  }

  template<class DataType, int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::full_setup()
  {
    // reset the delay line
    for (int channel = 0; channel < nb_channels; ++channel)
    {
      impl->processed_input[channel].assign(max_delay, 0);
    }
  }

  template<class DataType, int nb_channels>
  void MultipleUniversalFixedDelayLineFilter<DataType, nb_channels>::process_impl(std::size_t size) const
  {
    for (std::size_t i = 0; i < size; ++i)
    {
      ATK_VECTORIZE for (int channel = 0; channel < nb_channels; ++channel)
      {
        auto j = impl->index - static_cast<int64_t>(delay[channel]);
        if (j < 0)
        {
          j += max_delay;
        }
        outputs[nb_channels + channel][i] = impl->processed_input[channel][j];
      }
      ATK_VECTORIZE for (int to_channel = 0; to_channel < nb_channels; ++to_channel)
      {
        impl->processed_input[to_channel][impl->index] = converted_inputs[to_channel][i];
        ATK_VECTORIZE for (int from_channel = 0; from_channel < nb_channels; ++from_channel)
        {
          impl->processed_input[to_channel][impl->index] += feedback[from_channel * nb_channels + to_channel] * outputs[nb_channels + from_channel][i];
        }
      }
      ATK_VECTORIZE for (int to_channel = 0; to_channel < nb_channels; ++to_channel)
      {
        outputs[to_channel][i] = blend[to_channel] * impl->processed_input[to_channel][impl->index];
        ATK_VECTORIZE for (int from_channel = 0; from_channel < nb_channels; ++from_channel)
        {
          outputs[to_channel][i] += feedforward[from_channel * nb_channels + to_channel] * outputs[nb_channels + from_channel][i];
        }
      }
      ++impl->index;
      if (impl->index == max_delay)
        impl->index = 0;
    }
  }

  template class MultipleUniversalFixedDelayLineFilter<float, 2>;
  template class MultipleUniversalFixedDelayLineFilter<double, 2>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<float>, 2>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<double>, 2>;

  template class MultipleUniversalFixedDelayLineFilter<float, 4>;
  template class MultipleUniversalFixedDelayLineFilter<double, 4>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<float>, 4>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<double>, 4>;

  template class MultipleUniversalFixedDelayLineFilter<float, 8>;
  template class MultipleUniversalFixedDelayLineFilter<double, 8>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<float>, 8>;
  template class MultipleUniversalFixedDelayLineFilter<std::complex<double>, 8>;
}
