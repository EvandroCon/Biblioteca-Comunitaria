//
// Created by aluno on 03/11/2026.
//

#include "emprestimos.h"

typedef struct {
    int livro_id;
    int usuario_id;
    char data_emprestimo[100];
    char data_devolução[100];
} Emprestimo;