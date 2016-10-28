#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#define M 16									//Size for arr	
#define N 64

int main (int argc, char *argv[]) {
	FILE *in;
	FILE *inter;
	char line[1024];
	char arr[M][N];
	int i, mot_size = 64, pot_size = 64;
	mot_tab *mot;
	pot_tab *pot;
    
	mot = init_mot(mot);
	pot = init_pot(pot);

	mot_size = read_mot("mnemonic.txt", mot);
	pot_size = read_pot("popcode.txt", pot);

	i = 0;	
	in = fopen(argv[1], "r");						//Input file
	inter = fopen("intermediate.txt", "w+");				//Intermediate file

    	if(in == NULL) {
    		perror("ERROR IN OPERATIONS\n");
    		return -1;
    	}

	if(inter == NULL) {
		perror("ERROR IN OPERATIONS\n");
                return -1;
	}

	while(fgets(line, 1024, in) != NULL) {
        	tokenize(line, arr);
		if(search_label(arr[i])) {
			//check whether it is already there in sym_tab 
			
			//if not then insert into sym_tab
			
			i++;
		}

		mot_tab *res;
		if(search_mot(mot, res, arr[i], mot_size)) {
			printf("okay acha hai\n"); 			//Add to intermediate file
		}
	}

	return 0;
}

int tokenize(char *line, char arr[M][N]) {				//Returns no of tokens
	int i = 0;
	char *s;
	s = strtok(line, " ");
	strcpy(arr[0], s);
        while(s != NULL) {
		printf("%d\n", i);
		i++;
		s = strtok(NULL, " ");
		if(s && s[0] == ';' ) {					//Comments
			return i;
		}
		else if(s) {
			strcpy(arr[i], s);
		}
        }
	return i;
}

int search_label(char *arr) {
	int i = 0;
	while(arr[i] != '\0') {
		if(arr[i] == ':') {
			arr[i] = '\0';
			return 2; 					//label found
		}
		i++;
	}
	return 0;							//no label found
}

int search_symtab(char *arr, sym_tab *tab, ) {				//returns -1 if label is already ther in sym_tab
	
	return 0;
}
