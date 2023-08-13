int strlen(char *string){
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


