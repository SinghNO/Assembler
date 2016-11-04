typedef struct mot {
	char mnemonic[64];
	int opcode;
	int ops;
	int len;	
}mot_tab;

typedef struct pot {
	char popcode[64];
	int ops;
	int len;
}pot_tab;

typedef struct symtab {
	char symbol[64];
	char type[64];
	int address;
}sym_tab;

mot_tab* init_mot(mot_tab *tab);
int read_mot(char *file, mot_tab *tab);	
mot_tab* search_mot(mot_tab *tab, char *str, int size);	
				
pot_tab* init_pot(pot_tab *tab);	
int read_pot(char *file, pot_tab *tab);
pot_tab* search_pot(pot_tab *tab, char *str, int size);	

sym_tab* init_sym(sym_tab *tab);
sym_tab* search_sym(sym_tab *tab, char *str, int size);

int tokenize(char *line, char arr[16][64]);
int is_label(char *arr);
int is_comment(char *arr);

