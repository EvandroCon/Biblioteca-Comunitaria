#ifndef BIBLIOTECA_COMUNITARIA_LIVRO_H
#define BIBLIOTECA_COMUNITARIA_LIVRO_H

typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    int quantidade;
} Livro;


void inicializarLivros(void);
int cadastrarLivro(Livro livro);
Livro *buscarLivroPorId(int id);
int buscarLivrosPorTitulo(const char *titulo);
void liberarLivros(void);

#endif //BIBLIOTECA_COMUNITARIA_LIVRO_H