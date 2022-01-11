#include <dirent.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _DIR 1             
#define MAX_NUM 100           
#define NAME_LENGTH 100	//defines numbers to be used for variables

int list_file_type(char type, char result[MAX_NUM][NAME_LENGTH]){
	DIR *d;                                                  
	struct dirent *dir;           
	d = opendir(".");             
	int count=0;                  
	if (d){
    	while ((dir = readdir(d)) != NULL) {                             
          	if (type == _DIR && dir->d_type == DT_DIR){
                strcpy(result[count++],dir->d_name);       	//opens the directory and takes each of the names of each folder
          	}
    	} 
	closedir(d);                                                     
    	}
  	return(count);                                                     
}

int dup=0;
int main(void){
	char given[100];
  	FILE *fptr;
  	fptr = fopen("temp.txt", "r");	//takes the word that came from the shell file and puts it in to variable given
  	(fscanf(fptr, "%[^\n]", given)); 
	fclose(fptr);
	remove("temp.txt");
	
  	char typ=_DIR;                                                     
  	char result_list[MAX_NUM][NAME_LENGTH];                   
  	int num_found;                                             
  	num_found= list_file_type(typ, result_list);                       
	for (int i=0;i<num_found;i++)
  		if (strcmp(result_list[i],given)==0){		//compares the name of the folders to given to make sure the name is not already taken
    		dup=1;
    		}

	if (dup==1) {
		printf("A folder of that name already exists.  Aborting. \n");
	}
	else {
		char command[1000];
		snprintf(command,sizeof(command), "git init %s", given);
		system(command);
		snprintf(command,sizeof(command), "make feature NAME=%s >/dev/null", given );		//makes a feature with the name of the project, using Makefile
		system(command);
	}
}
