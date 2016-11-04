#include "main.h"

extern int error;
extern sym_tab *sym;

int main(int argc, char *argv[]) {
	pass1(argv[1]);
	if(error)
		return -1;
	pass2(sym);
	return 0;
}
