//
// Created by Bruce and Thaïs on 07/04/2022.
//

#ifndef TAKUZU_TAKUZU_H
#define TAKUZU_TAKUZU_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LENGTH 8 //Maximum length, our real length choosen being tl
typedef struct {
    int x;
    int y;
    int value;
}COORDINATES;

int choose();
COORDINATES enter_coordinates(int tl);
int move_is_correct(int Mat[LENGTH][LENGTH], int Mask[LENGTH][LENGTH], int tl);
void print_matrix(int Mat[LENGTH][LENGTH], int tl);
int check_matrix(int Mat[LENGTH][LENGTH], int tl);
void create_matrix(int Mat[LENGTH][LENGTH],int tl);
void create_rows(int Mat[LENGTH][LENGTH], int i, int tl);
void verify_columns (int Mat[LENGTH][LENGTH], int x, int tl);
void Mask_matrix(int Mask[LENGTH][LENGTH], int tl);
void print_with_mask(int Mat[LENGTH][LENGTH], int Mask[LENGTH][LENGTH], int tl);
void solve_matrix();
int solve_matrix_system(int Mat[LENGTH][LENGTH], int Mask[LENGTH][LENGTH], int tl, int steps);
int ask_menu();
int end(int Mask[LENGTH][LENGTH], int heart, int tl);

#endif //TAKUZU_TAKUZU_H
