//
// Created by aluno on 05/11/2026.
//
#include <stdio.h>
#include "menu.h"

void menuPrincipal() {
    int opcao;

    while (opcao != 0) {
        printf("\n");
        printf("\tLivraria Comunitaria\n");
        printf("\n");

        printf("\n1 - Gerenciar Livros\n");
        printf("2 - Gerenciar usuarios\n");
        printf("3 - Gerenciar Emprestimos\n");
        printf("4 - Historico de operacoes\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nMenu de livros");
                break;

            case 2:
                printf("\nMenu de usuarios");
                break;

            case 3:
                printf("\nMenu de emprestimos");
                break;

            case 4:
                printf("\nMenu de historico");
                break;

            case 0:
                printf("\nSair");
                break;

            default:
                printf("\nOpcao invalida");
        }
    }
}