#include <iostream>
#include <algorithm>
#include <vector>
#include <fn.hpp>

using namespace fn;

std::vector<int> get_men(std::vector<int> vet) {
	//To do
}

std::vector<int> get_calm_women(std::vector<int> vet) {
	//To do
}

std::vector<int> sort(std::vector<int> vet) {
	//To do
}

std::vector<int> sort_stress(std::vector<int> vet) {
	//To do
}

std::vector<int> reverse(std::vector<int> vet) {
	//To do
}

void reverse_inplace(std::vector<int> &vet) {
	//To do
}

std::vector<int> unique(std::vector<int> vet) {
	//To do
}

std::vector<int> repeated(std::vector<int> vet) {
	//To do
}

int main() {
    auto strToVet = [](auto s) { return map(split(s.substr(1, s.size() - 2), ','), FNT(x, (int)+x)); };

    while(true) {
        std::string line = input();
        auto args = split(line, ' ');
        write('$' + line);

        if     (args[0] == "get_men"        ) { write(get_men(strToVet(args[1])));        }
        else if(args[0] == "get_calm_women" ) { write(get_calm_women(strToVet(args[1]))); }
        else if(args[0] == "sort"           ) { write(sort(strToVet(args[1])));           }
        else if(args[0] == "sort_stress"    ) { write(sort_stress(strToVet(args[1])));    }
        else if(args[0] == "reverse"        ) { write(reverse(strToVet(args[1])));        }
        else if(args[0] == "reverse_inplace") { 
            auto vet = strToVet(args[1]);
            reverse_inplace(vet);
            write(vet);
        }
        else if(args[0] == "unique"         ) { write(unique(strToVet(args[1])));         }
        else if(args[0] == "repeated"       ) { write(repeated(strToVet(args[1])));       }
        else if(args[0] == "end"            ) { break;                                    }
    }
}