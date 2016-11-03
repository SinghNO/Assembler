#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#define M 16									//Size for arr	
#define N 64

int main (int argc, char *argv[]) {
	FILE *in;
	FILE *inter;
	FILE *symfile;
	char line[1024];
	char arr[M][N];

	int i, j;
	int lc = 0;

	int mot_size = 64;
	int pot_size = 64;
	int sym_size = 64;
	int sym_count = 0;

	mot_tab *mot;
	pot_tab *pot;
	sym_tab *sym;
 
	mot = init_mot(mot);
	pot = init_pot(pot);
	sym = init_sym(sym);

	mot_size = read_mot("mnemonic.txt", mot);
	pot_size = read_pot("popcode.txt", pot);
	
	in = fopen(argv[1], "r");						//Input file
	inter = fopen("intermediate.txt", "w+");				//Intermediate file
	symfile = fopen("symbtab.txt", "w+");

    	if(in == NULL) {
    		perror("ERROR IN OPERATIONS\n");
    		return -1;
    	}

	if(inter == NULL) {
		perror("ERROR IN OPERATIONS\n");
                return -1;
	}

	if(symfile == NULL) {
		perror("ERROR IN OPERATIONS\n");
		return -1;
	}

	while(fgets(line, 1024, in) != NULL) {
		i = 0;
        	int count = tokenize(line, arr);
		if(search_label(arr[i])) {
			if(search_sym(sym, arr[i], sym_size)) {
				perror("Label already used before\n");		//Label already exists in symbol table
				exit(1);
			} 
			else {
				strcpy(sym[sym_count].symbol, arr[i]);
				strcpy(sym[sym_count].type, "label");
				sym[sym_count].address = lc;
				sym_count++;
				if(sym_count >= 64) {
					sym = (sym_tab *)realloc(sym, sizeof(sym_tab) * sym_size * 2);
				}	
			}
			i++;
			count--;
		}
		mot_tab *res;
		if(res = search_mot(mot, arr[i], mot_size)) {
			if(res->ops != count - 1) {
				perror("kuch toh gadbad hai\n");
				return -1;
			}
			fprintf(inter, "%d\t%d\n", lc, res->opcode);
			lc += res->len;
			for(j = 0; j < res->ops; j++) {
				i++;
				if(!(search_sym(sym, arr[i], sym_size))) {
					strcpy(sym[sym_count].symbol, arr[i]);
					strcpy(sym[sym_count].type, "id");
					sym[sym_count].address = -1;
					sym_count++;
					if(sym_count >= 64) {
	                                        sym = (sym_tab *)realloc(sym, sizeof(sym_tab) * sym_size * 2);
                                	}

				}
				fprintf(inter, "%d\t%s\n", lc, arr[i]);
				lc++;
			}						
		}
	}

	for(j = 0; j < sym_count; j++) 
		fprintf(symfile, "%s\t%s\t%d\n", sym[j].symbol, sym[j].type, sym[j].address);
	return 0;
}

int tokenize(char *line, char arr[M][N]) {				//Returns no of tokens
	int i = 0;
	int slen = 0;
	char *s;
	s = strtok(line, " ");
	strcpy(arr[0], s);
        while(s != NULL) {
		i++;
		s = strtok(NULL, " ");
		if(s && s[0] == ';' ) {					//Comments
			return i;
		}
		else if(s) {
			slen = strlen(s);
			if(s[slen - 1] == '\n') {
				s[slen - 1] = '\0';
			}	
			strcpy(arr[i], s);
		}
        }
	return i;
}
