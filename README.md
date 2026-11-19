## Biblioteca Comunitária

Sistema desenvolvido em C para gerenciar livros, usuários e empréstimos de uma biblioteca comunitária. O programa permite cadastrar, buscar, listar e remover registros, além de registrar empréstimos e devoluções. Os dados são armazenados em arquivos CSV.

## Instituição

A instituição é uma biblioteca comunitária idealizada, aberta a qualquer pessoa interessada em pegar livros emprestados. Para organizar os empréstimos e as devoluções, cada usuário precisa ser cadastrado no sistema.

## Justificativa

O projeto foi escolhido para representar uma biblioteca comunitária acessível a qualquer pessoa interessada em pegar livros emprestados. O sistema ajuda a organizar o acervo e os cadastros de usuários, além de registrar empréstimos e devoluções. Com isso, é possível consultar a disponibilidade dos livros e acompanhar quais empréstimos ainda estão em aberto.

## Funcionalidades

- Cadastrar, buscar, listar e remover livros.
- Cadastrar, buscar, listar e remover usuários.
- Registrar, buscar e listar empréstimos.
- Registrar a devolução de um livro.
- Verificar se o livro e o usuário existem antes de registrar um empréstimo.
- Verificar a disponibilidade de exemplares.
- Atualizar a quantidade disponível de um livro ao emprestá-lo ou recebê-lo de volta.
- Salvar livros, usuários e empréstimos em arquivos CSV.

## Estrutura de dados utilizadas

| Estrutura | Onde é usada | Por que foi escolhida |
|---|---|---|
| Lista simplesmente encadeada | Livros | O acervo pode crescer ou diminuir sem definir um tamanho máximo fixo nem deslocar elementos, como aconteceria em um vetor. A lista é percorrida pelo título para exibir os livros em ordem alfabética. Também pode remover sem deslocamento bastando religar o nó anterior ao seguinte. Em um vetor, todos os elementos depois do removido precisam ser movidos uma posição. Inserção simples, encaixar um livro no meio da lista são dois ajustes de ponteiro. Em um vetor ordenado, seria preciso abrir espaço empurrando todos os elementos seguintes. |
 | Árvore binária de pesquisa | Usuarios | Os usuários são organizados pelo código. A árvore permite buscar um código percorrendo os ramos e listar os registros em ordem. Foi escolhida por ser mais simples que uma árvore balanceada para este cadastro; como não é balanceada, sua eficiência depende da forma como os dados são inseridos. Diferentemente de uma lista, a busca pode evitar percorrer todos os usuários; porém, como a árvore não é balanceada, sua eficiência depende da ordem de inserção dos IDs. ABP simples não se reorganiza sozinha. Ela apenas aplica a regra de inserção: ID menor vai para a esquerda; ID maior vai para a direita. |
 | Árvore AVL | Empréstimos | A AVL é usada para organizar os empréstimos pelo ID e manter a árvore balanceada a cada inserção. Isso evita que ela fique muito inclinada ? o que pode acontecer na ABP comum ? mantém buscas e inserções em O(log n), mesmo com IDs inseridos em ordem crescente ou decrescente. Permite listar os empréstimos em ordem de ID usando o percurso em ordem. Ideal para muitas leituras/buscas e também faz autobalanceamento por rotações.|

## Persistência

Os registros são armazenados em arquivos CSV na pasta `data`:

- `data/livros.csv`
- `data/usuarios.csv`
- `data/emprestimos.csv`

As operações de cadastro, remoção, empréstimo e devolução devem salvar os arquivos correspondentes após a alteração. O programa também salva os dados ao encerrar.

## Como compilar e executar

Requisitos: compilador C compatível com C23, CMake 4.1 ou superior e Git.

Na pasta principal do projeto:

```bash
cmake -S . -B build
cmake --build build
./build/Biblioteca-Comunitaria

Se não reconhecer os arquivos.csv: vá em Run > Edit Configurations,
localize o campo Working directory e altere para $ProjectFileDir$
```

## Organização do repositório

```text

??? data/                 # Arquivos CSV de livros, usuários e empréstimos
??? src/
?   ??? menu/             # Menus e interação com o usuário
?   ??? models/           # Entidades e operações das estruturas de dados
?   ??? utils/            # Funções auxiliares de entrada
??? main.c                # Inicialização, menu principal e encerramento
??? CMakeLists.txt        # Configuração de compilação
```

## Dificuldades e aprendizados

(refazer no final) O desenvolvimento envolve gerenciar nós e ponteiros nas estruturas encadeadas e nas árvores, manter as quantidades de livros coerentes com empréstimos e devoluções e salvar os dados em arquivos. O projeto permite praticar a escolha de uma estrutura de dados de acordo com a operação que o sistema precisa realizar.

## Uso de inteligência artificial

O ChatGPT foi utilizados como apoio para esclarecer conceitos de estruturas de dados, regras de negócio e validações, e organizar o texto do README.

## Autoria

Nome completo: Evandro Conceição

Matrícula: 202510703636