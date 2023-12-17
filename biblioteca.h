#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <vector>
#include <string>

class Material {
public:
    Material(const std::string& titulo, const std::string& codigo);
    virtual ~Material();
    virtual void exibirDetalhes() const = 0;
    virtual std::string getTitulo() const;
    virtual std::string getCodigo() const;

protected: 
    std::string titulo;
    std::string codigo;
};

class Livro : public Material {
public:
    Livro(const std::string& titulo, const std::string& codigo);
    virtual ~Livro() override = default;
    void exibirDetalhes() const override;
};

class Membro {
public:
    Membro(const std::string& nome, const std::string& id);
    virtual ~Membro() = default;
    virtual void exibirDetalhes() const;
    virtual std::string getNome() const;
    virtual std::string getId() const;

private:
    std::string nome;
    std::string id;
};

class Transacao {
public:
    Transacao(Material* material, Membro* membro);
    virtual ~Transacao();
    virtual void realizar() const = 0;
    virtual std::string obterDetalhes() const = 0;
    virtual Material* getMaterial() const;
    virtual Membro* getMembro() const;

protected:
    Material* material;
    Membro* membro;
};

class Emprestimo : public Transacao {
public:
    Emprestimo(Material* material, Membro* membro);
    ~Emprestimo() override;
    void realizar() const override;
    std::string obterDetalhes() const override;
};

class Devolucao : public Transacao {
public:
    Devolucao(Material* material, Membro* membro);
    ~Devolucao() override;
    void realizar() const override;
    std::string obterDetalhes() const override;
};

class Biblioteca {
public:
    Biblioteca();
    ~Biblioteca();
    void adicionarMaterial(Material *material, const std::string &tipo);
    void adicionarMembro(Membro* membro);
    void realizarTransacao(Transacao* transacao);
    Membro* getMembroPorIndice(std::size_t indice) const;
    const std::vector<Material*>& getMateriais() const;
    const std::vector<Membro*>& getMembros() const;

    void salvarMateriais(const std::string &nomeArquivo, const std::string &tipo) const;
    void carregarMateriais(const std::string &nomeArquivo);
    void salvarMembros(const std::string& nomeArquivo) const;
    void salvarNovoMembro(const Membro *membro) const;
    void carregarMembros(const std::string& nomeArquivo);
    void salvarHistorico(const std::string &nomeArquivo) const;
    void carregarHistorico(const std::string &nomeArquivo);
    void listarHistorico() const;
    bool existeEmprestimo(Material *material, Membro *membro) const;

private:
    std::vector<Material*> materiais;
    std::vector<Membro*> membros;
    std::vector<Transacao*> transacoes;
    std::vector<Transacao*> historico;
};

#endif // BIBLIOTECA_H
