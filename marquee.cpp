#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>

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
    if(_kbhit()){
        char key = _getch();
        if(key == 13){
            inpcmds.push_back("Command processed in MARQUEE_CONSOLE: " + inp);
            inp.clear();
        }
        else if (key == 8){
            if(!inp.empty()){
                inp.pop_back();
                //cout << "\b \b";
            }
        }
        else{
            inp.push_back(key);
            //cout << key;
        }
    }
}

void marquee(){
    system("CLS"); 

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

    if(xtext <= 0 || xtext >= swidth - text.length()){
        xtextdir *= -1;
    }
    if(ytext <= 4 || ytext >= sheight - 7){
        ytextdir *= -1;
    }
    
    COORD tcoord;
    tcoord.X = xtext;
    tcoord.Y = ytext;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tcoord);

    cout << text;
    
    COORD inpcoord;
    inpcoord.X = 0;
    inpcoord.Y = sheight - 4;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), inpcoord);
    std::cout << "Enter a command for MARQUEE_CONSOLE: " << inp;
    
    for(int i = 0 ; i < inpcmds.size(); i++){    
        COORD cmdcoord;
        cmdcoord.X = 0;
        cmdcoord.Y = sheight - 3 + i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cmdcoord);
        std::cout << inpcmds[inpcmds.size() - 1 - i] << "\n";
    }
    
    COORD fcoord;
     fcoord.X = strlen("Enter a command for MARQUEE_CONSOLE: ") + inp.length();
     fcoord.Y = sheight - 4;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), fcoord);        
}

int main(){
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csi);
    swidth = csi.srWindow.Right - csi.srWindow.Left + 1;
    sheight = csi.srWindow.Bottom - csi.srWindow.Top + 1;
    
    xtext = (swidth - text.length()) / 2;
    ytext = (sheight + 3) / 2;

    while (true) {
        keyboardpolling();
        marquee();
        Sleep(10);
    }

    return 0;
}