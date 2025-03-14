//
// Created by intak on 01.03.2025.
//

#include "mystring.h"
void coutString(char* string)
{
    for(int i = 0; string[i] != '\0'; ++i)
        printf("%c", string[i]);
}
void strSize(const char *string, int* size)
{
    while(string[*size] != '\0' && string[*size] != EOF)
    {
        (*size)++;
    }
}
void resize(char** array, int size)
{
    char *temp = NULL;
    temp = (char*)realloc(*array, sizeof(char) * (size+1));
    if(temp == NULL){
        printf("memory cant be allocated\n");
        free(temp);
        exit(1);
    }
    else{
        *array = (char*)temp;
        (*array)[size] = '\0';
    }
}
void strCat(char** string, int size, const char* sumString)
{
    int i = 0;
    while(sumString[i]!='\0' && sumString[i] != EOF)
    {
        resize(string, size+i+1);
        (*string)[size+i] = sumString[i];
        i++;
    }
}
void erase(int *size, char** array, int i, int length)
{
    if(i < 0 || length <= 0) {return;}
    if(i + length > *size){length = *size - i;}

    for (; i + length < *size; ++i)
        (*array)[i] = (*array)[i + length];

    *size -= length;
    resize(array, *size);
}

void scanString(char **string, int *size)
{
    *string = NULL;
    resize(string, 0);
    int c;
    for(int i=0;(c=getchar())!='\n' && c != EOF ;++i)
    {
        *size = i+1;
        resize(string, *size);
        (*string)[i] = (char) c;
    }
}