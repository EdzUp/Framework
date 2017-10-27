//
//  FileSystem.h - Copyright (C)EdzUp
//  Programmed by Ed 'EdzUp' Upton
//

#include <iostream>
#include <ostream>
#include <fstream>
#include "FileSystem.h"

std::ofstream    WriteData;
std::ifstream    ReadData;
char*       MemBlock;
bool        writing;                    //true if the file is open for writing
long long   Size;                       //this is the size of the file
bool        FileOk;                     //true if this file is ok

