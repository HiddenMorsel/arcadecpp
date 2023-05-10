/*
Tempo: 70 minutos.
-Fiz com a ajuda do monitor e com a dica de um colega no grupo da monitoria.
-Mesmo que fosse mais rápido verificar se um cliente já estava no cinema para fazer uma reserva usando a função procurar(), fiz usando um método que me deu mais dor de cabeça e me fez visitar o almoço com código. Mas isso foi bem produtivo, pois aprendi a criar um objeto do tipo shared_pointer para comparar e a enviar um objeto como parâmetro para uma função sem precisar criar explicitamente um objeto usando apenas {}.
Essa forma é bem útil, caso quisessemos diverenciar um cliente do outro pelo nome e telefone e não apenas pelo nome, em um caso onde por exemplo duas pessoas teriam o mesmo nome.
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <sstream>
#include<fn.hpp>

struct Cliente{
    std::string id;
    std::string fone;

public:

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
        for(int i = 0; i < (int) cadeiras.size(); i++){
        if( cadeiras[i] != nullptr && cadeiras[i]->getId() == nome) return i;
      }
      return -1;
    }

public:
    Sala(int qtd) {
      int i = 0;
      while(i < qtd){
        cadeiras.push_back(nullptr);
        i++;
      }
    }

    bool clienteExiste(Cliente c){
      std::shared_ptr<Cliente> cliente(new Cliente(c));
      for(int i = 0; i < (int) cadeiras.size(); i++){
        if( cadeiras[i] != nullptr && cadeiras[i]->getId() == cliente->getId()) return true;
      }
      return false;
    }

    bool indexExiste(int ind){
      if(ind >= 0 && ind < (int) cadeiras.size()){
        return true;
      }
      return false;
    }

    void reservar(std::string id, std::string fone, int index) {

      // if(procurar(id) >= 0){
      //   fn::write("fail: cliente ja esta no cinema");
      //    return;
      // }
      if(clienteExiste({id, fone})) {
        fn::write("fail: cliente ja esta no cinema");
        return;
      }
      else if(!indexExiste(index)){
        fn::write("fail: cadeira nao existe");
        return;
      } 
      else if(cadeiras[index] == nullptr){
        cadeiras[index] = std::make_shared<Cliente> (id, fone);
     
      } else if (cadeiras[index] != nullptr){
        fn::write("fail: cadeira ja esta ocupada");
      }
    }

    void cancelar(std::string id) {
      auto i = procurar(id);
      
      if( i >= 0) {
        cadeiras[i] = nullptr; 
        return;
      } else fn::write("fail: cliente nao esta no cinema");
    }

    std::string str() {
        auto cadeiras_str = cadeiras | fn::MAP(FNT(c, c == nullptr ? "-" : c->str()));
        return "[" + fn::join(cadeiras_str, " ") + "]";
    }
};

int main() {

  Sala sala(0);
  
  while(true){
    auto line = fn::input();
    auto args = fn::split(line, ' ');

    fn::write('$' + line);

    if(args[0] == "end"){
      break;
    } else if(args[0] == "show"){
      fn::write(sala.str());
    } else if(args[0] == "init"){
      sala = Sala( (int) +args[1] );
    } else if(args[0] == "reservar"){
      sala.reservar(args[1], args[2], (int) +args[3]);
    } else if(args[0] == "cancelar") {
      sala.cancelar(args[1]);
    } else fn::write("fail: funçao nao encontrada");
  }

}
