/**
 * @file Grafo.h
 * @author Leonardo Gomes (a20609@alunos.ipca.pt)
 * @brief Trabalho prático de AED2
 * @version 0.1
 * @date 2023-05-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_Alugeres 100
#define N 30
#define R 6371.0 // Raio médio da Terra em quilômetros
#define M_PI 3.14159265358979323846

#pragma warning (disable: 4996)

typedef struct Adj {
    int cod;
    float dist;
    struct Adj* next;
} Adj;

typedef struct PontoRecolha {
    int cod;
    char cidade[N];
    char coordenadas[N];
    struct PontoRecolha* next;
    struct Adj* adjacentes;
} PontoRecolha;

typedef struct PontoRecolhaFile
{
    int cod;
    char coordenadas[N];
    char cidade[N];
} PontoRecolhaFile;

typedef struct AdjFile
{
    int codDestino;    //codigo da Adjacência 
    int codOrigem;    //codigo da Adjacência 
    float dist;   
}AdjFile;

#pragma region Mat

double toRadians(double degree);
double calcularDistanciaGeocodes(const char* geocode1, const char* geocode2);

#pragma endregion


#pragma region Grafo

    PontoRecolha* CriaVertice(char* cidade, int cod, char* coordenadas);
    PontoRecolha* InsereVertice(PontoRecolha* g, PontoRecolha* novo);
    bool ExisteVertice(PontoRecolha* grafo, int cod);
    PontoRecolha* ProcuraVerticeCod(PontoRecolha* g, int cod);
    void LocalizarVerticesNoRaio(PontoRecolha* grafo, const char* geocodeReferencia, float raio);

#pragma endregion

#pragma region Adjacencias

    Adj* CriaAdj(int cod, float dist);
    Adj* InsereAdj(Adj* h, Adj* novo);
    bool ExisteAdjacencia(PontoRecolha* vertice, int codAdjacente);
    bool ExisteAdjacentes(Adj* h, int cod);

#pragma endregion

#pragma region Grafo_Adjacencias

    PontoRecolha* InsereAdjacenteVertice(PontoRecolha* g, char* origem, char* dest);
    PontoRecolha* InsereAdjacenteVerticeCod(PontoRecolha* g, int codOrigem, int codDest);

#pragma endregion

#pragma region Gravar_Ficheiros

    int gravaVerticesBinario(PontoRecolha* grafo, char* nomeFicheiro);
    int gravaAdjacenciasBinario(Adj* head, char* nomeFicheiro, int codVerticeOrigem);

#pragma endregion


#pragma region Ler_Ficheiros

    PontoRecolha* leVerticesBinario(PontoRecolha* grafo, char* nomeFicheiro, bool* resLeitura);
    PontoRecolha* leAdjacenciaBinario(PontoRecolha* grafo, bool* resLeitura);

#pragma endregion

#pragma region Interface

    void ImprimirGrafo(PontoRecolha* grafo);
    void menuGrafo();

#pragma endregion
