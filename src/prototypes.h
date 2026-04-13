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
Buffer* newBuff();
void UpdateBuff(Buffer* buff,char c);
void DisplayBuff(Buffer* buff);

// display.cpp
void ClearScreen();
void SetCursor(int ,int y);
void moveUpCursor(Buffer*buff);
void moveDownCursor(Buffer*buff);
void moveLeftCursor(Buffer*buff);
void moveRightCursor(Buffer*buff);