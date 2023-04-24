#include<iostream>
#include<sstream>
#include<memory>
#include <fn.hpp>

class Person {
    std::string name;
    int age;
public:
    Person(std::string name , int age) {
      this->name = name;
      this->age = age;
    }

    int getAge() {
        return age;
    }
    std::string getName() {
        return name; 
    }
    std::string str() {
       std::stringstream ss;
       ss << name << ":" << age;
       return ss.str();
    }
};
std::ostream& operator<<(std::ostream& os, Person& p) {
    return os << p.str();
}

class Motorcycle {
    std::shared_ptr<Person> person {nullptr}; //agregação
    int time {0};
    int power {1};


public:
    Motorcycle(int power = 1) { //todo power {power} {
    }

    bool insertPerson(std::shared_ptr<Person> p) {
       if(this->person != nullptr) {
         return fn::write("fail: busy motorcycle");
       }
      this->person = p;
      
    }

    std::string honk() {
        return {}; // todo
    }

    std::shared_ptr<Person> remove() {
        if(this->person == nullptr) {
          fn::write("fail: empty motorcycle");
          return nullptr;
        }

      auto aux = this->person;
      person = nullptr;
      return aux;
      
    }

    void buyTime(int time) {
    }

    void drive(int time) {
    }
    std::string str() {
        std::ostringstream os;
        os << "power:" << power << ", time:" << time;
        os << ", person:(" << (person == nullptr ? "empty" : person->str()) << ")";
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, Motorcycle m) {
    return os << m.str();
}

int main(){

  Motorcycle m;

  while(true) {
    auto line = fn::input();
    auto args = fn::split(line, ' ');
    fn::write('$' + line;);

    if(args[0] == "end") {
      break;
    } else if(args[0] == "show"){
      fn::write(m);
    } else if(args[0] == "enter") {
      auto nome = args[1];
      auto idade = (int) + args[2];
      auto person = make_shared<Person>(nome, idade);
      m.insertPerson(person);
    } else if(args[0] == "remove") {
      fn::write(m.remove());
      
    } else {
      fn::write("Fail: comando invalido")
    }
  }
  
}
