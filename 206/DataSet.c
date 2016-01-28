#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 40
#define MAXLINE 200

int numExperiments;

void individualAverage(const char *exps[20], const int dt[10][20]){
	printf("Which Experiment? Enter number:");
	int num, average = 0;
	scanf("%d", &num); num--;
	if(num>=0&&num<numExperiments){
		for (int i = 0; i < 10; i++)
			average += dt[i][num];
		average = average/10;
		printf("The individual average is: %d\n", average);}
	else {printf("Invalid Choice\n");
		return;}}

void allAverage(const char *exps[20], const int dt[10][20]){
	int average = 0;
	for (int i = 0; i < numExperiments; i++){
		for (int j = 0; j < 10; j++)
			average += dt[j][i];}
	average = average/(10*numExperiments);
	printf("The overall average is: %d\n", average);}

void displayAll(const char *exps[20], const int dt[10][20]){
	for(int i = 0; i<numExperiments; i++){
		printf("%s", exps[i]);
		for(int j = 0; j<10; j++)
				printf("%d ", dt[j][i]);
		printf("\n");}}

void menu(){
	printf("DATA SET ANALYSIS\n"
			"1. Show all the data\n"
			"2. Calculate the average for an experiments\n"
			"3. Calculate the average for all experiments\n"
			"4. Quit\n"
			"Selection:");}

int main(int argc, char const *argv[]){

	char *experiments[20];
	int data[10][20];
	int index = 0;
	experiments[0] = malloc(sizeof(char)*SIZE);
	
	while(fgets(experiments[index],MAXLINE,stdin)!=NULL){
		
		char *string = strdup(experiments[index]);

		if(strstr(string, "*** END ***") != NULL) break;
		
		else{ 
			numExperiments++;

			char obvs[SIZE];
			fgets(obvs, MAXLINE, stdin);
			sscanf(obvs, "%d %d %d %d %d %d %d %d %d %d",
				&data[0][index], &data[1][index], 
				&data[2][index], &data[3][index],
				&data[4][index], &data[5][index],
				&data[6][index], &data[7][index],
				&data[8][index], &data[9][index]);

			index++; experiments[index] = malloc(sizeof(char)*SIZE);}}

	freopen("/dev/tty", "r", stdin);

	menu();
	char choice;
	
	do{
		scanf(" %c", &choice);
		switch(choice){
			case '1':
				displayAll(experiments, data);
				menu();
				break;
			case '2':
				individualAverage(experiments, data);
				menu();
				break;
			case '3':
				allAverage(experiments, data);
				menu();
				break;
			case '4': 
				break;
			default:
				printf("Invalid choice try again\n");
				menu();
				break;}}
	while(choice != '4');

	return 0;}