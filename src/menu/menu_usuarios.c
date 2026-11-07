//
// Created by vando on 07/11/2026.
//

#include "menu_usuarios.h"

#include <stdio.h>

void menuUsuarios() {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n");
        printf("\tGerenciar Usuarios\n");
        printf("\n");

        printf("\n1 - Cadastrar usuario\n");
        printf("2 - Buscar usuario\n");
        printf("3 - Remover usuario\n");
        printf("4 - Listar usuario\n");
        printf("0 - Voltar\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("\nCadastro de usuario");
            break;

        case 2:
            printf("\nBusca de usuario");
            break;

        case 3:
            printf("\nRemocao de usuario");
            break;

        case 4:
            printf("\nListagem de usuario");
            break;

        case 0:
            printf("\nVoltando ao menu pricipal\n");
            break;

        default:
            printf("\nOpcao invalida");
        }
    }
}
