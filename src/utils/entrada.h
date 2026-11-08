#ifndef BIBLIOTECA_COMUNITARIA_ENTRADA_H
#define BIBLIOTECA_COMUNITARIA_ENTRADA_H

#include <stddef.h>

int lerInt(const char *mensagem, int *valor);
void lerString(const char *mensagem, char *destino, size_t tamanho);

#endif