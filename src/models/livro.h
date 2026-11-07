//
// Created by aluno on 03/11/2026.
//

#ifndef BIBLIOTECA_COMUNITARIA_LIVRO_H
#define BIBLIOTECA_COMUNITARIA_LIVRO_H

typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    int quantidade;
} Livro;



void inicializarLivros();
int cadastrarLivro(Livro livro);

#endif //BIBLIOTECA_COMUNITARIA_LIVRO_H