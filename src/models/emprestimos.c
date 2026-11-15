#include <stdio.h>
#include "emprestimos.h"

typedef struct NoEmprestimo {
    Emprestimo emprestimo;
    int altura;
    struct NoEmprestimo *esquerda;
    struct NoEmprestimo *direita;
} NoEmprestimo;

static NoEmprestimo *raizEmprestimos = NULL;

void inicializarEmprestimos(void) {
    raizEmprestimos = NULL;
}

static int altura(const NoEmprestimo *no) {
    if (no == NULL) {
        return 0;
    }

    return no->altura;
}

static int maior(int a, int b) {
    return a > b ? a : b;
}

static void atualizarAltura(NoEmprestimo *no) {
    no->altura = 1 + maior(
        altura(no->esquerda),
        altura(no->direita)
    );
}

static int fatorBalanceamento(const NoEmprestimo *no) {
    if (no == NULL) {
        return 0;
    }

    return altura(no->esquerda) - altura(no->direita);
}

static NoEmprestimo *rotacionarDireita(NoEmprestimo *raiz) {
    NoEmprestimo *novaRaiz = raiz->esquerda;
    NoEmprestimo *subarvore = novaRaiz->direita;

    novaRaiz->direita = raiz;
    raiz->esquerda = subarvore;

    atualizarAltura(raiz);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}

static NoEmprestimo *rotacionarEsquerda(NoEmprestimo *raiz) {
    NoEmprestimo *novaRaiz = raiz->direita;
    NoEmprestimo *subarvore = novaRaiz->esquerda;

    novaRaiz->esquerda = raiz;
    raiz->direita = subarvore;

    atualizarAltura(raiz);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}