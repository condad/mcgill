#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100
char delim[4] = ",\r\n";

void add(const char *i, const char *q, const char *r, const char *c){
	FILE *file = fopen("inventory.csv", "a+");
	char *string = malloc(sizeof(char)*SIZE);
	
	sprintf(string,"%s,%s,%s,%s\r\n",i,q,r,c);
	fputs(string, file);
	fclose(file);}

void deduct(const char *key){
	char *item[10];
	FILE *ofile = fopen("inventory.csv", "r");
	char *string = malloc(sizeof(char)*SIZE);

	FILE *nfile = fopen("new.csv", "wt");

	while(fgets(string, SIZE, ofile)!=NULL){
		
		if(strstr(string, key)!=NULL){
			item[0] = strtok(string, delim);
			for (int i = 1; i < 4; ++i)
				item[i] = strtok(NULL, delim);
			sprintf(string,"%s,%d,%s,%s\r\n",
				item[0],atoi(item[1])-1,item[2],item[3]);}
		
		fputs(string, nfile);}
		
	fclose(ofile);
	fclose(nfile);
	remove("inventory.csv");
	rename("new.csv", "inventory.csv");}

void reorder(){
	char *item[10];
	char *string = malloc(sizeof(char)*SIZE);
	FILE *file = fopen("inventory.csv", "r");
	
	printf("***REORDER THE FOLLOWING***\n");
	
	while(fgets(string, SIZE, file)!=NULL){
		item[0] = strtok(string, delim);
		for (int i = 1; i < 4; ++i)
			item[i] = strtok(NULL, delim);
		if(atoi(item[2])>=atoi(item[1]))
			printf("%s\n",item[0]);}
	fclose(file);}

void list(){
	char *item[10];
	char *string = malloc(sizeof(char)*SIZE);
	FILE *file = fopen("inventory.csv", "r");
	
	printf("%-10s%-10s%-10s%-10s\n","ITEM","QUANTITY","REORDER","COST");
	
	while(fgets(string, SIZE, file)!=NULL){
		item[0] = strtok(string, delim);
		for (int i = 1; i < 4; ++i)
			item[i] = strtok(NULL, delim);
		printf("%-10s%8d%9d%10.2f\n",
			item[0],atoi(item[1]),atoi(item[2]),atof(item[3]));}
	fclose(file);}

int main(int argc, char const *argv[]){

	char *option = malloc(sizeof(char)*20);
	strcpy(option, argv[1]);
	
	switch(option[0]){
		case 'l':
			list();
			break;
		case 'r':
			reorder();
			break;
		case 'd':
			deduct(argv[2]);
			break;
		case 'a':
			add(argv[2],argv[3],argv[4],argv[5]);
			break;}

	return 0;}