
#include <stdio.h>
#include "menu.h"
#include "menu_livros.h"
#include "menu_usuarios.h"
#include "menu_emprestimos.h"
#include "menu_historico.h"
#include "../utils/entrada.h"

void menuPrincipal() {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n");
        printf("\tLivraria Comunitaria\n");
        printf("\n");

        printf("\n1 - Gerenciar Livros\n");
        printf("2 - Gerenciar usuarios\n");
        printf("3 - Gerenciar Emprestimos\n");
        printf("4 - Historico de operacoes\n");
        printf("0 - Sair\n");

        if (!lerInt("\nEscolha uma opcao: ", &opcao)) {
            printf("\nEntrada invalida\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
                menuLivros();
                break;

            case 2:
                menuUsuarios();
                break;

            case 3:
                menuEmprestimos();
                break;

            case 4:
                menuHistorico();
                break;

            case 0:
                printf("\nSair");
                break;

            default:
                printf("\nOpcao invalida");
        }
    }
}