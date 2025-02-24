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
void openFile(File *file)
{
    file->myFile = fopen(file->name, "r+");
    if(!file->myFile)
    {
        printf("Cant open file\n");
        system("pause");
        exit(0);
    }
}
void solve(File *file)
{
    int ans = 0;
    openFile(file);
    int num;
    while(fscanf(file->myFile,"%d ", &num) == 1)
    {
        ans += num;
    }

    printf("Sum is %d\n", ans);

    if(file->size > 1){swapInFile(file);}

    printf("Here is your changed file\n");
    fclose(file->myFile);
    outFile(file->name);

}
void enterFile(File *file)
{
    printf("enter size of the array\n");
    setNumber(&file->size);
    file->myFile = fopen(file->name, "w");
    if(!file->myFile)
    {
        printf("Cant open file\n");
        system("pause");
        exit(0);
    }
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
    if(!f)
    {
        printf("Cant open file\n");
        system("pause");
        exit(0);
    }
    int num;
    while (fscanf(f, "%d ", &num) == 1)
    {
        printf("%d ", num);
    }
    printf("\n");
    fclose(f);
}

void writeNum(int pos, int *num, File *file)
{
    fseek(file->myFile, pos, SEEK_SET);
    fprintf(file->myFile, "%d ", *num);
}
void swapInFile(File *file)
{
    rewind(file->myFile);
    int i = 0, num, num1, num2;
    while(i < file->size -2 && fscanf(file->myFile, "%d ", &num) == 1)
    {
        i++;
    }
    int pos1 = ftell(file->myFile);
    fscanf(file->myFile, "%d ", &num);
    num1 = num;

    fscanf(file->myFile, "%d", &num);
    num2 = num;

    writeNum(pos1, &num2, file);
    int pos2 = ftell(file->myFile);
    writeNum(pos2, &num1, file);
}

void deleteFile(File *file)
{
    remove(file->name);
    free(file->name);
}
