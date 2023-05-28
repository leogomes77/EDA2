/**
 * @file Cliente.c
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
#include "Cliente.h"


/**
 * @brief Cria um cliente
 * 
 * @param cliente 
 * @return Cliente* 
 */

Cliente* CriarCliente(Cliente cliente) {
    // Alocar memória
    Cliente* aux = (Cliente*)malloc(sizeof(Cliente));

    // Inserir atributos 
    strcpy(aux->endereco, cliente.endereco);
    strcpy(aux->nome, cliente.nome);
    aux->nif = cliente.nif;

    aux->saldo = cliente.saldo; 

    return aux;
}; 


/**
 * @brief Verifica se existe um cliente
 * 
 * @param inicio 
 * @param nif 
 * @return true 
 * @return false 
 */

bool existeCliente(Cliente* inicio, int nif)
{
  while(inicio!=NULL)
  {
    if (inicio->nif == nif ) return true;
    inicio = inicio->seguinte;
  }
  return false;
}


/**
 * @brief Insere um cliente
 * 
 * @param inicio 
 * @param nome 
 * @param nif 
 * @param endereco 
 * @param saldo 
 * @return Cliente* 
 */

Cliente* inserirCliente(Cliente* inicio, char nome[], int nif, char endereco[], float saldo)
{
    if (!existeCliente(inicio, nif))
    {
        Cliente* novo = malloc(sizeof(struct _Cliente));
        if (novo != NULL)
        {
            strcpy(novo->nome, nome);
            novo->nif = nif;
            strcpy(novo->endereco, endereco);
            novo->saldo = saldo;
            novo->seguinte = NULL;
            if (inicio == NULL)
            {
                // se a lista estiver vazia, o novo cliente será o primeiro nó
                inicio = novo;
            }
            else
            {
                // percorre a lista até o último nó
                Cliente* atual = inicio;
                while (atual->seguinte != NULL)
                {
                    atual = atual->seguinte;
                }
                // adiciona o novo cliente após o último nó
                atual->seguinte = novo;
            }
        }
    }
    return inicio;
}


/**
 * @brief Guarda todos os registos no ficheiro clientes.txt
 * 
 * @param inicio 
 * @return true 
 * @return false 
 */

bool guardarClientes(Cliente* inicio)
{
    FILE* fp;
    fp = fopen("clientes.txt","w");
    if (fp!=NULL)
    {
        Cliente* aux= inicio;
        while (aux != NULL) {
            fprintf(fp,"%s;%d;%s;%f\n", aux->nome, aux->nif, aux->endereco, aux->saldo);
            aux = aux->seguinte;
        }
        fclose(fp);
        return(true);
    }
    else return(false);
}


/**
 * @brief Lê os dados do ficheiro para a lista
 * 
 * @return Cliente* 
 */

Cliente* lerClientes()
{
    FILE* fp;
    char nome[50];
    int nif;
    char endereco[50];
    float saldo;
    Cliente* inicio = NULL;
    Cliente* ultimo = NULL;
    fp = fopen("clientes.txt","r");
    if (fp!=NULL)
    {
        while (fscanf(fp,"%[^;];%d;%[^;];%f\n", nome, &nif, endereco, &saldo) == 4)
        {
            Cliente* novo = malloc(sizeof(struct _Cliente));
            if (novo != NULL)
            {
                strcpy(novo->nome, nome);
                novo->nif = nif;
                strcpy(novo->endereco, endereco);
                novo->saldo = saldo;
                novo->seguinte = NULL;
                if (inicio == NULL)
                {
                    // se a lista estiver vazia, o novo cliente será o primeiro nó
                    inicio = novo;
                    ultimo = novo;
                }
                else
                {
                    // adiciona o novo cliente após o último nó
                    ultimo->seguinte = novo;
                    ultimo = novo;
                }
            }
        }
        fclose(fp);
    }
    return inicio;
}


/**
 * @brief lista na consola o conteúdo da lista ligada
 * 
 * @param inicio 
 */

void listarClientes(Cliente *inicio) {
    while (inicio != NULL) {
        printf("%s %d %s %.2f\n", inicio->nome, inicio->nif, inicio->endereco, inicio->saldo);
        inicio = inicio->seguinte;
    }
}


/**
 * @brief Edita um cliente pelo nif
 * 
 * @param inicio 
 * @param nome 
 * @param nif 
 * @param endereco 
 * @param saldo 
 * @return Cliente* 
 */

Cliente* editarCliente(Cliente* inicio, char nome[], int nif, char endereco[], float saldo) {
    Cliente* atual = inicio;
    
    // Procurar o cliente com o nome e NIF fornecidos
    while (atual != NULL && atual->nif != nif) {
        atual = atual->seguinte;
    }
    
    // Se o cliente não foi encontrado, retornar o início da lista original
    if (atual == NULL) {
        return inicio;
    }
    
    // Atualizar os dados do cliente
    strcpy(atual->nome, nome);
    strcpy(atual->endereco, endereco);
    atual->saldo = saldo;
    
    // Retornar o início da lista atualizada
    return inicio;
}


/**
 * @brief Remove um cliente pelo nif
 * 
 * @param inicio 
 * @param nif 
 * @return Cliente* 
 */

Cliente* removerCliente(Cliente* inicio, int nif) 
{
    Cliente *anterior=inicio, *atual=inicio, *aux;

    if (atual==NULL) return(NULL);
    else if (atual->nif == nif) // remoção do 1º registo
    {
        aux = atual->seguinte;
        free(atual);
        return(aux);
    }
    else
    {
        while ((atual!=NULL)&&(atual->nif!=nif)) {
            anterior = atual;
            atual = atual->seguinte;
            }
        if (atual==NULL) return(inicio);
        else
        {
            anterior->seguinte = atual->seguinte;
            free(atual);
            return(inicio);
        }
    }
}

/**
 * @brief Menu Clientes
 *
 */

void menuClientes()
{

    int opcao;
   
    Cliente* clientes = NULL; // Lista ligada vazia 

    clientes = lerClientes();

    int nif = 11;

    bool x;

    system("cls");

    do
    {
        printf("#####################################################\n");
        printf("#                                                   #\n");
        printf("#                       MENU                        #\n");
        printf("#                                                   #\n");
        printf("#####################################################\n");
        printf("#                                                   #\n");
        printf("#\t 1 - Adicionar Cliente                      #\n");
        printf("#                                                   #\n");
        printf("#\t 2 - Remover Cliente                        #\n");
        printf("#                                                   #\n");
        printf("#\t 3 - Guardar Cliente                        #\n");
        printf("#                                                   #\n");
        printf("#\t 4 - Editar Cliente                         #\n");
        printf("#                                                   #\n");
        printf("#\t 5 - Ver todos os Clientes                  #\n");
        printf("#                                                   #\n");
        printf("#\t 0 - SAIR                                   #\n");
        printf("#                                                   #\n");
        printf("#####################################################\n");
        printf(">\t Digite a sua opcao -> ");
        scanf("%d", &opcao);
        system("@cls||clear");

        switch (opcao)
        {

        case 1:

            clientes = inserirCliente(clientes,"teste", 4, "ep3", 13.23);
            // if(x == true){
            //     printf("Cliente inserido com sucesso!");
            // } else {
            //     printf("Erro ao inserir cliente!");
            // }
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;

        case 2:
            clientes = removerCliente(clientes, nif);
           /* if(x == true){
                printf("Cliente removido!");
            } else {
                printf("Erro ao remover cliente!");
            } */
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 3:
            x = guardarClientes(clientes);
            if(x == true){
                printf("Cliente guardado com sucesso!");
            } else {
                printf("Erro ao guardar cliente!");
            }
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 4:
            clientes = editarCliente(clientes,"eodspdsapdaskdapadkk",4,"Edi1111tado",11.99);
               
            if(x == true){
                printf("Cliente editado com sucesso!");
            } else {
                printf("Erro ao editar cliente!");
            }

            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 5:
            listarClientes(clientes);

            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 0:

            break;
        default:
            scanf("\n%d", &opcao);
            getchar();
            system("@cls||clear");
            break;
        }
    } while (opcao != 0);
}