#include <stdio.h>
#include <stdlib.h>


int comp(const void* a, const void* b) {
      
    return (*(int*)a - *(int*)b);
}


int main (int argc, char * argv[]){

    FILE* pointer;
    if (argc != 2) {
        printf("\tUsage : %s filename\n", argv[0]);
        return 1;
    }

    pointer = fopen(argv[1], "r");
    if (pointer == NULL) { printf("There's a problem with the pointer\n"); return 1;};

    int first_int;
    int second_int;
    int result = 0;
    int distance = 0;
    char c;

    int length = 0;
    while (!feof(pointer)) // Getting length of each array
    {
        fscanf(pointer,"%d %d\n",&first_int,&second_int);
        // printf("The first number is %d\n", first_int);
        // printf("The second number is %d\n", second_int);
        length+=1;
    }
    printf("Length is %d\n", length);
    int array1[length];
    int array2[length];
    fseek(pointer, 0, SEEK_SET);

    for (int i = 0; i<1000; i++)
    {
        fscanf(pointer,"%d %d\n",&first_int,&second_int);
        array1[i] = first_int;
        array2[i] = second_int;
    }
    
    qsort(array1, length, sizeof(int), comp);
    qsort(array2, length, sizeof(int), comp);

    for (int i = 0; i<1000; i++)
    {
        distance = abs(array2[i]-array1[i]);
        printf("\tCurrent distance is %d\n", distance);
        result+=distance;
    }


    printf("Result is %d\n", result);



    return 0;
}

