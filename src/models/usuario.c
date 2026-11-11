#include <stdlib.h>
#include <string.h>
#include "usuario.h"

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