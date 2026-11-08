//
// Created by vando on 07/11/2026.
//

#include "menu_emprestimos.h"
#include "../utils/entrada.h"
#include <stdio.h>

void menuEmprestimos() {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n");
        printf("\tGerenciar Emprestimos\n");
        printf("\n");

        printf("\n1 - Cadastrar emprestimo\n");
        printf("2 - Consultar emprestimo\n");
        printf("3 - Registrar devolucao\n");
        printf("4 - Listar emprestimo\n");
        printf("0 - Voltar\n");

        if (!lerInt("\nEscolha uma opcao: ", &opcao)) {
            printf("\nEntrada invalida\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {
        case 1:
            printf("\nCadastro de emprestimo");
            break;

        case 2:
            printf("\nConsulta de emprestimo");
            break;

        case 3:
            printf("\nRegistrar devolucao");
            break;

        case 4:
            printf("\nListar emprestimos");
            break;

        case 0:
            printf("\nVoltando ao menu principal\n");
            break;

        default:
            printf("\nOpcao invalida");
        }
    }
}
