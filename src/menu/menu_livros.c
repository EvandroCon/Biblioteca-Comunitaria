//
// Created by vando on 07/11/2026.
//
#include <stdio.h>
#include "menu_livros.h"
#include "../utils/entrada.h"
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

        if (!lerInt("\nEscolha uma opcao: ", &opcao)) {
            printf("\nEntrada invalida\n");
            opcao = -1;
            continue;
        }

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
            printf("\nVoltando ao menu principal\n");
            break;

        default:
            printf("\nOpcao invalida");
        }
    }
}

void menuCadastrarLivro() {

    //cria uma variavel livro do tipo Livro
    Livro livro;

    printf("\n--- CADASTRAR LIVRO ---\n");

    printf("Codigo: ");
    scanf("%d", &livro.id);

    //consume o \n que fica no buffer depois que o usuario digita o código e pressiona Enter
    getchar();

    //validacao do codigo
    if (livro.id <= 0) {
        printf("\nErro: o codigo deve ser positivo!\n");
        return;
    }

    printf("Titulo: ");
    //fgets() permite ler textos com espaços.
    fgets(livro.titulo, 100, stdin);

    //remove o Enter que fica armazenado no final do texto, substitui por \0
    livro.titulo[strcspn(livro.titulo, "\n")] = '\0';

    //calcula a quantidade de caracteres existentes no texto, sem contar o \0
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

    //validacao da quantidade
    if (livro.quantidade < 0) {
        printf("\nErro: a quantidade nao pode ser negativa!\n");
        return;
    }

    //tenta fazer o cadastro
    if (cadastrarLivro(livro)) {
        printf("\nLivro cadastrado com sucesso!\n");
    } else {
        printf("\nNao foi possivel cadastrar, livro já cadastrado.\n");
    }
}