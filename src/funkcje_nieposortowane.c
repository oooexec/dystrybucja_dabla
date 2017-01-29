#include <stdio.h>
#include <inttypes.h>
#include <mpfr.h>
#include "funkcje_nieposortowane.h"

void distribute(double X, double tab_in[], double tab_out[], size_t tabsize) {
	double tab_tmp[tabsize];
	for(size_t i=0;i<tabsize;++i) { tab_tmp[i] = X/tabsize; }
	for(size_t i=0;i<tabsize;++i) { tab_tmp[i] *= tab_in[i]; }
	double suma = sum_tab(tab_tmp, tabsize);
	if(suma) {
		double ratio = X/suma;
		for(size_t i=0;i<tabsize;++i) { tab_tmp[i] *= ratio; }
	}
	copy_tab(tab_tmp, tab_out, tabsize);
}
void copy_tab_(double tab_in[], mpfr_t tab_out[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) { mpfr_set_d(tab_out[i], tab_in[i], MPFR_RNDD); }
}
void copy_tab__(mpfr_t tab_in[], double tab_out[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) { tab_out[i] = mpfr_get_d(tab_in[i], MPFR_RNDD); }
}
/*
void copy_tab_(mpfr_t tabf_tmp[], double tab_out[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) { tab_out[i] = mpfr_get_d(tabf_tmp[i], MPFR_RNDD); }
}*/
void init_tabf(mpfr_t tab[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) {
		mpfr_init2(tab[i], PRECISION);
	}
}
void clear_tabf(mpfr_t tab[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) {
		mpfr_clear(tab[i]);
	}
}
int distribute_(double X, double tab_in[], double tab_out[], size_t tabsize) {
	int wynik = 0;
	mpfr_t Xf;
	mpfr_init2(Xf, PRECISION);
	mpfr_set_d(Xf, X, MPFR_RNDD);

	mpfr_t tabsizef;
	mpfr_init2(tabsizef, PRECISION);
	mpfr_set_ui(tabsizef, tabsize, MPFR_RNDD);

	mpfr_t sumaf;
	mpfr_init2(sumaf, PRECISION);
	mpfr_set_d(sumaf, 0.0, MPFR_RNDD);

	mpfr_t tabf_tmp[tabsize];
	mpfr_t tabf_in[tabsize];

	init_tabf(tabf_tmp, tabsize);
	init_tabf(tabf_in, tabsize);

	copy_tab_(tab_in, tabf_in, tabsize);

	for(size_t i=0;i<tabsize;++i) { mpfr_div(tabf_tmp[i], Xf, tabsizef, MPFR_RNDD); }
	for(size_t i=0;i<tabsize;++i) { mpfr_div(tabf_tmp[i], tabf_tmp[i], tabf_in[i], MPFR_RNDD); }
	sum_tabf(&sumaf, tabf_tmp, tabsize);
	if(mpfr_cmp_d(sumaf, 0.0)) {
		mpfr_t ratiof;
		mpfr_init2(ratiof, PRECISION);
		mpfr_div(ratiof, Xf, sumaf, MPFR_RNDD);
		for(size_t i=0;i<tabsize;++i) { mpfr_mul(tabf_tmp[i], tabf_tmp[i], ratiof, MPFR_RNDD); }
		mpfr_clear(ratiof);
	}
	sum_tabf(&sumaf, tabf_tmp, tabsize);
	if(mpfr_cmp_d(sumaf, X)) { wynik = 1; }
	copy_tab__(tabf_tmp, tab_out, tabsize);
	clear_tabf(tabf_tmp, tabsize);
	clear_tabf(tabf_in, tabsize);
	mpfr_clear(Xf);
	mpfr_clear(tabsizef);
	return wynik;
}
void sum_tabf(mpfr_t *sumaf, mpfr_t tabf_tmp[], size_t tabsize) {
	mpfr_set_d(*sumaf, 0.0, MPFR_RNDD);
	for(size_t i=0;i<tabsize;++i) { mpfr_add(*sumaf, *sumaf, tabf_tmp[i], MPFR_RNDD); }
}
void print_tab(double tab[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) {
		printf("%10.50f", tab[i]);
		if((i%3)==2) { printf("\n"); }
		else { printf(" "); }
	}
}

double sum_tab(double tab[], size_t tabsize) {
	double sum = 0.0;
	for(size_t i=0;i<tabsize;++i) { sum += tab[i]; }
	return sum;
}

void copy_tab(double tab_in[], double tab_out[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) { tab_out[i] = tab_in[i]; }
}

void print_output(double X, double tab_in[], double tab_out[], size_t tabsize) {
	puts("tab_in");
	print_tab(tab_in, tabsize);
	printf("\n");
	printf("%12s = %10.50f\n", "X", X);
	double suma = sum_tab(tab_out, tabsize);
	printf("%12s = %10.50f\n", "suma tab_out", suma);
	int difference = (suma == X);
	printf("czy suma tab_out równa się X: %s\n", difference ? "tak" : "nie");
	if(!difference) { printf("różnica = %.50f\n", X-suma); };
	puts("tab_out");
	print_tab(tab_out, tabsize);
	printf("\n");
}