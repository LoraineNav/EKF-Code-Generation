/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 01-Nov-2022 11:09:27
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "rt_nonfinite.h"
#include "SM_ekf_11model.h"
#include "main.h"
#include "SM_ekf_11model_terminate.h"
#include "SM_ekf_11model_initialize.h"

/* Function Declarations */
static void argInit_1x14_real_T(double result[14]);
static void argInit_3x3_real_T(double result[9]);
static void argInit_4x1_real_T(double result[4]);
static void argInit_4x4_real_T(double result[16]);
static double argInit_real_T(void);
static void main_SM_ekf_11model(void);

/* Function Definitions */

/*
 * Arguments    : double result[14]
 * Return Type  : void
 */
static void argInit_1x14_real_T(double result[14])
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 14; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[9]
 * Return Type  : void
 */
static void argInit_3x3_real_T(double result[9])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 3; idx0++) {
    for (idx1 = 0; idx1 < 3; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + 3 * idx1] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : double result[4]
 * Return Type  : void
 */
static void argInit_4x1_real_T(double result[4])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 4; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[16]
 * Return Type  : void
 */
static void argInit_4x4_real_T(double result[16])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 4; idx0++) {
    for (idx1 = 0; idx1 < 4; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + (idx1 << 2)] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_SM_ekf_11model(void)
{
  double dv0[4];
  double dv1[16];
  double dv2[4];
  double dv3[4];
  double dv4[14];
  double dv5[16];
  double dv6[9];
  double dv7[16];
  double xk_post[4];
  double Pk_post[16];
  double iter_out;

  /* Initialize function 'SM_ekf_11model' input arguments. */
  /* Initialize function input argument 'xkm1_post'. */
  /* Initialize function input argument 'Pkm1_post'. */
  /* Initialize function input argument 'ukm1'. */
  /* Initialize function input argument 'yk'. */
  /* Initialize function input argument 'params'. */
  /* Initialize function input argument 'Qin'. */
  /* Initialize function input argument 'R'. */
  /* Initialize function input argument 'Qp'. */
  /* Call the entry-point 'SM_ekf_11model'. */
  argInit_4x1_real_T(dv0);
  argInit_4x4_real_T(dv1);
  argInit_4x1_real_T(dv2);
  argInit_4x1_real_T(dv3);
  argInit_1x14_real_T(dv4);
  argInit_4x4_real_T(dv5);
  argInit_3x3_real_T(dv6);
  argInit_4x4_real_T(dv7);
  SM_ekf_11model(dv0, dv1, dv2, dv3, dv4, argInit_real_T(), dv5, dv6,
                 argInit_real_T(), dv7, xk_post, Pk_post, &iter_out);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  SM_ekf_11model_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_SM_ekf_11model();

  /* Terminate the application.
     You do not need to do this more than one time. */
  SM_ekf_11model_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
