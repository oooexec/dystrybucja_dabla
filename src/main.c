#include <stdio.h>
#include <float.h>
#include "funkcje_nieposortowane.h"

int main(int argc, char *argv[]) {

	double X = 1000;
	double tab_in[] = {DBL_MAX, DBL_MAX, DBL_MAX};
	size_t tabsize = sizeof(tab_in)/sizeof(double);
	double tab_out[tabsize];

	//if(distribute_(X, tab_in, tab_out, tabsize)) {
	//	printf("Brak możliwości dystrybucji podanej liczby.\n");
	//}
	//distribute(X, tab_in, tab_out, tabsize);

	distribute_(X, tab_in, tab_out, tabsize);
	print_output(X, tab_in, tab_out, tabsize);
	
	return 0;
}