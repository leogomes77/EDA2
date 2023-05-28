/**
 * @file Meio_Mobilidade.h
 * @author Leonardo Gomes (a20609@alunos.ipca.pt)
 * @brief Trabalho prático de AED2
 * @version 0.1
 * @date 2023-03-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_MEIOS 100
#define N 50

typedef struct _MeioMobilidade
{
    int id;
    char tipo[N];
    float cargaBateria;
    float custo;
    char localizacao[N];
} MeioMobilidade;

bool inserirMeioMobilidade(MeioMobilidade *meioMobilidade, int *numMeiosMobilidade);
bool guardarMeiosMobilidade(MeioMobilidade *meioMobilidade, int *numMeiosMobilidade);
bool carregarMeiosMobilidade(MeioMobilidade *meioMobilidade, int *numMeiosMobilidade);
bool removerMeioMobilidade(MeioMobilidade *meioMobilidade, int *numMeiosMobilidade, int id);
void listarPorLocalizacao(MeioMobilidade *meios, int *numMeios, char *localizacao);
void listarMeiosMobilidade();
bool editarMeioMobilidade(MeioMobilidade *meioMobilidade, int *numMeiosMobilidade, int id);
void listarPorAutonomia(MeioMobilidade *meioMobilidade, int *numMeiosMobilidade);
void MenuMobilidade();
