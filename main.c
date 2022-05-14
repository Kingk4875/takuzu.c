#include <stdio.h>
#include "takuzu.h"

void play(){
    int tl = choose(),life = 3, finished = 0;
    srand(time(NULL));
    int Mat[LENGTH][LENGTH];
    create_matrix(Mat, tl);
    int Masque[LENGTH][LENGTH];
    Masque_matrix(Masque, tl);
    COORDINATES x;
    //
    while (finished !=1) {
        print_with_mask(Mat, Masque, tl);
        life -= move_is_correct(Mat, Masque, tl);
        finished = end(Masque, life, tl);
        if (life > 0 && finished != 1) {
            printf("You have still %d hearts\n ...\n", life);
        }
    }
}
void rules(){
    printf("\n===These are the rules:===\n");
    printf("1) There must be the same number of ZERO and ONE in a line or a column\n");
    printf("2) Do not put 3 ONE or ZERO next to each other in a row or column\n");
    printf("3) Lines and columns are all different\n");
}

int main() {
    printf("\n      === TAKUZU MENU ===\n");
    printf("1) Play the game\n");
    printf("2) See rules\n");
    int response = ask_menu();
    switch (response){
        case 1:
            play();
            break;
        case 2:
            rules();
            int back;
            printf("Enter 0 to return to the menu:");
            scanf("%d", &back);
            if (back==0) {
                main();
            }
            break;
        default:
            printf("~Wrong response.~\n");
            main();
            break;
    }
    return 0;
}
