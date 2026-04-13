// #include "definations.h"
#include "prototypes.h"

#include <list>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#pragma once

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}


void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON); // turn off echo & canonical mode
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int readKey(Buffer* buff,char* c){
    if(read(STDIN_FILENO, c, 1) == 1){
        if (*c == CTRL_KEY('q')){ return 0;}
        UpdateBuff(buff,*c);
        ClearScreen();
        DisplayBuff(buff);
    }
    return 1;
}