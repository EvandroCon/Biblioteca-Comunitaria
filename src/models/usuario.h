//
// Created by aluno on 03/11/2026.
//

#ifndef BIBLIOTECA_COMUNITARIA_USUARIO_H
#define BIBLIOTECA_COMUNITARIA_USUARIO_H

typedef struct
{
    int id;
    char nome[100];
    char email[100];
} Usuario;

int cadastrarUsuario(Usuario usuario);
void inicializarUsuarios(void);
int buscarUsuario(int id, Usuario* usuarioEncontrado);
int removerUsuario(int id);
int listarUsuarios(void);
void liberarUsuarios(void);

int salvarUsuarios(void);
int carregarUsuarios(void);

int atualizarUsuario(int id, Usuario novosDados);
#endif //BIBLIOTECA_COMUNITARIA_USUARIO_H
