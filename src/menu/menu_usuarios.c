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
            menuBuscarUsuario();
            break;

        case 3:
            menuRemoverUsuario();
            break;

        case 4:
            menuListarUsuarios();
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

    if (cadastrarUsuario(usuario))
    {
        if (salvarUsuarios())
            printf("\nUsuario cadastrado e arquivo atualizado.\n");
        else
            printf("\nUsuario cadastrado, mas houve erro ao salvar o arquivo.\n");
    }
    else
    {
        printf("\nNao foi possivel cadastrar, codigo ja cadastrado.\n");
    }
}

void menuBuscarUsuario() {

    int id;
    Usuario usuario;

    printf("\n--- BUSCAR USUARIO ---\n");

    if (!lerInt("Codigo: ", &id) || id <= 0) {
        printf("\nErro: o codigo deve ser um numero positivo!\n");
        return;
    }

    if (!buscarUsuario(id, &usuario)) {
        printf("\nUsuario nao encontrado.\n");
        return;
    }

    printf("\nUsuario encontrado:\n");
    printf("Codigo: %d\n", usuario.id);
    printf("Nome: %s\n", usuario.nome);
    printf("E-mail: %s\n", usuario.email);
}

void menuRemoverUsuario() {

    int id;
    Usuario usuario;
    char resposta[10];

    printf("\n--- REMOVER USUARIO ---\n");

    if (!lerInt("Codigo: ", &id) || id <= 0) {
        printf("\nErro: o codigo deve ser um numero positivo!\n");
        return;
    }

    if (!buscarUsuario(id, &usuario)) {
        printf("\nUsuario nao encontrado.\n");
        return;
    }

    printf("\nUsuario encontrado: %d - %s (%s)\n", usuario.id, usuario.nome, usuario.email);
    lerString("Confirma a remocao? (s/n): ", resposta, sizeof resposta);

    if (resposta[0] != 's' && resposta[0] != 'S') {
        printf("\nRemocao cancelada.\n");
        return;
    }

    if (removerUsuario(id))
    {
        if (salvarUsuarios())
            printf("\nUsuario removido e arquivo atualizado.\n");
        else
            printf("\nUsuario removido, mas houve erro ao salvar o arquivo.\n");
    }
    else
    {
        printf("\nNao foi possivel remover o usuario.\n");
    }
}

void menuListarUsuarios() {

    printf("\n--- LISTA DE USUARIOS ---\n\n");

    int total = listarUsuarios();

    if (total == 0) {
        printf("Nenhum usuario cadastrado.\n");
    } else {
        printf("\nTotal: %d usuario(s)\n", total);
    }
}

void menuAtualizarUsuario(void) {

    int id;
    Usuario existente;

    printf("\n--- ATUALIZAR USUARIO ---\n");

    if (!lerInt("Codigo do usuario: ", &id) || id <= 0) {
        printf("\nErro: o codigo deve ser um numero positivo!\n");
        return;
    }

    if (!buscarUsuario(id, &existente)) {
        printf("\nUsuario nao encontrado.\n");
        return;
    }

    printf("\nUsuario atual: %s (%s)\n", existente.nome, existente.email);

    Usuario novosDados = existente;

    lerString("Novo nome: ", novosDados.nome, sizeof novosDados.nome);
    if (strlen(novosDados.nome) == 0) {
        printf("\nErro: o nome nao pode ficar vazio!\n");
        return;
    }

    lerString("Novo e-mail: ", novosDados.email, sizeof novosDados.email);
    if (!emailValido(novosDados.email)) {
        printf("\nErro: e-mail invalido (use o formato nome@dominio.com)!\n");
        return;
    }

    if (!atualizarUsuario(id, novosDados)) {
        printf("\nNao foi possivel atualizar o usuario.\n");
        return;
    }

    if (salvarUsuarios())
        printf("\nUsuario atualizado e arquivo atualizado.\n");
    else
        printf("\nUsuario atualizado, mas houve erro ao salvar o arquivo.\n");
}