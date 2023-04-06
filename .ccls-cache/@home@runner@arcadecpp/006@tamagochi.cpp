/*
-Tempo: 80 minutos.
-Demorou um tempinho para dar uma desenferrujada e começar a programar.
-Tentei ver o vídeo para ajudar a desenganchar, mas desisti.
-Olhei novamente para a questão do relógio e para o solver.cpp para refrescar a memória a respeito de gets e sets.
-Com exceção da main e de algumas partes baseadas no solver, fiz os código sozinho.
*/
#include<iostream>
#include<fn.hpp>

class Pet{
  private: 
  bool alive{true};
  int clean{0};
  int cleanMax{0};
  int energy{0};
  int energyMax{0};
  int hungry{0};
  int hungryMax{0};
  int age{0};
  int diamonds{0};

  bool testAlive(){
    if(alive) return true;
    else fn::write("fail: pet esta morto"); 
    return false;
  }

void setClean(int value){
    if(value <= 0) {
      clean = 0;
      fn::write("fail: pet morreu de sujeira");
      alive = false;
    }else if(value >= cleanMax){
      clean = cleanMax;
    }else clean = value;
  }

  void setHungry(int value){
    if(value <= 0) {
      hungry = 0;
      fn::write("fail: pet morreu de fome");
      alive = false;
    } else if(value >= hungryMax) {
      hungry = hungryMax;
    } else hungry = value;
  }

  void setEnergy(int value){
    if(value <= 0) {
      energy = 0;
      fn::write("fail: pet morreu de fraqueza");
      alive = false;
    } else if(value >= energyMax) {
      energy = energyMax;
    } else energy = value;
  }

  public:
  void pet(int energyMax, int hungryMax, int cleanMax){
    this->energyMax = energyMax;
    this->hungryMax = hungryMax;
    this->cleanMax = cleanMax;

    energy = energyMax;
    hungry = hungryMax;
    clean = cleanMax;
    
  }

  int getClean(){
    return clean;
  }

  int getHungry(){
    return hungry;
  }

  int getEnergy(){
    return energy;
  }

  void play(){
    if(!testAlive()) return;
    setEnergy(getEnergy() -2);
    setHungry(getHungry() -1);
    setClean(getClean() -3);

    age += 1;
    diamonds +=1;
  }

  void eat(){
    if(!testAlive()) return;
    setEnergy(getEnergy() -1);
    setHungry(getHungry() +4);
    setClean(getClean() -2);

    age += 1;
  }

  bool testSleepy(){
    if( (energyMax - getEnergy()) >= 5 ) return true;
    fn::write("fail: nao esta com sono");
    return false;
  }

  void sleep(){
  if(!testAlive()) return;
  if(!testSleepy()) return;

    /*while(getEnergy() != energyMax){
      setEnergy(getEnergy() +1);
      age += 1;
    }*/
    age += (energyMax  - getEnergy());
    setEnergy(energyMax);
    setHungry(getHungry() -1);
  }

  void shower(){
    if(!testAlive()) return;
    setEnergy(getEnergy() -3);
    setHungry(getHungry() -1);
    setClean(cleanMax);

    age += 2;
  }

  std::string toString(){
    return fn::format( "E:{}/{}, S:{}/{}, L:{}/{}, D:{}, I:{}",energy, energyMax, hungry, hungryMax, clean, cleanMax, diamonds, age );
  }

};

int main(){
  Pet pet;
  
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');

        fn::write("$" + line);

        if (args[0] == "end") {
            break;
        } else if (args[0] == "init") {
            pet.pet(+args[1], +args[2], +args[3]);
        } else if (args[0] == "show") {
            fn::write(pet.toString());
        } else if (args[0] == "play") {
            pet.play();
        } else if (args[0] == "eat") {
            pet.eat();
        } else if (args[0] == "sleep") {
            pet.sleep();
        } else if (args[0] == "shower") {
            pet.shower();
        } else {
           fn::write("fail: comando invalido");
        }
      }
}