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

typedef struct littab {
	char literal[64];
	int value;
	int line_no;
	int address;
}lit_tab;

int search_mot(mot_tab *tab, mot_tab *res, char *str, int size);			//Search from mot
int read_mot(char *file, mot_tab *tab);							//Fill mot

int search_pot(pot_tab *tab, pot_tab *res, char *str, int size);			//Search from pot
int read_pot(char *file, pot_tab *tab);							//Fill pot

int lit_sym_tab(lit_tab *tab, char *literal, int value, int line_no, int address);	//Add to literal table
int add_sym_tab(sym_tab *tab, char *symbol, char *type, int address);			//Add to symbol table

mot_tab* init_mot(mot_tab *tab);							//Initialize mot
pot_tab* init_pot(pot_tab *tab);							//Initialize pot
sym_tab* init_sym(sym_tab *tab);							//Initialize symbol table

int tokenize(char *line, char arr[16][64]);
int search_label(char *arr);								//To search whether it is a label
