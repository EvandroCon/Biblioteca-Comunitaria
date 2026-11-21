//
// Created by vando on 21/11/2026.
//

#include "menu_fila.h"
#include "../utils/entrada.h"
#include <stdio.h>

void menuFilaEspera()
{
    int opcao = -1;
    while (opcao != 0)
    {
        printf("\n");
        printf("\tFila de espera\n");
        printf("\n");

        printf("\n1 - Entrar na fila\n");
        printf("2 - Listar fila\n");
        printf("3 - Cancelar pedido\n");
        printf("0 - Voltar\n");

        if (!lerInt("\nEscolha uma opcao: ", &opcao)) {
            printf("\nEntrada invalida\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {
        case 1:
            printf("\nEntrar na fila");
            break;

        case 2:
            printf("\nListar fila");
            break;

        case 3:
            printf("\nCancelar pedido\n");
            break;

        case 0:
            printf("\nVoltando ao menu principal\n");
            break;
        default:
            printf("\nOpcao invalida");
        }
    }
}