#include <dirent.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define _FILE 1             
#define MAX_NUM 100           
#define NAME_LENGTH 100	//defines the integer to use with the variables


int duped=0;

int list_file_type(char type, char result[MAX_NUM][NAME_LENGTH])
{
  DIR *d;                                                  
  struct dirent *dir;           
  d = opendir(".");             
  int count=0;                  
  if (d)
  {
    while ((dir = readdir(d)) != NULL) {                             
    
          if (type == _FILE && dir->d_type == DT_REG)                //opens the directory and takes each of the names of each file
          {
                strcpy(result[count++],dir->d_name);                 
          }
    }
    closedir(d);                                                     
  }
  return(count);                                                     
}
int main(void)
{
  	char typ=_FILE;                                                     
  	char result_list[MAX_NUM][NAME_LENGTH];                          
  	int num_found;                                             
  	typ=_FILE; 
   	num_found= list_file_type(typ, result_list);                                          
	
	char pmtag[100]=".pmtag";					//compares the name of the files to check if there are any .pmtag file
	
  	for (int i=0;i<num_found;i++)
  		if (strcmp(result_list[i],pmtag)==0)		
  		{
    			duped=1;
    		}

	if (duped==1) 
	{
		char init[100];
  		FILE *fptr;
  		fptr = fopen(".pmtag", "r");
  		(fscanf(fptr, "%[^\n]", init));
		fclose(fptr);
		printf("Already tag in this folder\n");		//if there is already a file with that name, it checks the tag inside of the file, and reports it to the user
		printf("%s\n", init);


	}
	else 
	{
	
		char given[MAX_NUM];
		char path[MAX_NUM];
		
  		FILE *fptr;
 		fptr = fopen("temp.txt", "r");
  		(fscanf(fptr, "%[^\n]", given));		//takes the text given by the C file and puts it in to the variable given, to be added to the file .pmtag
		fclose(fptr);
		
  		fptr = fopen(".pmtag", "w");
  		fprintf(fptr,"%s\n", given);			//writes the given to the file .pmtag
		fclose(fptr);
		
		strcat(given,"-");
		fptr = fopen("/home/pat/cw2/tags", "a");	//adds the tag and the tag location to the main directory, to later help with the finding the tags
  		fprintf(fptr,"%s\n", given);
		fclose(fptr);
		
		getcwd(path, MAX_NUM);
		fptr = fopen("/home/pat/cw2/tagsloc", "a");
  		fprintf(fptr,"%s\n", path);
		fclose(fptr);
		
		
			
		
	}
}
