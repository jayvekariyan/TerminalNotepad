#include "prototypes.h"

#include "buffer.cpp"
#include "display.cpp"
#include "raw.cpp"
#include "files.cpp"

// #pragma once


int main() {
    enableRawMode();
    // Buffer* buff = newBuff();
    ClearScreen();
    Buffer* buff = FileToBuff("myfile.txt");
    DisplayBuff(buff);
    BuffToFile(buff);
    // SetCursor(1,1);
    char* c = new char;
    int running=1;
    while (running) {
        running = readKey(buff,c);
    }
    return 0;
}






