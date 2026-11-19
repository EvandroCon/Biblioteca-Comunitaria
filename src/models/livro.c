#include <stdio.h>
#include "livro.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoLivro
{
    Livro livro;
    struct NoLivro* proximo;
} NoLivro;

static NoLivro* inicioLivros = NULL;

static const char *caminho = "data/livros.csv";

static int quantidadeLivros = 0;

void inicializarLivros(void)
{
    inicioLivros = NULL;
    quantidadeLivros = 0;
}

static int compararTitulos(const char* a, const char* b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        int ca = tolower((unsigned char)a[i]);
        int cb = tolower((unsigned char)b[i]);

        if (ca != cb)
        {
            //As letras sao diferentes?
            return ca - cb; //A subtracao diz quem vem primeiro
        }
        i++;
    }
    return tolower((unsigned char)a[i]) - tolower((unsigned char)b[i]);
}

int cadastrarLivro(Livro livro)
{
    if (livro.quantidade < 0)
    {
        return 0;
    }

    if (livro.id <= 0)
    {
        return 0;
    }

    NoLivro* atual = inicioLivros;
    NoLivro* anteriorPosicao = NULL;
    int posicaoEncontrada = 0;

    while (atual != NULL)
    {
        if (atual->livro.id == livro.id)
        {
            return 0;
        }

        if (strcmp(atual->livro.titulo, livro.titulo) == 0 &&
            strcmp(atual->livro.autor, livro.autor) == 0)
        {
            return 0;
        }

        if (!posicaoEncontrada)
        {
            if (compararTitulos(livro.titulo, atual->livro.titulo) < 0)
            {
                posicaoEncontrada = 1;
            }
            else
            {
                anteriorPosicao = atual;
            }
        }

        atual = atual->proximo;
    }

    NoLivro* novo = malloc(sizeof(NoLivro));
    if (novo == NULL)
    {
        return 0;
    }
    novo->livro = livro;

    // Insere mantendo a ordem alfabetica por titulo
    if (anteriorPosicao == NULL)
    {
        novo->proximo = inicioLivros;
        inicioLivros = novo;
    }
    else
    {
        novo->proximo = anteriorPosicao->proximo;
        anteriorPosicao->proximo = novo;
    }

    quantidadeLivros++;
    return 1;
}

Livro* buscarLivroPorId(int id)
{
    NoLivro* atual = inicioLivros;

    while (atual != NULL)
    {
        if (atual->livro.id == id)
        {
            return &atual->livro;
        }
        atual = atual->proximo;
    }
    return NULL;
}

int removerLivro(int id)
{
    NoLivro* atual = inicioLivros;
    NoLivro* anterior = NULL;

    while (atual != NULL)
    {
        if (atual->livro.id == id)
        {
            if (anterior == NULL)
            {
                inicioLivros = atual->proximo;
            }
            else
            {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            quantidadeLivros--;
            return 1;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    return 0;
}

int listarLivros(void)
{
    NoLivro* atual = inicioLivros;

    while (atual != NULL)
    {
        printf("%d - %s\n", atual->livro.id, atual->livro.titulo);
        atual = atual->proximo;
    }

    return quantidadeLivros;
}

void liberarLivros(void)
{
    NoLivro* atual = inicioLivros;

    while (atual != NULL)
    {
        NoLivro* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicioLivros = NULL;
    quantidadeLivros = 0;
}

int salvarLivros(void) //Recebe o caminho do arquivo
{

    FILE *arquivo = fopen(caminho, "w"); //Abre o arquivo para escrita

    if (arquivo == NULL) //Verifica se a abertura falhou
    {
        return 0;
    }

    fprintf(arquivo, "id;titulo;autor;ano;quantidade\n"); //Escreve o cabeçalho

    NoLivro *atual = inicioLivros; //Começa pelo primeiro livro

    while (atual != NULL) //Percorre a lista até o fim
    {
        fprintf(arquivo, "%d;%s;%s;%d;%d\n",
                atual->livro.id,
                atual->livro.titulo,
                atual->livro.autor,
                atual->livro.ano,
                atual->livro.quantidade);

        atual = atual->proximo; //Avança para o próximo nó
    }

    fclose(arquivo); //Fecha o arquivo e informa sucesso
    return 1;
}

int carregarLivros(void)
{

    FILE *arquivo = fopen(caminho, "r");

    if (arquivo == NULL)
    {
        return 0;
    }

    char linha[512];

    if (fgets(linha, sizeof linha, arquivo) == NULL)
    {
        fclose(arquivo);
        return 0;
    }

    int carregados = 0;

    while (fgets(linha, sizeof linha, arquivo) != NULL)
    {
        Livro livro;

        if (sscanf(linha, "%d;%99[^;];%99[^;];%d;%d",
                   &livro.id,
                   livro.titulo,
                   livro.autor,
                   &livro.ano,
                   &livro.quantidade) == 5)
        {
            if (cadastrarLivro(livro))
            {
                carregados++;
            }
        }
    }

    fclose(arquivo);
    return carregados;
}

int atualizarLivro(int id, Livro novosDados)
{
    if (id <= 0 ||
        novosDados.titulo[0] == '\0' ||
        novosDados.autor[0] == '\0' ||
        novosDados.ano <= 0 ||
        novosDados.quantidade < 0)
    {
        return 0;
    }

    NoLivro *atual = inicioLivros;
    NoLivro *anterior = NULL;

    while (atual != NULL && atual->livro.id != id)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
        return 0;

    for (NoLivro *outro = inicioLivros; outro != NULL; outro = outro->proximo)
    {
        if (outro != atual &&
            strcmp(outro->livro.titulo, novosDados.titulo) == 0 &&
            strcmp(outro->livro.autor, novosDados.autor) == 0)
        {
            return 0;
        }
    }

    if (anterior == NULL)
        inicioLivros = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    atual->livro = novosDados;
    atual->livro.id = id;

    NoLivro *anteriorPosicao = NULL;
    NoLivro *posicao = inicioLivros;

    while (posicao != NULL &&
           compararTitulos(atual->livro.titulo, posicao->livro.titulo) >= 0)
    {
        anteriorPosicao = posicao;
        posicao = posicao->proximo;
    }

    atual->proximo = posicao;

    if (anteriorPosicao == NULL)
        inicioLivros = atual;
    else
        anteriorPosicao->proximo = atual;

    return 1;
}