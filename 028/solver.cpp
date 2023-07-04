/*
Tempo: 120 min
- Inicialmente tentei fazer usando um header para declarar todos os objetos e um outro arquivo cpp para implementar e apenas usar um #include no arquivo principal, mas mesmo fazendo todos os códigos na mesma pasta o replit mandava a header para lugares misteriosos, nem eu e o monitor conseguimos descobrir como resolver isso no almoço código. 
-Algumas coisas tirei dúvidas com o monitor, como sobre a questão dos headers e algumas formas de escrever código que havia se tornado meio vago por ter passado alguns dias sem praticar. 
-O catch foi particularmente desafiante, terminei colocando a exceção dos nomes duplicados dentro dos objetos e não na main por falta de atenção, a última exceção tirei dúvida com o professor, pois fiquei enganchado em relação a onde colocar o throw.
-De resto fiz sozinho.
*/

#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<sstream>
#include<string>
#include<fn.hpp>

class Evento;
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

class Evento{
  std::string name;
  double price;
public:
  Evento(std::string name, double price) : name(name), price(price){}

  std::string getName(){
    return name;
  }

  double getPrice(){
    return price;
  }

  std::string toString(){
    std::stringstream ss;
    ss << getName() << ":"<< std::fixed << std::setprecision(2) << getPrice();
    return ss.str();
  }
};

class Venda{
  Pessoa pessoa;
  Evento evento;
  double valor;
public:
  Venda(Pessoa pessoa, Evento evento) : pessoa(pessoa), evento(evento){
    if(pessoa.getMeia() == true) {
      this-> valor = evento.getPrice() / 2;
      return;
    }
    this-> valor = evento.getPrice();
  }

  Pessoa getPessoa(){
    return pessoa;
  }

  Evento getEvento(){
    return evento;
  }

  double getValor(){
    return valor;
  }

  std::string toString(){
    std::stringstream ss;
    ss << getPessoa().getName() << ":" << getEvento().getName() << ":" << std::fixed << std::setprecision(2) << getValor();
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

  void addEvento(std::string nome, double valor) {
      try {
        if(repEvento.count(nome) == 1) throw 1;
      } catch(int i) {
        std::cout << "fail: evento " << nome << " ja existe" << "\n";
      }
      repEvento.insert({nome, {nome, valor} });
  }

  void showEvento(){
      std::string os = "[" ;
  
      for(auto& e : repEvento){
        os += e.second.toString() + ", ";
      }
  
      os.erase(os.size() - 2);
      os += "]";
  
      std::cout << os << "\n";
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

  Evento getEvento(std::string name){

      bool existe = eventoExiste(name, repEvento);
      if(existe) {
          auto it = repEvento.find(name);
          return it->second;
      } else throw std::out_of_range("fail: evento " + name + " nao existe");
     
  }
  

  void vender(std::string name, std::string evento){
    
    auto venda = Venda(getPessoa(name), getEvento(evento));
    repVendas.push_back(venda);
  }

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
        b.addEvento(args[1], +args[2]);
      } else if(args[0] == "eventos"){
        b.showEvento();
      } 
      else if(args[0] == "vender"){
        b.vender(args[1], args[2]);
      } else if(args[0] == "vendas") {
        b.showVendas();
      } else std::cout <<"fail: comando invalido!";
    } catch(std::out_of_range& oops){
      std::cout << oops.what() << std::endl;
    }
  }
  
}
