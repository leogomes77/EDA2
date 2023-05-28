/**
 * @file Aluger.c
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
#include "Aluger.h"

/**
 * @brief Guardar os Alugeres do array no ficheiro Alugeres.bin
 * 
 * @param Alugeres 
 * @param numAlugeres 
 * @return true 
 * @return false 
 */

bool guardarAlugeres(Aluger *Alugeres, int *numAlugeres)
{
    FILE *ficheiroAlugeres = fopen("Alugeres.bin", "wb");

    fwrite(numAlugeres, sizeof(int), 1, ficheiroAlugeres);

    for (int i = 0; i < *numAlugeres; i++)
    {
        fwrite(&Alugeres[i], sizeof(Aluger), 1, ficheiroAlugeres); 
    }

    fclose(ficheiroAlugeres); 
    return true;
}



/**
 * @brief Inserir um Aluger
 * 
 * @param Alugeres 
 * @param numAlugeres 
 * @return true 
 * @return false 
 */

bool inserirAluger(Aluger *Alugeres, int *numAlugeres)
{

    if(*numAlugeres < 0 && *numAlugeres > MAX_Alugeres ){
        return false;
    }

    Aluger *novoAluger = (Aluger *)malloc(sizeof(Aluger));

   
    strcpy(novoAluger->nifCliente, "25");
    novoAluger->idMeio = 25;
    strcpy(novoAluger->dataInicio, "25/03/2033");
    strcpy(novoAluger->dataFim, "25/03/2033");
    novoAluger->custo = 65;

   
    Alugeres[*numAlugeres] = *novoAluger;

    *numAlugeres += 1; 

    return true;
}


/**
 * @brief Listar todos os Alugeres do ficheiro Aluger.txt
 * 
 */

bool listarAlugeres()
{
    FILE *ficheiroAlugeres = fopen("Alugeres.bin", "rb"); 
   

    int numAlugeres;
    fread(&numAlugeres, sizeof(int), 1, ficheiroAlugeres);

    Aluger Aluger;

    for (int i = 0; i < numAlugeres; i++)
    {
        fread(&Aluger, sizeof(Aluger), 1, ficheiroAlugeres); 

        printf("\nID Veiculo: %d\n", Aluger.idMeio);
        printf("NIF Cliente: %s\n", Aluger.nifCliente);
        printf("Data Inicio: %s\n", Aluger.dataInicio);
        printf("Data Inicio: %s\n", Aluger.dataFim);
        printf("Custo: %f\n", Aluger.custo);
    
    }

    fclose(ficheiroAlugeres); //fecha o ficheiro

    return true;
}

/**
 * @brief Carregar todos os Alugeres do ficheiro Alugeres.txt
 * 
 * @param Alugeres 
 * @param numAlugeres 
 * @return true 
 * @return false 
 */

bool carregarAlugeres(Aluger *Alugeres, int *numAlugeres)
{
    FILE *ficheiroAlugeres = fopen("Alugeres.bin", "rb");

    fread(numAlugeres, sizeof(int), 1, ficheiroAlugeres); 

    for (int i = 0; i < *numAlugeres; i++)
    {
        fread(&Alugeres[i], sizeof(Aluger), 1, ficheiroAlugeres); 
    }

    fclose(ficheiroAlugeres);

    return true;
}

/**
 * @brief Editar Aluger
 * 
 * @param Alugeres 
 * @param numAlugeres 
 * @param nif 
 * @return true 
 * @return false 
 */

void menuAluger()
{

    int opcao;
    int numAlugeres = 0;
    Aluger *Alugeres = (Aluger *)malloc(sizeof(Aluger) * MAX_Alugeres);

    carregarAlugeres(Alugeres, &numAlugeres);

    system("cls");

    do
    {
        printf("#####################################################\n");
        printf("#                                                   #\n");
        printf("#                       MENU                        #\n");
        printf("#                                                   #\n");
        printf("#####################################################\n");
        printf("#                                                   #\n");
        printf("#\t 1 - Adicionar Aluger                       #\n");
        printf("#                                                   #\n");
        printf("#\t 2 - Guardar Aluger                         #\n");
        printf("#                                                   #\n");
        printf("#\t 3 - Ver todos os Alugeres                  #\n");
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
        
            inserirAluger(Alugeres, &numAlugeres);
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;

        case 2:
            guardarAlugeres(Alugeres, &numAlugeres);
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 3:
            listarAlugeres();
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