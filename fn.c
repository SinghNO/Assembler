#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pass1.h"

int is_comment(char *arr) {
	if(arr[0] == ';')
		return 1;
	return 0;
}

int is_label(char *arr) {
        int i = 0;
        while(arr[i] != '\0') {
        	if(arr[i] == ':') {
        		arr[i] = '\0';
        		return 1; 
        	}
        	i++;
        }
        return 0;
}

int tokenize(char *line, char arr[16][64]) {
	int i, slen;
	char *s;

	i = slen = 0;
	s = strtok(line, " ");
	if(s) {
		slen = strlen(s);
		if(s[slen - 1] == '\n')
			s[slen - 1] = '\0';
	}
	strcpy(arr[0], s);
    while(s != NULL) {
		i++;
		s = strtok(NULL, " ");
		if(s) {
			slen = strlen(s);
			if(s[slen - 1] == '\n') {
				s[slen - 1] = '\0';
			}	
			strcpy(arr[i], s);
		}
    }

	return i;
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

pot_tab* search_pot(pot_tab *tab, char *str, int size) {
	pot_tab *res = NULL;
	while(size--) {
		if(!strcasecmp(str, tab[size].popcode)) {
			res = (pot_tab *)malloc(sizeof(pot_tab));
			strcpy(res->popcode, tab[size].popcode);
			res->len = tab[size].len;
			res->ops = tab[size].ops;		
			return res;
		}
	}
	return NULL;
}

sym_tab* search_sym(sym_tab *tab, char *str, int size) {
	sym_tab *res = NULL;
	while(size--) {
		if(!strcasecmp(str, tab[size].symbol)) {
			res = (sym_tab *)malloc(sizeof(pot_tab));
			strcpy(res->symbol, tab[size].symbol);
			strcpy(res->type, tab[size].type);
			res->address = tab[size].address;		
			return res;
		}
	}
	return NULL;
}
