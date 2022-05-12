#include <stdio.h>
#include "takuzu.h"

int main() {
    int tl = choose();
    srand(time(NULL));

    int Mat[LENGTH][LENGTH];
    create_matrix(Mat, LENGTH);
    int a = 0;
    while (a ==0){
        a=check_matrix(Mat, tl);
        printf("Test in process\n");
        if (a==0){
            create_matrix(Mat, tl);
        }
    }
    int* Masque[LENGTH][LENGTH];
    print_full_matrix(Mat,tl);
    printf("\nFiltre\n");
    Masque_matrix(Masque, tl);
    print_full_matrix(Masque, tl);
    printf("\nMatrice avec filtre\n");
    print_with_mask(Mat,Masque,tl);

    return 0;
}