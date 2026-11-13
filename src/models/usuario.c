#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include <stdio.h>


typedef struct NoUsuario {
    Usuario usuario;
    struct NoUsuario *esquerda;
    struct NoUsuario *direita;
} NoUsuario;

static NoUsuario *raizUsuarios = NULL;

void inicializarUsuarios(void) {
    raizUsuarios = NULL;
}

static NoUsuario *inserirUsuario(NoUsuario *raiz, Usuario usuario) {

    if (raiz == NULL) {

        NoUsuario *novo = malloc(sizeof(NoUsuario));

        if (novo == NULL) {
            return NULL;
        }

        novo->usuario = usuario;
        novo->esquerda = NULL;
        novo->direita = NULL;

        return novo;
    }

    if (usuario.id < raiz->usuario.id) {
        raiz->esquerda = inserirUsuario(raiz->esquerda, usuario);
    }
    else if (usuario.id > raiz->usuario.id) {
        raiz->direita = inserirUsuario(raiz->direita, usuario);
    }

    return raiz;
}

int cadastrarUsuario(Usuario usuario) {

    if (usuario.id <= 0 ||
        strlen(usuario.nome) == 0 ||
        strlen(usuario.email) == 0) {
        return 0;
        }

    NoUsuario *atual = raizUsuarios;

    while (atual != NULL) {

        if (usuario.id == atual->usuario.id) {
            return 0;
        }

        if (usuario.id < atual->usuario.id) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    raizUsuarios = inserirUsuario(raizUsuarios, usuario);

    return 1;
}

int buscarUsuario(int id, Usuario *usuarioEncontrado) {

    if (id <= 0 || usuarioEncontrado == NULL) {
        return 0;
    }

    NoUsuario *atual = raizUsuarios;

    while (atual != NULL) {

        if (id == atual->usuario.id) {
            *usuarioEncontrado = atual->usuario;
            return 1;
        }

        if (id < atual->usuario.id) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    return 0;
}

static NoUsuario *encontrarMenor(NoUsuario *raiz) {

    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }

    return raiz;
}

static NoUsuario *removerNo(NoUsuario *raiz, int id, int *removido) {

    if (raiz == NULL) {
        return NULL;
    }

    if (id < raiz->usuario.id) {
        raiz->esquerda = removerNo(raiz->esquerda, id, removido);
    }
    else if (id > raiz->usuario.id) {
        raiz->direita = removerNo(raiz->direita, id, removido);
    }
    else {

        *removido = 1;

        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }

        if (raiz->esquerda == NULL) {
            NoUsuario *auxiliar = raiz->direita;
            free(raiz);
            return auxiliar;
        }

        if (raiz->direita == NULL) {
            NoUsuario *auxiliar = raiz->esquerda;
            free(raiz);
            return auxiliar;
        }

        NoUsuario *auxiliar = encontrarMenor(raiz->direita);

        raiz->usuario = auxiliar->usuario;

        int removidoSucessor = 0;

        raiz->direita = removerNo(
            raiz->direita,
            auxiliar->usuario.id,
            &removidoSucessor
        );
    }

    return raiz;
}

int removerUsuario(int id) {

    if (id <= 0) {
        return 0;
    }

    int removido = 0;

    raizUsuarios = removerNo(raizUsuarios, id, &removido);

    return removido;
}

static int listarNo(const NoUsuario *raiz) {

    if (raiz == NULL) {
        return 0;
    }

    int total = listarNo(raiz->esquerda);

    printf("%d - %s (%s)\n", raiz->usuario.id, raiz->usuario.nome, raiz->usuario.email);

    return total + 1 + listarNo(raiz->direita);
}

int listarUsuarios(void) {
    return listarNo(raizUsuarios);
}

static void liberarNo(NoUsuario *raiz) {

    if (raiz == NULL) {
        return;
    }

    liberarNo(raiz->esquerda);
    liberarNo(raiz->direita);
    free(raiz);
}

void liberarUsuarios(void) {
    liberarNo(raizUsuarios);
    raizUsuarios = NULL;
}