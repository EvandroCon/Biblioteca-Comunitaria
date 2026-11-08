#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"

//le um número inteiro digitado pelo usuario e verifica se a entrada é valida
int lerInt(const char *mensagem, int *valor) {
    char buffer[64];
    char *fim;

    //exibe uma mensagem para o usuario e realiza a leitura de uma entrada
    //pelo teclado, verificando se a leitura ocorreu corretamente
    printf("%s", mensagem);
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    //a função strtol() converte um texto em número inteiro.
    *valor = (int) strtol(buffer, &fim, 10);

    //verifica se o usuário digitou algo inválido
    if (fim == buffer || (*fim != '\n' && *fim != '\0')) {
        return 0;
    }
    return 1;
}

//solicitar um texto ao usuario, armazenar esse texto em uma variavel e
//remover o caractere de quebra de linha (\n) que fica no final da leitura
void lerString(const char *mensagem, char *destino, size_t tamanho) {
    printf("%s", mensagem);
    if (fgets(destino, (int) tamanho, stdin) == NULL) {
        destino[0] = '\0';
        return;
    }
    //remocao do caractere de quebra de linha
    destino[strcspn(destino, "\n")] = '\0';
}