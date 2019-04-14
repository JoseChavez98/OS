#include <iostream>
#include <fstream>

int main(){

    std::fstream arc("/proc/cpuinfo", std::ios::in);
    std::string palabra;
    int i=-1;
    while(arc>>palabra){
        if(palabra=="Intel(R)"){
            i=0;
            std::cout<<"cpu name: ";
        }
        if(i>=0 and i<=6){
            std::cout<<palabra<<" ";
            i++;
        }
        if(i==6){
            break;
        }
    }
    arc.close();

    std::fstream file("/proc/meminfo", std::ios::in);
    std::string palabra2;
    getline(file,palabra2);
    std::cout<<'\n'<<palabra2<<'\n';
    file.close();

    std::fstream file2("/proc/version", std::ios::in);
    std::string palabra3;
    int j=0;
    while(file2>>palabra3){
        std::cout<<palabra3<<" ";
        j++;
        if(j==3){
            break;
        }
    }    
    
    std::fstream file3("/proc/uptime", std::ios::in);
    std::string palabra4;
    std::cout<<'\n';
    while(file3>>palabra4){
        std::cout<<palabra4<<" ";
    }
    std::cout<<" segundos";       

    return 0;
}