//
// Created by vando on 20/11/2026.
//
#include <stdio.h>
#include "fila_espera.h"

#include <stdlib.h>

typedef struct NoFila
{
    SolicitacaoFila solicitacao;
    struct NoFila *proximo;
} NoFila;

static NoFila *inicio = NULL;
static NoFila *fim = NULL;
static int proximoId = 1;

void inicializarFilaEspera(void)
{
    inicio = NULL;
    fim = NULL;
    proximoId = 1;
}

int adicionarFilaEspera(int livro_id, int usuario_id)
{
    if (livro_id <= 0 || usuario_id <= 0)
    {
        return 0;
    }

    for (NoFila *atual = inicio; atual != NULL; atual = atual->proximo)
    {
        if (atual->solicitacao.livro_id == livro_id &&
            atual->solicitacao.usuario_id == usuario_id)
        {
            return 0;
        }
    }

    NoFila *novo = malloc(sizeof *novo);
    if (novo == NULL)
    {
        return 0;
    }

    novo->solicitacao = (SolicitacaoFila){proximoId++, livro_id, usuario_id};
    novo->proximo = NULL;

    if (fim == NULL)
    {
        inicio = novo;
    }
    else
    {
        fim->proximo = novo;
    }

    fim = novo;

    return novo->solicitacao.id;
}

int listarFilaEspera(int livro_id)
{
    int total = 0;
    int posicao = 0;

    for (NoFila *atual = inicio;
         atual != NULL;
         atual = atual->proximo)
    {
        if (livro_id > 0 &&
            atual->solicitacao.livro_id != livro_id)
        {
            continue;
        }

        posicao++;

        printf("Posicao %d - Pedido %d - Livro %d - Usuario %d\n",
               posicao,
               atual->solicitacao.id,
               atual->solicitacao.livro_id,
               atual->solicitacao.usuario_id);

        total++;
    }

    return total;
}

//a função procura um pedido pelo ID, remove o noh correspondente da lista e libera a memoria que ele ocupava
int removerFilaEspera(int id)
{
    if (id <= 0)
    {
        return 0;
    }

    NoFila *atual = inicio;
    NoFila *anterior = NULL;

    while (atual != NULL && atual->solicitacao.id != id)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        return 0;
    }

    if (anterior == NULL)
    {
        inicio = atual->proximo;
    }
    else
    {
        anterior->proximo = atual->proximo;
    }

    if (fim == atual)
    {
        fim = anterior;
    }

    free(atual);

    return 1;
}

void liberarFilaEspera(void)
{
    NoFila *atual = inicio;
    while (atual != NULL)
    {
        NoFila *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicio = fim = NULL;
    proximoId = 1;
}
