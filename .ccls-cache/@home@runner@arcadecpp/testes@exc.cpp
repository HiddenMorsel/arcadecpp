#include<iostream>
#include<vector>  
#include<fn.hpp>

int division (int a, int b){
  if(b == 0){
    throw std::runtime_error("Divide by zero");
  }
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
        auto r =  division((int)+args[1], (int) +args[2]) ;
        std::cout<<"A divisao é:" <<  r << '\n';
      }
    }
    catch(std::exception &e){
      std::cout<< e.what() << "\n";
      
    }
    
    
      
    
  }
}