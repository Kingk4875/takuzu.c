#include <stdio.h>
#include "takuzu.h"

void play(){
    int tl = choose(),life = 3, finished = 0;
    srand(time(NULL));
    int Mat[LENGTH][LENGTH];
    create_matrix(Mat, tl);
    int Mask[LENGTH][LENGTH];
    Mask_matrix(Mask, tl);
    COORDINATES x;
    //
    while (finished !=1) {
        print_with_mask(Mat, Mask, tl);
        life -= move_is_correct(Mat, Mask, tl);
        finished = end(Mask, life, tl);
        if (life > 0 && finished != 1) {
            printf("(You have still %d hearts)\n ...\n", life);
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
    printf("3) Solve Matrix System \n");
    printf("4) Quit the game\n");
    int response = ask_menu();
    switch (response){
        case 1:
            play();
            int back=1;
            printf("\nEnter 0 to return to the menu:");
            scanf("%d", &back);
            while (back != 0){
                printf("\nEnter 0 to return to the menu:");
                scanf("%d", &back);
            }
            main();
            break;
        case 2:
            rules();
            back=1;
            printf("\nEnter 0 to return to the menu:");
            scanf("%d", &back);
            while (back != 0){
                printf("\nEnter 0 to return to the menu:");
                scanf("%d", &back);
            }
            main();
            break;
        case 3:
            solve_matrix();
            back=1;
            printf("\nEnter 0 to return to the menu:");
            scanf("%d", &back);
            while (back != 0){
                printf("\nEnter 0 to return to the menu:");
                scanf("%d", &back);
            }
            main();
            break;
        case 4:
            printf("Goodbye!");
            break;
        default:
            printf("~Wrong response.~\n");
            main();
            break;
    }
    return 0;
}
