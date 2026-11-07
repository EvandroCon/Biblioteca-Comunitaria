//
// Created by vando on 07/11/2026.
//
#include <stdio.h>
#include "menu_livros.h"

#include <string.h>

#include "../models/livro.h"

void menuLivros() {
    int opcao = -1;

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
            menuCadastrarLivro();
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

void menuCadastrarLivro() {

    Livro livro;

    printf("\n--- CADASTRAR LIVRO ---\n");

    printf("Codigo: ");
    scanf("%d", &livro.id);

    getchar();

    if (livro.id <= 0) {
        printf("\nErro: o codigo deve ser positivo!\n");
        return;
    }

    printf("Titulo: ");
    fgets(livro.titulo, 100, stdin);

    livro.titulo[strcspn(livro.titulo, "\n")] = '\0';

    if (strlen(livro.titulo) == 0) {
        printf("\nErro: o titulo nao pode ficar vazio!\n");
        return;
    }

    printf("Autor: ");
    fgets(livro.autor, 100, stdin);

    livro.autor[strcspn(livro.autor, "\n")] = '\0';

    if (strlen(livro.autor) == 0) {
        printf("\nErro: o autor nao pode ficar vazio!\n");
        return;
    }

    printf("Quantidade: ");
    scanf("%d", &livro.quantidade);

    if (livro.quantidade < 0) {
        printf("\nErro: a quantidade nao pode ser negativa!\n");
        return;
    }

    if (cadastrarLivro(livro)) {
        printf("\nLivro cadastrado com sucesso!\n");
    } else {
        printf("\nNao foi possivel cadastrar, livro já cadastrado.\n");
    }
}