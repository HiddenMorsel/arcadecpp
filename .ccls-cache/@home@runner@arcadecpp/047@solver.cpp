/*
Tempo: 100 min
-Fiz sozinho, mas pedi ajuda no grupo por conta de que não havia conseguido pensar em uma forma de se obter a base e altura do retângulo.
-Aprendi um pouco mais sobre herança e como aplicar usando o public: Classe e a criar um vetor que receba objetos que descendam de um mesmo tipo usando ponteiro para evitar slicing.
*/

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include<math.h>
#include <fn.hpp>
#include<iomanip>

class Point2D{
  double x;
  double y;

public:
  Point2D(double x = 0, double y = 0) : x(x), y(y){}

  double getX(){
    return x;
  }

  double getY(){
    return y;
  }

  std::string toStr(){
    std::stringstream ss;
    ss << "(" << std::fixed << std::setprecision(2) << x << ", "<< y << ")";
    // return "(" + fn::tostr(x) + ","+ fn::tostr(y) + ")";
    return ss.str();
  }
};

class Calc{
public:
  static double distance(Point2D a, Point2D b){
    return sqrt(pow(b.getX() - a.getX(), 2) + pow(b.getY() - a.getY(), 2));
}
};

class Shape {
  std::string name;

public:
  Shape(std::string name = "") : name(name){}

  std::string getName(){
    return name;
  }

  virtual bool inside(Point2D a) = 0;
  virtual double getArea() = 0;
  virtual double getPerimeter() = 0;
  virtual std::string toString() = 0;
  virtual std::string info() = 0;
};

class Circle : public Shape, Calc{
  Point2D center;
  double radius;
public:
  Circle(Point2D center = {0, 0} , double radius = 0) : center(center), radius(radius){};
  
  bool inside(Point2D a) override{
    if(distance(a, center) < radius) return false;
    return true;
  }

  double getArea() override{
    return pow(radius, 2)*3.1415;
  }

  double getPerimeter() override{
    return 2*3.1415*radius;
  }

  std::string info() override{
    std::stringstream ss;
    ss << "Circ: A=" << std::fixed << std::setprecision(2) << getArea() << " P=" << getPerimeter() << std::endl; 
    return ss.str();
  }

  std::string toString() override{
    std::stringstream ss;
    ss << "Circ: C=" << center.toStr() << ", R=" << std::fixed << std::setprecision(2) << radius << std::endl;
    return ss.str();
    // return "Circ: C=" + center.toStr() + ", R=" + fn::tostr(radius) + "\n";
  }
};

class Rectangle : public Shape, Calc{
  Point2D p1, p2;
public:
  Rectangle(Point2D p1 = {0, 0}, Point2D p2 = {0, 0} ) : p1(p1), p2(p2){}

  bool inside(Point2D a) override{
    if( a.getX() < std::min( p1.getX(), p2.getX() ) || a.getX() > std::max(p1.getX(), p2.getX()) ) return false;
    if ( a.getY() < std::min( p1.getY(), p2.getY() ) || a.getY() > std::max(p1.getY(), p2.getY()) ) return false;

  return true;
  }

  double diagonal(){
     auto d = distance(p1, p2);
    return d;
  }

  double base(){
     auto b = abs(p1.getX() - p2.getX());
    return b;
  }

  double altura(){
    auto h = abs(p1.getY() - p2.getY());
    return h;
  }

   double getArea() override{
    return base() * altura();
     return 0;
  }
   double getPerimeter() override{
    return 2*(base() + altura());
    return 0;
  }

  std::string info() override{
    std::stringstream ss;
    ss << "Rect: A=" << std::fixed << std::setprecision(2) << getArea() << " P=" << getPerimeter() << std::endl; 
    return ss.str();
    return "";
  }

  std::string toString() override{
    std::stringstream ss;
    ss << "Rect: P1=" << p1.toStr() << " P2=" << p2.toStr() << std::endl;
    return ss.str();
  }

};

int main(){
  std::vector<Shape*> shapes;

  while(true){
    auto line = fn::input();
        auto args = fn::split(line, ' ');

        fn::write('$' + line);

        if (args[0] == "end") {
            break;
        } else if( args[0] == "circle"){
          auto c = new Circle( {+args[1], +args[2]} , +args[3]);
          shapes.push_back(c) ;
        }  else if( args[0] == "rect"){
          auto r = new Rectangle( {+args[1], +args[2]}, {+args[3], +args[4]} );
          shapes.push_back(r);
        } else if( args[0] == "info"){
            for(auto a: shapes){
              std::cout<< a->info();
            } 
        } else if( args[0] == "show") {
            for(auto a : shapes){
              std::cout << a->toString();
            }
        } else std::cout<<"fail: comando invalido\n";
  }
  
}