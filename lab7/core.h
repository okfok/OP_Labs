#ifndef CORE_H
#define CORE_H

#include <cmath>
#include <iostream>


class LogWrongArgument: std::exception{
    double _arg;
public:
    LogWrongArgument(double arg): _arg(arg){}

    std::string what () {
        return "Wrong argument given: " + std::to_string(_arg) + " must be > 0";
    }
};

class Function
{
    double _x;

public:
    Function(): _x(0) {}

    Function(double x): _x(x) {}

    double get_x() { return _x; }

    double get_y();
};

#endif // CORE_H
