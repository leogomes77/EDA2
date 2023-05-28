/**
 * @file Meio_Mobilidade.c
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
#include "Meio_Mobilidade.h"

/**
 * @brief Guardar Meios de mobilidade no ficheiro meiosMobilidade.bin
 *
 * @param meioMobilidade
 * @param numMeiosMobilidade
 * @return true
 * @return false
 */
bool guardarMeiosMobilidade(MeioMobilidade *meioMobilidade, int *numMeiosMobilidade)
{
    FILE *ficheiroMeios = fopen("meiosMobilidade.bin", "wb");

    fwrite(numMeiosMobilidade, sizeof(int), 1, ficheiroMeios);

    for (int i = 0; i < *numMeiosMobilidade; i++)
    {
        fwrite(&meioMobilidade[i], sizeof(MeioMobilidade), 1, ficheiroMeios);
    }

    fclose(ficheiroMeios);

    return true;
}

/**
 * @brief Verifica se existe um meio com aquele id
 *
 * @param meioMobilidade
 * @param id
 * @param numMeios
 * @return true
 * @return false
 */

bool existeMeio(MeioMobilidade *meioMobilidade, int id, int *numMeios)
{
    for (int i = 0; i < *numMeios; i++)
    {
        if (meioMobilidade[i].id == id)
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief Inserir um meio de mobilidade
 *
 * @param meioMobilidade
 * @param numMeiosMobilidade
 * @return true
 * @return false
 */

bool inserirMeioMobilidade(MeioMobilidade *meioMobilidade, int *numMeiosMobilidade)
{

    if (*numMeiosMobilidade < 0 && *numMeiosMobilidade > MAX_MEIOS)
    {
        return false;
    }

    MeioMobilidade *novoMeio = (MeioMobilidade *)malloc(sizeof(MeioMobilidade));

    novoMeio->id = 2;
    strcpy(novoMeio->tipo, "BUS");
    novoMeio->cargaBateria = 90;
    novoMeio->custo = 34.23;
    strcpy(novoMeio->localizacao, "BRAGA");

    if (existeMeio(meioMobilidade, novoMeio->id, numMeiosMobilidade) == true)
    {
        return false;
    }

    meioMobilidade[*numMeiosMobilidade] = *novoMeio;

    *numMeiosMobilidade += 1;


    return true;
}

/**
 * @brief  Listar todos os Meios de Mobilidade
 *
 */

void listarMeiosMobilidade()
{
    FILE *ficheiroMeios = fopen("meiosMobilidade.bin", "rb"); // abre o arquivo em modo de leitura binária
    if (ficheiroMeios == NULL)
    {
        printf("Erro ao abrir o arquivo Gestores.bin.\n");
        return;
    }

    int numMeios;
    fread(&numMeios, sizeof(int), 1, ficheiroMeios); // lê o número de Gestores do arquivo

    MeioMobilidade meioMobilidade;

    for (int i = 0; i < numMeios; i++)
    {
        fread(&meioMobilidade, sizeof(MeioMobilidade), 1, ficheiroMeios); // lê cada Gestor do arquivo

        printf("\nID: %d\n", meioMobilidade.id);
        printf("Tipo: %s\n", meioMobilidade.tipo);
        printf("Bateria: %f\n", meioMobilidade.cargaBateria);
        printf("Custo: %f\n", meioMobilidade.custo);
        printf("Localizacao: %s\n", meioMobilidade.localizacao);
    }

    fclose(ficheiroMeios);
}

/**
 * @brief Carregar os Meios de Mobilidade para o meioMobilidade
 *
 * @param meioMobilidade
 * @param numMeiosMobilidade
 * @return true
 * @return false
 */

bool carregarMeiosMobilidade(MeioMobilidade *meioMobilidade, int *numMeiosMobilidade)
{
    FILE *ficheiroMeios = fopen("meiosMobilidade.bin", "rb");
    if (ficheiroMeios == NULL)
    {
        return false;
    }

    fread(numMeiosMobilidade, sizeof(int), 1, ficheiroMeios);

    for (int i = 0; i < *numMeiosMobilidade; i++)
    {
        fread(&meioMobilidade[i], sizeof(MeioMobilidade), 1, ficheiroMeios);
    }

    fclose(ficheiroMeios);

    return true;
}

/**
 * @brief Editar um Meio Mobilidade
 *
 * @param meioMobilidade
 * @param numMeiosMobilidade
 * @param id
 * @return true
 * @return false
 */

bool editarMeioMobilidade(MeioMobilidade *meioMobilidade, int *numMeiosMobilidade, int id)
{

    for (int i = 0; i < *numMeiosMobilidade; i++)
    {
        if (meioMobilidade[i].id == id)
        {
            meioMobilidade[i].id = 55;
            strcpy(meioMobilidade[i].tipo, "teste");
            meioMobilidade[i].cargaBateria = 55.32;
            meioMobilidade[i].custo = 100.32;
            strcpy(meioMobilidade[i].localizacao, "BR32");

            return true;
        }
    }

    return false;
}

/**
 * @brief Remover um Meio de Mobilidade
 *
 * @param meioMobilidade
 * @param numMeiosMobilidade
 * @param id
 * @return true
 * @return false
 */

bool removerMeioMobilidade(MeioMobilidade *meioMobilidade, int *numMeiosMobilidade, int id)
{

    for (int i = 0; i < *numMeiosMobilidade; i++)
    {
        if (meioMobilidade[i].id == id)
        {
            int j;
            for (j = i; j < *numMeiosMobilidade - 1; j++)
            {

                meioMobilidade[j] = meioMobilidade[j + 1];
            }
            //free(&meioMobilidade[*numMeiosMobilidade - 1]);
            *numMeiosMobilidade -= 1;

            return true;
        }
    }

    return false;
}

/**
 * @brief Listar por ordem decrescente de Autonomia
 *
 * @param meios
 * @param numMeios
 */

void listarPorAutonomia(MeioMobilidade *meios, int *numMeios)
{
    int i, j;
    MeioMobilidade *meiosOrdenados = malloc(*numMeios * sizeof(MeioMobilidade));
    MeioMobilidade temp;
    for (i = 0; i < *numMeios; i++)
    {
        meiosOrdenados[i] = meios[i];
    }
    for (i = 0; i < *numMeios - 1; i++)
    {
        for (j = 0; j < *numMeios - i - 1; j++)
        {
            if (meiosOrdenados[j].cargaBateria < meiosOrdenados[j + 1].cargaBateria)
            {
                temp = meiosOrdenados[j];
                meiosOrdenados[j] = meiosOrdenados[j + 1];
                meiosOrdenados[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < *numMeios; i++)
    {
        printf("ID: %d, Tipo: %s, Carga de Bateria: %.2f, Custo: %.2f, Localizacao: %s\n",
               meiosOrdenados[i].id, meiosOrdenados[i].tipo, meiosOrdenados[i].cargaBateria,
               meiosOrdenados[i].custo, meiosOrdenados[i].localizacao);
    }

    free(meiosOrdenados);
}

/**
 * @brief Listar por uma determina Localização
 *
 * @param meios
 * @param numMeios
 * @param localizacao
 */
void listarPorLocalizacao(MeioMobilidade *meios, int *numMeios, char *localizacao)
{
    int i, j;
    MeioMobilidade *meiosLoc = malloc(*numMeios * sizeof(MeioMobilidade));
    MeioMobilidade temp;
    for (i = 0; i < *numMeios; i++)
    {
        meiosLoc[i] = meios[i];
    }
    for (i = 0; i < *numMeios - 1; i++)
    {
        for (j = 0; j < *numMeios - i - 1; j++)
        {
            if (meiosLoc[j].cargaBateria < meiosLoc[j + 1].cargaBateria)
            {
                temp = meiosLoc[j];
                meiosLoc[j] = meiosLoc[j + 1];
                meiosLoc[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < *numMeios; i++)
    {
        if (strcmp(meiosLoc[i].localizacao, localizacao) == 0)
        {
            printf("ID: %d, Tipo: %s, Carga de Bateria: %.2f, Custo: %.2f, Localizacao: %s\n",
                   meiosLoc[i].id, meiosLoc[i].tipo, meiosLoc[i].cargaBateria,
                   meiosLoc[i].custo, meiosLoc[i].localizacao);
        }
    }
    free(meiosLoc);
}

/**
 * @brief Menu Meios de Mobilidade
 *
 */

void MenuMobilidade()
{

    int opcao;
    int numMeios = 0;
    MeioMobilidade *meioMobilidade = (MeioMobilidade *)malloc(sizeof(MeioMobilidade) * MAX_MEIOS);

    carregarMeiosMobilidade(meioMobilidade, &numMeios);

    int id = 2;

    char localizacao[] = "BRAGA";

    system("cls");

    do
    {
        printf("#####################################################\n");
        printf("#                                                   #\n");
        printf("#                       MENU                        #\n");
        printf("#                                                   #\n");
        printf("#####################################################\n");
        printf("#                                                   #\n");
        printf("#\t 1 - Adicionar Meio Mobilidade              #\n");
        printf("#                                                   #\n");
        printf("#\t 2 - Remover Meio Mobilidade                #\n");
        printf("#                                                   #\n");
        printf("#\t 3 - Guardar Meio Mobilidade                #\n");
        printf("#                                                   #\n");
        printf("#\t 4 - Editar Meio Mobilidade                 #\n");
        printf("#                                                   #\n");
        printf("#\t 5 - Ver todos os Meios Mobilidades         #\n");
        printf("#                                                   #\n");
        printf("#\t 6 - Listar Meios Mobilidade por Bateria    #\n");
        printf("#                                                   #\n");
        printf("#\t 7 - Listar por Localizacao                 #\n");
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

            inserirMeioMobilidade(meioMobilidade, &numMeios);
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;

        case 2:
            removerMeioMobilidade(meioMobilidade, &numMeios, id);
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 3:
            guardarMeiosMobilidade(meioMobilidade, &numMeios);
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 4:
            editarMeioMobilidade(meioMobilidade, &numMeios, id);

            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 5:
            listarMeiosMobilidade();
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 6:
            listarPorAutonomia(meioMobilidade, &numMeios);
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 7:
            listarPorLocalizacao(meioMobilidade, &numMeios, localizacao);
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
