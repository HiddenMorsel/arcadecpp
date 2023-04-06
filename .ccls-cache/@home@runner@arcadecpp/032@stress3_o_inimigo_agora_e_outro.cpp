#include<iostream>
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



int main(){
   auto strToVet = [](auto s) { return s.substr(1, s.size() - 2) | fn::SPLIT(',') | fn::MAP(FNT(x, (int)+x)); };

    while(true) {
        std::string line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write('$' + line);

      if (args[0] == "get_men" ) {    
      fn::write(get_men(fn::TOSTR(args[1])));        
      } else if(args[0] == "end" ) { 
        break;                                    
      }

    }
}