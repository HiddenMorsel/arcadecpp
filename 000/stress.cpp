/*Tempo: 50 min
-Resolução para criar as funções em si foi rápida, mas encontrei um problema na função min_element, onde por conta da verificação de se o vetor era vazio só ocorrer após a criação da variável min fazia um erro aparecer.
-Tive ajuda de monitores durante o almoço com código, a dúvida também foi postada no Discord, mas não tive tempo de ver o site e discutir o problema lá.
*/
#include<iostream>
#include<vector>
#include<fn.hpp>

bool in(std::vector<int> vet, int num){
  for (int elem : vet) {
    if(elem == num)
      return true; 
  }
  return false;
}

int index_of(std::vector<int>vet, int num){
  for (auto i = 0; i < vet.size(); i++){
    if( vet[i] == num) return i;
  }
  return -1;
}

int find_if(std::vector<int>vet){
  for (auto i = 0; i < vet.size(); i++){
    if( vet[i] > 0) return i;
  }
  return -1;
  
}

int min_element(std::vector<int>vet){
  if(vet.size() == 0) return -1;
  
  int min = vet[0], minIndx{0};
  
  for (auto i = 0; i < vet.size(); i++){
    if( vet[i] < min) {
      min = vet[i];
      minIndx = i;
    }
  }return minIndx;
}

int find_min_if(std::vector<int>vet){
  if(vet.size() == 0) return -1;

  int min = vet[0], minIndx{-1};

  for(auto i = 0;i < vet.size(); i++) {
    if(vet[i] > 0 && vet[i] < min){
      min = vet[i];
      minIndx = i;
    }
  } return minIndx;
  
}

int main(){

  auto STRTOVET = [](auto s) { return fn::map(fn::split(s.substr(1, s.size() - 2), ','), FNT(x, (int)+x)); };

  while(true){
    auto line = fn::input();
    fn::write('$' + line);
    auto args = fn::split(line);

    if(args[0] == "end"){
      break;
    }
    else if(args[0] == "in"){
      fn::write(   fn::tostr(in(STRTOVET(args[1]), +args[2])));
    }
    else if (args[0] == "index_of") { 
      fn::write(  index_of(STRTOVET(args[1]), +args[2]));  
    }
     else if (args[0] == "find_if") {
       fn::write(  find_if(STRTOVET(args[1])));           
    }
    else if (args[0] == "min_element") { 
      fn::write(  min_element(STRTOVET(args[1])));
    }else if (args[0] == "find_min_if") { 
      fn::write(find_min_if(STRTOVET(args[1])));           
    }
    else { 
      fn::write("fail: unknown command");                   
    }
  }
  
}