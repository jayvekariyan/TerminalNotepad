
#include "prototypes.h"

// #include <stdlib.h>

Buffer* newBuff(std::string filename){
    Buffer* buff = new Buffer;
    buff->filename = filename;
    buff->curr_line = NULL;
    buff->first_line = NULL;
    buff->last_line = NULL;
    buff->ln = 0;
    buff->size = 0;
    return buff;
}


void UpdateBuff(Buffer* buff,char c){
    if (!buff->curr_line) return;
    Action new_action = {buff->ln,buff->curr_line->col,std::string(1, c),buff->curr_line, INSERT_CHAR};
    buff->status = "Unsaved";
    // when backspace
    if ((int)c == 127) {
        if (buff->curr_line->col > 1) {
            new_action.data = buff->curr_line->text[buff->curr_line->col - 2];
            new_action.type = DELETE_CHAR;
            addAction(buff,new_action);
            buff->curr_line->text.erase(buff->curr_line->col - 2, 1);
            buff->curr_line->col--;
        }
        else if (buff->curr_line->prev) {
            Line* curr = buff->curr_line;
            Line* prev = buff->curr_line->prev;
            prev->text += curr->text;
            delete_cl(buff);
            buff->ln--;

            new_action.type = MERGE_LINE;
            new_action.line = prev;
            new_action.l = buff->ln;
            new_action.c = prev->col;
            // new_action.data = line->text;
            addAction(buff,new_action);

        }
        return;
    }

    else if (c == CTRL_KEY('s')) {
        buff->status = "Saved";
        BuffToFile(buff);
    }

    else if (c == CTRL_KEY('z')) {
        undo(buff);
        
    }

    else if (c == CTRL_KEY('r')) {
        redo(buff);
    }

    // when enter
    else if ((int)c == 13) {
        Line* line = new Line;
        new_action.line = buff->curr_line;
        new_action.l = buff->ln;
        new_action.data = line->text;
        line->text = buff->curr_line->text.substr(buff->curr_line->col-1);
        buff->curr_line->text.erase(buff->curr_line->col-1);
        buff->curr_line->col = buff->curr_line->text.size()+1;
        line->col = 1;

        insert_after_cl(buff, line);
        buff->curr_line = line;
        buff->ln++;

        new_action.type = SPLIT_LINE;
        
        
    
        addAction(buff,new_action);
    }

    // ESC (ARROWS)
    else if (c == '\x1b') {
        char seq[2];

        if (read(STDIN_FILENO, &seq[0], 1) != 1) return;
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return;

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': moveUpCursor(buff); break;
                case 'B': moveDownCursor(buff); break;
                case 'C': moveRightCursor(buff); break;
                case 'D': moveLeftCursor(buff); break;
            }
        }
    }

    // NORMAL CHARACTER
    else if (c >= 32 && c <= 126) {
        buff->curr_line->text.insert(buff->curr_line->col - 1, 1, c);
        buff->curr_line->col++;
        new_action.c = buff->curr_line->col;
        addAction(buff,new_action);
    }
}

void DisplayBuff(Buffer* buff){

    //change cursor position here using arrow keys
    std::string header = "File: "+buff->filename +"      Ln "+std::to_string(buff->ln)+"/"+std::to_string(buff->size)+",Col "+ std::to_string(buff->curr_line->col)+"     ["+buff->status  +"]\n";
    write(1, "\x1b[1;44m", 7); 
    write(STDOUT_FILENO, header.c_str(), header.size());
    write(1, "\x1b[0m", 4); 

    Line* line = buff->first_line;
    while (line!=NULL)
    {
        write(STDOUT_FILENO, (line->text+"\n").c_str(), line->text.size()+1);
        line=line->next;
    }
    SetCursor(buff->ln+1,buff->curr_line->col);
}