#include "biblioteca.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip> 

// Implementação da classe Material

Material::Material(const std::string &titulo, const std::string &codigo): titulo(titulo), codigo(codigo) {}

Material::~Material() {
  std::cout << "Destrutor de Material: " << titulo << std::endl;
}

std::string Material::getTitulo() const { return titulo; }

std::string Material::getCodigo() const { return codigo; }

void Material::exibirDetalhes() const {
  std::cout << "Material: " << getTitulo() << " (Código: " << getCodigo() << ")\n";
}

// Implementação da classe Livro (derivada de Material)

Livro::Livro(const std::string &titulo, const std::string &codigo): Material(titulo, codigo) {}

void Livro::exibirDetalhes() const {
    std::cout << "Livro: " << getTitulo() << " (Código: " << getCodigo() << ")\n";
}

// Implementação da classe Membro

Membro::Membro(const std::string &nome, const std::string &id): nome(nome), id(id) {}

std::string Membro::getNome() const { return nome; }

std::string Membro::getId() const { return id; }

void Membro::exibirDetalhes() const {
  std::cout << "Membro: " << getNome() << " (ID: " << getId() << ")\n";
}

// Implementação da classe Biblioteca

Membro *Biblioteca::getMembroPorIndice(std::size_t indice) const {
  if (indice < membros.size()) {
    return membros[indice];
  } else {
    return nullptr; // Índice fora do alcance
  }
}

// Implementação da classe Transacao

Transacao::Transacao(Material *material, Membro *membro): material(material), membro(membro) {}

Transacao::~Transacao() {
  std::cout << "Destrutor de Transacao\n";
}

Material* Transacao::getMaterial() const {
    return material;
}
Membro* Transacao::getMembro() const {
    return membro;
}
// Implementação da classe Emprestimo (derivada de Transacao)

Emprestimo::Emprestimo(Material *material, Membro *membro)
    : Transacao(material, membro) {}

Emprestimo::~Emprestimo() {
  std::cout << "Destrutor de Emprestimo\n";
}


void Emprestimo::realizar() const {
  std::cout << "Realizando empréstimo do material ";
  material->exibirDetalhes();
  std::cout << "Para o membro ";
  membro->exibirDetalhes();
}
std::string Emprestimo::obterDetalhes() const {
    return "Tipo: Empréstimo\nMembro: " + getMembro()->getNome() + " (ID: " + getMembro()->getId() + ")";
}

// Implementação da classe Devolucao (derivada de Transacao)

Devolucao::Devolucao(Material *material, Membro *membro): Transacao(material, membro) {}

Devolucao::~Devolucao() {
  std::cout << "Destrutor de Devolucao\n";
}
std::string Devolucao::obterDetalhes() const {
    return "Tipo: Devolução\nMembro: " + getMembro()->getNome() + " (ID: " + getMembro()->getId() + ")";
}

void Devolucao::realizar() const {
  std::cout << "Realizando devolução do material ";
  material->exibirDetalhes();
  std::cout << "Do membro ";
  membro->exibirDetalhes();
}

// Implementação da classe Biblioteca
Biblioteca::Biblioteca() {
  carregarMateriais("materiais.txt");
  carregarMembros("membros.txt");
  carregarHistorico("transacoes.txt");
}

Biblioteca::~Biblioteca() {
  for (auto &material : materiais) {
    delete material;
  }

  for (auto &membro : membros) {
    delete membro;
  }

  for (auto &transacao : transacoes) {
    delete transacao;
  }

}

void Biblioteca::adicionarMaterial(Material *material, const std::string &tipo) {
  materiais.push_back(material);
  salvarMateriais("materiais.txt", tipo);
}

void Biblioteca::adicionarMembro(Membro *membro) {
  membros.push_back(membro);
  salvarNovoMembro(membro);
}

void Biblioteca::realizarTransacao(Transacao *transacao) {
  transacao->realizar();
  transacoes.push_back(transacao); 

  // Verificar se é um Livro antes de exibir detalhes
  Material *material = transacao->getMaterial();
  Livro *livro = dynamic_cast<Livro*>(material);

  if (livro) {
    livro->exibirDetalhes();
  } else {
    std::cerr << "Erro: Material não é um Livro.\n";
  }
  //salve o histórico após adicionar a transação
  salvarHistorico("transacoes.txt");
}

const std::vector<Material *> &Biblioteca::getMateriais() const {
  return materiais;
}

const std::vector<Membro *> &Biblioteca::getMembros() const {
  return membros;
}

void Biblioteca::salvarMateriais(const std::string &nomeArquivo, const std::string &tipo) const {
  std::ofstream arquivo(nomeArquivo);
  if (arquivo.is_open()) {
    for (const auto &material : materiais) {
      arquivo << tipo << material->getTitulo() << "," << material->getCodigo() << "\n";
    }
    arquivo.close();
  } else {
    std::cerr << "Não foi possível abrir o arquivo para salvar materiais.\n";
  }
}

void Biblioteca::carregarMateriais(const std::string &nomeArquivo) {
  std::ifstream arquivo(nomeArquivo);
  if (arquivo.is_open()) {
    std::string linha;
    while (std::getline(arquivo, linha)) {
      // Supomos que cada linha do arquivo tem o formato "tipo,titulo,codigo"
      size_t pos1 = linha.find(',');
      size_t pos2 = linha.find(',', pos1 + 1);
      if (pos1 != std::string::npos && pos2 != std::string::npos) {
        std::string tipo = linha.substr(0, pos1);
        std::string titulo = linha.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string codigo = linha.substr(pos2 + 1);

        // Verifica o tipo e cria o objeto apropriado (por exemplo, Livro)
        if (tipo == "Livro") {
          materiais.push_back(new Livro(titulo, codigo));
        } else {
          // Ainda sem implementações de outros tipos de materiais
        }
      }
    }
    arquivo.close();
  } else {
    std::cerr << "Não foi possível abrir o arquivo para carregar materiais.\n";
  }
}

void Biblioteca::salvarMembros(const std::string &nomeArquivo) const {
  std::ofstream arquivo(nomeArquivo);
  if (arquivo.is_open()) {
    for (const auto &membro : membros) {
      arquivo << membro->getNome() << "," << membro->getId() << "\n";
    }
    arquivo.close();
  } else {
    std::cerr << "Não foi possível abrir o arquivo para salvar membros.\n";
  }
}

void Biblioteca::carregarMembros(const std::string &nomeArquivo) {
  std::ifstream arquivo(nomeArquivo);
  if (arquivo.is_open()) {
    membros.clear(); // Limpa os membros existentes
    std::string linha;
    while (std::getline(arquivo, linha)) {
      // Supomos que cada linha do arquivo tem o formato "nome,id"
      size_t pos = linha.find(',');
      if (pos != std::string::npos) {
        std::string nome = linha.substr(0, pos);
        std::string id = linha.substr(pos + 1);
        // Criar e adicionar um novo membro ao vetor
        membros.push_back(new Membro(nome, id));
      }
    }
    arquivo.close();
  } else {
    std::cerr << "Não foi possível abrir o arquivo para carregar membros.\n";
  }
}

void Biblioteca::salvarNovoMembro(const Membro *membro) const {
  std::ofstream arquivo("membros.txt", std::ios::app);  // Abre o arquivo em modo de apêndice
  if (arquivo.is_open()) {
    arquivo << membro->getNome() << "," << membro->getId() << "\n";
    arquivo.close();
  } else {
    std::cerr << "Não foi possível abrir o arquivo para salvar membros.\n";
  }
}

void Biblioteca::salvarHistorico(const std::string &nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        for (const auto &transacao : transacoes) {
            arquivo << transacao->getMaterial()->getTitulo() << ","
                    << transacao->getMaterial()->getCodigo() << ","
                    << transacao->getMembro()->getNome() << ","
                    << transacao->getMembro()->getId() << ","
                    << (dynamic_cast<Emprestimo*>(transacao) ? "Emprestimo" : "Devolucao")
                    << "\n";
        }
        arquivo.close();

        // Adicione este cout para verificar se está chegando até aqui
        std::cout << "Salvando histórico.\n";
    } else {
        std::cerr << "Não foi possível abrir o arquivo para salvar o histórico.\n";
    }
}

void Biblioteca::carregarHistorico(const std::string &nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        std::string linha;
        while (std::getline(arquivo, linha)) {
            size_t pos1 = linha.find(',');
            size_t pos2 = linha.find(',', pos1 + 1);
            size_t pos3 = linha.find(',', pos2 + 1);
            size_t pos4 = linha.find(',', pos3 + 1);

            if (pos1 != std::string::npos && pos2 != std::string::npos &&
                pos3 != std::string::npos && pos4 != std::string::npos) {
                std::string titulo = linha.substr(0, pos1);
                std::string codigo = linha.substr(pos1 + 1, pos2 - pos1 - 1);
                std::string nomeMembro = linha.substr(pos2 + 1, pos3 - pos2 - 1);
                std::string idMembro = linha.substr(pos3 + 1, pos4 - pos3 - 1);
                std::string tipoTransacao = linha.substr(pos4 + 1);

                Membro *membro = nullptr;
                Material *material = nullptr;

                for (const auto &m : membros) {
                    if (m->getNome() == nomeMembro && m->getId() == idMembro) {
                        membro = m;
                        break;
                    }
                }

                for (const auto &m : materiais) {
                    if (m->getTitulo() == titulo && m->getCodigo() == codigo) {
                        material = m;
                        break;
                    }
                }

                if (membro && material) {
                    if (tipoTransacao == "Emprestimo") {
                        transacoes.push_back(new Emprestimo(material, membro));
                    } else if (tipoTransacao == "Devolucao") {
                        transacoes.push_back(new Devolucao(material, membro));
                    }
                }
            }
        }
        arquivo.close();
    } else {
        std::cerr << "Não foi possível abrir o arquivo para carregar o histórico.\n";
    }
}

void Biblioteca::listarHistorico() const {
    std::cout << "\nHistórico de transações:\n\n";

    // Encontrar o comprimento máximo da linha em materiais.txt
    std::size_t maxLineLength = 0;
    for (const auto &material : materiais) {
        std::size_t materialLineLength = material->getTitulo().size() + material->getCodigo().size() + 25;  // 3 é para contar as vírgulas e o espaço
        maxLineLength = std::max(maxLineLength, materialLineLength);
    }
    std::cout << std::string(maxLineLength, '-') << "\n";
    for (const auto &transacao : transacoes) {
        std::cout << "Material: " << transacao->getMaterial()->getTitulo() << " (Código: " << transacao->getMaterial()->getCodigo() << ")\n";
        std::cout << transacao->obterDetalhes() << "\n";

        // Imprimir linha com tamanho igual ao máximo
        std::cout << std::string(maxLineLength, '-') << "\n";
    }
}



bool Biblioteca::existeEmprestimo(Material *material, Membro *membro) const {
  for (const auto &transacao : transacoes) {
    Emprestimo *emprestimo = dynamic_cast<Emprestimo*>(transacao);
    if (emprestimo && emprestimo->getMaterial() == material && emprestimo->getMembro() == membro) {
      return true;
    }
  }
  return false;
}


