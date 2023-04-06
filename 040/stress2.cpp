/*
-Tempo: 70 minutos
-Fiz tudas as funções sozinho na calada da madrugada.
-Não houveram muitos problemas ou imprevistos.
*/
#include <fn.hpp>
#include <iostream>
#include <vector>

int count(std::vector<int> vet, int x) {
  int cont{0};
  
  for (auto i = 0; i < vet.size(); i++) {
    if (vet[i] == x) {
      cont++;
    }
  }
  return cont;
}

int sum(std::vector<int> vet) {
  int soma{0};
  
  for (auto i = 0; i < vet.size(); i++) {
    if (vet[i] < 0)
      vet[i] *= -1;
    soma += vet[i];
  }
  return soma;
}

double average( std::vector<int> vet) {
  double media = double(sum(vet)) / vet.size();
  return media;
}

bool is_man(int value) {
  if (value > 0)
    return true;
  return false;
}

std::string more_men( std::vector<int> vet) {
  int numMen{0}, numWomen{0};
  
  for (auto i = 0; i < vet.size(); i++) {
    if (is_man(vet[i]))
      numMen += 1;
    else
      numWomen += 1;
  }

  if(numMen > numWomen) return std::string ("men");
  else if(numMen < numWomen) return std::string ("women");
  else return std::string ("draw");
  
}

std::string half_compare( std::vector<int> vet) {
  int stress1{0}, stress2{0}, segundaMetade{0};
  
  for (auto i = 0; i < vet.size()/2; i++) {
    if(vet[i] < 0) vet[i] *=-1;
    stress1 += vet[i];
    segundaMetade = i;
  }

  for (auto i = segundaMetade + 1; i < vet.size(); i++) {
    if(vet[i] < 0) vet[i] *=-1;
    stress2 += vet[i];
  }

  if(stress1 > stress2) return std::string ("first");
  else if(stress1 < stress2) return std::string ("second");
  else return std::string ("draw");
  
}

std::string sex_battle( std::vector<int> vet) {
  int stressMen{0}, stressWomen{0};
  
  for(auto i = 0; i < vet.size(); i++){
    if(is_man(vet[i])) stressMen += vet[i];
    else stressWomen += vet[i];
  }
  
  stressWomen *= -1;
  
  if(stressMen > stressWomen ) return std::string ("men");
  else if(stressMen < stressWomen ) return std::string ("women");
  else return std::string ("draw");
  
}
int main() {

  auto str2vet = [](auto s) {
    return s.substr(1, s.size() - 2) | fn::SPLIT(',') |
           fn::MAP(FNT(x, (int)+x));
  };

  while (true) {
    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line);

    if (args[0] == "end") {
      break;
    } else if (args[0] == "count") {
      count(str2vet(args[1]), +args[2]) | fn::WRITE();
    } else if (args[0] == "sum") {
      sum(str2vet(args[1])) | fn::WRITE();
    } else if (args[0] == "average") {
      average(str2vet(args[1])) | fn::TOSTR("%.2f") | fn::WRITE();
    } else if (args[0] == "more_men") {
      more_men(str2vet(args[1])) | fn::WRITE();
    } else if (args[0] == "sex_battle") { 
      sex_battle(str2vet(args[1])) | fn::WRITE();
    } else if (args[0] == "half_compare"  ) { 
      half_compare(str2vet(args[1])) | fn::WRITE();
    }else {
      fn::write("fail: unknown command");
    }
  }
}