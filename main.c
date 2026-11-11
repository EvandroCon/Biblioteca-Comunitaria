#include <stdio.h>
#include "src/menu/menu.h"
#include "src/models/livro.h"
#include "src/models/usuario.h"
int main() {

    inicializarLivros();
    inicializarUsuarios();
    menuPrincipal();

    liberarUsuarios();
    liberarLivros();

    return 0;
}