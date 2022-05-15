//
// Created by Bruce and Thaïs on 07/04/2022.
//

#include "takuzu.h"
#include<math.h>


int choose()
/* This function have to let choose the user between a 4 or 8 map */
{
    int choice = -1;
    while ((choice != 4) && (choice != 8))
    {
        printf("Choose between 4 and (8):");
        scanf( "%d", &choice);
    }
    return choice;
}

COORDINATES enter_coordinates(int tl){
    /*Enter coordinates of the case*/
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
int move_is_correct(int Mat[LENGTH][LENGTH], int Mask[LENGTH][LENGTH], int tl)
{
    /* Verify if the move is correct*/
        COORDINATES  values = enter_coordinates(tl);
        sleep(1);
        int y = 0;
        int x = values.y-1;
        while (values.x != 'A'+y)
            y++;
        if (Mask[x][y]==1)
        //Case if the value is already wrote
        {
            printf("This is already filled coordinates, please choose something else.\n");
            move_is_correct(Mat,Mask,tl);
        }
        else
        //Case if the value can be correct ?
        {
            if (Mat[x][y] == values.value)
            {
                printf("Nice move!\n");
                Mask[x][y]=1;
                //modif_mask_function
                return 0;
            }
            else
            {
                // verify if the move is not wrong
                int countX = 0, countY = 0;
                for(int X=0; X<tl ; X++)
                {
                    if (Mask[X][y] == 1)
                    {
                        countX+=Mat[X][y];
                    }
                }

                for(int Y=0; Y<tl ; Y++)
                {
                    if (Mask[x][Y] == 1)
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
                    if (Mask[X][y] == 0)
                    {
                        countX+=Mat[X][y];
                    }
                }

                for(int Y=0; Y<tl ; Y++)
                {
                    if (Mask[x][Y] == 0)
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
                printf("Nope, valid move but incorrect case ;)\n");
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
    //verifying everything is good
    if (valid ==1){
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
/* This function prints the matrix for us to see it when needed*/
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


void Mask_matrix(int Mask[LENGTH][LENGTH], int tl)
/* This function creates a real mask onto the matrix*/
{
    for (int ligne =0; ligne<tl ; ligne++)
        for (int col=0; col<tl ; col++)
            Mask[ligne][col]=rand()%2;
}

void print_with_mask(int Mat[LENGTH][LENGTH], int Mask[LENGTH][LENGTH], int tl)
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
            if (Mask[ligne][col]==1)
                printf("%d ", Mat[ligne][col]);
            else
                printf("/ ");
        }
        printf("\n");
    }
}

void solve_matrix()
/* This function tries to solve the matrix*/
{
    int tl = choose();
    srand(time(NULL));
    int Mat[LENGTH][LENGTH];
    create_matrix(Mat, tl);
    int Mask[LENGTH][LENGTH];
    Mask_matrix(Mask, tl);
    int steps = 0;
    printf("The system will try to solve this Matrix : \n");
    print_with_mask(Mat,Mask,tl);
    int Unsolved = tl*tl;
    while (Unsolved > 0)
    {
        Unsolved = tl*tl;
        steps = solve_matrix_system(Mat, Mask, tl, steps);
        for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                if (Mask[x][y]==1)
                    Unsolved -=1;
            }
        }
    }
    printf("\nThe Solved Matrix is :\n");
    print_with_mask(Mat,Mask,tl);


}


int solve_matrix_system(int Mat[LENGTH][LENGTH], int Mask[LENGTH][LENGTH],int tl, int steps) {
    //First we check if a row is full of 1 or full of 0
    int success = 0;
    for (int x = 0; x < 4; x++) {
        int sum_row_1 = 0;
        int sum_row_0 = 0;
        for (int y = 0; y < 4; y++) {
            if ((Mask[x][y] == 1) && (Mat[x][y] == 1))
                sum_row_1++;
            if ((Mask[x][y] == 1) && (Mat[x][y] == 0))
                sum_row_0++;
        }
        for (int yp = 0; yp < 4; yp++) {
            if (sum_row_1 == (tl / 2)) {
                if (Mask[x][yp] == 0) {
                    Mat[x][yp] = 0;
                    Mask[x][yp] = 1;
                    success++;
                    steps++;
                    sleep(1);
                    printf("Searching...\n");
                    sleep(1);
                    printf("\nStep %d", steps);
                    print_with_mask(Mat,Mask, tl);
                    printf("\n");
                }
            }
            if (sum_row_0 == (tl / 2)) {
                if (Mask[x][yp] == 0) {
                    Mat[x][yp] = 1;
                    Mask[x][yp] = 1;
                    steps++;
                    success++;
                    sleep(1);
                    printf("Searching...\n");
                    sleep(1);
                    printf("\nStep %d", steps);
                    print_with_mask(Mat,Mask, tl);
                    printf("\n");
                }
            }
        }
    }
    for (int x = 0; x < 4; x++) {
        int sum_row_1 = 0;
        int sum_row_0 = 0;
        for (int y = 0; y < 4; y++) {
            if ((Mask[y][x] == 1) && (Mat[y][x] == 1))
                sum_row_1++;
            if ((Mask[y][x] == 1) && (Mat[y][x] == 0))
                sum_row_0++;
        }
        for (int xp = 0; xp < 4; xp++) {
            if (sum_row_1 == (tl / 2)) {
                if (Mask[xp][x] == 0) {
                    Mat[xp][x] = 0;
                    Mask[xp][x] = 1;
                    steps++;
                    success++;
                    sleep(1);
                    printf("Searching...\n");
                    sleep(1);
                    printf("\nStep %d", steps);
                    print_with_mask(Mat,Mask, tl);
                    printf("\n");
                }
            }
            if (sum_row_0 == (tl / 2)) {
                if (Mask[xp][x] == 0) {
                    Mat[xp][x] = 1;
                    Mask[xp][x] = 1;
                    steps++;
                    success++;
                    sleep(1);
                    printf("Searching...\n");
                    sleep(1);
                    printf("\nStep %d", steps);
                    print_with_mask(Mat,Mask, tl);
                    printf("\n");
                }
            }
        }
    }
    //if it can't find a logical move based on the matrix, it tries one without more searches
    if (success == 0){
        int end=0;
        for (int i=0; i<tl;i++){
            for (int j=0 ; j<tl; j++){
                if (Mask[i][j] == 0){
                    if (end != 1){
                        Mask[i][j] = 1;
                        steps++;
                        sleep(1);
                        printf("Searching...\n");
                        sleep(1);
                        printf("\nStep %d", steps);
                        print_with_mask(Mat,Mask, tl);
                        printf("\n");
                        end++;
                    }
                }
            }
        }
    }
    return steps;
}


int ask_menu(){
/* This function have to let choose the user between the option of the menu */
    int choice = -1;
    printf("Choose what do you want to do:");
    scanf( "%d", &choice);
    return choice;
}

int end(int Mask[LENGTH][LENGTH], int heart, int tl){
    /* It ends the game if there is no life anymore or if the grid is complete*/
    if (heart == 0) {
        printf("===GAME OVER===");
        return 1;
    }
    int sum=0;
    for (int i=0; i<tl;i++) {
        for (int j = 0; j < tl; j++) {
            sum += Mask[i][j];
        }
    }
    if (sum == tl*tl){
        printf("=== VICTORY!! WELL DONE <3===\n");
        return 1;
    }
    return 0;
}