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
 
    int b_domul = 1; // True if detects "do()" and false if detects "don't()"
    
    int first_num = 0; // Equals to the first number in a mul op
    int second_num = 0; // Equals to the second number in a mul op
    int res = 0;
    int * addrarray[8] = {&b_m, &b_u, &b_l, &b_firstnum, &b_secondnum, &b_clospar, &first_num, &second_num};
    

    void reset_bools(int size, int ** inttab){
        for (int i = 0; i< size; i++){
            *inttab[i] = 0;
        };
    };

    int c = fgetc(pointer); // First char
    while (c != EOF) {
        if (b_domul && c == 'm') { // Detects mul(n1,n2) patern
            c = fgetc(pointer); // Next char
            if (c == 'u') {
                c = fgetc(pointer); // Next char
                if (c == 'l') {
                    c = fgetc(pointer); // Next char
                    if (c == '(') {
                        c = fscanf(pointer, "%d", &first_num); // First number of a mul
                        c = fgetc(pointer); // Next char
                        if (c == ',') {
                            c = fscanf(pointer, "%d", &second_num); // Second number of a mul
                            c = fgetc(pointer); // Next char
                            if (c == ')') {
                                res += first_num*second_num;
                                c = fgetc(pointer); // Next char
                            }
                        }
                    }
                }
            }
        }
        else if (c == 'd') { // Detects do() and don't() patern
            c = fgetc(pointer); // Next char
            if (c == 'o') {
                c = fgetc(pointer); // Next char
                if (c == '('){
                    c = fgetc(pointer); // Next char
                    if (c == ')') {
                        b_domul = 1;
                        c = fgetc(pointer); // Next char
                    }
                }
                else if (c == 'n'){
                    c = fgetc(pointer); // Next char
                    if (c == 39){ // Apostrophe
                        c = fgetc(pointer); // Next char
                        if (c == 't'){
                            c = fgetc(pointer); // Next char
                            if (c == '('){
                                c = fgetc(pointer); // Next char
                                    if (c == ')') {
                                        b_domul = 0;
                                        c = fgetc(pointer); // Next char
                                    }
                            }
                        }
                    }
                }
            }
        }
        else c = fgetc(pointer); // Next char
    }

    printf("Result : %d\n", res);
   




    return 0;
}