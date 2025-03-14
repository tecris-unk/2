//
// Created by intak on 24.02.2025.
//

#include "functions.h"
void setNumber(int* number)
{
    int isInvalid = 0;
    do {
        isInvalid = 0;
        int i = 0;
        *number = 0;
        char digits[10];
        scanf("%s", digits);
        int negative = 1;
        if(digits[0] == '-'){negative = -1;i++;}
        do {
            if (digits[i] < '0' || digits[i] > '9') {
                printf("Enter a valid number\n");
                isInvalid = 1;
                while(getchar()!='\n');
                break;
            }
            else {*number = *number * 10 + digits[i] - '0'; }
        } while(digits[++i] != 0);
        *number *= negative;
    }while(isInvalid == 1);
    rewind(stdin);
}

void initFile(File *file, int n_arg, char *arg[])
{
    char* txt =".txt\0";

    int size = 0;
    if (n_arg > 1){
        file->name = (char*)malloc(sizeof(arg[1]) * 20);
        if(file->name == NULL){fprintf(stderr, "memory cant be allocated\n");exit(1);}
        file->name = arg[1];
        strSize(file->name, &size);
        resize(&file->name, size+1);
    }

    strCat(&file->name, size, txt);
    free(txt);
    coutString(file->name);
    printf("\n");
    file->size = 0;
    enterFile(file);
    outFile(file->name);
}
void fileCheck(FILE *f)
{
    if(!f)
    {
        printf("Cant open file\n");
        exit(1);
    }
}
void solve(File *file)
{
    int ans = 0;
    file->myFile = fopen(file->name, "r+");
    fileCheck(file->myFile);

    int num, size = 0;
    while(fscanf(file->myFile,"%d ", &num) == 1)
    {
        ans += num;
        size++;
    }
    printf("Sum is %d\n", ans);
    if(file->size > 1){swapInFile(file, size-2, size-1);}

    printf("Here is your changed file\n");
    fclose(file->myFile);
    outFile(file->name);

}
void enterFile(File *file)
{
    printf("enter size of the array\n");
    setNumber(&file->size);

    file->myFile = fopen(file->name, "w");
    fileCheck(file->myFile);

    printf("enter array elements\n");
    int num;
    for(int i = 0; i < file->size; ++i)
    {
        setNumber(&num);
        fprintf(file->myFile, "%d ", num);
    }
    fclose(file->myFile);
    printf("File has been written\n");
}
void outFile(char* filename)
{
    FILE *f = fopen(filename, "r");
    fileCheck(f);

    int num;
    while (fscanf(f, "%d ", &num) == 1)
    {
        printf("%d ", num);
    }
    printf("\n");
    fclose(f);
}

void writeNum(int pos, const int *num, File *file)
{
    fseek(file->myFile, pos, SEEK_SET);
    fprintf(file->myFile, "%d ", *num);
}

void swapInFile(File *file, int pos1, int pos2)
{
    rewind(file->myFile);
    if(pos1 > pos2){pos1^=(pos2^=(pos1^=pos2));}
    int i = 0, num, num1, num2, posBytes1, posBytes2;
    while(i < pos2 && fscanf(file->myFile, "%d ", &num) == 1)
    {
        i++;
        if(i == pos1){
            posBytes1 = ftell(file->myFile);
            fscanf(file->myFile, "%d ", &num);
            i++;
            num1 = num;
        }
        if(i == pos2)
        {
            fscanf(file->myFile, "%d ", &num);
            num2 = num;
            writeNum(posBytes1, &num2, file);
        }
    }
    i = pos1+1;
    while(i < pos2 && fscanf(file->myFile, "%d ", &num) == 1)
    {
        i++;
    }
    posBytes2 = ftell(file->myFile);
    writeNum(posBytes2, &num1, file);
}
void deleteFile(File *file)
{
    remove(file->name);
    free(file->name);
}
