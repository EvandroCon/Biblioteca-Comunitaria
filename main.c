#include <stdio.h>
#include "src/menu/menu.h"
#include "src/models/livro.h"
#include "src/models/usuario.h"
#include "src/models/emprestimos.h"

int main() {

    inicializarLivros();

    carregarLivros("data/livros.csv");
    carregarUsuarios("data/usuarios.csv");

    inicializarUsuarios();
    inicializarEmprestimos();
    menuPrincipal();

    salvarLivros("data/livros.csv");
    salvarUsuarios("data/usuarios.csv");

    liberarUsuarios();
    liberarLivros();
    liberarEmprestimos();

    return 0;
}