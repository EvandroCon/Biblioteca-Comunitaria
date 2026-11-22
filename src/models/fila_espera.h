//
// Created by vando on 20/11/2026.
//

#ifndef BIBLIOTECA_COMUNITARIA_FILA_ESPERA_H
#define BIBLIOTECA_COMUNITARIA_FILA_ESPERA_H

typedef struct
{
    int id;
    int livro_id;
    int usuario_id;
} SolicitacaoFila;

void inicializarFilaEspera(void);
int adicionarFilaEspera(int livro_id, int usuario_id);
void liberarFilaEspera(void);
int listarFilaEspera(int livro_id);
int removerFilaEspera(int id);

int salvarFilaEspera(void);
int carregarFilaEspera(void);

#endif //BIBLIOTECA_COMUNITARIA_FILA_ESPERA_H
