#include <stdlib.h>
#include <stdio.h>

void uwu() { printf("uwu\n"); }

int main(int argc, char *argv[])
{

    FILE *pointer;
    if (argc != 2)
    {
        printf("\tUsage : %s filename\n", argv[0]);
        return 1;
    }

    pointer = fopen(argv[1], "r");
    if (pointer == NULL)
    {
        printf("There's a problem with the pointer\n");
        return 1;
    };

    int array_length = 0;

    char c;
    int scanned;
    int line_start;
    int i;

    int result = 0; // Number of Safe
    while (c != EOF)
    {
        line_start = ftell(pointer);
        printf("line_start : %d\n", line_start);
        array_length = 0;


        // Parse the line to see how long is the array we'll have to create
        while (c != '\n' && c != EOF)
        {

            fscanf(pointer, "%d", &scanned);
            c = getc(pointer);
            // printf("Scanned : %d \n", scanned);

            // printf("Char : %c \n", c);
            array_length += 1;
            // printf("Array Length: %d\n", array_length);
        }


        // Storing and treating values in an array
        if (array_length < 2) result += 1;
        else
        {
            int array[array_length];
            fseek(pointer, line_start, SEEK_SET); // Puts the pointer back to the beginning of the line to store all the value in an array this time
            c = getc(pointer);
            ungetc(c, pointer);

            i = 0;
            // Some kind of for loop to store the integers
            while (c != '\n' && c != EOF)
            {
                fscanf(pointer, "%d", &array[i]);
                c = getc(pointer);
                printf("Scanned and stored : %d\n", array[i]);
                i += 1;
            }
            
            // Treatment of the values
            int croissant = 0;
            if (array[0] < array[1]) croissant = 1;
            printf("Croissant Status: %d\n",croissant);
            if (croissant){
                for (int i = 0; i<array_length-1; i++)
                {
                    printf("Array[i+1] : %d | Array[i] : %d\n", array[i+1], array[i]);
                    if (array[i+1] - array[i] <= 0 || array[i+1] - array[i] > 3){printf("\tNot Safe Line\n"); break;}
                    if (i == array_length - 2) {result+=1; printf("\tOne more Safe !\n");}
                }
            }
            else {
                for (int i = 0; i<array_length-1; i++)
                {
                    printf("Array[i+1] : %d | Array[i] : %d\n", array[i+1], array[i]);
                    if (array[i] - array[i+1] <= 0 || array[i] - array[i+1] > 3) {printf("\tNot Safe Line\n") ; break;}
                    if (i == array_length - 2) {result+=1; printf("\tOne more Safe !\n");}
                }
            }
        }

        printf("Next Line\n");

        c = getc(pointer);
        ungetc(c, pointer);

        
    }
    printf("Result | Number of Safe : %d \n", result);
    return 0;
}