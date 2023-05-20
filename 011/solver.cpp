/*
Tempo: 120 minutos.
-Fiz as funções para printar a informação com o exemplo que o professor havia dado em sala de aula.
-No teste de inicialização meu código não estava dando a quebra de linha no momento certo, então pedi ajuda ao monitor, a forma que fizemos com a condicional no laço creio que não seja a mais eficiente, mas foi o que pensamos na hora.
-O resto do código foi feito outro dia, fiz tudo sozinho. Implementar as funções não foi muito difícil, mas tentei fazer tudo com o máximo de atenção.
-Aprendi mais a respeito de formatação de saída com stringstream e como escrever a própria main. Além de ter praticado a coordenação entre classes.
*/
#include <iostream>
#include <iomanip>
#include <list>
#include <sstream>
#include <memory>
#include <vector>
#include <fn.hpp>

class Slot{
  std::string name;
  int quantity;
  float price;
  

public:

  Slot(std::string name, int quantity, float price) : name(name), quantity(quantity), price(price){
  }

  std::string getName(){
    return name;
  }

  float getPrice(){
    return price;
  }

  int getQuantity(){
    return quantity;
  }

  void setName(std::string name){
    this->name = name;
  }

  void setPrice(float price){
    this->price = price;
  }

  void setQuantity(int quantity){
    this->quantity = quantity;
  }

  std::string toStr(){
    std::stringstream ss;
    ss << "[" << std::setw(8) << std::setfill(' ') << name << " : " 
       << quantity << " U : " << std::fixed << std::setprecision(2) << price << " RS]"; //padding;
    return ss.str();
    
  }
  
};

class VendingMachine{
  std::vector<Slot> slots;
  float profit{0};
  float cash{0};
  int capacity{0};

public:
  
  VendingMachine(int qtd_slots) {
    for(int i = 0; i < qtd_slots; i++){
      slots.push_back({"empty", 0, 0});
    }
    this->capacity = qtd_slots;
    }

  Slot getSlot(int index){
    return slots[index];
  }

  bool validarIndex(int index){
    if(index >= 0 && index < (int) slots.size()) return true;
    else return false;
  }
  

  void setSlot(int index, Slot slot){
    if(!validarIndex(index)) {
      fn::write("fail: indice nao existe");
      return;
    }
    slots[index] = slot;
  }

   void clearSlot(int index){
    if(!validarIndex(index)) {
      fn::write("fail: indice nao existe");
      return;
    }
    slots[index].setName("empty");
    slots[index].setQuantity(0);
    slots[index].setPrice(0);
   }

  void insertCash(float cash){
    this->cash += cash;
  }

  float getCash(){
    return cash;
  }

  float withdrawCash(){
    float change = getCash() - profit;
    return change;
  }

  std::string troco(){
    std::stringstream ss;
    ss << "voce recebeu " <<  std::fixed << std::setprecision(2) << withdrawCash();
    ss << " RS";
    cash = 0;
    return ss.str();
  }

  void buyItem(int index){
    if(!validarIndex(index)){
      fn::write("fail: indice nao existe");
      return;
    } else if(cash < slots[index].getPrice()) {
      fn::write("fail: saldo insuficiente");
      return;
    } else if(slots[index].getQuantity() == 0){
      fn::write("fail: espiral sem produtos");
      return;
    }

    cash -= slots[index].getPrice();
    slots[index].setQuantity (slots[index].getQuantity() - 1);
    fn::write("voce comprou um " + slots[index].getName());
     
  }
  
  
  std::string toStr(){
    std::stringstream ss;
    ss << "saldo: " << std::fixed << std::setprecision(2)<< cash <<"\n";
    // for(int i = 0; i < capacity; i++){
    //   if(i != capacity - 1) ss << i << " " << slots[i].toStr() << "\n";
    //   else if(i == capacity - 1) ss << i << " " << slots[i].toStr();
    // }

    // return ss.str();

    for(int i = 0; i < capacity; i++){
       ss << i << " " << slots[i].toStr() << "\n";
    }
    auto string = ss.str();
    string.pop_back();
    return string;
  }
};

int main(){
  VendingMachine machine(0);

      while(true){
        auto line = fn::input();
        auto args = fn::split(line, ' ');

        fn::write('$' + line);

        if (args[0] == "end") {
            break;
        } else if (args[0] == "init") {
          machine = VendingMachine( (int) +args[1]);
        } else if (args[0] == "show") {
          fn::write(machine.toStr());
        } else if(args[0] == "set"){
          Slot slot = Slot(args[2],(int) +args[3], (float) +args[4] );
          machine.setSlot((int) +args[1], slot);
        } else if(args[0] == "limpar"){
          machine.clearSlot((int) +args[1]);
        } else if(args[0] == "dinheiro"){
          machine.insertCash((int) +args[1]);
        } else if(args[0] == "troco"){
          fn::write(machine.troco());
        } else if(args[0] == "comprar"){
          machine.buyItem((int) +args[1]);
        } else fn::write("fail: comando invalido");
    }
}