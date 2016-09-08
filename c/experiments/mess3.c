#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX 5

struct camesi {
    char camasa[33];
    char culoare[33];
    int marime;
    char material[33];
} myStruct;

int main()
{
    int i = 0;
    FILE *file = NULL;

    //Fill a structure with values
    memset(&myStruct, 0, sizeof(myStruct));
    memcpy(myStruct.camasa, "asdf1", 5);
    memcpy(myStruct.culoare, "blue", 4);
    myStruct.marime = 45;
    memcpy(myStruct.material, "skin", 4);

    //Open the file to write
    if ((file = fopen("test.txt", "w+")) == NULL) {
        printf("Error opening file to write\n");
        return -1;
    }

    for (i = 0; i < MAX; i++)
        fwrite(&myStruct, sizeof(myStruct), 1, file);

    fclose(file);

    //Open the file for read
    if ((file = fopen("test.txt", "r")) == NULL) {
        printf("Error opening file for read\n");
        return -1;
    }

    //Clear the myStruct from previous values
    memset(&myStruct, 0, sizeof(myStruct));

    //Read and display
    for (i = 0; i < MAX; i++)
    {
        fread(&myStruct, sizeof(myStruct), 1, file);
        printf("%s\t%s\t%d\t%s\n", myStruct.camasa, myStruct.culoare, myStruct.marime, myStruct.material);

        //Clear the myStruct from previous value as we will read again in same object in next iteration
        memset(&myStruct, 0, sizeof(myStruct));
    }

    fclose(file);

    return 0;
}
