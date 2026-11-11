#include "menu_usuarios.h"
#include "../utils/entrada.h"
#include <stdio.h>
#include <string.h>
#include "../models/usuario.h"

void menuUsuarios() {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n");
        printf("\tGerenciar Usuarios\n");
        printf("\n");

        printf("\n1 - Cadastrar usuario\n");
        printf("2 - Buscar usuario\n");
        printf("3 - Remover usuario\n");
        printf("4 - Listar usuario\n");
        printf("0 - Voltar\n");

        if (!lerInt("\nEscolha uma opcao: ", &opcao)) {
            printf("\nEntrada invalida\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {
        case 1:
            menuCadastrarUsuario();
            break;

        case 2:
            printf("\nBusca de usuario");
            break;

        case 3:
            printf("\nRemocao de usuario");
            break;

        case 4:
            printf("\nListagem de usuario");
            break;

        case 0:
            printf("\nVoltando ao menu principal\n");
            break;

        default:
            printf("\nOpcao invalida");
        }
    }
}

static int emailValido(const char *email) {
    const char *arroba = strchr(email, '@');

    if (arroba == NULL || arroba == email) {
        return 0;
    }
    if (strchr(email, ' ') != NULL) {
        return 0;
    }

    const char *ponto = strchr(arroba + 1, '.');
    return ponto != NULL && ponto != arroba + 1 && ponto[1] != '\0';
}

void menuCadastrarUsuario() {

    Usuario usuario;

    printf("\n--- CADASTRAR USUARIO ---\n");

    if (!lerInt("Codigo: ", &usuario.id) || usuario.id <= 0) {
        printf("\nErro: o codigo deve ser um numero positivo!\n");
        return;
    }

    lerString("Nome: ", usuario.nome, sizeof usuario.nome);
    if (strlen(usuario.nome) == 0) {
        printf("\nErro: o nome nao pode ficar vazio!\n");
        return;
    }

    lerString("E-mail: ", usuario.email, sizeof usuario.email);
    if (!emailValido(usuario.email)) {
        printf("\nErro: e-mail invalido (use o formato nome@dominio.com)!\n");
        return;
    }

    if (cadastrarUsuario(usuario)) {
        printf("\nUsuario cadastrado com sucesso!\n");
    } else {
        printf("\nNao foi possivel cadastrar, codigo ja cadastrado.\n");
    }
}
