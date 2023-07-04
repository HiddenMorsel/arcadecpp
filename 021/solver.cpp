/*
-Tempo: 150 min
-Aprendi que é preciso ter muito cuidado com o que é passado como referência e o que é cópia, pois isso pode gerar inconsistência de arquivos.
-Vi como organizar relações de dependência entre classes, principalmente como se deve lidar com as declarações, já que por conta dessa atividade ter sido realizada no replit não foi possível utilizar headers.
-Fiz a atividade tirando dúvidas com o monitor no almoço com código e o professor por meio do Telegram.

*/

#include<iostream>
#include<iomanip>
#include<map>
#include<fn.hpp>
#include<string>
#include<sstream>

class Aluno;
class IDisciplina {
std::string id;
std::map<std::string, Aluno> alunos;
public:  
  virtual std::string getId() = 0;

};
class Sistema;

class Aluno{
  std::string id;
  std::map<std::string, IDisciplina*> disciplinas;
public:
  Aluno(std::string id) : id(id){}

  std::string getId(){
    return id;
  }

  std::string toString() {
    std::string  ss = "";
    ss += getId() + " ["; 
    for(auto d: disciplinas) {
      ss += d.second->getId(); 
      if( d.first != disciplinas.rbegin()->first) ss += ", ";
    }
    ss += "]\n";
    return ss;
    
  }

  void addDisciplina(IDisciplina* disc, std::string discName) {
    disciplinas.insert({discName, disc });
  }

  void rmDisciplina(std::string idDisciplina) {
    disciplinas.erase(idDisciplina);
  }

};

class Disciplina : public IDisciplina{
  std::string id;
  std::map<std::string, Aluno*> alunos;
public:
  Disciplina(std::string id) : id(id){}

  std::string getId(){
    return id;
  }

  std::string toString(){
    std::string  ss = "";
    ss += getId() + " ["; 
    for(auto d: alunos) {
      ss += d.second->getId(); 
      if( d.first != alunos.rbegin()->first) ss += ", ";
    }
    ss += "]\n";
    return ss;
  }

  void addAluno(Aluno* aluno){
      alunos.insert( {aluno->getId(), {aluno}});
  }

  void rmAluno(std::string idAluno) {
    alunos.erase(idAluno);
  }

};

class Sistema{
  std::map<std::string, Aluno> alunos;
  std::map<std::string, Disciplina> disciplinas;
public:
  Sistema(std::map<std::string, Aluno>, std::map<std::string, Disciplina> ){}

  void addAluno(std::string id) {
    alunos.insert({id, {id}});
  }

  void addDisci(std::string id) {
     disciplinas.insert({id, id});
  }

  void show() {
    std::string ss = "- alunos\n";
    for(auto& e : alunos) {
      ss +=  e.second.toString() ;
    }
    
    ss+= "- discps\n";

    for(auto& d : disciplinas) {
     ss += d.second.toString();
    }
    
    ss.erase(ss.size() -1);
    std::cout << ss << "\n";
  }

  void matricular(std::string idAluno, std::string idDisciplina) {
    if(alunos.count(idAluno) == 0) throw "fail: aluno " + idAluno + " não existe";
    if(disciplinas.count(idDisciplina) == 0) throw "fail: disciplina " + idDisciplina + " não existe";

    auto it = alunos.find(idAluno);
    auto disc = disciplinas.find(idDisciplina);
    
    it->second.addDisciplina(&disc->second, idDisciplina);
    disc->second.addAluno(&it->second);
    
  }

  void desmatricular(std::string idAluno, std::string idDisciplina) {
    if(alunos.count(idAluno) == 0) throw "fail: aluno " + idAluno + " não existe";
    if(disciplinas.count(idDisciplina) == 0) throw "fail: disciplina " + idDisciplina + " não existe";

    auto aluno = alunos.find(idAluno);
    auto disc = disciplinas.find(idDisciplina);

    disc->second.rmAluno(idAluno);
    aluno->second.rmDisciplina(idDisciplina);
  }

  void rmAluno(std::string idAluno){
    if(alunos.count(idAluno) == 0) throw "fail: aluno " + idAluno + " não existe";

    for(auto& d : disciplinas) {
        d.second.rmAluno(idAluno);
    }
    alunos.erase(idAluno);
  }

  void rmDisciplina(std::string idDisciplina){
    if(disciplinas.count(idDisciplina) == 0) throw "fail: disciplina " + idDisciplina + " não existe";

    for(auto& d : alunos) {
        d.second.rmDisciplina(idDisciplina);
    }
    disciplinas.erase(idDisciplina);
  }
  
};

int main(){
  Sistema s({{}, {}});

  while(true) {
    std::string line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line, ' ');

    try{
      if(args[0] == "nwalu") {
        for(int i = 1; i < (int) args.size(); i++){
          s.addAluno(args[i]);
        }
      } else if(args[0] == "nwdis"){
          for(int i = 1; i < (int) args.size(); i++){
            s.addDisci(args[i]);
          }
      } else if(args[0] == "show") {
        s.show();
      } else if(args[0] == "end") {
        break;
      } else if(args[0] == "tie") {
        for(int i = 2; i < (int) args.size(); i++){
            s.matricular(args[1], args[i]);
          }
      } else if(args[0] == "untie") {
        for(int i = 2; i < (int) args.size(); i++){
            s.desmatricular(args[1], args[i]);
          }
      } else if(args[0] == "rmalu") {
          s.rmAluno(args[1]);
      } else if(args[0] == "rmdisc") {
          s.rmDisciplina(args[1]);
      }
    } catch(std::out_of_range& whoops){
      std::cout << whoops.what() << "\n";
    }
    
  }
  
}