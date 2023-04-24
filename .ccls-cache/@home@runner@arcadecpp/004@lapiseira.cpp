#include<iostream>
#include <iomanip>
#include<memory>
#include<sstream>
#include<fn.hpp>

class Lead{
  float thickness{0};
  std::string hardness;
  int size{0};

public:
  Lead(float thickness, std::string hardness, int size){
    this->thickness = thickness;
    this->hardness = hardness;
    this->size = size;
  }

  int usagePerSheet(){
    if(hardness == "HB"){
      return 1;
    } else if(hardness == "2B"){
      return 2;
    } else if(hardness == "4B"){
      return 4;
    }else if(hardness == "6B"){
      return 6;
    }
    
    
  }

  std::string getHardness(){
    return hardness;
  }

  int getSize(){
    return size;
  }

  float getThickness(){
    return thickness;
  }

  void setSize(int size){
    this-> size = size;
   }

  std::string str() const {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) 
           << thickness << ":" << hardness << ":" << size;
        return ss.str();
    }
  
};

std::ostream& operator<<(std::ostream& ss, Lead grafite) {
    return ss << grafite.str();
}

struct Pencil{
float thickness{0};
std::shared_ptr<Lead> tip{nullptr};

public:
  Pencil(float thickness = 0.0){
    this->thickness = thickness;
    
  }

  bool hasGrafite(){
    if(tip != nullptr) return true;
    else return false;
  }

  void insert( std::shared_ptr<Lead> tip){
    if(!hasGrafite()){
      if(tip->getThickness() != thickness){
        fn::write("fail: calibre incompativel");
        return;
      }
      this->tip = tip;
      return;
    }
    fn::write("fail: ja existe grafite");
    
  }

  std::shared_ptr<Lead> remove(){
    auto aux = this->tip;
    this->tip = nullptr;
    return aux;
  }
  void writePage(){
    if(!hasGrafite()) {
      fn::write("fail: nao existe grafite");
      return;
    }
    if(tip->getSize() > 10){
      if(tip->getSize() - tip->usagePerSheet() < 10){
        fn::write("fail: folha incompleta");
        tip->setSize(10);
      } 
      if(tip->getSize() - tip->usagePerSheet() == 10){
        fn::write("fail: tamanho insuficiente");
        tip->setSize(tip->getSize());
      } 
      tip->setSize(tip->getSize() - tip->usagePerSheet());
    }
    
    
  }

  std::string str() {
        std::stringstream ss;
        ss << "calibre: " << thickness << ", grafite: ";
        if (tip != nullptr)
            ss << "[" << *tip << "]";
        else
            ss << "null";
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Pencil l) {
    return os << l.str();
}

int main(){
  Pencil pencil;
  
  while(true){
        auto line = fn::input();
        fn::write("$" + line);
        auto args = fn::split(line);

        if (args[0] == "end" ) { 
          break;                                                      }
        else if (args[0] == "show") { 
          fn::write(pencil);                                          }
        else if (args[0] == "init"  ) { 
          pencil = Pencil( + args[1]);                           } 
        else if (args[0] == "insert"  ) { 
          auto thickness = (float) + args[1];
          auto hardness= args[2];
          auto size = (int) +args[3];
          auto grafite = std::make_shared<Lead> (thickness, hardness, size);
          pencil.insert(grafite);
          //make_shared<Lead>(+args[1], args[2], (int) +args[3]);     
        } else if (args[0] == "remove") { 
          pencil.remove();                                                  } else if (args[0] == "write" ) { 
          pencil.writePage();                                               }
  }
}