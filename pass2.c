#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

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
		sym_tab *res = NULL;
		if(search_sym(tab, symbol, 64) != NULL) {
			fprintf(obj, "%s\t%d\n", lc, res->address);
		}
		else if(search_sym(tab, symbol, 64) == NULL) {
			fprintf(obj, "%s\t%s\n", lc, symbol);
		}
	}
	return;
}

sym_tab* search_sym(sym_tab *tab, char *str, int size) {
	sym_tab *res = NULL;
	while(size--) {
		if(!strcasecmp(str, tab[size].symbol)) {
			res = (sym_tab *)malloc(sizeof(sym_tab));
			strcpy(res->symbol, tab[size].symbol);
			strcpy(res->type, tab[size].type);
			res->address = tab[size].address;		
			return res;
		}
	}
	return NULL;
}
