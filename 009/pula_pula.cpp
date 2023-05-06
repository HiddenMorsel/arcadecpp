// Tempo: 80 minutos;

// -Fiz com a ajuda do professor para identificar um erro, onde o removeKid precisava de um retorno PtrKid, mas meu código só chamava a função de remover da lista. 
// -Aprendi que é importante ter cuidado para colocar o retorno de uma função, ou pode arruinar tudo.


#include <iostream>
#include <list>
#include <sstream>
#include <memory>
#include <vector>
#include <fn.hpp>
using namespace fn;

class Kid {
private:
    int age;
    std::string name;
public:
    Kid(std::string name, int age) {
        this->age = age;
        this->name = name;
    }
    int getAge() {
        return age;
    }
    std::string getName() {
        return name;
    }
    std::string str() {
        return name + ":" + std::to_string(age);
    }
};

using PtrKid = std::shared_ptr<Kid>;

std::ostream& operator<<(std::ostream& os,  Kid kid) {
    return os << kid.str();
}

std::ostream& operator<<(std::ostream& os,  PtrKid kid) {
    return os << kid->str();
}

class Trampoline {
    std::list<PtrKid> waiting;
    std::list<PtrKid> playing;

public:
   PtrKid removeFromList(std::string name, std::list<PtrKid>& lista) {
    //   // for(auto it = lista.begin(); it != lista.end(); ++it){
        
    //   // }
    //   /*for(auto it = lista.begin(); it != lista.end();){
    //     if((*it)->getName() != name){
    //       it = lista.erase(it);
    //     }else ++it;
    //   }*/
     for(auto it = lista.begin(); it != lista.end();){
       if((*it)->getName() == name){
         auto aux = (*it);
         it = lista.erase(it);  
         return aux;
        } else {
         ++it;
        }
       }
      return nullptr;
    }

    Trampoline() {
    }
    
    void arrive(PtrKid kid) {
      waiting.push_front(kid);
    }

    void enter() {
      playing.push_front(waiting.back());
      waiting.pop_back();
    }

    void leave() {
      if(playing.empty()) return;
      waiting.push_front(playing.back());
      playing.pop_back();
      
    }

    PtrKid removeKid(std::string name) {
       removeFromList(name, waiting);
       removeFromList(name, playing);  
      return nullptr;
    }
    std::string str() {
        return "["s + join(waiting,", ") + "] => [" + join(playing,", ") + "]";
    }
};

int main() {
    Trampoline tr;
    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if      (args[0] == "end"   ) { break;                                                     }
        else if (args[0] == "arrive") { tr.arrive(std::make_shared<Kid>(args[1], (int) +args[2])); }
        else if (args[0] == "enter" ) { tr.enter();                                                }
        else if (args[0] == "leave" ) { tr.leave();                                                }
        else if (args[0] == "remove") { tr.removeKid(args[1]);                                     }
        else if (args[0] == "show"  ) { write(tr.str());                                           }
        else                          { write("fail: invalid command");                            }
    }
}