#include "prototypes.h"

#include "buffer.cpp"
#include "display.cpp"
#include "raw.cpp"
#include "files.cpp"
#include "dll.cpp"

// #pragma once


int main(int argc, char* argv[]) {
    enableRawMode();
    std::string filename = argv[1];
    ClearScreen();
    Buffer* buff = FileToBuff(filename);
    if (!buff) return 0;
    
    DisplayBuff(buff);
    BuffToFile(buff);
    // SetCursor(1,1);
    char* c = new char;
    int running=1;
    while (running) {
        running = readKey(buff,c);
    }
    ClearScreen();
    return 0;
}






