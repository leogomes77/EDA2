/**
 * @file Gestor.h
 * @author Leonardo Gomes (a20609@alunos.ipca.pt)
 * @brief Trabalho prático de AED2
 * @version 0.1
 * @date 2023-03-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define MAX_Gestores 100
#define N 50

typedef struct _Gestor
{
    char nome[N];
    char email[N];
    char senha[N];
} Gestor;

bool inserirGestor(Gestor *Gestores, int *numGestores);
bool guardarGestores(Gestor *Gestores, int *numGestores);
bool carregarGestores(Gestor *Gestores, int *numGestores);
bool removerGestor(Gestor *Gestores, int *numGestores, char *email);
void listarGestores();
bool editarGestor(Gestor *Gestores, int *numGestores, char *email);
void menuGestores();