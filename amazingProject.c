#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



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

int checkPathOfFile(char *path){
    
}

int main(int argc, char **argv){

    struct stat *buff;
    buff =(struct stat *)malloc(sizeof(struct stat));

    if(argc>1){
        for(int i=0; i<argc; i++){//firstly we check which type of file do we have
            int typeOfFile=FileType(argv[i], buff);

            if (typeOfFile==0){
                printf("REGULAR FILE");
            }

            if (typeOfFile==1){
                printf("DIRECTORY");
            }

            if (typeOfFile==2){
                printf("SYMBOLIC LINK");
            }
        }
    }

}