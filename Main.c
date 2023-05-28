/**
 * @file Main.c
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
#include "Meio_Mobilidade.h"
#include "Gestor.h"
#include "Cliente.h"
#include "Aluger.h"
#include "Grafo.h"

void Menu()
{

    int opcao;

    system("cls");

    do
    {
        printf("#####################################################\n");
        printf("#                                                   #\n");
        printf("#                       MENU                        #\n");
        printf("#                                                   #\n");
        printf("#####################################################\n");
        printf("#                                                   #\n");
        printf("#\t 1 - Clientes                               #\n");
        printf("#                                                   #\n");
        printf("#\t 2 - Gestores                               #\n");
        printf("#                                                   #\n");
        printf("#\t 3 - Meios Mobilidade                       #\n");
        printf("#                                                   #\n");
        printf("#\t 4 - Aluger                                 #\n");
        printf("#                                                   #\n");
        printf("#\t 5 - Grafo                                 #\n");
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
            menuClientes();
            printf("\nPressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;

        case 2:
            menuGestores();
            printf("Pressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 3:
            MenuMobilidade();
            printf("Pressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 4:
            menuAluger();
            printf("Pressione uma tecla para voltar ao menu principal!");
            system("pause");
            system("@cls||clear");
            break;
        case 5:
            menuGrafo();
            printf("Pressione uma tecla para voltar ao menu principal!");
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

int main()
{

    Menu();

    return 0;
}
