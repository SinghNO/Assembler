#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pass1.h"

extern int ssize;

void pass2(sym_tab* tab) {
	FILE *obj;
	FILE *inter;
	char lc[64];
	char symbol[64];	
	obj = fopen("object.txt", "w+");
	inter = fopen("intermediate.txt", "r");
	
	if(obj == NULL) {
		perror("ERROR IN OPERATIONS\n");
		return;
	}
	
	if(inter == NULL) {
		perror("ERROR IN OPERATIONS\n");
		return;
	}

	while(fscanf(inter, "%s\t%s", lc, symbol) != -1) {
		sym_tab *res;
		if((res = search_sym(tab, symbol, ssize))) {
			fprintf(obj, "%s\t%d\n", lc, res->address);
		}
		else if(!(res = search_sym(tab, symbol, ssize))) {
			fprintf(obj, "%s\t%s\n", lc, symbol);
		}
	}
	return;
}
