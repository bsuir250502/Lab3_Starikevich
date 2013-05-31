#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "mylib.h"

#define MAXLENGTH 64
// ------------------------------------------
int print_manual() {
	char buffer[MAXLENGTH];
	
	FILE *fp = fopen("README.md", "r");
	while (fgets(buffer, MAXLENGTH, fp)) {
		printf("%s", buffer);
	}
	printf("\n");
	fclose(fp);

	return 0;
}
// ------------------------------------------
char mygets(char *str) {
	fgets(str, MAXLENGTH, stdin);
	str[strlen(str) - 1] = '\0';

	return *str;
}
// ------------------------------------------
int myget_int() {
	int number;
	char buffer[MAXLENGTH];
	
	while (1) {
		fgets(buffer, MAXLENGTH, stdin);
		number = atoi(buffer);
		if (number <= 0) {
			printf("Error! Please, enter the correct number...: ");
			continue;
		}
		break;
	}

	return number;
}
// ------------------------------------------
int myget_int_range(int a, int b) {
	int number;
	
	while(1) {
		number = myget_int();
		if (number >= a && number <= b) {
			return number;
			break;
		} else {
			printf("Error! Please, enter the correct number in range [%d-%d]...: ", a, b);
			continue;
		}
	}
}
// ------------------------------------------
int confirm_choice() {
	char answer;
	
	while(1) {
		answer = getchar();
		__fpurge(stdin);
	
		if(answer == 'y' || answer == 'Y') {
			return 1;
		}
		if(answer == 'n' || answer == 'N') {
			return 0;
		}
		printf("\nError! Please, make your choice... (y/n)? ");
	}
}
// ------------------------------------------
#ifdef __cplusplus
}
#endif
