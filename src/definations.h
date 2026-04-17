#include <iostream>
#include <stdlib.h>
#include <list>
#include <termios.h>
#include <unistd.h>
#include <stack>

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

enum ActionType { INSERT=1, DELETE=0 };
//Action struct
struct Action
{
    int l;
    int c;
    char data; //std::string data;
    Line* line;
    ActionType type;
};


//Test buffer
struct Buffer{
    Line* first_line;
    Line* last_line;
    Line* curr_line;
    std::string filename;
    std::stack<Action> undoStack;
    std::stack<Action> redoStack;
    int ln;
    int size;
    // int col;
};

// Line* newLine(){
//     Line* line = new Line;

// }