#include "emprestimos.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct NoEmprestimo
{
    Emprestimo emprestimo;
    int altura;
    struct NoEmprestimo* esquerda;
    struct NoEmprestimo* direita;
} NoEmprestimo;

static NoEmprestimo* raizEmprestimos = NULL;

void inicializarEmprestimos(void)
{
    raizEmprestimos = NULL;
}

static int altura(const NoEmprestimo* no)
{
    if (no == NULL)
    {
        return 0;
    }

    return no->altura;
}

static int maior(int a, int b)
{
    return a > b ? a : b;
}

static void atualizarAltura(NoEmprestimo* no)
{
    no->altura = 1 + maior(
        altura(no->esquerda),
        altura(no->direita)
    );
}

static int fatorBalanceamento(const NoEmprestimo* no)
{
    if (no == NULL)
    {
        return 0;
    }

    return altura(no->esquerda) - altura(no->direita);
}

static NoEmprestimo* rotacionarDireita(NoEmprestimo* raiz)
{
    NoEmprestimo* novaRaiz = raiz->esquerda;
    NoEmprestimo* subarvore = novaRaiz->direita;

    novaRaiz->direita = raiz;
    raiz->esquerda = subarvore;

    atualizarAltura(raiz);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}

static NoEmprestimo* rotacionarEsquerda(NoEmprestimo* raiz)
{
    NoEmprestimo* novaRaiz = raiz->direita;
    NoEmprestimo* subarvore = novaRaiz->esquerda;

    novaRaiz->esquerda = raiz;
    raiz->direita = subarvore;

    atualizarAltura(raiz);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}

static NoEmprestimo* inserirAVL(NoEmprestimo* no, Emprestimo emprestimo, int* sucesso)
{
    if (no == NULL)
    {
        NoEmprestimo* novo = malloc(sizeof *novo);

        if (novo == NULL)
        {
            *sucesso = 0;
            return NULL;
        }

        novo->emprestimo = emprestimo;
        novo->altura = 1;
        novo->esquerda = NULL;
        novo->direita = NULL;

        *sucesso = 1;
        return novo;
    }

    if (emprestimo.id < no->emprestimo.id)
    {
        NoEmprestimo* filho =
            inserirAVL(no->esquerda, emprestimo, sucesso);

        if (!*sucesso)
        {
            return no;
        }

        no->esquerda = filho;
    }
    else if (emprestimo.id > no->emprestimo.id)
    {
        NoEmprestimo* filho =
            inserirAVL(no->direita, emprestimo, sucesso);

        if (!*sucesso)
        {
            return no;
        }

        no->direita = filho;
    }
    else
    {
        *sucesso = 0;
        return no;
    }

    atualizarAltura(no);

    int fator = fatorBalanceamento(no);

    if (fator > 1 &&
        emprestimo.id < no->esquerda->emprestimo.id)
    {
        return rotacionarDireita(no);
    }

    if (fator < -1 &&
        emprestimo.id > no->direita->emprestimo.id)
    {
        return rotacionarEsquerda(no);
    }

    if (fator > 1 &&
        emprestimo.id > no->esquerda->emprestimo.id)
    {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    if (fator < -1 &&
        emprestimo.id < no->direita->emprestimo.id)
    {
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    return no;
}

int cadastrarEmprestimo(Emprestimo emprestimo)
{
    if (emprestimo.id <= 0 ||
        emprestimo.livro_id <= 0 ||
        emprestimo.usuario_id <= 0 ||
        emprestimo.data_emprestimo[0] == '\0') {
        return 0;
    }

    int sucesso = 0;

    raizEmprestimos =
        inserirAVL(raizEmprestimos, emprestimo, &sucesso);

    return sucesso;
}

Emprestimo *buscarEmprestimo(int id) {
    NoEmprestimo *atual = raizEmprestimos;
    while (atual != NULL) {
        if (id == atual->emprestimo.id) return &atual->emprestimo;
        atual = id < atual->emprestimo.id ? atual->esquerda : atual->direita;
    }
    return NULL;
}

static void listarNos(const NoEmprestimo *atual, int *total)
{
    if (atual == NULL)
    {
        return;
    }

    listarNos(atual->esquerda, total);

    printf("Codigo: %d - Livro: %d - Usuario: %d - ",
           atual->emprestimo.id,
           atual->emprestimo.livro_id,
           atual->emprestimo.usuario_id);

    if (atual->emprestimo.devolvido)
    {
        printf("Devolvido em: %s\n",
               atual->emprestimo.data_devolucao);
    }
    else
    {
        printf("Emprestimo em aberto\n");
    }

    (*total)++;

    listarNos(atual->direita, total);
}

int listarEmprestimos(void)
{
    int total = 0;

    listarNos(raizEmprestimos, &total);

    return total;
}

static void liberarNos(NoEmprestimo* no)
{
    if (no == NULL) return;
    liberarNos(no->esquerda);
    liberarNos(no->direita);
    free(no);
}

void liberarEmprestimos(void)
{
    liberarNos(raizEmprestimos);
    raizEmprestimos = NULL;
}
