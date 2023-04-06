/* Tempo: 140 min 
-Fiz a atividade sozinho, como não estava familiarizado com alguns detalhes principalmente a respeito de preparar a função main para os testes foi dado uma olhada no solver.cpp para ver como escrevia o código de forma correta.
-O código foi escrito conforme lia-se os problemas e implementava cada função por vez, a função de drive foi a que mais demorou para ser escrita, pois não estava conseguindo pensar em uma boa estratégia para o caso de uma viagem de longa distância.
-Não revi o padrão de escrita de código da matéria, então algumas coisas podem não estar em um estado de apresentação ideal.
*/
#include<iostream>
#include<fn.hpp>
using namespace std;
using namespace fn;

struct Car{
  int pass{0};
  int passMax{2};
  int km{0};
  int gas{0};
  int gasMax{100};

  void enter(){
      if(pass == passMax){
        write("fail: limite de pessoas atingido"); 
        return;
      }
    pass +=1;
  }

  void leave(){
      if(pass == 0){
        write("fail: nao ha ninguem no carro");
        return;
      }
    pass -=1;
  }

  void fuel(int combustivel){
    gas += combustivel;
    if(combustivel >= gasMax){
      gas = gasMax;
      return;
    }
    
  }

  void drive(int distancia){
    if(pass == 0){
      write("fail: nao ha ninguem no carro");
      return;
      
    }if(gas == 0){
      write("fail: tanque vazio");
      return;
    }
    if(gas - distancia < 0){
      write("fail: tanque vazio apos andar "+ tostr(gas) +" km");
      km += gas;
      gas = 0;
      return;
    }
    km += distancia;
    gas -= distancia;
  }

  string info(){
    return "pass: " + tostr(pass) + ", gas: " + tostr(gas) + ", km: "+ tostr(km);
  }
};

int main(){
  Car carro;

  while(true){
    auto line = input();
    write("$" + line);
    vector<string> argumento = split(line, ' ');

    if(argumento[0] == "enter"){
      carro.enter();
    }
    else if(argumento[0] == "leave"){
      carro.leave();
    }
    else if(argumento[0] == "show"){
      write(carro.info());
    }
    else if(argumento[0] == "fuel"){
      carro.fuel(+argumento[1]);
    }
    else if(argumento[0] == "drive"){
      carro.drive(+argumento[1]);
    }
    else if(argumento[0] == "end"){
      break;
    }
  }
}