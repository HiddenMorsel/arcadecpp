/*
Tempo: 60 min
-Fiz tudo sozinho, desta vez nem foi preciso pedir ajuda no grupo ou ir ao almoço com código.
-Aprendi a usar a função find() no problema de validar os números. Acho que a forma como fiz a questão usando um contador pode não ter sido a melhor possível.
*/


#include <fn.hpp>
#include<vector>
#include<iomanip>
#include<iostream>
#include<string>


class Fone{
    std::string id;
    std::string number;
public:
    Fone(std::string id = "", std::string number= "") : id(id), number(number){
    }
    std::string getId() {
        return id;
    }
    std::string getNumber() {
        return number;
    }

    std::string str() {
        std::stringstream ss;
      ss << id << ":" << number;
      return ss.str();
    }   
};

class Contact{
    std::string name;
    bool favorited{false};
    std::vector<Fone> fones;
public:
    Contact(std::string name = "") : name(name){ //todo
    }

    std::string getName() {
        return name;
    }

    std::vector<Fone> getFones() {
        return fones;
    }

    bool isValid(std::string number) {
      std::string validos = "0123456789().";
      int cont{0};
        for(int i = 0; i < (int) number.size(); i++){
          if(validos.find(number[i]) != std::string::npos) cont++;
        } 
      if(cont ==  (int) number.size()) return true;
        return false;
    }

    void addFone(std::string id, std::string number) {
      if(isValid(number)) {
        fones.push_back({id, number});
        return;
      } else {
        fn::write("fail: invalid number");
        return;
      }
      
    }

    void rmFone(int index) {
      fones.erase(fones.begin() + index);
    }

    void toogleFavorited() {
      if(favorited == true) favorited = false;
      else favorited = true;
      
    }

    bool isFavorited() {
        if(favorited == true) return true;
        return false;
    }

    std::string str() {
        std::stringstream ss;
      if(isFavorited()) ss << "@ ";
      else ss <<"- ";
        ss << getName() << " [" << fn::join(fones, ", ") << "]";
      return ss.str();
  }
};

std::ostream& operator<<(std::ostream& out, Contact contato) { return out << contato.str(); }
std::ostream& operator<<(std::ostream& out, Fone fone      ) { return out << fone.str();    }

int main(){
   Contact contato;

    while(true) {
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line, ' ');

        if(args[0] == "end") {
            break;
        } else if(args[0] == "init") {//name
            contato = Contact(args[1]);
        } else if(args[0] == "show") {
            fn::write(contato);
        } else if(args[0] == "init"){
          contato = Contact(args[1]);
        } else if(args[0] == "add"){
          contato.addFone(args[1], args[2]);
        } else if(args[0] == "rm"){
          contato.rmFone((int) +args[1]);
        } else if(args[0] == "tfav"){
          contato.toogleFavorited();
        }
        else{
            fn::write("fail: comando invalido");
        }
    }
}