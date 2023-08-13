int strlen(char *string){
	int i=0;
	while(string[i] != '\0')
		i++;
		
	return i;	
}

void strcpy(char *string, char *string2){
	int i=0;
	while(string2[i] != '\0'){
		string[i] = string2[i];
		i++;
	}
	string[i] = '\0';
	
	return string;
}
