#include<iostream>
#include<fn.hpp>
using namespace fn;
using namespace std;

struct Car{
  int pass{0};
  int gas{0};
  int km{0};

  void entrar(){
    if(pass == 2){
      write("fail: limite de pessoas atingido");
      return;
    }
    pass += 1;
  }

  string str(){
    return "pass: " + tostr(pass) +", gas: " + tostr(gas) + ", km: " + tostr(km);
  }

  void abastecer(int qtd){
    gas += qtd;
  }
};

int main(){
  Car car;

  while(true){
    auto line = input();
    write("$" + line);
    vector<string> args = split(line, ' ');

    if (args[0] == "end") {
      break;
    }
    else if (args[0] == "show"){
      write(car.str());
    }
    else if (args[0] == "enter"){
      car.entrar();
    }
    else if(args[0] == "fuel"){
      car.abastecer(+args[1]);
    }
  }
  
}