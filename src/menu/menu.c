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
                menuLivros();
                break;

            case 2:
                menuUsuarios();
                break;

            case 3:
                menuEmprestimos();
                break;

            case 4:
                menuHistorico();
                break;

            case 0:
                printf("\nSair");
                break;

            default:
                printf("\nOpcao invalida");
        }
    }
}

void menuLivros() {
    int opcao;

    while (opcao != 0) {
        printf("\n");
        printf("\tGerenciar Livros\n");
        printf("\n");

        printf("\n1 - Cadastrar livro\n");
        printf("2 - Buscar livro\n");
        printf("3 - Remover livro\n");
        printf("4 - Listar livros\n");
        printf("0 - Voltar\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nCadastro de livro");
                break;

            case 2:
                printf("\nBusca de livro");
                break;

            case 3:
                printf("\nRemocao de livro");
                break;

            case 4:
                printf("\nListagem de livro");
                break;

            case 0:
                printf("\nVoltando ao menu pricipal\n");
                break;

            default:
                printf("\nOpcao invalida");
        }
    }
}

void menuUsuarios() {
    int opcao;

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

void menuEmprestimos() {
    int opcao;

    while (opcao != 0) {
        printf("\n");
        printf("\tGerenciar Emprestimos\n");
        printf("\n");

        printf("\n1 - Cadastrar emprestimo\n");
        printf("2 - Consultar emprestimo\n");
        printf("3 - Registrar devolucao\n");
        printf("4 - Listar emprestimo\n");
        printf("0 - Voltar\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

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
                printf("\nVoltando ao menu pricipal\n");
                break;

            default:
                printf("\nOpcao invalida");
        }
    }
}

void menuHistorico() {
    int opcao;

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