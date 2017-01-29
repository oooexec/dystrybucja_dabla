#include <stdio.h>
#include <inttypes.h>
#include <mpfr.h>

#ifndef FUNKCJE_NIEPOSORTOWANE_H
#define FUNKCJE_NIEPOSORTOWANE_H
#define PRECISION 100000
#define ROUNDING MPFR_RNDN
void distribute(double X, double tab_in[], double tab_out[], size_t tabsize);
int distribute_(double X, double tab_in[], double tab_out[], size_t tabsize);
void print_output(double X, double tab_in[], double tab_out[], size_t tabsize);
void print_tab(double tab[], size_t tabsize);
double sum_tab(double tab[], size_t tabsize);
void sum_tabf(mpfr_t *sumaf, mpfr_t tabf_tmp[], size_t tabsize);
void copy_tab(double tab_in[], double tab_out[], size_t tabsize);
void copy_tab_(double tab_in[], mpfr_t tab_out[], size_t tabsize);
void copy_tab__(mpfr_t tabf_tmp[], double tab_out[], size_t tabsize);
#endif