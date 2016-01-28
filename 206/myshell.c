#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){

	char *command = malloc(sizeof(char)*100);

	do{
		printf(">>");
		scanf("%s", command);
		if(strcmp(command, "done")!=0)
			system(command);}
	while(strcmp(command, "done")!=0);

	printf("Thank you for using mysh!!\n");

return 0;}