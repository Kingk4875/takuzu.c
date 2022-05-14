//
// Created by Bruce on 07/04/2022.
//

#include "takuzu.h"
#include<math.h>


int choose()
/* This function have to let choose the user between a 4 or 8 map */
{
    int choice = -1;
    while ((choice != 4) && (choice != 8))
    {
        printf("Choose between 4 and 8:");
        scanf( "%d", &choice);
    }
    return choice;
}

COORDINATES enter_coordinates(int tl){
    COORDINATES co;
    printf("\nPleaser enter a letter IN UPPERCASE for the column and an INTEGER for the line separated by space : \n");
    scanf(" %c",&co.x);
    scanf(" %d",&co.y);
    while (((co.x>'A'+tl-1) || (co.x<'A')) || ((co.y>tl)||(co.y<1)))
    {
        printf("\nPleaser enter a letter IN UPPERCASE for the column and an INTEGER for the line separated by space : \n");
        scanf(" %c",&co.x);
        scanf(" %d",&co.y);
    }
    printf("You chose point (%c,%d)\n",co.x,co.y);
    printf("Now enter 1 or 0 : \n");
    scanf(" %d",&co.value);
    while((co.value !=0) && ( co.value != 1))
    {
        printf("Now enter 1 or 0 : \n");
        scanf(" %d",&co.value);
    }
    return co;
}
int move_is_correct(int Mat[LENGTH][LENGTH], int MASQUE[LENGTH][LENGTH], int tl)
{
        COORDINATES  values = enter_coordinates(tl);
        int y = 0;
        int x = values.y-1;
        while (values.x != 'A'+y)
            y++;
        if (MASQUE[x][y]==1)
        //Case if the value is already wrote
        {
            printf("This is already filled coordinates, please choose something else.\n");
            move_is_correct(Mat,MASQUE,tl);
        }
        else
        //Case if the value can be correct ?
        {
            if (Mat[x][y] == values.value)
            {
                printf("Nice move!\n");
                MASQUE[x][y]=1;
                //modif_mask_function
                return 0;
            }
            else
            {
                // verify if the move is not wrong
                int countX = 0, countY = 0;
                for(int X=0; X<tl ; X++)
                {
                    if (MASQUE[X][y] == 1)
                    {
                        countX+=Mat[X][y];
                    }
                }

                for(int Y=0; Y<tl ; Y++)
                {
                    if (MASQUE[x][Y] == 1)
                    {
                        countY+=Mat[x][Y];
                    }
                }
                if (values.value ==1) {
                    if (countX == tl / 2 || countY == tl / 2) {
                        printf("Wrong case, please follow the rules.\n You lost one heart.\n");
                        return 1;
                    }
                }
                countX = 0, countY = 0;
                for(int X=0; X<tl ; X++)
                {
                    if (MASQUE[X][y] == 0)
                    {
                        countX+=Mat[X][y];
                    }
                }

                for(int Y=0; Y<tl ; Y++)
                {
                    if (MASQUE[x][Y] == 0)
                    {
                        countY+=Mat[x][Y];
                    }
                }
                if (values.value ==0) {
                    if (countX == tl / 2 || countY == tl / 2) {
                        printf("Wrong case, please follow the rules.\n You lost one heart.\n");
                        return 1;
                    }
                }
                printf("Nope, correct but incorrect case ;)\n");
                return 0;
            }
        }
        return 1;

}

int check_matrix(int Mat[LENGTH][LENGTH], int tl){
    int valid =0, valid_rows=0;
    //check if there is same number of 0 and 1 in rows
    for (int i=0; i<tl;i++){
        int sum=0;
        for (int j=0; j<tl;j++){
            sum += Mat[i][j];
        }
        if (sum == (tl/2)){
            valid_rows +=1;
        }
    }
    if (valid_rows == tl){
        valid +=1;
    }
    //check if every row is different
    double nbs_row[4]={0,0,0,0,};
    for (int i=0; i<tl;i++){
        double nb=0;
        for (int j=0; j<tl;j++){
            nb += Mat[i][j]*pow(2,j);
        }
        nbs_row[i]=nb;
        for (int k=0; k<i;k++) {
            if (nbs_row[k] == nb) {
                valid -= 1;
            }
        }
    }
    for (int h=0;h<tl;h++){
    }
    valid +=1;
    //verifying everything is good
    if (valid ==2){
        return 1;
    }
    else{
        return 0;
    }
}
void create_matrix(int Mat[LENGTH][LENGTH], int tl){
/* This function call other functions as verify_columns, create_rows or check_matrix to create and make sure that the matrix is correct*/
    for (int i=0; i<tl; i++){
        create_rows(Mat, i, tl);
    }
    for (int x=0; x<tl;x++){
        verify_columns(Mat,x,tl);
    }
    int a= check_matrix(Mat, tl);
    if (a==0){
        create_matrix(Mat, tl);
    }
}

void verify_columns (int Mat[LENGTH][LENGTH], int x, int tl){
/* This function verify that colums are good in the matrix*/
    int sum=0, j=0;
    for (j=0; j<tl;j++) {
        const int MIN = 0, MAX = 1;
        int number = (rand() % (MAX + 1 - MIN)) + MIN; // MIN <= number <= MAX
        Mat[j][x] = number;
        sum += Mat[j][x];
    }
    if (sum != (tl/2)) {
        create_rows(Mat, j, tl);
        verify_columns(Mat, x, tl);
    }
}

void create_rows(int Mat[LENGTH][LENGTH], int i, int tl){
/* This function creates each row by each row to verify them one by one*/
    int sum=0;
    for (int j=0; j<tl;j++){
        const int MIN = 0, MAX = 1;
        int number = (rand() % (MAX + 1 - MIN)) + MIN; // MIN <= number <= MAX
        Mat[i][j] = number;
        sum += Mat[i][j];
    }
    if (sum != (tl/2)) {
        create_rows(Mat, i, tl);
    }
}

void print_matrix(int Mat[LENGTH][LENGTH], int tl)
/* This function prints the matrix*/
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
/* This function creates a real masque onto the matrix*/
{
    for (int ligne =0; ligne<tl ; ligne++)
        for (int col=0; col<tl ; col++)
            masque[ligne][col]=rand()%2;
}

void print_with_mask(int Mat[LENGTH][LENGTH], int masque[LENGTH][LENGTH], int tl)
/* This function prints the matrix with the mask on*/
{   printf("\n             ");
    for (int lettre =0; lettre<tl ; lettre++)
        printf("%c ",'A'+lettre);
    printf("\n");
    printf("            ");
    for (int lettre =0; lettre<tl*2 ; lettre++)
        printf("_");
    printf("\n");

    for (int ligne =0; ligne<tl ; ligne++)
    {
        printf("         ");
        printf("%c | ",'1'+ligne);
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

int ask_menu(){
/* This function have to let choose the user between the option of the menu */
    int choice = -1;
    printf("Choose what do you want to do:");
    scanf( "%d", &choice);
    return choice;
}

int end(int Masque[LENGTH][LENGTH], int heart, int tl){
    /* It ends the game if there is no life anymore or if the grid is complete*/
    if (heart == 0) {
        printf("===GAME OVER===");
        return 1;
    }
    int sum=0;
    for (int i=0; i<tl;i++) {
        for (int j = 0; j < tl; j++) {
            sum += Masque[i][j];
        }
    }
    if (sum == tl*tl){
        printf("=== VICTORY!! WELL DONE <3===\n");
        return 1;
    }
    return 0;
}