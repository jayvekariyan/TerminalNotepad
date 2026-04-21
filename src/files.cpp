#include "prototypes.h"

#include<iostream>
#include <fstream>
#include <string>


Buffer* FileToBuff(std::string filename){
    Buffer* buff;

    std::ifstream file(filename); 
    std::string l = "";
    int ln = 0;
    if (file.is_open()) { // Check if file opened successfully
        buff = newBuff(filename);
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
    else { //Make new file if not exists
        std::ofstream file(filename);
        buff = FileToBuff(filename);
        file.close();
    }

    buff->status="Saved";
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