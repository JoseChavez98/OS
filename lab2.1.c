#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

void pointlessFunction(){
    printf(" ");
}

int main(){

    int cont=0;
    float a[20];
    float b[20];
    float c[20];

    while(cont<20) {

        struct timeval start;
        struct timeval finish;
        long compTime;
        double Time;

        gettimeofday(&start, 0);
        pointlessFunction();
        gettimeofday(&finish, 0);

        compTime = (finish.tv_sec - start.tv_sec) * 1000000;
        compTime = compTime + (finish.tv_usec - start.tv_usec);
        Time = (double)compTime;

        a[cont]=(double) Time / 1000000.0;



        char buf1[21] = "";

        gettimeofday(&start, 0);
        write(1, buf1, 0);
        gettimeofday(&finish, 0);


        compTime = (finish.tv_sec - start.tv_sec) * 1000000;
        compTime = compTime + (finish.tv_usec - start.tv_usec);
        Time = (double) compTime;

        b[cont] = (double) Time / 1000000.0;

        int fd1[2];
        int fd2[2];

        char fixed_str[] = "A";
        char input_str[] = "B";
        pid_t p;

        if (pipe(fd1) == -1) {
            fprintf(stderr, "Pipe Failed");
            return 1;
        }
        if (pipe(fd2) == -1) {
            fprintf(stderr, "Pipe Failed");
            return 1;
        }

        gettimeofday(&start, 0);

        p = fork();

        if (p < 0) {
            fprintf(stderr, "fork Failed");
            return 1;
        } else if (p > 0) {
            char concat_str[100];

            close(fd1[0]);
            //write(fd1[1], input_str, strlen(input_str) + 1);
            close(fd1[1]);

            wait(NULL);

            close(fd2[1]);
            read(fd2[0], concat_str, 100);
            printf(" %s\n", concat_str);
            close(fd2[0]);
        } else {
            close(fd1[1]);
            char concat_str[100];
            read(fd1[0], concat_str, 100);

            int k = strlen(concat_str);
            int i;
            for (i = 0; i < strlen(fixed_str); i++)
                concat_str[k++] = fixed_str[i];

            concat_str[k] = '\0';

            close(fd1[0]);
            close(fd2[0]);

            //write(fd2[1], concat_str, strlen(concat_str) + 1);
            close(fd2[1]);

            exit(0);
        }
        gettimeofday(&finish, 0);

        compTime = (finish.tv_sec - start.tv_sec) * 1000000;
        compTime = compTime + (finish.tv_usec - start.tv_usec);
        Time = (double) compTime;

        c[cont]=(double) Time / 1000000.0;


        cont++;
    }

    float prom1,prom2,prom3;

    for(int i = 0 ;i < 20 ; i++ ){
        prom1+=a[i];
        prom2+=b[i];
        prom3+=c[i];
    }

    printf("El costo en segundos de llamar a una función mínima en C /C++: %f \n",prom1/20);
    printf("El costo en segundos en llamar a un syscall: %f \n",prom2/20);
    printf("El costo de hacer un cambio de contexto: %f \n",prom3/20);

    return 0;
}