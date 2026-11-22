//
// Created by vando on 21/11/2026.
//

#include "menu_fila_espera.h"
#include "../utils/entrada.h"
#include <stdio.h>
#include "../models/usuario.h"
#include "../models/livro.h"
#include "../models/fila_espera.h"

void menuFilaEspera()
{
    int opcao = -1;
    while (opcao != 0)
    {
        printf("\n");
        printf("\tFila de espera\n");
        printf("\n");

        printf("\n1 - Entrar na fila\n");
        printf("2 - Listar fila\n");
        printf("3 - Cancelar pedido\n");
        printf("0 - Voltar\n");

        if (!lerInt("\nEscolha uma opcao: ", &opcao)) {
            printf("\nEntrada invalida\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {
        case 1:
            menuEntrarFila();
            break;

        case 2:
            printf("\nListar fila\n");
            break;

        case 3:
            printf("\nCancelar pedido\n");
            break;

        case 0:
            printf("\nVoltando ao menu principal\n");
            break;
        default:
            printf("\nOpcao invalida");
        }
    }
}

void menuEntrarFila()
{
    int livroId;
    int usuarioId;
    Usuario usuario;

    if (!lerInt("Codigo do livro: ", &livroId))
    {
        printf("Codigo do livro invalido.\n");
        return;
    }

    Livro *livro = buscarLivroPorId(livroId);

    if (livro == NULL)
    {
        printf("Livro nao encontrado.\n");
        return;
    }

    if (livro->quantidade > 0)
    {
        printf("Ha exemplares disponiveis. Nao e necessario entrar na fila.\n");
        return;
    }

    if (!lerInt("Codigo do usuario: ", &usuarioId) ||
        !buscarUsuario(usuarioId, &usuario))
    {
        printf("Usuario nao encontrado.\n");
        return;
    }

    int id = adicionarFilaEspera(livroId, usuarioId);

    if (id == 0)
    {
        printf("Nao foi possivel adicionar. O usuario talvez ja esteja na fila deste livro.\n");
    }
    else
    {
        printf("Pedido %d adicionado ao final da fila.\n", id);
    }
}
