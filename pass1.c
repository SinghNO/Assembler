#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pass1.h"

int error;
sym_tab *sym;

void pass1(char *input) {
	
	FILE *in, *inter, *symtab;

	mot_tab *mot;
	pot_tab *pot;
	
	int msize, psize, ssize;
	int scount, tcount, lcount;
	int cseg, dseg;
	int lc;
	int i, j;

	char line[1024], arr[16][64];
	
	in = fopen(input, "r");
	inter = fopen("intermediate.txt", "w");
	symtab = fopen("symbol.txt", "w");
	if(in == NULL || inter == NULL || symtab == NULL) {
		perror("Unable to open file\n");
		return;
	}

	mot = init_mot(mot);
	pot = init_pot(pot);
	sym = init_sym(sym);

	scount = tcount = lcount = 0;
	ssize = 64;
	cseg = dseg = error = 0;
	lc = 0;
		
	msize = read_mot("mnemonic.txt", mot);
	psize = read_pot("popcode.txt", pot);

	while(fgets(line, 1024, in) != NULL) {
		lcount++;	
		tcount = tokenize(line, arr);
		for(i = 0; i < tcount; i++) {
			if(!(strcasecmp(arr[i], "start"))) {
				char *endptr;
				long int temp = strtol(arr[i + 1], &endptr, 10);
				if(*endptr == '\0')
					lc = (int)temp;
				cseg = 1;
				break;
			}
		}
		if(cseg)
			break;
	}

	if(cseg) {
		while(fgets(line, 1024, in) != NULL) {	
			lcount++;
			tcount = tokenize(line, arr);
			for(i = 0; i < tcount; i++) {
				mot_tab *mres;
				pot_tab *pres;
				if(is_comment(arr[i]))
					break;
				else if(is_label(arr[i])) {
					if(search_sym(sym, arr[i], ssize)) {
						error = 1;
						printf("%s:%d: Duplicate label\n", input, lcount);
						continue;
					}
					else {
						strcpy(sym[scount].symbol, arr[i]);
						strcpy(sym[scount].type, "label");
						sym[scount].address = lc;
						scount++;
						if(scount == ssize) {
							ssize *= 2;
							sym = (sym_tab *)realloc(sym, sizeof(sym_tab) * ssize);
						}
					}
				}
				else if((mres = search_mot(mot, arr[i], msize))) {
					fprintf(inter, "%d\t%d\n", lc, mres->opcode);
					lc += mres->len;
					for(j = 0; j < mres->ops; j++) {
						i++;
						if(!(search_sym(sym, arr[i], ssize))) {
							strcpy(sym[scount].symbol, arr[i]);
							strcpy(sym[scount].type, "id");
							sym[scount].address = -1;
							scount++;
							if(scount == ssize) {
								ssize *= 2;
	            	            sym = (sym_tab *)realloc(sym, sizeof(sym_tab) * ssize);
                           	}
						}
						fprintf(inter, "%d\t%s\n", lc, arr[i]);
						lc++;
					}
					free(mres);
				}
				else if((pres = search_pot(pot, arr[i], psize))) {
					if(!(strcasecmp("start", pres->popcode))) {
						error = 1;
						printf("%s:%d:Multiple use of 'start' directive\n", input, lcount); 
						continue;
					}
					else if(!(strcasecmp("endp", pres->popcode))) {
						dseg = 1;
						cseg = 0;
						break;
					}
					else if(!(strcasecmp("end", pres->popcode))) {
						error = 1;
						printf("%s:%d:No data segment\n", input, lcount);
						continue;
					}
				}
				else {
					if(tcount) { 
						error = 1;
						printf("%s:%d:Invalid token\n", input, lcount);
						continue;
					}
					else {
						error = 1;
						printf("%s:%d:No 'end' directive\n", input, lcount);
						continue;
					}
				}	
			}
			if(dseg)
				break;
		}	
	}
	else {
		error = 1;
		printf("No start directive found\n");
	}

	if(dseg) {
		while(fgets(line, 1024, in) != NULL) {
			lcount++;
			tcount = tokenize(line, arr);
			for(i = 0; i < tcount; i++) {
				pot_tab *pres;
				if(!(strcasecmp("end", arr[i]))) {
					dseg = 0;
					break;
				}
				else if((pres = search_pot(pot, arr[i + 1], psize))) {
					char *endptr;
					long int temp = strtol(arr[i + 2], &endptr, 10);
					if(*endptr == '\0') {
						fprintf(inter, "%d\t%d\n", lc, (int)temp);
						strcpy(sym[scount].symbol, arr[i]);
						strcpy(sym[scount].type, "variable");
						sym[scount].address = lc;
						lc += pres->len;
						scount++;
						if(ssize == scount) {
							ssize *= 2;
							sym = (sym_tab *)realloc(sym, sizeof(sym_tab) * ssize);
						}
						i += 2;
					}
					else {
						error = 1;
						printf("%s:%d:Invalid data declaration statement\n", input, lcount);
						continue;
					}
				}
				else {
					if(tcount) {
						error = 1;
						printf("%s:%d:Invalid token\n", input, lcount);
						continue;
					}
					else {
						error = 1;
						printf("%s:%d:No 'end' directive\n", input, lcount);
						continue;
					}
				}
			}
			if(!dseg)
				break;	
		}
		if(dseg) {
			error = 1;
			printf("%s:%d:No 'end' directive\n", input, lcount);
		}
	}
	else {
		error = 1;
		printf("%s:%d:No data segment\n", input, lcount);	
	}

	if(error)
		printf("Failed to assemble %s\n", input);

	for(j = 0; j < scount; j++) 
		fprintf(symtab, "%s\t%s\t%d\n", sym[j].symbol, sym[j].type, sym[j].address);
	
	fclose(in);
	fclose(inter);
	fclose(symtab);

	return;
}
