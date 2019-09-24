#include "__cf_wheelset_continuous.h"
#ifndef RTW_HEADER_wheelset_continuous_acc_private_h_
#define RTW_HEADER_wheelset_continuous_acc_private_h_
#include "rtwtypes.h"
#ifndef RTW_COMMON_DEFINES_
#define RTW_COMMON_DEFINES_
#define rt_VALIDATE_MEMORY(S, ptr)   if(!(ptr)) {\
  ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
  }
#if !defined(_WIN32)
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((ptr));\
  (ptr) = (NULL);\
  }
#else
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((void *)(ptr));\
  (ptr) = (NULL);\
  }
#endif
#endif
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else
#ifndef RTWTYPES_ID_C08S16I32L32N32F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif
#endif
#endif
void wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Init (
SimStruct * const S ) ; void
wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Deriv (
SimStruct * const S ) ; void
wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Projection (
SimStruct * const S ) ; void
wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( SimStruct *
const S ) ; void
wheelset_continuous_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Term (
SimStruct * const S ) ;
#endif
