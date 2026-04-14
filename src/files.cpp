// #include"definations.h"
#include "prototypes.h"

#include<iostream>
#include <fstream>
#include <string>



Buffer* FileToBuff(std::string filename){
    Buffer* buff = new Buffer;
    buff->filename = filename;
    buff->dll = newDLL();
    std::ifstream file(filename); 
    std::string l;
    int ln = 0;
    if (file.is_open()) { // Check if file opened successfully
        while (std::getline(file, l)) {
            Line* line = new Line;
            line->text = l; 
            line->col = l.size()+1;
            ln++;
            push_back(buff->dll,line);
            buff->curr_line = line;
        }
        file.close(); // Good practice to close
    } 
    else {
        std::cerr << "Unable to open file" << std::endl;
    }

    buff->ln = ln;
    // buff->col = back(buff->dll)->col;
    return buff;
}

void BuffToFile(Buffer* buff){
    std::ofstream file(buff->filename);
    int ln = 1;
    Line* line = buff->dll->front;
    while (line!=NULL)
    {
        file <<line->text +"\n";
        line=line->next;
    }
    file.close(); 

}