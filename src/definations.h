#include <iostream>
#include <stdlib.h>
#include <list>

#pragma once


#define CTRL_KEY(k) ((k) & 0x1f)

// Lines
struct Line{
    std::string text;
    int cln;
    int col;
};


//Test buffer
struct Buffer{
    std::list <Line*> dll;
    std::string filename;
    //cursor
    int ln;
    int col;
};

// Line* newLine(){
//     Line* line = new Line;

// }