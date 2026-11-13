//
// Created by aluno on 03/11/2026.
//

#ifndef BIBLIOTECA_COMUNITARIA_USUARIO_H
#define BIBLIOTECA_COMUNITARIA_USUARIO_H

typedef struct {
    int id;
    char nome[100];
    char email[100];
} Usuario;

int cadastrarUsuario(Usuario usuario);
void inicializarUsuarios(void);
int buscarUsuario(int id, Usuario *usuarioEncontrado);
int removerUsuario(int id);
void liberarUsuarios(void);

#endif //BIBLIOTECA_COMUNITARIA_USUARIO_H