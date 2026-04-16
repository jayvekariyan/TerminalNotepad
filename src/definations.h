#include <iostream>
#include <stdlib.h>
#include <list>
#include <termios.h>
#include <unistd.h>

#pragma once


#define CTRL_KEY(k) ((k) & 0x1f)

// Lines
struct Line{
    std::string text;
    Line* next;
    Line* prev;
    int col;
};

struct DLL{
    Line* front;
    Line* back;
    int size;
};


//Test buffer
struct Buffer{
    Line* first_line;
    Line* last_line;
    Line* curr_line;
    std::string filename;
    int ln;
    int size;
    // int col;
};

// Line* newLine(){
//     Line* line = new Line;

// }