#include <stdio.h>
#include "emprestimos.h"

typedef struct NoEmprestimo {
    Emprestimo emprestimo;
    int altura;
    struct NoEmprestimo *esquerda;
    struct NoEmprestimo *direita;
} NoEmprestimo;

static NoEmprestimo *raizEmprestimos = NULL;

void inicializarEmprestimos(void) {
    raizEmprestimos = NULL;
}