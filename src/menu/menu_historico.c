//
// Created by vando on 07/11/2026.
//

#include "menu_historico.h"
#include "../utils/entrada.h"
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

        if (!lerInt("\nEscolha uma opcao: ", &opcao)) {
            printf("\nEntrada invalida\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {
        case 1:
            printf("\nConsulta da ultima operacao");
            break;

        case 2:
            printf("\nListagem do historico");
            break;

        case 0:
            printf("\nVoltando ao menu principal\n");
            break;

        default:
            printf("\nOpcao invalida");
        }
    }
}
