
#include "prototypes.h"

#include <termios.h>
#include <unistd.h>
// #include <stdlib.h>

Buffer* newBuff(){
    Buffer* buff = new Buffer;
    buff->col = 0;
    buff->ln = 0;
    return buff;
}


void UpdateBuff(Buffer* buff,char c){
    Line* curr_line = buff->dll.back();
    // buff->col = curr_line->col;
    // buff->ln = curr_line->cln;
    //When Backspace
    if ((int)c==127)
    {
        if (curr_line->text.size())
        {
            curr_line->text.erase(curr_line->col-2,1);
            curr_line->col--;
            buff->col=curr_line->col;
        }
        else if(buff->dll.size()>1)
        {
            buff->dll.pop_back();
            buff->col = buff->dll.back()->col;
            buff->ln--;
        }
        
        return;
    }
    else if (c==CTRL_KEY('s'))
    {
        BuffToFile(buff);
    }
    else if ((int)c==13)
    {
        Line* line = new Line;
        line->cln = buff->ln++;
        buff->dll.push_back(line);
        buff->col = line->col=1;
    }
    else if (c == '\x1b') {
        char seq[2];
        char str[] = "A";
        write(STDOUT_FILENO,str,1);

        read(STDIN_FILENO, &seq[0], 1) ;
        read(STDIN_FILENO, &seq[1], 1) ;
        if (seq[0] == '[' ) { //&& ((int)seq[1]<=68 && (int)seq[1]>=65
            switch (seq[1]) {
                
                // moveCursor accordingly
                case 'A': moveUpCursor(buff); break; // Up
                case 'B': moveDownCursor(buff); break;// Down
                case 'C': moveRightCursor(buff); break;// Right
                case 'D': moveLeftCursor(buff); break;// Left
            }

        // else{

        //     }
        }
    }
    else if ( ((int)c<=127 && (int)c>=32)) 
    {
        // std::cout<<curr_line->text<<" "<<curr_line->col;
        curr_line->text.push_back(c);
        // std::cout<<curr_line->text<<" "<<curr_line->col;
        curr_line->col++;
        buff->col=curr_line->col;
    }
    
    

}

void DisplayBuff(Buffer* buff){

    //change cursor position here using arrow keys
    std::string header = "File: "+buff->filename +"      Ln "+std::to_string(buff->ln)+",Col "+ std::to_string(buff->col) +"\n";
    write(1, "\x1b[1;45m", 7); 
    write(STDOUT_FILENO, header.c_str(), header.size());
    write(1, "\x1b[0m", 4); 

    for (Line* line : buff->dll)
    {
        write(STDOUT_FILENO, (line->text+"\n").c_str(), line->text.size()+1);
    }
    SetCursor(buff->ln+1,buff->col);
}