// #include"definations.h"
#include "prototypes.h"

#include<iostream>
#include <fstream>
#include <string>



Buffer* FileToBuff(std::string filename){
    Buffer* buff = new Buffer;
    buff->filename = filename;
    std::ifstream file(filename); 
    std::string l;
    int ln = 1;
    if (file.is_open()) { // Check if file opened successfully
        while (std::getline(file, l)) {
            Line* line = new Line;
            line->text = l; 
            line->col = l.size()+1;
            line->cln = ln++;
            // line->col = 0;
            buff->dll.push_back(line);
        }
        file.close(); // Good practice to close
    } 
    else {
        std::cerr << "Unable to open file" << std::endl;
    }

    buff->ln = buff->dll.back()->cln;
    buff->col = buff->dll.back()->col;
    return buff;
}

void BuffToFile(Buffer* buff){
    std::ofstream file(buff->filename);
    int ln = 1;
    for (Line* line : buff->dll)
    {
            file << line->text +"\n";
    }
    file.close(); 

}