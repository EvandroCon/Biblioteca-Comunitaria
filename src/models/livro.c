#include <stdio.h>
#include "livro.h"
#include "libprg/libprg.h"

#define MAX_LIVROS 100

Livro livros[MAX_LIVROS];

int quantidadeLivros = 0;

lista_linear_t *listaLivros;

void inicializarLivros() {
    listaLivros = criar_lista(true);
}

int cadastrarLivro(Livro livro) {

    //Verificando a quantidade, nao pode ser negativa
    if (livro.quantidade < 0) {
        return 0;
    }
    
    //Verificar se o codigo é valido
    if (livro.id <= 0) {
        return 0;
    }

    // Verificar se existe espaço disponível
    if (quantidadeLivros >= MAX_LIVROS) {
        return 0;
    }

    // Verificar se o código já está cadastrado
    for (int i = 0; i < quantidadeLivros; i++) {

        if (livros[i].id == livro.id) {
            return 0;
        }
    }

    // Inserir o código na lista da libprg
    if (!inserir(listaLivros, livro.id)) {
        return 0;
    }

    // Armazenar os dados completos do livro
    livros[quantidadeLivros] = livro;

    quantidadeLivros++;



    return 1;
}