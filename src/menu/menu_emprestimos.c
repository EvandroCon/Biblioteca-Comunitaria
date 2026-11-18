#include "menu_emprestimos.h"
#include "../models/emprestimos.h"
#include "../models/livro.h"
#include "../models/usuario.h"
#include "../utils/entrada.h"
#include <stdio.h>
#include <string.h>

void menuEmprestimos()
{
    int opcao = -1;

    while (opcao != 0)
    {
        printf("\n");
        printf("\tGerenciar Emprestimos\n");
        printf("\n");

        printf("\n1 - Cadastrar emprestimo\n");
        printf("2 - Buscar emprestimo\n");
        printf("3 - Registrar devolucao\n");
        printf("4 - Listar emprestimo\n");
        printf("0 - Voltar\n");

        if (!lerInt("\nEscolha uma opcao: ", &opcao))
        {
            printf("\nEntrada invalida\n");
            opcao = -1;
            continue;
        }

        switch (opcao)
        {
        case 1:
            menuCadastrarEmprestimo();
            break;
        case 2:
            menuBuscarEmprestimo();
            break;

        case 3:
            menuDevolverLivro();
            break;

        case 4:
            menuListarEmprestimos();
            break;

        case 0:
            printf("\nVoltando ao menu principal\n");
            break;

        default:
            printf("\nOpcao invalida");
        }
    }
}

void menuCadastrarEmprestimo(void)
{
    Emprestimo emprestimo = {0};
    Usuario usuario;
    Livro* livro;

    printf("\n--- CADASTRAR EMPRESTIMO ---\n");
    if (!lerInt("Codigo do emprestimo: ", &emprestimo.id) || emprestimo.id <= 0)
    {
        printf("Codigo invalido.\n");
        return;
    }
    if (!lerInt("Codigo do livro: ", &emprestimo.livro_id) || emprestimo.livro_id <= 0 ||
        (livro = buscarLivroPorId(emprestimo.livro_id)) == NULL)
    {
        printf("Livro nao encontrado. Cadastre o livro antes do emprestimo.\n");
        return;
    }
    if (!lerInt("Codigo do usuario: ", &emprestimo.usuario_id) || emprestimo.usuario_id <= 0 ||
        !buscarUsuario(emprestimo.usuario_id, &usuario))
    {
        printf("Usuario nao encontrado. Cadastre o usuario antes do emprestimo.\n");
        return;
    }
    if (livro->quantidade <= 0)
    {
        printf("Nao ha exemplares disponiveis deste livro.\n");
        return;
    }
    lerString("Data do emprestimo (DD/MM/AAAA): ", emprestimo.data_emprestimo,
              sizeof emprestimo.data_emprestimo);
    if (strlen(emprestimo.data_emprestimo) == 0)
    {
        printf("A data do emprestimo e obrigatoria.\n");
        return;
    }

    emprestimo.devolvido = 0;
    emprestimo.data_devolucao[0] = '\0';
    if (!cadastrarEmprestimo(emprestimo))
    {
        printf("Nao foi possivel cadastrar. Verifique se o codigo ja existe.\n");
        return;
    }
    livro->quantidade--;

    int emprestimosSalvos = salvarEmprestimos();
    int livrosSalvos = salvarLivros();

    if (!emprestimosSalvos || !livrosSalvos)
    {
        printf("Emprestimo cadastrado, mas houve erro ao salvar um ou mais arquivos.\n");
    }
    else
    {
        printf("Emprestimo cadastrado e arquivos atualizados.\n");
    }

    printf("Exemplares disponiveis: %d\n", livro->quantidade);
}

void menuBuscarEmprestimo(void)
{
    int id;
    if (!lerInt("Codigo do emprestimo: ", &id) || id <= 0)
    {
        printf("Codigo invalido.\n");
        return;
    }
    Emprestimo* e = buscarEmprestimo(id);
    if (e == NULL)
    {
        printf("Emprestimo nao encontrado.\n");
        return;
    }
    printf("\nCodigo: %d\nLivro: %d\nUsuario: %d\nData do emprestimo: %s\n",
           e->id, e->livro_id, e->usuario_id, e->data_emprestimo);
    if (e->devolvido) printf("Data da devolucao: %s\n", e->data_devolucao);
    else printf("Situacao: em aberto\n");
}

void menuListarEmprestimos(void)
{
    printf("\n--- LISTA DE EMPRESTIMOS ---\n\n");

    int total = listarEmprestimos();

    if (total == 0)
    {
        printf("Nenhum emprestimo cadastrado.\n");
    }
    else
    {
        printf("\nTotal: %d emprestimo(s)\n", total);
    }
}

void menuDevolverLivro(void)
{
    int id;
    char data[TAMANHO_DATA];
    if (!lerInt("Codigo do emprestimo: ", &id) || id <= 0)
    {
        printf("Codigo invalido.\n");
        return;
    }
    Emprestimo* e = buscarEmprestimo(id);
    if (e == NULL)
    {
        printf("Emprestimo nao encontrado.\n");
        return;
    }
    if (e->devolvido)
    {
        printf("Este emprestimo ja foi devolvido.\n");
        return;
    }
    lerString("Data da devolucao (DD/MM/AAAA): ", data, sizeof data);
    if (strlen(data) == 0)
    {
        printf("A data da devolucao e obrigatoria.\n");
        return;
    }
    int livroId = e->livro_id;
    if (registrarDevolucao(id, data))
    {
        Livro *livro = buscarLivroPorId(livroId);
        if (livro != NULL)
            livro->quantidade++;

        if (!salvarEmprestimos())
            printf("Aviso: devolucao registrada, mas houve erro ao salvar emprestimos.\n");

        printf("Devolucao registrada.\n");
    }
}
