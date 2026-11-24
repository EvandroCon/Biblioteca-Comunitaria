## Biblioteca Comunitária

Sistema desenvolvido em C para gerenciar livros, usuários, empréstimos e a fila de espera de uma biblioteca comunitária. O programa permite cadastrar, buscar, listar, remover registros, além de registrar empréstimos, devoluções e organizar uma fila de espera para os livros. Os dados são armazenados em arquivos CSV.

## Instituição

A instituição é uma **biblioteca comunitária idealizada**: um espaço aberto a qualquer pessoa interessada em pegar livros emprestados, mantido pela própria comunidade, com um acervo pequeno e poucos exemplares de cada título. Para emprestar, a pessoa precisa estar cadastrada. Quando um livro não tem exemplar disponível, o interessado entra em uma fila de espera.

## Justificativa

O projeto foi escolhido para representar uma biblioteca comunitária acessível a qualquer pessoa interessada em pegar livros emprestados. O sistema ajuda a organizar o acervo e os cadastros de usuários, além de registrar empréstimos e devoluções e ainda a utilização de uma fila de espera. Com isso, é possível consultar a disponibilidade dos livros e acompanhar quais empréstimos ainda estão em aberto.

Características do sistema:

- mantém o acervo e os cadastros organizados;
- impede emprestar um livro sem exemplar disponível;
- mantém o histórico de empréstimos e devoluções;
- organiza a espera por um livro em ordem de chegada, de forma justa.

## Fontes e pesquisa

> - Projeto anterior de uma livraria através de terminal feita em typescript junto a um projeto de banco de dados em SQL. Disponível em: https://github.com/EvandroCon/BookStore-Manager-CLI.

> - Instituto Federal de Santa Catarina. Bibliotecas ? Portal do IFSC. Disponível em: https://www.ifsc.edu.br/bibliotecas. Usada como referência dos serviços de uma biblioteca real: cadastro de usuários, registro de empréstimos e devoluções com histórico, e reserva de materiais, que inspirou a fila de espera.

> - Conceitos de estruturas de dados vistos na disciplina de Programação 2.

## Funcionalidades

**Livros**
- Cadastrar, buscar (por código), atualizar, remover e listar livros (listagem em ordem alfabética de título).
- Controle da quantidade de exemplares disponíveis.

**Usuários**
- Cadastrar (com validação de e-mail), buscar (por código), atualizar, remover e listar usuários (listagem em ordem de código).

**Empréstimos**
- Cadastrar empréstimo, verificando se o livro e o usuário existem e se há exemplar disponível; a quantidade do livro é reduzida automaticamente.
- Registrar devolução, que devolve o exemplar ao estoque.
- Buscar um empréstimo por código e listar todos (com título do livro e nome do usuário).
- Livros e usuários com empréstimo em aberto não podem ser removidos.

**Fila de espera**
- Entrar na fila de um livro sem exemplar disponível (o mesmo usuário não pode entrar duas vezes na fila do mesmo livro).
- Listar os pedidos, de todos os livros ou de um livro específico, com a posição de cada um.
- Cancelar um pedido.
- Integração com os empréstimos: se um livro tem fila, só o primeiro da fila pode retirá-lo; ao concluir o empréstimo, o pedido sai da fila. Ao devolver um livro, o sistema avisa quem é o próximo da fila.

**Persistência**
- Livros, usuários, empréstimos e fila são salvos em CSV após cada alteração e novamente ao encerrar o programa; são carregados ao iniciar.

## Estrutura de dados utilizadas

| Estrutura | Onde é usada | Por que foi escolhida |
|---|---|---|
| Lista simplesmente encadeada  (ordenada por título)| Acervo de livros | O acervo pode crescer ou diminuir sem definir um tamanho máximo fixo nem deslocar elementos, como aconteceria em um vetor. A lista é percorrida pelo título para exibir os livros em ordem alfabética. Também pode remover sem deslocamento bastando religar o nó anterior ao seguinte. Em um vetor, todos os elementos depois do removido precisam ser movidos uma posição. Inserção simples, encaixar um livro no meio da lista são dois ajustes de ponteiro. Em um vetor ordenado, seria preciso abrir espaço empurrando todos os elementos seguintes.|
 | Árvore binária de pesquisa (ABP)| Usuários, organizados pelo código | A busca por código descarta metade dos ramos a cada comparação, em vez de percorrer todos os usuários como em uma lista, e o percurso em ordem lista os usuários já ordenados. Foi escolhida por ser mais simples que uma árvore balanceada para um cadastro de crescimento moderado. Limitação: como não se reorganiza, se os códigos forem inseridos em ordem crescente ela degenera em uma lista e a busca passa a ser O(n). A remoção trata os três casos (nó folha, um filho e dois filhos, usando o menor da subárvore direita). |
 | Árvore AVL | Empréstimos, organizados pelo código | Arvore AVL única, ganho em memória porém perde velocidade. É a base do histórico (todos os empréstimos já feitos), que só cresce e é consultado com frequência. A AVL garante altura O(log n) mesmo com códigos inseridos em ordem crescente ou decrescente (o caso em que uma ABP comum degeneraria), usando rotações simples e duplas a cada inserção. Também permite listar em ordem de código com o percurso em ordem.
| Fila (lista encadeada com ponteiros para início e fim) | Fila de espera por livros| A espera por um livro segue a regra "quem chegou primeiro é atendido primeiro" (FIFO), então a fila reflete diretamente a regra de negócio. Entrar na fila é O(1) graças ao ponteiro para o fim. Uma pilha serviria ao contrário (o último a chegar seria atendido primeiro), e um vetor teria tamanho fixo. A implementação usa nós encadeados também para permitir cancelar um pedido que está no meio da fila, religando os vizinhos.


## Como compilar e executar

Requisitos: compilador C compatível com C23, CMake 4.1 ou superior e Git.

Na pasta principal do projeto:

```bash
Se não tiver com cmake instalado:

winget install --id Kitware.CMake --exact


Se já estiver instalado:

cmake -S . -B build
cmake --build build
./build/Biblioteca-Comunitaria

Pelo CLion: se não reconhecer os arquivos.csv: vá em Run > Edit Configurations,
localize o campo Working directory e altere para $ProjectFileDir$
``` 

## Organização do repositório

```text
.
??? data/                      # Arquivos CSV (livros, usuários, empréstimos e fila de espera)
??? src/
?   ??? menu/                  # Menus e interação com o usuário
?   ?   ??? menu.c             # Menu principal
?   ?   ??? menu_livros.c
?   ?   ??? menu_usuarios.c
?   ?   ??? menu_emprestimos.c
?   ?   ??? menu_fila_espera.c
?   ??? models/                # Entidades e implementação das estruturas de dados
?   ?   ??? livro.c            # Lista encadeada ordenada
?   ?   ??? usuario.c          # Árvore binária de pesquisa
?   ?   ??? emprestimos.c      # Árvore AVL
?   ?   ??? fila_espera.c      # Fila
?   ??? utils/
?       ??? entrada.c          # Funções auxiliares de leitura de dados
??? main.c                     # Carrega os dados, abre o menu principal e salva ao encerrar
??? CMakeLists.txt             # Configuração de compilação
??? README.md
```

## Dificuldades e aprendizados

- **Árvore de usuários e a persistência:** percebi que a ABP de usuários perdia a forma ao fechar e abrir o programa. O `salvarNos` gravava os usuários em ordem crescente de código (percurso em ordem), e, ao carregar, essa sequência era reinserida e transformava a árvore em uma "escada" para a direita, com busca O(n). Corrigi gravando cada nó antes das sub-árvores (pré-ordem), o que recria a mesma forma na carga. Também aprendi que isso apenas preserva a forma: a ABP não se balanceia sozinha, e códigos cadastrados em ordem crescente continuam degenerando a árvore. É com a AVL que esse problema se resolve.
- **Rotações da AVL:** entender quando aplicar rotação simples ou dupla e manter as alturas atualizadas.
- **Consistência entre estruturas:** o estoque do livro, os empréstimos e a fila precisam andar juntos. Isso levou a regras como impedir a remoção de livros e usuários com empréstimo em aberto e salvar os arquivos imediatamente após cada operação.
- **Fila integrada ao empréstimo:** garantir que, havendo fila, só o primeiro usuário consiga retirar o livro.
- **Aprendizado:** a escolha da estrutura deve partir da operação que o sistema mais faz (busca, ordem de chegada, ordem alfabética), e não do contrário. E sobre a ABP sua forma depende da ordem de inserção, e a ordem em que os dados são salvos em arquivo também influencia a árvore reconstruída na carga. Para dados que chegam ordenados, uma árvore balanceada (AVL) é mais segura.

## Uso de inteligência artificial

- **ChatGPT:** apoio para esclarecer conceitos de estruturas de dados, regras de negócio e validações, e para organizar o texto do README.

## Autoria

Nome completo: Evandro Conceição

Matrícula: 202510703636