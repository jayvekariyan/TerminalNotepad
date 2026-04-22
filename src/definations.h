#include <iostream>
#include <stdlib.h>
#include <list>
#include <termios.h>
#include <unistd.h>
#include <stack>
#include <fstream>
#include <string>

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

enum ActionType { INSERT_CHAR=1, DELETE_CHAR=0,SPLIT_LINE=3, MERGE_LINE=2}; 
//Action struct
struct Action
{
    int l;
    int c;
    std::string data; //char data; 
    Line* line;
    ActionType type;
};


//Test buffer
struct Buffer{
    Line* first_line;
    Line* last_line;
    Line* curr_line;
    std::string filename;
    std::string status;
    std::stack<Action> undoStack;
    std::stack<Action> redoStack;
    int ln;
    int size;

};
