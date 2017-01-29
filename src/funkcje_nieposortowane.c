#include <stdio.h>
#include <inttypes.h>
#include <mpfr.h>
#include "funkcje_nieposortowane.h"
void debug_print(mpfr_t *f, char *info) {
	double test = mpfr_get_d(*f, ROUNDING);
	puts("DEBUG");
	puts(info);
	printf("%20.20f\n", test);
	puts("DEBUG");
}
void debug_print2(mpfr_t *f) {
	double test = mpfr_get_d(*f, ROUNDING);
	printf("%20.20f\n", test);
}
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
	for(size_t i=0;i<tabsize;++i) { mpfr_set_d(tab_out[i], tab_in[i], ROUNDING); }
}
void copy_tab__(mpfr_t tab_in[], double tab_out[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) { tab_out[i] = mpfr_get_d(tab_in[i], ROUNDING); }
}
/*
void copy_tab_(mpfr_t tabf_tmp[], double tab_out[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) { tab_out[i] = mpfr_get_d(tabf_tmp[i], ROUNDING); }
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

void distribute_(double X, double tab_in[], double tab_out[], size_t tabsize) {
	//int wynik = 0;
	mpfr_t Xf;
	mpfr_init2(Xf, PRECISION);
	mpfr_set_d(Xf, X, ROUNDING);

	mpfr_t tabsizef;
	mpfr_init2(tabsizef, PRECISION);
	mpfr_set_ui(tabsizef, tabsize, ROUNDING);

	mpfr_t sumaf;
	mpfr_init2(sumaf, PRECISION);
	mpfr_set_d(sumaf, 0.0, ROUNDING);
	//debug_print(&sumaf, "1sumaf");

	mpfr_t tabf_tmp[tabsize];
	mpfr_t tabf_in[tabsize];

	init_tabf(tabf_tmp, tabsize);
	init_tabf(tabf_in, tabsize);

	copy_tab_(tab_in, tabf_in, tabsize);

	//printf("1\n");for(size_t i=0;i<tabsize;++i) { debug_print2(&tabf_tmp[i]); }printf("1\n");

	for(size_t i=0;i<tabsize;++i) { mpfr_div(tabf_tmp[i], Xf, tabsizef, ROUNDING); }

	//printf("2\n");for(size_t i=0;i<tabsize;++i) { debug_print2(&tabf_tmp[i]); }printf("2\n");

	for(size_t i=0;i<tabsize;++i) { mpfr_mul(tabf_tmp[i], tabf_tmp[i], tabf_in[i], ROUNDING); }

	//printf("3\n");for(size_t i=0;i<tabsize;++i) { debug_print2(&tabf_tmp[i]); }printf("3\n");

	sum_tabf(&sumaf, tabf_tmp, tabsize);
	//debug
	//debug_print(&sumaf, "sumaf");
	//koniec debug
	if(mpfr_cmp_d(sumaf, 0.0)) {
		mpfr_t ratiof;
		mpfr_init2(ratiof, PRECISION);
		mpfr_set_d(ratiof, 0.0, ROUNDING);
		//debug_print2(&ratiof);
		mpfr_div(ratiof, Xf, sumaf, ROUNDING);
		//debug_print2(&Xf);
		//debug_print2(&sumaf);
		//debug_print2(&ratiof);
		for(size_t i=0;i<tabsize;++i) { mpfr_mul(tabf_tmp[i], tabf_tmp[i], ratiof, ROUNDING); }
		mpfr_clear(ratiof);
	}
	sum_tabf(&sumaf, tabf_tmp, tabsize);
	//debug_print2(&sumaf);
	//if(mpfr_cmp_d(sumaf, X)) { wynik = 1; }
	copy_tab__(tabf_tmp, tab_out, tabsize);
	clear_tabf(tabf_tmp, tabsize);
	clear_tabf(tabf_in, tabsize);
	mpfr_clear(Xf);
	mpfr_clear(tabsizef);
	mpfr_clear(sumaf);
	//return wynik;
}
void sum_tabf(mpfr_t *sumaf, mpfr_t tabf_tmp[], size_t tabsize) {
	mpfr_set_d(*sumaf, 0.0, ROUNDING);
	for(size_t i=0;i<tabsize;++i) { mpfr_add(*sumaf, *sumaf, tabf_tmp[i], ROUNDING); }
}
void print_tab(double tab[], size_t tabsize) {
	for(size_t i=0;i<tabsize;++i) {
		printf("%10.50f", tab[i]);
		printf("\n");
		//if((i%3)==2) { printf("\n"); }
		//else { printf(" "); }
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