#include <stdio.h>
#include "src/menu/menu.h"
#include "src/models/livro.h"

int main() {

    inicializarLivros();

    menuPrincipal();

    liberarLivros();

    return 0;
}