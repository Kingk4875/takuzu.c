//
// Created by Bruce on 07/04/2022.
//

#include "takuzu.h"



int choose()
/* This function have to let choose the user between a 4 or 8 map */
{
    int choice = -1;
    while ((choice != 4) && (choice != 8))
    {
        printf("Choose between 4 and 8: ");
        scanf( "%d", &choice);
    }
    return choice;
}

int check_matrix(int Mat[LENGTH][LENGTH], int tl){
    int valid =0, valid_rows=0;
    //check if there is same number of 0 and 1 in rows
    for (int i=0; i<tl;i++){
        int sum=0;
        for (int j=0; j<tl;j++){
            sum += Mat[i][j];
        }
        printf("The sum is %d\n", sum);
        if (sum == (tl/2)){
            valid_rows +=1;
        }
    }
    printf("Number of valid rows is: %d\n", valid_rows);
    if (valid_rows == tl){
        valid +=1;
    }
    printf("Valid? %d\n", valid);
    if (valid ==1){
        return 1;
    }
    else{
        return 0;
    }
}
void create_matrix(int Mat[TAILLE][TAILLE], int tl){
    for (int i=0; i<tl; i++){
        create_rows(Mat[TAILLE][TAILLE], i, tl);
    }
}

void create_rows(int Mat[TAILLE][TAILLE], int i, int tl){
    int sum=0;
    for (int j=0; j<tl;j++){
        const int MIN = 0, MAX = 1;
        int number = (rand() % (MAX + 1 - MIN)) + MIN; // MIN <= number <= MAX
        Mat[i][j] = number;
        sum += Mat[i][j];
    }
    if (sum != (tl/2)){
        create_rows(Mat[TAILLE][TAILLE], i, tl);
    }
}

void print_full_matrix(int Mat[LENGTH][LENGTH], int tl)
/* Cette fonction affiche la Matrice entrée en paramètre*/
{
    for (int ligne = 0; ligne<tl;ligne++)
    {
        for (int col = 0; col<tl; col++)
        {
            printf("%d ", Mat[ligne][col]);
        }
        printf("\n");
    }
}


void Masque_matrix(int masque[LENGTH][LENGTH], int tl)
/* Cette fonction modifie un tableau masque pour en faire un masque ne taille LENGTH*/
{
    for (int ligne =0; ligne<tl ; ligne++)
        for (int col=0; col<tl ; col++)
            masque[ligne][col]=rand()%2;
}

void print_with_mask(int Mat[LENGTH][LENGTH], int masque[LENGTH][LENGTH], int tl)
/* Cette fonction affiche la Matrice entrée en paramètre avec son masque*/
{   printf("            ");
    for (int lettre =0; lettre<tl ; lettre++)
        printf("%c ",'A'+lettre);
    printf("\n");
    printf("            ");
    for (int lettre =0; lettre<tl*2 ; lettre++)
        printf("_");
    printf("\n");

    for (int ligne =0; ligne<tl ; ligne++)
    {
        printf("%d COLONNE | ",ligne+1);
        for (int col=0; col<tl ; col++)
        {
            if (masque[ligne][col]==1)
                printf("%d ", Mat[ligne][col]);
            else
                printf("/ ");
        }
        printf("\n");
    }
}

