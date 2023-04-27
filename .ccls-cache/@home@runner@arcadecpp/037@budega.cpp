/*
Tempo: 40 min
-Na primeira vez que tentei fazer a questão, não progredi nada porque acho que na hora de copiar os parâmetros do solver alguma coisa estava fora de lugar e não conseguia usar o esperando.push_back(p).
-Analisando com o monitor no Almoço com Código, decidimos que seria uma boa ideia começar do zero copiando logo todo o template do Solver.
-Aprendi que quando se usa com shared_ptr e com os templates do string stream um erro pode ser fatal.
  */
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <fn.hpp>

class Pessoa {
    std::string nome;
public:
    Pessoa(std::string nome) { 
      this->nome = nome;
    }
    std::string getNome() const {
        return nome;
    }
    std::string str() const {
      std::stringstream ss;
      ss << nome;
        return ss.str();
    }
};
std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
    return (os << p.str());
}

class Mercantil {
    std::vector<std::shared_ptr<Pessoa>> caixas; 
    std::list  <std::shared_ptr<Pessoa>> esperando; 

    bool validarIndice(int indice) {
      if(indice <= caixas.size() - 1){
        return true;
      }
        return false; // todo
    }

public:
    Mercantil(int qtd_caixas) {
      for(int i = 0; i < qtd_caixas; i++){
      caixas.push_back(nullptr);
    }
    }
    
    void chegar(const std::shared_ptr<Pessoa>& person) {
      esperando.push_back(person);
    }

    bool chamarNoCaixa(int indice) {
        if(caixas[indice] == nullptr){
          if (esperando.empty()) {
                std::cout<<"fail: sem clientes"<<"\n";
                return false;
            }
          caixas[indice] = esperando.front();
          esperando.pop_front();
          return true;
        }else if(!validarIndice(indice)){ 
          fn::write("fail: caixa inexistente");
            return false;
        }else if(caixas[indice] != nullptr){
            std::cout<<"fail: caixa ocupado"<<"\n";
            return false;
        }
        return false;
        
      }
    
    
    bool finalizar(int indice) {
        if(!validarIndice(indice)){
            fn::write("fail: caixa inexistente");
          return false;
        }else if (caixas[indice] == nullptr) {
            std::cout<<"fail: caixa vazio"<<"\n";
          return false;
        }
         else if(caixas[indice] != nullptr){
            caixas[indice] = nullptr;
          return true;
        }
    }

    std::string str() const {
        auto caixas_str = caixas | fn::MAP(FNT(c, c == nullptr ? "-----" : c->getNome()));
        return "Caixas: " + fn::tostr(caixas_str) + "\n" + "Espera: " + fn::tostr(esperando);
    }
};

std::ostream& operator<<(std::ostream& os, const Mercantil& b) {
    return (os << b.str());
}

int main() {
    Mercantil bank(0);
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if      (args[0] == "end"   ) { break;                                          }
        else if (args[0] == "init"  ) { bank = Mercantil(+args[1]);                     }
        else if (args[0] == "call"  ) { bank.chamarNoCaixa(+args[1]);                   }
        else if (args[0] == "finish") { bank.finalizar(+args[1]);                       }
        else if (args[0] == "arrive") { bank.chegar(std::make_shared<Pessoa>(args[1])); }
        else if (args[0] == "show"  ) { fn::write(bank);                                }
        else                          { fn::write("fail: comando invalido");            }
        
    }
}
