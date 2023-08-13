
int strlen(char *string){
	int i=0;
	while(string[i] != '\0')
		i++;
		
	return i;	
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
