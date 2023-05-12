#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

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

void printName(char *filename){
    printf("Name of file:%s\n", filename);
}

void menuForRegular(char *filename){
    
    printf("---- MENU ----\n");
    printf("* n: name\n");
    printf("* m: last time of modif\n");
    printf("* a: access\n");
    printf("* d: size of file\n");
    printf("* h: count of hard links\n");
    printf("* l: create symbolic link\n");

    printf("\nPlease enter your options\n\n");
    printf("STANDARD INPUT: ");

    char input[10];
    struct stat buff;

    fgets(input, 10, stdin);
    
    if (stat(filename, &buff) == -1) 
         perror("stat");
                  
    for(int i=1;i<strlen(input)-1; i++){

        if(input[i]=='n')
            printName(filename);
        else{
            if(input[i]=='d')
              printf("Size: %d bytes\n", (int)buff.st_size);
            else
               if(input[i]=='h')    
                  printf("Hard links count: %d\n",(int)buff.st_nlin k);
               else
                  if(input[i]=='m'){
                         printf("Time of last modification: %s\n", ctime(&buff.st_mtime));

                  }
        }
         if (input[i] == 'l') {
                char createLink[15];

                printf("Give the name of symlink: ");
                fgets(createLink, 15, stdin);

                char *newline = strchr(createLink, '\n');
                if (newline != NULL) {
                    *newline = '\0';
                }
            
                 if(symlink(filename, createLink) == 0) {
                        printf("You succeed creating a symbolic link: %s\n", createLink);
                    }
                    else {
                        printf("Fail :(");
                    }
                    printf("\n");
                
            }

            if (input[i] == 'a') {
                
                    printf("Access rights: \n");

                    printf("User:\n");
                    buff.st_mode & S_IRUSR ? printf("   Read - yes\n") : printf("   Read - no\n");
                    buff.st_mode & S_IWUSR ? printf("   Write - yes\n") : printf("   Write - no\n");
                    buff.st_mode & S_IXUSR ? printf("   Execute - yes\n") : printf("   Execute - no\n");
                        
                    printf("Group:\n");
                    buff.st_mode & S_IRGRP ? printf("   Read - yes\n") : printf("   Read - no\n");
                    buff.st_mode & S_IWGRP ? printf("   Write - yes\n") : printf("   Write - no\n");
                    buff.st_mode & S_IXGRP ? printf("   Execute - yes\n") : printf("   Execute - no\n");

                    printf("Other:\n");
                    buff.st_mode & S_IROTH ? printf("   Read - yes\n") : printf("   Read - no\n");
                    buff.st_mode & S_IWOTH ? printf("   Write - yes\n") : printf("   Write - no\n");
                    buff.st_mode & S_IXOTH ? printf("   Execute - yes\n") : printf("   Execute - no\n");

                    printf("\n");
                }
            }

                
    }

void menuForSymlink(char *filename){
 
    printf("---- MENU ----\n");
    printf("* n: name\n");
    printf("* a: access\n");
    printf("* d: size of symbolic link\n");
    printf("* t: size of target file\n");
    printf("* l: delete symbolic link (if you choose this one the other options will no longer be\n");

    printf("\nPlease enter your options\n\n");
    printf("STANDARD INPUT: ");

    char input[10];
    struct stat buff;
    fgets(input, 10, stdin);
    int delete=0;

    for(int i=1;i<strlen(input)-1 && delete==0; i++){
        if(input[i]=='n')
            printName(filename);
        if (input[i] == 'd') {
                
                    printf("Size of symbolic link: %d bytes\n", (int)buff.st_size);
                    printf("\n");
        }
        if (input[i] == 'l') {//daca primesti l nu mai face ce e dupa
            
           if(unlink(filename) == 0) {
                 printf("We deleted it :)\n");
                 delete= 1;
                 
            }
           else {
                 printf("Deleting error :(\n");
             }
                    printf("\n");
                
            }

        if (input[i] == 't') {
             if(stat(filename, &buff)) {
                    printf("An error has occurred\n");
                }
                else {
                   printf("Size of target file: %d bytes\n", (int)buff.st_size);
                    printf("\n");
                }
        }

        if (input[i] == 'a') {
                
            printf("Access rights: \n");

            printf("User:\n");
                buff.st_mode & S_IRUSR ? printf("   Read - yes\n") : printf("   Read - no\n");
                buff.st_mode & S_IWUSR ? printf("   Write - yes\n") : printf("   Write - no\n");
                buff.st_mode & S_IXUSR ? printf("   Execute - yes\n") : printf("   Execute - no\n");
                        
            printf("Group:\n");
                buff.st_mode & S_IRGRP ? printf("   Read - yes\n") : printf("   Read - no\n");                    
                buff.st_mode & S_IWGRP ? printf("   Write - yes\n") : printf("   Write - no\n");
                buff.st_mode & S_IXGRP ? printf("   Execute - yes\n") : printf("   Execute - no\n");

            printf("Other:\n");
                buff.st_mode & S_IROTH ? printf("   Read - yes\n") : printf("   Read - no\n");
                buff.st_mode & S_IWOTH ? printf("   Write - yes\n") : printf("   Write - no\n");
                buff.st_mode & S_IXOTH ? printf("   Execute - yes\n") : printf("   Execute - no\n");

             printf("\n");
        }
    }
}


/**int main(int argc, char **argv){

    
    return 0;
    }

       for (int i = 1; i < argc; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            handle_c_file(argv[i]);
            exit(EXIT_SUCCESS);
        }
        else if (pid < 0) {
            perror("Error forking");
            exit(EXIT_FAILURE);
        }
    }

    int status;
    pid_t w;
    while ((w = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child process %d exited with status %d\n", w, WEXITSTATUS(status));
        }
        else 
           if (WIFSIGNALED(status)) {
              printf("Child process %d terminated by signal %d\n", w, WTERMSIG(status));
        }
    }  
*/


void menuForDir(char *filename){
 
    printf("---- MENU ----\n");
    printf("* n: name\n");
    printf("* d: size\n");
    printf("* a: access\n");
    printf("* c: number of files with .c extension\n");

     
    printf("\nPlease enter your options\n\n");
    printf("STANDARD INPUT: ");

    pid_t pid, w;
    pid = fork();
    int wstatus;

    if(pid==0){ //sunt in copil
        char *createfileName=strcpy(createfileName, filename);
        strcat(createfileName, "_file.txt");
        FILE *newFile= fopen(createfileName, "w");
        if(newFile==NULL)
        {
            printf("File was not created");
            exit(1);
        }
        else
          printf("We succeed creating the file");
        fclose(newFile);
        exit(5);
    }
    else
        if(pid>0){
            w = wait(&wstatus);
            if(WIFEXITED(wstatus)) {
                printf("process with pid %d, exited, status = %d\n\n", w, WEXITSTATUS(wstatus));

        }
    /*if(pid < 0) {
        printf("error forking for dir");
        exit(1);
    }

    if(pid == 0) {
        printf("\nBecause this is a directory,\na .txt file will be created with the following name: %s_file.txt\n", path);
        
        char *file_name = strcpy(file_name, path);
        strcat(file_name, "_file.txt");
        FILE *file_ptr = fopen(file_name, "w");
        if (file_ptr == NULL) {
            printf("Error: Unable to create file.\n");
            exit(1);
        }
        printf("%s_file.txt was created successfully.\n", path);
        fclose(file_ptr);

        exit(10);
    }
    else {
        if(pid > 0) {
            // printf("parent of .c part\n");
            w = wait(&wstatus);
            if(WIFEXITED(wstatus)) {
                printf("process with pid %d, exited, status = %d\n\n", w, WEXITSTATUS(wstatus));
            }
        }
    }*/

    char input[10];
    struct stat buff;
    fgets(input, 10, stdin);

    for(int i = 1; i < strlen(input)-1; i++) {
        if (input[i] == 'n') 
            printName(filename);
            
        if (input[i] == 'd') 
            printf("Size of directory: %d\n", (int)buff.st_size);

        if (input[i] == 'a') {
                if(stat(input, &buff)) {
                    printf("ErroR :(\n");
                }
                else {
                    printf("Access rights: \n");

                    printf("User:\n");
                    buff.st_mode & S_IRUSR ? printf("   Read - yes\n") : printf("   Read - no\n");
                    buff.st_mode & S_IWUSR ? printf("   Write - yes\n") : printf("   Write - no\n");
                    buff.st_mode & S_IXUSR ? printf("   Execute - yes\n") : printf("   Execute - no\n");
                        
                    printf("Group:\n");
                    buff.st_mode & S_IRGRP ? printf("   Read - yes\n") : printf("   Read - no\n");
                    buff.st_mode & S_IWGRP ? printf("   Write - yes\n") : printf("   Write - no\n");
                    buff.st_mode & S_IXGRP ? printf("   Execute - yes\n") : printf("   Execute - no\n");

                    printf("Other:\n");
                    buff.st_mode & S_IROTH ? printf("   Read - yes\n") : printf("   Read - no\n");
                    buff.st_mode & S_IWOTH ? printf("   Write - yes\n") : printf("   Write - no\n");
                    buff.st_mode & S_IXOTH ? printf("   Execute - yes\n") : printf("   Execute - no\n");

                }
            }
        if(input[i]=='c'){
                
                DIR *dir = opendir(filename);
                if (dir == NULL) {
                     perror("Error: failed to open directory");
                 }

               struct dirent *entry;
               int count = 0;
               while ((entry = readdir(dir)) != NULL) {
                     if (entry->d_type == DT_REG) { // regular file
                          const char *dir_name = entry->d_name;
                          size_t len = strlen(dir_name);
                          if (len >= 2 && strcmp(dir_name + len - 2, ".c") == 0) 
                                     count++;  
                     }
               }

                  closedir(dir);
                  printf("Total number of .c files in %s: %d\n", filename, count);   
            }
    }  

        }                  
}
/**pid_t pid, w;
    pid = fork();
    int wstatus;

    if(pid<0) {
        printf("error fork()");
        exit(1);
    }
    
    if(pid==0) {
         printf("this is the child process with pid %d \n", getpid());
        
        //execlp("ls", "ls", "-l", NULL);
        exit(5);
    }
    else {
        if(pid>0) {
            printf("this is the parent process\n");
            w = wait(&wstatus);
            if(WIFEXITED(wstatus)) {
                printf("process with pid %d, exited, status = %d\n", w, WEXITSTATUS(wstatus));
            }
        }
    }
    From main:
    if(pid1 > 0) {        
                w = wait(&wstatus);
                if(WIFEXITED(wstatus)) {
                    printf("process with pid %d, exited, status = %d\n", w, WEXITSTATUS(wstatus));
                }
            }
        else
        {
            if(pid < 0) {
                printf("\nerror at forking\n");
                exit(1);
            }
            else
    
    
    
    */

int main(int argc, char **argv){

    struct stat *buff;
    buff =(struct stat *)malloc(sizeof(struct stat));

    pid_t pid1, pid2, w;
    int wstatus1, wstatus2;

    if(argc>1){
        for(int i=1;i<argc; i++){
            pid1=fork();

            if(pid1==0){//this means we are in th child process            
                    
                    int typeOfFile=FileType(argv[i], buff);

                     if (typeOfFile==0){
                          printf("REGULAR FILE\n");
                          menuForRegular(argv[i]);
                    }

                     if (typeOfFile==1){
                          printf("DIRECTORY\n");
                          menuForDir(argv[i]);
                     }

                     if (typeOfFile==2){
                          printf("SYMBOLIC LINK\n");
                          menuForSymlink(argv[i]);
                
                     }

                     if(typeOfFile==-1){
                          printf("Wrong type of argument");
                     }
                     exit(0);
            }
            pid2=fork(); //create another child
            if(pid2==0){ //we are in the 2nd child
                int typeOfFile=FileType(argv[i], buff);

                     if (typeOfFile==0){ //we have reg file
                          if(strcmp(argv[i], ".c")){
                             printf("The file has: ");
                             execlp("bash", "bash", "compile.sh", argv[i], NULL);
                             exit(EXIT_SUCCESS);
                          }
                          else
                            if(strrchr(argv[i], '.')!=NULL && strcmp(argv[i], ".c")!=0){
                                printf("Number of lines of the file: ");
                                execl("/usr/bin/wc", "wc", "-l", argv[i], NULL);
                                exit(EXIT_SUCCESS);
                            }
                    }

                     if (typeOfFile==1){//we have a dir
                         
                     }

                     if (typeOfFile==2){//we have a symlink
                          
                
                     }

                     exit(0);
            } 
        w = wait(&wstatus1);
        waitpid(pid1, &wstatus1, 0);
        if(WIFEXITED(wstatus1)) {
                printf("Child process with pid %d, exited, status = %d\n", w, WEXITSTATUS(wstatus1));
            }
        waitpid(pid2, &wstatus2, 0);
        if(WIFEXITED(wstatus2)) {
                printf("Child process 2 with pid ..., exited, status = %d\n", WEXITSTATUS(wstatus2));
            }
        } 
    }     

}