#include <iostream>
#include <fstream>
#include <thread>
#include <bits/types/clock_t.h>
#include <time.h>

void delay(int n){
    int milli_seconds = 1000 * n;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

int main(){

    while(1) {

/*
 *
 * Punto a.
 *
 *
 * */

        std::fstream meminfo("/proc/meminfo", std::ios::in);
        std::string palabra1;
        int total = 0;
        int available = 0;
        int i = 0;
        while (meminfo >> palabra1) {
            if (i > 0) {
                if (i == 1 && total == 0) {
                    total = stoi(palabra1);
                } else if (i == 2) {
                    available = stoi(palabra1);
                    break;
                }
            }
            if (palabra1 == "MemTotal:" or palabra1 == "MemAvailable:") {
                i++;
            }

        }

        std::cout << (available * 100) / total << "% de memoria disponible\n";
        meminfo.close();
/*
 *
 * PUnto b
 *
 * */


        std::fstream stat("/proc/stat", std::ios::in);

        std::string number;
        getline(stat, number, ' ');
        getline(stat, number);
        std::string container[10];
        std::string extra = "";
        int cont = 0;
        int tot = 0;
        char a = 'a';

        for (auto &i : number) {
            if (a == 'a') {
                a = 'b';
            } else {

                if (i == ' ') {
                    container[cont] = extra;
                    cont++;
                    extra = "";
                } else {
                    extra += i;
                }
            }

        }

        for (auto &j : container) {
            if (j != "") {
                tot += stoi(j);
            }
        }

        std::cout << "user mode time -> " << (stoi(container[0]) * 100) / tot << " %\n";
        std::cout << "system mode time -> " << (stoi(container[2]) * 100) / tot << " %\n";
        std::cout << "idle time -> " << (stoi(container[3]) * 100) / tot << " %\n";

        std::string palabra, ctxt, processes;
        bool switch1 = true;
        bool switch2 = true;
        while (stat >> palabra) {
            if (palabra == "ctxt") {
                switch1 = false;
            }
            if (palabra == "processes") {
                switch2 = false;
            }
            if (!switch1) {
                ctxt = palabra;
            }
            if (!switch2) {
                processes = palabra;
            }
        }

        std::cout << "tasa de cambio contexto kerne : " << ctxt << '\n';
        std::cout << "tasa de creacion procesos sistema : " << processes << '\n';

        std::cout<<"#######################################################'\n";
        delay(1000);
    }

    return 0;
}