/*
Tempo : 180 min.
-Eu sou meio lerdo e ruim de lógica então algumas funções demoraram muito mais tempo que outras.
-Com exceção da ajuda pedida ao grupo da monitoria e o geral de POO sobre a main e a função reverse, o código foi feito sozinho, MAS eu pesquisei algoritmo e exemplos de código para problemas cuja lógica tive problemas de imaginar sozinho. Principalmente a ajuda do Geeks for Geeks.
*/#include<iostream>
#include<fn.hpp>

bool is_man(int value) {
  if (value > 0)
    return true;
  return false;
}

std::vector<int> get_men(std::vector<int> vet) {
  std::vector<int>vetMen;
    for(long unsigned int i = 0; i < vet.size(); i++){
      if(is_man(vet[i])) vetMen.push_back(vet[i]);
    }
  return vetMen;
}

std::vector<int> get_calm_women(std::vector<int> vet) {
  std::vector<int>vetCalmWomen;
    for(long unsigned int i = 0; i < vet.size(); i++){
      if( vet[i] < 0 && vet[i] > -10) vetCalmWomen.push_back(vet[i]);
    }
  return vetCalmWomen;
}

std::vector<int> sort(std::vector<int> vet) {
	int aux{0};

  for(long unsigned int i = 0; i < vet.size(); i++){
      for(long unsigned int j = i +1; j < vet.size(); j++){
        if(vet[i] > vet[j]){
          aux = vet[i];
          vet[i] = vet[j];
          vet[j] = aux;
        }
      }
    }
  return vet;
}

std::vector<int> sort_stress(std::vector<int> vet) {
	int aux{0};

  for(long unsigned int i = 0; i < vet.size(); i++){
      for(long unsigned int j = i +1; j < vet.size(); j++){
        if(abs(vet[i]) > abs(vet[j])){
          aux = vet[i];
          vet[i] = vet[j];
          vet[j] = aux;
        }
      }
    }
  return vet;
}

std::vector<int> reverse(std::vector<int> vet) {
	std::vector<int> vetInvertido(0);
  if(vet.size() == 0) return vetInvertido;
  
  int vetSize = vet.size();
  int end{vetSize - 1};
  
  while(vetInvertido.size() < vet.size()) {
    vetInvertido.push_back(vet[end]);
    end--;
  }
  return vetInvertido;
}

bool is_unico(std::vector<int> vet, int value){
  for(auto i = 0; i < vet.size(); i++){
    if( value == vet[i]) return true;
  }
  return false;
}

std::vector<int> unique(std::vector<int> vet) {
  
  if(vet.size() == 0) return vet;

  std::vector<int> vetUnico;
  vetUnico.push_back(vet[0]);
  
	for(auto i = 0; i < vet.size(); i++){
      if(!is_unico(vetUnico, vet[i]) ) {
        vetUnico.push_back(vet[i]);
      }
    }
  return vetUnico;
}

std::vector<int> repeated(std::vector<int> vet) {
  
  if(vet.size() == 0) return vet;
  std::vector<int> vetRepetidos;

  for(auto i = 0; i < vet.size(); i++){
      for(auto j = i + 1; j < vet.size(); j++){
        if(vet[i] == vet[j]){
          vetRepetidos.push_back(vet[i]);
          break;
        }
      }
   }
  return sort(vetRepetidos);
}

int main(){
   auto strToVet = [](auto s) { return fn::map(fn::split(s.substr(1, s.size() - 2), ','), FNT(x, (int)+x)); };

    while(true) {
        std::string line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write('$' + line);

      if (args[0] == "get_men" ) {         
      fn::write(get_men(strToVet(args[1])));  
      }  else if(args[0] == "get_calm_women"      ) {   
      fn::write(get_calm_women(strToVet(args[1]))); 
      } else if(args[0] == "sort"  ) {
      fn::write(sort(strToVet(args[1])));           
      } else if(args[0] == "sort_stress" ) { 
      fn::write(sort_stress(strToVet(args[1])));    
      } else if(args[0] == "reverse"  ) {     
      fn::write(reverse(strToVet(args[1])));        
      } else if(args[0] == "unique"         ) { 
      fn::write(unique(strToVet(args[1])));         
      } else if(args[0] == "repeated"       ) {              
      fn::write(repeated(strToVet(args[1])));       
      } else if(args[0] == "end"  ) { 
      break; 
      }
      
     }
}