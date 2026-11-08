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
            printf("\nRemocao de livro");
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

void menuBuscarLivro() {

    int tipo;

    printf("\n--- BUSCAR LIVRO ---\n");
    printf("1 - Por codigo\n");
    printf("2 - Por titulo\n");

    if (!lerInt("Escolha: ", &tipo)) {
        printf("\nEntrada invalida\n");
        return;
    }

    if (tipo == 1) {
        int id;
        if (!lerInt("Codigo: ", &id) || id <= 0) {
            printf("\nErro: o codigo deve ser um numero positivo!\n");
            return;
        }

        Livro *livro = buscarLivroPorId(id);
        if (livro == NULL) {
            printf("\nLivro nao encontrado.\n");
            return;
        }
        printf("\nCodigo: %d | Titulo: %s | Autor: %s | Ano: %d | Quantidade: %d\n",
               livro->id, livro->titulo, livro->autor, livro->ano, livro->quantidade);

    } else if (tipo == 2) {
        char titulo[100];
        lerString("Titulo (ou parte dele): ", titulo, sizeof titulo);

        if (strlen(titulo) == 0) {
            printf("\nErro: digite pelo menos uma parte do titulo!\n");
            return;
        }

        printf("\n");
        if (buscarLivrosPorTitulo(titulo) == 0) {
            printf("Nenhum livro encontrado.\n");
        }

    } else {
        printf("\nOpcao invalida\n");
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