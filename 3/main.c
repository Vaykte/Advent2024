#include <stdlib.h>
#include <stdio.h>






int main (int argc, char* argv[]){

    FILE* pointer;
    if (argc != 2) {
        printf("\tUsage : %s filename\n", argv[0]);
        return 1;
    }

    pointer = fopen(argv[1], "r");
    if (pointer == NULL) { printf("There's a problem with the pointer\n"); return 1;};

    int b_m = 0; // True if detects "m"
    int b_u = 0; // True if detects "u" and the previous bools are true
    int b_l = 0; // True if detects "l" and the previous bools are true
    int b_firstnum = 0; // True if detects a first number and the previous bools are true
    int b_secondnum = 0; // True if detects a second number and the previous bools are true
    int b_clospar = 0; // True if detects ")" and the previous bools are true
 
    int first_num = 0; // Equals to the first number in a mul op
    int second_num = 0; // Equals to the second number in a mul op
    int res = 0;
    int * addrarray[8] = {&b_m, &b_u, &b_l, &b_firstnum, &b_secondnum, &b_clospar, &first_num, &second_num};
    

    void reset_bools(int size, int ** inttab){
        for (int i = 0; i< size; i++){
            *inttab[i] = 0;
        };
    };

    int c = fgetc(pointer);
    while (c != EOF) {
        if (c == 'm') { b_m = 1;}
        else if (c == 'u' && b_m) { b_u = 1;}
        else if (c == 'l' && b_u) { b_l = 1;}
        else if (c == '(' && b_l ) {c = fscanf(pointer, "%d", &first_num); printf("The first number is %d | ", first_num); b_firstnum = 1; continue}
        else if (c == ',' && b_firstnum) {c = fscanf(pointer, "%d", &second_num),printf("The second number is %d\n", second_num); b_secondnum = 1;}
        else if (c == ')' && b_secondnum) { res += first_num*second_num; reset_bools(8, addrarray);}
        else {
            
            reset_bools(8, addrarray);
        }
        c = fgetc(pointer); // Next char
    }

    printf("Result : %d\n", res);
   




    return 0;
}