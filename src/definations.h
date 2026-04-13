#include <iostream>
#include <stdlib.h>
#include <list>

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
    DLL* dll;
    std::string filename;
    int ln;
    int col;
};

// Line* newLine(){
//     Line* line = new Line;

// }