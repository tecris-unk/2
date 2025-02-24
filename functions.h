//
// Created by intak on 24.02.2025.
//

#ifndef INC_2_FUNCTIONS_H
#define INC_2_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

void resize(char** array, int size);
void strCat(char** string, int size, const char* sumString);
void coutString(char* string);
void initFile(File *file, int n_arg, char *arg[]);
void strSize(const char *string, int* size);
void fileCheck(FILE *f);
void setNumber(int* number);
void outFile(char* filename);
void enterFile(File *file);
void writeNum(int pos, const int *num, File *file);
void solve(File *file);
void deleteFile(File *file);
void swapInFile(File *file);


#endif //INC_2_FUNCTIONS_H
