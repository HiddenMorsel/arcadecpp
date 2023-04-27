#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <sstream>
#include <aux.hpp>
#include<fn.hpp>

struct Cliente{
    std::string id;
    std::string fone;

    Cliente(std::string id = "", std::string fone = "") {
        this->id = id;
        this->fone = fone;
    }

    std::string getFone(){
      return fone;
    }

    std::string getId(){
      return id;
    }
    std::string str() {
        std::stringstream ss;
        ss << this->id << ":" << this->fone;
        return ss.str();
    }

};

std::ostream& operator<<(std::ostream& os, Cliente c) {
    return os << c.str();
}



class Sala{
    std::vector<std::shared_ptr<Cliente>> cadeiras;

    int procurar(std::string nome) {
      for(auto i = 0; i < cadeiras.size(); i++){
        if(cadeiras[i]->id == nome){
          return i;
        }
      }
        return -1;
    }

    bool verificarIndice(int indice){
      if(indice <= cadeiras.size() - 1){
        return true;
      }
        return false; // todo
    }
    

public:
    Sala(int qtd) {
      if(!cadeiras.empty()) cadeiras.clear();
      for(int i = 0; i < qtd; i++){
        cadeiras.push_back(nullptr);
      }
    }


    void reservar(std::string id, std::string fone, int ind) {
      if(verificarIndice(ind)){
        cadeiras[ind]->id = id; 
        cadeiras[ind]->fone = fone; 
        return;
      } 
      fn::write("tal cadeira nao existe");
      return;
    }

    void cancelar(std::string id) {
      for(long unsigned int i = 0; i < cadeiras.size(); i++){
        if(cadeiras[i]->id == id){
          cadeiras[i] = nullptr;
        }
      }
    }

    std::string str() {
      std::stringstream ss;
      ss << cadeiras;
      return ss.str();
    }
};

int main() {
    aux::Chain chain;
    aux::Param param;
    Sala sala(0);
  
    chain["init"]     = [&]() { sala = Sala(aux::to<int>(param[1])); };
    chain["reservar"] = [&]() { sala.reservar(param[1], param[2], aux::to<int>(param[3])); };
    chain["cancelar"] = [&]() { sala.cancelar(param[1]); };
    chain["show"]     = [&]() { std::cout << sala.str() << std::endl; };
    aux::execute(chain, param);
}