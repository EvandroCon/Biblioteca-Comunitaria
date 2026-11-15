//
// Created by aluno on 03/11/2026.
//

#ifndef BIBLIOTECA_COMUNITARIA_EMPRESTIMOS_H
#define BIBLIOTECA_COMUNITARIA_EMPRESTIMOS_H

typedef struct {
    int id;
    int livro_id;
    int usuario_id;
    char data_emprestimo[100];
    char data_devolucao[100];
    int devolvido;
} Emprestimo;

void inicializarEmprestimos(void);
int cadastrarEmprestimo(Emprestimo emprestimo);
Emprestimo *buscarEmprestimo(int id);
int listarEmprestimos(void);
void liberarEmprestimos(void);

#endif //BIBLIOTECA_COMUNITARIA_EMPRESTIMOS_H