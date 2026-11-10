#include <stdio.h>
#include "livro.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// No da lista encadeada: guarda um livro completo e aponta para o proximo
typedef struct NoLivro {
    Livro livro;
    struct NoLivro *proximo;   // NULL no ultimo no
} NoLivro;

// Ponteiro para o primeiro no: e por ele que a lista e percorrida.
// Se for NULL, nao ha livros cadastrados.
static NoLivro *inicioLivros = NULL;

// Contador de livros; aumenta no cadastro e diminui na remocao.
static int quantidadeLivros = 0;

//Essa função coloca a lista de livros no estado inicial: vazia.
void inicializarLivros(void) {
    inicioLivros = NULL;
    quantidadeLivros = 0;
}

//Compara dois titulos sem diferenciar maiusculas de minusculas
//Devolve negativo se a<b, 0 se iguais, positivo se a > b
static int compararTitulos(const char *a, const char *b) {
    int i =0;
    while (a[i] != '\0' && b[i] != '\0') {
        int ca = tolower((unsigned char) a[i]);
        int cb = tolower((unsigned char) b[i]);

        if (ca != cb) {    //As letras sao diferentes?
            return ca - cb; //A subtracao diz quem vem primeiro
        }
        i++;
    }
    return tolower((unsigned char) a[i]) - tolower((unsigned char) b[i]);
}

//A funcao recebe uma copia do livro ja montado pelo menu.
//Ela devolve 1 se cadastrou e 0 se recusou.
int cadastrarLivro(Livro livro) {

    // A quantidade nao pode ser negativa
    if (livro.quantidade < 0) {
        return 0;
    }

    // O codigo deve ser valido
    if (livro.id <= 0) {
        return 0;
    }

    // Percorre a lista verificando duplicidade e guardando o ultimo no
    NoLivro *atual = inicioLivros; //no que esta sendo examinado, começando no primeiro
    NoLivro *anteriorPosicao = NULL; //no depois do qual o novo livro sera inserido
    int posicaoEncontrada = 0;

    //percorre a lista inteira
    while (atual != NULL) {

        // Codigo ja cadastrado
        if (atual->livro.id == livro.id) {
            return 0;
        }

        // Mesmo titulo e autor ja cadastrados
        // (strcmp diferencia maiusculas de minusculas)
        if (strcmp(atual->livro.titulo, livro.titulo) == 0 &&
            strcmp(atual->livro.autor, livro.autor) == 0) {
            return 0;
            }

        //Se a posicao alfabetica chegou, enquanto nao achou o lugarm compara o titulo novo com o do no
        //Enquanto o novo titulo vier depois do atual, a posicao ainda nao chegou
        if (!posicaoEncontrada) {
            if (compararTitulos(livro.titulo, atual->livro.titulo) < 0) {
                posicaoEncontrada = 1;
            } else {
                anteriorPosicao = atual;
            }
        }

        atual = atual->proximo;
    }

    // Cria o novo no
    NoLivro *novo = malloc(sizeof(NoLivro));
    if (novo == NULL) {
        return 0;
    }
    novo->livro = livro;

    // Insere mantendo a ordem alfabetica por titulo
    if (anteriorPosicao == NULL) {
        novo->proximo = inicioLivros; //Vai para o inicio
        inicioLivros = novo;
    } else {
        novo->proximo = anteriorPosicao->proximo;
        anteriorPosicao->proximo = novo;
    }

    quantidadeLivros++;
    return 1;
}

// Devolve um ponteiro para o livro, ou NULL se nao existir
Livro *buscarLivroPorId(int id) {
    NoLivro *atual = inicioLivros;

    while (atual != NULL) {
        if (atual->livro.id == id) {
            return &atual->livro;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// Remove o livro com o codigo informado. Devolve 1 se removeu, 0 se nao achou
int removerLivro(int id) {
    NoLivro *atual = inicioLivros;
    NoLivro *anterior = NULL;

    while (atual != NULL) {

        if (atual->livro.id == id) {

            // Religa a lista, pulando o no removido
            if (anterior == NULL) {
                inicioLivros = atual->proximo;   // removendo o primeiro no
            } else {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            quantidadeLivros--;
            return 1;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    return 0;
}

// Imprime codigo e titulo de todos os livros, na ordem de cadastro.
// Devolve quantos foram listados
int listarLivros(void) {
    NoLivro *atual = inicioLivros;

    while (atual != NULL) {
        printf("%d - %s\n", atual->livro.id, atual->livro.titulo);
        atual = atual->proximo;
    }

    return quantidadeLivros;
}

// Libera a memoria de todos os nos
void liberarLivros(void) {
    NoLivro *atual = inicioLivros;

    while (atual != NULL) {
        NoLivro *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicioLivros = NULL;
    quantidadeLivros = 0;
}