#include "biblioteca.h"
#include <cstdlib>
#include <iostream>

// Função para limpar o console
void limparConsole() {
    std::cout << "\033[2J\033[H"; // Código de escape ANSI para limpar a tela
}

int main() {
  // Criar uma instância de Biblioteca
  Biblioteca biblioteca;

  int escolha;

  do {
    // Exibindo o menu
    std::cout << "\n============= MENU =============\n";
    std::cout << "[1] - Cadastrar um novo material\n";
    std::cout << "[2] - Cadastrar um novo membro\n";
    std::cout << "[3] - Listar materiais\n";
    std::cout << "[4] - Listar membros\n";
    std::cout << "[5] - Realizar transação\n";
    std::cout << "[6] - Listar transações\n";
    std::cout << "[0] - Sair\n";
    std::cout << "============= FIM =============\n";
    std::cout << "Escolha: ";
    std::cin >> escolha;

    switch (escolha) {
    case 1: {
      // Cadastrar um novo material
      std::string titulo, codigo;
      std::cout << "Informe o título do material: ";
      std::cin.ignore();
      std::getline(std::cin, titulo);
      std::cout << "Informe o código do material: ";
      std::getline(std::cin, codigo);

      Material *novoMaterial = new Livro(titulo, codigo);
      biblioteca.adicionarMaterial(novoMaterial, "Livro,");
      limparConsole();
      std::cout << "Material cadastrado com sucesso!\n";
      break;
    }
    case 2: {
      // Cadastrar um novo membro
      std::string nome, id;
      std::cout << "Informe o nome do membro: ";
      std::cin.ignore();
      std::getline(std::cin, nome);
      std::cout << "Informe o ID do membro: ";
      std::getline(std::cin, id);

      Membro *novoMembro = new Membro(nome, id);
      biblioteca.adicionarMembro(novoMembro);
      limparConsole();
      std::cout << "Membro cadastrado com sucesso!\n";
      break;
    }
    case 3: {
      // Listar materiais
      limparConsole();
      std::cout << "\nMateriais:\n";
      for (const auto &material : biblioteca.getMateriais()) {
        std::cout << std::string(75, '-') << "\n";
        material->exibirDetalhes();
      }
      std::cout << std::string(75, '-') << "\n";
      break;
      }
    case 4: {
      // Listar membros
      limparConsole();
      std::cout << "\nMembros:\n";
      for (const auto &membro : biblioteca.getMembros()) {
        std::cout << std::string(50, '-') << "\n";
        membro->exibirDetalhes();
      }
      std::cout << std::string(75, '-') << "\n";
      break;
      }
    case 5: {
      limparConsole();
      // Realizar transação
      int tipoTransacao;
      std::cout
          << "Escolha o tipo de transação (1. Empréstimo / 2. Devolução): ";
      std::cin >> tipoTransacao;

      if (tipoTransacao == 1 || tipoTransacao == 2) {
        // Listar materiais
        limparConsole();
        std::cout << "Materiais disponíveis:\n";
        const auto &materiais = biblioteca.getMateriais();
        for (std::size_t i = 0; i < materiais.size(); ++i) {
          std::cout <<"["<< i + 1 << "] - ";
          materiais[i]->exibirDetalhes();
        }
        std::size_t indiceMaterial, indiceMembro;
        std::cout << "\nInforme o número do material: ";
        std::cin >> indiceMaterial;
        
        // Listar membros
        std::cout << "\nMembros disponíveis:\n";
        const auto &membros = biblioteca.getMembros();
        for (std::size_t i = 0; i < membros.size(); ++i) {
          std::cout <<"["<< i + 1 << "] - ";
          membros[i]->exibirDetalhes();
        }
        std::cout << "Informe o número do membro: ";
        std::cin >> indiceMembro;

        if (indiceMaterial >= 1 && indiceMaterial <= materiais.size() &&
            indiceMembro >= 1 && indiceMembro <= membros.size()) { //Verifica se os indices estão dentro de intervalos válidos
          // Ajustar índices para correspondência interna
          --indiceMaterial;
          --indiceMembro;

          Material *material = materiais[indiceMaterial];
          Membro *membro = membros[indiceMembro];

          Transacao *transacao;
          if (tipoTransacao == 1) {
            transacao = new Emprestimo(material, membro);
          } else {
            transacao = new Devolucao(material, membro);
          }

          biblioteca.realizarTransacao(transacao);
        } else {
          std::cerr << "Números de material ou membro inválidos.\n";
        }
      } else {
        std::cerr << "Tipo de transação inválido.\n";
      }
      break;
    }
    case 6: {
      limparConsole();
      biblioteca.listarHistorico();
      break;
      }
    case 0:
      break;
    default:
      std::cerr << "Opção inválida. Tente novamente.\n";
      break;
    }

  } while (escolha != 0);

  return 0;
}
