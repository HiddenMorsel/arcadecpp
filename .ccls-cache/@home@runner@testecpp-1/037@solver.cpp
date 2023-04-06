#include <aux.hpp>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Pessoa {
  std::string nome;

public:
  Pessoa(std::string nome) { this->nome = nome; }
  std::string getNome() const { return nome; }
  std::string str() const { return nome; }
};
std::ostream &operator<<(std::ostream &os, const Pessoa &p) {
  return (os << p.str());
}

using PtrPessoa = std::shared_ptr<Pessoa>;

class Mercantil {
  std::vector<PtrPessoa> caixas;  // caixas do supermercado
  std::list<PtrPessoa> esperando; // lista de clientes esperando

  // verifica se o indice é válido para acessar os caixas
  bool validarIndice(int indice) {
    if (indice < 0 || indice >= (int)this->caixas.size())
      return false;
    return true;
  }

public:
  Mercantil(int qtd_caixas) : caixas(qtd_caixas, nullptr) {}

  void chegar(const std::shared_ptr<Pessoa> &person) {
    this->esperando.push_back(person);
  }

  // 1. verifica se o indice é válido
  // 2. verifica se o caixa chamado está vazio
  // 3. verifica se existe alguém na lista de espera
  // 4. O primeiro cliente da lista de espera é movido para este caixa
  bool chamarNoCaixa(int indice) {
    if (this->veri  )
    this->caixas[indice] = this->esperando.front();
    this->esperando.pop_front();
    return true;
  }
  // 1. verifica se o indice é válido
  // 2. verifica se este caixa possui um cliente
  // Se tudo estiver ok, o cliente é removido do caixa e o caixa volta a ser
  // null para indicar que está vazio
  std::shared_ptr<Pessoa> finalizar(int indice) {
    return std::exchange(this->caixas[indice], nullptr);
  }

  std::string str() const {
    std::stringstream os;
    os << "Caixas: |";
    for (int i = 0; i < (int)this->caixas.size(); i++) {
      auto &caixa = this->caixas[i];
      os << " " << i << ":";
      if (caixa != nullptr)
        os << std::setw(5) << *caixa;
      else
        os << "-----";
      os << " |";
    }
    os << "\nEspera: "
       << aux::fmt(aux::map(this->esperando, [](auto x) { return *x; }), ", ");
    return os.str();
  }
};

std::ostream &operator<<(std::ostream &os, const Mercantil &b) {
  return (os << b.str());
}

int main() {
  aux::Chain chain;
  aux::Param par;

  Mercantil bank(0);

  chain["init"] = [&]() { bank = Mercantil(aux::to<int>(par[1])); };
  chain["call"] = [&]() { bank.chamarNoCaixa(aux::to<int>(par[1])); };
  chain["finish"] = [&]() { bank.finalizar(aux::to<int>(par[1])); };
  chain["arrive"] = [&]() { bank.chegar(std::make_shared<Pessoa>(par[1])); };
  chain["show"] = [&]() { aux::show << bank; };

  aux::execute(chain, par);
}
