#include "prototypes.h"


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
