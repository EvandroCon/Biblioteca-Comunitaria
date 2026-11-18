#include <stdio.h>
#include "src/menu/menu.h"
#include "src/models/livro.h"
#include "src/models/usuario.h"
#include "src/models/emprestimos.h"

int main() {

    inicializarLivros();
    carregarLivros();


    inicializarUsuarios();
    carregarUsuarios();


    inicializarEmprestimos();
    carregarEmprestimos();

    menuPrincipal();

    salvarLivros();
    salvarUsuarios();
    salvarEmprestimos();

    liberarUsuarios();
    liberarLivros();
    liberarEmprestimos();

    return 0;
}