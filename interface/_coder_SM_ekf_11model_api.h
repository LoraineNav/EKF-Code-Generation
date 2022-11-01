/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_SM_ekf_11model_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 01-Nov-2022 11:09:27
 */

#ifndef _CODER_SM_EKF_11MODEL_API_H
#define _CODER_SM_EKF_11MODEL_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_SM_ekf_11model_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void SM_ekf_11model(real_T xkm1_post[4], real_T Pkm1_post[16], real_T
  ukm1[4], real_T yk[4], real_T params[14], real_T Tf, real_T Qin[16], real_T R
  [9], real_T iter_in, real_T Qp[16], real_T xk_post[4], real_T Pk_post[16],
  real_T *iter_out);
extern void SM_ekf_11model_api(const mxArray *prhs[10], const mxArray *plhs[3]);
extern void SM_ekf_11model_atexit(void);
extern void SM_ekf_11model_initialize(void);
extern void SM_ekf_11model_terminate(void);
extern void SM_ekf_11model_xil_terminate(void);

#endif

/*
 * File trailer for _coder_SM_ekf_11model_api.h
 *
 * [EOF]
 */
