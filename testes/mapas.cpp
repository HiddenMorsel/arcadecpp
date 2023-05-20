#include<algorithm>
#include<fn.hpp>
#include<map>

int main(){
  std::map<std::string, int> series;

  series["OreImo"] = 12;
  series["Chuunibyou"] = 13;
  series["Clannad"] = 25;

  fn::write(series);

  for(auto& [nome, episodios] : series) {
    episodios += 1;
    std::cout << "Nome: "<< nome << " Episodios: " << episodios << "\n";
  }

  auto iterador = series.find("Chuunibyou");
  
  
}