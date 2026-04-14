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
    buff->ln--;
}

void moveDownCursor(Buffer*buff){
    buff->ln++;
}
void moveLeftCursor(Buffer*buff){
    buff->curr_line->col--;
}
void moveRightCursor(Buffer*buff){
    buff->curr_line->col++;
}