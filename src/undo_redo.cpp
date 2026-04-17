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
    curr->text.insert(a.c-2, 1,a.data);
    //update cursor
    curr->col = a.c;
    buff->curr_line = curr;
    buff->ln = a.l;
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

    if (a.type == INSERT)
    {
        deleteChar(buff,a);
        // inverse = {a.l, a.c, a.data, DELETE};
    } else {
        insertChar(buff, a);
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

    if (a.type == INSERT){
        insertChar(buff, a);
        // inverse = {a.l, a.c, a.data, DELETE};
        
    }
    else{
        deleteChar(buff,a);
        // inverse = {a.l, a.c, a.data, DELETE};

    }

    buff->undoStack.push(a);
}