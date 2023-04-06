/*
Tempo: 120 minutos.
-Fiz a atividade sozinho mais uma vez, na hora de olhar como fazer o main(), dei uma olhada no solver_casa.cpp
-Notei que o Readme.md de quando você seleciona o 'l' leva para o Readme.md da questão do carro.
-A implementação de algumas funções foi inspirada na forma de como foi feita em aula. Acho que deve existir um meio de fazer o nextSecond e os casos de init de forma mais eficiente, porém não consegui pensar em nenhum.

*/
#include <iostream>
#include<fn.hpp>

class Time{
  private:
  int hour{0};
  int minute{0};
  int second{0};

  public: 
  void setHour(int h){
    if(h >= 0 && h <= 23){
      hour = h;
    }
    else fn::write("fail: hora invalida");
  }

  void setMinute(int m){
    if(m >= 0 && m <= 59){
      minute = m;
    }
    else fn::write("fail: minuto invalido");
  }

  void setSecond(int s){
   if(s >= 0 && s <= 59){
     second = s;
   }
   else fn::write("fail: segundo invalido");
  }

//
void initHour(int h){
    if(h >= 0 && h <= 23){
      setHour(h);
    }
    else {
      fn::write("fail: hora invalida");
      setHour(0);
    }
  }

  void initMinute(int m){
    if(m >= 0 && m <= 59){
      setMinute(m);
    }
    else {
      fn::write("fail: minuto invalido");
      setMinute(0);
    }
  }

  void initSecond(int s){
   if(s >= 0 && s <= 59){
     setSecond(s);
   }
   else {
     fn::write("fail: segundo invalido");
     setSecond(0);
   }
  }
//
  
  int getHour() {
    return hour;
  }
  int getMinute() {
    return minute;
  }
  int getSecond() {
    return second;
  }

  void nextSecond(){
    if(getSecond() == 59){
      second = 0;
      if(getMinute() == 59){
        setMinute(0);
        if(getHour() == 23){
          setHour(0);
        }else hour += 1;
      } else minute += 1;
    }else second += 1;
    
  }

  std::string toString(){
    return fn::format("{%02d}:{%02d}:{%02d}", hour, minute, second);
  }
};

int main(){
  Time relogio;

  while(true){
    auto line = fn::input();
    fn::write("$" + line);
    std::vector<std::string>args = fn::split(line, ' ');

    if(args[0] == "end") {
      break;
    }
    else if(args[0] == "show") {
      fn::write(relogio.toString());
    }
    else if(args[0] == "set"){
      relogio.setHour(+args[1]);
      relogio.setMinute(+args[2]);
      relogio.setSecond(+args[3]);
    }else if(args[0] == "init"){
      relogio.initHour(+args[1]);
      relogio.initMinute(+args[2]);
      relogio.initSecond(+args[3]);
    }
    else if(args[0] == "next"){
      relogio.nextSecond();
    }
  }
}