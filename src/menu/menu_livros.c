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

    Livro livro;

    printf("\n--- CADASTRAR LIVRO ---\n");

    //Se a leitura falhou ou o código é menor ou igual a zero, então mostre o erro e saia.
    if (!lerInt("Codigo: ", &livro.id) || livro.id <= 0) {
        printf("\nErro: o codigo deve ser um numero positivo!\n");
        return;
    }

    lerString("Titulo: ", livro.titulo, sizeof livro.titulo);
    if (strlen(livro.titulo) == 0) {
        printf("\nErro: o titulo nao pode ficar vazio!\n");
        return;
    }

    lerString("Autor: ", livro.autor, sizeof livro.autor);
    if (strlen(livro.autor) == 0) {
        printf("\nErro: o autor nao pode ficar vazio!\n");
        return;
    }

    if (!lerInt("Ano: ", &livro.ano) || livro.ano <= 0) {
        printf("\nErro: o ano deve ser um numero positivo!\n");
        return;
    }

    if (!lerInt("Quantidade: ", &livro.quantidade) || livro.quantidade < 0) {
        printf("\nErro: a quantidade deve ser um numero nao negativo!\n");
        return;
    }

    if (cadastrarLivro(livro)) {
        printf("\nLivro cadastrado com sucesso!\n");
    } else {
        printf("\nNao foi possivel cadastrar, livro ja cadastrado.\n");
    }
}