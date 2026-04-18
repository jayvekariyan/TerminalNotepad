#include "definations.h"


// make new action at every time update buffer
//

void addAction(Buffer* buff,Action action){
    buff->undoStack.push(action);
    // std::cout<<"act:"+std::to_string(action.data)+"|"+std::to_string(action.l)+"|"+std::to_string(action.c)+"|"+std::to_string(action.type)+" ";
    while (!buff->redoStack.empty())
    {
        buff->redoStack.pop();
    }
}

void deleteChar(Buffer* buff ,Action a){
    Line* curr = a.line;
    curr->text.erase(a.c-2, 1);
    //update cursor
    curr->col = a.c-1;
    buff->curr_line = curr;
    buff->ln = a.l;
}

void insertChar(Buffer* buff ,Action a){
    Line* curr = a.line;
    curr->text.insert(a.c-2, 1,a.data[0]);
    //update cursor
    curr->col = a.c;
    buff->curr_line = curr;
    buff->ln = a.l;
}

void mergeLine(Buffer* buff,Action a){
    Line* curr = a.line;
    Line* next = curr->next;
    curr->text += next->text;
    buff->curr_line = next;
    delete_cl(buff);
    //cursor

    buff->curr_line = curr;
    buff->ln = a.l;
}
void splitLine(Buffer* buff,Action a){
    Line* line = a.line;
    buff->curr_line = line;
    Line* next = new Line;
    next->text = line->text.substr(a.c-1);
    line->text.erase(a.c-1);
    line->col = line->text.size()+1;
    insert_after_cl(buff,next);
    //cursor
    next->col = 1;
    buff->curr_line = next;
    buff->ln = a.l+1;

}


void undo(Buffer* buff){
    if (buff->undoStack.empty())
    {
        return;
    }
    
    Action a = buff->undoStack.top();
    Action inverse;
    buff->undoStack.pop();
    // std::cout<<"undo:"+std::to_string(a.data)+"|"+std::to_string(a.l)+"|"+std::to_string(a.c)+"|"+std::to_string(a.type)+" ";

    if (a.type == INSERT_CHAR)
    {
        deleteChar(buff,a);
        // inverse = {a.l, a.c, a.data, DELETE};
    } 
    else if (a.type == DELETE_CHAR) {
        insertChar(buff, a);
        // inverse = {a.l, a.c, a.data, INSERT};
    }
    else if (a.type == SPLIT_LINE) {
        mergeLine(buff, a);
        // inverse = {a.l, a.c, a.data, INSERT};
    }
    else if (a.type == MERGE_LINE) {
        splitLine(buff, a);
        // inverse = {a.l, a.c, a.data, INSERT};
    }
    buff->redoStack.push(a);
    

}


void redo(Buffer* buff) {
    if (buff->redoStack.empty()) return;
    
    Action a = buff->redoStack.top();
    Action inverse;
    // std::cout<<"redo:"+std::to_string(a.data)+"|"+std::to_string(a.l)+"|"+std::to_string(a.c)+"|"+std::to_string(a.type)+" ";
    
    buff->redoStack.pop();

    if (a.type == INSERT_CHAR){
        insertChar(buff, a);
        // inverse = {a.l, a.c, a.data, DELETE};
        
    }
    else if (a.type == DELETE_CHAR){
        deleteChar(buff,a);
        // inverse = {a.l, a.c, a.data, DELETE};
    }
    else if (a.type == SPLIT_LINE) {
        splitLine(buff, a);
        // inverse = {a.l, a.c, a.data, INSERT};
    }
    else if (a.type == MERGE_LINE) {
        mergeLine(buff, a);
        // inverse = {a.l, a.c, a.data, INSERT};
    }

    buff->undoStack.push(a);
}