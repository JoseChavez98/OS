#include <stdio.h>
#include <bits/types/clock_t.h>
#include <time.h>
#define MAXCHAR 100
void delay(int n){
    int milli_seconds = 1000 * n;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}
int main(){
while(1){
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "/proc/meminfo";

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL) {
        delay(1000);
        printf("%s", str);
    }
    fclose(fp);

}
}