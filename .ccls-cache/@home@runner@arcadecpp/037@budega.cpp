#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <fn.hpp>

class Pessoa{
  std::string nome;

public:
 Pessoa(std::string nome) {  
    }
    std::string getNome() {
        return nome; 
    }
    std::string str() {
      std::stringstream ss;
      ss<< nome;
      return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Pessoa p) {
    return (os << p.str());
}

class Mercantil{
std::vector<std::shared_ptr<Pessoa>> caixas;
std::list  <std::shared_ptr<Pessoa>> esperando;

bool validarIndice(int indice) {
        return {}; // todo
    }

public:
Mercantil(int qtd_caixas) { 
        for(auto i = 0; i < qtd_caixas; i ++){
          caixas.push_back(nullptr);
        }
    }
    
    void arrive(  std::shared_ptr<Pessoa> person) {
      esperando.emplace_back( person );
    }

    bool call(int indice) {
        
    }
    
    std::shared_ptr<Pessoa> finish(int indice) {
        return {}; // todo
    }

    std::string str()  {
     auto caixas_str = caixas | fn::MAP(FNT(c, c == nullptr ? "-----" : c->getNome()));
        return "Caixas: " + fn::tostr(caixas_str) + "\n" + "Espera: " + fn::tostr(esperando);
    }
        
};

std::ostream& operator<<(std::ostream& os, Mercantil b) {
    return (os << b.str());
}

int main(){
  Mercantil bank(0);
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if      (args[0] == "end"   ) { break;                                          }
        else if (args[0] == "init"  ) { bank = Mercantil(+args[1]);                     }
       else if (args[0] == "show"  ) { fn::write(bank);                                } 
        else if (args[0] == "arrive") { bank.arrive(std::make_shared<Pessoa>(args[1])); }
      }
}
