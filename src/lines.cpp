#include "prototypes.h"


void insert_after_cl(Buffer* buff,Line* new_line){
    //If there is nothing
    if (!buff->curr_line)
    {
        buff->curr_line = new_line;
        buff->first_line = new_line;
        buff->last_line = new_line;
        buff->size++;
        return;
    }
    //if next line is null
    if (buff->curr_line->next==NULL)
    {
        new_line->next = NULL;
        new_line->prev = buff->curr_line;
        buff->curr_line->next = new_line;
        buff->last_line = new_line;
        buff->size++;
        return;
    }
    
    buff->curr_line->next->prev = new_line;
    new_line->next = buff->curr_line->next;
    buff->curr_line->next = new_line;
    new_line->prev = buff->curr_line;
    buff->size++;

}

std::string delete_cl(Buffer* buff) {
    //if current line is empty
    if (!buff->curr_line) {
        return "Error: Empty buffer";
    }

    Line* line = buff->curr_line;
    std::string str = line->text;

    // if ony one node
    if (line->prev == NULL && line->next == NULL) {
        buff->first_line = NULL;
        buff->last_line = NULL;
        buff->curr_line = NULL;
    }
    // deleting first 
    else if (line->prev == NULL) {
        buff->first_line = line->next;
        line->next->prev = NULL;
        buff->curr_line = line->next;
    }
    // deleting last
    else if (line->next == NULL) {
        buff->last_line = line->prev;
        line->prev->next = NULL;
        buff->curr_line = line->prev;
    }
    // deleting from middle
    else {
        line->prev->next = line->next;
        line->next->prev = line->prev;
        buff->curr_line = line->prev; 
    }

    buff->size--;
    delete line;

    return str;
}