#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

typedef std:: string String;
using namespace std;
String input;
COORD coord;

struct procinfo{
    int gpu;
    String giid;
    String ciid;
    int pid;
    String type;
    String name;
    String memory;
};

std::vector<procinfo> procinfos;
String finname;

void time(){
    time_t now = time(0);
    tm* localtm = localtime(&now);
    char datetime[100];
    
    strftime(datetime, sizeof(datetime), "%a %b %d %H:%M:%S %Y", localtm);
    std::cout << datetime;
}

void printgpuinfo(){
    time();
    printf("\n");
    printf("+-----------------------------------------------------------------------------+\n");
    printf("| NVIDIA-SMI 516.91       Driver Version: 516.91       CUDA Version: 11.7     |\n");
    printf("|-------------------------------+----------------------+----------------------+\n");
    printf("| GPU  Name            TCC/WDDM | Bus-Id        Disp.A | Volatile Uncorr. ECC |\n");
    printf("| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |\n");
    printf("|                               |                      |               MIG M. |\n");
    printf("|===============================+======================+======================|\n");
    printf("|   0  NVIDIA GeForce ... WDDM  | 00000000:01:00.0 Off |                  N/A |\n");
    printf("| N/A   41C    P8     2W /  N/A |    120MiB /  4096MiB |      0%      Default |\n");
    printf("|                               |                      |                  N/A |\n");
    printf("+-------------------------------+----------------------+----------------------+\n");
}

void printprocess(){
    int maxpid = 0;
    for (const auto& proc: procinfos){
        int lpid = std::to_string(proc.pid).size();
        if(lpid > maxpid){
            maxpid = lpid;
        }
    }

    printgpuinfo();
    printf("\n");
    printf("+-----------------------------------------------------------------------------+\n");
    printf("| Processes:                                                                  |\n");
    printf("|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |\n");
    printf("|        ID   ID                                                   Usage      |\n");
    printf("|=============================================================================|\n");
    
    for(int i = 0; i < procinfos.size(); i++){
        coord.Y = 18 + i;
        
        coord.X = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << "|";
        
        coord.X = 5;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << procinfos[i].gpu;

        coord.X = 9;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << procinfos[i].giid;

        coord.X = 14;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << procinfos[i].ciid;

        coord.X = 22;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << std::setw(maxpid) << procinfos[i].pid;

        coord.X = 31;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << procinfos[i].type;

        coord.X = 37;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        if(procinfos[i].name.size() > 25){ 
            finname = "..." + procinfos[i].name.substr(procinfos[i].name.size() - 22);
        } 
        else{
            finname =  String(25 - procinfos[i].name.size(), ' ') + procinfos[i].name;
        }
        std::cout << finname;

        coord.X = 69;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << procinfos[i].memory;

        coord.X = 78;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << "|\n";
    }

    printf("+-----------------------------------------------------------------------------+\n");
}

int main(){
    procinfos.push_back({0, "N/A", "N/A", 4496, "C+G", "aaaaaaaaaaaaaaaaaaaaaaaaaaaa.exe", "N/A"});
    procinfos.push_back({0, "N/A", "N/A", 5020, "C+G", "bbbbbbbbbbbbbbbbbbbbbbbbbbbb.exe", "N/A"});
    procinfos.push_back({0, "N/A", "N/A", 5500, "C+G", "cccccccccccccccccccccccccccc.exe", "N/A"});
    procinfos.push_back({0, "N/A", "N/A", 17840, "C+G", "ddddddddddddddd.exe", "N/A"});
    procinfos.push_back({0, "N/A", "N/A", 10076, "C+G", "eeeeeeeeeeeeeeee.exe", "N/A"});
    procinfos.push_back({0, "N/A", "N/A", 20428, "C+G", "fffffffffffffffffffffffffff.exe", "N/A"});

    std::cout << "Enter a command: ";
    std::cin >> input;

    while (input != "csopesy-smi"){
        std::cout << " Command not found. Enter a command: ";
        std::cin >> input;
    }

    system("CLS");
    printprocess();

    return 0;
}
