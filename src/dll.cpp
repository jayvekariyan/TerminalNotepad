#include "prototypes.h"

// template <typename T>

// int main(){
//     DLL* dll = newDLL();
//     Line *line1 = new Line;
//     Line *line2 = new Line;
//     Line *line3 = new Line;
//     line1->text = "1";
//     line2->text = "2";
//     line3->text = "3";

//     push_back(dll,line1);
//     push_back(dll,line2);
//     push_back(dll,line3);

    // pop_back(dll);
    // pop_back(dll);
    // pop_back(dll);
    // std::cout<<pop_back(dll)<<pop_back(dll)<<pop_back(dll);
// }

DLL* newDLL(){
    DLL* dll = new DLL;
    dll->back=dll->front=NULL;
    dll->size = 0;
    return dll;
}

void push_front(DLL* dll,Line* line){
    if (dll->front==NULL)
    {
        dll->back=dll->front=line;
        dll->size++;
        return;
    }
    line->next = dll->front;
    dll->front->prev = line;
    dll->front = line;
    line->prev=NULL;
    dll->size++;
    
}
void push_back(DLL* dll,Line* line){
    if (dll->back==NULL)
    {
        dll->back=dll->front=line;
        dll->size++;
        return;
    }
    dll->back->next = line;
    line->prev = dll->back;
    dll->back = line;
    line->next=NULL;
    dll->size++;
}
std::string pop_front(DLL* dll){
    if (dll->front==NULL)
    {
        return "Error Empty list";
    }
    
    Line* temp = dll->front;
    std::string str = temp->text;
    dll->front = dll->front->next;
    if (dll->front!=NULL)
    {
        dll->front->prev = NULL;
    }
    dll->size--;
    delete temp;
    return str;
}
std::string pop_back(DLL* dll){
    if (dll->back==NULL)
    {
        return "Error Empty list";

    }
    Line* temp = dll->back;
    std::string str = temp->text;
    dll->back = dll->back->prev;
    if (dll->back!=NULL)
    {
        dll->back->next = NULL;
    }
    dll->size--;
    delete temp;
    return str;
}

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

// std::string delete_cl(Buffer* buff){
//     Line* line = buff->curr_line;
//     std::string str = line->text;
//     line->prev->next = line->next;
//     line->next->prev= line->prev;
//     buff->size--;
//     delete line;
//     return str;
// }

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

Line* back(DLL* dll){
    return dll->back;
}
Line* front(DLL* dll){
    return dll->front;
}