#include <stdio.h>
#include <inttypes.h>
#include <stdarg.h>
#include <mpfr.h>
#include "distribute_internal.h"

void distribute(double X, double tab_in[], double tab_out[], size_t tabsize) {
	double tab_tmp[tabsize];
	double tab_tmp2[tabsize];
	for(size_t i=0;i<tabsize;++i) { tab_tmp[i] = X/tabsize; }
	for(size_t i=0;i<tabsize;++i) { tab_tmp2[i] = tab_tmp[i]*tab_in[i]; }
	double suma = sum_tab_d(tab_tmp2, tabsize);
	if(suma) {
		double ratio = X/suma;
		for(size_t i=0;i<tabsize;++i) { tab_tmp2[i] *= ratio; }
	}
	copy_tab_dd(tab_tmp, tab_out, tabsize);
}

void distribute_precise(double X, double tab_in[], double tab_out[], size_t tabsize) {
	MPFR_T(Xf);mpfr_set_d(Xf, X, ROUNDING);
	MPFR_T(tabsizef);mpfr_set_ui(tabsizef, tabsize, ROUNDING);
	MPFR_T(sumaf);mpfr_set_d(sumaf, 0.0, ROUNDING);
	mpfr_t tabf_tmp[tabsize], tabf_in[tabsize];
	init_tab_f(tabf_tmp, tabsize);
	init_tab_f(tabf_in, tabsize);
	copy_tab_df(tab_in, tabf_in, tabsize);

	for(size_t i=0;i<tabsize;++i) { mpfr_div(tabf_tmp[i], Xf, tabsizef, ROUNDING); }
	for(size_t i=0;i<tabsize;++i) { mpfr_mul(tabf_tmp[i], tabf_tmp[i], tabf_in[i], ROUNDING); }
	
	sum_tab_f(&sumaf, tabf_tmp, tabsize);
	
	if(mpfr_cmp_d(sumaf, 0.0)) {
		MPFR_T(ratiof);
		mpfr_set_d(ratiof, 0.0, ROUNDING);
		mpfr_div(ratiof, Xf, sumaf, ROUNDING);
		for(size_t i=0;i<tabsize;++i) { mpfr_mul(tabf_tmp[i], tabf_tmp[i], ratiof, ROUNDING); }
		mpfr_clear(ratiof);
	}

	sum_tab_f(&sumaf, tabf_tmp, tabsize);
	copy_tab_fd(tabf_tmp, tab_out, tabsize);

	clear_tab_f(tabf_tmp, tabsize);
	clear_tab_f(tabf_in, tabsize);
	mpfr_clears(Xf, tabsizef, sumaf, NULL);
}

void print_output(double X, double tab_in[], double tab_out[], size_t tabsize) {
	puts("tab_in");
	print_tab_d(tab_in, tabsize);
	printf("\n");
	printf("%12s = %10.50f\n", "X", X);
	double suma = sum_tab_d(tab_out, tabsize);
	printf("%12s = %10.50f\n", "suma tab_out", suma);
	int difference = (suma == X);
	printf("czy suma tab_out równa się X: %s\n", difference ? "tak" : "nie");
	if(!difference) { printf("różnica = %.50f\n", X-suma); };
	puts("tab_out");
	print_tab_d(tab_out, tabsize);
	printf("\n");
}