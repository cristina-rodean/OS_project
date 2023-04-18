#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


int FileType(char *path, struct stat *buff){
    

    if(stat(path, buff) == 0) { //for files and directories 
        if(S_ISREG(buff->st_mode) != 0) { //if it's a regular file
            return 0; 
        }
        else if(S_ISDIR(buff->st_mode) != 0) { // if it's a directory
            return 1;
        }
    } 

    if(lstat(path, buff)==0){ //for sym links
        if(S_ISLNK(buff->st_mode)!=0) //if it's a symlink
                return 2;
    }

    return -1;
}

void menuForRegular(char *filename){
    
    
    printf("---- MENU ----\n");
    printf("* n: name\n");
    printf("* m: last time of modif\n");
    printf("* a: access\n");
     
    printf("\nPlease enter your options\n\n");
    printf("STANDARD INPUT: ");

    char input[10];
    struct stat buff;
    fgets(input, 10, stdin);
    
    for(int i=1;i<strlen(input)-1; i++){
        if(input[i]=='n')
            printf("Name of file:%s\n", filename );
        else
            if(input[i]=='d')
              printf("Size: %d bytes\n", (int)buff.st_size);
            else
               if(input[i]=='h')    
                  printf("Hard links count: %d\n", (int)buff.st_size);
               else
                  if(input[i]=='m')
                     printf("Time of last modification: %ld\n", buff.st_mtime);
                     
    }


}

int main(int argc, char **argv){

    struct stat *buff;
    buff =(struct stat *)malloc(sizeof(struct stat));

    if(argc>1){
        for(int i=0; i<argc; i++){//firstly we check which type of file do we have
            int typeOfFile=FileType(argv[i], buff);

            if (typeOfFile==0){
                printf("REGULAR FILE\n");
                menuForRegular(argv[i]);
            }

            if (typeOfFile==1){
                printf("DIRECTORY\n");
            }

            if (typeOfFile==2){
                printf("SYMBOLIC LINK\n");
            }
        }
    }

}