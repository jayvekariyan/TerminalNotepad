#include "prototypes.h"


#include <termios.h>
#include <unistd.h>

void ClearScreen(){
    system("clear");
}

void SetCursor(int x,int y){
    std::string location = "\x1b["+std::to_string(x)+";"+std::to_string(y)+"H";
    write(STDOUT_FILENO, location.c_str(), location.size());
}

void moveUpCursor(Buffer*buff){
    if(buff->curr_line->prev){
        buff->curr_line = buff->curr_line->prev;
        buff->ln--;
    }
}

void moveDownCursor(Buffer*buff){
    if (buff->curr_line->next)
    {   
        buff->curr_line = buff->curr_line->next;    
        buff->ln++;
    }
}
void moveLeftCursor(Buffer*buff){
    if (buff->curr_line->col<=1)
    {
        return;
    }
    buff->curr_line->col--;
}
void moveRightCursor(Buffer*buff){
    if (buff->curr_line->col>buff->curr_line->text.size())
    {
        return;
    }
    buff->curr_line->col++;
}