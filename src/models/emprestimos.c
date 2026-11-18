#include "livro.h"
#include "usuario.h"
#include "emprestimos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct NoEmprestimo
{
    Emprestimo emprestimo;
    int altura;
    struct NoEmprestimo* esquerda;
    struct NoEmprestimo* direita;
} NoEmprestimo;

static NoEmprestimo* raizEmprestimos = NULL;

static const char *caminho = "data/emprestimos.csv";

void inicializarEmprestimos(void)
{
    raizEmprestimos = NULL;
}

static int altura(const NoEmprestimo* no)
{
    if (no == NULL)
    {
        return 0;
    }

    return no->altura;
}

static int maior(int a, int b)
{
    return a > b ? a : b;
}

static void atualizarAltura(NoEmprestimo* no)
{
    no->altura = 1 + maior(
        altura(no->esquerda),
        altura(no->direita)
    );
}

static int fatorBalanceamento(const NoEmprestimo* no)
{
    if (no == NULL)
    {
        return 0;
    }

    return altura(no->esquerda) - altura(no->direita);
}

static NoEmprestimo* rotacionarDireita(NoEmprestimo* raiz)
{
    NoEmprestimo* novaRaiz = raiz->esquerda;
    NoEmprestimo* subarvore = novaRaiz->direita;

    novaRaiz->direita = raiz;
    raiz->esquerda = subarvore;

    atualizarAltura(raiz);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}

static NoEmprestimo* rotacionarEsquerda(NoEmprestimo* raiz)
{
    NoEmprestimo* novaRaiz = raiz->direita;
    NoEmprestimo* subarvore = novaRaiz->esquerda;

    novaRaiz->esquerda = raiz;
    raiz->direita = subarvore;

    atualizarAltura(raiz);
    atualizarAltura(novaRaiz);

    return novaRaiz;
}

static NoEmprestimo* inserirAVL(NoEmprestimo* no, Emprestimo emprestimo, int* sucesso)
{
    if (no == NULL)
    {
        NoEmprestimo* novo = malloc(sizeof *novo);

        if (novo == NULL)
        {
            *sucesso = 0;
            return NULL;
        }

        novo->emprestimo = emprestimo;
        novo->altura = 1;
        novo->esquerda = NULL;
        novo->direita = NULL;

        *sucesso = 1;
        return novo;
    }

    if (emprestimo.id < no->emprestimo.id)
    {
        NoEmprestimo* filho =
            inserirAVL(no->esquerda, emprestimo, sucesso);

        if (!*sucesso)
        {
            return no;
        }

        no->esquerda = filho;
    }
    else if (emprestimo.id > no->emprestimo.id)
    {
        NoEmprestimo* filho =
            inserirAVL(no->direita, emprestimo, sucesso);

        if (!*sucesso)
        {
            return no;
        }

        no->direita = filho;
    }
    else
    {
        *sucesso = 0;
        return no;
    }

    atualizarAltura(no);

    int fator = fatorBalanceamento(no);

    if (fator > 1 &&
        emprestimo.id < no->esquerda->emprestimo.id)
    {
        return rotacionarDireita(no);
    }

    if (fator < -1 &&
        emprestimo.id > no->direita->emprestimo.id)
    {
        return rotacionarEsquerda(no);
    }

    if (fator > 1 &&
        emprestimo.id > no->esquerda->emprestimo.id)
    {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    if (fator < -1 &&
        emprestimo.id < no->direita->emprestimo.id)
    {
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    return no;
}

int cadastrarEmprestimo(Emprestimo emprestimo)
{
    if (emprestimo.id <= 0 ||
        emprestimo.livro_id <= 0 ||
        emprestimo.usuario_id <= 0 ||
        emprestimo.data_emprestimo[0] == '\0')
    {
        return 0;
    }

    int sucesso = 0;

    raizEmprestimos =
        inserirAVL(raizEmprestimos, emprestimo, &sucesso);

    return sucesso;
}

Emprestimo* buscarEmprestimo(int id)
{
    NoEmprestimo* atual = raizEmprestimos;
    while (atual != NULL)
    {
        if (id == atual->emprestimo.id) return &atual->emprestimo;
        atual = id < atual->emprestimo.id ? atual->esquerda : atual->direita;
    }
    return NULL;
}

static void listarNos(const NoEmprestimo *no, int *total)
{
    if (no == NULL)
    {
        return;
    }

    listarNos(no->esquerda, total);

    const Emprestimo *e = &no->emprestimo;
    Livro *livro = buscarLivroPorId(e->livro_id);

    Usuario usuario;
    int usuarioEncontrado = buscarUsuario(e->usuario_id, &usuario);

    printf("Emprestimo %d | Livro: %s | Usuario: %s | ",
           e->id,
           livro != NULL ? livro->titulo : "nao encontrado",
           usuarioEncontrado ? usuario.nome : "nao encontrado");

    if (e->devolvido)
    {
        printf("Devolvido em %s\n", e->data_devolucao);
    }
    else
    {
        printf("Em aberto\n");
    }

    (*total)++;

    listarNos(no->direita, total);
}

int listarEmprestimos(void)
{
    int total = 0;

    listarNos(raizEmprestimos, &total);

    return total;
}

int registrarDevolucao(int id, const char* data_devolucao)
{
    Emprestimo* emprestimo = buscarEmprestimo(id);
    if (emprestimo == NULL || emprestimo->devolvido || data_devolucao == NULL ||
        data_devolucao[0] == '\0')
        return 0;
    strncpy(emprestimo->data_devolucao, data_devolucao, TAMANHO_DATA - 1);
    emprestimo->data_devolucao[TAMANHO_DATA - 1] = '\0';
    emprestimo->devolvido = 1;
    return 1;
}

static void liberarNos(NoEmprestimo* no)
{
    if (no == NULL) return;
    liberarNos(no->esquerda);
    liberarNos(no->direita);
    free(no);
}

void liberarEmprestimos(void)
{
    liberarNos(raizEmprestimos);
    raizEmprestimos = NULL;
}

static int salvarNos(FILE* arquivo, const NoEmprestimo* no)
{
    if (no == NULL)
    {
        return 1;
    }

    if (!salvarNos(arquivo, no->esquerda))
    {
        return 0;
    }

    const Emprestimo* e = &no->emprestimo;

    if (fprintf(arquivo, "%d;%d;%d;%s;%s;%d\n",
                e->id,
                e->livro_id,
                e->usuario_id,
                e->data_emprestimo,
                e->devolvido ? e->data_devolucao : "-",
                e->devolvido) < 0)
    {
        return 0;
    }

    return salvarNos(arquivo, no->direita);
}

int salvarEmprestimos(void)
{
    FILE* arquivo = fopen(caminho, "w");

    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo de emprestimos");
        return 0;
    }

    if (fprintf(arquivo,
                "id;livro_id;usuario_id;data_emprestimo;"
                "data_devolucao;devolvido\n") < 0 ||
        !salvarNos(arquivo, raizEmprestimos))
    {
        fclose(arquivo);
        return 0;
    }

    if (fclose(arquivo) != 0)
    {
        perror("Erro ao fechar o arquivo de emprestimos");
        return 0;
    }

    return 1;
}

static int carregarLinhaEmprestimo(char *linha)
{
    Emprestimo emprestimo = {0};

    int camposLidos = sscanf(
        linha,
        "%d;%d;%d;%19[^;];%19[^;];%d",
        &emprestimo.id,
        &emprestimo.livro_id,
        &emprestimo.usuario_id,
        emprestimo.data_emprestimo,
        emprestimo.data_devolucao,
        &emprestimo.devolvido
    );

    if (camposLidos != 6)
    {
        return 0;
    }

    if (strcmp(emprestimo.data_devolucao, "-") == 0)
    {
        emprestimo.data_devolucao[0] = '\0';
    }

    if (emprestimo.devolvido != 0 && emprestimo.devolvido != 1)
    {
        return 0;
    }

    return cadastrarEmprestimo(emprestimo);
}

int carregarEmprestimos(void)
{
    FILE *arquivo = fopen(caminho, "r");

    if (arquivo == NULL)
    {
        return 0;
    }

    char linha[256];

    if (fgets(linha, sizeof linha, arquivo) == NULL)
    {
        fclose(arquivo);
        return 0;
    }

    int totalCarregados = 0;

    while (fgets(linha, sizeof linha, arquivo) != NULL)
    {
        if (carregarLinhaEmprestimo(linha))
        {
            totalCarregados++;
        }
    }

    fclose(arquivo);
    return totalCarregados;
}