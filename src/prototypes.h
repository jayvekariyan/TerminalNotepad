//Contains all function prototypes
#include "definations.h"

// raw.pp

void disableRawMode();
void enableRawMode();
int readKey(Buffer* buff,char* c);

//files.cpp
Buffer* FileToBuff(std::string filename);
void BuffToFile(Buffer* buff);

// buffer.cpp
Buffer* newBuff(std::string filename);
void UpdateBuff(Buffer* buff,char c);
void DisplayBuff(Buffer* buff);

// display.cpp
void ClearScreen();
void SetCursor(int ,int y);
void moveUpCursor(Buffer*buff);
void moveDownCursor(Buffer*buff);
void moveLeftCursor(Buffer*buff);
void moveRightCursor(Buffer*buff);


//dll.cpp
DLL* newDLL();
void push_front(DLL* dll,Line* line);
void push_back(DLL* dll,Line* line);
std::string pop_front(DLL* dll);
std::string pop_back(DLL* dll);
void insert_after_cl(Buffer* buff,Line* new_line);
std::string delete_cl(Buffer* buff);
Line* back(DLL* dll);
Line* front(DLL* dll);

//undo_redo.cpp
void addAction(Buffer* buff,Action action);
void undo(Buffer* buff);
void redo(Buffer* buff);

void deleteChar(Buffer* buff ,Action action); 
void insertChar(Buffer* buff ,Action action);

void mergeLine(Buffer* buff,Action a);
void splitLine(Buffer* buff,Action a);

