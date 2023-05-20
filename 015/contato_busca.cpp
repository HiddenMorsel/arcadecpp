#include <fn.hpp>
#include<vector>
#include<iomanip>
#include<algorithm>
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

class Agenda {
    std::vector<Contact> contatos;

public:
    //add contato que não existe ou adicionar fones ao contato que existe

    int findContact(std::string id) {
      for(int i = 0; i < (int) contatos.size(); i++){
        if(contatos[i].getName() == id) return i;
      }
      return -1;
    }

    void addContato(std::string name, std::vector<Fone> fones) {

      if(findContact(name) >= 0){
          for(int i = 0; i < (int) fones.size(); i++){
            contatos[findContact(name)].addFone(fones[i].getId(), fones[i].getNumber());
          }
        } 
      else {
        Contact contato = Contact(name);
        for(int i = 0; i < (int) fones.size(); i++){
            contato.addFone(fones[i].getId(), fones[i].getNumber());
      }
        contatos.push_back(contato);
      }

    }

    void rmContact(std::string name) {
      
      int indice = findContact(name);
      if(indice >= 0) contatos.erase(contatos.begin() + indice);
      
    }

    Contact * getContact(std::string id) {
      int indice = findContact(id);
      
      auto c = &contatos[indice];

      return c;
    }

    // std::vector<Contact> getContatos() {
    //     return {}; // todo
    // }

    bool static OrdemAlfabetica(Contact a, Contact b){
      return a.getName() < b.getName();
    }

    std::vector<Contact> search(std::string pattern) {
      std::vector<Contact> contatosBuscados;
      
        for(int i = 0; i < (int) contatos.size(); i++){ 
            if( contatos[i].str().find(pattern)  != std::string::npos){
            contatosBuscados.push_back(contatos[i]);
          } 
        }
      std::sort(contatosBuscados.begin(), contatosBuscados.end(), OrdemAlfabetica);
      return contatosBuscados;
    }

    std::vector<Contact> getFavorited() {
        std::vector<Contact> favoritos;
      for(int i = 0; i < (int) contatos.size(); i++){
        if(contatos[i].isFavorited()) favoritos.push_back(contatos[i]);
      }
      std::sort(favoritos.begin(), favoritos.end(), OrdemAlfabetica);
      return favoritos;
    }

   
    std::string str() {
      std::stringstream ss;

      std::sort(contatos.begin(), contatos.end(), OrdemAlfabetica);
      
      for(int i = 0; i < (int) contatos.size(); i++){
        ss << contatos[i].str() << "\n";
      }
      auto string = ss.str();
      string.pop_back();
      return string;
      
      }
      
};


std::ostream& operator<<(std::ostream& out, Fone fone      ) { return out << fone.str();    }
std::ostream& operator<<(std::ostream& out, Contact contato) { return out << contato.str(); }
std::ostream& operator<<(std::ostream& out, Agenda agenda  ) { return out << agenda.str();  }

int main() {
    Agenda agenda;
    while(true) {
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line, ' ');
        if(args[0] == "end") {
            break;
        }
        else if(args[0] == "add") {//name id:fone id:fone ...
            std::vector<Fone> fones;
            for (int i = 2; i < (int) args.size(); i++) {
                auto parts = fn::split(args[i], ':');
                fones.push_back(Fone(parts[0], parts[1]));
            }
            agenda.addContato(args[1], fones);
        }
        else if(args[0] == "show") {
            fn::write(agenda);
        }
        else if(args[0]== "rmFone") {//id index
            Contact * contato = agenda.getContact(args[1]);
            if(contato != nullptr)
                contato->rmFone((int) +args[2]);
        }
        else if(args[0] == "rm") {//id
            agenda.rmContact(args[1]);
        }
        else if(args[0] == "tfav") {//id 1 ou 0
            Contact * contato = agenda.getContact(args[1]);
            if(contato != nullptr)
                contato->toogleFavorited();
        }
        else if(args[0] == "favs") {
            agenda.getFavorited() | fn::JOIN("\n") | fn::WRITE();
        }
        else if(args[0] == "search") {//pattern
            agenda.search(args[1]) | fn::JOIN("\n") | fn::WRITE();
        }
        else{
            fn::write("fail: comando invalido");
        }
    }
}
