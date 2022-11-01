/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SM_ekf_11model.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 01-Nov-2022 11:09:27
 */

#ifndef SM_EKF_11MODEL_H
#define SM_EKF_11MODEL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "SM_ekf_11model_types.h"

/* Function Declarations */
extern void SM_ekf_11model(const double xkm1_post[4], const double Pkm1_post[16],
  const double ukm1[4], const double yk[4], const double params[14], double Tf,
  const double Qin[16], const double R[9], double iter_in, const double Qp[16],
  double xk_post[4], double Pk_post[16], double *iter_out);

#endif

/*
 * File trailer for SM_ekf_11model.h
 *
 * [EOF]
 */
