#include <iostream>
#include <sstream>
#include <iomanip>
#include <aux.hpp>

class Time {
private:
    int hour {0}, minute {0}, second {0};
public:
    Time(int hour = 0, int minute = 0, int second = 0) {
      setHour(hour);
      setMinute(minute);
      setSecond(second);
    }
    void setHour(int hour) {
      if (hour >= 0 && hour <= 23){
        this ->hour = hour;
      }else fn::write("fail: hora invalida");
    }
    void setMinute(int minute) {
      if (minute >= 0 && minute <= 59){
        this ->minute = minute;
      }else fn::write("fail: minuto invalido");
    }
    void setSecond(int second) {
      if (second >= 0 && second <= 59){
        this ->second = second;
      }else else fn::write("fail: segundo invalido");
    }
    int getHour() {
        return hour; // todo
    }
    int getMinute() {
        return minute; // todo
    }
    int getSecond() {
        return second; // todo
    }
    void nextSecond() {
    }
    std::string str() {
        return fn::format("{02%d}:{02%d}:{02%d}", hour, minute, second);
        /*std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << hour << ":"
           << std::setfill('0') << std::setw(2) << minute << ":"
           << std::setfill('0') << std::setw(2) << second;
        return ss.str();*/
    }
};

int main() {
    aux::Chain chain;
    aux::Param param;
    Time time;

    auto INT = aux::STR2<int>();

    chain["set"] = [&]() {
        time.setHour(INT(param[1]));
        time.setMinute(INT(param[2]));
        time.setSecond(INT(param[3]));
    };
    chain["init"] = [&]() {
        time = Time(INT(param[1]), INT(param[2]), INT(param[3]));
    };
    chain["show"] = [&]() {
        std::cout << time.str() << '\n';
    };
    chain["next"] = [&]() {
        time.nextSecond();
    };

    aux::execute(chain, param);
}