#include <stdio.h>
#include <inttypes.h>
#include <mpfr.h>

#ifndef DISTRIBUTE_INTERNAL_H
#define DISTRIBUTE_INTERNAL_H

/****************/
/* BEGIN MACROS */
/****************/
#define PRECISION 100000
#define ROUNDING MPFR_RNDN
#define MPFR_T(NAME) mpfr_t NAME ;mpfr_init2( NAME , PRECISION);
/****************/
/*   END MACROS */
/****************/

/*************************/
/* BEGIN DEBUG FUNCTIONS */
/*************************/
void debug_print(mpfr_t *f, char *info);
void debug_print2(mpfr_t *f);
/*************************/
/*   END DEBUG FUNCTIONS */
/*************************/

/*************************/
/* BEGIN PRINT FUNCTIONS */
/*************************/
void print_tab_d(double tab[], size_t tabsize);
/*************************/
/*   END PRINT FUNCTIONS */
/*************************/

/************************/
/* BEGIN INIT FUNCTIONS */
/************************/
void init_tab_f(mpfr_t tab[], size_t tabsize);
void clear_tab_f(mpfr_t tab[], size_t tabsize);
/************************/
/*   END INIT FUNCTIONS */
/************************/

/*********************************************/
/* BEGIN COMPUTE AND DATA TRANSFER FUNCTIONS */
/*********************************************/
void copy_tab_dd(double tab_in[], double tab_out[], size_t tabsize);
void copy_tab_df(double tab_in[], mpfr_t tab_out[], size_t tabsize);
void copy_tab_fd(mpfr_t tab_in[], double tab_out[], size_t tabsize);
void sum_tab_f(mpfr_t *sumaf, mpfr_t tabf_tmp[], size_t tabsize);
double sum_tab_d(double tab[], size_t tabsize);
/*********************************************/
/*   END COMPUTE AND DATA TRANSFER FUNCTIONS */
/*********************************************/

#endif