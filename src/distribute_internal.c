#include <stdio.h>
#include <inttypes.h>
#include <mpfr.h>
#include "distribute_internal.h"

/*************************/
/* BEGIN DEBUG FUNCTIONS */
/*************************/

void debug_print(mpfr_t *f, char *info) {
	double test = mpfr_get_d(*f, ROUNDING);
	puts("DEBUG");
	puts(info);
	printf("%20.50f\n", test);
	puts("DEBUG");
}

void debug_print2(mpfr_t *f) {
	double test = mpfr_get_d(*f, ROUNDING);
	printf("%20.20f\n", test);
}

/*************************/
/*   END DEBUG FUNCTIONS */
/*************************/

/*************************/
/* BEGIN PRINT FUNCTIONS */
/*************************/

void print_tab_d(double tab[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) {
		printf("%10.50f", tab[i]);
		printf("\n");
		//if((i%3)==2) { printf("\n"); }
		//else { printf(" "); }
	}
}

/*************************/
/*   END PRINT FUNCTIONS */
/*************************/

/************************/
/* BEGIN INIT FUNCTIONS */
/************************/

void init_tab_f(mpfr_t tab[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) {
		mpfr_init2(tab[i], PRECISION);
	}
}

void clear_tab_f(mpfr_t tab[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) {
		mpfr_clear(tab[i]);
	}
}

/************************/
/*   END INIT FUNCTIONS */
/************************/

/*********************************************/
/* BEGIN COMPUTE AND DATA TRANSFER FUNCTIONS */
/*********************************************/

void copy_tab_dd(double tab_in[], double tab_out[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) { tab_out[i] = tab_in[i]; }
}

void copy_tab_df(double tab_in[], mpfr_t tab_out[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) { mpfr_set_d(tab_out[i], tab_in[i], ROUNDING); }
}

void copy_tab_fd(mpfr_t tab_in[], double tab_out[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) { tab_out[i] = mpfr_get_d(tab_in[i], ROUNDING); }
}

void sum_tab_f(mpfr_t *sumaf, mpfr_t tabf_tmp[], size_t tabsize) {
	mpfr_set_d(*sumaf, 0.0, ROUNDING);
	for(size_t i=0;i<tabsize;++i) { mpfr_add(*sumaf, *sumaf, tabf_tmp[i], ROUNDING); }
}

double sum_tab_d(double tab[], size_t tabsize) {
	double sum = 0.0;
	for(size_t i=0;i<tabsize;++i) { sum += tab[i]; }
	return sum;
}

/*********************************************/
/*   END COMPUTE AND DATA TRANSFER FUNCTIONS */
/*********************************************/