**README.md**

## Descrição do Código

Este código consiste em uma implementação de um sistema de biblioteca em C++. A seguir, descrevo onde cada um dos critérios solicitados é atendido:

### 1. Alocação de Memória Dinâmica

A alocação de memória dinâmica é utilizada para criar objetos das classes `Livro`, `Membro`, e `Transacao`. Por exemplo:

```cpp
Material *novoMaterial = new Livro(titulo, codigo);
```

### 2. Manipulação de Arquivos

A manipulação de arquivos é realizada nas funções `carregarMateriais`, `salvarMateriais`, `carregarMembros`, `salvarMembros`, `salvarNovoMembro`, `carregarHistorico` e `salvarHistorico`. Essas funções carregam e salvam informações sobre materiais, membros e transações em arquivos de texto.

### 3. Construtores
Os construtores são implementados nas classes `Material`, `Livro`, `Membro`, `Transacao`, `Emprestimo` e `Devolucao`. Exemplo:

```cpp
Material::Material(const std::string &titulo, const std::string &codigo): titulo(titulo), codigo(codigo) {}
```

### 4. Destrutores 

Os destrutores são implementados nas classes `Material`, `Emprestimo`, `Devolucao` e `Biblioteca`. Exemplo:

```cpp
Material::~Material() {
  std::cout << "Destrutor de Material: " << titulo << std::endl;
}
```

### 5. Herança

A herança é utilizada na classe `Livro`, que é derivada da classe `Material`. Exemplo:

```cpp
class Livro : public Material {
    // ...
};
```

## Executando o Programa

Para executar o programa, basta compilar os arquivos `biblioteca.cpp` e `main.cpp` e rodar o executável gerado. Certifique-se de fornecer os dados corretos durante a execução do programa, como título, código, nome e ID.

```bash
g++ biblioteca.cpp main.cpp -o biblioteca
./biblioteca
```

O programa exibirá um menu interativo para realizar diferentes operações em uma biblioteca.

Lembre-se de criar os arquivos `materiais.txt`, `membros.txt` e `transacoes.txt` antes de executar o programa pela primeira vez.

```bash
touch materiais.txt membros.txt transacoes.txt
```

Espero que esta descrição seja útil. Caso tenha alguma dúvida ou sugestão, sinta-se à vontade para entrar em contato.
Pretendo implementar melhorias, pricipalmente no processo de devolução e empréstimo. 