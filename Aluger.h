/**
 * @file Aluger.h
 * @author Leonardo Gomes (a20609@alunos.ipca.pt)
 * @brief Trabalho prático de AED2
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_Alugeres 100
#define N 30

typedef struct _Aluger
{
    char nifCliente[N];
    int idMeio;
    char dataInicio[N];
    char dataFim[N];
    float custo;
} Aluger;

bool inserirAluger(Aluger *Alugeres, int *numAlugeres);
bool guardarAluger(Aluger *Alugeres, int *numAlugeres);
bool carregarAluger(Aluger *Alugeres, int *numAlugeres);
bool listarAlugeres();
void menuAluger();