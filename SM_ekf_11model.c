/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SM_ekf_11model.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 01-Nov-2022 11:09:27
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SM_ekf_11model.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * %% Unpack Past State, Input, and Parameters
 * Arguments    : const double xkm1_post[4]
 *                const double Pkm1_post[16]
 *                const double ukm1[4]
 *                const double yk[4]
 *                const double params[14]
 *                double Tf
 *                const double Qin[16]
 *                const double R[9]
 *                double iter_in
 *                const double Qp[16]
 *                double xk_post[4]
 *                double Pk_post[16]
 *                double *iter_out
 * Return Type  : void
 */
void SM_ekf_11model(const double xkm1_post[4], const double Pkm1_post[16], const
                    double ukm1[4], const double yk[4], const double params[14],
                    double Tf, const double Qin[16], const double R[9], double
                    iter_in, const double Qp[16], double xk_post[4], double
                    Pk_post[16], double *iter_out)
{
  int i;
  double A[16];
  double F[16];
  double Pk_pre[16];
  double b_A[16];
  double b_F[16];
  double c_A[16];
  int r1;
  int r2;
  double b_xkm1_post[4];
  double xk_pre[4];
  signed char Hk[12];
  static const signed char iv0[4] = { 0, 1, 0, 0 };

  static const signed char iv1[4] = { 1, 0, 0, 0 };

  double b_Hk[12];
  double a[9];
  double c_Hk[9];
  double b_a[9];
  double d_A[9];
  int r3;
  double maxval;
  double a21;
  static const signed char c_a[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  double Kk[12];
  double yk_hat[3];
  double yk_tilde_data[4];
  double b_yk[3];
  double b_maxval;

  /*  unpack state variables */
  /*  unpack input variables (currents Iabcs) */
  /*  unpack machine parameters */
  /*  Computing voltages Vqd */
  if (iter_in > 0.0) {
    /*     %% Compute Jacobian Matrices for System Dynamics */
    /*  compute A = dpx/dx */
    memset(&A[0], 0, sizeof(double) << 4);
    memset(&F[0], 0, sizeof(double) << 4);
    A[0] = -1.0 / params[9];
    A[5] = -1.0 / params[11];
    A[2] = -ukm1[0] / (2.0 * params[13]);
    A[6] = -ukm1[1] / (2.0 * params[13]);
    A[11] = params[0];

    /*  NOTE: A(9,9) may be nonzero if Tfw is a function of w. */
    /*  compute F = dxk/dxkm1 */
    for (i = 0; i < 4; i++) {
      F[i + (i << 2)] = 1.0;
    }

    /*  compute B = dpx/du */
    for (i = 0; i < 16; i++) {
      F[i] += Tf * A[i];
      A[i] = 0.0;
    }

    A[4] = -1.0 / params[9] * (params[3] - params[4]);
    A[12] = 1.0 / params[9];
    A[1] = 1.0 / params[11] * (params[6] - params[7]);
    A[6] = 1.0 / (2.0 * params[13]) * (-xkm1_post[1] - (params[7] - params[4]) *
      ukm1[0]);
    A[2] = 1.0 / (2.0 * params[13]) * (-xkm1_post[0] - (params[7] - params[4]) *
      ukm1[1]);
    A[10] = 1.0 / (2.0 * params[13]);

    /*  compute G = dxk/dukm1 */
    /*  compute L = dxk/dwkm1 */
    for (i = 0; i < 16; i++) {
      A[i] = -(Tf * A[i]);
    }

    /*     %% Predict Step */
    for (i = 0; i < 4; i++) {
      for (r1 = 0; r1 < 4; r1++) {
        Pk_pre[i + (r1 << 2)] = 0.0;
        b_A[i + (r1 << 2)] = 0.0;
        for (r2 = 0; r2 < 4; r2++) {
          Pk_pre[i + (r1 << 2)] += F[i + (r2 << 2)] * Pkm1_post[r2 + (r1 << 2)];
          b_A[i + (r1 << 2)] += A[i + (r2 << 2)] * Qin[r2 + (r1 << 2)];
        }
      }

      for (r1 = 0; r1 < 4; r1++) {
        b_F[i + (r1 << 2)] = 0.0;
        c_A[i + (r1 << 2)] = 0.0;
        for (r2 = 0; r2 < 4; r2++) {
          b_F[i + (r1 << 2)] += Pk_pre[i + (r2 << 2)] * F[r1 + (r2 << 2)];
          c_A[i + (r1 << 2)] += b_A[i + (r2 << 2)] * A[r1 + (r2 << 2)];
        }
      }
    }

    /*  unpack state variables */
    /*  unpack input variables */
    /*  unpack machine parameters */
    /*  compute derivatives */
    /*  neglecting friction and windage damping torques */
    /*  pack derivatives */
    b_xkm1_post[0] = ((-xkm1_post[0] - (params[3] - params[4]) * ukm1[1]) +
                      ukm1[3]) / params[9];
    b_xkm1_post[1] = (-xkm1_post[1] + (params[6] - params[7]) * ukm1[0]) /
      params[11];
    b_xkm1_post[2] = (((ukm1[2] - xkm1_post[1] * ukm1[1]) - xkm1_post[0] * ukm1
                       [0]) - (params[7] - params[4]) * ukm1[1] * ukm1[0]) /
      (2.0 * params[13]);
    b_xkm1_post[3] = xkm1_post[2] * params[0];
    for (i = 0; i < 4; i++) {
      for (r1 = 0; r1 < 4; r1++) {
        Pk_pre[r1 + (i << 2)] = (b_F[r1 + (i << 2)] + c_A[r1 + (i << 2)]) +
          Qp[r1 + (i << 2)];
      }

      xk_pre[i] = xkm1_post[i] + Tf * b_xkm1_post[i];
    }

    /*     %% Compute Jacobian Matrices for System Outputs */
    /*  NOTE: Probably best to rename state and current variables here rather */
    /*  than re-writing them, but that's a lot of work... */
    /*  unpack predicted state variables */
    /*  dH/dx using Vqd without wr included */
    /*  */
    /*  compute Ck = dy/dx == Hk = dyk/dxk */
    for (i = 0; i < 12; i++) {
      Hk[i] = 0;
    }

    for (i = 0; i < 4; i++) {
      Hk[1 + 3 * i] = iv0[i];
      Hk[3 * i] = iv1[i];
    }

    Hk[11] = 1;

    /*  compute Mk = dyk/dvkm1 */
    /*     %% Update Step */
    /*  update Kalman gain */
    for (i = 0; i < 3; i++) {
      for (r1 = 0; r1 < 4; r1++) {
        b_Hk[i + 3 * r1] = 0.0;
        for (r2 = 0; r2 < 4; r2++) {
          b_Hk[i + 3 * r1] += (double)Hk[i + 3 * r2] * Pk_pre[r2 + (r1 << 2)];
        }
      }

      for (r1 = 0; r1 < 3; r1++) {
        a[i + 3 * r1] = 0.0;
        for (r2 = 0; r2 < 3; r2++) {
          a[i + 3 * r1] += (double)c_a[i + 3 * r2] * R[r2 + 3 * r1];
        }

        c_Hk[i + 3 * r1] = 0.0;
        for (r2 = 0; r2 < 4; r2++) {
          c_Hk[i + 3 * r1] += b_Hk[i + 3 * r2] * (double)Hk[r1 + 3 * r2];
        }
      }

      for (r1 = 0; r1 < 3; r1++) {
        b_a[i + 3 * r1] = 0.0;
        for (r2 = 0; r2 < 3; r2++) {
          b_a[i + 3 * r1] += a[i + 3 * r2] * (double)c_a[r2 + 3 * r1];
        }
      }
    }

    for (i = 0; i < 3; i++) {
      for (r1 = 0; r1 < 3; r1++) {
        d_A[r1 + 3 * i] = c_Hk[r1 + 3 * i] + b_a[r1 + 3 * i];
      }
    }

    r1 = 0;
    r2 = 1;
    r3 = 2;
    maxval = fabs(d_A[0]);
    a21 = fabs(d_A[1]);
    if (a21 > maxval) {
      maxval = a21;
      r1 = 1;
      r2 = 0;
    }

    if (fabs(d_A[2]) > maxval) {
      r1 = 2;
      r2 = 1;
      r3 = 0;
    }

    d_A[r2] /= d_A[r1];
    d_A[r3] /= d_A[r1];
    d_A[3 + r2] -= d_A[r2] * d_A[3 + r1];
    d_A[3 + r3] -= d_A[r3] * d_A[3 + r1];
    d_A[6 + r2] -= d_A[r2] * d_A[6 + r1];
    d_A[6 + r3] -= d_A[r3] * d_A[6 + r1];
    if (fabs(d_A[3 + r3]) > fabs(d_A[3 + r2])) {
      i = r2;
      r2 = r3;
      r3 = i;
    }

    d_A[3 + r3] /= d_A[3 + r2];
    d_A[6 + r3] -= d_A[3 + r3] * d_A[6 + r2];
    for (i = 0; i < 3; i++) {
      a[3 * i] = c_a[r1 + 3 * i];
      a[1 + 3 * i] = (double)c_a[r2 + 3 * i] - a[3 * i] * d_A[r2];
      a[2 + 3 * i] = ((double)c_a[r3 + 3 * i] - a[3 * i] * d_A[r3]) - a[1 + 3 *
        i] * d_A[3 + r3];
      a[2 + 3 * i] /= d_A[6 + r3];
      a[3 * i] -= a[2 + 3 * i] * d_A[6 + r1];
      a[1 + 3 * i] -= a[2 + 3 * i] * d_A[6 + r2];
      a[1 + 3 * i] /= d_A[3 + r2];
      a[3 * i] -= a[1 + 3 * i] * d_A[3 + r1];
      a[3 * i] /= d_A[r1];
    }

    for (i = 0; i < 4; i++) {
      for (r1 = 0; r1 < 3; r1++) {
        b_Hk[i + (r1 << 2)] = 0.0;
        for (r2 = 0; r2 < 4; r2++) {
          b_Hk[i + (r1 << 2)] += Pk_pre[i + (r2 << 2)] * (double)Hk[r1 + 3 * r2];
        }
      }

      for (r1 = 0; r1 < 3; r1++) {
        Kk[i + (r1 << 2)] = 0.0;
        for (r2 = 0; r2 < 3; r2++) {
          Kk[i + (r1 << 2)] += b_Hk[i + (r2 << 2)] * a[r2 + 3 * r1];
        }
      }
    }

    /*  compute predicted outputs */
    /*  unpack state variables */
    /*  unpack input variables */
    /*  unpack machine parameters */
    /*  compute voltages */
    /*  pack output */
    yk_hat[0] = (-params[1] * ukm1[0] - params[4] * ukm1[1]) + xk_pre[0];
    yk_hat[1] = (-params[1] * ukm1[1] + params[7] * ukm1[0]) + xk_pre[1];
    yk_hat[2] = xk_pre[3];

    /*  adjust measurement of thetar to account for circular wrapping */
    if (fabs(yk[2] - xk_pre[3]) > 3.1415926535897931) {
      maxval = yk[2] - xk_pre[3];
      for (i = 0; i < 2; i++) {
        b_yk[i] = yk[i];
      }

      if (maxval < 0.0) {
        b_maxval = -1.0;
      } else if (maxval > 0.0) {
        b_maxval = 1.0;
      } else if (maxval == 0.0) {
        b_maxval = 0.0;
      } else {
        b_maxval = maxval;
      }

      b_yk[2] = yk[2] - 6.2831853071795862 * b_maxval;
      for (i = 0; i < 3; i++) {
        yk_tilde_data[i] = b_yk[i];
      }
    } else {
      for (i = 0; i < 4; i++) {
        yk_tilde_data[i] = yk[i];
      }
    }

    /*  update state estimate */
    for (i = 0; i < 3; i++) {
      b_yk[i] = yk_tilde_data[i] - yk_hat[i];
    }

    for (i = 0; i < 4; i++) {
      maxval = 0.0;
      for (r1 = 0; r1 < 3; r1++) {
        maxval += Kk[i + (r1 << 2)] * b_yk[r1];
      }

      xk_post[i] = xk_pre[i] + maxval;
    }

    /*  wrap thetar as needed */
    maxval = xk_post[3] / 6.2831853071795862;
    if (fabs(maxval - rt_roundd_snf(maxval)) <= 2.2204460492503131E-16 * fabs
        (maxval)) {
      maxval = 0.0;
    } else {
      maxval = (maxval - floor(maxval)) * 6.2831853071795862;
    }

    xk_post[3] = maxval;

    /*  update state covariance */
    memset(&A[0], 0, sizeof(double) << 4);
    for (i = 0; i < 4; i++) {
      A[i + (i << 2)] = 1.0;
    }

    for (i = 0; i < 4; i++) {
      for (r1 = 0; r1 < 4; r1++) {
        maxval = 0.0;
        for (r2 = 0; r2 < 3; r2++) {
          maxval += Kk[i + (r2 << 2)] * (double)Hk[r2 + 3 * r1];
        }

        b_A[i + (r1 << 2)] = A[i + (r1 << 2)] - maxval;
      }

      for (r1 = 0; r1 < 4; r1++) {
        Pk_post[i + (r1 << 2)] = 0.0;
        for (r2 = 0; r2 < 4; r2++) {
          Pk_post[i + (r1 << 2)] += b_A[i + (r2 << 2)] * Pk_pre[r2 + (r1 << 2)];
        }
      }
    }
  } else {
    for (i = 0; i < 4; i++) {
      xk_post[i] = xkm1_post[i];
    }

    memcpy(&Pk_post[0], &Pkm1_post[0], sizeof(double) << 4);
  }

  *iter_out = iter_in + 1.0;
}

/*
 * File trailer for SM_ekf_11model.c
 *
 * [EOF]
 */
