// #include"definations.h"
#include "prototypes.h"

#include<iostream>
#include <fstream>
#include <string>



Buffer* FileToBuff(std::string filename){
    Buffer* buff = newBuff(filename);

    std::ifstream file(filename); 
    std::string l = "";
    int ln = 0;
    if (file.is_open()) { // Check if file opened successfully
        while (std::getline(file, l) || !buff->size) {
            Line* line = new Line;
            line->text = l; 
            line->col = l.size()+1;
            buff->ln++;
            insert_after_cl(buff,line);
            buff->curr_line = line;
        }
        file.close(); // Good practice to close
    } 
    else {
        std::cerr << "Unable to open file" << std::endl;
        return NULL;
    }

    
    // buff->col = back(buff->dll)->col;
    return buff;
}

void BuffToFile(Buffer* buff){
    std::ofstream file(buff->filename);
    int ln = 1;
    Line* line = buff->first_line;
    while (line!=NULL)
    {
        file <<line->text +"\n";
        line=line->next;
    }
    file.close(); 

}