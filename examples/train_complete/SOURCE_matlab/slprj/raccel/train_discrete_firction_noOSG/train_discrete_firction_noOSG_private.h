#include "__cf_train_discrete_firction_noOSG.h"
#ifndef RTW_HEADER_train_discrete_firction_noOSG_private_h_
#define RTW_HEADER_train_discrete_firction_noOSG_private_h_
#include "rtwtypes.h"
#ifndef RTW_COMMON_DEFINES_
#define RTW_COMMON_DEFINES_
#define rt_VALIDATE_MEMORY(S, ptr)   if(!(ptr)) {\
  ssSetErrorStatus(rtS, RT_MEMORY_ALLOCATION_ERROR);\
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
#ifdef rt_VALIDATE_MEMORY
#undef rt_VALIDATE_MEMORY
#define rt_VALIDATE_MEMORY(S, ptr)       if(!(ptr)) {\
      ssSetErrorStatus(rtS, RT_MEMORY_ALLOCATION_ERROR);\
      }
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
extern void mu_div_mod_vel_sliding_vel_Outputs_wrapper ( const real_T * u0 ,
const real_T * u1 , real_T * y0 ) ; extern void c_s_func_linalg_discrete (
SimStruct * rts ) ;
#if defined(MULTITASKING)
#error Model (train_discrete_firction_noOSG) was built in \
SingleTasking solver mode, however the MULTITASKING define is \
present. If you have multitasking (e.g. -DMT or -DMULTITASKING) \
defined on the Code Generation page of Simulation parameter dialog, please \
remove it and on the Solver page, select solver mode \
MultiTasking. If the Simulation parameter dialog is configured \
correctly, please verify that your template makefile is \
configured correctly.
#endif
#endif
