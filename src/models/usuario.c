#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include <stdio.h>

//os ids de usuario nao precisam ser em ordem crescente, até porque
//se forem, como a arvore nao se balanceia, cada no vai para a direita
//do anterior e a arvore vira uma lista
typedef struct NoUsuario
{
    Usuario usuario;
    struct NoUsuario* esquerda;
    struct NoUsuario* direita;
} NoUsuario;

static NoUsuario* raizUsuarios = NULL;

static const char *caminho = "data/usuarios.csv";

void inicializarUsuarios(void)
{
    raizUsuarios = NULL;
}

static NoUsuario* inserirUsuario(NoUsuario* raiz, Usuario usuario)
{
    if (raiz == NULL)
    {
        NoUsuario* novo = malloc(sizeof(NoUsuario));

        if (novo == NULL)
        {
            return NULL;
        }

        novo->usuario = usuario;
        novo->esquerda = NULL;
        novo->direita = NULL;

        return novo;
    }

    if (usuario.id < raiz->usuario.id)
    {
        raiz->esquerda = inserirUsuario(raiz->esquerda, usuario);
    }
    else if (usuario.id > raiz->usuario.id)
    {
        raiz->direita = inserirUsuario(raiz->direita, usuario);
    }

    return raiz;
}

int cadastrarUsuario(Usuario usuario)
{
    if (usuario.id <= 0 ||
        strlen(usuario.nome) == 0 ||
        strlen(usuario.email) == 0)
    {
        return 0;
    }

    NoUsuario* atual = raizUsuarios;

    while (atual != NULL)
    {
        if (usuario.id == atual->usuario.id)
        {
            return 0;
        }

        if (usuario.id < atual->usuario.id)
        {
            atual = atual->esquerda;
        }
        else
        {
            atual = atual->direita;
        }
    }

    raizUsuarios = inserirUsuario(raizUsuarios, usuario);

    return 1;
}

int buscarUsuario(int id, Usuario* usuarioEncontrado)
{
    if (id <= 0 || usuarioEncontrado == NULL)
    {
        return 0;
    }

    NoUsuario* atual = raizUsuarios;

    while (atual != NULL)
    {
        if (id == atual->usuario.id)
        {
            *usuarioEncontrado = atual->usuario;
            return 1;
        }

        if (id < atual->usuario.id)
        {
            atual = atual->esquerda;
        }
        else
        {
            atual = atual->direita;
        }
    }

    return 0;
}

static NoUsuario* encontrarMenor(NoUsuario* raiz)
{
    while (raiz->esquerda != NULL)
    {
        raiz = raiz->esquerda;
    }

    return raiz;
}

static NoUsuario* removerNo(NoUsuario* raiz, int id, int* removido)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    if (id < raiz->usuario.id)
    {
        raiz->esquerda = removerNo(raiz->esquerda, id, removido);
    }
    else if (id > raiz->usuario.id)
    {
        raiz->direita = removerNo(raiz->direita, id, removido);
    }
    else
    {
        *removido = 1;

        if (raiz->esquerda == NULL && raiz->direita == NULL)
        {
            free(raiz);
            return NULL;
        }

        if (raiz->esquerda == NULL)
        {
            NoUsuario* auxiliar = raiz->direita;
            free(raiz);
            return auxiliar;
        }

        if (raiz->direita == NULL)
        {
            NoUsuario* auxiliar = raiz->esquerda;
            free(raiz);
            return auxiliar;
        }

        NoUsuario* auxiliar = encontrarMenor(raiz->direita);

        raiz->usuario = auxiliar->usuario;

        int removidoSucessor = 0;

        raiz->direita = removerNo(
            raiz->direita,
            auxiliar->usuario.id,
            &removidoSucessor
        );
    }

    return raiz;
}

int removerUsuario(int id)
{
    if (id <= 0)
    {
        return 0;
    }

    int removido = 0;

    raizUsuarios = removerNo(raizUsuarios, id, &removido);

    return removido;
}

static int listarNo(const NoUsuario* raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    int total = listarNo(raiz->esquerda);

    printf("%d - %s (%s)\n", raiz->usuario.id, raiz->usuario.nome, raiz->usuario.email);

    return total + 1 + listarNo(raiz->direita);
}

int listarUsuarios(void)
{
    return listarNo(raizUsuarios);
}

static void imprimirNo(const NoUsuario* no, int nivel)
{
    if (no == NULL)
    {
        return;
    }

    imprimirNo(no->direita, nivel + 1);
    printf("%*s%d\n", nivel * 4, "", no->usuario.id);
    imprimirNo(no->esquerda, nivel + 1);
}

void imprimirArvoreUsuarios(void)
{
    imprimirNo(raizUsuarios, 0);
}

static void liberarNo(NoUsuario* raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    liberarNo(raiz->esquerda);
    liberarNo(raiz->direita);
    free(raiz);
}

void liberarUsuarios(void)
{
    liberarNo(raizUsuarios);
    raizUsuarios = NULL;
}

//O codigo antigo organizava o arquivo em ordem crescente
//e isso estraga a arvore na proxima abertura, com a função
//nova, o arquivo sai em pre-ordem(nó, esquerda, direita).
//percorre a arvore binaria em ordem e grava cada usuario
static int salvarNos(FILE *arquivo, const NoUsuario *no)
{
    if (no == NULL)
    {
        return 1;
    }

    // 1) grava o nó primeiro (pré-ordem)
    if (fprintf(arquivo, "%d;%s;%s\n",
                no->usuario.id,
                no->usuario.nome,
                no->usuario.email) < 0)
    {
        return 0;
    }

    // 2) depois a esquerda e 3) a direita
    if (!salvarNos(arquivo, no->esquerda))
    {
        return 0;
    }

    return salvarNos(arquivo, no->direita);
}

int salvarUsuarios(void)
{
    FILE *arquivo = fopen(caminho, "w");

    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo de usuarios");
        return 0;
    }

    if (fprintf(arquivo, "id;nome;email\n") < 0 ||
        !salvarNos(arquivo, raizUsuarios))
    {
        fclose(arquivo);
        return 0;
    }

    if (fclose(arquivo) != 0)
    {
        perror("Erro ao fechar o arquivo de usuarios");
        return 0;
    }

    return 1;
}

//interpreta uma linha do arquivo e cadastra o usuario
static int carregarLinhaUsuario(char *linha)
{
    Usuario usuario;

    if (sscanf(linha, "%d;%99[^;];%99[^\r\n]",
               &usuario.id,
               usuario.nome,
               usuario.email) != 3)
    {
        return 0;
    }

    return cadastrarUsuario(usuario);
}

int carregarUsuarios(void)
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
        if (carregarLinhaUsuario(linha))
        {
            totalCarregados++;
        }
    }

    fclose(arquivo);
    return totalCarregados;
}

int atualizarUsuario(int id, Usuario novosDados)
{
    if (id <= 0 ||
        novosDados.nome[0] == '\0' ||
        novosDados.email[0] == '\0')
    {
        return 0;
    }

    NoUsuario* atual = raizUsuarios; //começa na raiz

    while (atual != NULL && atual->usuario.id != id)
    {
        if (id < atual->usuario.id)
            atual = atual->esquerda; //id procurado e menor: vai a esquerda
        else
            atual = atual->direita; //id procurado e maior: vai a direita
    }

    if (atual == NULL)
    {
        return 0;
    }

    atual->usuario = novosDados;
    atual->usuario.id = id;

    return 1;
}