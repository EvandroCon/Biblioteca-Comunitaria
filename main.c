#include <stdio.h>
#include "src/menu/menu.h"
#include "src/models/livro.h"
#include "src/models/usuario.h"
#include "src/models/emprestimos.h"
#include "src/models/fila_espera.h"

int main() {

    inicializarLivros();
    carregarLivros();

    inicializarUsuarios();
    carregarUsuarios();

    inicializarEmprestimos();
    carregarEmprestimos();

    inicializarFilaEspera();

    menuPrincipal();

    salvarLivros();
    salvarUsuarios();
    salvarEmprestimos();

    liberarUsuarios();
    liberarLivros();
    liberarEmprestimos();


    return 0;
}