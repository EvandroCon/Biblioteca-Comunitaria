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
            menuBuscarLivro();
            break;

        case 3:
            menuRemoverLivro();
            break;

        case 4:
            menuListarLivros();
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

void menuBuscarLivro() {

    int id;

    printf("\n--- BUSCAR LIVRO ---\n");

    if (!lerInt("Codigo: ", &id) || id <= 0) {
        printf("\nErro: o codigo deve ser um numero positivo!\n");
        return;
    }

    Livro *livro = buscarLivroPorId(id);

    if (livro == NULL) {
        printf("\nLivro nao encontrado.\n");
        return;
    }

    printf("\nLivro encontrado:\n");
    printf("Codigo: %d\n", livro->id);
    printf("Titulo: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Ano: %d\n", livro->ano);
    printf("Quantidade: %d\n", livro->quantidade);
}

void menuRemoverLivro() {

    int id;

    printf("\n--- REMOVER LIVRO ---\n");

    if (!lerInt("Codigo: ", &id) || id <= 0) {
        printf("\nErro: o codigo deve ser um numero positivo!\n");
        return;
    }

    if (removerLivro(id)) {
        printf("\nLivro removido com sucesso!\n");
    } else {
        printf("\nLivro nao encontrado.\n");
    }
}

void menuListarLivros() {

    printf("\n--- LISTA DE LIVROS ---\n\n");

    int total = listarLivros();

    if (total == 0) {
        printf("Nenhum livro cadastrado.\n");
    } else {
        printf("\nTotal: %d livro(s)\n", total);
    }
}