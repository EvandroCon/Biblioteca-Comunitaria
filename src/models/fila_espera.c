//
// Created by vando on 20/11/2026.
//
#include <stdio.h>
#include "fila_espera.h"

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