#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>
#include <thread>

typedef std:: string String;
using namespace std;
String input;
String text = "Hello world in marquee!";
int swidth = 0;
int sheight = 0;
CONSOLE_SCREEN_BUFFER_INFO csi;
int xtextdir = 1;
int ytextdir = 1;
int xtext = 0;
int ytext = 0;
String inp = "";
vector<String> inpcmds;


void keyboardpolling(){
    while(true){
        if(_kbhit()){
            char key = _getch();
            if(key == 13){
                inpcmds.push_back("Command processed in MARQUEE_CONSOLE: " + inp);
                inp.clear();
            }
            else if (key == 8){
                if(!inp.empty()){
                    inp.pop_back();
                }
            }
            else{
                inp.push_back(key);
            }
        }
        Sleep(20);
    }
}

void marquee(){
    while (true){
        system("CLS"); 

        //header coordinates
        COORD hcoord;
        hcoord.X = 0;
        hcoord.Y = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), hcoord);
        std::cout << "*********************************\n";
        std::cout << "* Displaying a marquee console! *\n";
        std::cout << "*********************************\n";

        //check the screen size 
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csi);
        swidth = csi.srWindow.Right - csi.srWindow.Left + 1;
        sheight = csi.srWindow.Bottom - csi.srWindow.Top + 1;
        
        xtext += xtextdir;
        ytext += ytextdir;
        
        //bounce off the screen
        if(xtext <= 0 || xtext >= swidth - text.length()){
            xtextdir *= -1;
        }
        if(ytext <= 4 || ytext >= sheight - 7){
            ytextdir *= -1;
        }
        
        //text coordinates to move around the screen
        COORD tcoord;
        tcoord.X = xtext;
        tcoord.Y = ytext;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tcoord);

        cout << text;
        
        //input coordinates
        COORD inpcoord;
        inpcoord.X = 0;
        inpcoord.Y = sheight - 4;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), inpcoord);
        std::cout << "Enter a command for MARQUEE_CONSOLE: " << inp;
        
        //printing history coordinates
        for(int i = 0 ; i < inpcmds.size(); i++){    
            COORD cmdcoord;
            cmdcoord.X = 0;
            cmdcoord.Y = sheight - 3 + i;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cmdcoord);
            std::cout << inpcmds[inpcmds.size() - 1 - i] << "\n";
        }
        
        //final position of cursor
        COORD fcoord;
        fcoord.X = strlen("Enter a command for MARQUEE_CONSOLE: ") + inp.length();
        fcoord.Y = sheight - 4;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), fcoord);        
        Sleep(10);
    }
}

int main(){
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csi);
    swidth = csi.srWindow.Right - csi.srWindow.Left + 1;
    sheight = csi.srWindow.Bottom - csi.srWindow.Top + 1;
    
    xtext = (swidth - text.length()) / 2;
    ytext = (sheight + 3) / 2;

    std::thread kpoll(keyboardpolling);
    std::thread marq(marquee);
    kpoll.join();
    marq.join();

    return 0;
}
