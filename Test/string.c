// Arquivo de teste biblioteca string
#include<stdio.h>
#include<stdlib.h>
#include "../library/string.h"

int main(void) {
	int i=0;
	char *string, *string2, *string3;
	string = (char*) malloc(sizeof(char)*100);
	scanf("%s", string);
	//scanf("%s", string2);
	strcpy(string, &string2);
	printf("%d", strlen(string));
	printf("\n%s", string2);
	
	
	return 0;
}
