#include "stdio.h"

void reverse (char* str);

int main() {
	char str[5] = "abcd";
	printf("%s\n", str);
	reverse(str);
	printf("reversed string %s\n", str);
	return 0;
}

void reverse (char* str) {
	char* tmp = str;
	printf("%s %s\n", tmp, str);
	while (*tmp != '\0') 
		tmp++;
	tmp--;
	while (*str != '\0') 
		*str++ = *tmp--;
	str = '\0';
}