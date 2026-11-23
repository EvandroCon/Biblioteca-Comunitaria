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

    imprimirArvoreUsuarios();

    inicializarEmprestimos();
    carregarEmprestimos();

    inicializarFilaEspera();
    carregarFilaEspera();

    menuPrincipal();

    salvarLivros();
    salvarUsuarios();
    salvarEmprestimos();
    salvarFilaEspera();

    liberarUsuarios();
    liberarLivros();
    liberarEmprestimos();
    liberarFilaEspera();

    return 0;
}