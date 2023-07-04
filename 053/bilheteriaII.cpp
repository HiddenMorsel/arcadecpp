#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<sstream>
#include<string>
#include<fn.hpp>

class Evento;
class Setor;
class Pessoa;
class Venda;

class Pessoa{
  std::string name;
  bool meia;
public:
  Pessoa(std::string name, std::string meia){
  
    this->name = name;
    
    if(meia == "inteira"){
         this->meia = false;
    } else if(meia == "meia"){
        this->meia = true;
      }
    
  }

  std::string getName(){
      return name;
  }
  bool getMeia(){
    return meia;
  }

  std::string toString(){
    std::stringstream ss;
    ss << getName() << ":" << (getMeia() ? "meia" : "inteira") ;
    return ss.str();
  }
};

class Setor{
  std::string evento;
  std::string name;
  double preco;

public:
  Setor(std::string evento, std::string name, double preco) : evento(evento), name(name), preco(preco){}

  std::string getName() {
    return name;
  }

  std::string getEvento() {
    return evento;
  }

  double getPreco() {
    return preco;
  }

std::string toString() {
  std::stringstream ss; 
  ss << getName() << ":" << std::fixed << std::setprecision(2) << getPreco();
  return ss.str();
   
}
};

class Evento{
  std::string name;
  std::map<std::string, Setor> setores;
public:
  Evento(std::string name, std::map<std::string, Setor> setores ) : name(name), setores(setores) {}

  std::string getName(){
    return name;
  }

  std::map<std::string, Setor> getSetores() {
    return setores; 
  }

  void addSetor(std::string name, double price) {
    if(setores.count(name) == 1) throw std::out_of_range ("fail setor: " + name +" já existe\n");

    getSetores().insert({name, {name, getName(), price}});
  } 

  std::string getSetor() {
    std::string os;
    
    for(auto& s : setores){
      os += s.second.toString() + ", ";
    }
    
    return os;
  }

};

class Venda{
  Pessoa pessoa;
  Setor setor;
  double valor;
public:
  Venda(Pessoa pessoa, Setor setor) : pessoa(pessoa), setor(setor){
    if(pessoa.getMeia() == true) {
      this-> valor = setor.getPreco() / 2;
      return;
    }
    this-> valor = setor.getPreco();
  }

  Pessoa getPessoa(){
    return pessoa;
  }

  Setor getSetor(){
    return setor;
  }

  double getValor(){
    return valor;
  }

  std::string toString(){
    std::stringstream ss;
    ss << getPessoa().getName() << ":" << getSetor().getName() << ":" << std::fixed << std::setprecision(2) << getValor();
    return ss.str();
  }

};

class Bilheteria{
  
  std::vector<Venda> repVendas;
  std::map<std::string, Pessoa> repPessoas;
  std::map<std::string, Evento> repEvento;

public:
  Bilheteria(std::vector<Venda> = {{}, }) {}


  void showPessoas(){
      std::string output;
      output += "[";
  
      for(auto& e : repPessoas){
        output += e.second.toString() + ", ";
      }
  
      output.erase(output.size() - 2);
  
      output += "]";
  
      std::cout << output << "\n";
  }

  void addPessoa(std::string nome, std::string meia){
      try{
        if(repPessoas.count(nome) == 1) throw 1;
      } catch(int i){
        std::cout << "fail: pessoa " << nome << " ja existe" << "\n";
      }
      auto pessoa = Pessoa(nome, meia);
      repPessoas.insert({nome, pessoa});
  }

  void addEvento(std::string nome) {
      try {
        if(repEvento.count(nome) == 1) throw 1;
      } catch(int i) {
        std::cout << "fail: evento " << nome << " ja existe" << "\n";
      }
      repEvento.insert({nome , {nome, {{}, }} }); 
  }

  bool pessoaExiste(std::string& name, std::map<std::string, Pessoa>& repPessoas){
    auto existe = repPessoas.find(name);
    if(existe != repPessoas.end()) {
     return true;
    } else return false;
  }

  bool eventoExiste(std::string& name, std::map<std::string, Evento>& repEvento){
     auto existe = repEvento.find(name);
    if(existe != repEvento.end()) {
     return true;
    } else return false;
  }

  Pessoa getPessoa(std::string name){
  
      bool fulanoExiste = pessoaExiste(name, repPessoas);
      if(fulanoExiste) {
          auto it = repPessoas.find(name);
          return it->second;
      }  else throw std::out_of_range("fail: pessoa " + name + " nao existe");
  }

  std::string getEvento(std::string name){

      bool existe = eventoExiste(name, repEvento);
      if(existe) {
          auto it = repEvento.find(name);
          return it->second.getName();
      } else throw std::out_of_range("fail: evento " + name + " nao existe");
  }

   void addSetor(std::string nEvento, std::string setor, double price) {
    if(eventoExiste(nEvento, repEvento)) {
      auto it = repEvento.find(nEvento); 
      it->second.addSetor(setor, price);
      return;
    } else throw std::out_of_range("fail: evento " + nEvento + " nao existe");
  }

  
  void showEvento(){
      std::string os;
  
      for(auto& e : repEvento){
        os += e.second.getName() +" [" + e.second.getSetor() +"]\n";
      }
  
      os.erase(os.size() - 1);
    
      std::cout << os << "\n";
  }

  // void vender(std::string name, std::string evento, std::string setor, double valor){
    
  //   auto venda = Venda(getPessoa(name), getEvento(evento).getSetor(setor), valor);
  //   repVendas.push_back(venda);
  // }

  void showVendas(){
    std::string os = "[";
    
    for(auto& e : repVendas){
      os += e.toString() + ", ";
    }
    os.erase(os.size() - 2);
    os += "]";
  
    std::cout << os << "\n";
  }
};

int main(){
  Bilheteria b;

  while(true) {
    std::string line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line, ' ');

    try{
      if(args[0] == "end"){
        break;
      } else if(args[0]  == "addPessoa") {
        b.addPessoa({args[1]}, {args[2]});
      } else if(args[0] == "pessoas"){
        b.showPessoas();
      } else if(args[0] == "addEvento"){
        b.addEvento(args[1]);
      } else if(args[0] == "eventos"){
        b.showEvento();
      } else if(args[0] == "addSetor") {
        b.addSetor(args[1], args[2], +args[3]);
      }
      // else if(args[0] == "vender"){
      //   b.vender(args[1], args[2]);
      // } 
      else if(args[0] == "vendas") {
        b.showVendas();
      } else std::cout <<"fail: comando invalido!";
    } catch(std::out_of_range& oops){
      std::cout << oops.what() << std::endl;
    }
  }
  
}
