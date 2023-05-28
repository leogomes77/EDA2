/**
 * @file Cliente.h
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

#define MAX_CLIENTES 100
#define N 50


typedef struct _Cliente
{
    char nome[N];
    int nif;
    char endereco[N];
    float saldo;
    struct _Cliente* seguinte;
} Cliente;

Cliente* CriarCliente(Cliente cliente);
Cliente* inserirCliente(Cliente* inicio, char nome[], int nif, char endereco[], float saldo); // Inserção de um novo registo
void listarClientes(Cliente* inicio); // listar na consola o conteúdo da lista ligada
bool existeCliente(Cliente* inicio, int nif); // Determinar existência do 'codigo' na lista ligada 'inicio'
Cliente* removerCliente(Cliente* inicio, int nif); // Remover um meio a partir do seu código
Cliente* editarCliente(Cliente* inicio, char nome[], int nif, char endereco[], float saldo); // Alterar dados

bool guardarClientes(Cliente* inicio);
Cliente* lerClientes();
void menuClientes();