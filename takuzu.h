//
// Created by zhang on 07/04/2022.
//

#ifndef TAKUZU_TAKUZU_H
#define TAKUZU_TAKUZU_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH 8


int choose();
void print_full_matrix(int Mat[LENGTH][LENGTH], int tl);
int check_matrix(int Mat[LENGTH][LENGTH], int tl);
void create_matrix(int Mat[LENGTH][LENGTH],int tl);
void create_rows(int Mat[LENGTH][LENGTH], int i, int tl);
void verify_columns (int Mat[LENGTH][LENGTH], int x, int tl);
/* Cette fonction affiche la Matrice entrée en paramètre*/
void Masque_matrix(int Masque[LENGTH][LENGTH], int tl);
void print_with_mask(int Mat[LENGTH][LENGTH], int masque[LENGTH][LENGTH], int tl);

#endif //TAKUZU_TAKUZU_H
