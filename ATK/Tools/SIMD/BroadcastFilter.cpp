/**
 * \file BroadcastFilter.cpp
 */

#include <ATK/Tools/SIMD/BroadcastFilter.hxx>
#include <ATK/Core/TypeTraits.h>

#include <simdpp/dispatch/dispatcher.h>
#include <simdpp/dispatch/get_arch_gcc_builtin_cpu_supports.h>
#include <simdpp/dispatch/get_arch_raw_cpuid.h>
#include <simdpp/dispatch/get_arch_linux_cpuinfo.h>

#if SIMDPP_HAS_GET_ARCH_RAW_CPUID
# define SIMDPP_USER_ARCH_INFO ::simdpp::get_arch_raw_cpuid()
#elif SIMDPP_HAS_GET_ARCH_GCC_BUILTIN_CPU_SUPPORTS
# define SIMDPP_USER_ARCH_INFO ::simdpp::get_arch_gcc_builtin_cpu_supports()
#elif SIMDPP_HAS_GET_ARCH_LINUX_CPUINFO
# define SIMDPP_USER_ARCH_INFO ::simdpp::get_arch_linux_cpuinfo()
#else
# error "Unsupported platform"
#endif

namespace ATK
{
  template class BroadcastFilter<double, simdpp::float64<2> >;
  template class BroadcastFilter<float, simdpp::float32<4> >;
  template class BroadcastFilter<double, simdpp::float64<4> >;
  template class BroadcastFilter<float, simdpp::float32<8> >;
  template class BroadcastFilter<double, simdpp::float64<8> >;
  
  namespace SIMDPP_ARCH_NAMESPACE
  {
  template<typename DataType, std::size_t VL>
  std::unique_ptr<BaseFilter> createBroadcastFilter(std::size_t nb_channels)
  {
  return std::unique_ptr<BaseFilter>(new BroadcastFilter<DataType, typename SIMDTypeTraits<DataType>::template SIMDType<VL> >(nb_channels));
  }
  }
  
  SIMDPP_MAKE_DISPATCHER((template<typename DataType, std::size_t VL>) (<DataType, VL>) (std::unique_ptr<BaseFilter>) (createBroadcastFilter)
                         ((std::size_t) nb_channels))
  
  SIMDPP_INSTANTIATE_DISPATCHER(
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createBroadcastFilter<double, 2>(std::size_t)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createBroadcastFilter<float, 4>(std::size_t)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createBroadcastFilter<double, 4>(std::size_t)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createBroadcastFilter<float, 8>(std::size_t)),
    (template ATK_TOOLS_EXPORT std::unique_ptr<BaseFilter> createBroadcastFilter<double, 8>(std::size_t)));
}
