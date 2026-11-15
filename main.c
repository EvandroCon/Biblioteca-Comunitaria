#include <stdio.h>
#include "src/menu/menu.h"
#include "src/models/livro.h"
#include "src/models/usuario.h"
#include "src/models/emprestimos.h"

int main() {

    inicializarLivros();
    inicializarUsuarios();
    inicializarEmprestimos();
    menuPrincipal();

    salvarLivros("data/livros.csv");

    liberarUsuarios();
    liberarLivros();
    liberarEmprestimos();

    return 0;
}