//
// Created by vando on 07/11/2026.
//

#include "menu_historico.h"

#include <stdio.h>

void menuHistorico() {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n");
        printf("\tHistorico de operacoes\n");
        printf("\n");

        printf("\n1 - Consultar ultima operacao\n");
        printf("2 - Lista historico de operacoes\n");
        printf("0 - Voltar\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("\nConsulta da ultima operacao");
            break;

        case 2:
            printf("\nListagem do historico");
            break;

        case 0:
            printf("\nVoltando ao menu pricipal\n");
            break;

        default:
            printf("\nOpcao invalida");
        }
    }
}
