// Arquivo de teste biblioteca string
#include<stdio.h>
#include "../library/string.h"

int main(void) {
	String *string;
	printf("fff");
	inicString(&string);
	addCaractere(&string, 'C');
	exibeString(string);
	return 0;
}
