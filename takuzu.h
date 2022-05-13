//
// Created by zhang on 07/04/2022.
//

#ifndef TAKUZU_TAKUZU_H
#define TAKUZU_TAKUZU_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH 8 //Maximum length, our real length choosen being tl
typedef struct {
    int x;
    int y;
    int value;
}COORDINATES;

int choose();
COORDINATES enter_coordinates(int tl);
int move_is_correct(int Mat[LENGTH][LENGTH], int MASQUE[LENGTH][LENGTH], int tl);
void print_matrix(int Mat[LENGTH][LENGTH], int tl);
int check_matrix(int Mat[LENGTH][LENGTH], int tl);
void create_matrix(int Mat[LENGTH][LENGTH],int tl);
void create_rows(int Mat[LENGTH][LENGTH], int i, int tl);
void verify_columns (int Mat[LENGTH][LENGTH], int x, int tl);
void Masque_matrix(int Masque[LENGTH][LENGTH], int tl);
void print_with_mask(int Mat[LENGTH][LENGTH], int masque[LENGTH][LENGTH], int tl);
int ask_menu();

#endif //TAKUZU_TAKUZU_H
