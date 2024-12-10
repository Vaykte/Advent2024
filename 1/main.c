#include <stdio.h>
#include <stdlib.h>


int comp(const void* a, const void* b) {
      
    return (*(int*)a - *(int*)b);
}

int count_in_sorted_array(int *array, int length, int target){
    int nb_found = 0;
    int previously_found = 0;

    for (int i = 0; i<length ; i++)
    {
        if (array[i] == target) {
            nb_found+=1;
            previously_found = 1;
            }
        else if (previously_found) break;
    }
    
    return nb_found;
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

    printf("Array length is %d\n", length);
    int array1[length];
    int array2[length];
    fseek(pointer, 0, SEEK_SET);
    for (int i = 0; i<length; i++)
    {
        fscanf(pointer,"%d %d\n",&first_int,&second_int);
        array1[i] = first_int;
        array2[i] = second_int;
    }
    
    qsort(array1, length, sizeof(int), comp);
    qsort(array2, length, sizeof(int), comp);

    int previous_int = 0;
    int number_of_occurences = 0;
    for (int i = 0; i<length; i++)
    {
        if (array1[i] == previous_int) result+= previous_int*number_of_occurences;
        else {
            previous_int = array1[i]; // Which is actually the current int
            number_of_occurences = count_in_sorted_array(array2, length, previous_int);
            result+= previous_int * number_of_occurences;
        }
        
    }


    printf("Result is %d\n", result);



    return 0;
}

