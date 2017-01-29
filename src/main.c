#include <stdio.h>
#include <float.h>
#include "distribute.h"

int main(int argc, char *argv[]) {

	double X = 100;
	double tab_in[] = {20, -10};
	size_t tabsize = sizeof(tab_in)/sizeof(double);
	double tab_out[tabsize];

	distribute_precise(X, tab_in, tab_out, tabsize);
	print_output(X, tab_in, tab_out, tabsize);
	
	return 0;
}
