#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <wait.h>

void *ask(char *comand){
    printf("SOJose$ ");
    scanf("%s",comand);
    printf("");
}

int str_comp(char * a, char * b){
    for(int i = 0 ;i<7;i++){
        if(a[i] == b[i]){
            if(a[i] == '\0'){
                return 1;
            }

        }
        else{
            return -1;
        }
    }
}

void forkFunction() {
    if(fork()==0){
        char *cmd = "ls";
        char *argv[2];
        argv[0] = "ls";
        argv[1] = NULL;

        execvp(cmd, argv);
        fork();

    }
    else{
        wait(NULL);
    }

}

void forkFunction2() {
    char file[30];
    scanf("%s",file);
    char *arg[3]={"/bin/nano",file,NULL};

    if(fork()==0){
        execvp("/bin/nano",arg);
    }
    else{
        wait(NULL);
    }

}

void forkFunction3() {
    char file[30];
    scanf("%s",file);
    char *arg[3]={"/bin/cat",file,NULL};

    if(fork()==0){
        execvp("/bin/cat",arg);

    }
    else{
        wait(NULL);
    }

}


int main(){

    while(1) {
        char comand[6];


        ask(comand);


        if( str_comp(comand,"pwd") == 1 )
        {
            char pwd[100];
            if (getcwd(pwd, sizeof(pwd)) != NULL)
            {
                printf("%s\n", pwd);
            }
        }
        else if(str_comp(comand,"cd") == 1)
        {
            char cd[100];
            scanf("%s",cd);

            if (chdir(cd) != 0)
                perror("chdir() to /usr failed");

        }
        else if(str_comp(comand,"mkdir") == 1)
        {

            char directory[100];
            scanf("%s",directory);
            //e_t process_mask = umask(0);
            int result_code = mkdir(directory, S_IRWXU | S_IRWXG | S_IRWXO);
            //umask(process_mask);
        }
        else if(str_comp(comand,"ls") == 1)
        {
           forkFunction();


        }
        else if(str_comp(comand,"rm") == 1)
        {
            char file[100];
            scanf("%s",file);
            unlink(file);
        }

        else if(str_comp(comand,"nano") == 1) {
           forkFunction2();
        }
        else if(str_comp(comand,"cat") == 1) {
            forkFunction3();
        }
    }
    return 0;
}