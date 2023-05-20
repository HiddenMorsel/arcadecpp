#include <fn.hpp>


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
    // bool isValid(std::string number) {
    //   if(number <= '0' && number <='9');
    // }
      
    std::string str() {
        std::stringstream ss;
      ss << id << ":" << number;
    }   
};

class Contact{
    std::string name;
    bool favorited;
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

    void addFone(std::string id, std::string number) {
    }

    void rmFone(int index) {
    }

    void toogleFavorited() {
    }

    bool isFavorited() {
        return {}; // todo
    }

    std::string str() {
        return {}; // todo
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
        }
        else if(args[0] == "init") {//name
            contato = Contact(args[1]);
        } else if(args[0] == "show") {
            fn::write(contato);
        }
        else{
            fn::write("fail: comando invalido");
        }
    }
}