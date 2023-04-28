#include <stdio.h>
#include <unistd.h>
#include <string.h>
int _strcmp(const char string1[], const char string2[])
{
    	int i = 0;
	while (string1[i] == string2[i]) {
        	if (string1[i] == '\0' || string2[i] == '\0')
			 break;
		i++;
   		}
	        if (string1[i] == '\0' && string2[i] == '\0')
	            return 0;
	        else
		    return -1;
}


int _strncmp(const char *s1, const char *s2, size_t n) {
	size_t i;
	for ( i = 0; i < n; i++) {
		if (s1[i] != s2[i]) {
				return s1[i] - s2[i];
		}
		if (s1[i] == '\0' || s2[i] == '\0') {
				return strlen(s1) - strlen(s2);
		}
	}

	return 0;
}


int _putchar(char c){
	return(write(1, &c, 1));
}


void _puts(char *str){
	int i, j = 0;
	while (str[j] != '\0')
	{
		j++;
	}
	for (i = 0; i < j; i += 2)
	{	
		_putchar(str[i]);
	}
}
