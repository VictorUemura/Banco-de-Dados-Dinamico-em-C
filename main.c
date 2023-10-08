#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>
#include "./library/fila.h"
#include "./library/tad.h"
#include "./library/Refat/utils.h"

int main(void) {
	DescFilaString F;
	init(&F);
	char string[100];
	gets(string);
	printf("%s\n", string);
	criaFilaS(string, &F);
	exibeFila(F);
	
	return 0;
}
