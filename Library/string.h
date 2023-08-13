
int strlen(char *string) {
	int i=0;
	while(string[i] != '\0')
		i++;
		
	return i;	
}

void strcpy(char *string, char **string2){
	int i=0;
	*string2 = (char*) malloc(sizeof(char)*strlen(string));
	while(string[i] != '\0'){
		(*string2)[i] = string[i];
		i++;
	}
	(*string2)[i] = '\0';
}

char strcmp(char *string1, char *string2) {
	int i = 0;
	while(string1[i] != '\0' && string2[i] != '\0' && string1[i] == string2[i])
		i++;
	if(string1[i] < string2[i] || (string1[i] == '\0' && string2[i] != '\0'))
		return -1;
	else if(string1[i] == string2[i])
		return 0;
	else
		return 1;
}

char stricmp(char *string1, char *string2) {
	int i = 0;
	char caractere1, caractere2;
	do {
		caractere1 = string1[i];
		caractere2 = string2[i];
		if(caractere1 >= 65 && caractere1 <= 90)
			caractere1 += 32;
		if(caractere2 >= 65 && caractere2 <= 90)
			caractere1 += 32;
		if(caractere1 == caractere2)
			i++;
	} while(string1[i] != '\0' && string2[i] != '\0' && caractere1 == caractere2);
	if((string1[i] == '\0' && string2[i] != '\0') || caractere1 < caractere2)
		return -1;
	else if((string1[i] != '\0' && string2[i] == '\0') || caractere1 > caractere2)	
		return 1;
	else
		return 0;
}

