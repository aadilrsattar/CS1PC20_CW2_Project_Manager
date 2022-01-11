#include <dirent.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _DIR 1              
#define MAX_NUM 100           
#define NAME_LENGTH 100	//defines numbers to be used for variables

int dup=0;

int list_file_type(char type, char result[MAX_NUM][NAME_LENGTH])
{

	DIR *d;                                                  
	struct dirent *dir;           
	d = opendir(".");             
		int count=0;                  //opens the directory and takes each of the names of each folder
  	if (d)
  	{
    	while ((dir = readdir(d)) != NULL) {                             
          	if (type == _DIR && dir->d_type == DT_DIR)                 
          	{
                strcpy(result[count++],dir->d_name);                 
          	}
    	} 
    	closedir(d);                                                     
  	}
  	return(count);                                                     
	}
int main(void){
	char given[100];
  	FILE *fptr;
  	fptr = fopen("temp.txt", "r");
  	(fscanf(fptr, "%[^\n]", given));		//takes the word that came from the shell file and puts it in to variable given
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

	if (dup==1) 
	{
		printf("A folder of that name already exists.  Aborting. \n");
	}

	else 
	{
		char command[200];		
		snprintf(command,sizeof(command), "mkdir %s", given);
		system(command);
		
		char command1[200];				
		snprintf(command1,sizeof(command1), "make feature NAME=%s >/dev/null", given);	//makes a feature with the name of the feature, using Makefile
		system(command1);

	}
}
