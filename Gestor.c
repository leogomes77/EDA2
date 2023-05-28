/**
 * @file Gestor.c
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
#include "Gestor.h"

/**
 * @brief Guardar os Gestores do array no ficheiro Gestores.bin
 *
 * @param Gestores
 * @param numGestores
 * @return true
 * @return false
 */

bool guardarGestores(Gestor *Gestores, int *numGestores)
{
    FILE *ficheiroGestores = fopen("Gestores.bin", "wb");

    fwrite(numGestores, sizeof(int), 1, ficheiroGestores);

    for (int i = 0; i < *numGestores; i++)
    {
        fwrite(&Gestores[i], sizeof(Gestor), 1, ficheiroGestores);
    }

    fclose(ficheiroGestores);

    return true;
}

/**
 * @brief Verifica se já existe um Gestor com aquele email
 *
 * @param gestores
 * @param email
 * @param numGestores
 * @return true
 * @return false
 */

bool existeGestor(Gestor *gestores, char *email, int *numGestores)
{
    for (int i = 0; i < *numGestores; i++)
    {
        if (strcmp(gestores[i].email, email) == 0)
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief Inserir um Gestor
 *
 * @param Gestores
 * @param numGestores
 * @return true
 * @return false
 */

bool inserirGestor(Gestor *gestores, int *numGestores)
{

    if (*numGestores < 0 && *numGestores > MAX_Gestores)
    {
        return false;
    }

    Gestor *novoGestor = (Gestor *)malloc(sizeof(Gestor));

    strcpy(novoGestor->nome, "teste");
    strcpy(novoGestor->email, "teste@gmail.com");
    strcpy(novoGestor->senha, "tes23");

    if (existeGestor(gestores, novoGestor->email, numGestores) == true)
    {
        return false;
    }

    gestores[*numGestores] = *novoGestor;

    *numGestores += 1;

    free(novoGestor);

    return true;
}

/**
 * @brief Listar todos os Gestores do ficheiro Gestores.bin
 *
 */

void listarGestores()
{
    FILE *ficheiroGestores = fopen("Gestores.bin", "rb");

    int numGestores;
    fread(&numGestores, sizeof(int), 1, ficheiroGestores);

    Gestor Gestor;

    for (int i = 0; i < numGestores; i++)
    {
        fread(&Gestor, sizeof(Gestor), 1, ficheiroGestores);

        printf("\nNome: %s\n", Gestor.nome);
        printf("Email: %s\n", Gestor.email);
        printf("Senha: %s\n", Gestor.senha);
    }

    fclose(ficheiroGestores);
}

/**
 * @brief Carregar todos os Gestores do ficheiro Gestores.txt
 *
 * @param Gestores
 * @param numGestores
 * @return true
 * @return false
 */

bool carregarGestores(Gestor *Gestores, int *numGestores)
{
    FILE *ficheiroGestores = fopen("Gestores.bin", "rb");

    fread(numGestores, sizeof(int), 1, ficheiroGestores);

    for (int i = 0; i < *numGestores; i++)
    {
        fread(&Gestores[i], sizeof(Gestor), 1, ficheiroGestores);
    }

    fclose(ficheiroGestores);

    return true;
}

/**
 * @brief Editar Gestor
 *
 * @param Gestores
 * @param numGestores
 * @param nif
 * @return true
 * @return false
 */

bool editarGestor(Gestor *Gestores, int *numGestores, char *email)
{

    // Procura o Gestor com o NIF informado
    for (int i = 0; i < *numGestores; i++)
    {
        if (strcmp(Gestores[i].email, email) == 0)
        {
            strcpy(Gestores[i].nome, "alterado");
            strcpy(Gestores[i].email, "alterado@gmail.com");
            strcpy(Gestores[i].senha, "123");

            return true;
        }
    }

    return false;
}

/**
 * @brief Remover Gestor
 *
 * @param Gestores
 * @param numGestores
 * @param nif
 * @return true
 * @return false
 */

bool removerGestor(Gestor *Gestores, int *numGestores, char *email)
{

    for (int i = 0; i < *numGestores; i++)
    {
        if (strcmp(Gestores[i].email, email) == 0)
        {

            int j;
            for (j = i; j < *numGestores - 1; j++)
            {

                Gestores[j] = Gestores[j + 1];
            }
            free(&Gestores[*numGestores - 1]);
            *numGestores -= 1;

            return true;
        }
    }

    return false;
}

/**
 * @brief  Menu Gestores
 *
 */

void menuGestores()
{

    int opcao;
    int numGestores = 0;
    Gestor *Gestores = (Gestor *)malloc(sizeof(Gestor) * MAX_Gestores);

    carregarGestores(Gestores, &numGestores);

    char email[] = "teste@gmail.com";

    system("cls");

    do
    {
        printf("#####################################################\n");
        printf("#                                                   #\n");
        printf("#                       MENU                        #\n");
        printf("#                                                   #\n");
        printf("#####################################################\n");
        printf("#                                                   #\n");
        printf("#\t 1 - Adicionar Gestor                       #\n");
        printf("#                                                   #\n");
        printf("#\t 2 - Remover Gestor                         #\n");
        printf("#                                                   #\n");
        printf("#\t 3 - Guardar Gestor                         #\n");
        printf("#                                                   #\n");
        printf("#\t 4 - Editar Gestor                          #\n");
        printf("#                                                   #\n");
        printf("#\t 5 - Ver todos os Gestores                  #\n");
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

            inserirGestor(Gestores, &numGestores);
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;

        case 2:
            removerGestor(Gestores, &numGestores, email);
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 3:
            guardarGestores(Gestores, &numGestores);
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 4:
            editarGestor(Gestores, &numGestores, email);

            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 5:
            listarGestores();

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