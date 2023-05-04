/*
Tempo: 50 minutos
-Aprendi que é preciso ficar atento para saber quando imprimir uma saída ou quando é necessário apenas retornar um valor.
-Fiz tudo sozinho, apenas com a sugestão de um monitor no grupo e do professor a respeito de um caso de testes que estava errado(get coins).
  */

#include <fn.hpp>
#include <utility>
#include<iomanip>

class Coin {
    float value;
    int volume;
    std::string label;

    Coin(double value, int volume, std::string label) :
        value(value), volume(volume), label(label) {
    }
public:
    const static Coin C10;
    const static Coin C25;
    const static Coin C50;
    const static Coin C100;

    float getValue() const { 
        return value; 
    }
    int getVolume() const { 
        return volume; 
    }
    std::string getLabel() const { 
        return label; 
    }
};

const Coin Coin::C10 {0.10, 1, "C10"};
const Coin Coin::C25 {0.25, 2, "C25"};
const Coin Coin::C50 {0.50, 3, "C50"};
const Coin Coin::C100 {1.00, 4, "C100"};


class Item {
    std::string label;
    int volume;
public:
    Item(std::string label, int volume) : label(label), volume(volume) {
    
    }
    int getVolume() const {
        return volume;
    }
    std::string getLabel() const {
        return label;
    }
    void setVolume(int volume) {
      this->volume = volume;
    }
    void setLabel(std::string label) {
      this->label = label;
    }
    std::string str() const {
        return {}; // todo
    }
};

std::ostream& operator<<(std::ostream& os, const Item& item) {
    return os << item.str();
}

class Pig {
    std::vector<std::string> itens;
    double value {0};
    int volume {0};
    int volumeMax {0};
    bool broken {false};

public:
    Pig(int volumeMax) {
        this->volumeMax = volumeMax;
    }

    bool breakPig() {
        if(!broken){
            broken = true;
            this->volume = 0;
            return broken;
        }
        return broken = false;
    }

    void addCoin(Coin coin) {
        if(broken) {
          fn::write("fail: the pig is broken");
          return;
        } if(this->volume + coin.getVolume() > volumeMax){
        fn::write("fail: the pig is full");
          return;
       }
  
        this->value += coin.getValue();
        this->volume += coin.getVolume();
        
    }

    void addItem(Item item) {
      if(broken) {
          fn::write("fail: the pig is broken");
          return;
        }
      if(this->volume + item.getVolume() > volumeMax){
        fn::write("fail: the pig is full");
          return;
       }
      itens.push_back(item.getLabel());
        
      this->volume += item.getVolume();
      

    }

    double getCoins() {
        if(!broken) {
          fn::write("fail: you must break the pig first");
         return 0;
        }
        else {
        double valueRetornar = value;
         value = 0;
          return valueRetornar;
          
        }
                    
    }

    std::string getItems() {
        if(!broken) {
          fn::write("fail: you must break the pig first");
          return "[]";
        } else {
            std::vector<std::string> itensCopy;
            itensCopy = itens;
            this->itens.clear();
            std::stringstream ss;
            ss << "[";
            for(int i = 0; i < (int)itensCopy.size(); i ++){
            ss << itensCopy[i];
            if(i >= 0 && i < (int)itensCopy.size()-1) ss <<", ";
            }
            ss <<"]";
            return ss.str();
            }
          }
    //return fn::write("[" + fn::join(itensCopy, ", ") + "]");
                //}

    std::string str() const {
   return fn::format( "[" + fn::join(itens, ", ") + "] " + ": " + "{%0.2f}$" + " : " + std::to_string(volume) + "/" + std::to_string(volumeMax) + " : {}"  ,value, (!broken) ? "unbroken" : "broken" );
}
};

std::ostream& operator<<(std::ostream& os, const Pig& pig) {
    return os << pig.str();
}


int main() {

    Pig pig(0);
    while (true) {
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line);

        if      (args[0] == "end"    ) { break; }
        else if (args[0] == "addCoin") { 
            if      (args[1] == "10" ) pig.addCoin(Coin::C10);
            else if (args[1] == "25" ) pig.addCoin(Coin::C25);
            else if (args[1] == "50" ) pig.addCoin(Coin::C50);
            else if (args[1] == "100") pig.addCoin(Coin::C100);
        }
        else if (args[0] == "init"    ) { pig = Pig( (int) +(args[1]));                 }
        else if (args[0] == "addItem" ) { pig.addItem(Item(args[1], (int) +(args[2]))); }
        else if (args[0] == "break"   ) { pig.breakPig();                               }
        else if (args[0] == "getCoins") { fn::write(fn::tostr(pig.getCoins(), "%.2f")); }
        else if (args[0] == "getItems") { fn::write(pig.getItems());                    }
        else if (args[0] == "show"    ) { fn::write(pig);                               }
        else                            { fn::write("fail: invalid command"); }
    }
}