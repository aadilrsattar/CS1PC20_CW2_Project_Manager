#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

void listfiles(const char* dirname, int level) {
	DIR* dir = opendir(dirname);		//opens directory
	if (dir == NULL) {
		return;
	}

	struct dirent* entity;
	entity = readdir(dir);	//reads directory
	while (entity != NULL) {
		if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0)  {
	   		char str_level[150];		//removes all the files starting with . and any files that are outside of the current forward directory (./..)
	   		strcpy(str_level,"");
	   		for (int i =0;i < level; i++)
	   		{
				strcat(str_level,"*");		//depending on how deep it is in the subdirectories, adds a star
	   		}
	   		char cont[2000];
	   		strcpy(cont,str_level);
	   		strcat(cont," ");
	   		strcat(cont,entity->d_name);		
	   		strcat(cont, " ");
	   		strcat(cont,"\n");
	   		FILE* fp = fopen("DrawWBS.txt","a");		//opens to DrawWBS.txt in append mode
	   		fputs(cont,fp);
	   		fclose(fp);
		    	char path[100] = { 0 };
		    	printf(path,"%s");
		    	strcat(path, dirname);
		    	strcat(path, "/");
		    	strcat(path, entity->d_name);		//writes to DrawWBS.txt
		    	listfiles(path,level+1);
			}
		entity = readdir(dir);
	    	}

	    closedir(dir);
	}

	int draw_list_files(char *name){
	    	FILE* fp = fopen("DrawWBS.txt", "w");		//opens file again to provide opening and ending of the txt
	    	char cont[2000];
	    	strcpy(cont,"@startwbs\n");
		strcat(cont,"* ");
	    	strcat(cont,name);
	    	strcat(cont,"\n");
		fputs(cont, fp);
	    	fclose(fp);
	    	listfiles(name,2);
	    	fopen("DrawWBS.txt","a");
	    	fputs("@endwbs", fp);
	    	fclose(fp);
	}

	int main(int argc, char* argv[]){
	    	draw_list_files(".");
	}

	 
