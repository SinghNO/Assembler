#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

mot_tab* search_mot(mot_tab *tab, char *str, int size) {
	mot_tab *res = NULL;
	while(size--) {
		if(!strcasecmp(str, tab[size].mnemonic)) {
			res = (mot_tab *)malloc(sizeof(mot_tab));
			strcpy(res->mnemonic, tab[size].mnemonic);
			res->opcode = tab[size].opcode;
			res->len = tab[size].len;
			res->ops = tab[size].ops;		
			return res;
		}
	}
	return NULL;
}

int read_mot(char *file, mot_tab *mot) {
	FILE *fd;
	char mnemonic[50];
	int opcode, len, ops, count, size;
	fd = fopen(file, "r");
	count = 0;
	size = 64;
	while((fscanf(fd, "%s%d%d%d", mnemonic, &opcode, &ops, &len)) != -1) {
		strcpy(mot[count].mnemonic, mnemonic);
		mot[count].opcode = opcode;
		mot[count].len = len;
		mot[count].ops = ops;
		count++;
		if(count == size) {
			size *= 2;
			mot = (mot_tab *)realloc(mot, sizeof(mot_tab) * size);
		}
	}

	fclose(fd);
	return count;
}

int read_pot(char *file, pot_tab *pot) {
	FILE *fd;
	char popcode[50];
	int len, ops, count, size;
	
	fd = fopen(file, "r");
	count = 0;
	size = 64;

	while((fscanf(fd, "%s%d%d", popcode, &ops, &len)) != -1) {
		strcpy(pot[count].popcode, popcode);
		pot[count].len = len;
		pot[count].ops = ops;
		count++;
		if(count == size) {
			size *= 2;
			pot = (pot_tab *)realloc(pot, sizeof(pot_tab) * size);
		}
	}

	fclose(fd);
	return count;
}


mot_tab* init_mot(mot_tab *tab) {
	int size = 64;
	tab = (mot_tab *)malloc(sizeof(mot_tab) * size);
	return tab;
}

pot_tab* init_pot(pot_tab *tab) {
	int size = 64;
	tab = (pot_tab *)malloc(sizeof(pot_tab) * size);
	return tab;
}

sym_tab* init_sym(sym_tab *tab) {
        int size = 64;
        tab = (sym_tab *)malloc(sizeof(sym_tab) * size);
        return tab;
}

int search_label(char *arr) {
        int i = 0;
        while(arr[i] != '\0') {
                if(arr[i] == ':') {
                        arr[i] = '\0';
                        return 2;                                       //label found
                }
                i++;
        }
        return 0;                                                       //no label found
}


int search_sym(sym_tab *tab, char *str, int size) {
        while(size--) {
                if(!strcasecmp(str, tab[size].symbol)) {			//already in symbol table
                        return 1;
                }
        }
        return 0;
}

