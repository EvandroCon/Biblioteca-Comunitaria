#ifndef BIBLIOTECA_COMUNITARIA_EMPRESTIMOS_H
#define BIBLIOTECA_COMUNITARIA_EMPRESTIMOS_H

#define TAMANHO_DATA 20

typedef struct
{
    int id;
    int livro_id;
    int usuario_id;
    char data_emprestimo[TAMANHO_DATA];
    char data_devolucao[TAMANHO_DATA];
    int devolvido;
} Emprestimo;

void inicializarEmprestimos(void);
int cadastrarEmprestimo(Emprestimo emprestimo);
Emprestimo* buscarEmprestimo(int id);
int listarEmprestimos(void);
int registrarDevolucao(int id, const char *data_devolucao);;
void liberarEmprestimos(void);

int salvarEmprestimos(void);
int carregarEmprestimos(void);

int livroTemEmprestimoEmAberto(int livroId);
int usuarioTemEmprestimoEmAberto(int usuarioId);
#endif //BIBLIOTECA_COMUNITARIA_EMPRESTIMOS_H
