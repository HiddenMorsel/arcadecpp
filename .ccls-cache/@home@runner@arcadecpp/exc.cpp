#include<iostream>
#include<vector>  
#include<fn.hpp>

int division (int a, int b){
    return a/b;
    
}

int main(){
  std::vector<int> v;
  
  while(true){
    try{
      auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line);

    if(args[0] == "div"){
      std::cout << division((int)+args[1], (int) +args[2]) << "\n";
    }
    }
    catch(std::exception &e){
      std::cout<< "Nao ha divisao por zero" << "\n";
      
    }
    
    
      
    
  }
}