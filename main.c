#include <stdio.h>
#include "src/menu/menu.h"
#include "src/models/livro.h"
#include "src/models/usuario.h"
#include "src/models/emprestimos.h"

int main() {

    inicializarLivros();
    carregarLivros("data/livros.csv");


    inicializarUsuarios();
    carregarUsuarios("data/usuarios.csv");


    inicializarEmprestimos();
    carregarEmprestimos("data/emprestimos.csv");

    menuPrincipal();

    salvarLivros("data/livros.csv");
    salvarUsuarios("data/usuarios.csv");
    salvarEmprestimos("data/emprestimos.csv");

    liberarUsuarios();
    liberarLivros();
    liberarEmprestimos();

    return 0;
}